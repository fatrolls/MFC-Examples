// MYVXD.C -- C-language skeleton using DDK tools
#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vxdwraps.h>

#pragma VxD_ICODE_SEG
#pragma VxD_IDATA_SEG

BOOL _stdcall OnDeviceInit(PVMMCB hVM, DWORD refdata)
    {				// OnDeviceInit
    return TRUE;
    }				// OnDeviceInit
