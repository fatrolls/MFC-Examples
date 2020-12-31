// Main.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "StartServiceDlg.h"
#include "RemoteAdminDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma data_seg("Shared")
LONG g_Counter = -1;
#pragma data_seg()

#pragma comment(linker, "/section:Shared,rws")

/////////////////////////////////////////////////////////////////////////////
// CMainApp

BEGIN_MESSAGE_MAP(CMainApp, CWinApp)
	//{{AFX_MSG_MAP(CMainApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainApp construction

CMainApp::CMainApp()
{
	m_pTrayIcon = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMainApp object

CMainApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMainApp initialization

BOOL CMainApp::InitInstance()
{
	if (!(InterlockedIncrement(&g_Counter) == 0))
    {
        ::AfxMessageBox("已经有一个该程序的实例在运行");
        return FALSE;
    }
	SetRegistryKey(_T("VC_net_programs_v1.8"));
	//LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	SetRegistryBase (_T("Settings"));
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
    if(CStartServiceDlg::OnService())
		return FALSE;
	CreateAndShowTrayIcon();
	CMainDlg dlg;
    m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}

int CMainApp::ExitInstance() 
{
	if (m_pTrayIcon != NULL)
		delete m_pTrayIcon;
	BCGCBProCleanUp ();	
	return CWinApp::ExitInstance();
}

bool CMainApp::CreateAndShowTrayIcon()
{
    ASSERT(m_pTrayIcon == NULL); 
	HICON hTrayIcon = ::AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDR_MAINFRAME));
	TCHAR szAppName[_MAX_PATH];
	::LoadString(::AfxGetApp()->m_hInstance, IDS_APP_NAME, szAppName, _MAX_PATH);
	m_pTrayIcon = new CAppSysIcon;
	if (m_pTrayIcon != NULL)
	{
		BOOL bTrayIconCreated = m_pTrayIcon->CreateIcon(hTrayIcon, 1, szAppName);
		BOOL bTrayIconShown   = m_pTrayIcon->ShowIcon(1);
		return (bTrayIconCreated && bTrayIconShown);
	}
	return FALSE;
}

BOOL CMainApp::ShowBalloonMsgInTray(CString strTitle, CString strMsgTxt)
{
	return m_pTrayIcon->ShowBalloon(1, strTitle.GetBuffer(0), strMsgTxt.GetBuffer(0), NIIF_WARNING);
}

//////////////////////////////////////////////////////////////////////
// CAppSysIcon Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppSysIcon::CAppSysIcon()
{

}

CAppSysIcon::~CAppSysIcon()
{

}

void CAppSysIcon::OnRButtonDown(UINT nIconID, CPoint ptMouse)
{
	CMainApp* pApp = (CMainApp*)AfxGetApp();
	CMainDlg* pMainDlg = (CMainDlg*)pApp->m_pMainWnd;
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = pMainDlg->m_aChild.find(pClass);
	ASSERT(it != pMainDlg->m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	if (pDlg == NULL || !IsWindow(pDlg->m_hWnd))
		return;
	if (!pDlg->IsWindowVisible())
		return;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pMachineView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pFrame->m_wndSplitter.GetPane(0, 1);
    CMenu t_Menu;
	DWORD dwData = pMainDlg->m_FuncList.GetItemData(pMainDlg->m_FuncList.GetCurSel());
	CRuntimeClass* pRunTime = (CRuntimeClass*)dwData;
    DWORD dwParam = pMachineView->GetSelectedItemParam();

	if (pRunTime == RUNTIME_CLASS(CRemoteControlDlg))
	{
		BOOL b = t_Menu.LoadMenu(IDR_SYS_TRAY_CONTEXT);
        CMenu* pMenu = t_Menu.GetSubMenu(0);
		pMachineView->SetMenuState(pMenu, 5);
		pAdminView->SetMenuState(pMenu);
		if (!pFrame->m_bTopMost)
		    pMenu->CheckMenuItem(ID_SETTINGS_WINDOW_ALWAYSONTOP, MF_UNCHECKED | MF_BYCOMMAND);
		else
			pMenu->CheckMenuItem(ID_SETTINGS_WINDOW_ALWAYSONTOP, MF_CHECKED | MF_BYCOMMAND);
		OnContextMenu(pMenu, ptMouse, ::AfxGetMainWnd());
	}
}

void CAppSysIcon::OnLButtonDblClk(UINT nIconID, CPoint ptMouse)
{

}


