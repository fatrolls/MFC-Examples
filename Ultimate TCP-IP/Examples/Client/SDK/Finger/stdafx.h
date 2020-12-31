
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

#ifndef _WINSOCK_2_0_
    // WINSOCK 1.1
    // When you you want to include winsock 1,1
    // the you need to link or load winsock.lib 
    // (for 16 bit apps)  or wsock32.lib ( 32 bit apps)
    #pragma comment(lib, "wsock32.lib")
    #include <winsock.h>        //use for Winsock v1.x
    #define WINSOCKVER  MAKEWORD(1,1)
#else
    // WINSOCK 2.0
    // When you you want to include winsock 2.0
    // the you need to link or load ws2_32.lib 
    // (There is only a 32 bit version of it )
    #pragma comment(lib, "ws2_32.lib")
    #include <winsock2.h>     //use for Winsock v2.x
    #define WINSOCKVER    MAKEWORD(2,0)
#endif

#include <windows.h>

#include "stdutfx.h"	// standard ultimate TCP macros etc


#endif // __STDAFX_H__INCLUDED


