// HTMLEdit.h : main header file for the HTMLEdit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CHTMLEditApp:
// See HTMLEdit.cpp for the implementation of this class
//

class CHTMLEditApp : public CWinApp
{
public:
	CHTMLEditApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHTMLEditApp theApp;