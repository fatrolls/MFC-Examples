// MdLessPpsh.h : main header file for the MDLESSPPSH application
//

#if !defined(AFX_MDLESSPPSH_H__D1BCD6FA_F032_11D1_A7E2_E88B6FC70000__INCLUDED_)
#define AFX_MDLESSPPSH_H__D1BCD6FA_F032_11D1_A7E2_E88B6FC70000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshApp:
// See MdLessPpsh.cpp for the implementation of this class
//

class CMdLessPpshApp : public CWinApp
{
public:
	CMdLessPpshApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdLessPpshApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMdLessPpshApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDLESSPPSH_H__D1BCD6FA_F032_11D1_A7E2_E88B6FC70000__INCLUDED_)
