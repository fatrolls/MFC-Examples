// DragEdit.h : main header file for the DRAGEDIT application
//

#if !defined(AFX_DRAGEDIT_H__871E3CC6_6359_11D1_8251_444553540000__INCLUDED_)
#define AFX_DRAGEDIT_H__871E3CC6_6359_11D1_8251_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDragEditApp:
// See DragEdit.cpp for the implementation of this class
//

class CDragEditApp : public CWinApp
{
public:
	CDragEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDragEditApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGEDIT_H__871E3CC6_6359_11D1_8251_444553540000__INCLUDED_)
