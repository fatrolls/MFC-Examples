// HLSample.h : main header file for the HLSAMPLE application
//

#if !defined(AFX_HLSAMPLE_H__D1625065_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_HLSAMPLE_H__D1625065_574B_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHLSampleApp:
// See HLSample.cpp for the implementation of this class
//

class CHLSampleApp : public CWinApp
{
public:
	CHLSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHLSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHLSampleApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HLSAMPLE_H__D1625065_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
