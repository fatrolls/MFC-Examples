// WINRWPM32.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ExMultiDocTemplate.h"
#include "MIDIGenerator.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "IpFrame.h"
#include "WINRWPM32Doc.h"
#include "WINRWPM32View.h"
#include "Splash.h"
#include "MathStr.h"
#include "Hyperlink.h"
#include <locale.h>
#include <dos.h>
#include <direct.h>
#include <regstr.h>
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinRWPM32App

BEGIN_MESSAGE_MAP(CWinRWPM32App, CWinApp)
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
	//{{AFX_MSG_MAP(CWinRWPM32App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinRWPM32App construction

CWinRWPM32App::CWinRWPM32App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWinRWPM32App object

CWinRWPM32App theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {848F16E0-749A-11D0-B74E-444553540000}
static const CLSID clsid =
{ 0x848f16e0, 0x749a, 0x11d0, { 0xb7, 0x4e, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

/////////////////////////////////////////////////////////////////////////////
// CWinRWPM32App initialization

void CWinRWPM32App::Registry_Uninstall(bool install)
{
	char keystr[255];
	strcpy(keystr, REGSTR_PATH_UNINSTALL);
	strcat(keystr, _T("\\") );
	strcat(keystr, m_pszAppName);
	if (install)
	{
		HKEY hkey;
		char uninststr[255];
		::GetModuleFileName(m_hInstance, uninststr, sizeof(uninststr)-1);
		strcat(uninststr, _T(" /uninstall"));
		::RegCreateKey(HKEY_LOCAL_MACHINE, keystr, &hkey);
		::RegSetValueEx(hkey, REGSTR_VAL_UNINSTALLER_DISPLAYNAME, 0, REG_SZ, (BYTE*)_T("WIN-RWPM 32-Bit Application (only remove registry entries)"), 0);
		::RegSetValueEx(hkey, REGSTR_VAL_UNINSTALLER_COMMANDLINE, 0, REG_SZ, (BYTE*)uninststr, 0);
		strcat(uninststr, _T("quiet"));
		::RegSetValueEx(hkey, "QuietUninstallString", 0, REG_SZ, (BYTE*)uninststr, 0);
		::RegCloseKey(hkey);
	}
	else
	{
		DelRegTree(HKEY_LOCAL_MACHINE, keystr);
	}
}

void CWinRWPM32App::Registry_Software(bool install)
{
	char keystr[255];
	char enumkeystr[255];
	HKEY hkey;
	strcpy(keystr, _T("Software\\Andreas Jaeger\\"));
	strcat(keystr, m_pszAppName);
	if (install)
	{
		strcat(keystr, _T("\\1.0"));
		::RegCreateKey(HKEY_LOCAL_MACHINE, keystr, &hkey);
		::RegCloseKey(hkey);
	}
	else
	{
		DelRegTree(HKEY_CURRENT_USER, keystr);
		strcat(keystr, _T("\\1.0"));
		DelRegTree(HKEY_LOCAL_MACHINE, keystr);
		// übergeordnete Schlüssel löschen, sofern keine weiteren Einträge
		// in HKEY_CURRENT_USER
		strcpy(keystr, _T("Software\\Andreas Jaeger"));
		::RegOpenKey(HKEY_CURRENT_USER, keystr, &hkey);
		int ret = ::RegEnumKey(hkey, 0, enumkeystr, sizeof(enumkeystr)-1);
		::RegCloseKey(hkey);
		if (ret==ERROR_NO_MORE_ITEMS)
		{
			DelRegTree(HKEY_CURRENT_USER, keystr);
		}
		// in HKEY_LOCAL_MACHINE
		strcpy(keystr, _T("Software\\Andreas Jaeger\\"));
		strcat(keystr, m_pszAppName);
		::RegOpenKey(HKEY_LOCAL_MACHINE, keystr, &hkey);
		ret = ::RegEnumKey(hkey, 0, enumkeystr, sizeof(enumkeystr)-1);
		::RegCloseKey(hkey);
		if (ret==ERROR_NO_MORE_ITEMS)
		{
			DelRegTree(HKEY_LOCAL_MACHINE, keystr);
		}
		// noch weiter nach oben in HKEY_LOCAL_MACHINE
		strcpy(keystr, _T("Software\\Andreas Jaeger"));
		::RegOpenKey(HKEY_LOCAL_MACHINE, keystr, &hkey);
		ret = ::RegEnumKey(hkey, 0, enumkeystr, sizeof(enumkeystr)-1);
		::RegCloseKey(hkey);
		if (ret==ERROR_NO_MORE_ITEMS)
		{
			DelRegTree(HKEY_LOCAL_MACHINE, keystr);
		}
	}
}

BOOL CWinRWPM32App::InitInstance()
{
	// CG: The following block was inserted by 'Status Bar' component.
	{
		//Set up date and time defaults so they're the same as system defaults
		setlocale(LC_ALL, "");
	}

	// CG: The following block was added by the Splash Screen component.
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Andreas Jaeger"));

	// Initialize static members of CGDIThread
	InitializeCriticalSection(&CGDIThread::m_csGDILock);

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CExMultiDocTemplate(
		IDR_WINRWPTYPE,
		RUNTIME_CLASS(CWinRWPM32Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CWinRWPM32View));
	pDocTemplate->SetContainerInfo(IDR_WINRWPTYPE_CNTR_IP);
	pDocTemplate->SetServerInfo(
		IDR_WINRWPTYPE_SRVR_EMB, IDR_WINRWPTYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);


	if (stricmp(m_lpCmdLine, _T("/uninstall"))==0 || stricmp(m_lpCmdLine, _T("/uninstallquiet"))==0)
	{
		// This does not work fine under NT 4.0, so we want to use InstallShield
		//Registry_Uninstall(false);
		//Registry_Software(false);

		COleTemplateServer::UnregisterAll();

		UnregisterShellFileTypes();

		Unregister();
		if (stricmp(m_lpCmdLine, _T("/uninstallquiet"))!=0)
			AfxMessageBox(_T("Deinstallation successfully"));
		return TRUE;
	}

	// Einträge in der Registry setzen, u.a. zum Deinstallieren
	// This does not work fine under NT 4.0, so we want to use InstallShield
	//Registry_Uninstall(true);
	//Registry_Software(true);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);


	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	// CG: This line inserted by 'Tip of the Day' component.
	ShowTipAtStartup();

	// CG: This block was added by the MAPI component
	/* TRY TO DELETE THIS BLOCK
	{
		// TODO: Add a menu item for sending mail:
		//   1. In ResourceView, open your application's menu resource
		//   2. Select the File submenu
		//   3. Double-click on the blank item at the bottom of the submenu
		//   4. Assign the new item an ID: ID_FILE_SEND_MAIL
		//   5. Assign the item a Caption: Sen&d...

		// TODO: Delete this entire block of code.
		// The code below is only for temporary use, until the above
		// instructions have been carried out. This code will not work
		// correctly if your application has multiple menus or is an
		// MDI application and starts up maximized.

		CMenu* pMenu = NULL;
		CMenu* pFileMenu = NULL;
		if ((m_pMainWnd != NULL) &&
			((pMenu = m_pMainWnd->GetMenu()) != NULL) &&
			((pFileMenu = pMenu->GetSubMenu(0)) != NULL))
		{
			// Locate the "Sen&d..." menu item
			for (int i = 0, nLength = pFileMenu->GetMenuItemCount();
				i<nLength; i++)
			{
				CString strSend;
				pFileMenu->GetMenuString(i, strSend, MF_BYPOSITION);
				if (strSend == _T("Sen&d...")) break;
			}

			if (i == nLength)
			{
				// Didn't find Sen&d... menu item, so add one.
				pFileMenu->InsertMenu(nLength-1, MF_BYPOSITION);
				pFileMenu->InsertMenu(nLength-1, MF_BYPOSITION,
				ID_FILE_SEND_MAIL, _T("Sen&d..."));
			}
		}
	}
	BLOCK DELETED
	*/

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX1 };
	CAnimateCtrl	m_AnimateCtrl;
	CHyperLink      m_eMail;
	CHyperLink      m_HomePage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ANIMATE1, m_AnimateCtrl);
	DDX_Control(pDX, IDC_EMAIL, m_eMail);
	DDX_Control(pDX, IDC_HOMEPAGE, m_HomePage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_RBUTTONDBLCLK()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CWinRWPM32App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWinRWPM32App commands

BOOL CWinRWPM32App::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	// CG:  This was added by System Info Component.

	m_eMail.SetURL(_T("mailto:JaegerA@aol.com"));
	m_eMail.SetColours(m_eMail.GetLinkColour(), RGB(255, 0, 0));
	m_eMail.SetUnderline(FALSE);
	m_eMail.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HYPERLINK));

	m_HomePage.SetURL(_T("http://members.aol.com/JaegerA"));
	m_HomePage.SetColours(m_eMail.GetLinkColour(), RGB(255, 0, 0));
	m_HomePage.SetUnderline(FALSE);
	m_HomePage.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HYPERLINK));

	// CG: Following block was added by System Info Component.
	{
		CString strFreeDiskSpace;
		CString strFreeMemory;
		CString strFmt;

		// Fill available memory
		MEMORYSTATUS MemStat;
		MemStat.dwLength = sizeof(MEMORYSTATUS);
		GlobalMemoryStatus(&MemStat);
		strFmt.LoadString(CG_IDS_PHYSICAL_MEM);
		strFreeMemory.Format(strFmt, MemStat.dwTotalPhys / 1024L);

		//TODO: Add a static control to your About Box to receive the memory
		//      information.  Initialize the control with code like this:
		// SetDlgItemText(IDC_PHYSICAL_MEM, strFreeMemory);

		// Fill disk free information
		struct _diskfree_t diskfree;
		int nDrive = _getdrive(); // use current default drive
		if (_getdiskfree(nDrive, &diskfree) == 0)
		{
			strFmt.LoadString(CG_IDS_DISK_SPACE);
			strFreeDiskSpace.Format(strFmt,
				(DWORD)diskfree.avail_clusters *
				(DWORD)diskfree.sectors_per_cluster *
				(DWORD)diskfree.bytes_per_sector / (DWORD)1024L,
				nDrive-1 + _T('A'));
		}
		else
			strFreeDiskSpace.LoadString(CG_IDS_DISK_SPACE_UNAVAIL);

		//TODO: Add a static control to your About Box to receive the memory
		//      information.  Initialize the control with code like this:
		// SetDlgItemText(IDC_DISK_SPACE, strFreeDiskSpace);
	}

	return TRUE;	// CG:  This was added by System Info Component.

}

void CWinRWPM32App::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CTipDlg dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}

}

void CWinRWPM32App::ShowTipOfTheDay(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CTipDlg dlg;
	dlg.DoModal();

}

int CWinRWPM32App::ExitInstance() 
{
	if (stricmp(m_lpCmdLine, _T("/uninstall"))==0)
	{
	}
	else
	{
		DeleteCriticalSection(&CGDIThread::m_csGDILock);
		CloseHandle(CGDIThread::m_hAnotherDead);
	}

	return CWinApp::ExitInstance();
}


void CAboutDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// Wenn in die linke obere Ecke des About-Dialogs mit der rechten
	// Maustaste doppelgeklickt wird, erhält man Infos zu den Programmierern
	if (point.x<=5 && point.y<=5)
	{
		if (m_AnimateCtrl.Open(IDR_AVI1))
		{
			m_AnimateCtrl.Play(0, UINT(-1), UINT(-1));
		}
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
	}
	CDialog::OnRButtonDblClk(nFlags, point);
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	PlaySound(NULL, NULL, 0);
}
