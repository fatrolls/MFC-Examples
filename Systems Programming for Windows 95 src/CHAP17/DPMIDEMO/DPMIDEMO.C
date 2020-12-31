/*****************************************************************************/
/*									     */
/*    DPMIDEMO.C -- Demonstration program for DPMI features		     */
/*									     */
/*    Copyright (C) 1993 by Walter Oney 				     */
/*    All rights reserved						     */
/*									     */
/*****************************************************************************/

#ifdef _WINDOWS
   #include <windows.h>
   #define WALTIO_MAIN _main
   #include "waltio.h"
   #define main _main
   #define STRING LPSTR
#else
   #include <stdio.h>
   #define MAKELP(s,o) ((void _far *)( ((unsigned long)(unsigned short)(s) << 16) | ( (unsigned long) (unsigned short) (o) & 65535L )  ))
   #define SELECTOROF(p) ((unsigned short) ((unsigned long) p >> 16))
   #define OFFSETOF(p) ((unsigned short) (unsigned long) p)
   #define STRING char *
#endif

#include <stdlib.h>
#include <string.h>

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

typedef struct
   {				 // real-mode register structure
   unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax;
   unsigned short flags, es, ds, fs, gs, ip, cs, sp, ss;
   } RMREGS;			 // real-mode register structure

typedef struct tagIFRAME
   {				 // interrupt frame
   unsigned short es, ds;
   unsigned short di, si, bp, sp, bx, dx, cx, ax;
   unsigned short ip, cs, flags;
   } IFRAME;			 // interrupt frame

static void showdesc(unsigned short sel, char *name, unsigned short _far *desc);
static void showsel(unsigned short sel, char *name);
static void pause(void);
static int cancel(unsigned int sel);
static void (interrupt _far int1b)(IFRAME f);
static void (interrupt _far emulate)(IFRAME f);
static void _far _loadds int07();

static volatile int breakflag;
static volatile int fpuflag;
static unsigned int selincr;

int main(int argc, char *argv[])
   {				 // main
   unsigned int code;		 // error code

   puts("DPMI Demonstration Program Version 1.0\n"
	"Copyright (C) 1993 by Walter Oney\n"
	"All rights reserved");

/*---------------------------------------------------------------------------*/

   {				 // display execution environment
   unsigned short csreg, dsreg, envseg;

   putchar('\n');
   _asm
      { 			 // capture segment regs
      mov   csreg, cs
      mov   dsreg, ds
      mov   es, _psp
      mov   ax, word ptr es:[2Ch]
      mov   envseg, ax
      } 			 // capture segment regs
   showsel(csreg, "CS");
   showsel(dsreg, "DS");
   showsel(_psp, "PSP");
   showsel(envseg, "ENV");
   }				 // display execution environment

/*---------------------------------------------------------------------------*/

   {				 // access video memory
   unsigned int b800;		 // selector to B800:
   unsigned short _far *video;
   static unsigned char msg[] =
      {'H', 0xB5
      ,'e', 0xB5
      ,'l', 0xB5
      ,'l', 0xB5
      ,'o', 0xB5
      ,',', 0xB5
      ,' ', 0xB5
      ,'W', 0xB5
      ,'o', 0xB5
      ,'r', 0xB5
      ,'l', 0xB5
      ,'d', 0xB5
      ,'!', 0xB5};

   pause();
   _asm
      { 			 // get selector for video memory
      mov   ax, 0002h		 ; fcn 0002: Segment to Descriptor
      mov   bx, 0B800h		 ; BX = real-mode segment
      int   31h 		 ; get selector (return in AX)
      mov   b800, ax		 ; save selector
      rcl   al, 1		 ; capture error flag
      mov   code, ax		 ;   ..
      } 			 // get selector for video memory
   if (code & 1)
      puts("==> Unable to map segment B800 to a selector <==");
   else
      { 			 // use the selector
      showsel(b800, "B800");
      video = MAKELP(b800, 15*2*80);
      _fmemcpy(video, msg, sizeof(msg));
      cancel(b800);
      } 			 // use the selector
   }				 // access video memory

/*---------------------------------------------------------------------------*/

   {				 // install Ctrl-Break handler
   void (interrupt _far *org1b)();
   void _far *callback; 	 // real-mode callback address
   RMREGS rmregs;		 // real-mode registers for callback
   long i;			 // loop counter

   pause();

/* Ctrl-Break is signalled by the BIOS on INT 1B in real mode. We'll hook
   the real-mode interrupt to a real-mode callback which will pass control
   to our "int1b" handler. */

   _asm
      { 			 // hook real-mode 1B
      push  ds			 ; save DS across call

   ;  When we allocate the real-mode callback using 31/0303, we supply
   ;  the address of a real-mode register structure that must exist at
   ;  the time the callback occurs. Normally, you'd use a static variable
   ;  for this purpose. It suffices here to use an automatic variable
   ;  because we'll free the callback before it goes out of scope.

      mov   ax, 0303h		 ; fcn 0303: allocate real-mode callback
      mov   si, cs		 ; DS:SI -> protected-mode procedure to call
      mov   ds, si		 ;   ..
      mov   si, offset int1b	 ;   ..
      mov   di, ss		 ; ES:DI -> real-mode register structure
      mov   es, di		 ;   ..
      lea   di, rmregs		 ;   ..
      int   31h 		 ; call DPMI, return in CX:DX

      pop   ds			 ; restore DS no matter what
      jc    err1b		 ; skip ahead if error

      mov   word ptr callback, dx   ; save callback address for eventual 0304
      mov   word ptr callback+2, cx ;  ..

   ;  No-one will restore the real-mode interrupt vector if we don't, so
   ;  be sure to save the original value before hooking it

      mov   ax, 0200h		 ; fcn 0200: get real-mode interrupt vector
      mov   bl, 1Bh		 ; BL = interrupt #
      int   31h 		 ; call DPMI, return in CX:DX
      mov   word ptr org1b, dx	 ; save old 1B vector
      mov   word ptr org1b+2, cx ;   ..

      mov   ax, 0201h		 ; fcn 0201: set real-mode interrupt vector
      mov   bl, 1Bh		 ; BL = interrupt #
      mov   dx, word ptr callback; CX:DX = new handler address
      mov   cx, word ptr callback+2 ;  ..
      int   31h 		 ; (always succeeds)

   err1b:
      rcl   al, 1		 ; capture error code
      mov   code, ax		 ;   ..
      } 			 // hook real-mode 1B

   if (code & 1)
      puts("==> Error trying to hook real-mode INT 1B <==");
   else
      { 			 // exercise 1B hook
      breakflag = 0;
      puts("INT 1Bh hooked. Press Ctrl-Break to test it . . .");
      for (i = 0; i < 10000000 && !breakflag; ++i)
	 ;
      if (breakflag)
	 printf("Loop terminated due to Ctrl-Break with counter = %ld\n", i);
      else
	 printf("Loop terminated by itself after %ld iterations\n", i);

      _asm
	 {			 // cleanup
	 mov   ax, 0201h	 ; restore original INT 1B handler
	 mov   bl, 1Bh
	 mov   dx, word ptr org1b
	 mov   cx, word ptr org1b+2
	 int   31h
	 mov   ax, 0304h	       ; fcn 0304: free real-mode callback address
	 mov   dx, word ptr callback   ; CX:DX -> real-mode callback to free
	 mov   cx, word ptr callback+2 ;  ..
	 int   31h		       ;  ..
	 rcl   al, 1		 ; capture error indication
	 mov   code, ax
	 }			 // cleanup
      if (code & 1)
	 puts("==> Error trying to free real-mode callback address <==");
      } 			 // exercise 1B hook
   }				 // install Ctrl-Break handler

/*---------------------------------------------------------------------------*/

   {				 // illustrate FPU emulation
   unsigned short fpustatus;	 // status reported by 31/0E00
   void (far *org07)(); 	 // original INT 7 handler

   pause();

/* Use 31/0E00 to get information about the coprocessor (if any) on this
   machine. */

   _asm
      { 			 // get FPU info
      mov   ax, 0E00h		 ; fcn 0E00: get coprocessor status
      int   31h 		 ; return in AX
      mov   fpustatus, ax	 ; save status return
      rcl   al, 1		 ; capture error indication
      mov   code, ax		 ;   ..
      } 			 // get FPU info
   if (code & 1)
      { 			 // 0E00 failed
      puts("==> DPMI host doesn't support 0Exx calls <==");
      goto fpudone;
      } 			 // 0E00 failed
   printf("31/0E00 reports FPU status %4.4X\n", fpustatus);
   printf("        coprocessor is%s enabled for this client\n",
      (STRING) ((fpustatus & 1) ? "" : " not"));
   printf("        emulation is%s enabled for this client\n",
      (STRING) ((fpustatus & 2) ? "" : " not"));
   printf("        coprocessor is%s present\n",
      (STRING) ((fpustatus & 4) ? "" : " not"));
   printf("        host is%s emulating coprocessor\n",
      (STRING) ((fpustatus & 8) ? "" : " not"));
   printf("        coprocessor type is: ");
   if ((fpustatus & 0xF0) == 0)
      puts("none");
   else if ((fpustatus & 0xF0) == 0x20)
      puts("80287");
   else if ((fpustatus & 0xF0) == 0x30)
      puts("80387");
   else if ((fpustatus & 0xF0) == 0x40)
      puts("i486 with integral coprocessor");

/* Hook the coprocessor not present exception (INT 07). Then turn on
   emulation for this VM. */

   _asm
      { 			 // hook not-present exception
      mov   ax, 0202h		 ; fcn 0202: get processor exception vector
      mov   bl, 7		 ; BL = interrupt number
      int   31h 		 ; (return in CX:DX)
      mov   word ptr org07, dx	 ; save current int 7 handler addr
      mov   word ptr org07+2, cx ;   ..

      mov   ax, 0203h		 ; fcn 0203: set processor exception vector
      mov   bl, 7		 ; BL = interrupt number
      mov   cx, cs		 ; CX:DX -> exception handler
      mov   dx, offset int07	 ;   ..
      int   31h 		 ;   ..

      mov   ax, 0E01h		 ; fcn 0E01: set coprocessor emulation
      mov   bx, 2		 ; BX = flags (here: turn on emulation)
      int   31h 		 ;   ..
      smsw  code		 ; capture resulting MSW
      } 			 // hook not-present exception

   printf("MSW after 31/0E01 is %4.4X\n", code);
   if (code & 4)
      puts("Coprocessor emulation has been established, about to trigger INT 7");

   fpuflag = 0;
   _asm _emit 0D9h		; i.e., FNOP
   _asm _emit 0D0h
   if (fpuflag)
      printf("Not-present handler got called %d time(s)\n", fpuflag);
   else
      puts("==> Not-present handler never got called (?) <==");

/* Cleanup after emulation demonstration */

   _asm
      { 			 // cleanup
      mov   ax, 0E01h
      xor   bx, bx
      int   31h
      mov   ax, 0203h
      mov   bl, 7
      mov   dx, word ptr org07
      mov   cx, word ptr org07+2
      int   31h
      } 			 // cleanup

fpudone:
   ;
   }				 // illustrate FPU emulation

/*---------------------------------------------------------------------------*/

   {				 // get DPMI status info
   unsigned char vermajor, verminor, cputype, masterpic, slavepic;
   unsigned short flags;
   static char *cpuname[] = {"", "", "80286", "80386", "i486", "Pentium"};

   pause();
   _asm
      { 			 // get version info
      mov   ax, 0400h		 ; fcn 0400: get version
      int   31h 		 ; (return in other regs)
      mov   vermajor, ah	 ; AH = major version #
      mov   verminor, al	 ; AL = minor version #
      mov   flags, bx		 ; BX = flags
      mov   cputype, cl 	 ; CL = cpu type
      mov   masterpic, dh	 ; DH = master PIC base interrupt
      mov   slavepic, dl	 ; DL = slave PIC base interrupt
      } 			 // get version info
   printf("32/0400 reports DPMI version %d.%2.2d\n", vermajor, verminor);
   printf("        host is %d-bit\n", (flags & 1) ? 32 : 16);
   printf("        interrupts reflected to %s mode\n",
      (STRING) ((flags & 2) ? "real" : "V86"));
   printf("        processor type is %s\n", (STRING) cpuname[cputype]);
   printf("        PIC interrupt base addresses are %2.2X, %2.2X\n",
      masterpic, slavepic);
   }				 // get DPMI status info

/*---------------------------------------------------------------------------*/

   {				 // allocate a huge array
   long huge *foo;		 // pointer to >64k worth of integers
   long i;			 // loop control
   long sum;
   unsigned long hmem;		 // handle to memory block

   pause();
   _asm
      { 			 // allocate a huge array
      mov   ax, 0003h		 ; fcn 0003: get selector increment value
      int   31h 		 ;   ..
      mov   selincr, ax 	 ;   ..

      mov   ax, 0000h		 ; fcn 0000: allocate selector
      mov   cx, 2		 ; CX = # selectors wanted
      int   31h 		 ;   ..
      jc    err501
      mov   word ptr foo, 0	 ; build pointer to base of array
      mov   word ptr foo+2, ax	 ;   ..

      mov   ax, 0501h		 ; fcn 0501: allocate memory
      xor   cx, cx		 ; BX:CX = length (128k)
      mov   bx, 2		 ;   ..
      int   31h 		 ; (returns linaddr in BX:CX)
      jc    err501		 ; skip if error
      mov   word ptr hmem, di	 ; SI:DI = memory block handle
      mov   word ptr hmem+2, si  ;   ..

      mov   ax, 0007h		 ; fcn 0007: set segment base address
      mov   dx, cx		 ; CX:DX = base address
      mov   cx, bx		 ;   ..
      mov   bx, word ptr foo+2	 ; BX = selector
      int   31h 		 ; set base addr for 1st selector
      jc    err501		 ; skip if error

      mov   ax, 0007h		 ; set base for 2d selector
      add   bx, selincr 	 ;   ..
      inc   cx			 ; (64k higher than 1st)
      int   31h 		 ;   ..
      jc    err501		 ; skip if error

      xor   cx, cx		 ; set limit on last selector to 64k
      xor   dx, dx		 ;   ..
      dec   dx			 ;   ..
      mov   ax, 0008h		 ;   ..
      int   31h 		 ;   ..
      jc    err501		 ;   ..

      sub   bx, selincr 	 ; set limits on earlier selectors
      inc   cx			 ; (i.e., 1st one spans whole array)
      mov   ax, 0008h		 ;   ..
      int   31h 		 ;   ..

   err501:
      rcl   al, 1		 ; capture error indication
      mov   code, ax		 ;   ..
      } 			 // allocate a huge array

   if (code & 1)
      puts("==> Error trying to allocate huge array <==");
   else
      { 			 // use huge array
      showsel(SELECTOROF(foo), "FOO[0]");
      showsel(SELECTOROF(foo)+selincr, "FOO[1]");
      for (i = 0; i < 32768; ++i)
	 foo[i] = i;
      for (sum = 0, i = 0; i < 32768; ++i)
	 sum += foo[i];
      printf("Sum of integers in huge array is %ld (correct would be %ld)\n",
	 sum, (32768L*32767L)/2L);
      cancel(SELECTOROF(foo));
      cancel(SELECTOROF(foo)+selincr);
      _asm
	 {			 // cleanup
	 mov   ax, 0502h	 ; fcn 0502: free memory block
	 mov   di, word ptr hmem ; SI:DI = memory block handle
	 mov   si, word ptr hmem+2
	 int   31h		 ; release memory
	 }			 // cleanup
      } 			 // use huge array
   }				 // allocate a huge array

   }				 // main

/*****************************************************************************/

static void showdesc(unsigned short sel, char *name, unsigned short _far *desc)
   {				 // showdesc
   unsigned long limit, base;
   unsigned int type;

   #define GBIT 0x0080		 // in desc[3]
   #define BBIT 0x0040		 // "
   #define PBIT 0x8000		 // in desc[2]
   #define DPL	0x6000		 // "
   #define SBIT 0x1000		 // "
   #define TYPE 0x0F00		 // "
   static char *systypes[] =
      {"", "Avail TSS16", "LDT", "Busy TSS16", "CGate16", "TaskGate",
      "IGate16", "TGate16", "", "Avail TSS32", "", "Busy TSS32",
      "CGate32", "", "IGate32", "TGate32"};

   printf("%s (%4.4X) descriptor is: %4.4X.%4.4X.%4.4X.%4.4X\n",
      (STRING) name, sel, desc[3], desc[2], desc[1], desc[0]);
   limit = ((unsigned long) desc[0])
      | (((unsigned long) desc[3] & 0x000F) << 16);
   base = ((unsigned long) desc[1])
      | (((unsigned long) desc[2] & 0x00FF) << 16)
      | (((unsigned long) desc[3] & 0xFF00) << 16);
   if (desc[3] & GBIT)
      limit = (limit << 12) | 4095;
   type = (desc[2] & TYPE) >> 8;
   if (desc[2] & SBIT)
      { 			 // application segment
      printf("   %sPresent %s %s segment at %8.8lX,\n   length %8.8lX, DPL %d, ",
	 (STRING) ((desc[2] & PBIT) ? "" : "Not "),
	 (STRING) ((desc[3] & BBIT) ? "USE32" : "USE16"),
	 (STRING) ((type & 8) ? "CODE" : "DATA"),
	 base, limit+1, (desc[2] & DPL) >> 13);
      if (type & 8)
	 printf("%s, %sconforming\n", (STRING) ((type & 2) ? "XR" : "XO"),
	    (STRING) ((type & 4) ? "" : "not "));
      else
	 printf("%s, expand %s\n", (STRING) ((type & 2) ? "RW" : "RO"),
	    (STRING) ((type & 4) ? "down" : "up"));
      } 			 // application segment
   else
      { 			 // system segment
      printf("   %sPresent %s at %8.8lX, length %8.8lX, DPL %d\n",
	 (STRING) ((desc[2] & PBIT) ? "" : "Not "),
	 (STRING) systypes[type], base, limit+1, (desc[2] & DPL) >> 13);
      } 			 // system segment
   }				 // showdesc

/*****************************************************************************/

static void showsel(unsigned short sel, char *name)
   {				 // showsel
   unsigned short desc[4];
   int code;

   _asm
      { 			 // get descriptor for this selector
      mov   ax, 000Bh		 ; fcn 000B: get descriptor
      mov   bx, sel		 ; BX = selector in question
      mov   di, ss		 ; ES:DI -> descriptor buffer
      mov   es, di		 ;   ..
      lea   di, desc		 ;   ..
      int   31h 		 ; go get descriptor
      rcl   al, 1		 ; capture error flag
      mov   code, ax		 ;   ..
      } 			 // get descriptor for this selector

   if (code & 1)
      printf("%s (%4.4X) selector is invalid or cancelled\n", (STRING) name, sel);
   else
      showdesc(sel, name, desc);

   }				 // showsel

/*****************************************************************************/

static void pause(void)
   {				 // pause
#ifndef _WINDOWS
   char junkbuf[132];
   printf("\nPress [Enter] to continue>");
   gets(junkbuf);
#endif
   }				 // pause

/*****************************************************************************/

static int cancel(unsigned int sel)
   {				 // cancel
   #pragma warning(disable:4035)
   _asm
      { 			 // cancel the selector
      mov   ax, 0001h		 ; fcn 0001: free descriptor
      mov   bx, sel		 ; BX = selector to cancel
      int   31h 		 ;   ..
      mov   ax, 0FFFFh		 ; capture error code
      rcl   al, 1		 ;   ..
      not   ax			 ; change to T/F return value
      } 			 // cancel the selector
   }				 // cancel

/*****************************************************************************/

/* Our INT 1B handler is entered as a real-mode callback from the real-mode
   INT 1B vector. The registers will be as follows:

   DS:SI -> protected-mode address corresponding to real-mode stack
	    at the time of the interrupt
   ES:DI -> real-mode register structure in which real-mode registers
	    have been saved
   SS:SP -> locked 4K stack provided by DPMI host

   In Windows, the stack will contain an interrupt frame pointing to a
   a protected-mode callback in "segment" 3B. We are expected to IRET to
   this address.

   In addition, the compiler will generate the following prolog:

      PUSHA
      PUSH  DS
      PUSH  ES
      MOV   DS, DGROUP	 [well, you know what I mean]
*/

static void (interrupt _far int1b)(IFRAME f)
   {				 // int1b
   unsigned short _far *stack;	 // pointer to real-mode stack
   RMREGS _far *rp;		 // pointer to real-mode registers

/* Assert a flag that will cause the loop to terminate. Note that this is
   the only substantive operation actually done inside this routine -- the
   rest is administrative stuff. */

   breakflag = 1;

/* Simulate an IRET on behalf of the real-mode process. *We* must do this
   because DPMI doesn't have any a-priori way to know whether the callback
   was reached via a near call, far call, interrupt, or whatever. */

   stack = MAKELP(f.ds, f.si);
   rp = MAKELP(f.es, f.di);
   rp->ip = stack[0];
   rp->cs = stack[1];
   rp->flags = stack[2];
   rp->sp += 6;
   }				 // int1b

/*****************************************************************************/

/* A DPMI exception handler is entered as if from a far call on a special
   4K locked stack. It must return, which means it can't simply do a
   longjmp around some problem or another. This handler illustrates the
   standard technique of saving the interrupt-old context and redirecting
   execution to a real handler that runs on the stack where the interrupt
   occurred. */

static void _far _loadds int07
   (unsigned int code,		 // exception error code
   unsigned int oldip,		 // interrupt-old IP
   unsigned int oldcs,		 // interrupt-old CS
   unsigned int oldflags,	 // interrupt-old flags
   unsigned int oldsp,		 // interrupt-old SP
   unsigned int oldss)		 // interrupt-old SS
   {				 // int07
   unsigned short _far *stack = MAKELP(oldss, oldsp -= 6);
   stack[0] = oldip;
   stack[1] = oldcs;
   stack[2] = oldflags;

   _asm
      { 			 // redirect restart address
      mov   oldcs, cs
      mov   ax, offset emulate
      mov   oldip, ax
      } 			 // redirect restart address
   }				 // int07

/*****************************************************************************/

/* This dummy emulation routine is entered as a true interrupt handler on the
   same stack as the interrupting instruction. If you were writing a real
   emulator, you'd do lots of work here. In this example, we only executed
   a 2-byte FNOP instruction, so that's all we have to skip. Note that we're
   back on the DGROUP stack when we get here, so it's okay to call printf. */

static void (interrupt _far emulate)(IFRAME f)
   {				 // emulate
   _asm sti			 // enable virtual interrupts
   printf("Coprocessor not-present exception occurred at %4.4X:%4.4X\n",
      f.cs, f.ip);
   f.ip += 2;			 // skip "emulated" instruction
   ++fpuflag;
   }				 // emulate
