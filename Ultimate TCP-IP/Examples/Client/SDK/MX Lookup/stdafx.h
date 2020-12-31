
#ifndef __STDAFX_H__INCLUDED
#define __STDAFX_H__INCLUDED

// This file is included in all .CPP implementation files to
// maintain compatibility with MFC and pre-compiled headers.
// If you're building an MFC application you will not need 
// this file as the Application AppWizard will automatically
// generate one for you. 
//
// Also note that ".\" -- the current working directory -- has
// been added to the project's "Additional include directories" list
// (found in the project build settings). This is needed since the
// files in the Ultimate TCP/IP v4.2 source directory include the
// "stdafx.h" header file which does not exist in the source
// directory. Adding ".\" to the list of additional include
// directories tells the compiler to search the project directory
// for "stdafx.h" (in addition to the other standard include
// directories)

#include <winsock2.h>
#include <windows.h>

// Tell the linker to link in the winsock2 library
#pragma comment(lib, "ws2_32.lib")

#include "stdutfx.h"	// standard ultimate TCP macros etc


#endif // __STDAFX_H__INCLUDED


