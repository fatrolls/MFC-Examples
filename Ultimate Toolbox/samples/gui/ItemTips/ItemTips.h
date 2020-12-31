// ItemTips.h : main header file for the ITEMTIPS application
//

#if !defined(AFX_ITEMTIPS_H__60CB2B7A_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
#define AFX_ITEMTIPS_H__60CB2B7A_E9A4_11D1_8855_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define LISTICONCOUNT		4
#define ICONLISTFIRST		0
#define ICONLISTLAST		(ICONLISTFIRST + LISTICONCOUNT - 1)
#define ICONCOUNT			(LISTICONCOUNT)

#define COLOR_BLUE			RGB(0,0,255)
#define COLOR_RED			RGB(255,0,0)
#define COLOR_YELLOW		RGB(255,255,0)

/////////////////////////////////////////////////////////////////////////////
// CItemTipsApp:
// See ItemTips.cpp for the implementation of this class
//

class CItemTipsApp : public CWinApp
{
public:
	CItemTipsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemTipsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CItemTipsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMTIPS_H__60CB2B7A_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
