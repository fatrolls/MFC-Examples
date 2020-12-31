// splitdlg.h : main header file for the SPLITDLG application
//

#if !defined(AFX_SPLITDLG_H__0DB1DF86_BF0B_11D1_B39A_00C02658086B__INCLUDED_)
#define AFX_SPLITDLG_H__0DB1DF86_BF0B_11D1_B39A_00C02658086B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplitdlgApp:
// See splitdlg.cpp for the implementation of this class
//

class CSplitdlgApp : public CWinApp
{
public:
	CSplitdlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitdlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSplitdlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITDLG_H__0DB1DF86_BF0B_11D1_B39A_00C02658086B__INCLUDED_)
