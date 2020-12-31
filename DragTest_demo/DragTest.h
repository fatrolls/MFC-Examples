// DragTest.h : main header file for the DRAGTEST application
//

#if !defined(AFX_DRAGTEST_H__C2CA86A2_9DC9_4EEE_AA61_0D92F9A7FCC5__INCLUDED_)
#define AFX_DRAGTEST_H__C2CA86A2_9DC9_4EEE_AA61_0D92F9A7FCC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDragTestApp:
// See DragTest.cpp for the implementation of this class
//

class CDragTestApp : public CWinApp
{
public:
	CDragTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDragTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGTEST_H__C2CA86A2_9DC9_4EEE_AA61_0D92F9A7FCC5__INCLUDED_)
