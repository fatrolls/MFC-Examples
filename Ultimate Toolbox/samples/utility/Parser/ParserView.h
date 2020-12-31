// ParserView.h : main header file for the PARSERVIEW application
//

#if !defined(AFX_PARSERVIEW_H__8E0F0926_0728_11D3_A9F8_2EA565000000__INCLUDED_)
#define AFX_PARSERVIEW_H__8E0F0926_0728_11D3_A9F8_2EA565000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CParserViewApp:
// See ParserView.cpp for the implementation of this class
//

class CParserViewApp : public CWinApp
{
public:
	CParserViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParserViewApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CParserViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSERVIEW_H__8E0F0926_0728_11D3_A9F8_2EA565000000__INCLUDED_)
