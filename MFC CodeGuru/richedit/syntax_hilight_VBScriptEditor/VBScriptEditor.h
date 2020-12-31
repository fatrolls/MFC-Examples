// VBScriptEditor.h : main header file for the VBSCRIPTEDITOR application
//

#if !defined(AFX_VBSCRIPTEDITOR_H__EDDE6D49_C472_11D1_8635_00403395B157__INCLUDED_)
#define AFX_VBSCRIPTEDITOR_H__EDDE6D49_C472_11D1_8635_00403395B157__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorApp:
// See VBScriptEditor.cpp for the implementation of this class
//

class CVBScriptEditorApp : public CWinApp
{
public:
	CVBScriptEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVBScriptEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVBScriptEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VBSCRIPTEDITOR_H__EDDE6D49_C472_11D1_8635_00403395B157__INCLUDED_)
