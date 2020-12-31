// MYVXD.C -- Sample Virtual Device Driver

#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vxdwraps.h>

#pragma VxD_ICODE_SEG
#pragma VxD_IDATA_SEG

BOOL _stdcall OnDeviceInit(PVMMCB hVM, DWORD refdata)
	{							// OnDeviceInit
	return TRUE;
	}							// OnDeviceInit

BOOL _stdcall OnSysCriticalInit(PVMMCB hVM, DWORD refdata)
	{							// OnSysCriticalInit
	return TRUE;
	}							// OnSysCriticalInit

BOOL _stdcall OnInitComplete(PVMMCB hVM, DWORD refdata)
	{							// OnInitComplete
	return TRUE;
	}							// OnInitComplete

