#define WIN32_LEAN_AND_MEAN

#include <thread>
#include <windows.h>

#include "version.h"
extern "C" UINT_PTR procs[17]{0};

HMODULE hModule = nullptr;
UINT32 langID = 0;

static void GetLangID();

unsigned __stdcall RemoveLangRestriction(void *) {
  GetLangID();

  HMODULE fc64 = nullptr;
  while (!fc64) {
    fc64 = GetModuleHandle("FC64.dll");
    Sleep(10);
  }

  UINT_PTR base = (UINT_PTR)fc64;
  UINT_PTR baseStruct = base + 0x2D577F0;
  UINT32 *baseLangID = (UINT32 *)(baseStruct + 0x50);

  while (*baseLangID != 17)
    ;

  *baseLangID = langID;

  return 0;
}

BOOL WINAPI DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
  if (fdwReason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hinstDLL);
    SetupWrappers();
    hModule = hinstDLL;

    UINT_PTR hThread =
        _beginthreadex(NULL, 0, RemoveLangRestriction, NULL, 0, NULL);
    if (hThread)
      CloseHandle((HANDLE)hThread);
  }
  return TRUE;
}

static void GetLangID() {
  wchar_t path[MAX_PATH];
  GetModuleFileNameW(nullptr, path, MAX_PATH);
  wchar_t *lastSlash = wcsrchr(path, L'\\');
  if (lastSlash)
    *lastSlash = L'\0';
  wcscat_s(path, L"\\lang_fix.ini");
  langID = GetPrivateProfileIntW(L"Settings", L"Lang", 0, path);
}
