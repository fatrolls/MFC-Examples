; DEVDCL.ASM -- Assembly language interfaces for Sample VxD

    .386p
    include vmm.inc
    include debug.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control,\
    Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD

Control_Dispatch Sys_Critical_Init, OnDeviceInit,      sCall, <ebx, edx>
Control_Dispatch Device_Init,	    OnSysCriticalInit, sCall, <ebx, edx>
Control_Dispatch Init_Complete,     OnInitComplete,    sCall, <ebx, edx>

End_Control_Dispatch   MYVXD

    end
