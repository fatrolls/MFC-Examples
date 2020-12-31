//////////////////////////////////////////////////////////////////////
//
//	File:		tracereg.cpp
//	Module:		tracereg.dll
//	Copyright:	1996-2001, Microsoft Corporation
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
#define _WIN32_WINNT		0x0400
#define WIN32
#define NT

#define DBG_TRACE   0

#include <windows.h>
#include <stdio.h>
#include "detours.h"
#include "syelog.h"

#define PULONG_PTR			PVOID
#define PLONG_PTR			PVOID
#define ULONG_PTR			PVOID
#define LONG_PTR			PVOID
#define ENUMRESNAMEPROCA 	PVOID
#define ENUMRESNAMEPROCW 	PVOID
#define ENUMRESLANGPROCA 	PVOID
#define ENUMRESLANGPROCW 	PVOID
#define ENUMRESTYPEPROCA 	PVOID
#define ENUMRESTYPEPROCW 	PVOID
#define STGOPTIONS          PVOID

//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4127)   // Many of our asserts are constants.

#ifndef _DEFINED_ASMBREAK_
#define _DEFINED_ASMBREAK_
#define ASMBREAK()	__asm { int 3 }
//#define ASMBREAK()	DebugBreak()
#endif	// _DEFINED_ASMBREAK_

#define ASSERT_ALWAYS(x)   \
    do {                                                        \
	if (!(x)) {                                                 \
            AssertMessage(#x, __FILE__, __LINE__);              \
			ASMBREAK();                                         \
	}                                                           \
    } while (0)

#ifndef NDEBUG
#define ASSERT(x)           ASSERT_ALWAYS(x)
#else
#define ASSERT(x)
#endif

#define UNUSED(c)    	(c) = (c)
#define ARRAYOF(x)	   	(sizeof(x)/sizeof(x[0]))

//////////////////////////////////////////////////////////////////////
static HINSTANCE s_hInst;
static WCHAR s_wzDllPath[MAX_PATH];

BOOL ProcessEnumerate();
BOOL InstanceEnumerate(HINSTANCE hInst);

VOID _PrintEnter(PCSTR psz, ...);
VOID _PrintExit(PCSTR psz, ...);
VOID _Print(PCSTR psz, ...);

VOID AssertMessage(CONST PCHAR pszMsg, CONST PCHAR pszFile, ULONG nLine);

//////////////////////////////////////////////////////////////////////////////
//
#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

extern "C" {
    DETOUR_TRAMPOLINE(HANDLE WINAPI
                      Real_CreateFileW(LPCWSTR a0,
                                       DWORD a1,
                                       DWORD a2,
                                       LPSECURITY_ATTRIBUTES a3,
                                       DWORD a4,
                                       DWORD a5,
                                       HANDLE a6),
                      CreateFileW);

    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_WriteFile(HANDLE hFile,
                                     LPCVOID lpBuffer,
                                     DWORD nNumberOfBytesToWrite,
                                     LPDWORD lpNumberOfBytesWritten,
                                     LPOVERLAPPED lpOverlapped),
                      WriteFile);
    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_FlushFileBuffers(HANDLE hFile),
                      FlushFileBuffers);
    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_CloseHandle(HANDLE hObject),
                      CloseHandle);

    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_WaitNamedPipeW(LPCWSTR lpNamedPipeName, DWORD nTimeOut),
                      WaitNamedPipeW);
    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_SetNamedPipeHandleState(HANDLE hNamedPipe,
                                                   LPDWORD lpMode,
                                                   LPDWORD lpMaxCollectionCount,
                                                   LPDWORD lpCollectDataTimeout),
                      SetNamedPipeHandleState);

    DETOUR_TRAMPOLINE(DWORD WINAPI
                      Real_GetCurrentProcessId(VOID),
                      GetCurrentProcessId);
    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime),
                      GetSystemTimeAsFileTime);

    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_InitializeCriticalSection(LPCRITICAL_SECTION lpSection),
                      InitializeCriticalSection);
    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_EnterCriticalSection(LPCRITICAL_SECTION lpSection),
                      EnterCriticalSection);
    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_LeaveCriticalSection(LPCRITICAL_SECTION lpSection),
                      LeaveCriticalSection);
}

//////////////////////////////////////////////////////////////////////////////
//

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CopyFileExA(LPCSTR a0,
                                                  LPCSTR a1,
                                                  LPPROGRESS_ROUTINE a2,
                                                  LPVOID a3,
                                                  LPBOOL a4,
                                                  DWORD a5),
                  CopyFileExA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CopyFileExW(LPCWSTR a0,
                                                  LPCWSTR a1,
                                                  LPPROGRESS_ROUTINE a2,
                                                  LPVOID a3,
                                                  LPBOOL a4,
                                                  DWORD a5),
                  CopyFileExW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CreateDirectoryExW(LPCWSTR a0,
                                                         LPCWSTR a1,
                                                         LPSECURITY_ATTRIBUTES a2),
                  CreateDirectoryExW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CreateDirectoryW(LPCWSTR a0,
                                                       LPSECURITY_ATTRIBUTES a1),
                  CreateDirectoryW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CreateProcessW(LPCWSTR lpApplicationName,
                                                  LPWSTR lpCommandLine,
                                                  LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                                  LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                                  BOOL bInheritHandles,
                                                  DWORD dwCreationFlags,
                                                  LPVOID lpEnvironment,
                                                  LPCWSTR lpCurrentDirectory,
                                                  LPSTARTUPINFOW lpStartupInfo,
                                                  LPPROCESS_INFORMATION lpProcessInformation),
                  CreateProcessW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_DeleteFileA(LPCSTR a0),
                  DeleteFileA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_DeleteFileW(LPCWSTR a0),
                  DeleteFileW);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_FindFirstFileExA(LPCSTR a0,
                                                         FINDEX_INFO_LEVELS a1,
                                                         LPVOID a2,
                                                         FINDEX_SEARCH_OPS a3,
                                                         LPVOID a4,
                                                         DWORD a5),
                  FindFirstFileExA);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_FindFirstFileExW(LPCWSTR a0,
                                                         FINDEX_INFO_LEVELS a1,
                                                         LPVOID a2,
                                                         FINDEX_SEARCH_OPS a3,
                                                         LPVOID a4,
                                                         DWORD a5),
                  FindFirstFileExW);

DETOUR_TRAMPOLINE(DWORD WINAPI Real_GetFileAttributesW(LPCWSTR a0),
                  GetFileAttributesW);

DETOUR_TRAMPOLINE(DWORD WINAPI Real_GetModuleFileNameW(HMODULE a0,
                                                          LPWSTR a1,
                                                          DWORD a2),
                  GetModuleFileNameW);

DETOUR_TRAMPOLINE(FARPROC WINAPI Real_GetProcAddress(struct HINSTANCE__* a0,
                                                        LPCSTR a1),
                  GetProcAddress);

DETOUR_TRAMPOLINE(HMODULE WINAPI Real_LoadLibraryExW(LPCWSTR a0,
                                                        HANDLE a1,
                                                        DWORD a2),
                  LoadLibraryExW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_MoveFileA(LPCSTR a0,
                                                LPCSTR a1),
                  MoveFileA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_MoveFileExA(LPCSTR a0,
                                                  LPCSTR a1,
                                                  DWORD a2),
                  MoveFileExA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_MoveFileExW(LPCWSTR a0,
                                                  LPCWSTR a1,
                                                  DWORD a2),
                  MoveFileExW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_MoveFileW(LPCWSTR a0,
                                                LPCWSTR a1),
                  MoveFileW);

DETOUR_TRAMPOLINE(HFILE WINAPI Real_OpenFile(LPCSTR a0,
                                                struct _OFSTRUCT* a1,
                                                UINT a2),
                  OpenFile);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegCreateKeyExA(HKEY a0,
                                                      LPCSTR a1,
                                                      DWORD a2,
                                                      LPSTR a3,
                                                      DWORD a4,
                                                      REGSAM a5,
                                                      LPSECURITY_ATTRIBUTES a6,
                                                      PHKEY a7,
                                                      LPDWORD a8),
                  RegCreateKeyExA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegCreateKeyExW(HKEY a0,
                                                      LPCWSTR a1,
                                                      DWORD a2,
                                                      LPWSTR a3,
                                                      DWORD a4,
                                                      REGSAM a5,
                                                      LPSECURITY_ATTRIBUTES a6,
                                                      PHKEY a7,
                                                      LPDWORD a8),
                  RegCreateKeyExW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegDeleteKeyA(HKEY a0,
                                                    LPCSTR a1),
                  RegDeleteKeyA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegDeleteKeyW(HKEY a0,
                                                    LPCWSTR a1),
                  RegDeleteKeyW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegDeleteValueA(HKEY a0,
                                                      LPCSTR a1),
                  RegDeleteValueA);


DETOUR_TRAMPOLINE(LONG WINAPI Real_RegDeleteValueW(HKEY a0,
                                                      LPCWSTR a1),
                  RegDeleteValueW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegEnumKeyExA(HKEY a0,
                                                    DWORD a1,
                                                    LPSTR a2,
                                                    LPDWORD a3,
                                                    LPDWORD a4,
                                                    LPSTR a5,
                                                    LPDWORD a6,
                                                    struct _FILETIME* a7),
                  RegEnumKeyExA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegEnumKeyExW(HKEY a0,
                                                    DWORD a1,
                                                    LPWSTR a2,
                                                    LPDWORD a3,
                                                    LPDWORD a4,
                                                    LPWSTR a5,
                                                    LPDWORD a6,
                                                    struct _FILETIME* a7),
                  RegEnumKeyExW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegEnumValueA(HKEY a0,
                                                    DWORD a1,
                                                    LPSTR a2,
                                                    LPDWORD a3,
                                                    LPDWORD a4,
                                                    LPDWORD a5,
                                                    LPBYTE a6,
                                                    LPDWORD a7),
                  RegEnumValueA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegEnumValueW(HKEY a0,
                                                    DWORD a1,
                                                    LPWSTR a2,
                                                    LPDWORD a3,
                                                    LPDWORD a4,
                                                    LPDWORD a5,
                                                    LPBYTE a6,
                                                    LPDWORD a7),
                  RegEnumValueW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegOpenKeyExA(HKEY a0,
                                                    LPCSTR a1,
                                                    DWORD a2,
                                                    REGSAM a3,
                                                    PHKEY a4),
                  RegOpenKeyExA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegOpenKeyExW(HKEY a0,
                                                    LPCWSTR a1,
                                                    DWORD a2,
                                                    REGSAM a3,
                                                    PHKEY a4),
                  RegOpenKeyExW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegQueryInfoKeyA(HKEY a0,
                                                       LPSTR a1,
                                                       LPDWORD a2,
                                                       LPDWORD a3,
                                                       LPDWORD a4,
                                                       LPDWORD a5,
                                                       LPDWORD a6,
                                                       LPDWORD a7,
                                                       LPDWORD a8,
                                                       LPDWORD a9,
                                                       LPDWORD a10,
                                                       struct _FILETIME* a11),
                  RegQueryInfoKeyA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegQueryInfoKeyW(HKEY a0,
                                                       LPWSTR a1,
                                                       LPDWORD a2,
                                                       LPDWORD a3,
                                                       LPDWORD a4,
                                                       LPDWORD a5,
                                                       LPDWORD a6,
                                                       LPDWORD a7,
                                                       LPDWORD a8,
                                                       LPDWORD a9,
                                                       LPDWORD a10,
                                                       struct _FILETIME* a11),
                  RegQueryInfoKeyW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegQueryValueExA(HKEY a0,
                                                       LPCSTR a1,
                                                       LPDWORD a2,
                                                       LPDWORD a3,
                                                       LPBYTE a4,
                                                       LPDWORD a5),
                  RegQueryValueExA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegQueryValueExW(HKEY a0,
                                                       LPCWSTR a1,
                                                       LPDWORD a2,
                                                       LPDWORD a3,
                                                       LPBYTE a4,
                                                       LPDWORD a5),
                  RegQueryValueExW);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegSetValueExA(HKEY a0,
                                                     LPCSTR a1,
                                                     DWORD a2,
                                                     DWORD a3,
                                                     BYTE* a4,
                                                     DWORD a5),
                  RegSetValueExA);

DETOUR_TRAMPOLINE(LONG WINAPI Real_RegSetValueExW(HKEY a0,
                                                     LPCWSTR a1,
                                                     DWORD a2,
                                                     DWORD a3,
                                                     BYTE* a4,
                                                     DWORD a5),
                  RegSetValueExW);

DETOUR_TRAMPOLINE(HFILE WINAPI Real__lcreat(LPCSTR a0,
                                               int a1),
                  _lcreat);

DETOUR_TRAMPOLINE(HFILE WINAPI Real__lopen(LPCSTR a0,
                                              int a1),
                  _lopen);

/////////////////////////////////////////////////////////////
// Detours
//
BOOL WINAPI Mine_WaitNamedPipeW(LPCWSTR lpNamedPipeName, DWORD nTimeOut)
{
    return Real_WaitNamedPipeW(lpNamedPipeName, nTimeOut);
}

BOOL WINAPI Mine_CloseHandle(HANDLE hObject)
{
    return Real_CloseHandle(hObject);
}

VOID WINAPI Mine_GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime)
{
    Real_GetSystemTimeAsFileTime(lpSystemTimeAsFileTime);
}

BOOL WINAPI Mine_SetNamedPipeHandleState(HANDLE hNamedPipe,
                                            LPDWORD lpMode,
                                            LPDWORD lpMaxCollectionCount,
                                            LPDWORD lpCollectDataTimeout)
{
    return Real_SetNamedPipeHandleState(hNamedPipe,
                                        lpMode,
                                        lpMaxCollectionCount,
                                        lpCollectDataTimeout);
}

BOOL WINAPI Mine_WriteFile(HANDLE hFile,
                           LPCVOID lpBuffer,
                           DWORD nNumberOfBytesToWrite,
                           LPDWORD lpNumberOfBytesWritten,
                           LPOVERLAPPED lpOverlapped)
{
    return Real_WriteFile(hFile,
                          lpBuffer,
                          nNumberOfBytesToWrite,
                          lpNumberOfBytesWritten,
                          lpOverlapped);
}

BOOL WINAPI Mine_CreateProcessW(LPCWSTR lpApplicationName,
                                LPWSTR lpCommandLine,
                                LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                BOOL bInheritHandles,
                                DWORD dwCreationFlags,
                                LPVOID lpEnvironment,
                                LPCWSTR lpCurrentDirectory,
                                LPSTARTUPINFOW lpStartupInfo,
                                LPPROCESS_INFORMATION lpProcessInformation)
{
    _PrintEnter("CreateProcessW(%ls,%ls,%lx,%lx,%lx,%lx,%lx,%ls,%lx,%lx)\n",
                lpApplicationName,
                lpCommandLine,
                lpProcessAttributes,
                lpThreadAttributes,
                bInheritHandles,
                dwCreationFlags,
                lpEnvironment,
                lpCurrentDirectory,
                lpStartupInfo,
                lpProcessInformation);

    _Print("Calling DetourCreateProcessWithDllW(,%ls)\n", s_wzDllPath);
    
    BOOL rv = 0;
    __try {
        rv = DetourCreateProcessWithDllW(lpApplicationName,
                                   lpCommandLine,
                                   lpProcessAttributes,
                                   lpThreadAttributes,
                                   bInheritHandles,
                                   dwCreationFlags,
                                   lpEnvironment,
                                   lpCurrentDirectory,
                                   lpStartupInfo,
                                   lpProcessInformation,
                                   s_wzDllPath,
                                   Real_CreateProcessW);
    } __finally {
        _PrintExit("CreateProcessW(,,,,,,,,,) -> %lx\n", rv);
    };
    return rv;
}

//
//////////////////////////////////////////////////////////////////////////////

BOOL WINAPI Mine_CopyFileExA(LPCSTR a0,
                                LPCSTR a1,
                                LPPROGRESS_ROUTINE a2,
                                LPVOID a3,
                                LPBOOL a4,
                                DWORD a5)
{
    _PrintEnter("CopyFileExA(%hs,%hs,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    BOOL rv = 0;
    __try {
        rv = Real_CopyFileExA(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("CopyFileExA(,,,,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_CopyFileExW(LPCWSTR a0,
                                LPCWSTR a1,
                                LPPROGRESS_ROUTINE a2,
                                LPVOID a3,
                                LPBOOL a4,
                                DWORD a5)
{
    _PrintEnter("CopyFileExW(%ls,%ls,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    BOOL rv = 0;
    __try {
        rv = Real_CopyFileExW(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("CopyFileExW(,,,,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_CreateDirectoryExW(LPCWSTR a0,
                                       LPCWSTR a1,
                                       LPSECURITY_ATTRIBUTES a2)
{
    _PrintEnter("CreateDirectoryExW(%ls,%ls,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_CreateDirectoryExW(a0, a1, a2);
    } __finally {
        _PrintExit("CreateDirectoryExW(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_CreateDirectoryW(LPCWSTR a0,
                                     LPSECURITY_ATTRIBUTES a1)
{
    _PrintEnter("CreateDirectoryW(%ls,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_CreateDirectoryW(a0, a1);
    } __finally {
        _PrintExit("CreateDirectoryW(,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_CreateFileW(LPCWSTR a0,
                                  DWORD a1,
                                  DWORD a2,
                                  LPSECURITY_ATTRIBUTES a3,
                                  DWORD a4,
                                  DWORD a5,
                                  HANDLE a6)
{
	_PrintEnter(NULL);
    HANDLE rv = 0;
    __try {
        rv = Real_CreateFileW(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
		_PrintExit("CreateFileW(%ls,%lx,%lx,%lx,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, a5, a6, rv);
    };
    return rv;
}

BOOL WINAPI Mine_DeleteFileA(LPCSTR a0)
{
    _PrintEnter("DeleteFileA(%hs)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_DeleteFileA(a0);
    } __finally {
        _PrintExit("DeleteFileA() -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_DeleteFileW(LPCWSTR a0)
{
    _PrintEnter("DeleteFileW(%ls)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_DeleteFileW(a0);
    } __finally {
        _PrintExit("DeleteFileW() -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_FindFirstFileExA(LPCSTR a0,
                                       FINDEX_INFO_LEVELS a1,
                                       LPVOID a2,
                                       FINDEX_SEARCH_OPS a3,
                                       LPVOID a4,
                                       DWORD a5)
{
    _PrintEnter("FindFirstFileExA(%hs,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    HANDLE rv = 0;
    __try {
        rv = Real_FindFirstFileExA(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("FindFirstFileExA(,,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_FindFirstFileExW(LPCWSTR a0,
                                       FINDEX_INFO_LEVELS a1,
                                       LPVOID a2,
                                       FINDEX_SEARCH_OPS a3,
                                       LPVOID a4,
                                       DWORD a5)
{
    _PrintEnter(NULL);

    HANDLE rv = 0;
    __try {
        rv = Real_FindFirstFileExW(a0, a1, a2, a3, a4, a5);
    } __finally {
		_PrintExit("FindFirstFileExW(%ls,%lx,%lx,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, a5, rv);
    };
    return rv;
}

DWORD WINAPI Mine_GetFileAttributesW(LPCWSTR a0)
{
    _PrintEnter(NULL);

    DWORD rv = 0;
    __try {
        rv = Real_GetFileAttributesW(a0);
    } __finally {
		_PrintExit("GetFileAttributesW(%ls) -> %lx\n", a0, rv);
    };
    return rv;
}

DWORD WINAPI Mine_GetModuleFileNameW(HMODULE a0, LPWSTR a1, DWORD a2)
{
    _PrintEnter("GetModuleFileNameW(%lx,%lx,%lx)\n", a0, a1, a2);
    DWORD rv = 0;
    __try {
        rv = Real_GetModuleFileNameW(a0, a1, a2);
    } __finally {
        _PrintExit("GetModuleFileNameW(%lx,%lx:%ls,%lx) -> %lx\n", a0, a1, a1, a2, rv);
    };
    return rv;
}

FARPROC WINAPI Mine_GetProcAddress(struct HINSTANCE__* a0,
                                      LPCSTR a1)
{
	WCHAR wzModule[MAX_PATH] = L"";
	PWCHAR pwzModule = wzModule;
	if (Real_GetModuleFileNameW(a0, wzModule, ARRAYOF(wzModule)) != 0) {
		if ((pwzModule = wcsrchr(wzModule, '\\')) == NULL) {
			if ((pwzModule = wcsrchr(wzModule, ':')) == NULL) {
				pwzModule = wzModule;
			}
			else {
				pwzModule++;							// Skip ':'
			}
		}
		else {
			pwzModule++;								// Skip '\\'
		}
	}
	else {
		wzModule[0] = '\0';
	}

	_PrintEnter(NULL);
    FARPROC rv = 0;
    __try {
        rv = Real_GetProcAddress(a0, a1);
    } __finally {
		if (pwzModule[0] == 0) {
			_PrintExit("GetProcAddress(%lx,%hs) -> %lx\n", a0, a1, rv);
		}
		else {
			_PrintExit("GetProcAddress(%lx:%ls,%hs) -> %lx\n", a0, pwzModule, a1, rv);
		}
    };
    return rv;
}

HMODULE WINAPI Mine_LoadLibraryExW(LPCWSTR a0,
                                      HANDLE a1,
                                      DWORD a2)
{
    _PrintEnter("LoadLibraryExW(%ls,%lx,%lx)\n", a0, a1, a2);

    HMODULE rv = 0;
    __try {
        rv = Real_LoadLibraryExW(a0, a1, a2);
    } __finally {
        _PrintExit("LoadLibraryExW(,,) -> %lx\n", rv);
		if (rv) {
			InstanceEnumerate(rv);
		}
    };
    return rv;
}

BOOL WINAPI Mine_MoveFileA(LPCSTR a0,
                              LPCSTR a1)
{
    _PrintEnter("MoveFileA(%hs,%hs)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_MoveFileA(a0, a1);
    } __finally {
        _PrintExit("MoveFileA(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_MoveFileExA(LPCSTR a0,
                                LPCSTR a1,
                                DWORD a2)
{
    _PrintEnter("MoveFileExA(%hs,%hs,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_MoveFileExA(a0, a1, a2);
    } __finally {
        _PrintExit("MoveFileExA(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_MoveFileExW(LPCWSTR a0,
                                LPCWSTR a1,
                                DWORD a2)
{
    _PrintEnter("MoveFileExW(%ls,%ls,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_MoveFileExW(a0, a1, a2);
    } __finally {
        _PrintExit("MoveFileExW(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_MoveFileW(LPCWSTR a0,
                              LPCWSTR a1)
{
    _PrintEnter("MoveFileW(%ls,%ls)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_MoveFileW(a0, a1);
    } __finally {
        _PrintExit("MoveFileW(,) -> %lx\n", rv);
    };
    return rv;
}

HFILE WINAPI Mine_OpenFile(LPCSTR a0,
                              struct _OFSTRUCT* a1,
                              UINT a2)
{
    _PrintEnter("OpenFile(%hs,%lx,%lx)\n", a0, a1, a2);

    HFILE rv = 0;
    __try {
        rv = Real_OpenFile(a0, a1, a2);
    } __finally {
        _PrintExit("OpenFile(,,) -> %lx\n", rv);
    };
    return rv;
}

LONG WINAPI Mine_RegCreateKeyExA(HKEY a0,
                                    LPCSTR a1,
                                    DWORD a2,
                                    LPSTR a3,
                                    DWORD a4,
                                    REGSAM a5,
                                    LPSECURITY_ATTRIBUTES a6,
                                    PHKEY a7,
                                    LPDWORD a8)
{
    _PrintEnter("RegCreateKeyExA(%lx,%hs,%lx,%hs,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7, a8);

    LONG rv = 0;
    __try {
        rv = Real_RegCreateKeyExA(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    } __finally {
        _PrintExit("RegCreateKeyExA(,,,,,,,,) -> %lx\n", rv);
    };
    return rv;
}

LONG WINAPI Mine_RegCreateKeyExW(HKEY a0,
                                    LPCWSTR a1,
                                    DWORD a2,
                                    LPWSTR a3,
                                    DWORD a4,
                                    REGSAM a5,
                                    LPSECURITY_ATTRIBUTES a6,
                                    PHKEY a7,
                                    LPDWORD a8)
{
	_PrintEnter(NULL);
    LONG rv = 0;
    __try {
        rv = Real_RegCreateKeyExW(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    } __finally {
		_PrintExit("RegCreateKeyExW(%lx,%ls,%lx,%ls,%lx,%lx,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, a5, a6, a7, a8, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegDeleteKeyA(HKEY a0,
                                  LPCSTR a1)
{
	_PrintEnter(NULL);
    LONG rv = 0;
    __try {
        rv = Real_RegDeleteKeyA(a0, a1);
    } __finally {
		_PrintExit("RegDeleteKeyA(%lx,%hs) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegDeleteKeyW(HKEY a0,
                                  LPCWSTR a1)
{
	_PrintEnter(NULL);
    LONG rv = 0;
    __try {
        rv = Real_RegDeleteKeyW(a0, a1);
    } __finally {
		_PrintExit("RegDeleteKeyW(%lx,%ls) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegDeleteValueA(HKEY a0,
                                    LPCSTR a1)
{
    _PrintEnter("RegDeleteValueA(%lx,%hs)\n", a0, a1);

    LONG rv = 0;
    __try {
        rv = Real_RegDeleteValueA(a0, a1);
    } __finally {
        _PrintExit("RegDeleteValueA(,) -> %lx\n", rv);
    };
    return rv;
}

LONG WINAPI Mine_RegDeleteValueW(HKEY a0,
                                    LPCWSTR a1)
{
    _PrintEnter("RegDeleteValueW(%lx,%ls)\n", a0, a1);

    LONG rv = 0;
    __try {
        rv = Real_RegDeleteValueW(a0, a1);
    } __finally {
        _PrintExit("RegDeleteValueW(,) -> %lx\n", rv);
    };
    return rv;
}

LONG WINAPI Mine_RegEnumKeyExA(HKEY a0,
                                  DWORD a1,
                                  LPSTR a2,
                                  LPDWORD a3,
                                  LPDWORD a4,
                                  LPSTR a5,
                                  LPDWORD a6,
                                  struct _FILETIME* a7)
{
    _PrintEnter("RegEnumKeyExA(%lx,%lx,%lx,%lx,%lx,%hs,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7);

    LONG rv = 0;
    __try {
        rv = Real_RegEnumKeyExA(a0, a1, a2, a3, a4, a5, a6, a7);
    } __finally {
        _PrintExit("RegEnumKeyExA(,,%hs,,,%hs,,) -> %lx\n", a2, a5, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegEnumKeyExW(HKEY a0,
                                  DWORD a1,
                                  LPWSTR a2,
                                  LPDWORD a3,
                                  LPDWORD a4,
                                  LPWSTR a5,
                                  LPDWORD a6,
                                  struct _FILETIME* a7)
{
    _PrintEnter("RegEnumKeyExW(%lx,%lx,%lx,%lx,%lx,%ls,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7);

    LONG rv = 0;
    __try {
        rv = Real_RegEnumKeyExW(a0, a1, a2, a3, a4, a5, a6, a7);
    } __finally {
        _PrintExit("RegEnumKeyExW(,,%ls,,,%ls,,) -> %lx\n", a2, a5, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegEnumValueA(HKEY a0,
                                  DWORD a1,
                                  LPSTR a2,
                                  LPDWORD a3,
                                  LPDWORD a4,
                                  LPDWORD a5,
                                  LPBYTE a6,
                                  LPDWORD a7)
{
    _PrintEnter("RegEnumValueA(%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7);

    LONG rv = 0;
    __try {
        rv = Real_RegEnumValueA(a0, a1, a2, a3, a4, a5, a6, a7);
    } __finally {
        _PrintExit("RegEnumValueA(,,%hs,,,,,) -> %lx\n", a2, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegEnumValueW(HKEY a0,
                                  DWORD a1,
                                  LPWSTR a2,
                                  LPDWORD a3,
                                  LPDWORD a4,
                                  LPDWORD a5,
                                  LPBYTE a6,
                                  LPDWORD a7)
{
    _PrintEnter("RegEnumValueW(%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7);

    LONG rv = 0;
    __try {
        rv = Real_RegEnumValueW(a0, a1, a2, a3, a4, a5, a6, a7);
    } __finally {
        _PrintExit("RegEnumValueW(,,%ls,,,,,) -> %lx\n", a2, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegOpenKeyExA(HKEY a0,
                                  LPCSTR a1,
                                  DWORD a2,
                                  REGSAM a3,
                                  PHKEY a4)
{
    _PrintEnter(NULL);

    LONG rv = 0;
    __try {
        rv = Real_RegOpenKeyExA(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("RegOpenKeyExA(%lx,%hs,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegOpenKeyExW(HKEY a0,
                                  LPCWSTR a1,
                                  DWORD a2,
                                  REGSAM a3,
                                  PHKEY a4)
{
    _PrintEnter(NULL);

    LONG rv = 0;
    __try {
        rv = Real_RegOpenKeyExW(a0, a1, a2, a3, a4);
    } __finally {
		_PrintExit("RegOpenKeyExW(%lx,%ls,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegQueryInfoKeyA(HKEY a0,
                                     LPSTR a1,
                                     LPDWORD a2,
                                     LPDWORD a3,
                                     LPDWORD a4,
                                     LPDWORD a5,
                                     LPDWORD a6,
                                     LPDWORD a7,
                                     LPDWORD a8,
                                     LPDWORD a9,
                                     LPDWORD a10,
                                     struct _FILETIME* a11)
{
    _PrintEnter("RegQueryInfoKeyA(%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n",
				a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

    LONG rv = 0;
    __try {
        rv = Real_RegQueryInfoKeyA(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    } __finally {
        _PrintExit("RegQueryInfoKeyA(,%hs,,,,,,,,,,) -> %lx\n", a1, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegQueryInfoKeyW(HKEY a0,
                                     LPWSTR a1,
                                     LPDWORD a2,
                                     LPDWORD a3,
                                     LPDWORD a4,
                                     LPDWORD a5,
                                     LPDWORD a6,
                                     LPDWORD a7,
                                     LPDWORD a8,
                                     LPDWORD a9,
                                     LPDWORD a10,
                                     struct _FILETIME* a11)
{
    _PrintEnter("RegQueryInfoKeyW(%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n",
				a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);

    LONG rv = 0;
    __try {
        rv = Real_RegQueryInfoKeyW(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    } __finally {
        _PrintExit("RegQueryInfoKeyW(,%ls,,,,,,,,,,) -> %lx\n", a1, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegQueryValueExA(HKEY a0,
                                     LPCSTR a1,
                                     LPDWORD a2,
                                     LPDWORD a3,
                                     LPBYTE a4,
                                     LPDWORD a5)
{
    _PrintEnter(NULL);

    LONG rv = 0;
    __try {
        rv = Real_RegQueryValueExA(a0, a1, a2, a3, a4, a5);
    } __finally {
		_PrintExit("RegQueryValueExA(%lx,%hs,%lx,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, a5, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegQueryValueExW(HKEY a0,
                                     LPCWSTR a1,
                                     LPDWORD a2,
                                     LPDWORD a3,
                                     LPBYTE a4,
                                     LPDWORD a5)
{
	_PrintEnter(NULL);
    LONG rv = 0;
    __try {
        rv = Real_RegQueryValueExW(a0, a1, a2, a3, a4, a5);
    } __finally {
		_PrintExit("RegQueryValueExW(%lx,%ls,%lx,%lx,%lx,%lx) -> %lx\n",
					a0, a1, a2, a3, a4, a5, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegSetValueExA(HKEY a0,
                                   LPCSTR a1,
                                   DWORD a2,
                                   DWORD a3,
                                   BYTE* a4,
                                   DWORD a5)
{
    _PrintEnter(NULL);
    LONG rv = 0;
    __try {
        rv = Real_RegSetValueExA(a0, a1, a2, a3, a4, a5);
    } __finally {
		_PrintExit("RegSetValueExA(%lx,%hs,%lx,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, a5, rv);
    };
    return rv;
}

LONG WINAPI Mine_RegSetValueExW(HKEY a0,
                                   LPCWSTR a1,
                                   DWORD a2,
                                   DWORD a3,
                                   BYTE* a4,
                                   DWORD a5)
{
	_PrintEnter(NULL);
    LONG rv = 0;
    __try {
        rv = Real_RegSetValueExW(a0, a1, a2, a3, a4, a5);
    } __finally {
		_PrintExit("RegSetValueExW(%lx,%ls,%lx,%lx,%lx,%lx) -> %lx\n",
				   a0, a1, a2, a3, a4, a5, rv);
    };
    return rv;
}

HFILE WINAPI Mine__lcreat(LPCSTR a0, int a1)
{
	_PrintEnter(NULL);
    HFILE rv = 0;
    __try {
        rv = Real__lcreat(a0, a1);
    } __finally {
		_PrintExit("_lcreat(%hs,%lx) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

HFILE WINAPI Mine__lopen(LPCSTR a0, int a1)
{
    _PrintEnter(NULL);
    HFILE rv = 0;
    __try {
        rv = Real__lopen(a0, a1);
    } __finally {
		_PrintEnter("_lopen(%hs,%lx) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

/////////////////////////////////////////////////////////////
// TrampolineWith
//
VOID TrampolineWith(VOID)
{
    DetourFunctionWithTrampoline((PBYTE)Real_CopyFileExA,
                                 (PBYTE)Mine_CopyFileExA);
    DetourFunctionWithTrampoline((PBYTE)Mine_WaitNamedPipeW,
                                 (PBYTE)Real_WaitNamedPipeW);
    DetourFunctionWithTrampoline((PBYTE)Mine_CloseHandle,
                                 (PBYTE)Real_CloseHandle);
    DetourFunctionWithTrampoline((PBYTE)Mine_GetSystemTimeAsFileTime,
                                 (PBYTE)Real_GetSystemTimeAsFileTime);
    DetourFunctionWithTrampoline((PBYTE)Mine_SetNamedPipeHandleState,
                                 (PBYTE)Real_SetNamedPipeHandleState);
    DetourFunctionWithTrampoline((PBYTE)Mine_WriteFile,
                                 (PBYTE)Real_WriteFile);
    DetourFunctionWithTrampoline((PBYTE)Mine_CreateProcessW,
                                 (PBYTE)Real_CreateProcessW);
    DetourFunctionWithTrampoline((PBYTE)Real_CopyFileExA,
                                 (PBYTE)Mine_CopyFileExA);
    DetourFunctionWithTrampoline((PBYTE)Real_CopyFileExW,
                                 (PBYTE)Mine_CopyFileExW);
    DetourFunctionWithTrampoline((PBYTE)Real_CreateDirectoryExW,
                                 (PBYTE)Mine_CreateDirectoryExW);
    DetourFunctionWithTrampoline((PBYTE)Real_CreateDirectoryW,
                                 (PBYTE)Mine_CreateDirectoryW);
    DetourFunctionWithTrampoline((PBYTE)Real_CreateFileW,
                                 (PBYTE)Mine_CreateFileW);
    DetourFunctionWithTrampoline((PBYTE)Real_DeleteFileA,
                                 (PBYTE)Mine_DeleteFileA);
    DetourFunctionWithTrampoline((PBYTE)Real_DeleteFileW,
                                 (PBYTE)Mine_DeleteFileW);
    DetourFunctionWithTrampoline((PBYTE)Real_FindFirstFileExA,
                                 (PBYTE)Mine_FindFirstFileExA);
    DetourFunctionWithTrampoline((PBYTE)Real_FindFirstFileExW,
                                 (PBYTE)Mine_FindFirstFileExW);
    DetourFunctionWithTrampoline((PBYTE)Real_GetFileAttributesW,
                                 (PBYTE)Mine_GetFileAttributesW);
    DetourFunctionWithTrampoline((PBYTE)Real_GetModuleFileNameW,
                                 (PBYTE)Mine_GetModuleFileNameW);
    DetourFunctionWithTrampoline((PBYTE)Real_GetProcAddress,
                                 (PBYTE)Mine_GetProcAddress);
    DetourFunctionWithTrampoline((PBYTE)Real_LoadLibraryExW,
                                 (PBYTE)Mine_LoadLibraryExW);
    DetourFunctionWithTrampoline((PBYTE)Real_MoveFileA,
                                 (PBYTE)Mine_MoveFileA);
    DetourFunctionWithTrampoline((PBYTE)Real_MoveFileExA,
                                 (PBYTE)Mine_MoveFileExA);
    DetourFunctionWithTrampoline((PBYTE)Real_MoveFileExW,
                                 (PBYTE)Mine_MoveFileExW);
    DetourFunctionWithTrampoline((PBYTE)Real_MoveFileW,
                                 (PBYTE)Mine_MoveFileW);
    DetourFunctionWithTrampoline((PBYTE)Real_OpenFile,
                                 (PBYTE)Mine_OpenFile);
    DetourFunctionWithTrampoline((PBYTE)Real_RegCreateKeyExA,
                                 (PBYTE)Mine_RegCreateKeyExA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegCreateKeyExW,
                                 (PBYTE)Mine_RegCreateKeyExW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegDeleteKeyA,
                                 (PBYTE)Mine_RegDeleteKeyA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegDeleteKeyW,
                                 (PBYTE)Mine_RegDeleteKeyW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegDeleteValueA,
                                 (PBYTE)Mine_RegDeleteValueA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegDeleteValueW,
                                 (PBYTE)Mine_RegDeleteValueW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegEnumKeyExA,
                                 (PBYTE)Mine_RegEnumKeyExA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegEnumKeyExW,
                                 (PBYTE)Mine_RegEnumKeyExW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegEnumValueA,
                                 (PBYTE)Mine_RegEnumValueA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegEnumValueW,
                                 (PBYTE)Mine_RegEnumValueW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegOpenKeyExA,
                                 (PBYTE)Mine_RegOpenKeyExA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegOpenKeyExW,
                                 (PBYTE)Mine_RegOpenKeyExW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegQueryInfoKeyA,
                                 (PBYTE)Mine_RegQueryInfoKeyA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegQueryInfoKeyW,
                                 (PBYTE)Mine_RegQueryInfoKeyW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegQueryValueExA,
                                 (PBYTE)Mine_RegQueryValueExA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegQueryValueExW,
                                 (PBYTE)Mine_RegQueryValueExW);
    DetourFunctionWithTrampoline((PBYTE)Real_RegSetValueExA,
                                 (PBYTE)Mine_RegSetValueExA);
    DetourFunctionWithTrampoline((PBYTE)Real_RegSetValueExW,
                                 (PBYTE)Mine_RegSetValueExW);
    DetourFunctionWithTrampoline((PBYTE)Real__lcreat,
                                 (PBYTE)Mine__lcreat);
    DetourFunctionWithTrampoline((PBYTE)Real__lopen,
                                 (PBYTE)Mine__lopen);
}
//
//////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////// Logging System.
//
static BOOL s_bLog = 1;
static LONG s_nTlsIndent = -1;
static LONG s_nTlsThread = -1;
static LONG s_nThreadCnt = 0;

VOID _PrintEnter(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent);
		TlsSetValue(s_nTlsIndent, (PVOID)(nIndent + 1));
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}
		
	if (s_bLog && psz) {
		CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
		*pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

		va_list  args;
		va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

		va_end(args);
	}
	SetLastError(dwErr);
}

VOID _PrintExit(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent) - 1;
        ASSERT(nIndent >= 0);
		TlsSetValue(s_nTlsIndent, (PVOID)nIndent);
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}
		
	if (s_bLog && psz) {
		CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
		*pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

		va_list  args;
		va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

		va_end(args);
	}
	SetLastError(dwErr);
}

VOID _Print(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent);
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}

	if (s_bLog && psz) {
        CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
        *pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

        va_list  args;
        va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

        va_end(args);
    }
        
	SetLastError(dwErr);
}

VOID AssertMessage(CONST PCHAR pszMsg, CONST PCHAR pszFile, ULONG nLine)
{
    Syelog(SYELOG_SEVERITY_FATAL,
           "ASSERT(%s) failed in %s, line %d.\n", pszMsg, pszFile, nLine);
}

VOID NullExport()
{
}

//////////////////////////////////////////////////////////////////////////////
//
PIMAGE_NT_HEADERS NtHeadersForInstance(HINSTANCE hInst)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hInst;
	__try {
		if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			SetLastError(ERROR_BAD_EXE_FORMAT);
			return NULL;
		}
		
		PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader +
														  pDosHeader->e_lfanew);
		if (pNtHeader->Signature != IMAGE_NT_SIGNATURE) {
			SetLastError(ERROR_INVALID_EXE_SIGNATURE);
			return NULL;
		}
		if (pNtHeader->FileHeader.SizeOfOptionalHeader == 0) {
			SetLastError(ERROR_EXE_MARKED_INVALID);
			return NULL;
		}
		return pNtHeader;
	} __except(EXCEPTION_EXECUTE_HANDLER) {
	}
	SetLastError(ERROR_EXE_MARKED_INVALID);
	
	return NULL;
}

BOOL InstanceEnumerate(HINSTANCE hInst)
{
	WCHAR wzDllName[MAX_PATH];

	PIMAGE_NT_HEADERS pinh = NtHeadersForInstance(hInst);
	if (pinh && Real_GetModuleFileNameW(hInst, wzDllName, ARRAYOF(wzDllName))) {
        Syelog(SYELOG_SEVERITY_INFORMATION,
               "### %08lx: %-43.43ls %08x\n",
               hInst, wzDllName, pinh->OptionalHeader.CheckSum);
		return TRUE;
	}
	return FALSE;
}

BOOL ProcessEnumerate()
{
    Syelog(SYELOG_SEVERITY_INFORMATION,
           "######################################################### Binaries\n");
	for (HINSTANCE hInst = NULL; (hInst = DetourEnumerateModules(hInst)) != NULL;) {
		InstanceEnumerate(hInst);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL ThreadAttach(HMODULE hDll)
{
	if (s_nTlsIndent >= 0) {
		TlsSetValue(s_nTlsIndent, (PVOID)0);
	}
	if (s_nTlsThread >= 0) {
		LONG nThread = InterlockedIncrement(&s_nThreadCnt);
		TlsSetValue(s_nTlsThread, (PVOID)nThread);
	}
	return TRUE;
}

BOOL ThreadDetach(HMODULE hDll)
{
	if (s_nTlsIndent >= 0) {
		TlsSetValue(s_nTlsIndent, (PVOID)0);
	}
	if (s_nTlsThread >= 0) {
		TlsSetValue(s_nTlsThread, (PVOID)0);
	}
	return TRUE;
}

BOOL ProcessAttach(HMODULE hDll)
{
	s_bLog = FALSE;
	s_nTlsIndent = TlsAlloc();
	s_nTlsThread = TlsAlloc();

	WCHAR wzExeName[MAX_PATH];

    s_hInst = hDll;
	Real_GetModuleFileNameW(hDll, s_wzDllPath, ARRAYOF(s_wzDllPath));
	Real_GetModuleFileNameW(NULL, wzExeName, ARRAYOF(wzExeName));

    SyelogOpen("traceapi", SYELOG_FACILITY_APPLICATION);
	ProcessEnumerate();
	
	TrampolineWith();

	ThreadAttach(hDll);
	
	s_bLog = TRUE;
	return TRUE;
}

BOOL ProcessDetach(HMODULE hDll)
{
	ThreadDetach(hDll);
	
	s_bLog = FALSE;
    SyelogClose();

	if (s_nTlsIndent >= 0) {
		TlsFree(s_nTlsIndent);
	}
	if (s_nTlsThread >= 0) {
		TlsFree(s_nTlsThread);
	}
	return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD dwReason, PVOID lpReserved)
{
	switch (dwReason) {
	  case DLL_PROCESS_ATTACH:
		return ProcessAttach(hModule);
	  case DLL_PROCESS_DETACH:
		return ProcessDetach(hModule);
	  case DLL_THREAD_ATTACH:
		return ThreadAttach(hModule);
	  case DLL_THREAD_DETACH:
		return ThreadDetach(hModule);
	}
	return TRUE;
}
//
///////////////////////////////////////////////////////////////// End of File.
