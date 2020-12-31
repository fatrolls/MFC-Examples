// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7040DB86_9039_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_STDAFX_H__7040DB86_9039_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

typedef struct tagRECTPROP {
    int nWidth;
	int nHeight;
	int nUnits;
} RECTPROP;

#define WM_USER_APPLY				WM_USER+0x100
#define WM_USER_DIALOG_DESTROYED	WM_USER+0x101

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__7040DB86_9039_11D2_8E53_006008A82731__INCLUDED_)
