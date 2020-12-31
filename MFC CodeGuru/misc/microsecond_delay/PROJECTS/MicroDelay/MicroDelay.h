// MicroDelay.h : main header file for the MICRODELAY application
//

#if !defined(AFX_MICRODELAY_H__D7406E72_9B3A_11D1_94DB_00400540824C__INCLUDED_)
#define AFX_MICRODELAY_H__D7406E72_9B3A_11D1_94DB_00400540824C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMicroDelayApp:
// See MicroDelay.cpp for the implementation of this class
//

class CMicroDelayApp : public CWinApp
{
public:
	CMicroDelayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMicroDelayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMicroDelayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MICRODELAY_H__D7406E72_9B3A_11D1_94DB_00400540824C__INCLUDED_)
