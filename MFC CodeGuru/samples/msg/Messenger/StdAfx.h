// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3987ADCA_E657_11D1_B802_0060084C3BF4__INCLUDED_)
#define AFX_STDAFX_H__3987ADCA_E657_11D1_B802_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#ifndef _DEBUG
	#pragma check_stack(off)
#else
	#pragma check_stack(on)
#endif

// reenable warnings
#pragma warning(default: 4100)	// 'identifier' : unreferenced formal parameter
#pragma warning(default: 4700)	// local variable 'name' used without having been initialized
#pragma warning(default: 4701)  // local variable *may* be used without init
#pragma warning(default: 4702)  // unreachable code caused by optimizations


// determine number of elements in an array (not bytes)
#define _countof(array) (sizeof(array)/sizeof(array[0]))


#define COMMUNICATION_SLOT	_T("Messenger")

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3987ADCA_E657_11D1_B802_0060084C3BF4__INCLUDED_)
