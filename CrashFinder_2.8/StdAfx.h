/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#if !defined ( _STDAFX_H )
#define _STDAFX_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#define _CRTDBG_MAP_ALLOC
#define VC_EXTRALEAN

#define _WIN32_WINNT 0x501
#define WINVER 0x501
#define _WIN32_IE 0x600

#include <afxwin.h>
#include <afxext.h>
#include <AFXCVIEW.H>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

// Utilize the sexy (and safe!) string functions.
// Use the library.
#define STRSAFE_LIB
// Only use character count functions.
#define STRSAFE_NO_CB_FUNCTIONS
// Also, with the Vista SDK headers, STRSAFE.H does not compile with the
// /analyze switch (amazing, I know).
#pragma warning ( disable : 6011 )
#pragma warning ( disable : 6387 )
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#pragma warning ( default : 6011 )
#pragma warning ( disable : 6387 )

#define _USE_32BIT_TIME_T
#include <time.h>

//{{AFX_INSERT_LOCATION}}

#if _MSC_VER > 1310
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#endif // !_STDAFX_H
