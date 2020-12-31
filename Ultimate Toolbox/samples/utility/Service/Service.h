// Service.h : main header file for the SERVICE application
//

#if !defined(AFX_SERVICE_H__E906DAA4_18DB_11D1_B900_444553540000__INCLUDED_)
#define AFX_SERVICE_H__E906DAA4_18DB_11D1_B900_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CServiceApp:
// See Service.cpp for the implementation of this class
//

class CServiceApp : public CWinApp
{
public:
	CServiceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CServiceApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICE_H__E906DAA4_18DB_11D1_B900_444553540000__INCLUDED_)
