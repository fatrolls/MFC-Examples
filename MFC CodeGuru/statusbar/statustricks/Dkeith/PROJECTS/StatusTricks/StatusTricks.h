// StatusTricks.h : main header file for the STATUSTRICKS application
//

#if !defined(AFX_STATUSTRICKS_H__9823BE2E_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
#define AFX_STATUSTRICKS_H__9823BE2E_4C57_11D1_B853_0020AF6F26D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksApp:
// See StatusTricks.cpp for the implementation of this class
//

class CStatusTricksApp : public CWinApp
{
public:
	CStatusTricksApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusTricksApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStatusTricksApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSTRICKS_H__9823BE2E_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
