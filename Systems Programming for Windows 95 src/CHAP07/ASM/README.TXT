The Asm sample is almost the simplest possible skeleton VxD that can
be written in assembly language. It contains a Declare_Virtual_Device
macro call, a Device Control Procedure, and a handler for the
Device_Init system control message. (The only simpler VxD wouldn't 
even handle Device_Init.)

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f 
myvxd.mak" to build the VxD from a command prompt, or open the Asm 
project in Microsoft Developer Studio and build within that 
environment.