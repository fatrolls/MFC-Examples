
// NCSkinDemo.h : main header file for the NCSkinDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CNCSkinDemoApp:
// See NCSkinDemo.cpp for the implementation of this class
//

class CNCSkinDemoApp : public CWinAppEx
{
public:
	CNCSkinDemoApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CNCSkinDemoApp theApp;
