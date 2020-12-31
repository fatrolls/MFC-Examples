// ColorSelector.h : main header file for the COLORSELECTOR application
//

#if !defined(AFX_COLORSELECTOR_H__E61E3C52_84EE_4654_AC3D_82156B4B4694__INCLUDED_)
#define AFX_COLORSELECTOR_H__E61E3C52_84EE_4654_AC3D_82156B4B4694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// some private messages and their values

#define UWM_SPECTRUMWINDOWEVENT	(WM_USER+1)
#define SWE_NEWFOCUSCOLOR		0x0001



/////////////////////////////////////////////////////////////////////////////
// CColorSelectorApp:
// See ColorSelector.cpp for the implementation of this class
//

class CColorSelectorApp : public CWinApp
{
public:
	CColorSelectorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelectorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorSelectorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSELECTOR_H__E61E3C52_84EE_4654_AC3D_82156B4B4694__INCLUDED_)
