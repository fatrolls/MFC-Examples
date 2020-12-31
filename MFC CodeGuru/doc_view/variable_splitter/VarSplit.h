// VarSplit.h : main header file for the VARSPLIT application
//

#if !defined(AFX_VARSPLIT_H__233727C5_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
#define AFX_VARSPLIT_H__233727C5_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVarSplitApp:
// See VarSplit.cpp for the implementation of this class
//

class CVarSplitApp : public CWinApp
{
public:
	CVarSplitApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVarSplitApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVarSplitApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARSPLIT_H__233727C5_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
