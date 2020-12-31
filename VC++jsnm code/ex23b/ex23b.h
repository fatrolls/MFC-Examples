// ex23b.h : main header file for the EX23B DLL
//

#if !defined(AFX_EX23B_H__4F329AE7_5DF1_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX23B_H__4F329AE7_5DF1_11D0_848F_00400526305B__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx23bApp
// See ex23b.cpp for the implementation of this class
//

class CEx23bApp : public CWinApp
{
public:
	CEx23bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23bApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx23bApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23B_H__4F329AE7_5DF1_11D0_848F_00400526305B__INCLUDED_)
