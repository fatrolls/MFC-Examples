///////////////////////////////////////////////////
//
//  common.h - Copyright 1997, Don Box
//  
//  Common call/thread context structures used by hook
//
//

#ifndef _COMMON_H
#define _COMMON_H

#include <windows.h>

// information about a particular call site
struct NODE_INFO
{
    DWORD pid;
    DWORD tid;
    DWORD ip;
};

// wire represenation of ORPCTHIS extention
struct HOOK_THIS
{
    GUID  cid;              // fake causality ID
    NODE_INFO niDirect;     // node of immediate caller
    NODE_INFO niIndirect;   // node of original caller
};

// wire represenation of ORPCTHIS extention
struct HOOK_THAT
{
    NODE_INFO niTarget;     // node where call executed
};

// call contexts are a linked list of ORPCTHIS structs
struct CALL_CONTEXT : public HOOK_THIS
{
    CALL_CONTEXT *pNext;
};

// thread context is a linked list of calls + an ORPCTHAT
struct THREAD_CONTEXT : public HOOK_THAT
{
    NODE_INFO niThis;
    CALL_CONTEXT *pCurrentCall;
};


// EXTENTID_HostHook is the ORPCTHIS/THAT extension ID
// {F23ADD53-4992-11d1-991C-006097585A3C}
DEFINE_GUID(EXTENTID_HostHook, 
0xf23add53, 0x4992, 0x11d1, 0x99, 0x1c, 0x0, 0x60, 0x97, 0x58, 0x5a, 0x3c);

extern HINSTANCE g_hInstance;

// helper function to grab thread context from TLS
THREAD_CONTEXT *GetCurrentThreadContext(void);


#endif
