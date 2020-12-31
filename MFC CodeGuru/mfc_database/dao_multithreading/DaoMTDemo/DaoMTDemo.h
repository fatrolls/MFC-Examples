// DaoMTDemo.h : main header file for the DAOMTDEMO application
//

#if !defined(AFX_DAOMTDEMO_H__CFCF52F6_AEA9_11D1_9811_00A024DFE858__INCLUDED_)
#define AFX_DAOMTDEMO_H__CFCF52F6_AEA9_11D1_9811_00A024DFE858__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDaoMTDemoApp:
// See DaoMTDemo.cpp for the implementation of this class
//

class CDaoMTDemoApp : public CWinApp
{
public:
	CDaoMTDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoMTDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDaoMTDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define MYWM_UPDATE			WM_APP+1
#define MYWM_TERMINATING	WM_APP+2


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOMTDEMO_H__CFCF52F6_AEA9_11D1_9811_00A024DFE858__INCLUDED_)
