// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D985ED2C_5BB7_4A58_8CEC_BF5FB5C03A98__INCLUDED_)
#define AFX_STDAFX_H__D985ED2C_5BB7_4A58_8CEC_BF5FB5C03A98__INCLUDED_

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

#include <afxole.h>

// STEP 4a: Tabbed MDI Page - Define OX_CUSTOMIZE_TABBEDMDI in your StdAfx.h file
#define OX_CUSTOMIZE_TABBEDMDI

// STEP 6a: Toolbars Page - Define OX_CUSTOMIZE_TOOLBARS in your StdAfx.h file
#define OX_CUSTOMIZE_TOOLBARS

// STEP 6a: Commands Page - Define OX_CUSTOMIZE_COMMANDS in your StdAfx.h file
#define OX_CUSTOMIZE_COMMANDS

// STEP 7a: Cool Controls Page - Define OX_CUSTOMIZE_COOLCONTROLS in your StdAfx.h file
#define OX_CUSTOMIZE_COOLCONTROLS

// STEP 8a: Instance Manager Page - Define OX_CUSTOMIZE_INSTANCE_MANAGER in your StdAfx.h file
#define OX_CUSTOMIZE_INSTANCE_MANAGER

// STEP 9a: IntelliMouse Support Page - Define OX_CUSTOMIZE_INTELLIMOUSE in your StdAfx.h file
#define OX_CUSTOMIZE_INTELLIMOUSE

// STEP 10a: Shortkeys Page - Define OX_CUSTOMIZE_SHORTKEYS in your StdAfx.h file
#define OX_CUSTOMIZE_SHORTKEYS

// STEP 11a: Splash Window Page - Define OX_CUSTOMIZE_SPLASHWINDOW in your StdAfx.h file
#define OX_CUSTOMIZE_SPLASHWINDOW

// STEP 12a: Background Painter Page - Define OX_CUSTOMIZE_BACKGROUND in your StdAfx.h file
#define OX_CUSTOMIZE_BACKGROUND

// STEP 13a: Tray Icon Page - Define OX_CUSTOMIZE_TRAYICON in your StdAfx.h file
#define OX_CUSTOMIZE_TRAYICON

// STEP 14a: Workspace State Page - Define OX_CUSTOMIZE_WORKSPACE_STATE in your StdAfx.h file
#define OX_CUSTOMIZE_WORKSPACE_STATE

#include "OXAdvancedAssert.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D985ED2C_5BB7_4A58_8CEC_BF5FB5C03A98__INCLUDED_)
