// TriangleButtonDemo.h : main header file for the TRIANGLEBUTTONDEMO application
//

#if !defined(AFX_TRIANGLEBUTTONDEMO_H__11402BA9_8D8B_11D1_8F03_0060975DBA64__INCLUDED_)
#define AFX_TRIANGLEBUTTONDEMO_H__11402BA9_8D8B_11D1_8F03_0060975DBA64__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoApp:
// See TriangleButtonDemo.cpp for the implementation of this class
//

class CTriangleButtonDemoApp : public CWinApp
{
public:
	CTriangleButtonDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriangleButtonDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTriangleButtonDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIANGLEBUTTONDEMO_H__11402BA9_8D8B_11D1_8F03_0060975DBA64__INCLUDED_)
