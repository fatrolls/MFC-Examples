// CustToolBarTest.h : main header file for the CUSTTOOLBARTEST application
//

#if !defined(AFX_CUSTTOOLBARTEST_H__761D39DC_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_CUSTTOOLBARTEST_H__761D39DC_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestApp:
// See CustToolBarTest.cpp for the implementation of this class
//

class CCustToolBarTestApp : public CWinApp
{
public:
	CCustToolBarTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustToolBarTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCustToolBarTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTTOOLBARTEST_H__761D39DC_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
