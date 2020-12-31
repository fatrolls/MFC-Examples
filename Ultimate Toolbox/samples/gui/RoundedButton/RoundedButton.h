// RoundedButton.h : main header file for the ROUNDEDBUTTON application
//

#if !defined(AFX_ROUNDEDBUTTON_H__9B0A917A_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_)
#define AFX_ROUNDEDBUTTON_H__9B0A917A_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonApp:
// See RoundedButton.cpp for the implementation of this class
//

class CRoundedButtonApp : public CWinApp
{
public:
	CRoundedButtonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundedButtonApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRoundedButtonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDEDBUTTON_H__9B0A917A_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_)
