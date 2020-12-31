;   DevCtrl.asm -- Device control procedure for PNPMON.VXD
;	Copyright (C) 1997 by Walter Oney
;	All rights reserved

	.586p
	include vmm.inc
	include debug.inc

VxD_LOCKED_DATA_SEG
didinit  dd    0
VxD_LOCKED_DATA_ENDS

_init segment dword public flat 'icode'
beginit  dd    0
_init ends

_einit  segment dword public flat 'icode'
endinit  dd    0
_einit  ends

_bss	 segment dword public flat 'lcode'
startbss dd    0
_bss	 ends

_ebss	 segment dword public flat 'lcode'
endbss	 dd    0
_ebss ends

Declare_Virtual_Device PNPMON, 4, 10, PNPMON_control,\
	Undefined_Device_ID, Undefined_Init_Order,\
	, \
	, \

;------------------------------------------------------------------------------
;    Control function:
;------------------------------------------------------------------------------

Begin_Control_Dispatch PNPMON
	 bts   didinit, 0				; been here before?
	 jc    skipinit					; if yes, skip initialization
	 pushad							; save all registers

	 cld							; force forward direction
	 mov   edi, offset32 startbss	; point to start of BSS area
	 mov   ecx, offset32 endbss		; compute length
	 sub   ecx, edi					; ..
	 shr   ecx, 2					; convert to dwords
	 xor   eax, eax					; get const zero
	 rep   stosd					; zero-fill BSS area

	 mov   esi, offset32 beginit+4	; point to 1st initializer ptr
@@:
	 cmp   esi, offset32 endinit	; reached end of initializers?
	 jae   @F						; if yes, leave the loop
	 call  dword ptr [esi]			; call static initializer
	 add   esi, 4					; process all of them
	 jmp   @B						;   ..
@@:											

	 popad							; restore registers

skipinit:

Control_Dispatch Sys_Dynamic_Device_Init, OnSysDynamicDeviceInit, sCall
Control_Dispatch Sys_Dynamic_Device_Exit, OnSysDynamicDeviceExit, sCall
Control_Dispatch W32_DeviceIoControl, OnW32DeviceIoControl, sCall, <esi>

End_Control_Dispatch PNPMON

BeginProc __chkesp, locked
		je	@F

		Debug_Out 'PNPMON - Stack mismatch!'

@@:
		ret
EndProc	__chkesp

	end
