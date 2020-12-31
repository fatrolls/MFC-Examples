// GDI.h : main header file for the GDI application
//

#if !defined(AFX_GDI_H__A9BED224_2386_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDI_H__A9BED224_2386_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGDIApp:
// See GDI.cpp for the implementation of this class
//

class CGDIApp : public CWinApp
{
public:
	CGDIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGDIApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDI_H__A9BED224_2386_11D1_9C9A_444553540000__INCLUDED_)
