// ex24e.h : main header file for the EX24E application
//

#if !defined(AFX_EX24E_H__F02781A5_6269_11D0_8490_00400526305B__INCLUDED_)
#define AFX_EX24E_H__F02781A5_6269_11D0_8490_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx24eApp:
// See Ex24e.cpp for the implementation of this class
//

class CEx24eApp : public CWinApp
{
public:
	CEx24eApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24eApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx24eApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24E_H__F02781A5_6269_11D0_8490_00400526305B__INCLUDED_)
