// TestGdipButton.h : main header file for the TESTGDIPBUTTON application
//

#if !defined(AFX_TESTGDIPBUTTON_H__B06162DE_4E8B_49FE_BF0F_1FECA4EEF584__INCLUDED_)
#define AFX_TESTGDIPBUTTON_H__B06162DE_4E8B_49FE_BF0F_1FECA4EEF584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestGdipButtonApp:
// See TestGdipButton.cpp for the implementation of this class
//

class CTestGdipButtonApp : public CWinApp
{
public:
	CTestGdipButtonApp();

	ULONG_PTR m_gdiplusToken;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGdipButtonApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestGdipButtonApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGDIPBUTTON_H__B06162DE_4E8B_49FE_BF0F_1FECA4EEF584__INCLUDED_)
