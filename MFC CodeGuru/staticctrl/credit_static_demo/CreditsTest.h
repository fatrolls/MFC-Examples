// CreditsTest.h : main header file for the CREDITSTEST application
//

#if !defined(AFX_CREDITSTEST_H__E110A1A5_E319_11D1_9E4E_00A0245800CF__INCLUDED_)
#define AFX_CREDITSTEST_H__E110A1A5_E319_11D1_9E4E_00A0245800CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestApp:
// See CreditsTest.cpp for the implementation of this class
//

class CCreditsTestApp : public CWinApp
{
public:
	CCreditsTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditsTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCreditsTestApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITSTEST_H__E110A1A5_E319_11D1_9E4E_00A0245800CF__INCLUDED_)
