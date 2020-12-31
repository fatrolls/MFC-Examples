// ex26c.h : main header file for the EX26C application
//

#if !defined(AFX_EX26C_H__4EBFDD75_5F7D_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26C_H__4EBFDD75_5F7D_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx26cApp:
// See ex26c.cpp for the implementation of this class
//

class CEx26cApp : public CWinApp
{
public:
	CEx26cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx26cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26C_H__4EBFDD75_5F7D_11D0_848F_00400526305B__INCLUDED_)
