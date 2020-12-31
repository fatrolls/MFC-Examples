// ActiveDesktop.h : main header file for the ACTIVEDESKTOP application
//

#if !defined(AFX_ACTIVEDESKTOP_H__CD16C203_EDE3_11D3_ACB6_0050BAAB46B1__INCLUDED_)
#define AFX_ACTIVEDESKTOP_H__CD16C203_EDE3_11D3_ACB6_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopApp:
// See ActiveDesktop.cpp for the implementation of this class
//

class CActiveDesktopApp : public CWinApp
{
public:
	CActiveDesktopApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveDesktopApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CActiveDesktopApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEDESKTOP_H__CD16C203_EDE3_11D3_ACB6_0050BAAB46B1__INCLUDED_)
