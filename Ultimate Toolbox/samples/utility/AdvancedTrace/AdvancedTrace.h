// AdvancedTrace.h : main header file for the ADVANCEDTRACE application
//

#if !defined(AFX_ADVANCEDTRACE_H__3454410A_BC3C_11D2_A7BD_525400DAF3CE__INCLUDED_)
#define AFX_ADVANCEDTRACE_H__3454410A_BC3C_11D2_A7BD_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "OXTrace.h"

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceApp:
// See AdvancedTrace.cpp for the implementation of this class
//

class CAdvancedTraceApp : public CWinApp
{
public:
	CAdvancedTraceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedTraceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAdvancedTraceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDTRACE_H__3454410A_BC3C_11D2_A7BD_525400DAF3CE__INCLUDED_)
