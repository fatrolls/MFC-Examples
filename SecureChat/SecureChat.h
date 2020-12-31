// SecureChat.h : main header file for the SECURECHAT application
//

#if !defined(AFX_SECURECHAT_H__797D8826_8159_4C52_B410_8596417792F3__INCLUDED_)
#define AFX_SECURECHAT_H__797D8826_8159_4C52_B410_8596417792F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSecureChatApp:
// See SecureChat.cpp for the implementation of this class
//

class CSecureChatApp : public CWinApp
{
public:
	CSecureChatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureChatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSecureChatApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECURECHAT_H__797D8826_8159_4C52_B410_8596417792F3__INCLUDED_)
