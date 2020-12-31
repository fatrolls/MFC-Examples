The Ring0DMA sample illustrates the methods described in the text for
performing DMA transfers in a VxD. The sample has two parts:

	MYVXD.VXD is a Plug and Play device driver with a protected-mode
	API that will read the boot sector from your drive A. There's
	also an untested subroutine (named "foo") that illustrates how
	to do a DMA transfer using low-level VDMAD service calls.

	DMATEST.EXE is an MS-DOS test program that will call the VxD
	and display a few bytes of the data read from the floppy.

Build DMATEST.EXE using MSVC 1.52. Build MYVXD.VXD using MSVC 4.0,
either using MYVXD.MAK from a command prompt or the Ring0DMA project
from within Microsoft Developer Studio. (Follow the general
directions for setting up your system in the README.TXT in the
root directory of this disc.)										  

I don't recommend that you try to run this sample. If you simply must,
follow the directions at the start of MYVXD.C to disable all the
people who are currently using your floppy drive. Also grovel around
in your BIOS to pick up the various configuration values it uses
to address your 3.5" floppy drive. You may have to modify the
parameters in MYVXD.C, and you may have to change the code to
address drive B instead of drive A. 
*********************************************************************
* Back up your hard disk before you try this, because it would be   *
* quite easy to overwrite critical data if you get the I/O commands *
* or the transfer direction wrong by accident.                      *
*********************************************************************
Then use the regular Add New Hardware wizard to install this driver 
using the WCO.INF in the sample directory.

Once MYVXD is part of your system, use the DMATEST program to read
the boot sector of a diskette. Compare what you see with the real
contents by reading the sector inside DEBUG. Then carefully restore
all the registry entries you had to clobber to get the test working
in the first place. In my experience, I needed several reboots before
Windows 95 once again recognized my floppy drive.

Please don't write or call me if you have trouble running this sample!
Like I said, I don't recommend running it!
