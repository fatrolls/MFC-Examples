// LookMaSDI.h : main header file for the LOOKMASDI application
//

#if !defined(AFX_LOOKMASDI_H__B5EC07F8_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_)
#define AFX_LOOKMASDI_H__B5EC07F8_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIApp:
// See LookMaSDI.cpp for the implementation of this class
//

class CLookMaSDIApp : public CWinApp
{
public:
	CLookMaSDIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLookMaSDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLookMaSDIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOOKMASDI_H__B5EC07F8_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_)
