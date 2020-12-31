The SchoolBus sample illustrates the major aspects of Plug and Play
VxD programming, including:

	A bus enumerator for the School Bus (SCHOOL.VXD)
	A resource arbitrator for telepathic input channels (SCHOOL.VXD)
	A device driver for telepathic devices (TELEPATH.VXD)
	A property page provider for Device Manager (SCHOOLUI.DLL)
	An INF file for installing the school bus (WCO.INF)

The property page provider, SCHOOLUI.DLL, is a 16-bit DLL built with
MSVC version 1.52. Open the SCHOOLUI project to examine it further.
You'll need to point your Include Files Path (use the Options Directories
command) to the \DDK\INC16 directory as well as to the usual MSVC 
directories to build this DLL.

To build the two VxDs, prepare your system according to the general
directions in the root directory of this disc. You'll have to switch
the order of the DDK\BIN and MSDEV\BIN directories for this sample,
however, so that the DDK\BIN directory is first. Run "nmake -f school.mak" 
to build from a command prompt, or open the SchoolBus project in Microsoft 
Developer Studio and build within that environment.

To test the sample, launch the Add New Hardware applet in the Control Panel and
indicate you want to install a new system device (but don't let Windows 95
try to detect the new hardware -- it's a figment of our imaginations). Click
Have Disk and enter the pathname to this sample directory. Indicate that you
want to add a School Bus to the system. After the device installer is done,
you can use the Device Manager (reached from the System applet in the Control
Panel) to peruse your new School Bus and Telepathic Device.

Cleanup by removing the School Bus via Device Manager. Delete SCHOOL.VXD,
TELEPATH.VXD, and SCHOOLUI.DLL from your system directory by hand. You'll
also have an OEMxx.INF file in the INF subdirectory of your Windows directory
that's a duplicate of the WCO.INF in the sample directory. Identify this file
positively (by looking inside it!) and delete it as well.  (You may end up
with several copies of the .INF file.  You should delete all of them.)
								