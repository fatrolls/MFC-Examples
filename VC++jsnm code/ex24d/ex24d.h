// ex24d.h : main header file for the EX24D application
//

#if !defined(AFX_EX24D_H__A9515B1A_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX24D_H__A9515B1A_5B85_11D0_848F_00400526305B__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx24dApp:
// See ex24d.cpp for the implementation of this class
//

class CEx24dApp : public CWinApp
{
public:
	CEx24dApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24dApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx24dApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24D_H__A9515B1A_5B85_11D0_848F_00400526305B__INCLUDED_)
