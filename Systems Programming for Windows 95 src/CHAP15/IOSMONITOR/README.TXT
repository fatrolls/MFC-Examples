The IOSMonitor sample illustrates how to write a Vendor Supplied Driver
(VSD). It has two parts:

    REQMON.VXD is the VSD. It has an API that provides interesting
    information to be reported by MONITOR.EXE.

    MONITOR.EXE is a Win32 applet that displays information about the
    current state of the IOS and about I/O requests.

Both files use MSVC 4.0. Build REQMON.VXD under the umbrella of the
IOSMonitor project and MONITOR.EXE under the Monitor project.

AEP.H on the Windows 95 DDK contains a syntax error in the definition for the 
AEP_rpm_change structure.  You should copy the corrected version of AEP.H from
this subdirectory to your \DDK\INC32 directory before building REQMON.VXD.

To test this sample, copy REQMON.VXD into the IOSUBSYS subdirectory
of your Windows system directory. Then restart Windows. Launch MONITOR
and use its totally intuitive (don't I just wish!) user interface to
learn more about the IOS. Clean up by removing REQMON.VXD from the IOSUBSYS
directory and restarting Windows once again.

Note: Some people have reported trouble running this sample with the
debug version of system VxDs installed. If it doesn't work for you the
first time, try executing your "DDKDEBUG RESTORE" command in \DDK\DEBUG.
