// datapkproj.h : main header file for the DATAPKPROJ application
//

#if !defined(AFX_DATAPKPROJ_H__D7484F47_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
#define AFX_DATAPKPROJ_H__D7484F47_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojApp:
// See datapkproj.cpp for the implementation of this class
//

class CDatapkprojApp : public CWinApp
{
public:
	CDatapkprojApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatapkprojApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDatapkprojApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPKPROJ_H__D7484F47_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
