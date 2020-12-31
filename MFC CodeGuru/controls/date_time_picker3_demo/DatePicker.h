// DatePicker.h : main header file for the DATEPICKER application
//

#if !defined(AFX_DATEPICKER_H__497A0324_55F0_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_DATEPICKER_H__497A0324_55F0_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDatePickerApp:
// See DatePicker.cpp for the implementation of this class
//

class CDatePickerApp : public CWinApp
{
public:
	CDatePickerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatePickerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDatePickerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEPICKER_H__497A0324_55F0_11D1_ABBA_00A0243D1382__INCLUDED_)
