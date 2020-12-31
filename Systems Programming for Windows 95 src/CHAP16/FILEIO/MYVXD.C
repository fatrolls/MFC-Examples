
#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <vwin32.h>
#include <vxdwraps.h>
#include <winerror.h>

#include "ifsmgr.h"
#include <string.h>
#pragma intrinsic(strlen)

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	DWORD hfile;
	int code;
	DWORD action;
	static unsigned char *data = "Hello, world!";
	DWORD nwritten;
	
	code = R0_OpenCreateFile(FALSE, ACCESS_READWRITE | SHARE_DENYREADWRITE,
		0, ACTION_CREATEALWAYS, 0,
		 "c:\\vxdbook\\Chap16\\FileIO\\HelloWorld.txt",
		&hfile, &action);
	if (code == 0)
		{						// file opened okay
		R0_WriteFile(FALSE, hfile, strlen(data), 0, data, &nwritten);
		R0_CloseFile(hfile);
		}						// file opened okay
	
	return TRUE;
	}							// OnSysDynamicDeviceInit

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	return TRUE;
	}							// OnSysDynamicDeviceExit

DWORD OnDeviceIoControl(PDIOCPARAMETERS p)
	{							// OnDeviceIoControl
	return 0;
	}							// OnDeviceIoControl
