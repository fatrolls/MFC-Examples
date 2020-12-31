// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__817B90D6_C232_11D1_B0E7_00A0C94457BF__INCLUDED_)
#define AFX_STDAFX_H__817B90D6_C232_11D1_B0E7_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#include <afxtempl.h>		// MFC support for templates (*WHY* isn't this in the default build!!!)

#ifndef TBSTYLE_TRANSPARENT
#error ***** You need a more recent version of commctrl.h to compile this project *****
#endif

#endif // !defined(AFX_STDAFX_H__817B90D6_C232_11D1_B0E7_00A0C94457BF__INCLUDED_)
