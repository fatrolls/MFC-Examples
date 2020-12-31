// SDITest.h : main header file for the SDITEST application
//

#if !defined(AFX_SDITEST_H__8765579C_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
#define AFX_SDITEST_H__8765579C_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDITestApp:
// See SDITest.cpp for the implementation of this class
//

class CSDITestApp : public CWinApp
{
public:
	CSDITestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDITestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSDITestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDITEST_H__8765579C_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
