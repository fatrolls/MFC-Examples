// viewport.h : main header file for the VIEWPORT application
//

#if !defined(AFX_VIEWPORT_H__2D3F586D_F6C5_414F_9EF7_8EEA9B150A42__INCLUDED_)
#define AFX_VIEWPORT_H__2D3F586D_F6C5_414F_9EF7_8EEA9B150A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CViewportApp:
// See viewport.cpp for the implementation of this class
//

class CViewportApp : public CWinApp
{
public:
	CViewportApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewportApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CViewportApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORT_H__2D3F586D_F6C5_414F_9EF7_8EEA9B150A42__INCLUDED_)
