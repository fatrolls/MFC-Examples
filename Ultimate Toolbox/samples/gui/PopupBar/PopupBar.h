// PopupBar.h : main header file for the POPUPBAR application
//

#if !defined(AFX_POPUPBAR_H__95493CE5_F252_11D1_B475_B0D808C10000__INCLUDED_)
#define AFX_POPUPBAR_H__95493CE5_F252_11D1_B475_B0D808C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPopupBarApp:
// See PopupBar.cpp for the implementation of this class
//

class CPopupBarApp : public CWinApp
{
public:
	CPopupBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupBarApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPopupBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPBAR_H__95493CE5_F252_11D1_B475_B0D808C10000__INCLUDED_)
