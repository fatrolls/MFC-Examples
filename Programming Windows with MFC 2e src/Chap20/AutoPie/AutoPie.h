// AutoPie.h : main header file for the AUTOPIE application
//

#if !defined(AFX_AUTOPIE_H__3B5BA30B_3B72_11D2_AC82_006008A8274D__INCLUDED_)
#define AFX_AUTOPIE_H__3B5BA30B_3B72_11D2_AC82_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoPieApp:
// See AutoPie.cpp for the implementation of this class
//

class CAutoPieApp : public CWinApp
{
public:
	CAutoPieApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPieApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CAutoPieApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPIE_H__3B5BA30B_3B72_11D2_AC82_006008A8274D__INCLUDED_)
