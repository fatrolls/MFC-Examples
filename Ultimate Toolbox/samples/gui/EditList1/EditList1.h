// EditList1.h : main header file for the EDITLIST1 application
//

#if !defined(AFX_EDITLIST1_H__6A3783BC_8679_11D1_A4E2_0020359647BF__INCLUDED_)
#define AFX_EDITLIST1_H__6A3783BC_8679_11D1_A4E2_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEditList1App:
// See EditList1.cpp for the implementation of this class
//

class CEditList1App : public CWinApp
{
public:
	CEditList1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditList1App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEditList1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIST1_H__6A3783BC_8679_11D1_A4E2_0020359647BF__INCLUDED_)
