// VirtualList.h : main header file for the VIRTUALLIST application
//

#if !defined(AFX_VIRTUALLIST_H__A1E7069A_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
#define AFX_VIRTUALLIST_H__A1E7069A_5F36_11D1_959E_D1A30ED05A05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVirtualListApp:
// See VirtualList.cpp for the implementation of this class
//

class CVirtualListApp : public CWinApp
{
public:
	CVirtualListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVirtualListApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRTUALLIST_H__A1E7069A_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
