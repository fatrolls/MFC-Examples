// ChartDemo.h : main header file for the CHARTDEMO application
//

#if !defined(AFX_CHARTDEMO_H__B7735086_C0AE_4EB2_91AF_2AA128DA4EBD__INCLUDED_)
#define AFX_CHARTDEMO_H__B7735086_C0AE_4EB2_91AF_2AA128DA4EBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChartDemoApp:
// See ChartDemo.cpp for the implementation of this class
//

class CChartDemoApp : public CWinApp
{
public:
	CChartDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChartDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTDEMO_H__B7735086_C0AE_4EB2_91AF_2AA128DA4EBD__INCLUDED_)
