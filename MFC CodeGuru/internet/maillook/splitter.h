// splitter.h : main header file for the SPLITTER application
//

#if !defined(AFX_SPLITTER_H__D5D5E418_F1FA_11D1_9447_BC2A94000000__INCLUDED_)
#define AFX_SPLITTER_H__D5D5E418_F1FA_11D1_9447_BC2A94000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp:
// See splitter.cpp for the implementation of this class
//

class CSplitterApp : public CWinApp
{
public:
	CSplitterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSplitterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTER_H__D5D5E418_F1FA_11D1_9447_BC2A94000000__INCLUDED_)
