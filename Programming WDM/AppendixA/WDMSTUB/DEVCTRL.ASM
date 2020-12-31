;   DevCtrl.asm -- Device control procedure for WDMSTUB.VXD
;	Copyright (C) 1997 by Walter Oney
;	All rights reserved

	.586p
	include vmm.inc
	include debug.inc
	include version.inc

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

Declare_Virtual_Device WDMSTUB, VERMAJOR, VERMINOR, WDMSTUB_control,\
	Undefined_Device_ID, <NTKERN_INIT_ORDER + 1000h>,\
	, \
	, \

;------------------------------------------------------------------------------
;    Control function:
;------------------------------------------------------------------------------

Begin_Control_Dispatch WDMSTUB
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

Control_Dispatch Device_Init, _OnDeviceInit, cCall, <edx>

End_Control_Dispatch WDMSTUB

	end
