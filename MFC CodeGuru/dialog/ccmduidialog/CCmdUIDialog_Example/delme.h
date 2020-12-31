// delme.h : main header file for the DELME application
//

#if !defined(AFX_DELME_H__7D35F4A5_7531_11D1_8FA7_000000000000__INCLUDED_)
#define AFX_DELME_H__7D35F4A5_7531_11D1_8FA7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDelmeApp:
// See delme.cpp for the implementation of this class
//

class CDelmeApp : public CWinApp
{
public:
	CDelmeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelmeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDelmeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELME_H__7D35F4A5_7531_11D1_8FA7_000000000000__INCLUDED_)
