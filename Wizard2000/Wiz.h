// Wiz.h : main header file for the WIZ application
//

#if !defined(AFX_WIZ_H__591B36A8_CFF1_11D3_A166_444553540000__INCLUDED_)
#define AFX_WIZ_H__591B36A8_CFF1_11D3_A166_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWizApp:
// See Wiz.cpp for the implementation of this class
//

class CWizApp : public CWinApp
{
public:
	CWizApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWizApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZ_H__591B36A8_CFF1_11D3_A166_444553540000__INCLUDED_)
