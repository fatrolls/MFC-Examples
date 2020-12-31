// PropDemo.h : main header file for the PROPDEMO application
//

#if !defined(AFX_PROPDEMO_H__9CE2B4A4_9067_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_PROPDEMO_H__9CE2B4A4_9067_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPropDemoApp:
// See PropDemo.cpp for the implementation of this class
//

class CPropDemoApp : public CWinApp
{
public:
	CPropDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPropDemoApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDEMO_H__9CE2B4A4_9067_11D2_8E53_006008A82731__INCLUDED_)
