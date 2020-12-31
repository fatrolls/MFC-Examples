// ExtendedListBox.h : main header file for the EXTENDEDLISTBOX application
//

#if !defined(AFX_EXTENDEDLISTBOX_H__21FF47E5_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_)
#define AFX_EXTENDEDLISTBOX_H__21FF47E5_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxApp:
// See ExtendedListBox.cpp for the implementation of this class
//

class CExtendedListBoxApp : public CWinApp
{
public:
	CExtendedListBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedListBoxApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExtendedListBoxApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDLISTBOX_H__21FF47E5_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_)
