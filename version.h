#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdio>

extern "C" UINT_PTR procs[17];

LPCSTR FuncNames[] = {"GetFileVersionInfoA",
                      "GetFileVersionInfoByHandle",
                      "GetFileVersionInfoExA",
                      "GetFileVersionInfoExW",
                      "GetFileVersionInfoSizeA",
                      "GetFileVersionInfoSizeExA",
                      "GetFileVersionInfoSizeExW",
                      "GetFileVersionInfoSizeW",
                      "GetFileVersionInfoW",
                      "VerFindFileA",
                      "VerFindFileW",
                      "VerInstallFileA",
                      "VerInstallFileW",
                      "VerLanguageNameA",
                      "VerLanguageNameW",
                      "VerQueryValueA",
                      "VerQueryValueW"};

void SetupWrappers() {
  CHAR sys_dir[MAX_PATH];
  GetSystemDirectoryA(sys_dir, MAX_PATH);
  char buffer[MAX_PATH];
  sprintf_s(buffer, "%s\\version.dll", sys_dir);
  HMODULE versionDLL = LoadLibraryA(buffer);
  for (int i = 0; i < 17; i++) {
    procs[i] =
        reinterpret_cast<UINT_PTR>(GetProcAddress(versionDLL, FuncNames[i]));
  }
}

extern "C" void GetFileVersionInfoA_wrapper();
extern "C" void GetFileVersionInfoByHandle_wrapper();
extern "C" void GetFileVersionInfoExA_wrapper();
extern "C" void GetFileVersionInfoExW_wrapper();
extern "C" void GetFileVersionInfoSizeA_wrapper();
extern "C" void GetFileVersionInfoSizeExA_wrapper();
extern "C" void GetFileVersionInfoSizeExW_wrapper();
extern "C" void GetFileVersionInfoSizeW_wrapper();
extern "C" void GetFileVersionInfoW_wrapper();
extern "C" void VerFindFileA_wrapper();
extern "C" void VerFindFileW_wrapper();
extern "C" void VerInstallFileA_wrapper();
extern "C" void VerInstallFileW_wrapper();
extern "C" void VerLanguageNameA_wrapper();
extern "C" void VerLanguageNameW_wrapper();
extern "C" void VerQueryValueA_wrapper();
extern "C" void VerQueryValueW_wrapper();
