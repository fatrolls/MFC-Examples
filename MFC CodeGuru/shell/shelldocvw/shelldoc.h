// shelldoc.h : main header file for the SHELLDOC application
//

#if !defined(AFX_SHELLDOC_H__A773FE77_4192_11D1_AE13_006097D60BAC__INCLUDED_)
#define AFX_SHELLDOC_H__A773FE77_4192_11D1_AE13_006097D60BAC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShelldocApp:
// See shelldoc.cpp for the implementation of this class
//

class CShelldocApp : public CWinApp
{
public:
	CShelldocApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShelldocApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShelldocApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLDOC_H__A773FE77_4192_11D1_AE13_006097D60BAC__INCLUDED_)
