#if !defined(AFX_STATUSBAR_H__DC9D02A4_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_)
#define AFX_STATUSBAR_H__DC9D02A4_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

class CStatusBarApp : public CWinApp
{
public:
	CStatusBarApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStatusBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CStatusBarApp)
	afx_msg void OnAppAbout();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_STATUSBAR_H__DC9D02A4_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_)
