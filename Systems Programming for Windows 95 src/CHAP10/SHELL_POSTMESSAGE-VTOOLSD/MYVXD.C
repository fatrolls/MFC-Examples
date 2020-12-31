// MYVXD.c - main module for VxD MYVXD

#define   DEVICE_MAIN
#include  "myvxd.h"
#undef    DEVICE_MAIN

typedef struct tagMSGSTUFF
{
    DWORD   hwnd;
    DWORD   msg;
    DWORD   wParam;
    DWORD   lParam;
} MSGSTUFF, *PMSGSTUFF;

VOID DoPostMessage(DWORD event, VMHANDLE hVM);
VOID __cdecl CheckPostMessage(DWORD rc, PMSGSTUFF p);
VOID __stdcall TimeoutCallback(VMHANDLE hVM, PCLIENT_STRUCT pRegs, PVOID refdata, DWORD extra);

DWORD hwnd;
DWORD msg;

TIMEOUT_THUNK TimeoutThunk;

#ifndef MAKELONG
    #define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

///////////////////////////////////////////////////////////////////////////////

Declare_Virtual_Device(MYVXD)

VOID PM_Api_Handler(VMHANDLE hVM, PCLIENT_STRUCT pRegs)
{
    _clientEFlags &= ~CF_MASK;
    switch (_clientAX)
        {                       // select API function

    case 0:
        _clientAX = (The_DDB.DDB_Dev_Major_Version << 8) | The_DDB.DDB_Dev_Minor_Version;
        break;

    case 1:
        hwnd = _clientBX;
        msg = _clientCX;
        break;

    default:
        _clientEFlags |= CF_MASK;
        break;
        }                       // select API function
}

DefineControlHandler(CREATE_VM, OnCreateVm);
DefineControlHandler(VM_CRITICAL_INIT, OnVmCriticalInit);
DefineControlHandler(VM_INIT, OnVmInit);
DefineControlHandler(VM_TERMINATE, OnVmTerminate);
DefineControlHandler(VM_NOT_EXECUTEABLE, OnVmNotExecuteable);
DefineControlHandler(DESTROY_VM, OnDestroyVm);
DefineControlHandler(VM_SUSPEND, OnVmSuspend);
DefineControlHandler(VM_RESUME, OnVmResume);
DefineControlHandler(BEGIN_PM_APP, OnBeginPmApp);
DefineControlHandler(END_PM_APP, OnEndPmApp);
DefineControlHandler(CLOSE_VM_NOTIFY, OnCloseVmNotify);
DefineControlHandler(SYS_DYNAMIC_DEVICE_INIT, OnSysDynamicDeviceInit);
DefineControlHandler(SYS_DYNAMIC_DEVICE_EXIT, OnSysDynamicDeviceExit);

BOOL ControlDispatcher(
    DWORD dwControlMessage,
    DWORD EBX,
    DWORD EDX,
    DWORD ESI,
    DWORD EDI,
    DWORD ECX)
{
    START_CONTROL_DISPATCH

        ON_CREATE_VM(OnCreateVm);
        ON_VM_CRITICAL_INIT(OnVmCriticalInit);
        ON_VM_INIT(OnVmInit);
        ON_VM_TERMINATE(OnVmTerminate);
        ON_VM_NOT_EXECUTEABLE(OnVmNotExecuteable);
        ON_DESTROY_VM(OnDestroyVm);
        ON_VM_SUSPEND(OnVmSuspend);
        ON_VM_RESUME(OnVmResume);
        ON_BEGIN_PM_APP(OnBeginPmApp);
        ON_END_PM_APP(OnEndPmApp);
        ON_CLOSE_VM_NOTIFY(OnCloseVmNotify);
        ON_SYS_DYNAMIC_DEVICE_INIT(OnSysDynamicDeviceInit);
        ON_SYS_DYNAMIC_DEVICE_EXIT(OnSysDynamicDeviceExit);

    END_CONTROL_DISPATCH

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL OnCreateVm(VMHANDLE hVM)
{
    DoPostMessage(CREATE_VM, hVM);
    return TRUE;
}

BOOL OnVmCriticalInit(VMHANDLE hVM)
{
    DoPostMessage(VM_CRITICAL_INIT, hVM);
    return TRUE;
}

BOOL OnVmInit(VMHANDLE hVM)
{
    DoPostMessage(VM_INIT, hVM);
    return TRUE;
}

VOID OnVmTerminate(VMHANDLE hVM)
{
    DoPostMessage(VM_TERMINATE, hVM);
}

VOID OnVmNotExecuteable(VMHANDLE hVM, DWORD flags)
{
    DoPostMessage(VM_NOT_EXECUTEABLE, hVM);
}

VOID OnDestroyVm(VMHANDLE hVM)
{
    DoPostMessage(DESTROY_VM, hVM);
}

VOID OnVmSuspend(VMHANDLE hVM)
{
    DoPostMessage(VM_SUSPEND, hVM);
}

BOOL OnVmResume(VMHANDLE hVM)
{
    DoPostMessage(VM_RESUME, hVM);
    return TRUE;
}

BOOL OnBeginPmApp(VMHANDLE hVM, DWORD flags, PPMCB pmcb)
{
    DoPostMessage(BEGIN_PM_APP, hVM);
    return TRUE;
}

VOID OnEndPmApp(VMHANDLE hVM, PPMCB pmcb)
{
    DoPostMessage(END_PM_APP, hVM);
}

BOOL OnCloseVmNotify(VMHANDLE hVM, DWORD flags)
{
    DoPostMessage(CLOSE_VM_NOTIFY, hVM);
    return TRUE;
}

BOOL OnSysDynamicDeviceInit()
{
    return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

VOID DoPostMessage(DWORD event, VMHANDLE hVM)
{
    PMSGSTUFF p;
    
    if (!hwnd)
        return;
    
    p = (PMSGSTUFF) _HeapAllocate(sizeof(MSGSTUFF), HEAPZEROINIT);
    Assert(p);
    p->hwnd = hwnd;
    p->msg = msg;
    p->wParam = event;
    p->lParam = (DWORD) hVM;

	_SHELL_PostMessage((HANDLE) hwnd, msg, (WORD) event, (DWORD) hVM, (PPostMessage_HANDLER) CheckPostMessage, p);
}

VOID __cdecl CheckPostMessage(DWORD rc, PMSGSTUFF p)
{
	if (rc)
		_HeapFree(p, 0);
	else
        Set_VM_Time_Out(100, Get_Sys_VM_Handle(), p, TimeoutCallback, &TimeoutThunk);
}


VOID __stdcall TimeoutCallback(VMHANDLE hVM, PCLIENT_STRUCT pRegs, PVOID refdata, DWORD extra)
{
    PMSGSTUFF p = (PMSGSTUFF) refdata;
    _SHELL_PostMessage((HANDLE) p->hwnd, p->msg, (WORD) p->wParam, p->lParam, (PPostMessage_HANDLER) CheckPostMessage, p);
}
