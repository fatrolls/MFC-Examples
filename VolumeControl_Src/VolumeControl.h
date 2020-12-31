// VolumeControl.h : main header file for the VOLUMECONTROL application
//

#if !defined(AFX_VOLUMECONTROL_H__B3120E25_DA79_41CE_96FA_E5DF7B09CDA5__INCLUDED_)
#define AFX_VOLUMECONTROL_H__B3120E25_DA79_41CE_96FA_E5DF7B09CDA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVolumeControlApp:
// See VolumeControl.cpp for the implementation of this class
//

class CVolumeControlApp : public CWinApp
{
public:
	CVolumeControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVolumeControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMECONTROL_H__B3120E25_DA79_41CE_96FA_E5DF7B09CDA5__INCLUDED_)
