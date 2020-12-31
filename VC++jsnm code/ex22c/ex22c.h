// ex22c.h : main header file for the EX22C application
//

#if !defined(AFX_EX22C_H__87F5675D_9A50_11D0_BED3_00C04FC2A0C2__INCLUDED_)
#define AFX_EX22C_H__87F5675D_9A50_11D0_BED3_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx22cApp:
// See ex22c.cpp for the implementation of this class
//

class CEx22cApp : public CWinApp
{
public:
	CEx22cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx22cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22C_H__87F5675D_9A50_11D0_BED3_00C04FC2A0C2__INCLUDED_)
