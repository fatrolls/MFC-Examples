// CalculatorCtrl.h : main header file for the CALCULATORCTRL application
//

#if !defined(AFX_CALCULATORCTRL_H__F848674A_083E_41FB_B63D_7EB048943179__INCLUDED_)
#define AFX_CALCULATORCTRL_H__F848674A_083E_41FB_B63D_7EB048943179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalculatorCtrlApp:
// See CalculatorCtrl.cpp for the implementation of this class
//

class CCalculatorCtrlApp : public CWinApp
{
public:
	CCalculatorCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalculatorCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORCTRL_H__F848674A_083E_41FB_B63D_7EB048943179__INCLUDED_)
