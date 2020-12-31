The DynaLoad-VtoolsD sample illustrates the simplest possible VxD that can be
dynamically loaded by an application. The sample is in two parts: MYVXD.VXD
is the VxD and includes DEVDCL.ASM (the Declare_Virtual_Device macro and
device control procedure) and MYVXD.C. CALLTEST.EXE is a Win32 console
application that loads and calls the VxD. If all goes well, you can
execute CALLTEST from a command prompt and receive confirmation that it
loaded the VxD successfully. (You must execute CALLTEST.EXE from the same
directory in which the VxD is saved.)

To build this sample, install VtoolsD according to its directions. Issue
the command "nmake -f myvxd.mak" from a command prompt. Alternatively, open
the DynaLoad-VtoolsD project within Microsoft Developer Studio and build 
within that environment.

You will also have to build CALLTEST.EXE separately by opening the
Calltest project within Microsoft Developer Studio and building it
within that environment.
