/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			CConstraint
 * JRRC:			%J%
 * Inlines:			-
 *
 ****************************************************************************/

#if !defined(AFX_CONSTRAINT_H__549FCE05_DB80_11D1_B6E6_08005AD2C08F__INCLUDED_)
#define AFX_CONSTRAINT_H__549FCE05_DB80_11D1_B6E6_08005AD2C08F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

class CConstraintApp : public CWinApp
{
public:
	CConstraintApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CConstraintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CConstraintApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_CONSTRAINT_H__549FCE05_DB80_11D1_B6E6_08005AD2C08F__INCLUDED_)
