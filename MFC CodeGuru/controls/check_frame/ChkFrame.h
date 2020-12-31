// ChkFrame.h : main header file for the CHKFRAME application
//

#if !defined(AFX_CHKFRAME_H__F3089B4A_AA09_11D1_A435_00A024E01A10__INCLUDED_)
#define AFX_CHKFRAME_H__F3089B4A_AA09_11D1_A435_00A024E01A10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChkFrameApp:
// See ChkFrame.cpp for the implementation of this class
//

class CChkFrameApp : public CWinApp
{
public:
	CChkFrameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChkFrameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChkFrameApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHKFRAME_H__F3089B4A_AA09_11D1_A435_00A024E01A10__INCLUDED_)
