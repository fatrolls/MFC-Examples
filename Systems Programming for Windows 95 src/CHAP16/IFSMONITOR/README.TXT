The IFSMonitor sample shows how to use the IFSMgr_InstallFileSystemApiHook
function to hook file system API calls. MYVXD.VXD is a VxD that creates
an API hook, and IFSMonitor.EXE is a Win32 app that displays the file
system functions that the VxD detects.

To build this sample, first setup your system according to the general directions
in the root directory of this disc. Build the VxD in Microsoft Developer Studio
under the umbrella of the MONVXD project and the EXE under the IFSMonitor project.

To test, move the IFSMonitor.EXE file to the same directory as the VxD is in.
Start the IFSMonitor application from the Windows 95 Explorer and do things 
that generate file system calls, such as moving around inside the Windows 
95 Explorer. If you don't see any output, close IFSMonitor and start it a 
second time. (There's a bug in this sample that causes it not to receive 
APCs from the VxD all the time.)
														  
