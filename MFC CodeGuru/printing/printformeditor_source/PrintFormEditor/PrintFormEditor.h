// PrintFormEditor.h : main header file for the PRINTFORMEDITOR application
//

#if !defined(AFX_PRINTFORMEDITOR_H__17660EA9_0940_11D2_840B_0000B43382FE__INCLUDED_)
#define AFX_PRINTFORMEDITOR_H__17660EA9_0940_11D2_840B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// App:
// See PrintFormEditor.cpp for the implementation of this class
//
class SECExtBar : public SECCustomToolBar
{
public:
	DECLARE_DYNCREATE(SECExtBar)
	SECExtBar() { m_cyTopBorder = m_cyBottomBorder = 1; };
	virtual ~SECExtBar() {};
};

class App : public CWinApp
{
public:
	App();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTFORMEDITOR_H__17660EA9_0940_11D2_840B_0000B43382FE__INCLUDED_)
