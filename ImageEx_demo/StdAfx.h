// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C5677A13_1C46_4D0D_9C24_3A86A61AEBA0__INCLUDED_)
#define AFX_STDAFX_H__C5677A13_1C46_4D0D_9C24_3A86A61AEBA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


// SUPPORT FOR THE GDI+ SUBSYSTEM
#pragma comment(lib,"gdiplus.lib")
#include <gdiplus.h>
using namespace Gdiplus;

#include "ImageEx.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C5677A13_1C46_4D0D_9C24_3A86A61AEBA0__INCLUDED_)
