// DlgCalc.h : main header file for the DLGCALC application
//

#if !defined(AFX_DLGCALC_H__F42970C4_9047_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_DLGCALC_H__F42970C4_9047_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcApp:
// See DlgCalc.cpp for the implementation of this class
//

class CDlgCalcApp : public CWinApp
{
public:
	CDlgCalcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgCalcApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALC_H__F42970C4_9047_11D2_8E53_006008A82731__INCLUDED_)
