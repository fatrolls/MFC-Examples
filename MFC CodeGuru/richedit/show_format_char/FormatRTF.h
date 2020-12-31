// FormatRTF.h : main header file for the FORMATRTF application
//

#if !defined(AFX_FORMATRTF_H__96742794_94A4_11D1_B661_204C4F4F5020__INCLUDED_)
#define AFX_FORMATRTF_H__96742794_94A4_11D1_B661_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFApp:
// See FormatRTF.cpp for the implementation of this class
//

class CFormatRTFApp : public CWinApp
{
public:
	CFormatRTFApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatRTFApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFormatRTFApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATRTF_H__96742794_94A4_11D1_B661_204C4F4F5020__INCLUDED_)
