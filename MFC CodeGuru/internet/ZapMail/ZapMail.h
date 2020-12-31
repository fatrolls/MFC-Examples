// ZapMail.h : main header file for the ZAPMAIL application
//

#if !defined(AFX_ZAPMAIL_H__333BA6D2_F593_11D1_870E_444553540001__INCLUDED_)
#define AFX_ZAPMAIL_H__333BA6D2_F593_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZapMailApp:
// See ZapMail.cpp for the implementation of this class
//

class CZapMailApp : public CWinApp
{
public:
	CZapMailApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZapMailApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZapMailApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZAPMAIL_H__333BA6D2_F593_11D1_870E_444553540001__INCLUDED_)
