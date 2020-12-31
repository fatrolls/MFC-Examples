// NetSample.h : main header file for the NETSAMPLE application
//

#if !defined(AFX_NETSAMPLE_H__347C5694_9C76_11D1_9436_0000C014F0A1__INCLUDED_)
#define AFX_NETSAMPLE_H__347C5694_9C76_11D1_9436_0000C014F0A1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetSampleApp:
// See NetSample.cpp for the implementation of this class
//

class CNetSampleApp : public CWinApp
{
public:
	CNetSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSAMPLE_H__347C5694_9C76_11D1_9436_0000C014F0A1__INCLUDED_)
