;==============================================================================
;
;    LOADER.ASM -- Protected mode loader
;
;    Copyright (C) 1994 by Walter Oney
;    All rights reserved
;
;    Assemble with MASM 6.1 or equivalent. Link explicitly with a VC 1.52
;    application.
;
;==============================================================================

	 name  loader
	 .model small, c
	 .386

;    Define these symbols so that huge pointer accessing works correctly

	 public _AHINCR
	 public _AHSHIFT

_AHINCR  equ   8
_AHSHIFT equ   3

byp	 equ   <byte ptr>
wp	 equ   <word ptr>
dwp	 equ   <dword ptr>

;    Old-executable file header:

exe_hdr 	struc

e_magic 	dw	0	;  0 magic number: 5A4D (MZ)
e_cblp		dw	0	;  2 bytes in last record of file
e_cp		dw	0	;  4 # 512-byte records in file
e_crlc		dw	0	;  6 # fixups
e_cparhdr	dw	0	;  8 size of file header in paragraphs
e_minalloc	dw	0	;  A minimum extra paragraphs needed
e_maxalloc	dw	0	;  C maximum extra paragraphs needed
e_ss		dw	0	;  E initial SS (relative)
e_sp		dw	0	; 10 initial SP
e_csum		dw	0	; 12 checksum
e_ip		dw	0	; 14 initial IP
e_cs		dw	0	; 16 initial CS (relative)
e_lfarlc	dw	0	; 18 offset of fixup table
e_ovno		dw	0	; 1A overlay number
e_res		dw	4 dup (0)
e_oemid 	dw	0	; 24 OEM identifier
e_oeminfo	dw	0	; 26 OEM information
e_res2		dw	10 dup (0)
e_lfanew	dd	0	; 3C offset of LE/PE/... header

exe_hdr 	ends

emagic		equ	5A4Dh	; MZ signature

c_etext  segment byte public 'endcode'
c_etext  ends

	 .data

toprot	 dd    ?			       ; mode-switch routine
hostdata dw    0			       ; host data area
hfile	 dw    ?			       ; EXE file handle
pspseg	 dw    ?			       ; real-mode PSP segment
codeseg  dw    ?			       ; real-mode CS
dataseg  dw    ?			       ; real-mode DS
fixseg	 dw    ?			       ; memory area for fixups
pspsel	 dw    ?			       ; protected-mode PSP segment
selincr  dw    ?			       ; next-selector increment value
lastseg  dw    -1			       ; last fixup-containing segment
relocfactor dw ?			       ; relocation factor for segments
endcode  dw    ?			       ; segment where code ends
exehdr	 exe_hdr <>			       ; EXE file header

	 .code

;------------------------------------------------------------------------------
;
;    This is the main entry point to the EXE module:
;
;	 DS = ES = PSP segment
;	 CS = near code segment
;
;------------------------------------------------------------------------------

	 public realstart
realstart:

	 mov   ax, @data		       ; get dgroup addressability
	 mov   ds, ax			       ;   ..
	 mov   pspseg, es		       ; save real-mode PSP seg
	 mov   codeseg, cs		       ; ditto CS & DS
	 mov   dataseg, ds		       ;   ..
	 mov   ax, es			       ; compute real-mode relocation factor
	 add   ax, 10h			       ; (in terms of paragraphs)
	 mov   relocfactor, ax		       ;   ..
	 mov   ax, seg c_etext		       ; save end of code address
	 mov   endcode, ax		       ; (can't use constant in code because
					       ; it'll get relocated later on)

;    1.  Shrink our PSP memory block down to the same size the C runtime
;	 initialization program would pick. We need to do this in real mode
;	 because the 21/4A call made later in protected mode doesn't end up
;	 doing anything.

	 mov   di, ds			       ; DI = dgroup
	 mov   si, wp es:[2]		       ; SI = # paragraphs in data area
	 sub   si, di			       ;   ..
	 cmp   si, 1000h		       ; more than 64K?
	 jb    short sizeok		       ; if not, leave it alone
	 mov   si, 1000h		       ; yes. use only 64K

sizeok:
	 add   si, di			       ; SI = dgroup + sizeof(dgroup)
	 mov   wp es:[2], si		       ; reset pointer in PSP
	 mov   bx, es			       ; calculate new size of PSP seg
	 sub   bx, si			       ;   ..
	 neg   bx			       ;   ..
	 mov   ah, 4Ah			       ; fcn 4A: resize ES seg to BX
	 int   21h			       ; resize our segment
	 jc    initfail 		       ; die on error

;    2.  Verify that we're running under a DPMI host and get the mode-switch
;	 address. Allocate a memory block for use by DPMI during the initial
;	 switch.

	 mov   ax, 1687h		       ; get DPMI switch address
	 int   2Fh			       ;   ..
	 test  ax, ax			       ; is DPMI active?
	 jnz   nodpmi			       ; if not, error

	 mov   wp toprot, di		       ; save protected-mode switch addr
	 mov   wp toprot+2, es		       ;   ..
	 mov   bx, si			       ; BX = # paragraphs needed by host

	 test  bx, bx			       ; any memory needed?
	 jz    short nohostmem		       ; if not, skip ahead
	 mov   ah, 48h			       ; yes. get memory
	 int   21h			       ;   ..
	 jc    nomem			       ; die if can't get it
	 mov   hostdata, ax		       ; save host data area segment

nohostmem:

;    3.  Locate the full name under which we were executed at the end of the
;	 environment block. Open the EXE file for reading and read the EXE
;	 file header into memory.

	 cld				       ; set forward direction
	 mov   es, pspseg		       ; ES:0 -> PSP again
	 mov   es, wp es:[2Ch]		       ; ES:DI -> environment
	 xor   di, di			       ;   ..
	 xor   al, al			       ; AL = null to compare agains
	 xor   cx, cx			       ; CX = practically infinite count
	 dec   cx			       ;   ..

skipvar:
	 repne scasb			       ; find end of this environment variable
	 scasb				       ; compare next byte
	 jne   skipvar			       ; if not another null, do it again

	 add   di, 2			       ; skip word count
	 mov   dx, di			       ; ES:DX -> start of filename
	 push  ds			       ; save DS across call (1)
	 push  es			       ; set DS:DX -> filename
	 pop   ds			       ;   ..
	 mov   ax, 3D00h		       ; fcn 3D: open file
	 int   21h			       ;   ..
	 pop   ds			       ; restore DS (1)
	 jc    initfail 		       ; die if we couldn't do it

	 mov   hfile, ax		       ; save file handle
	 mov   bx, ax			       ; BX = file handle
	 mov   ah, 3Fh			       ; fcn 3F: read file
	 mov   cx, size exe_hdr 	       ; CX = byte count
	 mov   dx, offset exehdr	       ; DS:DX -> input buffer
	 int   21h			       ; read EXE file header
	 jc    readerr			       ; die if error

;    4.  Allocate memory and read the relocation table for the incoming EXE

	 mov   ah, 48h			       ; fcn 48: allocate memory
	 mov   bx, exehdr.e_crlc	       ; BX = (# fixups * 4) / 16
	 add   bx, 3			       ;   ..
	 shr   bx, 2			       ;   ..
	 int   21h			       ; get memory
	 jc    nomem			       ; die if we can't
	 mov   fixseg, ax		       ; save fixup data area

	 mov   ax, 4200h		       ; fcn 42: set file position
	 mov   bx, hfile		       ; BX = file handle
	 xor   cx, cx			       ; CX:DX = new position
	 mov   dx, exehdr.e_lfarlc	       ;   ..
	 int   21h			       ; seek to start of fixups
	 jc    readerr			       ;   ..

	 mov   ah, 3Fh			       ; fcn 3F: read file
	 mov   cx, exehdr.e_crlc	       ; CX = # bytes to read
	 shl   cx, 2			       ;   (4 * # fixups)
	 push  ds			       ; save DS across call
	 mov   ds, fixseg		       ; DS:DX -> input buffer
	 xor   dx, dx			       ;   ..
	 int   21h			       ; read fixup table
	 pop   ds			       ; restore DS
	 jc    readerr			       ; die if error

;    5.  Close the EXE file -- we've got all the info we want from it

	 mov   ah, 3Eh			       ; fcn 3E: close file
	 mov   bx, hfile		       ; BX = file handle
	 int   21h			       ; close the file

;    6.  Switch into protected mode using the DPMI switch-mode function
;	 pointer we obtained earlier. On return, we'll be in protected
;	 mode with:
;	     DS = data selector for DS segment
;	     CS = code selector for CS segment
;	     ES = selector for PSP, wherein environment pointer
;		  will have been translated to a selector

	 xor   ax, ax			       ; indicate 16-bit client
	 mov   es, hostdata		       ; ES = host data area
	 call  [toprot] 		       ; switch to protected mode
	 jc    switchfail		       ; die if error
	 mov   pspsel, es		       ; save PSP selector

;    7.  Allocate a selector to use while we relocate the program. We'll
;	 keep switching the base address for this to point to the segments
;	 in which fixups need to be adjusted. Allocate another selector for
;	 accessing the fixup table itself.

	 mov   ax, 0003h		       ; fcn 0003: get selector increment value
	 int   31h			       ;   (return in AX)
	 mov   selincr, ax		       ; save for later use

	 mov   ax, 0000h		       ; fcn 0000: allocate selector
	 mov   cx, 2			       ; we want 2 selectors
	 int   31h			       ; get selector (return in AX)
	 jc    initfail 		       ; die if can't

	 mov   es, ax			       ; ES = accessing selector
	 add   ax, selincr		       ; GS = fixup table selector
	 mov   gs, ax			       ;   ..

	 mov   ax, 0008h		       ; fcn 0008: set segment limit
	 mov   bx, es			       ; BX = selector
	 xor   cx, cx			       ; CX:DX = new limit
	 xor   dx, dx			       ;   ..
	 dec   dx			       ;   (namely 64K)
	 int   31h			       ; call DPMI to set limit
	 jc    initfail 		       ; die if can't

	 mov   ax, 0008h		       ; set limit for fixup tbl selector
	 mov   bx, gs			       ;   ..
	 movzx edx, exehdr.e_crlc	       ;   ..
	 shl   edx, 2			       ;   ..
	 dec   edx			       ;   ..
	 mov   ecx, edx 		       ;   ..
	 shr   ecx, 16			       ;   ..
	 int   31h			       ;   ..
	 jc    initfail 		       ;   ..

	 mov   ax, 0007h		       ; fcn 0007: set segment base
	 movzx edx, fixseg		       ; CX:DX = segment base addr
	 shl   edx, 4			       ;   ..
	 mov   ecx, edx 		       ;   ..
	 shr   ecx, 16			       ;   ..
	 int   31h			       ;   ..
	 jc    initfail 		       ;   ..

;    8.  Relocate the program to contain protected-mode selectors instead of
;	 real-mode paragraph numbers. We make multiple passes over the fixup
;	 table. Each pass deals with a particular real-mode segment, which
;	 turns into a separate selector. We mark fixups as being in FFFF:FFFF
;	 when we process them, this being an address that can't occur in a
;	 valid EXE-file fixup
;
;	 During the loop:
;	     GS:BX -> fixup table entry
;	     CX    =  number of fixup entries left to examine
;	     SI    =  real-mode paragraph
;	     DI    =  selector corresponding to SI

nextsegment:
	 xor   di, di			       ; indicate selector not chosen yet
	 mov   cx, exehdr.e_crlc	       ; CX = # fixups
	 xor   bx, bx			       ; GS:BX -> fixup table

nextfixup:
	 movzx edx, wp gs:[bx+2]	       ; EDX = segment part of fixup addr
	 cmp   dx, -1			       ; already processed it?
	 jne   short nextfixup_1	       ; if not, stay here
	 cmp   wp gs:[bx], -1		       ; check offset part of fixup ptr too
	 je    skipfixup		       ;   ..

;    If necessary, change the base address for the ES segment to the segment
;    which contains a fixed-up location

nextfixup_1:
	 add   dx, relocfactor		       ; adjust fixup cell pointer
	 cmp   dx, lastseg		       ; is ES already set to same segment?
	 je    short nextfixup_2	       ;   ..
	 mov   lastseg, dx		       ; no. remember this for next time
	 shl   edx, 4			       ; EDX = linear addr of segment containing fixup

	 push  cx			       ; save BX & CX across call
	 push  bx			       ;   ..
	 mov   ax, 0007h		       ; fcn 0007: set segment base
	 mov   bx, es			       ; BX = selector
	 mov   ecx, edx 		       ; CX:DX = base address to set
	 shr   ecx, 16			       ;   ..
	 int   31h			       ; set base address for target segment
	 pop   bx			       ; restore registers anyway
	 pop   cx			       ;   ..
	 jc    initfail 		       ; die if error setting base

;    See if we already have a selector for the segment to which this
;    location was fixed up.

nextfixup_2:
	 push  bx			       ; save BX
	 mov   bx, wp gs:[bx]		       ; BX = offset part of fixup ptr
	 mov   ax, wp es:[bx]		       ; AX = segment at fixup location
	 pop   bx			       ; restore BX

	 test  di, di			       ; already have selector?
	 jnz   short nextfixup_4	       ; if not, skip ahead
	 mov   si, ax			       ; save real-mode segment

	 mov   di, cs			       ; is it our code segment?
	 cmp   ax, codeseg		       ;   ..
	 je    short nextfixup_4	       ;   ..
	 mov   di, ds			       ; is it our data segment?
	 cmp   ax, dataseg		       ;   ..
	 je    short nextfixup_4	       ;   ..
	 mov   di, pspsel		       ; it it our PSP segment?
	 cmp   ax, pspseg		       ;   ..
	 je    short nextfixup_4	       ;   ..

;    Allocate a new selector for a segment to which things are fixed up

	 push  bx			       ; save BX & CX
	 push  cx			       ;   ..

	 mov   cx, 1			       ; CX = selector count, namely 1
	 mov   ax, 0000h		       ; fcn 0000: allocate selector
	 int   31h			       ; get a selector
	 jc    short nextfixup_3	       ; die if we can't get selector

	 mov   di, ax			       ; save new selector

	 mov   ax, 0008h		       ; fcn 0008: set segment limit
	 mov   bx, di			       ; BX = selector
	 xor   cx, cx			       ; CX:DX = new limit
	 xor   dx, dx			       ;   ..
	 dec   dx			       ;   (namely 64K)
	 int   31h			       ; call DPMI to set limit
	 jc    short nextfixup_3

	 mov   ax, 0007h		       ; fcn 0007: set segment base
	 movzx edx, si			       ; CX:DX = segment base
	 shl   edx, 4			       ;   ..
	 mov   ecx, edx 		       ;   ..
	 shr   ecx, 16			       ;   ..
	 int   31h			       ;   ..
	 jc    nextfixup_3		       ; die if can't do it

;    If real-mode segment preceeds c_etext, it's a code segment

	 cmp   si, endcode		       ; code segment?
	 jae   nextfixup_3		       ; if not, don't change attributes
	 lar   ecx, edi 		       ; get current access rights
	 shr   ecx, 8			       ; shift to position for 31/0009
	 or    cl, 08h			       ; flag as code segment
	 mov   bx, di			       ; BX = selector
	 mov   ax, 0009 		       ; fcn 0009: set access rights
	 int   31h			       ; make this a code segment

nextfixup_3:
	 pop   cx			       ; restore BX & CX
	 pop   bx			       ;   ..
	 jc    initfail 		       ; die if error building descriptor
	 mov   ax, si			       ; make compare succeed 1st time

nextfixup_4:
	 cmp   ax, si			       ; in the same segment?
	 jne   short skipfixup		       ; if not, skip this fixup
	 push  bx			       ; yes. change relocation
	 mov   bx, wp gs:[bx]		       ;   ..
	 mov   wp es:[bx], di		       ;   ..
	 pop   bx			       ;   ..
	 mov   wp gs:[bx], -1		       ; flag this fixup as used up
	 mov   wp gs:[bx+2], -1 	       ;   ..

skipfixup:
	 add   bx, 4			       ; up to next fixup
	 dec   cx			       ;   ..
	 jg    nextfixup		       ;   ..
	 test  di, di			       ; did we find any unfixed fixups?
	 jnz   nextsegment		       ; if yes, do another pass

;    9.  Release the temporary selectors we've been using. The DPMI host
;	 *should* zero-out any segment register that contains the same
;	 selector before returning, but we want to do this ourselves to
;	 prevent a GP fault in case it doesn't.

	 mov   ax, 0001h		       ; fcn 0001: release selector
	 mov   bx, es			       ; BX = fixup location accessing selector
	 xor   cx, cx			       ; (clear ES ourselves to prevent GP fault)
	 mov   es, cx			       ;   ..
	 int   31h			       ; cancel accessing selector

	 mov   ax, 0001h		       ; now release fixup tbl selector
	 mov   bx, gs			       ;   ..
	 mov   gs, cx			       ;   ..
	 int   31h			       ;   ..

;    Release the DOS memory block we allocated to hold the fixup table from
;    the EXE file. We couldn't have used DPMI function 0101 for this purpose
;    because that only works for blocks allocated by function 0100. Therefore,
;    use function 0300 (simulate real-mode interrupt) to perform a 21/49.

	 mov   bp, sp			       ; save stack pointer
	 xor   eax, eax 		       ; get dword of zeros
	 push  eax			       ; build RM reg structure: ss:sp
	 push  eax			       ; cs:ip
	 push  eax			       ; fs, gs
	 push  ax			       ; ds
	 push  fixseg			       ; es (segment to release)
	 pushf				       ; flags
	 mov   ecx, 4900h		       ; eax = dos fcn 49
	 push  ecx			       ;   ..
	 push  eax			       ; ecx
	 push  eax			       ; edx
	 push  eax			       ; ebx
	 push  eax			       ; reserved (esp slot in pushad)
	 push  eax			       ; ebp
	 push  eax			       ; esi
	 push  eax			       ; edi

	 mov   ax, ss			       ; ES:DI -> real-mode register structure
	 mov   es, ax			       ;   ..
	 mov   di, sp			       ;   ..
	 mov   ax, 0300h		       ; fcn 0300: simulate real-mode interrupt
	 mov   bx, 21h			       ; BX = interrupt # (21)
	 xor   cx, cx			       ; CX = # bytes of stack to copy
	 int   31h			       ; release memory

	 mov   sp, bp			       ; restore stack past reg structure

;    10. Jump to the regular C library initialization routine.

	 mov   es, pspsel		       ; ES -> PSP
	 mov   ds, pspsel		       ; DS ditto
	 extrn _astart:near
	 jmp   _astart			       ; jump to library initialization

;------------------------------------------------------------------------------
;
;    Error handling:
;
;------------------------------------------------------------------------------

	 .data
initfailmsg db 'Unable to initialize program for protected-mode operation', 13, 10, '$'
nodpmimsg   db 'A DPMI host environment is required for this program', 13, 10, '$'
nomemmsg    db 'Insufficient memory to initialize program for protected mode', 13, 10, '$'
readerrmsg  db 'Error reading EXE file for protected-mode relocation', 13, 10, '$'
switchfailmsg db 'Unable to switch to protected mode', 13, 10, '$'

	 .code

initfail:
	 mov   dx, offset initfailmsg
	 jmp   msgdie

nodpmi:
	 mov   dx, offset nodpmimsg
	 jmp   msgdie

nomem:
	 mov   dx, offset nomemmsg
	 jmp   msgdie

readerr:
	 mov   dx, offset readerrmsg
	 jmp   msgdie

switchfail:
	 mov   dx, offset switchfailmsg
	 jmp   msgdie

msgdie:
	 mov   ah, 9			       ; fcn 9: write string
	 int   21h			       ; print error message
	 mov   ax, 4C01h		       ; exit with code 1
	 int   21h			       ;   (doesn't return)

@curseg  ends

;------------------------------------------------------------------------------
;
;    Replacement routine for runtime library FPINSTALL87 (which wants to
;    save addresses in the code segment -- a definite no-no in protected mode
;
;------------------------------------------------------------------------------

emulator_data segment byte public 'far_data'
org02	 dd    0			       ; original INT 02 vector
org23	 dd    0			       ; original INT 23 vector
emulator_data ends

emulator_text segment byte public 'code'

	 public _FPINSTALL87
_FPINSTALL87:
	 push  ds			       ; save DS
	 mov   ax, emulator_data	       ; point to emulator data segment
	 mov   ds, ax			       ;   ..
	 assume ds:emulator_data

	 mov   ax, 3502h		       ; fcn 35: get interrupt vector
	 int   21h			       ; get current INT 2 vector
	 mov   wp org02, bx		       ; save for later use
	 mov   wp org02+2, es		       ;   ..

	 mov   ax, 3523h		       ; ditto for INT 23
	 int   21h			       ;   ..
	 mov   wp org23, bx		       ;   ..
	 mov   wp org23+2, es		       ;   ..

	 mov   ax, cs			       ; set DS = CS
	 mov   ds, ax			       ;   ..
	 mov   ax, 2502h		       ; fcn 25: set interrupt vector
	 mov   dx, offset int02 	       ; DS:DX = new service routine
	 int   21h			       ; hook INT 2 for coprocessor emulation

	 mov   ax, 2523h		       ; hook INT 23 as well
	 mov   dx, offset int23 	       ;   ..
	 int   21h			       ;   ..

	 pop   ds			       ; restore DS
	 retn				       ; return to local caller

	 public _FPTERMINATE87
_FPTERMINATE87:
	 push  ax			       ; save working registers
	 push  dx			       ;   ..
	 push  ds			       ;   ..

	 mov   ax, emulator_data	       ; point DS to emulator data segment
	 mov   ds, ax			       ;   ..

	 mov   ax, 2502h		       ; fcn 25: set interrupt vector
	 lds   dx, org02		       ; DS:DX = handler address
	 int   21h			       ; unhook INT 2

	 pop   ds			       ; restore registers
	 pop   dx			       ;   ..
	 pop   ax			       ;   ..
	 retn				       ; return to caller

int23:
	 sub   sp, 4			       ; leave room for return address
	 push  ax			       ; save working registers
	 push  dx			       ;   ..
	 push  ds			       ;   ..
	 push  bp			       ;   ..
	 call  _FPTERMINATE87		       ; unhook INT 2

	 mov   ax, emulator_data	       ; get address of original INT 23 handler
	 mov   ds, ax			       ;   ..
	 lds   dx, org23		       ;   ..
	 mov   bp, sp			       ; save on our stack
	 mov   wp [bp+10], ds		       ;   ..
	 mov   wp [bp+8], dx		       ;   ..
	 mov   ax, 2523h		       ; unhook INT 23
	 int   21h			       ;   ..

	 pop   bp			       ; restore registers
	 pop   ds			       ;   ..
	 pop   dx			       ;   ..
	 pop   ax			       ;   ..
	 retf				       ; exit via original handler

int02:
	 push  ax			       ; save working register
	 fstsw ax			       ; get FPU status word
	 fwait				       ; wait for op to complete
	 test  al, 80h			       ; is there an exeption pending?
	 pop   ax			       ; restore AX in any case
	 jnz   chain02			       ; if no exception, chain the interrupt

	 extrn _FPEXCEPTION87:near
	 call  _FPEXCEPTION87		       ; call exception handler
	 iret				       ; return to point of interrupt

chain02:
	 sub   sp, 4			       ; make room for address
	 push  ax			       ; save working regs
	 push  ds			       ;   ..
	 push  bp			       ;   ..
	 mov   bp, sp			       ; get stack addressability
	 mov   ax, emulator_data	       ; address emulator data segment
	 mov   ds, ax			       ;   ..
	 mov   ax, wp org02		       ; copy old handler address
	 mov   wp [bp+6], ax		       ;   ..
	 mov   ax, wp org02+2		       ;   ..
	 mov   wp [bp+8], ax		       ;   ..
	 pop   bp			       ; restore registers
	 pop   ds			       ;   ..
	 pop   ax			       ;   ..
	 retf				       ; exit via original handler

emulator_text ends

	 end   realstart
