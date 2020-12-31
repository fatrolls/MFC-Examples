// RotoZoom.h : main header file for the ROTOZOOM application
//

#if !defined(AFX_ROTOZOOM_H__B368F865_CEF7_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_ROTOZOOM_H__B368F865_CEF7_11D1_91CA_0020AFF82585__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomApp:
// See RotoZoom.cpp for the implementation of this class
//

class CRotoZoomApp : public CWinApp
{
public:
	CRotoZoomApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotoZoomApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRotoZoomApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTOZOOM_H__B368F865_CEF7_11D1_91CA_0020AFF82585__INCLUDED_)
