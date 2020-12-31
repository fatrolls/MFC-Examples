// CBCPTest.h : main header file for the CBCPTEST application
//

#if !defined(AFX_CBCPTEST_H__D0CC2D48_DB55_11D1_ADB6_004095247E7D__INCLUDED_)
#define AFX_CBCPTEST_H__D0CC2D48_DB55_11D1_ADB6_004095247E7D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCBCPTestApp:
// See CBCPTest.cpp for the implementation of this class
//

class CCBCPTestApp : public CWinApp
{
public:
	CCBCPTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBCPTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCBCPTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBCPTEST_H__D0CC2D48_DB55_11D1_ADB6_004095247E7D__INCLUDED_)
