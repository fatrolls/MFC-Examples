// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6D8D50B9_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_)
#define AFX_STDAFX_H__6D8D50B9_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _WINSOCKAPI_

#include <winsock2.h>

#include <afxsock.h>		// MFC socket extensions

#include "stdutfx.h"	// standard ultimate TCP macros etc


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6D8D50B9_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_)
