The IOSCaller is a non-working sample that illustrates the text discussion
about how to create and perform an I/O request on a block device.

AEP.H on the Windows 95 DDK contains a syntax error in the definition for the 
AEP_rpm_change structure.  You should copy the corrected version of AEP.H from
this subdirectory to your \DDK\INC32 directory before building this sample.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f myvxd.mak" to
build from a command prompt, or open the IOSCaller project in Microsoft Developer
Studio and build within that environment.

Since this isn't a working VxD, you can't do anything with it once you do
build it.
