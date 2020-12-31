// DateTimePicker.h : main header file for the DateTimePicker application
//

#if !defined(AFX_DATETIMEPICKER_H__3F275487_255F_11D2_889C_0080C83F712F__INCLUDED_)
#define AFX_DATETIMEPICKER_H__3F275487_255F_11D2_889C_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDateTimePickerApp:
// See DateTimePicker.cpp for the implementation of this class
//

class CDateTimePickerApp : public CWinApp
{
public:
	CDateTimePickerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimePickerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDateTimePickerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMEPICKER_H__3F275487_255F_11D2_889C_0080C83F712F__INCLUDED_)
