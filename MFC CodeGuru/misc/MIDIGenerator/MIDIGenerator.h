// MIDIGenerator.h : main header file for the MIDIGENERATOR application
//

#if !defined(AFX_MIDIGENERATOR_H__0892C6D5_841E_11D1_A3FC_000000000000__INCLUDED_)
#define AFX_MIDIGENERATOR_H__0892C6D5_841E_11D1_A3FC_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorApp:
// See MIDIGenerator.cpp for the implementation of this class
//

class CMIDIGeneratorApp : public CWinApp
{
public:
	CMIDIGeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIDIGeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMIDIGeneratorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIGENERATOR_H__0892C6D5_841E_11D1_A3FC_000000000000__INCLUDED_)
