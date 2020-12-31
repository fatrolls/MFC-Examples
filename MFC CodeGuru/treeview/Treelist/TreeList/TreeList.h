// TreeList.h : main header file for the TREELIST application
//

#if !defined(AFX_TREELIST_H__0ADCB515_5905_11D1_980A_004095E0DEFA__INCLUDED_)
#define AFX_TREELIST_H__0ADCB515_5905_11D1_980A_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTreeListApp:
// See TreeList.cpp for the implementation of this class
//

class CTreeListApp : public CWinApp
{
public:
	CTreeListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTreeListApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREELIST_H__0ADCB515_5905_11D1_980A_004095E0DEFA__INCLUDED_)
