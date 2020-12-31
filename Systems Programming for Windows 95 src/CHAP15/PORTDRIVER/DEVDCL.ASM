;    DEVDCL.ASM -- Device declaration and control proc for IOS VxDs
;    Copyright (C) 1995 by Walter Oney
;    All rights reserved

	 .386p
	 include vmm.inc
	 include drp.inc
	 include ilb.inc

	 extrn _OnAsyncRequest:near

VxD_IDATA_SEG
	 public _theDRP

;    Declare ourselves as a level 19 port driver:

_theDRP  DRP   <EyeCatcher, DRP_MISC_PD, offset32 _OnAsyncRequest, \
	       offset32 _theILB, 'Sample Port Dvr', 0, 0, 0>

VxD_IDATA_ENDS

VxD_LOCKED_DATA_SEG
	 public _theILB
_theILB  ILB   <>			       ; I/O subsystem linkage block
VxD_LOCKED_DATA_ENDS

Declare_Virtual_Device RAMDISK, 1, 0, RAMDISK_control,\
		       Undefined_Device_ID, Undefined_Init_Order,,,_theDRP

Begin_Control_Dispatch RAMDISK
Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
End_Control_Dispatch   RAMDISK

	 end

