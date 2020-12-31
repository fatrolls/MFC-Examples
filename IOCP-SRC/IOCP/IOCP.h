// IOCP.h : main header file for the IOCP application
//

#if !defined(AFX_IOCP_H__1D046E65_D0A9_40E8_BA22_43659D2E4736__INCLUDED_)
#define AFX_IOCP_H__1D046E65_D0A9_40E8_BA22_43659D2E4736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIOCPApp:
// See IOCP.cpp for the implementation of this class
//

class CIOCPApp : public CWinApp
{
public:
	CIOCPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOCPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIOCPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCP_H__1D046E65_D0A9_40E8_BA22_43659D2E4736__INCLUDED_)
