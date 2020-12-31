// EventLog.h : main header file for the EVENTLOG application
//

#if !defined(AFX_EVENTLOG_H__B2FDEA46_8819_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_EVENTLOG_H__B2FDEA46_8819_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEventLogApp:
// See EventLog.cpp for the implementation of this class
//

class CEventLogApp : public CWinApp
{
public:
	CEventLogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventLogApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEventLogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTLOG_H__B2FDEA46_8819_11D1_A3D5_0080C83F712F__INCLUDED_)
