//////////////////////////////////////////////////////////////////////
//
//  File:       sleepnew.cpp
//	Module:		sleptnew.exe (slept.dll)
//
//	Copyright:	1996-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//

#include <windows.h>
#include <stdio.h>
#include "slept.h"

#include "verify.cpp"

int __cdecl main(void)
{
    printf("sleepnew.exe: Starting.\n");
    Verify((PBYTE)Sleep);
    
    printf("sleepnew.exe: Calling Sleep for 1 second.\n");
    Sleep(1000);
    printf("sleepnew.exe: Calling TimedSleep for 1 second.\n");
    TimedSleep(1000);
    printf("sleepnew.exe: Calling UntimedSleep for 1 second.\n");
    UntimedSleep(1000);
    printf("sleepnew.exe: Done sleeping.\n\n");

    printf("sleepnew.exe: GetSleptTicks() = %d\n\n", GetSleptTicks());
    return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
