// Separator.h : main header file for the SEPARATOR application
//

#if !defined(AFX_SEPARATOR_H__354BA845_6F3F_11D2_A75E_525400DAF3CE__INCLUDED_)
#define AFX_SEPARATOR_H__354BA845_6F3F_11D2_A75E_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSeparatorApp:
// See Separator.cpp for the implementation of this class
//

class CSeparatorApp : public CWinApp
{
public:
	CSeparatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparatorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSeparatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPARATOR_H__354BA845_6F3F_11D2_A75E_525400DAF3CE__INCLUDED_)
