// dirpick.h : main header file for the DIRPICK DLL
//

#if !defined(AFX_DIRPICK_H__875F2B26_E504_11D1_AABA_0080C74D32C6__INCLUDED_)
#define AFX_DIRPICK_H__875F2B26_E504_11D1_AABA_0080C74D32C6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirpickApp
// See dirpick.cpp for the implementation of this class
//

class CDirpickApp : public CWinApp
{
public:
	CDirpickApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirpickApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDirpickApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRPICK_H__875F2B26_E504_11D1_AABA_0080C74D32C6__INCLUDED_)
