// Layout.h : main header file for the LAYOUT application
//

#if !defined(AFX_LAYOUT_H__7D955F28_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
#define AFX_LAYOUT_H__7D955F28_0A9F_11D2_88B8_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLayoutApp:
// See Layout.cpp for the implementation of this class
//

class CLayoutApp : public CWinApp
{
public:
	CLayoutApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayoutApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLayoutApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYOUT_H__7D955F28_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
