// Notes.h : main header file for the NOTES application
//

#if !defined(AFX_NOTES_H__80E35AFA_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_)
#define AFX_NOTES_H__80E35AFA_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNotesApp:
// See Notes.cpp for the implementation of this class
//

class CNotesApp : public CWinApp
{
public:
	CNotesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNotesApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTES_H__80E35AFA_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_)
