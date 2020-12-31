;==============================================================================
;
;    MYVXD.ASM -- IRQ virtualization sample program
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
	 include vpicd.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control, \
	Undefined_Device_ID, Undefined_Init_Order, apifunc, apifunc

Begin_Control_Dispatch MYVXD
Control_Dispatch Device_Init, OnSysDynamicDeviceInit
Control_Dispatch Sys_Dynamic_Device_Init, OnSysDynamicDeviceInit
Control_Dispatch Sys_Dynamic_Device_Exit, OnSysDynamicDeviceExit
Control_Dispatch VM_Not_Executeable, OnVMNotExecutable
End_Control_Dispatch   MYVXD

;------------------------------------------------------------------------------

VxD_LOCKED_DATA_SEG
owner	 dd    0
irqhandle dd   0			       ; virtualized IRQ handle
vid	 label dword			       ; VPICD_IRQ_Descriptor structure
	 dw    12			       ; irq number
	 dw    VPICD_OPT_REF_DATA	       ; flags
	 dd    offset32 Hw_Int_Proc	       ; Hw_Int_Proc
	 dd    offset32 Virt_Int_Proc	       ; Virt_Int_Proc
	 dd    offset32 EOI_Proc	       ; EOI_Proc
	 dd    offset32 Mask_Change_Proc       ; Mask_Change_Proc
	 dd    0			       ; IRET_Proc
	 dd    500			       ; IRET_Time_Out
	 dd    42			       ; Hw_Int_Ref
data	 db    'Hello, world!', 0              ; data delivered by the port
pdata	 dd	offset32 data		       ; revolving pointer to data
VxD_LOCKED_DATA_ENDS

;------------------------------------------------------------------------------

BeginProc OnSysDynamicDeviceInit, locked
	 mov   esi, offset32 IOCallback        ; ESI = callback routine
	 mov   edx, 1234h		       ; EDX = port address
	 VMMCall Install_IO_Handler	       ; trap the port
	 jc    init_done		       ; skip if error

	 mov   edi, offset32 vid	       ; EDI -> irq descriptor
	 VxDCall VPICD_Virtualize_IRQ	       ; virtualize the IRQ
	 jc    init_fail		       ; skip if error
	 mov   irqhandle, eax		       ; save IRQ handle for later

init_done:
	 ret				       ; return with CF set for error

init_fail:
	 mov   edx, 1234h		       ; undo I/O trap
	 VMMCall Remove_IO_Handler	       ;   ..
	 stc				       ; indicate error
	 jmp   init_done		       ;   ..
EndProc OnSysDynamicDeviceInit

;------------------------------------------------------------------------------

BeginProc OnSysDynamicDeviceExit, locked
	 mov   edx, 1234h		       ; EDX = port address
	 VMMCall Remove_IO_Handler	       ; cancel our port trap

	 mov   eax, irqhandle		       ; EAX -> IRQ handle
	 test  eax, eax 		       ; zero? (side effect: CLC)
	 jz    @F			       ; if yes, nothing to do
	 VxDCall VPICD_Force_Default_Behavior  ; unvirtualize the irq
@@:
	 ret				       ; return with result
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

BeginProc apifunc, pageable
	 int   5Ch			       ; simulate interrupt on IRQ 12
	 ret				       ; return to application
EndProc  apifunc

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

;------------------------------------------------------------------------------

BeginProc Hw_Int_Proc, locked
	 mov   ebx, owner		       ; point to device owner
	 test  ebx, ebx 		       ; anyone own the device?
	 jz    @F			       ; if not, dismiss the interrupt

	 VxDJmp VPICD_Set_Int_Request	       ; set interrupt request for owner

@@:
	 VxDJmp VPICD_Phys_EOI		       ; dismiss an unowned interrupt
EndProc  Hw_Int_Proc

;------------------------------------------------------------------------------

BeginProc Mask_Change_Proc, locked
	 mov   owner, ebx		       ; take over the device
	 ret
EndProc  Mask_Change_Proc

;------------------------------------------------------------------------------

BeginProc Virt_Int_Proc, locked
	 clc
	 ret
EndProc  Virt_Int_Proc

;------------------------------------------------------------------------------

BeginProc EOI_Proc, locked
	 VxDCall VPICD_Clear_Int_Request       ; clear interrupt request from owner
	 VxDJmp VPICD_Phys_EOI		       ; dismiss the interrupt
EndProc  EOI_Proc

	 end
