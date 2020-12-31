// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1FE0A7D6_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_STDAFX_H__1FE0A7D6_27E9_11D3_B75D_00203596449E__INCLUDED_

#pragma warning ( disable : 4018 4146)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "stdutfx.h"	// standard ultimate TCP macros etc

#include "IMAP4_C.h"



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1FE0A7D6_27E9_11D3_B75D_00203596449E__INCLUDED_)
