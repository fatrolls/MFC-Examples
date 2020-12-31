// OXCalendarDemo1.h : main header file for the OXCALENDARDEMO1 application
//

#if !defined(AFX_OXCALENDARDEMO1_H__4EDE7CB7_874D_11D1_A4E3_0020359647BF__INCLUDED_)
#define AFX_OXCALENDARDEMO1_H__4EDE7CB7_874D_11D1_A4E3_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COXCalendarDemo1App:
// See OXCalendarDemo1.cpp for the implementation of this class
//

class COXCalendarDemo1App : public CWinApp
{
public:
	COXCalendarDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXCalendarDemo1App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COXCalendarDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OXCALENDARDEMO1_H__4EDE7CB7_874D_11D1_A4E3_0020359647BF__INCLUDED_)
