// SoundManager.h : main header file for the SOUNDMANAGER application
//

#if !defined(AFX_SOUNDMANAGER_H__A84121A8_1C0A_11D2_8890_0080C83F712F__INCLUDED_)
#define AFX_SOUNDMANAGER_H__A84121A8_1C0A_11D2_8890_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoundManagerApp:
// See SoundManager.cpp for the implementation of this class
//

class CSoundManagerApp : public CWinApp
{
public:
	CSoundManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundManagerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSoundManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDMANAGER_H__A84121A8_1C0A_11D2_8890_0080C83F712F__INCLUDED_)
