// DlgMgrTest.h : main header file for the DLGMGRTEST application
//

#if !defined(AFX_DLGMGRTEST_H__6FFAC336_E064_11D1_801C_4854E82A1622__INCLUDED_)
#define AFX_DLGMGRTEST_H__6FFAC336_E064_11D1_801C_4854E82A1622__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrTestApp:
// See DlgMgrTest.cpp for the implementation of this class
//

class CDlgMgrTestApp : public CWinApp
{
public:
	CDlgMgrTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMgrTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgMgrTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMGRTEST_H__6FFAC336_E064_11D1_801C_4854E82A1622__INCLUDED_)
