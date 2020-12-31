//////////////////////////////////////////////////////////////////////
//
//  Module:     heapa.dll
//
//  Copyright:  1996-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//

#include <stdio.h>
#include <windows.h>
#include "detours.h"
#include "syelog.h"

#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

extern "C" {
    //  Trampolines for SYELOG library.
    //
    DETOUR_TRAMPOLINE(HANDLE WINAPI
                      Real_CreateFileW(LPCWSTR a0, DWORD a1, DWORD a2,
                                       LPSECURITY_ATTRIBUTES a3, DWORD a4, DWORD a5,
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
static BOOL bInternal = TRUE;

DETOUR_TRAMPOLINE(LPVOID WINAPI Real_HeapAlloc(HANDLE Heap, DWORD Flags, DWORD Bytes),
                  HeapAlloc);

LPVOID WINAPI My_HeapAlloc(HANDLE hHeap, DWORD dwFlags, DWORD dwBytes)
{
    LPVOID pvRet = Real_HeapAlloc(hHeap, dwFlags, dwBytes);
    
    if (!bInternal) {
        Syelog(SYELOG_SEVERITY_NOTICE,
               "HeapAlloc(%08x, %08x, %08x) -> %08x\n",
               hHeap, dwFlags, dwBytes, pvRet);
    }
    return pvRet;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        BOOL bOk;
        PBYTE pbRealTrampoline;
        PBYTE pbRealTarget;

        SyelogOpen("heapa", SYELOG_FACILITY_APPLICATION);
        
        bOk = DetourFunctionWithTrampolineEx((PBYTE)Real_HeapAlloc, (PBYTE)My_HeapAlloc,
                                             &pbRealTrampoline, &pbRealTarget);

        Syelog(SYELOG_SEVERITY_INFORMATION,
               "DetourFunctionWithTrampolineEx -> %d", bOk);
        Syelog(SYELOG_SEVERITY_INFORMATION,
               "    HeapAlloc:  %08x -> %08x\n", HeapAlloc, pbRealTarget);
        Syelog(SYELOG_SEVERITY_INFORMATION,
               "    Trampoline: %08x -> %08x\n", Real_HeapAlloc, pbRealTrampoline);
        Syelog(SYELOG_SEVERITY_INFORMATION,
               "    Detour:     %08x\n", My_HeapAlloc);
        bInternal = FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH) {

        bInternal = TRUE;
        DetourRemove((PBYTE)Real_HeapAlloc, (PBYTE)My_HeapAlloc);
        SyelogClose();
    }
    return TRUE;
}
//
///////////////////////////////////////////////////////////////// End of File.
