/*
**	FILENAME			Commtest.h
**
**	PURPOSE				This is the application class.
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Remon Spekreijse
**
**
*/

#if !defined(AFX_COMMTEST_H__4FDAC184_34B5_11D1_9481_00805A147202__INCLUDED_)
#define AFX_COMMTEST_H__4FDAC184_34B5_11D1_9481_00805A147202__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommtestApp:
// See commtest.cpp for the implementation of this class
//

class CCommtestApp : public CWinApp
{
public:
	CCommtestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommtestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCommtestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMTEST_H__4FDAC184_34B5_11D1_9481_00805A147202__INCLUDED_)
