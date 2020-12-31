// CTestProgressBar.h : main header file for the CTESTPROGRESSBAR application
//

#if !defined(AFX_CTESTPROGRESSBAR_H__35E926A4_EBE7_11D1_9871_C5E6F2F2B45F__INCLUDED_)
#define AFX_CTESTPROGRESSBAR_H__35E926A4_EBE7_11D1_9871_C5E6F2F2B45F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCTestProgressBarApp:
// See CTestProgressBar.cpp for the implementation of this class
//

class CCTestProgressBarApp : public CWinApp
{
public:
	CCTestProgressBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTestProgressBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCTestProgressBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTESTPROGRESSBAR_H__35E926A4_EBE7_11D1_9871_C5E6F2F2B45F__INCLUDED_)
