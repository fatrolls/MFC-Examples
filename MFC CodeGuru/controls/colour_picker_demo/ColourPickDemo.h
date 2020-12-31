// ColourPickDemo.h : main header file for the COLOURPICKDEMO application
//

#if !defined(AFX_COLOURPICKDEMO_H__D0B758F4_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
#define AFX_COLOURPICKDEMO_H__D0B758F4_9830_11D1_9C0F_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColourPickDemoApp:
// See ColourPickDemo.cpp for the implementation of this class
//

class CColourPickDemoApp : public CWinApp
{
public:
	CColourPickDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColourPickDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColourPickDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURPICKDEMO_H__D0B758F4_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
