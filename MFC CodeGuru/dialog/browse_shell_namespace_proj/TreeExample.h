// TreeExample.h : main header file for the TREEEXAMPLE application
//

#if !defined(AFX_TREEEXAMPLE_H__F0B620A5_9D4F_11D1_B10E_B8F603C10000__INCLUDED_)
#define AFX_TREEEXAMPLE_H__F0B620A5_9D4F_11D1_B10E_B8F603C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTreeExampleApp:
// See TreeExample.cpp for the implementation of this class
//
//
// This source is part of CShellTree - Selom Ofori
// 
// Version: 1.02 (any previously unversioned copies are older/inferior
//
// This code is free for all to use. Mutatilate it as much as you want
// See MFCENUM sample from microsoft

class CTreeExampleApp : public CWinApp
{
public:
	CTreeExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTreeExampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEEXAMPLE_H__F0B620A5_9D4F_11D1_B10E_B8F603C10000__INCLUDED_)
