// PanningWindow.h : main header file for the PANNINGWINDOW application
//

#if !defined(AFX_PANNINGWINDOW_H__675D4657_02AF_11D2_B5CF_000000000000__INCLUDED_)
#define AFX_PANNINGWINDOW_H__675D4657_02AF_11D2_B5CF_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowApp:
// See PanningWindow.cpp for the implementation of this class
//

class CPanningWindowApp : public CWinApp
{
public:
	CPanningWindowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanningWindowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPanningWindowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANNINGWINDOW_H__675D4657_02AF_11D2_B5CF_000000000000__INCLUDED_)
