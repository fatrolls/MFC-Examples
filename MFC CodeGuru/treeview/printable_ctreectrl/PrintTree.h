// PrintTree.h : main header file for the PRINTTREE application
//

#if !defined(AFX_PRINTTREE_H__3FF28846_DDEA_11D1_80B0_0000F87772A5__INCLUDED_)
#define AFX_PRINTTREE_H__3FF28846_DDEA_11D1_80B0_0000F87772A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrintTreeApp:
// See PrintTree.cpp for the implementation of this class
//

class CPrintTreeApp : public CWinApp
{
public:
	CPrintTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPrintTreeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTTREE_H__3FF28846_DDEA_11D1_80B0_0000F87772A5__INCLUDED_)
