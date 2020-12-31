// DlgDemo2.h : main header file for the DLGDEMO2 application
//

#if !defined(AFX_DLGDEMO2_H__7040DB84_9039_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_DLGDEMO2_H__7040DB84_9039_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgDemo2App:
// See DlgDemo2.cpp for the implementation of this class
//

class CDlgDemo2App : public CWinApp
{
public:
	CDlgDemo2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDemo2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CDlgDemo2App)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEMO2_H__7040DB84_9039_11D2_8E53_006008A82731__INCLUDED_)
