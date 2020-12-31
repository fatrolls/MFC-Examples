// ex22a.h : main header file for the EX22A application
//

#if !defined(AFX_EX22A_H__2CBCCCC7_98CE_11D0_BED3_00C04FC2A0C2__INCLUDED_)
#define AFX_EX22A_H__2CBCCCC7_98CE_11D0_BED3_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx22aApp:
// See ex22a.cpp for the implementation of this class
//

class CEx22aApp : public CWinApp
{
public:
	CEx22aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx22aApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22A_H__2CBCCCC7_98CE_11D0_BED3_00C04FC2A0C2__INCLUDED_)
