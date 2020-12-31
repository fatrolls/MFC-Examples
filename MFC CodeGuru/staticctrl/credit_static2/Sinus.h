// Sinus.h : Haupt-Header-Datei für die Anwendung SINUS
//

#if !defined(AFX_SINUS_H__41258CB5_8436_11D1_9C04_084D65000000__INCLUDED_)
#define AFX_SINUS_H__41258CB5_8436_11D1_9C04_084D65000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CSinusApp:
// Siehe Sinus.cpp für die Implementierung dieser Klasse
//

class CSinusApp : public CWinApp
{
public:
	CSinusApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSinusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CSinusApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_SINUS_H__41258CB5_8436_11D1_9C04_084D65000000__INCLUDED_)
