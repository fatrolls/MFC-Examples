// ClipDock.h : main header file for the CLIPDOCK application
//

#if !defined(AFX_CLIPDOCK_H__89C11C7C_DA60_11D3_AC98_0050BAAB46B1__INCLUDED_)
#define AFX_CLIPDOCK_H__89C11C7C_DA60_11D3_AC98_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipDockApp:
// See ClipDock.cpp for the implementation of this class
//

class CClipDockApp : public CWinApp
{
public:
	CClipDockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipDockApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClipDockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPDOCK_H__89C11C7C_DA60_11D3_AC98_0050BAAB46B1__INCLUDED_)
