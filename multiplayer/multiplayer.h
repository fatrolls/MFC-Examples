// multiplayer.h : main header file for the MULTIPLAYER application
//

#if !defined(AFX_MULTIPLAYER_H__3F1B9978_F29D_401A_B8A4_D7D68BB0F247__INCLUDED_)
#define AFX_MULTIPLAYER_H__3F1B9978_F29D_401A_B8A4_D7D68BB0F247__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiplayerApp:
// See multiplayer.cpp for the implementation of this class
//

class CMultiplayerApp : public CWinApp
{
public:
	CMultiplayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiplayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiplayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLAYER_H__3F1B9978_F29D_401A_B8A4_D7D68BB0F247__INCLUDED_)
