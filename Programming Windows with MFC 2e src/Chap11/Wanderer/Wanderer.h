// Wanderer.h : main header file for the WANDERER application
//

#if !defined(AFX_WANDERER_H__AE0A6FFA_9B0F_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_WANDERER_H__AE0A6FFA_9B0F_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWandererApp:
// See Wanderer.cpp for the implementation of this class
//

class CWandererApp : public CWinApp
{
public:
	CWandererApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWandererApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWandererApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WANDERER_H__AE0A6FFA_9B0F_11D2_8E53_006008A82731__INCLUDED_)
