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

;    Declare ourselves as a level 17 VSD:

_theDRP  DRP   <EyeCatcher, DRP_VSD_9, offset32 _OnAsyncRequest, \
	       offset32 _theILB, 'Sample VSD', 0, 0, 0>

VxD_IDATA_ENDS

VxD_LOCKED_DATA_SEG
	 public _theILB
_theILB  ILB   <>			       ; I/O subsystem linkage block
VxD_LOCKED_DATA_ENDS

Declare_Virtual_Device REQMON, 1, 0, REQMON_control,\
		       Undefined_Device_ID, Undefined_Init_Order,,,_theDRP

Begin_Control_Dispatch REQMON
Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
Control_Dispatch W32_DeviceIoControl,	  _OnDeviceIoControl, cCall, <esi>
Control_Dispatch Terminate_Thread,	  _OnTerminateThread, cCall, <edi>
End_Control_Dispatch   REQMON

	 end
