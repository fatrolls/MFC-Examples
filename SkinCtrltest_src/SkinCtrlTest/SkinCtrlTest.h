// SkinCtrlTest.h : main header file for the SKINCTRLTEST application
//

#if !defined(AFX_SKINCTRLTEST_H__70BCA9BE_E98E_45E0_9B62_2506720AA495__INCLUDED_)
#define AFX_SKINCTRLTEST_H__70BCA9BE_E98E_45E0_9B62_2506720AA495__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkinCtrlTestApp:
// See SkinCtrlTest.cpp for the implementation of this class
//

class CSkinCtrlTestApp : public CWinApp
{
public:
	CSkinCtrlTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinCtrlTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSkinCtrlTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINCTRLTEST_H__70BCA9BE_E98E_45E0_9B62_2506720AA495__INCLUDED_)
