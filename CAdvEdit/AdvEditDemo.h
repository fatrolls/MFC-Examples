// AdvEditDemo.h : main header file for the ADVEDITDEMO application
//

#if !defined(AFX_ADVEDITDEMO_H__BCBD0922_AC53_4AB7_8CBF_C67A8D8E5C8A__INCLUDED_)
#define AFX_ADVEDITDEMO_H__BCBD0922_AC53_4AB7_8CBF_C67A8D8E5C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAdvEditDemoApp:
// See AdvEditDemo.cpp for the implementation of this class
//

class CAdvEditDemoApp : public CWinApp
{
public:
	CAdvEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAdvEditDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	COLORREF m_clrOutterShadow;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVEDITDEMO_H__BCBD0922_AC53_4AB7_8CBF_C67A8D8E5C8A__INCLUDED_)
