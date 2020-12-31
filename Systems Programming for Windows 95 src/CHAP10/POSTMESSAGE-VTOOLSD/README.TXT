The PostMessage sample shows how a VxD can post a window message using
a priority VM event. This technique was the only one available in
Windows 3.1 and earlier for allowing a VxD to "call" an application.
The sample is in two parts: MYVXD.VXD is a static VxD, and PMSGTEST.EXE
is a Win16 application that tests the VxD.

To build the VxD, install VtoolsD according to its directions. Issue
the command "nmake -f myvxd.mak" from a command prompt. Alternatively, open
the PostMessage project within Microsoft Developer Studio and build within
that environment.

To build PMSGTEST, open the PMSGTEST project in Microsoft Visual C++ 1.52
(the 16-bit development environment, that is).

To execute the test, add the following line to the [386enh] section of
SYSTEM.INI in your Windows directory (after substituting the pathname for
the directory where you actually built the VxD):

    device=c:\...\postme~1\myvxd.vxd

(Note that long filenames aren't usable in SYSTEM.INI because the names
are interpreted long before VFAT is up and running.) Now restart
Windows 95.

After Windows 95 restarts, launch the PMSGTEST applet. An empty window
will appear. Now open and close a couple of MS-DOS boxes and notice the
log of system control messages in the PMSGTEST window that are associated
with that activity.

Clean up by closing PMSGTEST and removing the line you added to SYSTEM.INI.
