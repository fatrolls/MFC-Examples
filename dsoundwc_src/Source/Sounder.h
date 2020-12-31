// Sounder.h : main header file for the SOUNDER application
//

#if !defined(AFX_SOUNDER_H__A14C6329_9447_433F_B74D_0D8727A76C05__INCLUDED_)
#define AFX_SOUNDER_H__A14C6329_9447_433F_B74D_0D8727A76C05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSounderApp:
// See Sounder.cpp for the implementation of this class
//

class CSounderApp : public CWinApp
{
public:
	CSounderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSounderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSounderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDER_H__A14C6329_9447_433F_B74D_0D8727A76C05__INCLUDED_)
