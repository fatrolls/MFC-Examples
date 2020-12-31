// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D2552D10_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_STDAFX_H__D2552D10_7143_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>			// MFC OLE extensions

// some extended styles that come in handy occasionally.
#ifndef WS_EX_CONTEXTHELP
#define WS_EX_CONTEXTHELP       0x0400L
#endif

#ifndef WS_EX_CLIENTEDGE
#define WS_EX_CLIENTEDGE 0x0200L
#endif

#include <afxpriv.h>       		// MFC extensions for help constants

#ifdef WIN32
	#include <afxtempl.h>		// MFC extensions for Templates
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define OX_PREVIEW_GRAPHICS
#define OX_PREVIEW_BMP

// If TEXT macro not defined in WIN16, define now
#if !defined(WIN32) && !defined(TEXT)
#define TEXT(s) s
#define _T(s) s
#endif

#include "OXAdvancedAssert.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D2552D10_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
