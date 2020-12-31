// Spider.h : main header file for the SPIDER application
//

#if !defined(AFX_SPIDER_H__26AC1024_E049_11D1_8F58_B6D09489096E__INCLUDED_)
#define AFX_SPIDER_H__26AC1024_E049_11D1_8F58_B6D09489096E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpiderApp:
// See Spider.cpp for the implementation of this class
//

class CSpiderApp : public CWinApp
{
public:
	CSpiderApp();
	CString   m_HomeDir;
	int m_FtpStartUpLoad;
	void WriteProfile();
	void ReadProfile();
	void ShowURL(LPCTSTR lpFileName,CString& text) ;

private:	
	virtual int ExitInstance();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpiderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpiderApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPIDER_H__26AC1024_E049_11D1_8F58_B6D09489096E__INCLUDED_)
