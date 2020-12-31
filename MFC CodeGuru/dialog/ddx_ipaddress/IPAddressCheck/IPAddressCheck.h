// IPAddressCheck.h : main header file for the IPADDRESSCHECK application
//

#if !defined(AFX_IPADDRESSCHECK_H__3C974E24_EB56_11D1_BB83_0040F684401F__INCLUDED_)
#define AFX_IPADDRESSCHECK_H__3C974E24_EB56_11D1_BB83_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCheckApp:
// See IPAddressCheck.cpp for the implementation of this class
//

class CIPAddressCheckApp : public CWinApp
{
public:
	CIPAddressCheckApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddressCheckApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPAddressCheckApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDRESSCHECK_H__3C974E24_EB56_11D1_BB83_0040F684401F__INCLUDED_)
