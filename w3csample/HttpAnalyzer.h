// HttpAnalyzer.h : main header file for the HTTPANALYZER application
//

#if !defined(AFX_HTTPANALYZER_H__D78F7BCE_11A3_4F2C_9EDA_0437F73CE3A3__INCLUDED_)
#define AFX_HTTPANALYZER_H__D78F7BCE_11A3_4F2C_9EDA_0437F73CE3A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerApp:
// See HttpAnalyzer.cpp for the implementation of this class
//

class CHttpAnalyzerApp : public CWinApp
{
public:
	CHttpAnalyzerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpAnalyzerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHttpAnalyzerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPANALYZER_H__D78F7BCE_11A3_4F2C_9EDA_0437F73CE3A3__INCLUDED_)
