// FileExplorer.h : main header file for the FILEEXPLORER application
//

#if !defined(AFX_FILEEXPLORER_H__10814F89_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
#define AFX_FILEEXPLORER_H__10814F89_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerApp:
// See FileExplorer.cpp for the implementation of this class
//

class CFileExplorerApp : public CWinApp
{
public:
	CFileExplorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileExplorerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFileExplorerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEEXPLORER_H__10814F89_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
