// OptionTree.h : main header file for the OPTIONTREE application
//

#if !defined(AFX_OPTIONTREE_H__1D5197E5_DB32_11D2_B476_00E0291A4FD3__INCLUDED_)
#define AFX_OPTIONTREE_H__1D5197E5_DB32_11D2_B476_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COptionTreeApp:
// See OptionTree.cpp for the implementation of this class
//

class COptionTreeApp : public CWinApp
{
public:
	COptionTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionTreeApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COptionTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONTREE_H__1D5197E5_DB32_11D2_B476_00E0291A4FD3__INCLUDED_)
