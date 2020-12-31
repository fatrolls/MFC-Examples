// YMTest.h : main header file for the YMTEST application
//

#if !defined(AFX_YMTEST_H__12C342E7_008C_11D2_AECD_0004AC31E75C__INCLUDED_)
#define AFX_YMTEST_H__12C342E7_008C_11D2_AECD_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CYMTestApp:
// See YMTest.cpp for the implementation of this class
//

class CYMTestApp : public CWinApp
{
public:
	CYMTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYMTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CYMTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YMTEST_H__12C342E7_008C_11D2_AECD_0004AC31E75C__INCLUDED_)
