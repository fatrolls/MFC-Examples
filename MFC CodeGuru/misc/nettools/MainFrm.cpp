// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "afxmt.h"
#include "nettools.h"
#include "MainFrm.h"
#include "PingDlg.h"
#include "NetstatDlg.h"
//#include "NbstatDlg.h"
//#include "TracertDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_COMMANDS_PING, OnCommandsPing)
	ON_COMMAND(ID_COMMANDS_NETSTAT, OnCommandsNetstat)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_PING, OnUpdateCommandsPing)
	ON_COMMAND(ID_COMMANDS_STOPPING, OnCommandsStopPing)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_STOPPING, OnUpdateCommandsStopPing)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_NETSTAT, OnUpdateCommandsNetstat)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_STOPSTAT, OnUpdateCommandsStopstat)
	ON_COMMAND(ID_COMMANDS_STOPSTAT, OnCommandsStopstat)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_PING_DONE,OnPingDone)
	ON_MESSAGE(WM_USER_PING_PRINT,OnPingPrint)
	ON_MESSAGE(WM_USER_INET_DONE,OnInetDone)
	ON_MESSAGE(WM_USER_INET_PRINT,OnInetPrint)
	ON_MESSAGE(WM_USER_INET_TABS,OnInetTabs)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


CCriticalSection m_CritWinLb;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	

	memset(m_PingThreadInfo.hostname,0,sizeof(m_PingThreadInfo.hostname));
	

	m_PingThreadInfo.m_hEventStartPing =
		CreateEvent(NULL, FALSE, FALSE, NULL);
	

	m_PingThreadInfo.m_hEventPingDone =
		CreateEvent(NULL, TRUE, TRUE, NULL);
	
	m_PingThreadInfo.m_hEventKillPing =
		CreateEvent(NULL, FALSE, FALSE, NULL);
	
	m_PingThreadInfo.m_hEventPingDead = 
		CreateEvent(NULL, FALSE, FALSE, NULL);
	
	

	m_pPingWorkerThread = NULL;
	m_pPingWorkerThread = new CPingThread(&m_PingThreadInfo);
	if (!m_pPingWorkerThread->Start())
	{
		AfxMessageBox("Cannot Start Ping");
		delete m_pPingWorkerThread;
		m_pPingWorkerThread = NULL;
		return;
	}
	m_PingStop_ButtEnabled = FALSE;
	m_Ping_ButtEnabled = TRUE;


	//
	// Inet Thread
	//

	m_InetThreadInfo.m_hEventStartInet =
		CreateEvent(NULL, FALSE, FALSE, NULL);
	

	m_InetThreadInfo.m_hEventInetDone =
		CreateEvent(NULL, TRUE, TRUE, NULL);
	
	m_InetThreadInfo.m_hEventKillInet =
		CreateEvent(NULL, FALSE, FALSE, NULL);
	
	m_InetThreadInfo.m_hEventInetDead = 
		CreateEvent(NULL, FALSE, FALSE, NULL);
	
	
	m_pInetWorkerThread = NULL;
	m_pInetWorkerThread = new CInetThread(&m_InetThreadInfo);
	if (!m_pInetWorkerThread->Start())
	{
		AfxMessageBox("Cannot Start Inet");
		delete m_pInetWorkerThread;
		m_pInetWorkerThread = NULL;
		return;
	}
	m_InetStop_ButtEnabled = FALSE;
	m_Inet_ButtEnabled = TRUE;
	//
	// end
	//
	
}

CMainFrame::~CMainFrame()
{

	//DWORD dwInetExitCode;
	if (m_pInetWorkerThread != NULL)
		//&&
		//GetExitCodeThread(m_pInetWorkerThread->m_hThread,
		//&dwInetExitCode) &&
		//dwInetExitCode == STILL_ACTIVE)
	{
		
		m_pInetWorkerThread->CleanUp();  //stop icmp/tcp
			
		// Kill the worker thread by setting the "kill thread" event.
		// See comment in OnKillWorkerThread for explanation of the sequence
		// of the "kill thread" and "start recalc" events.
		SetEvent(m_InetThreadInfo.m_hEventKillInet);
		SetEvent(m_InetThreadInfo.m_hEventStartInet);
		WaitForSingleObject(m_InetThreadInfo.m_hEventInetDead,
							INFINITE);
		
	}
		// In this application, the document owns the worker thread.
	// The document's destructor is responsible for killing the active worker
	// thread.

	// It's a good idea to wait for the worker thread to notify via a
	// "thread killed" event that it has killed itself. Otherwise, in the case
	// where the app is terminating, is possible (even if unlikely) that it
	// will detect a memory leak of the CWinThread object before the
	// CWinThread object has had a chance to auto-delete itself.

	//DWORD dwPingExitCode;
	if (m_pPingWorkerThread != NULL)
		//&&
		//GetExitCodeThread(m_pPingWorkerThread->m_hThread,
		//&dwPingExitCode) &&
		//dwPingExitCode == STILL_ACTIVE)
	{
		m_pPingWorkerThread->CleanUp();  //stop icmp/tcp
	
		// Kill the worker thread by setting the "kill thread" event.
		// See comment in OnKillWorkerThread for explanation of the sequence
		// of the "kill thread" and "start recalc" events.
		SetEvent(m_PingThreadInfo.m_hEventKillPing);
		SetEvent(m_PingThreadInfo.m_hEventStartPing);
		WaitForSingleObject(m_PingThreadInfo.m_hEventPingDead,
							INFINITE);
		
	}
	delete m_pPingWorkerThread;
	delete m_pInetWorkerThread;
	//
	// terminate inet thread
	//
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_wndListBox.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL
						| LBS_USETABSTOPS | WS_HSCROLL,
						CRect(0,0,0,0),
						this,
						LISTBOX_WINDOW);


	INT Tabs[7]  = {32,100,100,100,100,100,100};
	m_wndListBox.SetTabStops(7,Tabs);
	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
	
	
	CFrameWnd::RecalcLayout(bNotify);
	CRect rc;
	RepositionBars(0,
					0xFFFF,
					LISTBOX_WINDOW,
					CWnd::reposQuery,
					&rc);
	if (IsWindow(m_wndListBox.GetSafeHwnd()))
	{
		m_wndListBox.MoveWindow(&rc,FALSE);
	}

}

void CMainFrame::OnCommandsPing() 
{

	if (m_pPingWorkerThread == NULL)
	{
		AfxMessageBox("Ping Not Started");
		return;
	}
	
	CPingDlg pingdlg(this);
	

	pingdlg.m_ping_hostname = m_save_hostname;
	m_PingThreadInfo.opt_rrdata.RemoveAll();

	pingdlg.m_lpPingParms = &m_PingThreadInfo;

	if (pingdlg.DoModal() == IDOK)
	{
		
		m_save_hostname = pingdlg.m_ping_hostname;
		
		// The events are initially set or reset in the CreateEvent call;
		// but they may be left in an improperly initialized state if
		// a worker thread has been previously started and then prematurely
		// killed.  Set/reset the events to the proper initial state.
		// Set the "start recalc" event last, since it is the event the
		// triggers the starting of the worker thread recalculation.
		// OnPingDone() will be called by the frame when the 
		//thread sends a WM_USER_PING_DONE message.
		
		m_Ping_ButtEnabled = FALSE; // turn off start
		m_PingStop_ButtEnabled = TRUE; // turn on stop

		m_PingThreadInfo.m_hwndNotifyPingDone = 
			AfxGetMainWnd()->m_hWnd;

    	
		ResetEvent(m_PingThreadInfo.m_hEventPingDone);
		ResetEvent(m_PingThreadInfo.m_hEventKillPing);
		ResetEvent(m_PingThreadInfo.m_hEventPingDead);
		SetEvent(m_PingThreadInfo.m_hEventStartPing);
		
		
	}
	
}

LRESULT CMainFrame::OnPingPrint(WPARAM wParam,LPARAM lParam) 
{
	CHAR *prtline;;
	
	
	prtline = (CHAR*)lParam;
	//CString prt;
	//CPingThreadParmList *pPTPparm;
	//CStringArray *pPTPparm;
	//pPTPparm = (CPingThreadParmList*)lParam;
	//pPTPparm = (CStringArray*)lParam;

	m_CritWinLb.Lock();
	//for (int x = 0;x<pPTPparm->GetSize();x++)
	//{
	//	m_wndListBox.InsertString(-1,pPTPparm->GetAt(x));
	//}
	m_wndListBox.InsertString(-1,prtline);
	m_CritWinLb.Unlock();

	//pPTPparm->RemoveAll();
	return 0;
}



LRESULT CMainFrame::OnPingDone(WPARAM wParam,LPARAM lParam) 
{
	m_CritWinLb.Lock();

	m_wndListBox.InsertString(-1,"- Ping Done");
		
	m_CritWinLb.Unlock();

	m_Ping_ButtEnabled = TRUE;
	m_PingStop_ButtEnabled = FALSE;
	return 0;
}

LRESULT CMainFrame::OnInetDone(WPARAM wParam,LPARAM lParam) 
{
	m_CritWinLb.Lock();

	m_wndListBox.InsertString(-1,"- Inet Done");
		
	m_CritWinLb.Unlock();

	m_Inet_ButtEnabled = TRUE;
	m_InetStop_ButtEnabled = FALSE;
	return 0;
}

LRESULT CMainFrame::OnInetTabs(WPARAM wParam,LPARAM lParam) 
{
	LPINT tabs;
	tabs = (LPINT)lParam;

	m_CritWinLb.Lock();

	m_wndListBox.SetTabStops(7,tabs);
		
	m_CritWinLb.Unlock();

	
	return 0;
}

LRESULT CMainFrame::OnInetPrint(WPARAM wParam,LPARAM lParam) 
{
	CHAR *prtline;;
	
	
	prtline = (CHAR*)lParam;
	
	
	m_CritWinLb.Lock();

	m_wndListBox.InsertString(-1,prtline);
		
	m_CritWinLb.Unlock();


	return 0;
}


void CMainFrame::OnCommandsNetstat() 
{
	if (m_pInetWorkerThread == NULL)
	{
		AfxMessageBox("Inet Not Started");
		return;
	}

	CNetstatDlg netstatdlg(this);
	netstatdlg.m_lpInetParms = &m_InetThreadInfo;
	if (netstatdlg.DoModal() == IDOK)
	{
		
		// The events are initially set or reset in the CreateEvent call;
		// but they may be left in an improperly initialized state if
		// a worker thread has been previously started and then prematurely
		// killed.  Set/reset the events to the proper initial state.
		// Set the "start recalc" event last, since it is the event the
		// triggers the starting of the worker thread recalculation.
		// OnPingDone() will be called by the frame when the 
		//thread sends a WM_USER_PING_DONE message.
		
		m_Inet_ButtEnabled = FALSE; // turn off start
		m_InetStop_ButtEnabled = TRUE; // turn on stop

    	m_InetThreadInfo.m_hwndNotifyInetDone = 
			AfxGetMainWnd()->m_hWnd;

		//SetEvent(m_InetThreadInfo.m_hEventInetDone);
		ResetEvent(m_InetThreadInfo.m_hEventInetDone);
		ResetEvent(m_InetThreadInfo.m_hEventKillInet);
		ResetEvent(m_InetThreadInfo.m_hEventInetDead);
		SetEvent(m_InetThreadInfo.m_hEventStartInet);
		
		
	}
	
	
	
}


void CMainFrame::OnFileNew() 
{
	m_CritWinLb.Lock();
	m_wndListBox.ResetContent();
	m_CritWinLb.Unlock();
	
	
}



void CMainFrame::OnUpdateCommandsPing(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Ping_ButtEnabled);
	
}

void CMainFrame::OnCommandsStopPing() 
{
	if (m_pPingWorkerThread == NULL)
	{
		AfxMessageBox("Ping Not Started");
		return;
	}
	m_pPingWorkerThread->Kill();

	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateCommandsStopPing(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_PingStop_ButtEnabled);
}

void CMainFrame::OnUpdateCommandsNetstat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Inet_ButtEnabled);
}

void CMainFrame::OnUpdateCommandsStopstat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_InetStop_ButtEnabled);
}

void CMainFrame::OnCommandsStopstat() 
{
	// TODO: Add your command handler code here
	if (m_pInetWorkerThread == NULL)
	{
		AfxMessageBox("Inet Not Started");
		return;
	}
	m_pInetWorkerThread->Kill();
}


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	DWORD wrc;
	CHAR line[128];

	if (m_pInetWorkerThread != NULL)
	{
		m_pInetWorkerThread->Kill();
		wrc = WaitForSingleObject(m_InetThreadInfo.m_hEventInetDone,
							0);

		if (wrc != WAIT_OBJECT_0)
		{
			strcpy(line,"Inet Still Running! Being Terminated");
			OnInetPrint(0,(LONG)line);
			return;
		}
	}

	if (m_pPingWorkerThread != NULL)
	{
		m_pPingWorkerThread->Kill();
		wrc = WaitForSingleObject(m_PingThreadInfo.m_hEventPingDone,
							0);

		if (wrc != WAIT_OBJECT_0)
		{
			strcpy(line,"Ping Still Running! Being Terminated");
			OnPingPrint(0,(LONG)line);
			return;
		}
	}

	
	
	CFrameWnd::OnClose();
}
