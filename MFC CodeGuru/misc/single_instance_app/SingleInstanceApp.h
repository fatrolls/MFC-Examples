// SingleInstanceApp.cpp : header file
//
// CWinApp with single-instance support
//
// Copyright (C) 1997, 1998 Giancarlo Iovino (giancarlo@saria.com)
// All rights reserved. May not be sold for profit.
//
// Thanks to Kevin Lussier for the base idea.
//
// This code was developed for MFC Programmers SourceBook
// (http://www.codeguru.com)
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSingleInstanceApp:
//

class CSingleInstanceApp : public CWinApp
{
public:
	// Construction/Destruction
	CSingleInstanceApp();
	~CSingleInstanceApp();

	// Operations
	BOOL CheckSingleInstance(UINT nID);
	CString GetClassName() const;

protected:
	HANDLE m_hMutex;
	CString m_strClassName;
};


/////////////////////////////////////////////////////////////////////////////
