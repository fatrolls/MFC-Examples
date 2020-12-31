// ex20b.h : main header file for the EX20B application
//

#if !defined(AFX_EX20B_H__3985D2CD_8ED1_11D0_8FE4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX20B_H__3985D2CD_8ED1_11D0_8FE4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx20bApp:
// See ex20b.cpp for the implementation of this class
//

class CEx20bApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pTemplateString;
	CMultiDocTemplate* m_pTemplateHex;
	CEx20bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx20bApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx20bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX20B_H__3985D2CD_8ED1_11D0_8FE4_00C04FC2A0C2__INCLUDED_)
