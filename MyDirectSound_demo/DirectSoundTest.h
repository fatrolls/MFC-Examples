// DirectSoundTest.h : main header file for the DIRECTSOUNDTEST application
//

#if !defined(AFX_DIRECTSOUNDTEST_H__066BD984_6A8E_458C_9CBF_9C02EB6F6EBC__INCLUDED_)
#define AFX_DIRECTSOUNDTEST_H__066BD984_6A8E_458C_9CBF_9C02EB6F6EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirectSoundTestApp:
// See DirectSoundTest.cpp for the implementation of this class
//

class CDirectSoundTestApp : public CWinApp
{
public:
	CDirectSoundTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectSoundTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDirectSoundTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTSOUNDTEST_H__066BD984_6A8E_458C_9CBF_9C02EB6F6EBC__INCLUDED_)
