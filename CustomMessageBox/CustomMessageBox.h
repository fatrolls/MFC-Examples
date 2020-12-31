// CustomMessageBox.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CCustomMessageBoxApp:
// See CustomMessageBox.cpp for the implementation of this class
//
INT CBTMessageBox(HWND,LPSTR,LPSTR,UINT);
LRESULT CALLBACK CBTProc(INT, WPARAM, LPARAM);

class CCustomMessageBoxApp : public CWinApp
{
public:
	CCustomMessageBoxApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
};

extern CCustomMessageBoxApp theApp;