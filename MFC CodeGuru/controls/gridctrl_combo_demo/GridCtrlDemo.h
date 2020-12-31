// GridCtrlDemo.h : main header file for the GRIDCTRLDEMO application
//

#if !defined(AFX_GRIDCTRLDEMO_H__7E2ABF74_017B_11D2_AB4A_5C7377000000__INCLUDED_)
#define AFX_GRIDCTRLDEMO_H__7E2ABF74_017B_11D2_AB4A_5C7377000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoApp:
// See GridCtrlDemo.cpp for the implementation of this class
//

class CGridCtrlDemoApp : public CWinApp
{
public:
	CGridCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGridCtrlDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRLDEMO_H__7E2ABF74_017B_11D2_AB4A_5C7377000000__INCLUDED_)
