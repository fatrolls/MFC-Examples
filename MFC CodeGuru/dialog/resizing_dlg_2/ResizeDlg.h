// ResizeDlg.h : main header file for the RESIZEDLG application
//

#if !defined(AFX_RESIZEDLG_H__74620F66_C16B_11D1_A051_0000B435810F__INCLUDED_)
#define AFX_RESIZEDLG_H__74620F66_C16B_11D1_A051_0000B435810F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgApp:
// See ResizeDlg.cpp for the implementation of this class
//

class CResizeDlgApp : public CWinApp
{
public:
	CResizeDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CResizeDlgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEDLG_H__74620F66_C16B_11D1_A051_0000B435810F__INCLUDED_)
