// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F02781A7_6269_11D0_8490_00400526305B__INCLUDED_)
#define AFX_STDAFX_H__F02781A7_6269_11D0_8490_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdisp.h>

#import "..\ex24a\debug\ex24a.tlb" rename_namespace("BankDriv")
using namespace BankDriv;

#import "..\ex24b\debug\ex24b.tlb" rename_namespace("Ex24bDriv")
using namespace Ex24bDriv;

#import "..\ex24c\debug\ex24c.tlb" rename_namespace("ClockDriv")
using namespace ClockDriv;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F02781A7_6269_11D0_8490_00400526305B__INCLUDED_)
