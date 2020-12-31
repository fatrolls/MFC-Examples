// ColorPickerButton.h : main header file for the COLORPICKERBUTTON application
//

#if !defined(AFX_COLORPICKERBUTTON_H__875CC117_F4B4_11D1_8862_0080C83F712F__INCLUDED_)
#define AFX_COLORPICKERBUTTON_H__875CC117_F4B4_11D1_8862_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButtonApp:
// See ColorPickerButton.cpp for the implementation of this class
//

class CColorPickerButtonApp : public CWinApp
{
public:
	CColorPickerButtonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPickerButtonApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorPickerButtonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPICKERBUTTON_H__875CC117_F4B4_11D1_8862_0080C83F712F__INCLUDED_)
