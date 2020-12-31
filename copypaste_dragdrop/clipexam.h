// clipexam.h : main header file for the CLIPEXAM application
//

#if !defined(AFX_CLIPEXAM_H__DBF687EA_868E_11D1_B99D_00A0C9763A0A__INCLUDED_)
#define AFX_CLIPEXAM_H__DBF687EA_868E_11D1_B99D_00A0C9763A0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipExamApp:
// See clipexam.cpp for the implementation of this class
//

class CClipExamApp : public CWinApp
{
public:
	CClipExamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipExamApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CClipExamApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPEXAM_H__DBF687EA_868E_11D1_B99D_00A0C9763A0A__INCLUDED_)
