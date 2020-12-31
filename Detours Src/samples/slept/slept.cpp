//////////////////////////////////////////////////////////////////////
//
//	Module:		slept.dll
//	Copyright:	1996-2001, Microsoft Corporation
//
//	Microsoft Research Detours Package, Version 1.5 (Build 46)
//

#include <stdio.h>
#include <windows.h>
#include "detours.h"
#include "slept.h"

#include "verify.cpp"

LONG dwSlept = 0;

#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

DETOUR_TRAMPOLINE(VOID WINAPI UntimedSleep(DWORD dwMilliseconds), Sleep);
 
VOID WINAPI TimedSleep(DWORD dwMilliseconds)
{
    DWORD dwBeg = GetTickCount();
    UntimedSleep(dwMilliseconds);
    DWORD dwEnd = GetTickCount();
    
    InterlockedExchangeAdd(&dwSlept, dwEnd - dwBeg);
}

DWORD WINAPI GetSleptTicks(VOID)
{
    return dwSlept;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        printf("slept.dll: Starting.\n");
        Verify((PBYTE)Sleep);
        printf("\n");
        fflush(stdout);
    
        DetourFunctionWithTrampoline((PBYTE)UntimedSleep, (PBYTE)TimedSleep);
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourRemove((PBYTE)UntimedSleep, (PBYTE)TimedSleep);
        printf("slept.dll: Removed Sleep() trampoline, slept %d ticks.\n", dwSlept);
        fflush(stdout);
    }
    return TRUE;
}
//
///////////////////////////////////////////////////////////////// End of File.
