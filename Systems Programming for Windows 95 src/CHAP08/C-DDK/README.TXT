The C-DDK sample illustrates how to construct a simple C-language VxD that
handles the three system control messages used to initialize static drivers:
    Sys_Critical_Init
    Device_Init
    Init_Complete

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f myvxd.mak" to
build from a command prompt, or open the C-DDK project in Microsoft 
Developer Studio and build within that environment.
