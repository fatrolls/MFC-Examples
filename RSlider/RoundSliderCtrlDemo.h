// RoundSliderCtrlDemo.h : Haupt-Header-Datei für die Anwendung ROUNDSLIDERCTRLDEMO
//

#if !defined(_ROUNDSLIDERCTRLDEMO_H_)
#define _ROUNDSLIDERCTRLDEMO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CRoundSliderCtrlDemoApp:
// Siehe RoundSliderCtrlDemo.cpp für die Implementierung dieser Klasse
//

class CRoundSliderCtrlDemoApp : public CWinApp
{
public:
	CRoundSliderCtrlDemoApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CRoundSliderCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CRoundSliderCtrlDemoApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(_ROUNDSLIDERCTRLDEMO_H_)
