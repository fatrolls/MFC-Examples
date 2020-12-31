#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <shell.h>
#include <debug.h>
#include <vxdwraps.h>

APPY_HANDLE hevent;

VOID __cdecl OnAppyTime(DWORD refdata);

BOOL __stdcall OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	hevent = _SHELL_CallAtAppyTime(OnAppyTime, NULL, 0, 0);
	return TRUE;
	}							// OnSysDynamicDeviceInit

BOOL __stdcall OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	if (hevent)
		_SHELL_CancelAppyTimeEvent(hevent);
	return TRUE;
	}							// OnSysDynamicDeviceExit

VOID __cdecl OnAppyTime(DWORD refdata)
	{
	#pragma pack(1)
	struct {
		DWORD dwData;
		WORD fuCommand;
		DWORD lpszHelpFile;
		WORD hwnd;
		} WinHelpArgs;
	#pragma pack()

	hevent = 0;
	WinHelpArgs.hwnd = 0;
	WinHelpArgs.lpszHelpFile = _SHELL_LocalAllocEx(LPTR + LMEM_STRING,
		0, "D:\\DDPR.HLP");
	WinHelpArgs.fuCommand = 0x101;      // HELP_KEY
	WinHelpArgs.dwData = _SHELL_LocalAllocEx(LPTR + LMEM_STRING,
		0, "_SHELL_CallDll");

	_SHELL_CallDll("USER", "WinHelp", sizeof(WinHelpArgs),
		&WinHelpArgs);

	_SHELL_LocalFree(WinHelpArgs.lpszHelpFile);
	_SHELL_LocalFree(WinHelpArgs.dwData);
	}
