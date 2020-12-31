;==============================================================================
;	MYVXD.ASM -- The (almost) simplest possible VxD in assembly language
;	Written by Walter Oney
;==============================================================================

    name  myvxd
    .386p
    include vmm.inc
    include debug.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_Control, \
    Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD
    Control_Dispatch Device_Init, OnDeviceInit
End_Control_Dispatch   MYVXD

BeginProc OnDeviceInit, init
    clc		  ; indicate no error
    ret		  ; return to VMM
EndProc	OnDeviceInit

    end
