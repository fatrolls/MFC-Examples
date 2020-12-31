/*****************************************************************************/
/*                                                                           */
/*    TEST.C -- Test program for IRQ virtualization VxD                      */
/*                                                                           */
/*    Note: This test uses IRQ 12. To try it on your own system, find a free */
/*    IRQ. Modify this program and MYVXD.ASM.                                */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <dos.h>
#include <conio.h>

typedef struct tagIFRAME
	{unsigned _es, _ds, _di, _si, _bp, _sp, _bx, _dx, _cx,  _ax, _ip, _cs, _flags;} IFRAME;
	
typedef void (__interrupt INTPROC)();
typedef INTPROC __far* LPINTPROC;
void __interrupt int74(IFRAME);
static char answer[512];
static int done;
static int index;

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
	{							// main
	LPINTPROC org74;			// original interrupt vector
	unsigned char orgimr;		// original interrupt mask register for slave PIC
	
	org74 = _dos_getvect(0x74);	// remember original interrupt vector
	_dos_setvect(0x74, int74);	// hook hardware interrupt

	_asm
		{						// unmask IRQ
		cli						; disable while we change IMR
		in	al, 0A1h			; get slave PIC IMR
		mov	orgimr, al			; save for restoration later
		or	al, 10h				; toggle mask bit to force mask change
		out	0A1h, al			;   procedure to acknowledge us as owning VM
		jmp	delay1				;   ..
	delay1: jmp delay2			;   ..
	delay2:						;   ..
		and	al, not 10h			; unmask our IRQ
		out	0A1h, al			;   ..
		sti						; re-enable interrupts
		}						// unmask IRQ
	
	while (!done)
		_asm
			{					// wait for string to be read
			mov	ax, 1680h
			int 2Fh
			}					// wait for string to be read
	puts(answer);
	
	_asm
		{						// mask IRQ
		mov	ah, orgimr			; original mask register
		and	ah, 10h				; keep only our IRQ's bit
		cli						; disable while we change IMR
		in	al, 0A1h			; get slave PIC IMR
		or	al, ah				; restore original mask value
		out	0A1h, al			;   ..
		sti						; re-enable
		}						// mask IRQ
	_dos_setvect(0x74, org74);	// restore original interrupt vector
	return 0;
	}							// main
	
///////////////////////////////////////////////////////////////////////////////

void __interrupt int74(IFRAME f)
	{							// int74
	char ch;

	ch = inp(0x1234);			// read from simulated port
	outp(0xA0, 0x20);			// EOI slave
	outp(0x20, 0x20);			// EOI master
	answer[index++] = ch;		// accumulate string
	if (!ch)
		done = 1;				// reached end of string, so quit
	}							// int74
	