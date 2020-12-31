// RndBtnDemo.h : main header file for the RNDBTNDEMO application
//

#if !defined(AFX_RNDBTNDEMO_H__52541704_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_RNDBTNDEMO_H__52541704_59CF_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoApp:
// See RndBtnDemo.cpp for the implementation of this class
//

class CRndBtnDemoApp : public CWinApp
{
public:
	CRndBtnDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRndBtnDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRndBtnDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RNDBTNDEMO_H__52541704_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
