// AdvancedAssert.h : main header file for the STATICHYPERLINK application
//

#if !defined(AFX_ADVANCEDASSERT_H__ED8354A6_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_ADVANCEDASSERT_H__ED8354A6_AC60_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAdvancedAssertApp:
// See StaticHyperLink.cpp for the implementation of this class
//

class CAdvancedAssertApp : public CWinApp
{
public:
	CAdvancedAssertApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedAssertApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAdvancedAssertApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDASSERT_H__ED8354A6_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
