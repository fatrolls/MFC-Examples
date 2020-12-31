// HistoryEditDemo.h : main header file for the HISTORYEDITDEMO application
//

#if !defined(AFX_HISTORYEDITDEMO_H__63E7CA65_BC22_11D1_8EE6_94D40BC10000__INCLUDED_)
#define AFX_HISTORYEDITDEMO_H__63E7CA65_BC22_11D1_8EE6_94D40BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHistoryEditDemoApp:
// See HistoryEditDemo.cpp for the implementation of this class
//

class CHistoryEditDemoApp : public CWinApp
{
public:
	CHistoryEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHistoryEditDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYEDITDEMO_H__63E7CA65_BC22_11D1_8EE6_94D40BC10000__INCLUDED_)
