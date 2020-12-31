// SysInfo1.h : main header file for the SYSINFO1 application
//

#if !defined(AFX_SYSINFO1_H__1CD38C27_81E5_11D1_A4E0_0020359647BF__INCLUDED_)
#define AFX_SYSINFO1_H__1CD38C27_81E5_11D1_A4E0_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSysInfo1App:
// See SysInfo1.cpp for the implementation of this class
//

class CSysInfo1App : public CWinApp
{
public:
	CSysInfo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysInfo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSysInfo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFO1_H__1CD38C27_81E5_11D1_A4E0_0020359647BF__INCLUDED_)
