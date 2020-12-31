// Avidemo.h : main header file for the AVIDEMO application
//

#if !defined(AFX_AVIDEMO_H__0E6D65A4_A650_11D1_ABA0_443100C10000__INCLUDED_)
#define AFX_AVIDEMO_H__0E6D65A4_A650_11D1_ABA0_443100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAvidemoApp:
// See Avidemo.cpp for the implementation of this class
//

class CAvidemoApp : public CWinApp
{
public:
	CAvidemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAvidemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAvidemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIDEMO_H__0E6D65A4_A650_11D1_ABA0_443100C10000__INCLUDED_)
