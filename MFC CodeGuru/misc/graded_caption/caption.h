// caption.h : main header file for the CAPTION application
//

#if !defined(AFX_CAPTION_H__A5362394_6034_11D1_B4DF_006097608B1F__INCLUDED_)
#define AFX_CAPTION_H__A5362394_6034_11D1_B4DF_006097608B1F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCaptionApp:
// See caption.cpp for the implementation of this class
//

class CCaptionApp : public CWinApp
{
public:
	CCaptionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCaptionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTION_H__A5362394_6034_11D1_B4DF_006097608B1F__INCLUDED_)
