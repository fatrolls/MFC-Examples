// FastTest.h : main header file for the FASTTEST application
//

#if !defined(AFX_FASTTEST_H__7137DC8F_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
#define AFX_FASTTEST_H__7137DC8F_B77C_11D1_AE72_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFastTestApp:
// See FastTest.cpp for the implementation of this class
//

class CFastTestApp : public CWinApp
{
public:
	CFastTestApp();
    CDatabase   m_DB;
	CMultiDocTemplate* m_pFastTemplate;
   	CMultiDocTemplate* m_pSlowTemplate;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFastTestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileFastview();
	afx_msg void OnFileSlowview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CFastTestApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTTEST_H__7137DC8F_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
