// Pizza.h : main header file for the PIZZA application
//

#if !defined(AFX_PIZZA_H__36762C77_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_)
#define AFX_PIZZA_H__36762C77_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPizzaApp:
// See Pizza.cpp for the implementation of this class
//

class CPizzaApp : public CWinApp
{
public:
	CPizzaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPizzaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPizzaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIZZA_H__36762C77_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_)
