// IOCPClient.h : main header file for the IOCPCLIENT application
//

#if !defined(AFX_IOCPCLIENT_H__93DE8897_84C2_4593_B970_10A05C81DC10__INCLUDED_)
#define AFX_IOCPCLIENT_H__93DE8897_84C2_4593_B970_10A05C81DC10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIOCPClientApp:
// See IOCPClient.cpp for the implementation of this class
//

class CIOCPClientApp : public CWinApp
{
public:
	CIOCPClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOCPClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIOCPClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCPCLIENT_H__93DE8897_84C2_4593_B970_10A05C81DC10__INCLUDED_)
