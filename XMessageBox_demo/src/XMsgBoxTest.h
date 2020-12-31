// XMsgBoxTest.h : main header file for the application
//

#ifndef XMSGBOXTEST_H
#define XMSGBOXTEST_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXsgBoxTestApp:
// See XsgBoxTest.cpp for the implementation of this class
//

class CXsgBoxTestApp : public CWinApp
{
public:
	CXsgBoxTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXsgBoxTestApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXsgBoxTestApp)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XMSGBOXTEST_H
