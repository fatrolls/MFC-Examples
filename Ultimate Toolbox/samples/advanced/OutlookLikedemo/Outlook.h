// Outlook.h : main header file for the OUTLOOK application
//

#if !defined(AFX_OUTLOOK_H__DA7AA828_2C67_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_OUTLOOK_H__DA7AA828_2C67_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "OXSkins.h"

/////////////////////////////////////////////////////////////////////////////
// COutlookApp:
// See Outlook.cpp for the implementation of this class
//

class COutlookApp : public COXSkinnedApp//CWinApp
{
public:
	COutlookApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COutlookApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOK_H__DA7AA828_2C67_11D2_88E3_0080C859A484__INCLUDED_)
