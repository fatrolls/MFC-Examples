// MYVXD.c - main module for VxD MYVXD

#define   DEVICE_MAIN
#include  "myvxd.h"
#undef    DEVICE_MAIN

Declare_Virtual_Device(MYVXD)

DefineControlHandler(SYS_DYNAMIC_DEVICE_INIT, OnSysDynamicDeviceInit);
DefineControlHandler(SYS_DYNAMIC_DEVICE_EXIT, OnSysDynamicDeviceExit);
DefineControlHandler(W32_DEVICEIOCONTROL, OnW32Deviceiocontrol);

BOOL ControlDispatcher(
        DWORD dwControlMessage,
        DWORD EBX,
        DWORD EDX,
        DWORD ESI,
        DWORD EDI,
		DWORD ECX)
{
        START_CONTROL_DISPATCH

                ON_SYS_DYNAMIC_DEVICE_INIT(OnSysDynamicDeviceInit);
                ON_SYS_DYNAMIC_DEVICE_EXIT(OnSysDynamicDeviceExit);
                ON_W32_DEVICEIOCONTROL(OnW32Deviceiocontrol);

        END_CONTROL_DISPATCH

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

DWORD OnW32Deviceiocontrol(PIOCTLPARAMS p)
{
        return 0;
}
