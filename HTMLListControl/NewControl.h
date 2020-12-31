// NewControl.h : main header file for the NEWCONTROL application
//

#if !defined(AFX_NEWCONTROL_H__BF007F63_5BF0_433A_B8F0_F4F76476287A__INCLUDED_)
#define AFX_NEWCONTROL_H__BF007F63_5BF0_433A_B8F0_F4F76476287A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNewControlApp:
// See NewControl.cpp for the implementation of this class
//

class CNewControlApp : public CWinApp
{
public:
	CNewControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNewControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCONTROL_H__BF007F63_5BF0_433A_B8F0_F4F76476287A__INCLUDED_)
