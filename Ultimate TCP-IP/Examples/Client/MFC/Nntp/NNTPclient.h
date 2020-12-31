// NNTPclient.h : main header file for the NNTPCLIENT application
//

#if !defined(AFX_NNTPCLIENT_H__03D2D76F_1763_11D3_87EE_0080C86498A0__INCLUDED_)
#define AFX_NNTPCLIENT_H__03D2D76F_1763_11D3_87EE_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNNTPclientApp:
// See NNTPclient.cpp for the implementation of this class
//

class CNNTPclientApp : public CWinApp
{
public:
	CNNTPclientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNNTPclientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNNTPclientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NNTPCLIENT_H__03D2D76F_1763_11D3_87EE_0080C86498A0__INCLUDED_)
