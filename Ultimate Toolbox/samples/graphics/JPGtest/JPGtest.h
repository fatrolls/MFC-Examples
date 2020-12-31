// JPGtest.h : main header file for the JPGTEST application
//

#if !defined(AFX_JPGTEST_H__F8562DF7_85B7_11D1_A4E1_0020359647BF__INCLUDED_)
#define AFX_JPGTEST_H__F8562DF7_85B7_11D1_A4E1_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJPGtestApp:
// See JPGtest.cpp for the implementation of this class
//

class CJPGtestApp : public CWinApp
{
public:
	CJPGtestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJPGtestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJPGtestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPGTEST_H__F8562DF7_85B7_11D1_A4E1_0020359647BF__INCLUDED_)
