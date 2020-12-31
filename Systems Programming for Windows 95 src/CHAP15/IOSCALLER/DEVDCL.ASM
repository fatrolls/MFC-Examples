	 .386p
	 include vmm.inc
	 include vdmad.inc
	 include debug.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control,\
		       Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD
Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
End_Control_Dispatch   MYVXD

	 end
