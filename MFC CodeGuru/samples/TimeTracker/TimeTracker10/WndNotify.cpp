// WndNotify.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "TimeTracker.h"
#include "WndNotify.h"
#include "DlgZeiten.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndNotify
IMPLEMENT_DYNCREATE(CWndNotify, CFrameWnd)	


CWndNotify::CWndNotify()
{
}

// Destructor will only be called on normal exit
CWndNotify::~CWndNotify()
{
	// this has to be done, because Win NT4.0 calles the
	// destructor TWO TIMES in the non-debug-version
	// you can prove this by changing "Ende " in "~Ende"
	// and taking a look at you log-file
	static BOOL called=FALSE;
	if (!called)
	{
		theApp.AddEntry("Ende ");
		Shell_NotifyIcon(NIM_DELETE, &theApp.m_tnid); 	
	}
	called = TRUE;
}


BEGIN_MESSAGE_MAP(CWndNotify, CWnd)
	//{{AFX_MSG_MAP(CWndNotify)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_DATEI_ZEITENANZEIGEN, OnDateiZeitenanzeigen)
	ON_WM_ENDSESSION()
	//}}AFX_MSG_MAP
	ON_MESSAGE( 0x4711, OnTaskBarIcon)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CWndNotify 

// Some message came from the TimeTracker icon!
LONG CWndNotify::OnTaskBarIcon(UINT wparam, LONG lparam)
{
	if (wparam != 0x4711)
		return FALSE; 

	switch (lparam)
	{
	case WM_RBUTTONDOWN: // do something
		DisplayPopupMenu();
		TRACE("Icon Message: R Button Down\n");
		break;
	case WM_LBUTTONDOWN: // do something else
		TRACE("Icon Message: L Button Down\n");
		break;
	case WM_LBUTTONDBLCLK:
		TRACE("Icon Message: L Button Double Click\n");
		OnDateiZeitenanzeigen();
		break;
	case WM_RBUTTONDBLCLK:
		TRACE("Icon Message: R Button Double Click\n");
		break;
	default:             // or do nothing
		break;
	}
	return TRUE;
}


void CWndNotify::DisplayPopupMenu()
{
	CMenu menu;
	CPoint point;

	UINT i, prj=theApp.GetProfileInt("Projekte", "Anzahl", 0), f=0;

	CString t;
	GetCursorPos(&point);

	if (menu.LoadMenu(IDR_MAINFRAME))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		// dynamically increment the popup menu to display all projects
		// found in the ini-file.
		for (i=0; i<prj; i++)
		{
			t.Format("%i", i+1);
			t = "Projekt" + t;
			t = theApp.GetProfileString("Projekte", t, "Standard-Projekt");
			f = MF_STRING;
			if (i+1 == theApp.GetProfileInt("Projekte", "nAktiv", 0))
				f |= MF_CHECKED;
			pPopup->AppendMenu(f, WM_USER+i+20, t);
		}

		MENUITEMINFO mii;
		mii.fMask=MIIM_STATE;
		mii.cbSize = sizeof(mii);
		mii.hSubMenu = NULL;
		GetMenuItemInfo(pPopup->GetSafeHmenu(), ID_DATEI_ZEITENANZEIGEN, FALSE, &mii);
//		GetMenuItemInfo(pPopup->GetSafeHmenu(), 1, TRUE, &mii);
		mii.fState = MFS_DEFAULT;
		SetMenuItemInfo(pPopup->GetSafeHmenu(), ID_DATEI_ZEITENANZEIGEN, FALSE, &mii);
//		SetMenuItemInfo(pPopup->GetSafeHmenu(), 1, TRUE, &mii);

		pPopup->TrackPopupMenu(TPM_RIGHTALIGN|TPM_TOPALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON,
			point.x, point.y,
			this); 
	}
}

// cause the window to close and the app to exit
void CWndNotify::OnAppExit() 
{
	SendMessage(WM_CLOSE);	
}

// show registered times dialog
void CWndNotify::OnDateiZeitenanzeigen() 
{
	CDlgZeiten dlg;
	dlg.DoModal();
	
}

// Windows-Session will end soon!
// track the time
// HENCE: CWndNotify destructor will NOT be called!!!
void CWndNotify::OnEndSession(BOOL bEnding) 
{
	if (bEnding)
		theApp.AddEntry("Ende ");

	CWnd::OnEndSession(bEnding);
}

// You want to work on another project?
// no problem, close the actual one and start the other
BOOL CWndNotify::OnCommand(WPARAM wParam, LPARAM lParam) 
{

	if (wParam<WM_USER+20 || wParam>WM_USER+20+theApp.GetProfileInt("Projekte", "Anzahl", 0))
		return CWnd::OnCommand(wParam, lParam);

	if (wParam-WM_USER-19==theApp.GetProfileInt("Projekte", "nAktiv", 0))
		if (MessageBox("Zwischenzeit eintragen?", NULL, MB_YESNO)==IDNO)
			return 1;

	// Altes Projekt abschließen
	theApp.AddEntry("Ende ");
	theApp.WriteProfileInt("Projekte", "nAktiv", wParam-WM_USER-19);
	// neues Projekt anfangen
	theApp.AddEntry("Start");

	// update tooltip text
	theApp.AddNotifyIcon(NIM_MODIFY);

	return 1;
}
