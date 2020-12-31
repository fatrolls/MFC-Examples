// MonthCalendar.h : main header file for the MONTHCALENDAR application
//

#if !defined(AFX_MONTHCALENDAR_H__3F275487_255F_11D2_889C_0080C83F712F__INCLUDED_)
#define AFX_MONTHCALENDAR_H__3F275487_255F_11D2_889C_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMonthCalendarApp:
// See MonthCalendar.cpp for the implementation of this class
//

class CMonthCalendarApp : public CWinApp
{
public:
	CMonthCalendarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonthCalendarApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMonthCalendarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTHCALENDAR_H__3F275487_255F_11D2_889C_0080C83F712F__INCLUDED_)
