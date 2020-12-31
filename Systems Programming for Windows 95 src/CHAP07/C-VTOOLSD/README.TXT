The C-VtoolsD sample is a simple VxD built with the VtoolsD product from Vireo
Software. I used QuickVxD to construct the project and indicated I wanted
to handle Device_Init and W32_DeviceIoControl messages within a C-framework
device driver.

To build this sample, install VtoolsD according to its directions. Issue
the command "nmake -f myvxd.mak" from a command prompt.  Alternatively, open
the C-VtoolsD project within Microsoft Developer Studio and build within
that environment.