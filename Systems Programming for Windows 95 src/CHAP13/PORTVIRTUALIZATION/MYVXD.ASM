;==============================================================================
;
;    MYVXD.ASM -- Port trapping sample VxD
;
;    Copyright (C) 1995 by Walter Oney
;    All rights reserved
;
;==============================================================================

	 name  myvxd
	 .386p
	 include vmm.inc
	 include debug.inc
	 include shell.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control, \
	Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD
Control_Dispatch Sys_Dynamic_Device_Init, OnSysDynamicDeviceInit
Control_Dispatch Sys_Dynamic_Device_Exit, OnSysDynamicDeviceExit
Control_Dispatch VM_Not_Executeable, OnVMNotExecutable
End_Control_Dispatch   MYVXD

;------------------------------------------------------------------------------

VxD_LOCKED_DATA_SEG
owner	 dd    0			       ; VM that currently owns port
data	 db    'Hello, world!', 0              ; data delivered by the port
pdata	 dd	offset32 data		       ; revolving pointer to data
VxD_LOCKED_DATA_ENDS

;------------------------------------------------------------------------------

BeginProc OnSysDynamicDeviceInit, locked
	 mov   esi, offset32 IOCallback        ; ESI = callback routine
	 mov   edx, 1234h		       ; EDX = port address
	 VMMCall Install_IO_Handler	       ; trap the port
	 ret				       ; return with result of Install_IO_Handler
EndProc OnSysDynamicDeviceInit

;------------------------------------------------------------------------------

BeginProc OnSysDynamicDeviceExit, locked
	 mov   edx, 1234h		       ; EDX = port address
	 VMMCall Remove_IO_Handler	       ; cancel our port trap
	 ret				       ; return with result of Remove_IO_Handler
EndProc OnSysDynamicDeviceExit

;------------------------------------------------------------------------------

BeginProc OnVMNotExecutable, locked
	 cmp   ebx, owner		       ; is owner terminating?
	 jne   @F			       ; if not, okay
	 mov   owner, 0 		       ; yes. indicate no longer owned
@@:
	 ret				       ; return to caller
EndProc OnVMNotExecutable

;------------------------------------------------------------------------------

BeginProc IOCallback, locked
	 cmp   ebx, owner		       ; access by current owner?
	 je    okayio			       ; if yes, no problem
	 cmp   owner, 0 		       ; is there any owner at all?
	 jne   contend			       ; if yes, we've got a contention
	 mov   owner, ebx		       ; no. just take over the device
	 jmp   okayio			       ;   ..

;    Some VM other than the owner is trying to use the device. Ask the
;    end user what to do.

contend:
	 push  eax			       ; save possible output data (1)
	 mov   eax, owner		       ; EAX = current owner
	 mov   esi, offset32 MYVXD_DDB + DDB_Name ; esi -> name of device
	 VxDCall SHELL_Resolve_Contention      ; present contention dialog
	 pop   eax			       ; restore EAX (1)

	 jc    cantresolve		       ; skip ahead if can't resolve
	 cmp   ebx, owner		       ; did original owner win?
	 je    cantresolve		       ; if yes, give up on this VM
	 mov   owner, ebx		       ; take over the device

;    Here to simulate the I/O operation

okayio:
	 Dispatch_Byte_IO Fall_Through, byteout

bytein:
	 mov   esi, pdata		       ; point to current spot in string
	 xor   eax, eax 		       ; clear high-order part of return value
	 lodsb				       ; get next data byte
	 test  al, al			       ; reached null terminator?
	 jnz   @F			       ; if not, okay
	 mov   esi, offset32 data	       ; yes. start over next time
@@:
	 mov   pdata, esi		       ; save updated pointer

byteout:
	 ret				       ; return with new byte in AL

cantresolve:
	 VMMCall Crash_Cur_VM		       ; crash the current VM
	 ret				       ; (doesn't return)
EndProc  IOCallback

	 end
