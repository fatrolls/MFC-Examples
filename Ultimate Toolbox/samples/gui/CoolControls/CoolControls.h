// CoolControls.h : main header file for the COOLCONTROLS application
//

#if !defined(AFX_COOLCONTROLS_H__3696ECD8_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_COOLCONTROLS_H__3696ECD8_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCoolControlsApp:
// See CoolControls.cpp for the implementation of this class
//

class CCoolControlsApp : public CWinApp
{
public:
	CCoolControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolControlsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCoolControlsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLCONTROLS_H__3696ECD8_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
