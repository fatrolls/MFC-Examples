// Copyright (C) BrigSoft, 2003.
// http://www.brigsoft.com
// FilesDragDrop.h : main header file for the FILESDRAGDROP application
//

#if !defined(AFX_FILESDRAGDROP_H__B7BC1ABB_7455_4682_97CB_314DAA186E21__INCLUDED_)
#define AFX_FILESDRAGDROP_H__B7BC1ABB_7455_4682_97CB_314DAA186E21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropApp:
// See FilesDragDrop.cpp for the implementation of this class
//

class CFilesDragDropApp : public CWinApp
{
public:
	CFilesDragDropApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesDragDropApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFilesDragDropApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESDRAGDROP_H__B7BC1ABB_7455_4682_97CB_314DAA186E21__INCLUDED_)
