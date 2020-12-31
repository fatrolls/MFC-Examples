// Sample_S.h : main header file for the SAMPLE_S application
//

#if !defined(AFX_SAMPLE_S_H__6D8D50B5_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_)
#define AFX_SAMPLE_S_H__6D8D50B5_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#pragma warning ( disable : 4511 4512 )

/////////////////////////////////////////////////////////////////////////////
// CSample_SApp:
// See Sample_S.cpp for the implementation of this class
//

class CSample_SApp : public CWinApp
{
public:
	CSample_SApp();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample_SApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSample_SApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE_S_H__6D8D50B5_CAA0_11D2_8A0B_0080C86AC2FB__INCLUDED_)
