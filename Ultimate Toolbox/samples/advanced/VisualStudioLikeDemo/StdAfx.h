// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__73A06A3B_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
#define AFX_STDAFX_H__73A06A3B_E209_11D2_A7ED_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#if _MFC_VER>0x0421
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif	//	_MFC_VER>0x0421
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//////////////////////////////////////////////////////////////////////////////////////
// comment out this define if you would like to build SDI application.
// Make sure to delete the following key in the registry before running
// the application with changed architecture (from MDI to SDI, or from SDI to MDI):
//
// HKEY_CURRENT_USER\Software\Ultimate Toolbox Samples\VisualStudioLikeDemo
// 
// You have to do that as long as applications settings saved by customize pages
// are not compatible for this interfaces
#define _MDI_INTERFACE
//
//////////////////////////////////////////////////////////////////////////////////////

#define OX_CUSTOMIZE_TOOLBARS
#define OX_CUSTOMIZE_COMMANDS
#define OX_CUSTOMIZE_SHORTKEYS
#define OX_CUSTOMIZE_WORKSPACE_STATE
#define OX_CUSTOMIZE_INSTANCE_MANAGER
#define OX_CUSTOMIZE_TRAYICON
#define OX_CUSTOMIZE_SPLASHWINDOW
#ifdef _MDI_INTERFACE
#define OX_CUSTOMIZE_TABBEDMDI
#endif
#define OX_CUSTOMIZE_BACKGROUND
#define OX_CUSTOMIZE_COOLCONTROLS

#include "OXAdvancedAssert.h"

#include <afxtempl.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__73A06A3B_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
