// BmpClient.h : main header file for the BMPCLIENT application
//

#if !defined(AFX_BMPCLIENT_H__BAF706B5_89CB_11D1_A17A_000000000000__INCLUDED_)
#define AFX_BMPCLIENT_H__BAF706B5_89CB_11D1_A17A_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpClient:
// See BmpClient.cpp for the implementation of this class
//

class CBmpClient : public CWinApp
{
public:
	CBmpClient();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpClient)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBmpClient)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPCLIENT_H__BAF706B5_89CB_11D1_A17A_000000000000__INCLUDED_)
