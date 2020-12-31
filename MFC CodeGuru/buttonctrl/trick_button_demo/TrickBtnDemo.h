// TrickBtnDemo.h : main header file for the TRICKBTNDEMO application
//

#if !defined(AFX_TRICKBTNDEMO_H__B6A0FBA3_FDF4_11D1_AB40_8C80B0000000__INCLUDED_)
#define AFX_TRICKBTNDEMO_H__B6A0FBA3_FDF4_11D1_AB40_8C80B0000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrickBtnDemoApp:
// See TrickBtnDemo.cpp for the implementation of this class
//

class CTrickBtnDemoApp : public CWinApp
{
public:
	CTrickBtnDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrickBtnDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrickBtnDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRICKBTNDEMO_H__B6A0FBA3_FDF4_11D1_AB40_8C80B0000000__INCLUDED_)
