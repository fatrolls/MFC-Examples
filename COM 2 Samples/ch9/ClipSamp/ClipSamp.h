// ClipSamp.h : main header file for the CLIPSAMP application
//

#if !defined(AFX_CLIPSAMP_H__1D48F685_DFF7_11D2_9E78_00104B08CC22__INCLUDED_)
#define AFX_CLIPSAMP_H__1D48F685_DFF7_11D2_9E78_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipSampApp:
// See ClipSamp.cpp for the implementation of this class
//

class CClipSampApp : public CWinApp
{
public:
	CClipSampApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipSampApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClipSampApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPSAMP_H__1D48F685_DFF7_11D2_9E78_00104B08CC22__INCLUDED_)
