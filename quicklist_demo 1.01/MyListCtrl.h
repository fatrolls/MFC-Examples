// MyListCtrl.h : main header file for the MYLISTCTRL application
//

#if !defined(AFX_MYLISTCTRL_H__92CE8734_DD8F_11D8_B14D_002018574596__INCLUDED_)
#define AFX_MYLISTCTRL_H__92CE8734_DD8F_11D8_B14D_002018574596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrlApp:
// See MyListCtrl.cpp for the implementation of this class
//

class CMyListCtrlApp : public CWinApp
{
public:
	CMyListCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyListCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__92CE8734_DD8F_11D8_B14D_002018574596__INCLUDED_)
