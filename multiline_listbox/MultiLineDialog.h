// MultiLineDialog.h : main header file for the MULTILINEDIALOG application
//

#if !defined(AFX_MULTILINEDIALOG_H__2FE2DB04_86BF_11D2_AD97_0060088E1F9C__INCLUDED_)
#define AFX_MULTILINEDIALOG_H__2FE2DB04_86BF_11D2_AD97_0060088E1F9C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiLineDialogApp:
// See MultiLineDialog.cpp for the implementation of this class
//

class CMultiLineDialogApp : public CWinApp
{
public:
	CMultiLineDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiLineDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiLineDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILINEDIALOG_H__2FE2DB04_86BF_11D2_AD97_0060088E1F9C__INCLUDED_)
