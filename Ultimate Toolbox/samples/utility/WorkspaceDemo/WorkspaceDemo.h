// WorkspaceDemo.h : main header file for the WORKSPACEDEMO application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDemoApp:
// See WorkspaceDemo.cpp for the implementation of this class
//

class CWorkspaceDemoApp : public CWinApp
{
public:
	CWorkspaceDemoApp();

	CMultiDocTemplate* m_pTextDocTemplate;
	CMultiDocTemplate* m_pLengthDocTemplate;
	CMultiDocTemplate* m_pGraphDocTemplate;

	CString GetAppDir() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWorkspaceDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolsWorkspaces();
	afx_msg void OnWindowCloseall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
