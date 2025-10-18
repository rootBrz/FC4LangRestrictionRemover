#define WIN32_LEAN_AND_MEAN

#include <thread>
#include <windows.h>

#include "version.h"
extern "C" UINT_PTR procs[17]{0};

HMODULE hModule = nullptr;
UINT32 langID = 17;

void GetLangID();

struct
{
    HKEY hKey = nullptr;
    DWORD dwType = REG_DWORD;
    DWORD dwValue = 0;
    DWORD dwSize = sizeof(dwValue);
    DWORD dwDisp = 0;
} LangRegKey;

unsigned __stdcall
RemoveLangRestriction(void *)
{
    GetLangID();

    HMODULE fc64 = nullptr;
    while (!fc64)
    {
        fc64 = GetModuleHandle("FC64.dll");
        Sleep(10);
    }

    UINT_PTR base = (UINT_PTR)fc64;
    UINT_PTR baseStruct = base + 0x2D577F0;
    UINT32 *baseLangID = (UINT32 *)(baseStruct + 0x50);

    // Default lang set to 17 in game's struct
    while (*baseLangID != 17)
        ;

    *baseLangID = langID;

    // Struct holds lang ID at 0x58, 0xD0 and 0xD4
    UINT_PTR *computedStruct = (UINT_PTR *)(base + 0x2DD6A90);

    while (true)
    {
        UINT_PTR structPtr = *computedStruct;
        if (!structPtr) goto CONTINUE;

        UINT32 *currentLangID = (UINT32 *)(structPtr + 0xD0);
        if (!currentLangID) goto CONTINUE;

        if (langID == *currentLangID) goto CONTINUE;
        langID = *currentLangID;

        if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Ubisoft\\farcry4", 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &LangRegKey.hKey, &LangRegKey.dwDisp) != ERROR_SUCCESS)
            goto CONTINUE;

        RegSetValueExW(LangRegKey.hKey, L"InterfaceLang", 0, REG_DWORD, (const BYTE *)&langID, sizeof(langID));
        RegCloseKey(LangRegKey.hKey);

    CONTINUE:
        Sleep(500);
    }

    return 0;
}

BOOL WINAPI DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        SetupWrappers();
        hModule = hinstDLL;

        UINT_PTR hThread = _beginthreadex(NULL, 0, RemoveLangRestriction, NULL, 0, NULL);
        if (hThread) CloseHandle((HANDLE)hThread);
    }
    return TRUE;
}

void GetLangID()
{
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Ubisoft\\farcry4", 0, KEY_READ, &LangRegKey.hKey) != ERROR_SUCCESS) goto CLEAN;
    if (RegQueryValueExW(LangRegKey.hKey, L"InterfaceLang", nullptr, &LangRegKey.dwType, (LPBYTE)&LangRegKey.dwValue, &LangRegKey.dwSize) != ERROR_SUCCESS) goto CLEAN;
    if (LangRegKey.dwType == REG_DWORD) langID = LangRegKey.dwValue;

CLEAN:
    if (LangRegKey.hKey) RegCloseKey(LangRegKey.hKey);
}
