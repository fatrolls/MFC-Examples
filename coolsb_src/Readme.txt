Cool Scrollbar Library
Version 1.2
Copyright (c) J Brown 2001-2002
--------------------------------------------------------

The Cool Scrollbar Library provides the ability to 
customise the appearance of the standard scrollbars in 
a window. You can insert buttons, modify the appearance
of the scrollbars and resize the scrollbars.

This library is freeware, however, you may not publish
this code elsewhere or charge any money for it. This code
is supplied as-is. I make no guarantees about the suitability
of this code - use at your own risk.
	
Please read the main article text thoroughly before
compiling and executing any of these projects.

The contents of this package is split into several directories,
each of which contains a collection of source files.


coolsb                The Cool Scrollbar Library
--------------------------------------------------------
coolscroll.c        - main implementation
coolsblib.c         - the actual scrollbar API
coolscroll.h        - main include file. You should include just this file.
coolsb_internal.h   - private include file for the library
userdefs.h          - alter the #defines to control the library features
coolsb.dsp          - visual studio 6.0 project for the library


coolsb_detours        The Detours addon library (supports ALL windows)
--------------------------------------------------------
coolsb_detours.c    - main implementation
coolsb_detours.h    - main include file. You should include this file.
detours.h           - Main header for the detours library
* detours.lib *     - You must obtain this file from research.microsoft.com/sn/detours
ReadMe.txt          - Readme file for the coolsb_detours library
coolsb_detours.dsp  - 


coolsb_test           Win32 Test application for the Cool Scrollbar library
--------------------------------------------------------
coolsb_test.c       - Win32 test application which demonstrates the library
testcustdraw.c      - example of how to custom-draw the scrollbars
testlib.c           - helper routines for coolsb_test.c
script.rc           - resource file for the demo app
resource.h          - resource header file
skin01.bmp          - the main skin for the custom draw effect
bitmap1.bmp         - small bitmap for inserted buttons
coolsb_test.dsp     - demo project
coolsb_test.dsw     - demo workspace


coolsb_detourtest     Win32 coolsb_detours test
--------------------------------------------------------
detourtest.c        - main implementation
detourtest.dsp      - demo project
detourtest.dsw      - demo workspace
detourtest.rc       - resource file
resource.h          - resource header


coolsb_mfctest        MFC Test application for the Cool Scrollbar library
--------------------------------------------------------
* lots of MFC files *




Visit my web-page for other win32 software!
www.catch22.uk.net

Have fun!
James

