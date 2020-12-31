// ToolTipEx.h : main header file for the TOOLTIPEX application
//

#if !defined(AFX_TOOLTIPEX_H__7FF81955_1C44_11D2_965C_00A0C9668BF9__INCLUDED_)
#define AFX_TOOLTIPEX_H__7FF81955_1C44_11D2_965C_00A0C9668BF9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolTipExApp:
// See ToolTipEx.cpp for the implementation of this class
//

class CToolTipExApp : public CWinApp
{
public:
	CToolTipExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipExApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CToolTipExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPEX_H__7FF81955_1C44_11D2_965C_00A0C9668BF9__INCLUDED_)
