// mymenu.h : main header file for the MYMENU application
//

#if !defined(AFX_MYMENU_H__3BAD4104_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
#define AFX_MYMENU_H__3BAD4104_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMymenuApp:
// See mymenu.cpp for the implementation of this class
//

class CMymenuApp : public CWinApp
{
public:
	CMymenuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMymenuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMymenuApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMENU_H__3BAD4104_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
