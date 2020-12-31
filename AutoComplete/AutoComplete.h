// AutoComplete.h : Haupt-Header-Datei für die Anwendung AUTOCOMPLETE
//

#if !defined(AFX_AUTOCOMPLETE_H__CB5E1423_4E09_4E4C_803C_3910C27D9A90__INCLUDED_)
#define AFX_AUTOCOMPLETE_H__CB5E1423_4E09_4E4C_803C_3910C27D9A90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CAutoCompleteApp:
// Siehe AutoComplete.cpp für die Implementierung dieser Klasse
//

class CAutoCompleteApp : public CWinApp
{
public:
	CAutoCompleteApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAutoCompleteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CAutoCompleteApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_AUTOCOMPLETE_H__CB5E1423_4E09_4E4C_803C_3910C27D9A90__INCLUDED_)
