// FileChanger.h : main header file for the FILECHANGER application
//

#if !defined(AFX_FILECHANGER_H__C3AA0CE4_F410_11D0_B8FE_444553540000__INCLUDED_)
#define AFX_FILECHANGER_H__C3AA0CE4_F410_11D0_B8FE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileChangerDemoApp:
// See FileChanger.cpp for the implementation of this class
//

class CFileChangerDemoApp : public CWinApp
{
public:
	CFileChangerDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileChangerDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileChangerDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECHANGER_H__C3AA0CE4_F410_11D0_B8FE_444553540000__INCLUDED_)
