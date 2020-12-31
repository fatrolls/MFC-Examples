// proctest.h : main header file for the PROCTEST application
//

#if !defined(AFX_PROCTEST_H__3F3A24B5_FFCD_11D1_A30F_0000B481E689__INCLUDED_)
#define AFX_PROCTEST_H__3F3A24B5_FFCD_11D1_A30F_0000B481E689__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProctestApp:
// See proctest.cpp for the implementation of this class
//

class CProctestApp : public CWinApp
{
public:
	CProctestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProctestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProctestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCTEST_H__3F3A24B5_FFCD_11D1_A30F_0000B481E689__INCLUDED_)
