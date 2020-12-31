The ServiceHook sample illustrates how to hook a VxD service from an
assembly-language VxD. Coincidentally, it also illustrates how a Win32
application and a VxD cooperate using DeviceIoControl and _VWIN32_QueueUserApc.

MYVXD.VXD is a dynamic VxD that hooks the DOSMGR_Begin_V86_App and
DOSMGR_End_V86_App services in order to monitor the starting and stopping
of V86-mode programs. SERVTEST.EXE is a Win32 console application that
waits for APC notifications sent by the VxD in response to the hooked
service calls.

To build MYVXD.VXD, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f myvxd.mak" to
build from a command prompt, or open the ServiceHook project in Microsoft 
Developer Studio and build within that environment.

To build SERVTEST.EXE, open the SERVTEST project in Microsoft Developer
Studio and select the Build Rebuild All command.

To run the sample, start at an MS-DOS prompt in the project directory (where
the build script will have left MYVXD.VXD) and issue the command:																	   

	C:\...\ServiceHook-ASM>winrel\servtest
or
	C:\...\ServiceHook-ASM>windebug\servtest

The MS-DOS box will now pause while SERVTEST.EXE monitors start/stop events 
noted by the VxD. Open one or more other MS-DOS boxes and execute commands 
inside them to see messages from SERVTEST. Terminate SERVTEST.EXE by pressing 
Ctrl-Break with the focus in its MS-DOS session.
