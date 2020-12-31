// RangeEdit.h : main header file for the RANGEEDIT application
//

#if !defined(AFX_RANGEEDIT_H__63CDCB64_CD89_11D1_93FA_444553540000__INCLUDED_)
#define AFX_RANGEEDIT_H__63CDCB64_CD89_11D1_93FA_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRangeEditApp:
// See RangeEdit.cpp for the implementation of this class
//

class CRangeEditApp : public CWinApp
{
public:
	CRangeEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRangeEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRangeEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANGEEDIT_H__63CDCB64_CD89_11D1_93FA_444553540000__INCLUDED_)
