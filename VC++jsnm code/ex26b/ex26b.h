// ex26b.h : main header file for the EX26B DLL
//

#if !defined(AFX_EX26B_H__4EBFDD69_5F7D_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26B_H__4EBFDD69_5F7D_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx26bApp
// See ex26b.cpp for the implementation of this class
//

class CEx26bApp : public CWinApp
{
public:
	CEx26bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26bApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx26bApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26B_H__4EBFDD69_5F7D_11D0_848F_00400526305B__INCLUDED_)
