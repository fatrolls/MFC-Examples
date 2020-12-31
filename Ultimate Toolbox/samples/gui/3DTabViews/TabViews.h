// TabViews.h : main header file for the TABVIEWS application
//

#if !defined(AFX_TABVIEWS_H__14C16328_675D_11D2_A753_525400DAF3CE__INCLUDED_)
#define AFX_TABVIEWS_H__14C16328_675D_11D2_A753_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define _MDI_INTERFACE

#ifdef _MDI_INTERFACE
#define CMainFrameWindow CMDIFrameWnd
#else
#define CMainFrameWindow CFrameWnd
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabViewsApp:
// See TabViews.cpp for the implementation of this class
//

class CTabViewsApp : public CWinApp
{
public:
	CTabViewsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTabViewsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEWS_H__14C16328_675D_11D2_A753_525400DAF3CE__INCLUDED_)
