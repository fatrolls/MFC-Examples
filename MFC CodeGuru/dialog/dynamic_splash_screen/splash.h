// splash.h : Haupt-Header-Datei für die Anwendung SPLASH
//

#if !defined(AFX_SPLASH_H__00D06792_E8B9_11D1_A474_006097E3E7B0__INCLUDED_)
#define AFX_SPLASH_H__00D06792_E8B9_11D1_A474_006097E3E7B0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CSplashApp:
// Siehe splash.cpp für die Implementierung dieser Klasse
//

class CSplashApp : public CWinApp
{
public:
	CSplashApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSplashApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CSplashApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_SPLASH_H__00D06792_E8B9_11D1_A474_006097E3E7B0__INCLUDED_)
