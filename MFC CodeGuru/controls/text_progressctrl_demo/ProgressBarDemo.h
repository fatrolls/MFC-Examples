// ProgressBarDemo.h : main header file for the PROGRESSBARDEMO application
//

#if !defined(AFX_PROGRESSBARDEMO_H__4C78DBB4_EFB6_11D1_AB14_203E25000000__INCLUDED_)
#define AFX_PROGRESSBARDEMO_H__4C78DBB4_EFB6_11D1_AB14_203E25000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgressBarDemoApp:
// See ProgressBarDemo.cpp for the implementation of this class
//

class CProgressBarDemoApp : public CWinApp
{
public:
	CProgressBarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressBarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProgressBarDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSBARDEMO_H__4C78DBB4_EFB6_11D1_AB14_203E25000000__INCLUDED_)
