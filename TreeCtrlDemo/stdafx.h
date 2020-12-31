// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER			0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE		0x0501

#include <atlbase.h>
#include <atlstr.h>
#include <atlapp.h>

extern CAppModule _Module;

#define _WTL_NO_CSTRING

#include <atlwin.h>
#include <atlmisc.h>
#include <atlcrack.h>

#define END_MSG_MAP_EX	END_MSG_MAP
