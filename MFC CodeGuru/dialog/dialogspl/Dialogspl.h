// Dialogspl.h : main header file for the DIALOGSPL application
//

#if !defined(AFX_DIALOGSPL_H__0B145F24_A61A_11D1_ABA0_442100C10000__INCLUDED_)
#define AFX_DIALOGSPL_H__0B145F24_A61A_11D1_ABA0_442100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogsplApp:
// See Dialogspl.cpp for the implementation of this class
//

class CDialogsplApp : public CWinApp
{
public:
	CDialogsplApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogsplApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogsplApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSPL_H__0B145F24_A61A_11D1_ABA0_442100C10000__INCLUDED_)
