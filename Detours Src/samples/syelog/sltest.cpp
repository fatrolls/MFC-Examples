//////////////////////////////////////////////////////////////////////
//
//	File:		sltest.cpp
//	Module:		sltest.exe
//
//	Copyright 1999-2001, Microsoft Corporation. All rights reserved.
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
//  Test the named-pipe-based connection with syelog.lib to the syelog
//  system-event logger.
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "syelog.h"
#include "detours.h"

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

int main(int argc, char **argv) 
{ 
    SyelogOpen("sltest", SYELOG_FACILITY_APPLICATION);
    Syelog(SYELOG_SEVERITY_INFORMATION, "Hello World!");
    SyelogClose();
    
    return 0; 
} 
