// ProgressDemo.h : main header file for the PROGRESSDEMO application
//

#if !defined(AFX_PROGRESSDEMO_H__DA789504_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_PROGRESSDEMO_H__DA789504_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoApp:
// See ProgressDemo.cpp for the implementation of this class
//

class CProgressDemoApp : public CWinApp
{
public:
	CProgressDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProgressDemoApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDEMO_H__DA789504_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_)
