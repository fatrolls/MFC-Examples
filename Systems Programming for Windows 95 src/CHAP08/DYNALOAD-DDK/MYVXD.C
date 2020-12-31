
#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <vwin32.h>
#include <vxdwraps.h>
#include <winerror.h>

BOOL OnSysDynamicDeviceInit()
	{				// OnSysDynamicDeviceInit
	return TRUE;
	}				// OnSysDynamicDeviceInit

BOOL OnSysDynamicDeviceExit()
	{				// OnSysDynamicDeviceExit
	return TRUE;
	}				// OnSysDynamicDeviceExit

DWORD OnDeviceIoControl(PDIOCPARAMETERS p)
	{				// OnDeviceIoControl
	return 0;
	}				// OnDeviceIoControl
