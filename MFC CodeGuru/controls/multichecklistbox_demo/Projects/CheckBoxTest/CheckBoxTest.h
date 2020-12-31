// CheckBoxTest.h : main header file for the CHECKBOXTEST application
//

#if !defined(AFX_CHECKBOXTEST_H__D4D62F85_E758_11D1_AE66_A0B807C10000__INCLUDED_)
#define AFX_CHECKBOXTEST_H__D4D62F85_E758_11D1_AE66_A0B807C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxTestApp:
// See CheckBoxTest.cpp for the implementation of this class
//

class CCheckBoxTestApp : public CWinApp
{
public:
	CCheckBoxTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBoxTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCheckBoxTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBOXTEST_H__D4D62F85_E758_11D1_AE66_A0B807C10000__INCLUDED_)
