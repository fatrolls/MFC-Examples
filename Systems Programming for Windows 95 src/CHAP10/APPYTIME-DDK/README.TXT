The AppyTime sample shows how to schedule an AppyTime event and how
to execute a function in a 16-bit DLL from inside the callback routine.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Edit the pathname in
MYVXD.C to point to the DDK help file on this companion disc (you may
need to change the drive, for example). Run "nmake -f myvxd.mak" to 
build from a command prompt, or open the AppyTime project in Microsoft 
Developer Studio and build within that environment.

To run this sample, start at an MS-DOS prompt in the project directory.
Execute the LOAD command you'll find there to dynamically load the
VxD. A short time later, WinHelp should pop up with the help entry for
_SHELL_CallDll. Unload the VxD by executing the UNLOAD command in
the project directory. (LOAD and UNLOAD are simple .COM files I typed
directly into DEBUG. You can easily adapt them for dynamically loading
and unloading your own VxD for testing by changing the name strings at
offset 130 in each file's data segment. Be sure to include the .VXD
file extension in LOAD.COM and to *not* include it in UNLOAD.COM.  The
contents of these files are shown in the corresponding .TXT files.
You can modify the .TXT files and then rebuild the .COM files by
typing the following (for example) at a command prompt:
    C:>debug LOAD.COM <LOAD.TXT
