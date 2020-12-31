// ComboTree.h : main header file for the COMBOTREE application
//

#if !defined(AFX_COMBOTREE_H__10B74AFE_15F6_11D4_AD12_0050BAAB46B1__INCLUDED_)
#define AFX_COMBOTREE_H__10B74AFE_15F6_11D4_AD12_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComboTreeApp:
// See ComboTree.cpp for the implementation of this class
//

class CComboTreeApp : public CWinApp
{
public:
	CComboTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboTreeApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComboTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOTREE_H__10B74AFE_15F6_11D4_AD12_0050BAAB46B1__INCLUDED_)
