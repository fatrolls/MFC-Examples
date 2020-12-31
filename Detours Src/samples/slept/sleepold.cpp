//////////////////////////////////////////////////////////////////////
//
//  File:       sleepold.cpp
//	Module:		sleptold.exe (slept.dll)
//
//	Copyright:	1996-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//

#include <windows.h>
#include <stdio.h>

#include "verify.cpp"

int __cdecl main(int argc, char **argv)
{
    //
    // Verify what the code looks like.
    //
    printf("sleepold.exe: Starting.\n");
    Verify((PBYTE)Sleep);
    fflush(stdout);

    //
    // See if another process wants us to wait on a shared event.
    // This helps in testing Injection.

    if (argc == 2 && stricmp(argv[1], "-wait") == 0) {
        HANDLE hEvent = OpenEvent(SYNCHRONIZE, FALSE, "detours_inject_test_event");
        if (hEvent) {
            printf("sleepold.exe: Waiting for detours_inject_test_event to be set.\n");
            fflush(stdout);
            WaitForSingleObject(hEvent, INFINITE);
        }
        else {
            printf("sleepold.exe: Couldn't open detours_inject_test_event.\n");
        }
    }

    //
    // Try out sleep (which may be detours).
    //
    printf("sleepold.exe: Calling Sleep for 1 second.\n");
    Sleep(1000);
    printf("sleepold.exe: Done sleeping.\n\n");
    fflush(stdout);

    return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
