// SdiSquares.h : main header file for the SDISQUARES application
//

#if !defined(AFX_SDISQUARES_H__00156CE5_BB17_11D2_A2FD_0000861BAE71__INCLUDED_)
#define AFX_SDISQUARES_H__00156CE5_BB17_11D2_A2FD_0000861BAE71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSquaresApp:
// See SdiSquares.cpp for the implementation of this class
//

class CSquaresApp : public CWinApp
{
public:
	CSquaresApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquaresApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSquaresApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDISQUARES_H__00156CE5_BB17_11D2_A2FD_0000861BAE71__INCLUDED_)
