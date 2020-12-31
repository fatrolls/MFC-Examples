// FlatBar.h : main header file for the FLATBAR application
//

#if !defined(AFX_FLATBAR_H__1E0F37E3_4020_11D1_9FB1_444553540000__INCLUDED_)
#define AFX_FLATBAR_H__1E0F37E3_4020_11D1_9FB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlatBarApp:
// See FlatBar.cpp for the implementation of this class
//

class CFlatBarApp : public CWinApp
{
public:
	CFlatBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlatBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATBAR_H__1E0F37E3_4020_11D1_9FB1_444553540000__INCLUDED_)
