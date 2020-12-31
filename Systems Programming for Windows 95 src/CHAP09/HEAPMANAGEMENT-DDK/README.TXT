The HeapManagement sample is not a working program -- it's a compilable
version of the text illustrations converning heap allocation and
management of thread data slots. The MYVXD.C file contains some useful 
wrapper functions for _AllocateThreadDataSlot, _FreeThreadDataSlot,
Get_Sys_Thread_Handle, and Get_Next_Thread_Handle.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f myvxd.mak" to
build from a command prompt, or open the HeapManagement project in Microsoft 
Developer Studio and build within that environment.