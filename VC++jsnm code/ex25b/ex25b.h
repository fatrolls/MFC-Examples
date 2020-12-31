// ex25b.h : main header file for the EX25B application
//

#if !defined(AFX_EX25B_H__9C8ABB55_98B3_11D0_85CF_9992596EDB70__INCLUDED_)
#define AFX_EX25B_H__9C8ABB55_98B3_11D0_85CF_9992596EDB70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx25bApp:
// See ex25b.cpp for the implementation of this class
//

class CEx25bApp : public CWinApp
{
public:
	CEx25bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx25bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25B_H__9C8ABB55_98B3_11D0_85CF_9992596EDB70__INCLUDED_)
