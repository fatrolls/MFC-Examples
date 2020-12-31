// CVBScriptEditDlg.h : main header file for the CVBSCRIPTEDITDLG application
//

#if !defined(AFX_CVBSCRIPTEDITDLG_H__62D8DFD7_C490_11D1_8635_00403395B157__INCLUDED_)
#define AFX_CVBSCRIPTEDITDLG_H__62D8DFD7_C490_11D1_8635_00403395B157__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCVBScriptEditDlgApp:
// See CVBScriptEditDlg.cpp for the implementation of this class
//

class CCVBScriptEditDlgApp : public CWinApp
{
public:
	CCVBScriptEditDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCVBScriptEditDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCVBScriptEditDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVBSCRIPTEDITDLG_H__62D8DFD7_C490_11D1_8635_00403395B157__INCLUDED_)
