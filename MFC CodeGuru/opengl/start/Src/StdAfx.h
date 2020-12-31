//********************************************
// Stdafx.h
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created :
// Modified
//********************************************

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__06A3562B_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_STDAFX_H__06A3562B_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//////////////////////////////////////////////
//////////////////////////////////////////////
// Do not care OpenGL Headers...
//////////////////////////////////////////////
//////////////////////////////////////////////
#include <gl\gl.h>
#include <gl\glu.h>
#include <GL\glaux.h>



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__06A3562B_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
