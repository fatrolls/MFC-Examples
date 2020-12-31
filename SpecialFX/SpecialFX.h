// SpecialFX.h : main header file for the SPECIALFX application
//

#if !defined(AFX_SPECIALFX_H__7B228AF4_8EB4_44D5_8170_B4C1BE797E42__INCLUDED_)
#define AFX_SPECIALFX_H__7B228AF4_8EB4_44D5_8170_B4C1BE797E42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpecialFXApp:
// See SpecialFX.cpp for the implementation of this class
//

class CSpecialFXApp : public CWinApp
{
public:
	CSpecialFXApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecialFXApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpecialFXApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECIALFX_H__7B228AF4_8EB4_44D5_8170_B4C1BE797E42__INCLUDED_)
