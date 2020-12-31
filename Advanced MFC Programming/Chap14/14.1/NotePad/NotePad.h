// NotePad.h : main header file for the NOTEPAD application
//

#if !defined(AFX_NOTEPAD_H__7B486404_43AD_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_NOTEPAD_H__7B486404_43AD_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNotePadApp:
// See NotePad.cpp for the implementation of this class
//

class CNotePadApp : public CWinApp
{
public:
	CNotePadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotePadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNotePadApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPAD_H__7B486404_43AD_11D1_9C9A_444553540000__INCLUDED_)
