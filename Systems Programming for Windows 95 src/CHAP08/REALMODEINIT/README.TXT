The RealModeInit sample shows a VxD with a real-mode initialization function.
The sample also shows how to access registry services from a real-mode
initializer, which isn't necessarily one of the things you'd really have to
do in a typical device driver.

To build this sample, prepare your system according to the general
directions in the root directory of this disc. Run "nmake -f rmreg.mak" to
build from a command prompt, or open the RealModeInit project in Microsoft 
Developer Studio and build within that environment.

To actually execute this sample and see it do something:

1. Modify the sample to contain an INT 3 instruction at the beginning of
   the VxD_REAL_INIT_SEG segment.

2. Use REGEDIT to add the registry key       
      HKLM\System\CurrentControlSet\Services\VxD\RMREG.
   Within that key, add two values:

       StaticVxD = [path]\rmreg.vxd      (a string value)
       Port = 1234                       (a binary value)

   where [path] is the path to wherever you saved RMREG.VXD.  Note that you'll need
   to put the VxD in a path other than ...\RealModeInit, because Windows 95 can't
   handle the long file name in the registry entry.  The VxD must also be on 
   a drive that is visible in real mode before Windows startup (as opposed to
   a drive that has only protected-mode drivers).

3. Restart your system under control of the WDEB386 debugger. (Follow directions in
   the Windows 95 DDK about how to use this debugger.) You'll halt on the INT 3
   instruction in the real-mode initializer, whereupon you can trace the function
   calls that read out the Port value from the registry.

