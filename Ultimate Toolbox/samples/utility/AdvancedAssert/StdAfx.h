// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__ED8354AA_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_STDAFX_H__ED8354AA_AC60_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define BETA

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
// afx.h is normally included within afxwin.h, but we do so 
// here so that most of the MFC inline asserts will 
// use our Advanced Asserts mechanism. 
#include <afx.h>             // MFC version of ASSERT
#include "OXAdvancedAssert.h"  // Redefine ASSERT our way. 

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__ED8354AA_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
