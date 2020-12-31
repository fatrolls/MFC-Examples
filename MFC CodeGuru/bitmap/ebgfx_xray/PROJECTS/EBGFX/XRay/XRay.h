// XRay.h : main header file for the XRAY application
//

#if !defined(AFX_XRAY_H__13944467_CFB1_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_XRAY_H__13944467_CFB1_11D1_91CA_0020AFF82585__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXRayApp:
// See XRay.cpp for the implementation of this class
//

class CXRayApp : public CWinApp
{
public:
	CXRayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXRayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXRayApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XRAY_H__13944467_CFB1_11D1_91CA_0020AFF82585__INCLUDED_)
