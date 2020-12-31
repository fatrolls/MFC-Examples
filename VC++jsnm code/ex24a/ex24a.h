// ex24a.h : main header file for the EX24A application
//

#if !defined(AFX_EX24A_H__A9515AA6_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX24A_H__A9515AA6_5B85_11D0_848F_00400526305B__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx24aApp:
// See ex24a.cpp for the implementation of this class
//

class CEx24aApp : public CWinApp
{
public:
	CEx24aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx24aApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24A_H__A9515AA6_5B85_11D0_848F_00400526305B__INCLUDED_)
