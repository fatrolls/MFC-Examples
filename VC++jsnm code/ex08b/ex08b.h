// ex08b.h : main header file for the EX08B application
//

#if !defined(AFX_EX08B_H__13D86A39_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_)
#define AFX_EX08B_H__13D86A39_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx08bApp:
// See ex08b.cpp for the implementation of this class
//

class CEx08bApp : public CWinApp
{
public:
	CEx08bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx08bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX08B_H__13D86A39_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_)
