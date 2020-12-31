// ScrollDemo.h : main header file for the SCROLLDEMO application
//

#if !defined(AFX_SCROLLDEMO_H__DCCF4E05_9735_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_SCROLLDEMO_H__DCCF4E05_9735_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoApp:
// See ScrollDemo.cpp for the implementation of this class
//

class CScrollDemoApp : public CWinApp
{
public:
	CScrollDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CScrollDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLDEMO_H__DCCF4E05_9735_11D2_8E53_006008A82731__INCLUDED_)
