	 .386p
	 include vmm.inc
	 include debug.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control,\
		       Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD

Control_Dispatch Device_Init,	   _OnDeviceInit, cCall, <ebx, edx>
Control_Dispatch Create_VM,	   _OnCreateVM, cCall, <ebx>
Control_Dispatch Destroy_VM,	   _OnDestroyVM, cCall, <ebx>
Control_Dispatch Set_Device_Focus, _OnSetDeviceFocus, cCall, <ebx, edx, esi, edi>

End_Control_Dispatch   MYVXD

BeginProc __Allocate_Device_CB_Area, init
	 VxDJmp _Allocate_Device_CB_Area
EndProc __Allocate_Device_CB_Area

BeginProc __MapIntoV86, locked
	 VxDJmp _MapIntoV86
EndProc __MapIntoV86

BeginProc __PhysIntoV86, locked
	 VxDJmp _PhysIntoV86
EndProc __PhysIntoV86

BeginProc __Assign_Device_V86_Pages, init
	 VxDJmp _Assign_Device_V86_Pages
EndProc __Assign_Device_V86_Pages

	 end
