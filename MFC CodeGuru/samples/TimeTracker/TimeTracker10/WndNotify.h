#ifndef AFX_WNDNOTIFY_H__D0B3EC44_4B0F_11D1_94CD_0020187099A1__INCLUDED_
#define AFX_WNDNOTIFY_H__D0B3EC44_4B0F_11D1_94CD_0020187099A1__INCLUDED_

// WndNotify.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CWndNotify 

class CWndNotify : public CFrameWnd
{

	DECLARE_DYNCREATE(CWndNotify)	

// Konstruktion
public:
	CWndNotify();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CWndNotify)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
public:
	void DisplayPopupMenu();
	virtual ~CWndNotify();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CWndNotify)
	afx_msg void OnAppExit();
	afx_msg void OnDateiZeitenanzeigen();
	afx_msg void OnEndSession(BOOL bEnding);
	//}}AFX_MSG
	afx_msg LONG OnTaskBarIcon(UINT wparam, LONG lparam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_WNDNOTIFY_H__D0B3EC44_4B0F_11D1_94CD_0020187099A1__INCLUDED_
