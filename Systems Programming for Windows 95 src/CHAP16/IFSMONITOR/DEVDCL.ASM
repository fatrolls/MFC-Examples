;==============================================================================
;
;    DEVDCL.ASM -- Device declaration and control procedure for IOS Monitor support VxD
;
;    Copyright (C) 1996 by Walter Oney
;    All rights reserved
;
;==============================================================================

	 .386p
	 include vmm.inc

VxD_LOCKED_DATA_SEG
didinit  dd    0
VxD_LOCKED_DATA_ENDS

initcode segment dword public flat 'code'
beginit  dd    0
initcode ends

initend  segment dword public flat 'code'
endinit  dd    0
initend  ends

_bss	 segment dword public flat 'lcode'
startbss dd    0
_bss	 ends

_ebss	 segment dword public flat 'lcode'
endbss	 dd    0
_ebss ends

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control, \
	 Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD

;    The first time here, call any static initializers. Our C++ programs
;    were built with #pragma init_seg("initcode"), which forces all
;    static initializers into the INITCODE segment. Limitations in the
;    linker prevent us from (a) accessing the .CRT$XCU COFF segment the
;    compiler would use by default and (b) simply referencing EQU symbols
;    or segment names in the following code. Hence the name change and
;    the unnecessary use of DD variables

	 bts   didinit, 0		       ; been here before?
	 jc    skipinit 		       ; if yes, skip initialization
	 pushad 			       ; save all registers
	 mov   esi, offset32 beginit+4	       ; point to 1st initializer ptr
@@:
	 cmp   esi, offset32 endinit	       ; reached end of initializers?
	 jae   @F			       ; if yes, leave the loop
	 call  dword ptr [esi]		       ; call static initializer
	 add   esi, 4			       ; process all of them
	 jmp   @B			       ;   ..
@@:

;    The linker won't necessarily generate zero data for the BSS section,
;    which is where the compiler places uninitialized static data. Zero
;    this area by hand, therefore.

	 cld				       ; force forward direction
	 mov   edi, offset32 startbss	       ; point to start of BSS area
	 mov   ecx, offset32 endbss	       ; compute length
	 sub   ecx, edi 		       ;   ..
	 shr   ecx, 2			       ; convert to dwords
	 xor   eax, eax 		       ; get const zero
	 rep   stosd			       ; zero-fill BSS area

	 popad				       ; restore registers

skipinit:

Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
Control_Dispatch Terminate_Thread,	  _OnTerminateThread, cCall, <edi>
Control_Dispatch W32_DeviceIoControl,	  _OnDeviceIoControl, cCall, <esi>
End_Control_Dispatch   MYVXD

	 end
