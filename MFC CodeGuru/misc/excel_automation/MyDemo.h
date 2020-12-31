// MyDemo.h : Haupt-Header-Datei für die Anwendung MYDEMO
//

#if !defined(AFX_MYDEMO_H__44414C42_A85E_11D1_9BB6_00C0D109A731__INCLUDED_)
#define AFX_MYDEMO_H__44414C42_A85E_11D1_9BB6_00C0D109A731__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMyDemoApp:
// Siehe MyDemo.cpp für die Implementierung dieser Klasse
//

class CMyDemoApp : public CWinApp
{
public:
	CMyDemoApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMyDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CMyDemoApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_MYDEMO_H__44414C42_A85E_11D1_9BB6_00C0D109A731__INCLUDED_)
