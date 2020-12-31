// TaskBar.h : main header file for the TASKBAR application
//

#if !defined(AFX_TASKBAR_H__9089251D_A8C8_11D1_B257_006097960BB7__INCLUDED_)
#define AFX_TASKBAR_H__9089251D_A8C8_11D1_B257_006097960BB7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTaskBarApp:
// See TaskBar.cpp for the implementation of this class
//

class CTaskBarApp : public CWinApp
{
public:
	CTaskBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTaskBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKBAR_H__9089251D_A8C8_11D1_B257_006097960BB7__INCLUDED_)
