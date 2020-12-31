// TimeTracker.h : Haupt-Header-Datei für die Anwendung TimeTracker
//

#if !defined(AFX_TimeTracker_H__D0B3EC33_4B0F_11D1_94CD_0020187099A1__INCLUDED_)
#define AFX_TimeTracker_H__D0B3EC33_4B0F_11D1_94CD_0020187099A1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole
#include "WndNotify.h"

/////////////////////////////////////////////////////////////////////////////
// CTimeTrackerApp:
// Siehe TimeTracker.cpp für die Implementierung dieser Klasse
//

class CTimeTrackerApp : public CWinApp
{
public:
	CWndNotify m_Invisible;
	CTimeTrackerApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTimeTrackerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CTimeTrackerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void AddEntry(CString str);
	NOTIFYICONDATA m_tnid;
	BOOL AddNotifyIcon(DWORD Action=NIM_ADD);
	void AddStartTimeEntry();
};

#ifndef MAIN
	extern CTimeTrackerApp theApp;
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_TimeTracker_H__D0B3EC33_4B0F_11D1_94CD_0020187099A1__INCLUDED_)
