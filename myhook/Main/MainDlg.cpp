// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "StartServiceDlg.h"
#include "GroupTalkDlg.h"
#include "IoCompletePortTalkDlg.h"
#include "ComFilDlg.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include "NetstatDlg.h"
#include "NetStatisticsDlg.h"
#include "IpHlpMiscDlg.h"
#include "HookApiDlg.h"
#include "LSPDlg.h"
#include "HookFirewallDlg.h"
#include "P2PUdpDlg.h"
#include "SnifferDlg.h"
#include "PingDlg.h"
#include "TaceRouteDlg.h"
#include "NetWakeHostDlg.h"
#include "RemoteAdminDlg.h"
#include "IPHookDriverFirewall.h"
#include "HideProcessDlg.h"

#pragma comment(lib, "iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog
HHOOK CMainDlg::m_hHook = NULL;
CBCGPDialog CMainDlg::m_MessageBox;
CBCGPDialog* CMainDlg::m_pCurDlg = NULL;

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMainDlg::~CMainDlg()
{
	for(map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it=m_aChild.begin(); it!=m_aChild.end(); it++)
	{
		if (it->second.first == NULL)
			continue;
		delete it->second.first;
	}
	//UnhookWindowsHookEx(m_hHook);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_STATIC_PLACE, m_wndPlace);
	DDX_Control(pDX, IDC_LIST_FUNCTION, m_FuncList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_FUNCTION, OnSelchangeListFunction)
	ON_COMMAND(ID_FILE_ADD_MACHINE, OnFileAddMachine)
	ON_COMMAND(ID_FILE_DELETE_MACHINE, OnFileDeleteMachine)
	ON_COMMAND(ID_FILE_EXECUTE_PROCESS, OnFileExecuteProcess)
	ON_COMMAND(ID_FILE_KILL_PROCESS, OnFileKillProcess)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_REFRESHPROCESS, OnFileRefreshprocess)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SHUTDOWN_HALT, OnFileShutdownHalt)
	ON_COMMAND(ID_FILE_SHUTDOWN_REBOOT, OnFileShutdownReboot)
	ON_COMMAND(ID_FILESHUTDOWN_ABORTSHUTDOWN, OnFileshutdownAbortshutdown)
	ON_COMMAND(ID_SETTINGS_TIMERS, OnSettingsTimers)
	ON_COMMAND(ID_SETTINGS_WINDOW_ALWAYSONTOP, OnSettingsWindowAlwaysontop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	InitialFunctionList();

	m_FuncList.SetCurSel(0);
	OnSelchangeListFunction() ;
	
	//SetBackgroundColor(RGB(255, 255, 255));

	//m_hHook = SetWindowsHookEx(WH_CALLWNDPROCRET, (HOOKPROC)DialogBoxCallbackProc, NULL, ::GetCurrentThreadId());
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		int iCurSel = m_FuncList.GetCurSel();
		if (iCurSel == -1)
			return;
		CString str;
		m_FuncList.GetText(iCurSel, str);
		CRect rc;
		m_wndPlace.GetWindowRect(rc);
		ScreenToClient(&rc);
		rc.bottom = rc.top;
		rc.top -= 20;
		dc.FillSolidRect(rc, RGB(0, 255, 0));
		dc.DrawText(str, rc, DT_CENTER|DT_INTERNAL);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMainDlg::InitialFunctionList()
{
	AddDlg(RUNTIME_CLASS(CStartServiceDlg), "启动服务程序");
    AddDlg(RUNTIME_CLASS(CGroupTalkDlg), "多播聊天工具");
    AddDlg(RUNTIME_CLASS(CIoCompletePortTalkDlg), "完成端口TCP聊天工具");
    AddDlg(RUNTIME_CLASS(CComFileDlg), "串口传输文件");
    AddDlg(RUNTIME_CLASS(CNetstatDlg), "Netstat");
    AddDlg(RUNTIME_CLASS(CNetStatisticsDlg), "网络统计数据");
	AddDlg(RUNTIME_CLASS(CIpHlpMiscDlg), "IP助手杂项");
	AddDlg(RUNTIME_CLASS(CIpHlpMiscDlg2), "IP助手杂项2");
	AddDlg(RUNTIME_CLASS(CHookApiDlg), "为API挂钩");
	AddDlg(RUNTIME_CLASS(CLSPDlg), "LSP功能");
	AddDlg(RUNTIME_CLASS(CHookFirewallDlg), "钩子驱动防火墙");
	AddDlg(RUNTIME_CLASS(CP2PUdpServerDlg), "P2P Udp 服务器");
	AddDlg(RUNTIME_CLASS(CP2PUdpClientDlg), "P2P Udp 客户端");
	AddDlg(RUNTIME_CLASS(CSnifferDlg), "嗅探器");
	AddDlg(RUNTIME_CLASS(CPingDlg), "Ping主机");
	AddDlg(RUNTIME_CLASS(CTaceRouteDlg), "路由跟踪");
    AddDlg(RUNTIME_CLASS(CNetWakeHostDlg), "局域网唤醒主机");
	AddDlg(RUNTIME_CLASS(CRemoteControlDlg), "远程控制");
	AddDlg(RUNTIME_CLASS(CIpHookDrvDlg), "钩子驱动防火墙");
	AddDlg(RUNTIME_CLASS(CHideProcessDlg), "隐藏进程");
}

void CMainDlg::OnSelchangeListFunction() 
{
   DWORD dwData = m_FuncList.GetItemData(m_FuncList.GetCurSel());
   CRuntimeClass* pRunTime = (CRuntimeClass*)dwData;
   map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pRunTime);
   ASSERT(it != m_aChild.end());
   CRootDlg* pDlg;
   if (it->second.first == NULL)
   {
	   pDlg = (CRootDlg*)pRunTime->CreateObject();
	   it->second.first = pDlg;
	   pDlg->m_rcWindow = it->second.second;
	   pDlg->Create(pDlg->IDD);
	   pDlg->SetParent(this);
	   CRect rc;
	   m_wndPlace.GetWindowRect(rc);
	   ScreenToClient(&rc);
	   pDlg->MoveWindow(rc);
   }
   else
	   pDlg = (CRootDlg*)it->second.first;
   pDlg->ShowWindow(SW_SHOW);

   m_pCurDlg = pDlg;   

   for(map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it2=m_aChild.begin(); it2!=m_aChild.end(); it2++)
   {
       if (it2 == it)
		   continue;
	   if (it2->second.first == NULL)
		   continue;
	   it2->second.first->ShowWindow(SW_HIDE);
   }
   Invalidate();
}


void CMainDlg::AddDlg(CRuntimeClass *pDlgClass, CString strCaption)
{
	CRect rcWindow;
	m_wndPlace.GetClientRect(rcWindow);
	if (pDlgClass == RUNTIME_CLASS(CHookFirewallDlg))
		rcWindow.right = 600;
	else if (pDlgClass == RUNTIME_CLASS(CNetstatDlg))
		rcWindow.right = 550;
	else if (pDlgClass == RUNTIME_CLASS(CP2PUdpClientDlg))
		rcWindow.right = 536;
	else if (pDlgClass == RUNTIME_CLASS(CSnifferDlg))
		rcWindow.right = 545;
	else if (pDlgClass == RUNTIME_CLASS(CPingDlg))
		rcWindow.right += 30;
	else if (pDlgClass == RUNTIME_CLASS(CRemoteControlDlg))
		rcWindow.right += 400;
	else if (pDlgClass == RUNTIME_CLASS(CIpHookDrvDlg))
		rcWindow.right += 300;
    m_aChild.insert(make_pair(pDlgClass, make_pair((CDialog*)NULL, rcWindow)));
	m_FuncList.InsertString(-1, strCaption);
	m_FuncList.SetItemData(m_FuncList.GetCount()-1, (DWORD)pDlgClass);
}


void CMainDlg::OnFileAddMachine() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILE_ADD_MACHINE, 0);
}

void CMainDlg::OnFileDeleteMachine() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILE_DELETE_MACHINE, 0);
}

void CMainDlg::OnFileExecuteProcess() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILE_EXECUTE_PROCESS, 0);
}

void CMainDlg::OnFileKillProcess() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CRemoteAdminView* pView = (CRemoteAdminView*)pFrame->m_wndSplitter.GetPane(0, 1);
	pView->SendMessage(WM_COMMAND, ID_FILE_KILL_PROCESS, 0);
}

void CMainDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
}

void CMainDlg::OnFileRefreshprocess() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILE_REFRESHPROCESS, 0);
}

void CMainDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	
}

void CMainDlg::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	
}

void CMainDlg::OnFileShutdownHalt() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILE_SHUTDOWN_HALT, 0);
}

void CMainDlg::OnFileShutdownReboot() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILE_SHUTDOWN_REBOOT, 0);
}

void CMainDlg::OnFileshutdownAbortshutdown() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	CMachineView* pView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	pView->SendMessage(WM_COMMAND, ID_FILESHUTDOWN_ABORTSHUTDOWN, 0);
}

void CMainDlg::OnSettingsTimers() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	pFrame->SendMessage(WM_COMMAND, ID_SETTINGS_TIMERS, 0);
}

void CMainDlg::OnSettingsWindowAlwaysontop() 
{
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = m_aChild.find(pClass);
	ASSERT(it != m_aChild.end());
	CRemoteControlDlg* pDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pDlg->m_pFrame;
	pFrame->SendMessage(WM_COMMAND, ID_SETTINGS_WINDOW_ALWAYSONTOP, 0);
}

LRESULT CALLBACK CMainDlg::DialogBoxCallbackProc(int code, WPARAM wParam, LPARAM lparam)
{
	CWPRETSTRUCT*pS = (CWPRETSTRUCT*)lparam;
	if (pS->message == WM_INITDIALOG)
	{
		CBCGPDialog* pWnd = (CBCGPDialog*)CBCGPDialog::FromHandle(pS->hwnd);
		if (pWnd->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CRootDlg)))
			pWnd->SetBackgroundColor(RGB(0, 0, 255));
		else if (pWnd->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CFrameWnd)))
		{
		}
		else
		{
			if (m_MessageBox.m_hWnd != NULL)
				m_MessageBox.UnsubclassWindow();
			m_MessageBox.SubclassWindow(pS->hwnd);
			CDC* pDC = m_pCurDlg->GetDC();
			COLORREF clr = pDC->GetBkColor();
			m_pCurDlg->ReleaseDC(pDC);
            m_MessageBox.SetBackgroundColor(clr);
		}
	}
	return CallNextHookEx(m_hHook, code, wParam, lparam);
}

