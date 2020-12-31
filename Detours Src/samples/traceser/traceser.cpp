//////////////////////////////////////////////////////////////////////
//
//	File:		traceser.cpp
//	Module:		traceser.dll
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
static HMODULE s_hInst = NULL;
static WCHAR s_wzDllPath[MAX_PATH];

VOID _PrintDump(HANDLE h, PCHAR pszData, INT cbData);
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

DETOUR_TRAMPOLINE(DWORD WINAPI Real_GetModuleFileNameW(HMODULE a0,
                                                          LPWSTR a1,
                                                          DWORD a2),
                  GetModuleFileNameW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CreateProcessW(LPCWSTR a0,
                                                     LPWSTR a1,
                                                     LPSECURITY_ATTRIBUTES a2,
                                                     LPSECURITY_ATTRIBUTES a3,
                                                     BOOL a4,
                                                     DWORD a5,
                                                     LPVOID a6,
                                                     LPCWSTR a7,
                                                     struct _STARTUPINFOW* a8,
                                                     LPPROCESS_INFORMATION a9),
                  CreateProcessW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_BuildCommDCBA(LPCSTR a0,
                                                    struct _DCB* a1),
                  BuildCommDCBA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_BuildCommDCBAndTimeoutsA(LPCSTR a0,
                                                               struct _DCB* a1,
                                                               struct _COMMTIMEOUTS* a2),
                  BuildCommDCBAndTimeoutsA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_BuildCommDCBAndTimeoutsW(LPCWSTR a0,
                                                               struct _DCB* a1,
                                                               struct _COMMTIMEOUTS* a2),
                  BuildCommDCBAndTimeoutsW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_BuildCommDCBW(LPCWSTR a0,
                                                    struct _DCB* a1),
                  BuildCommDCBW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_ClearCommBreak(HANDLE a0),
                  ClearCommBreak);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_ClearCommError(HANDLE a0,
                                                     LPDWORD a1,
                                                     struct _COMSTAT* a2),
                  ClearCommError);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_CreateFileA(LPCSTR a0,
                                                    DWORD a1,
                                                    DWORD a2,
                                                    LPSECURITY_ATTRIBUTES a3,
                                                    DWORD a4,
                                                    DWORD a5,
                                                    HANDLE a6),
                  CreateFileA);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_EscapeCommFunction(HANDLE a0,
                                                         DWORD a1),
                  EscapeCommFunction);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetCommConfig(HANDLE a0,
                                                    LPCOMMCONFIG a1,
                                                    LPDWORD a2),
                  GetCommConfig);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetCommMask(HANDLE a0,
                                                  LPDWORD a1),
                  GetCommMask);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetCommModemStatus(HANDLE a0,
                                                         LPDWORD a1),
                  GetCommModemStatus);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetCommProperties(HANDLE a0,
                                                        LPCOMMPROP a1),
                  GetCommProperties);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetCommState(HANDLE a0,
                                                   struct _DCB* a1),
                  GetCommState);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetCommTimeouts(HANDLE a0,
                                                      struct _COMMTIMEOUTS* a1),
                  GetCommTimeouts);

DETOUR_TRAMPOLINE(DWORD WINAPI Real_GetCurrentThreadId(void),
                  GetCurrentThreadId);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_GetOverlappedResult(HANDLE a0,
                                                          LPOVERLAPPED a1,
                                                          LPDWORD a2,
                                                          BOOL a3),
                  GetOverlappedResult);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_PurgeComm(HANDLE a0,
                                                DWORD a1),
                  PurgeComm);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_ReadFile(HANDLE a0,
                                               LPVOID a1,
                                               DWORD a2,
                                               LPDWORD a3,
                                               LPOVERLAPPED a4),
                  ReadFile);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_SetCommBreak(HANDLE a0),
                  SetCommBreak);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_SetCommConfig(HANDLE a0,
                                                    LPCOMMCONFIG a1,
                                                    DWORD a2),
                  SetCommConfig);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_SetCommMask(HANDLE a0,
                                                  DWORD a1),
                  SetCommMask);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_SetCommState(HANDLE a0,
                                                   struct _DCB* a1),
                  SetCommState);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_SetCommTimeouts(HANDLE a0,
                                                      struct _COMMTIMEOUTS* a1),
                  SetCommTimeouts);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_SetupComm(HANDLE a0,
                                                DWORD a1,
                                                DWORD a2),
                  SetupComm);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_TransmitCommChar(HANDLE a0,
                                                       char a1),
                  TransmitCommChar);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_WaitCommEvent(HANDLE a0,
                                                    LPDWORD a1,
                                                    LPOVERLAPPED a2),
                  WaitCommEvent);

/////////////////////////////////////////////////////////////
// Detours
//

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

BOOL WINAPI Mine_BuildCommDCBA(LPCSTR a0,
                                  struct _DCB* a1)
{
    _PrintEnter("BuildCommDCBA(%hs,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_BuildCommDCBA(a0, a1);
    } __finally {
        _PrintExit("BuildCommDCBA(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_BuildCommDCBAndTimeoutsA(LPCSTR a0,
                                             struct _DCB* a1,
                                             struct _COMMTIMEOUTS* a2)
{
    _PrintEnter("BuildCommDCBAndTimeoutsA(%hs,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_BuildCommDCBAndTimeoutsA(a0, a1, a2);
    } __finally {
        _PrintExit("BuildCommDCBAndTimeoutsA(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_BuildCommDCBAndTimeoutsW(LPCWSTR a0,
                                             struct _DCB* a1,
                                             struct _COMMTIMEOUTS* a2)
{
    _PrintEnter("BuildCommDCBAndTimeoutsW(%ls,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_BuildCommDCBAndTimeoutsW(a0, a1, a2);
    } __finally {
        _PrintExit("BuildCommDCBAndTimeoutsW(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_BuildCommDCBW(LPCWSTR a0,
                                  struct _DCB* a1)
{
    _PrintEnter("BuildCommDCBW(%ls,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_BuildCommDCBW(a0, a1);
    } __finally {
        _PrintExit("BuildCommDCBW(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_ClearCommBreak(HANDLE a0)
{
    _PrintEnter("ClearCommBreak(%lx)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_ClearCommBreak(a0);
    } __finally {
        _PrintExit("ClearCommBreak() -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_ClearCommError(HANDLE a0,
                                   LPDWORD a1,
                                   struct _COMSTAT* a2)
{
    _PrintEnter("ClearCommError(%lx,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_ClearCommError(a0, a1, a2);
    } __finally {
        _PrintExit("ClearCommError(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_CloseHandle(HANDLE a0)
{
    _PrintEnter("CloseHandle(%lx)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_CloseHandle(a0);
    } __finally {
        _PrintExit("CloseHandle() -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_CreateFileA(LPCSTR a0,
                                  DWORD a1,
                                  DWORD a2,
                                  LPSECURITY_ATTRIBUTES a3,
                                  DWORD a4,
                                  DWORD a5,
                                  HANDLE a6)
{
    _PrintEnter("CreateFileA(%hs,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6);

    HANDLE rv = 0;
    __try {
        rv = Real_CreateFileA(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
        _PrintExit("CreateFileA(,,,,,,) -> %lx\n", rv);
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
    _PrintEnter("CreateFileW(%ls,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6);

    HANDLE rv = 0;
    __try {
        rv = Real_CreateFileW(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
        _PrintExit("CreateFileW(,,,,,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_EscapeCommFunction(HANDLE a0,
                                       DWORD a1)
{
    _PrintEnter("EscapeCommFunction(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_EscapeCommFunction(a0, a1);
    } __finally {
        _PrintExit("EscapeCommFunction(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetCommConfig(HANDLE a0,
                                  LPCOMMCONFIG a1,
                                  LPDWORD a2)
{
    _PrintEnter("GetCommConfig(%lx,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_GetCommConfig(a0, a1, a2);
    } __finally {
        _PrintExit("GetCommConfig(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetCommMask(HANDLE a0,
                                LPDWORD a1)
{
    _PrintEnter("GetCommMask(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_GetCommMask(a0, a1);
    } __finally {
        _PrintExit("GetCommMask(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetCommModemStatus(HANDLE a0,
                                       LPDWORD a1)
{
    _PrintEnter("GetCommModemStatus(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_GetCommModemStatus(a0, a1);
    } __finally {
        _PrintExit("GetCommModemStatus(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetCommProperties(HANDLE a0,
                                      LPCOMMPROP a1)
{
    _PrintEnter("GetCommProperties(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_GetCommProperties(a0, a1);
    } __finally {
        _PrintExit("GetCommProperties(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetCommState(HANDLE a0,
                                 struct _DCB* a1)
{
    _PrintEnter("GetCommState(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_GetCommState(a0, a1);
    } __finally {
        _PrintExit("GetCommState(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetCommTimeouts(HANDLE a0,
                                    struct _COMMTIMEOUTS* a1)
{
    _PrintEnter("GetCommTimeouts(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_GetCommTimeouts(a0, a1);
    } __finally {
        _PrintExit("GetCommTimeouts(,) -> %lx\n", rv);
    };
    return rv;
}

DWORD WINAPI Mine_GetCurrentThreadId(void)
{
    _PrintEnter("GetCurrentThreadId()\n");

    DWORD rv = 0;
    __try {
        rv = Real_GetCurrentThreadId();
    } __finally {
        _PrintExit("GetCurrentThreadId() -> %lx\n", rv);
    };
    return rv;
}

DWORD WINAPI Mine_GetModuleFileNameW(struct HINSTANCE__* a0,
                                        LPWSTR a1,
                                        DWORD a2)
{
    _PrintEnter("GetModuleFileNameW(%lx,%lx,%lx)\n", a0, a1, a2);

    DWORD rv = 0;
    __try {
        rv = Real_GetModuleFileNameW(a0, a1, a2);
    } __finally {
        _PrintExit("GetModuleFileNameW(,%ls,) -> %lx\n", a1, rv);
    };
    return rv;
}

BOOL WINAPI Mine_GetOverlappedResult(HANDLE a0,
                                        LPOVERLAPPED a1,
                                        LPDWORD a2,
                                        BOOL a3)
{
    _PrintEnter("GetOverlappedResult(%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3);

    BOOL rv = 0;
    __try {
        rv = Real_GetOverlappedResult(a0, a1, a2, a3);
    } __finally {
        _PrintExit("GetOverlappedResult(,,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_PurgeComm(HANDLE a0,
                              DWORD a1)
{
    _PrintEnter("PurgeComm(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_PurgeComm(a0, a1);
    } __finally {
        _PrintExit("PurgeComm(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_ReadFile(HANDLE a0,
                             LPVOID a1,
                             DWORD a2,
                             LPDWORD a3,
                             LPOVERLAPPED a4)
{
    _PrintEnter("ReadFile(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    BOOL rv = 0;
    __try {
        rv = Real_ReadFile(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("ReadFile(,,,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_SetCommBreak(HANDLE a0)
{
    _PrintEnter("SetCommBreak(%lx)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_SetCommBreak(a0);
    } __finally {
        _PrintExit("SetCommBreak() -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_SetCommConfig(HANDLE a0,
                                  LPCOMMCONFIG a1,
                                  DWORD a2)
{
    _PrintEnter("SetCommConfig(%lx,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_SetCommConfig(a0, a1, a2);
    } __finally {
        _PrintExit("SetCommConfig(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_SetCommMask(HANDLE a0,
                                DWORD a1)
{
    _PrintEnter("SetCommMask(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_SetCommMask(a0, a1);
    } __finally {
        _PrintExit("SetCommMask(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_SetCommState(HANDLE a0,
                                 struct _DCB* a1)
{
    _PrintEnter("SetCommState(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_SetCommState(a0, a1);
    } __finally {
        _PrintExit("SetCommState(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_SetCommTimeouts(HANDLE a0,
                                    struct _COMMTIMEOUTS* a1)
{
    _PrintEnter("SetCommTimeouts(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_SetCommTimeouts(a0, a1);
    } __finally {
        _PrintExit("SetCommTimeouts(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_SetupComm(HANDLE a0,
                              DWORD a1,
                              DWORD a2)
{
    _PrintEnter("SetupComm(%lx,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_SetupComm(a0, a1, a2);
    } __finally {
        _PrintExit("SetupComm(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_TransmitCommChar(HANDLE a0,
                                     char a1)
{
    _PrintEnter("TransmitCommChar(%lx,%lx)\n", a0, a1);

    BOOL rv = 0;
    __try {
        rv = Real_TransmitCommChar(a0, a1);
    } __finally {
        _PrintExit("TransmitCommChar(,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_WaitCommEvent(HANDLE a0,
                                  LPDWORD a1,
                                  LPOVERLAPPED a2)
{
    _PrintEnter("WaitCommEvent(%lx,%lx,%lx)\n", a0, a1, a2);

    BOOL rv = 0;
    __try {
        rv = Real_WaitCommEvent(a0, a1, a2);
    } __finally {
        _PrintExit("WaitCommEvent(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_WriteFile(HANDLE a0,
                              LPCVOID a1,
                              DWORD a2,
                              LPDWORD a3,
                              LPOVERLAPPED a4)
{
    _PrintEnter("WriteFile(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    BOOL rv = 0;
    __try {
        _PrintDump(a0, (PCHAR)a1, a2);
        rv = Real_WriteFile(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WriteFile(,,,,) -> %lx\n", rv);
    };
    return rv;
}

/////////////////////////////////////////////////////////////
// TrampolineWith
//
VOID TrampolineWith(VOID)
{
    DetourFunctionWithTrampoline((PBYTE)Real_CreateProcessW,
                                 (PBYTE)Mine_CreateProcessW);
    
    DetourFunctionWithTrampoline((PBYTE)Real_BuildCommDCBA,
                                 (PBYTE)Mine_BuildCommDCBA);
    DetourFunctionWithTrampoline((PBYTE)Real_BuildCommDCBAndTimeoutsA,
                                 (PBYTE)Mine_BuildCommDCBAndTimeoutsA);
    DetourFunctionWithTrampoline((PBYTE)Real_BuildCommDCBAndTimeoutsW,
                                 (PBYTE)Mine_BuildCommDCBAndTimeoutsW);
    DetourFunctionWithTrampoline((PBYTE)Real_BuildCommDCBW,
                                 (PBYTE)Mine_BuildCommDCBW);
    DetourFunctionWithTrampoline((PBYTE)Real_ClearCommBreak,
                                 (PBYTE)Mine_ClearCommBreak);
    DetourFunctionWithTrampoline((PBYTE)Real_ClearCommError,
                                 (PBYTE)Mine_ClearCommError);
    DetourFunctionWithTrampoline((PBYTE)Real_CloseHandle,
                                 (PBYTE)Mine_CloseHandle);
    DetourFunctionWithTrampoline((PBYTE)Real_CreateFileA,
                                 (PBYTE)Mine_CreateFileA);
    DetourFunctionWithTrampoline((PBYTE)Real_CreateFileW,
                                 (PBYTE)Mine_CreateFileW);
    DetourFunctionWithTrampoline((PBYTE)Real_EscapeCommFunction,
                                 (PBYTE)Mine_EscapeCommFunction);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCommConfig,
                                 (PBYTE)Mine_GetCommConfig);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCommMask,
                                 (PBYTE)Mine_GetCommMask);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCommModemStatus,
                                 (PBYTE)Mine_GetCommModemStatus);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCommProperties,
                                 (PBYTE)Mine_GetCommProperties);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCommState,
                                 (PBYTE)Mine_GetCommState);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCommTimeouts,
                                 (PBYTE)Mine_GetCommTimeouts);
    DetourFunctionWithTrampoline((PBYTE)Real_GetCurrentThreadId,
                                 (PBYTE)Mine_GetCurrentThreadId);
    DetourFunctionWithTrampoline((PBYTE)Real_GetModuleFileNameW,
                                 (PBYTE)Mine_GetModuleFileNameW);
    DetourFunctionWithTrampoline((PBYTE)Real_GetOverlappedResult,
                                 (PBYTE)Mine_GetOverlappedResult);
    DetourFunctionWithTrampoline((PBYTE)Real_PurgeComm,
                                 (PBYTE)Mine_PurgeComm);
    DetourFunctionWithTrampoline((PBYTE)Real_ReadFile,
                                 (PBYTE)Mine_ReadFile);
    DetourFunctionWithTrampoline((PBYTE)Real_SetCommBreak,
                                 (PBYTE)Mine_SetCommBreak);
    DetourFunctionWithTrampoline((PBYTE)Real_SetCommConfig,
                                 (PBYTE)Mine_SetCommConfig);
    DetourFunctionWithTrampoline((PBYTE)Real_SetCommMask,
                                 (PBYTE)Mine_SetCommMask);
    DetourFunctionWithTrampoline((PBYTE)Real_SetCommState,
                                 (PBYTE)Mine_SetCommState);
    DetourFunctionWithTrampoline((PBYTE)Real_SetCommTimeouts,
                                 (PBYTE)Mine_SetCommTimeouts);
    DetourFunctionWithTrampoline((PBYTE)Real_SetupComm,
                                 (PBYTE)Mine_SetupComm);
    DetourFunctionWithTrampoline((PBYTE)Real_TransmitCommChar,
                                 (PBYTE)Mine_TransmitCommChar);
    DetourFunctionWithTrampoline((PBYTE)Real_WaitCommEvent,
                                 (PBYTE)Mine_WaitCommEvent);
    DetourFunctionWithTrampoline((PBYTE)Real_WriteFile,
                                 (PBYTE)Mine_WriteFile);
}

/////////////////////////////////////////////////////////////
// Detours
//

VOID _PrintDump(HANDLE h, PCHAR pszData, INT cbData)
{
	if (pszData && cbData > 0) {
		CHAR szBuffer[256];
		PCHAR pszBuffer = szBuffer;
		INT cbBuffer = 0;
		INT nLines = 0;
		
		while (cbData > 0) {
			if (nLines > 20) {
				*pszBuffer++ = '.';
				*pszBuffer++ = '.';
				*pszBuffer++ = '.';
				cbBuffer += 3;
				break;
			}

			if (*pszData == '\t') {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 't';
				cbBuffer += 2;
				pszData++;
				cbData--;
				continue;
			}
			if (*pszData == '\r') {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 'r';
				cbBuffer += 2;
				pszData++;
				cbData--;
				continue;
			}
			else if (*pszData == '\n') {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 'n';
				cbBuffer += 2;
				*pszBuffer++ = '\0';
				_Print("%lx:   %hs\n", h, szBuffer);
				nLines++;
				pszBuffer = szBuffer;
				cbBuffer = 0;
				pszData++;
				cbData--;
				continue;
			}
			else if (cbBuffer >= 80) {
				*pszBuffer++ = '\0';
				_Print("%lx:   %hs\n", h, szBuffer);
				nLines++;
				pszBuffer = szBuffer;
				cbBuffer = 0;
			}
			
			if (*pszData < ' ' || *pszData >= 127) {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 'x';
				*pszBuffer++ = "0123456789ABCDEF"[(*pszData & 0xf0) >> 4];
				*pszBuffer++ = "0123456789ABCDEF"[(*pszData & 0x0f)];
				cbBuffer += 4;
			}
			else {
				*pszBuffer++ = *pszData;
			}
			cbBuffer++;
			pszData++;
			cbData--;
		}
		
		if (cbBuffer > 0) {
			*pszBuffer++ = '\0';
			_Print("%lx:   %hs\n", h, szBuffer);
		}
	}
}

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

	WCHAR wzExePath[MAX_PATH];

    s_hInst = hDll;
	Real_GetModuleFileNameW(hDll, s_wzDllPath, ARRAYOF(s_wzDllPath));
	Real_GetModuleFileNameW(NULL, wzExePath, ARRAYOF(wzExePath));

    SyelogOpen("traceser", SYELOG_FACILITY_APPLICATION);
    Syelog(SYELOG_SEVERITY_INFORMATION,
           "##################################################################\n");
    Syelog(SYELOG_SEVERITY_INFORMATION,
           "### %ls\n", wzExePath);
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
