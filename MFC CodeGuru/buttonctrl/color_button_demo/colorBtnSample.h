// colorBtnSample.h : main header file for the COLORBTNSAMPLE application
//

#if !defined(AFX_COLORBTNSAMPLE_H__5163CE17_D92D_11D1_A82F_0060974FADEB__INCLUDED_)
#define AFX_COLORBTNSAMPLE_H__5163CE17_D92D_11D1_A82F_0060974FADEB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorBtnSampleApp:
// See colorBtnSample.cpp for the implementation of this class
//

class CColorBtnSampleApp : public CWinApp
{
public:
	CColorBtnSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtnSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorBtnSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBTNSAMPLE_H__5163CE17_D92D_11D1_A82F_0060974FADEB__INCLUDED_)
