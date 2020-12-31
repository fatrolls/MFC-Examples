// IMAPClient.h : main header file for the IMAPCLIENT application
//

#if !defined(AFX_IMAPCLIENT_H__1FE0A7D4_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_IMAPCLIENT_H__1FE0A7D4_27E9_11D3_B75D_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIMAPClientApp:
// See IMAPClient.cpp for the implementation of this class
//

#pragma warning ( disable : 4511 4512 ) // VC6 level 4 - copy ctor & op=

class CIMAPClientApp : public CWinApp
{
public:
	CIMAPClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMAPClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CIMAPClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAPCLIENT_H__1FE0A7D4_27E9_11D3_B75D_00203596449E__INCLUDED_)
