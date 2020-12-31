// adHTMLHelp.h: interface for the CadHTMLHelp class.
//
//////////////////////////////////////////////////////////////////////
/*
	Version 1.1
	letzte Änderung: 21.01.1998
	Status: Entwicklung

	-------------------
	A. Dunkel
	media green GmbH
	www.mediagreen.de
	for free use
	-------------------

history:
	Version 1.0
		19.01.1998
		Grundlegende Implementation

	Version 1.1
		21.01.1998
		Umstellung von ShowHelp auf HH_DISPLAY_TOPIC, da der Aufruf
		über HH_HELP_CONTEXT nicht möglich war. Das Kommando 
		HH_DISPLAY_TOPIC wird zu einem späteren Zeitpunkt implementiert.
		Das einbinden der htmlhelp.lib ist nun nicht mehr nötig, da die
		Bibliothek erst zur Laufzeit nach ihrer Überprüfung geladen wird.
		Dadurch ist das entsprechende Programm auch ohne die HTML-Hile
		lauffähig.
		
*/
//////////////////////////////////////////////////////////////////////

#ifndef __ADHTMLHELP_H__
#define __ADHTMLHELP_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//////////////////////////////////////////////////////////////////////
// 
// from HTML-SDK ( free from Microsoft! )
// http://www.microsoft.com/workshop/author/htmlhelp/
//
#include "htmlhelp.h"

#include "resource.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
// Hook-Klasse für die Anzeige einer HTML-Hilfe-Seite	in einem Dialog
// oder einer Tab-Seite.
//
// Zur Verwendung dieser Klasse muß 
// (1.)
// der entsprechende Dialog zusätzlich
// von der Klasse	CDialogHelperHook abgeleitet werden.
// z.B. 
//		class CPage :public CDialog, CDialogHelperHook
//
// Durch diese Stategie müssen nicht alle Einträge der zugrundeliegenden
// Klasse geändert werden.
// 
// (2.)
// In der Methode OnInitDialog muß folgende Zeile eingetragen werden:
//		ShowHelp( this, _T( "html/helpsite.htm" ));
// Als Name für das aufzurufende "file" ist der Pfad innerhalb der
// Hilfedatei einzutragen, wie er im Hilfeprojekt für die gepackte
// Seite vermerkt wurde.
//
// Status: Entwicklung
//
//////////////////////////////////////////////////////////////////////
class CDialogHelperHook		  
{
protected:
	HWND HtmlHelp(HWND hWndCaller,const CString& 
		strFile,UINT uCommand,DWORD dwData);
	void ShowHelp(CWnd* pWnd, const CString& strFile);
	CString GetHTMLHelpPath();
public:
	UINT PareDlgIDForHelp(UINT nID) ;
};

//////////////////////////////////////////////////////////////////////
class CPageHelp : public CPropertyPage, public CDialogHelperHook
{
	DECLARE_DYNCREATE(CPageHelp)

// Construction
public:
	CPropertySheet* pSheet;
	UINT m_nHelpNameID;
	CPageHelp( UINT nHelpNameID = IDS_HELP_DEFAULT );
	~CPageHelp();

	enum { IDD = IDD_HELP_PAGE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageHelp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//////////////////////////////////////////////////////////////////////
#endif // !defined(__ADHTMLHELP_H__)
