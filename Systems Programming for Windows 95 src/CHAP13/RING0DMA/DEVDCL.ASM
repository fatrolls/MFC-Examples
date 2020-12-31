	 .386p
	 include vmm.inc
	 include vdmad.inc
	 include debug.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control,\
		       Undefined_Device_ID, Undefined_Init_Order,\
		       apicall, apicall

Begin_Control_Dispatch MYVXD
Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
Control_Dispatch PNP_New_Devnode,	  _OnPnpNewDevnode, cCall, <ebx, edx>
End_Control_Dispatch   MYVXD

BeginProc apicall, pageable
	 push  ebp			       ; client regs
	 push  edi			       ; current thread
	 push  ebx			       ; current VM
	 extrn _ApiEntry:near
	 call  _ApiEntry		       ; call C function
	 add   esp, 12			       ; lose args
	 ret				       ; return to caller
EndProc  apicall

;------------------------------------------------------------------------------
	 end
