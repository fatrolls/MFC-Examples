// SecureChatClient.h : main header file for the SECURECHATCLIENT application
//

#if !defined(AFX_SECURECHATCLIENT_H__FD24D203_BA2D_4412_8FA8_DD2E785DEFF3__INCLUDED_)
#define AFX_SECURECHATCLIENT_H__FD24D203_BA2D_4412_8FA8_DD2E785DEFF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientApp:
// See SecureChatClient.cpp for the implementation of this class
//

//#define _IOCPClientMode_  //define this in your project to make SecureChatIOCP act as the client. 

class CSecureChatClientApp : public CWinApp
{
private: 
	HACCEL m_haccel;
public:
	CSecureChatClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureChatClientApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSecureChatClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECURECHATCLIENT_H__FD24D203_BA2D_4412_8FA8_DD2E785DEFF3__INCLUDED_)
