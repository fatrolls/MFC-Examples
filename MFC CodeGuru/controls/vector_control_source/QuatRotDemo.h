// QuatRotDemo.h : main header file for the QUATROTDEMO application
//

#if !defined(AFX_QUATROTDEMO_H__BE23BA65_C0D3_11D1_9738_F0693C6EEA7E__INCLUDED_)
#define AFX_QUATROTDEMO_H__BE23BA65_C0D3_11D1_9738_F0693C6EEA7E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQuatRotDemoApp:
// See QuatRotDemo.cpp for the implementation of this class
//

class CQuatRotDemoApp : public CWinApp
{
public:
	CQuatRotDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuatRotDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQuatRotDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUATROTDEMO_H__BE23BA65_C0D3_11D1_9738_F0693C6EEA7E__INCLUDED_)
