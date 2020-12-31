The IRQVirtualization sample illustrates how to virtualize a hardware
interrupt and an I/O port. It consists of three pieces:

    MYVXD.VXD is a dynamic VxD that virtualizes IRQ 12 and traps
    I/O port 1234h. LOAD.COM and UNLOAD.COM are simple programs
    for loading and unloading this VxD.
    
    INTSIM.EXE is a Win16 app that you can use to generate bogus
    IRQ 12 interrupts for testing.
    
    TEST.EXE is an MS-DOS app that you can use for testing the VxD.
    
Before you build and test this sample, identify a free IRQ on your system.
The source code in this directory uses IRQ 12, which happens to be unused
on my computer but might be in use on yours. Then modify various pieces
of the VxD and test program to account for using a different IRQ:

	TEST.C currently hooks INT 74h to handle hardware interrupts from the
	bogus device. If you settle on some other IRQ in the range 8-15, change
	to INT 70h + (YourIRQ - 8). If you settle on some other IRQ in the range
	0-7, change to INT 8 + YourIRQ.
	
	TEST.C currently masks and unmasks IRQ 12 by toggling the 4 bit (mask =
	1 << 4 = 10h) in the slave PIC's Interrupt Mask Register at port address
	A1h. If your IRQ is in the range 8-15, you'll toggle bit (YourIRQ - 8),
	i.e. use a mask of (1 << (YourIRQ - 8)), at port A1h. If your IRQ is 
	in the range 0-7, you'll toggle bit YourIRQ, i.e. use a mask of
	(1 << YourIRQ), at port 21h.    
	
	TEST.C sends nonspecific EOI commands to both master and slave PICs by
	outputting 20h to port A0h and 20h. If your IRQ is in the range 8-15,
	you won't need to change this code. If your IRQ is in the range 0-7,
	omit the EOI for the slave PIC at port address A0h.
	
	MYVXD.ASM virtualizes IRQ 12 by passing VPICD_Virtualize_IRQ a
	virtual IRQ descriptor containing the number 12. Change that value to
	whatever IRQ you pick.
	
	MYVXD.ASM issues INT 5Ch in ring 0 to simulate an IRQ 12 hardware
	interrupt. Change that to 50h + YourIRQ.
	
If you're using a machine with an EISA bus, there may also be a conflict
between the bogus port number (1234h) in the sample and some actual
hardware on your computer. If so, change 1234h in both MYVXD.ASM and
TEST.C to something that's not in use.

Build TEST and INTSIM using MSVC 1.52 (the 16-bit compiler). Build MYVXD
using MSVC 4.0 (the 32-bit compiler). First follow the general instructions
in the root directory of this disc about how to set up your computer. Issue
the command "nmake -f myvxd.mak" from a command prompt, or open the
IRQVirtualization project in Microsoft Developer Studio.

The contents of the LOAD.COM and UNLOAD.COM files are shown in the
corresponding .TXT files.  You can rebuld the .COM files by typing
"debug load.com <load.txt", for example, from a command prompt.

To test, start in an MS-DOS box. Issue the LOAD command to dynamically load
the VxD. Issue the INTSIM command to launch the applet that will let you
generate bogus hardware interrupts. Finally, launch TEST. Press the Interrupt
button in INTSIM until you see a text string appear from TEST, whereupon
TEST will exit. Then exit from INTSIM and issue the UNLOAD command to unload
the VxD.

When you start TEST, it unmasks the IRQ. MYVXD's Mask_Change_Proc intercepts
that operation and records this MS-DOS VM as the owner of the IRQ.

Each time you press INTSIM's Interrupt button, INTSIM uses MYVXD's INT 2Fh/1684h
API to generate an interrupt that looks like a hardware interrupt on IRQ 12.
(Recall the discussion in Chapter 5 about how INT 5x has a DPL of 0 so that
you get a GP fault when a ring-three program issues it. A ring-zero program, 
on the other hand, generates a real INT 5x, which VPICD assumes must have come 
from hardware.) VPICD calls MYVXD's Hw_Int_Proc, which schedules the interrupt to
be handled in the owning VM. TEST receives the interrupt and reads from port
1234h. MYVXD has trapped this port, so it generates bogus data for TEST to
read.