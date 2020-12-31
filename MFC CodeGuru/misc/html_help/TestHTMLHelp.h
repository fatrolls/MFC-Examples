// TestHTMLHelp.h : main header file for the TESTHTMLHELP application
//

#if !defined(AFX_TESTHTMLHELP_H__8CE99826_B818_11D1_B855_444553540000__INCLUDED_)
#define AFX_TESTHTMLHELP_H__8CE99826_B818_11D1_B855_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
/////////////////////////////////////////////////////////////////////////////
// CTestHTMLHelpApp:
// See TestHTMLHelp.cpp for the implementation of this class
//

class CTestHTMLHelpApp : public CWinApp, CDialogHelperHook
{
public:
	CTestHTMLHelpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestHTMLHelpApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestHTMLHelpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTHTMLHELP_H__8CE99826_B818_11D1_B855_444553540000__INCLUDED_)
