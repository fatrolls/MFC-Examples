// ComboExDemo.h : main header file for the COMBOEXDEMO application
//

#if !defined(AFX_COMBOEXDEMO_H__115F4224_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_COMBOEXDEMO_H__115F4224_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoApp:
// See ComboExDemo.cpp for the implementation of this class
//

class CComboExDemoApp : public CWinApp
{
public:
	CComboExDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboExDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComboExDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOEXDEMO_H__115F4224_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
