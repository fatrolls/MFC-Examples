// ReportCtrlDemo.h : main header file for the REPORTCTRLDEMO application
//

#if !defined(AFX_REPORTCTRLDEMO_H__E384D081_A1F5_4E3B_AC0B_EC015055951C__INCLUDED_)
#define AFX_REPORTCTRLDEMO_H__E384D081_A1F5_4E3B_AC0B_EC015055951C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoApp:
// See ReportCtrlDemo.cpp for the implementation of this class
//

class CReportCtrlDemoApp : public CWinApp
{
public:
	CReportCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReportCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCTRLDEMO_H__E384D081_A1F5_4E3B_AC0B_EC015055951C__INCLUDED_)
