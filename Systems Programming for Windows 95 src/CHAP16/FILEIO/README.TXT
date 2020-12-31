The FileIO sample illustrates a few simple file system calls from 
ring zero. MYVXD.VXD is a dynamic VxD that will create a file called
"HelloWorld.txt" with predictable contents. CALLTEST.EXE is a test
program that will load and unload the VxD.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Open the FileIO project
in Microsoft Developer Studio and modify the pathname in MYVXD's call
to R0_OpenCreateFile to be appropriate for your system. Build the VxD
and then build the CALLTEST project as well.

To test, run the CALLTEST command from an MS-DOS command prompt with the
current directory set to where you've built MYVXD.VXD. A file named
HelloWorld.txt should be left behind.