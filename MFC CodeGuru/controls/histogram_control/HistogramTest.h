// HistogramTest.h : main header file for the HISTOGRAMTEST application
//

#if !defined(AFX_HISTOGRAMTEST_H__C5FA53C4_EACC_11D1_9DF0_0060970863EE__INCLUDED_)
#define AFX_HISTOGRAMTEST_H__C5FA53C4_EACC_11D1_9DF0_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHistogramTestApp:
// See HistogramTest.cpp for the implementation of this class
//

class CHistogramTestApp : public CWinApp
{
public:
	CHistogramTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHistogramTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMTEST_H__C5FA53C4_EACC_11D1_9DF0_0060970863EE__INCLUDED_)
