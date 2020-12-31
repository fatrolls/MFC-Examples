/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GRIDTREECTRLDEMO_H__A2C6C2C4_EBD7_11D3_B75D_00C04F6A7AE6__INCLUDED_)
#define AFX_GRIDTREECTRLDEMO_H__A2C6C2C4_EBD7_11D3_B75D_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridTreeCtrlDemoApp:
// See GridTreeCtrlDemo.cpp for the implementation of this class
//

class CGridTreeCtrlDemoApp : public CWinApp
{
public:
	CGridTreeCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridTreeCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGridTreeCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDTREECTRLDEMO_H__A2C6C2C4_EBD7_11D3_B75D_00C04F6A7AE6__INCLUDED_)
