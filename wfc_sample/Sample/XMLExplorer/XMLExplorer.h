// XMLExplorer.h : main header file for the XMLEXPLORER application
//
#if !defined(AFX_XMLEXPLORER_H__41D5252E_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
#define AFX_XMLEXPLORER_H__41D5252E_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerApplication:
// See XMLExplorer.cpp for the implementation of this class
//

class CXMLExplorerApplication : public CWinApp
{
public:
	CXMLExplorerApplication();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLExplorerApplication)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXMLExplorerApplication)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLEXPLORER_H__41D5252E_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
