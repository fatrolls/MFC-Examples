// Multiline.h : main header file for the MULTILINE application
//

#if !defined(AFX_MULTILINE_H__30509646_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
#define AFX_MULTILINE_H__30509646_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultilineApp:
// See Multiline.cpp for the implementation of this class
//

class CMultilineApp : public CWinApp
{
public:
	CMultilineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultilineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMultilineApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILINE_H__30509646_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
