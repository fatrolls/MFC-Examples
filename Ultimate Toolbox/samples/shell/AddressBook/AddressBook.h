// AddressBook.h : main header file for the ADDRESSBOOK application
//

#if !defined(AFX_ADDRESSBOOK_H__4FD8257A_E3AD_11D3_ACA4_0050BAAB46B1__INCLUDED_)
#define AFX_ADDRESSBOOK_H__4FD8257A_E3AD_11D3_ACA4_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAddressBookApp:
// See AddressBook.cpp for the implementation of this class
//

class CAddressBookApp : public CWinApp
{
public:
	CAddressBookApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddressBookApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAddressBookApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRESSBOOK_H__4FD8257A_E3AD_11D3_ACA4_0050BAAB46B1__INCLUDED_)
