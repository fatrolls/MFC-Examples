// MYVXD.c - main module for VxD MYVXD

#define   DEVICE_MAIN
#include  "myvxd.h"
#undef    DEVICE_MAIN

Declare_Virtual_Device(MYVXD)

DefineControlHandler(DEVICE_INIT, OnDeviceInit);
DefineControlHandler(W32_DEVICEIOCONTROL, OnW32Deviceiocontrol);

BOOL __cdecl ControlDispatcher(
	DWORD dwControlMessage,
	DWORD EBX,
	DWORD EDX,
	DWORD ESI,
	DWORD EDI,
	DWORD ECX)
{
	START_CONTROL_DISPATCH

		ON_DEVICE_INIT(OnDeviceInit);
		ON_W32_DEVICEIOCONTROL(OnW32Deviceiocontrol);

	END_CONTROL_DISPATCH

	return TRUE;
}


BOOL OnDeviceInit(VMHANDLE hVM, PCHAR CommandTail)
{
	return TRUE;
}

DWORD OnW32Deviceiocontrol(PIOCTLPARAMS p)
{
	return 0;
}
