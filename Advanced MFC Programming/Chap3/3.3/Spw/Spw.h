// Spw.h : main header file for the SPW application
//

#if !defined(AFX_SPW_H__D3F202D2_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPW_H__D3F202D2_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpwApp:
// See Spw.cpp for the implementation of this class
//

class CSpwApp : public CWinApp
{
public:
	CSpwApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpwApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpwApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPW_H__D3F202D2_FC3A_11D0_9C9A_444553540000__INCLUDED_)
