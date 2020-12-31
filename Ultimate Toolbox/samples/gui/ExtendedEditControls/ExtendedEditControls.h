// ExtendedEditControls.h : main header file for the EXTENDEDEDITCONTROLS application
//

#if !defined(AFX_EXTENDEDEDITCONTROLS_H__A1558738_B094_11D2_A7B0_525400DAF3CE__INCLUDED_)
#define AFX_EXTENDEDEDITCONTROLS_H__A1558738_B094_11D2_A7B0_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtendedEditControlsApp:
// See ExtendedEditControls.cpp for the implementation of this class
//

class CExtendedEditControlsApp : public CWinApp
{
public:
	CExtendedEditControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedEditControlsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExtendedEditControlsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDEDITCONTROLS_H__A1558738_B094_11D2_A7B0_525400DAF3CE__INCLUDED_)
