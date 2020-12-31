The PortVirtualization sample illustrates how to virtualize an I/O
device by "trapping" port I/O.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f myvxd.mak" to
build from a command prompt, or open the PortVirtualization project in 
Microsoft Developer Studio and build within that environment.

The contents of the LOAD.COM, TESTPORT.COM, and UNLOAD.COM files are 
shown in the corresponding .TXT files.  You can rebuld the .COM files 
by typing "debug load.com <load.txt", for example, from a command prompt.

To test, start at an MS-DOS prompt. Issue the LOAD command to load
the VxD. Then issue the TESTPORT command one or more times and notice
the text string that comes back. Start another MS-DOS session and try
to issue TESTPORT commands from there and notice the contention dialog
that appears. (If the TESTPORT command causes a GPF, the LOAD command 
was unable to load MYVXD.VXD.)  Clean up by issuing an UNLOAD command 
to unload the VxD.
