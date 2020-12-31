// TimeTracker.cpp : Legt das Klassenverhalten für die Anwendung fest.
//
#define MAIN

#include "stdafx.h"
#include "TimeTracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeTrackerApp

BEGIN_MESSAGE_MAP(CTimeTrackerApp, CWinApp)
	//{{AFX_MSG_MAP(CTimeTrackerApp)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeTrackerApp Konstruktion

CTimeTrackerApp::CTimeTrackerApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CTimeTrackerApp-Objekt

CTimeTrackerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTimeTrackerApp Initialisierung

BOOL CTimeTrackerApp::InitInstance()
{

	CString ClassName = AfxRegisterWndClass(0);

	// Create an invisible parent Window, size is arbitrary
	m_Invisible.CreateEx(WS_EX_TOPMOST, ClassName, _T(""), WS_POPUP, // WS_CAPTION|WS_POPUPWINDOW, 
		0, 0, 100, 25, // Position und Größe
		NULL, NULL);

	m_pMainWnd = &m_Invisible;

	AddNotifyIcon();

	AddStartTimeEntry();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTimeTrackerApp-Befehle

BOOL CTimeTrackerApp::AddNotifyIcon(DWORD Action/*=NIM_ADD*/)
{
	UINT uID=0x4711;
	CString t;
	t=GetProfileString("Projekte", "nAktiv", "1");
	t = "Projekt" + t;
	t=GetProfileString("Projekte", t, "Standard-Projekt");

    m_tnid.cbSize = sizeof(NOTIFYICONDATA); 
    m_tnid.hWnd = m_Invisible.m_hWnd; 
    m_tnid.uID = uID; 
    m_tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
    m_tnid.uCallbackMessage = 0x4711; 
    m_tnid.hIcon = LoadIcon(IDR_MAINFRAME);
    lstrcpyn(m_tnid.szTip, t, sizeof(m_tnid.szTip)); 
 
    return Shell_NotifyIcon(Action, &m_tnid); 
}


void CTimeTrackerApp::AddStartTimeEntry()
{
	AddEntry("Start");

}

void CTimeTrackerApp::AddEntry(CString kenn)
{
	CFile f;

	CString FileName;
	FileName=theApp.GetProfileString("Projekte", "nAktiv", "1");
	FileName = "Datei" + FileName;
	FileName=theApp.GetProfileString("Projekte", FileName, "Standard-Projekt.abz");
	
	if (!f.Open(FileName, CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate))
		return;
	f.SeekToEnd();

	CString str;
	CTime t = CTime::GetCurrentTime();
	str.Format("%s = %02i. %02i. %i, %02i:%02i.%02i\n", kenn, t.GetDay(), t.GetMonth(), t.GetYear(), t.GetHour(), t.GetMinute(), t.GetSecond());

	f.Write(str.GetBuffer(0), str.GetLength());
	str.ReleaseBuffer();
}

