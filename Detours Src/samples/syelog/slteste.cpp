//////////////////////////////////////////////////////////////////////
//
//	File:		slteste.cpp
//	Module:		slteste.exe
//
//	Copyright 1999-2001, Microsoft Corporation. All rights reserved.
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
//  Test the NT-event-log-based connection to the syelog system-event logger.
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "syelog.h"

VOID MyErrExit(PCSTR pszMsg)
{
    fprintf(stderr, "Error %s: %d\n", pszMsg, GetLastError());
    exit(1);
}

DWORD main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    
    HANDLE h; 

    h = RegisterEventSource(NULL, "Application");
    if (h == NULL) 
        MyErrExit("Could not register the event source."); 

    Sleep(2000);
    
    PCSTR rpszMsg[1] = { "etest: Hello World!" };
    
    if (!ReportEvent(h,                     // event log handle 
                     EVENTLOG_WARNING_TYPE, // event type 
                     0,                    // category zero 
                     0,        // event identifier 
                     NULL,                 // no user security identifier 
                     1,                    // one substitution string 
                     0,                    // no data 
                     rpszMsg,     // pointer to string array 
                     NULL)) {                // pointer to data 
        MyErrExit("Could not report the event.");
    }
    DeregisterEventSource(h);
    
    return 0;
} 
