C-DDK is nearly the simplest possible VxD written in C. It consists of
two files: DEVDCL.ASM contains the required Declare_Virtual_Device macro
and the device control procedure. MYVXD.C contains a handler for the
Device_Init system control message. (The only simpler VxD wouldn't even handle Device_Init.)

Note that this sample uses the "sCall" option in the Control_Dispatch macro
for Device_Init and declares OnDeviceInit with the "__stdcall" option. Most
of the other samples on this disc use the __cdecl calling convention for
control message handlers. The choice of calling convention is entirely up
to you.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f myvxd.mak" to
build from a command prompt, or open the C-DDK project in Microsoft Developer
Studio and build within that environment.