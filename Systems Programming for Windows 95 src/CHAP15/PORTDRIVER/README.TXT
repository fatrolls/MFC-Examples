The PortDriver sample illustrates how to build a port driver for a
non-SCSI disk device, namely a RAM disk with a fixed amount of storage.
(The only good reason for using a RAM disk in Windows 95 is for
demonstration and for testing a local file system driver, which we'll
do in Chapter 16.)

AEP.H on the Windows 95 DDK contains a syntax error in the definition for the 
AEP_rpm_change structure.  You should copy the corrected version of AEP.H from
this subdirectory to your \DDK\INC32 directory before building this sample.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f ramdisk.mak" to
build from a command prompt, or open the PortDriver project in Microsoft Developer
Studio and build within that environment.

To test the sample, launch the Add New Hardware wizard from the Control Panel
and specify you want to add a hard disk controller. Don't allow Windows to try
to detect your device (because it doesn't really exist). Press the Have Disk
button and point to this project directory. When the installer finishes, you
should have a new disk drive visible on the desktop. Experiment with putting
files on the disk, etc. If you do this under a debugger, you'll be able to
see VFAT's structures in the memory area allocated by the driver.

Clean up by removing the disk controller through the Device Manager.