The LPFS sample is the Low Performance File System discussed in the text. It's
intended for use in conjunction with the RAM disk driver that's part of the
PortDriver sample for Chapter 15.

AEP.H on the Windows 95 DDK contains a syntax error in the definition for the 
AEP_rpm_change structure.  You should copy the corrected version of AEP.H from
this subdirectory to your \DDK\INC32 directory before building this sample.

To build this sample, first prepare your system according to the general directions
in the root directory of this disc. Then open the LPFS project within Microsoft
Developer Studio.

To test, build and install the RAM disk driver as described in the README.TXT for
the PortDriver sample in Chapter 15. Add a "device=" line to SYSTEM.INI to load
LPFS.VXD from this sample directory. Then restart your system. Operations on the
RAM disk will use LPFS, which means you can read, write, and rename the one file
you see in the root directory. Clean up by deleting the RAM disk and removing the
"device=" statement from SYSTEM.INI.
