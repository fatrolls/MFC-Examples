// OWnd.h : main header file for the OWND DLL
//

#if !defined(AFX_OWND_H__43B321F8_0385_11D2_B5D0_000000000000__INCLUDED_)
#define AFX_OWND_H__43B321F8_0385_11D2_B5D0_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COWndApp
// See OWnd.cpp for the implementation of this class
//

class COWndApp : public CWinApp
{
public:
	COWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COWndApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(COWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWND_H__43B321F8_0385_11D2_B5D0_000000000000__INCLUDED_)
