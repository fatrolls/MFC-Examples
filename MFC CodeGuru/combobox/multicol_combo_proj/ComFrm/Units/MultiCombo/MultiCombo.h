// MultiCombo.h : main header file for the MULTICOMBO application
//

#if !defined(AFX_MULTICOMBO_H__9FAE7787_723F_11D1_AEBB_00A0240D05AF__INCLUDED_)
#define AFX_MULTICOMBO_H__9FAE7787_723F_11D1_AEBB_00A0240D05AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiComboApp:
// See MultiCombo.cpp for the implementation of this class
//

class CMultiComboApp : public CWinApp
{
public:
	CMultiComboApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiComboApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiComboApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTICOMBO_H__9FAE7787_723F_11D1_AEBB_00A0240D05AF__INCLUDED_)
