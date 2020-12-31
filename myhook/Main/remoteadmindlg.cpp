// RemoteAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "RemoteAdminDlg.h"
#include "MainDlg.h"
#include <winsvc.h>
#include <winsock2.h>
#include "Helper.h"

#pragma comment(lib, "Mpr.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminDlg

IMPLEMENT_DYNCREATE(CRemoteAdminFrame, CFrameWnd)

CRemoteAdminFrame::CRemoteAdminFrame()
{
	m_bUpdateProcessList  = TRUE;
    m_iUpdateProcessDelay = 10000;  // in milli secs
    m_iShutdownDelay      = 50000; // in milli secs
	m_bTopMost = false;
}

CRemoteAdminFrame::~CRemoteAdminFrame()
{
}


BEGIN_MESSAGE_MAP(CRemoteAdminFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CRemoteAdminFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_SETTINGS_TIMERS, OnSettingsTimers)
	ON_WM_CLOSE()
	ON_COMMAND(ID_SETTINGS_WINDOW_ALWAYSONTOP, OnSettingsWindowAlwaysontop)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_VIEW_LARGEICON, ID_VIEW_DETAILS, OnChangeRightViewStyle)
	ON_COMMAND_RANGE(WM_SET_STATUSBAR_TEXT, ID_VIEW_DETAILS, OnSetStatusBarText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CRemoteControlDlg dialog
IMPLEMENT_DYNCREATE(CRemoteControlDlg, CRootDlg)


CRemoteControlDlg::CRemoteControlDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CRemoteControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pFrame = NULL;
}


void CRemoteControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteControlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteControlDlg, CRootDlg)
	//{{AFX_MSG_MAP(CRemoteControlDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CMachineView

IMPLEMENT_DYNCREATE(CMachineView, CTreeView)

CMachineView::CMachineView()
{
	m_bMouseIn = false;
	m_hMachineViewRoot = NULL;
}

CMachineView::~CMachineView()
{
}


BEGIN_MESSAGE_MAP(CMachineView, CTreeView)
	//{{AFX_MSG_MAP(CMachineView)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_ADD_MACHINE, OnFileAddMachine)
	ON_COMMAND(ID_FILE_DELETE_MACHINE, OnFileDeleteMachine)
	ON_UPDATE_COMMAND_UI(ID_FILE_DELETE_MACHINE, OnUpdateFileDeleteMachine)
	ON_WM_RBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_FILE_SHUTDOWN_HALT, OnFileShutdownHalt)
	ON_UPDATE_COMMAND_UI(ID_FILE_SHUTDOWN_HALT, OnUpdateFileShutdownHalt)
	ON_COMMAND(ID_FILE_SHUTDOWN_REBOOT, OnFileShutdownReboot)
	ON_UPDATE_COMMAND_UI(ID_FILE_SHUTDOWN_REBOOT, OnUpdateFileShutdownReboot)
	ON_COMMAND(ID_FILESHUTDOWN_ABORTSHUTDOWN, OnFileshutdownAbortshutdown)
	ON_UPDATE_COMMAND_UI(ID_FILESHUTDOWN_ABORTSHUTDOWN, OnUpdateFileshutdownAbortshutdown)
	ON_COMMAND(ID_FILE_EXECUTE_PROCESS, OnFileExecuteProcess)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXECUTE_PROCESS, OnUpdateFileExecuteProcess)
	ON_UPDATE_COMMAND_UI(ID_FILE_ADD_MACHINE, OnUpdateFileAddMachine)
	ON_COMMAND(ID_FILE_REFRESHPROCESS, OnFileRefreshprocess)
	ON_UPDATE_COMMAND_UI(ID_FILE_REFRESHPROCESS, OnUpdateFileRefreshprocess)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	//ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMachineView drawing

void CMachineView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMachineView diagnostics

#ifdef _DEBUG
void CMachineView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMachineView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMachineView message handlers
/////////////////////////////////////////////////////////////////////////////
// CMachineDoc

IMPLEMENT_DYNCREATE(CMachineDoc, CDocument)

CMachineDoc::CMachineDoc()
{
	m_pUpdateThread    = NULL;
	m_pVisualProgressThread = NULL;
	m_ConnectedHostList = NULL;
}

BOOL CMachineDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
		return FALSE;
	CMainDlg* pDlg = (CMainDlg*)AfxGetMainWnd();
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = pDlg->m_aChild.find(pClass);
	CRemoteControlDlg* pMyDlg = (CRemoteControlDlg*)it->second.first;
	if (pMyDlg == NULL)
		return TRUE;
	CRemoteAdminFrame* pFrame = pMyDlg->m_pFrame;
	if (pFrame == NULL)
		return TRUE;
    CMachineView* pMachineView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pFrame->m_wndSplitter.GetPane(0, 1);
	
    ConnectInfo* pConnectInfo      = new ConnectInfo;
	pConnectInfo->pDoc             = this;
	pConnectInfo->pMachineView     = pMachineView;
	pConnectInfo->pAdminView       = pAdminView;
	pConnectInfo->strIP            = "";
	pConnectInfo->strPwd           = "";
	pConnectInfo->strUserName      = "";
	if (m_pUpdateThread == NULL)
		m_pUpdateThread = AfxBeginThread(AFX_THREADPROC(UpdateProcessListForAllMachines), pConnectInfo, 
		                                        THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	return TRUE;
}

CMachineDoc::~CMachineDoc()
{
}


BEGIN_MESSAGE_MAP(CMachineDoc, CDocument)
	//{{AFX_MSG_MAP(CMachineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMachineDoc diagnostics

#ifdef _DEBUG
void CMachineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMachineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMachineDoc serialization

void CMachineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CStringArray aHosts;;
        m_RemoteAdministrator.GetConnectHostIP(aHosts);
        ar << aHosts.GetSize();
        for (int i = 0; i < aHosts.GetSize(); ++i)
        {
            CMachineInfo* pMachineInfo = m_RemoteAdministrator.GetMachineInfo(aHosts[i]);
            ar << pMachineInfo;
        }
	}
	else
	{
		if (m_ConnectedHostList != NULL)
		{
			POSITION pos = m_ConnectedHostList->GetHeadPosition();
			CMachineInfo* pInfo;
			while(pos)
			{
				pInfo = m_ConnectedHostList->GetNext(pos);
				if (pInfo != NULL)
					delete pInfo;
			}
			m_ConnectedHostList->RemoveAll();
			delete m_ConnectedHostList;
		}

		m_ConnectedHostList   = new MachineInfoList;
        CMachineInfo* pMachineInfo     = NULL;
		int iCount;
        ar >> iCount;

        for (int i = 0; i < iCount; ++i)
        {
            ar >> pMachineInfo;
            m_ConnectedHostList->AddTail(pMachineInfo);
        }
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMachineDoc commands

BOOL CRemoteControlDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	CMainApp* pApp = (CMainApp*)AfxGetApp();
	pApp->LoadStdProfileSettings(); 
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CRemoteControlDocTemplate();
	pApp->AddDocTemplate(pDocTemplate);
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	ASSERT(pos != NULL);
	CSingleDocTemplate* pTemplate = (CSingleDocTemplate*)pApp->GetNextDocTemplate(pos);
	ASSERT(pTemplate != NULL);
	while(!pTemplate->IsKindOf(RUNTIME_CLASS(CRemoteControlDocTemplate)))
		pTemplate = (CSingleDocTemplate*)pApp->GetNextDocTemplate(pos);
    ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CRemoteControlDocTemplate)));
	pApp->m_pMainWnd = NULL;
	pTemplate->OpenDocumentFile(NULL, TRUE);
	m_pFrame = (CRemoteAdminFrame*)pApp->m_pMainWnd;
	CMainDlg* pParent = (CMainDlg*)GetParent();
	pApp->m_pMainWnd = pParent;
    m_pFrame->SetParent(this);
	m_pFrame->ModifyStyle(WS_BORDER, 0);
	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right += 22;
	m_pFrame->MoveWindow(rcClient);

	return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminView

IMPLEMENT_DYNCREATE(CRemoteAdminView, CListView)

CRemoteAdminView::CRemoteAdminView()
{
	m_strProcessID = "0";
}

CRemoteAdminView::~CRemoteAdminView()
{
}


BEGIN_MESSAGE_MAP(CRemoteAdminView, CListView)
	//{{AFX_MSG_MAP(CRemoteAdminView)
	ON_COMMAND(ID_FILE_KILL_PROCESS, OnFileKillProcess)
	ON_UPDATE_COMMAND_UI(ID_FILE_KILL_PROCESS, OnUpdateFileKillProcess)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS, OnDeleteallitems)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminView drawing

void CRemoteAdminView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminView diagnostics

#ifdef _DEBUG
void CRemoteAdminView::AssertValid() const
{
	CListView::AssertValid();
}

void CRemoteAdminView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminView message handlers
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CRemoteAdminFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_wndToolBar.CreateEx(this);
	m_wndToolBar.LoadToolBar(IDR_REMOTECONTROL);
	//m_wndReBar.Create(this);//用ReBar包装是为了可以拖动
	//m_wndReBar.AddBar(&m_wndToolBar);//不用ReBar包装不能拖动
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndStatusBar.Create(this);
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndStatusBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar( &m_wndToolBar);
	//DockControlBar( &m_wndStatusBar);
	m_rcSplitterWnd.SetRectEmpty();
    m_rcStatusBar.SetRectEmpty();
	
	m_tooltip.Create(this);
	m_tooltip.SetNotify();
	CRect rc;  
	GetClientRect(&rc); 
	m_tooltip.AddTool(this,	_T(""), rc);
	m_tooltip.SetBehaviour(PPTOOLTIP_DISABLE_AUTOPOP|PPTOOLTIP_MULTIPLE_SHOW|PPTOOLTIP_NOCLOSE_OVER); 
	return 0;
}

BOOL CRemoteAdminFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect rcClient;
    GetClientRect(rcClient);
    int nMachineViewWidth  = 0.25 * rcClient.Width();
    int nMachineViewHeight = rcClient.Height();
    int nRemoteAdminViewWidth  = rcClient.Width() - nMachineViewWidth;
    int nRemoteAdminViewHeight = rcClient.Height();
    if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMachineView), CSize(nMachineViewWidth, nMachineViewHeight), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRemoteAdminView), CSize(nRemoteAdminViewWidth, nRemoteAdminViewHeight), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	return TRUE;
}

void CRemoteAdminFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	if(m_wndSplitter.m_hWnd == NULL || !IsWindow(m_wndSplitter.m_hWnd))
		return;
	CView* pViewLeft = (CView*)m_wndSplitter.GetDlgItem(m_wndSplitter.IdFromRowCol(0, 0));
	CView* pViewRight = (CView*)m_wndSplitter.GetDlgItem(m_wndSplitter.IdFromRowCol(0, 1));
	if (pViewLeft == NULL || pViewRight == NULL || !IsWindow(pViewLeft->m_hWnd) || !IsWindow(pViewRight->m_hWnd))
		return;
	CWnd* pLeftWnd = m_wndSplitter.GetPane(0, 0);
	CWnd* pRightWnd = m_wndSplitter.GetPane(0, 1);
	if (pLeftWnd == NULL || pRightWnd == NULL || !IsWindow(pLeftWnd->m_hWnd) || !IsWindow(pRightWnd->m_hWnd))
		return;

	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.DeflateRect(1, 1);
	rcWindow.top += 46;
	rcWindow.bottom -= 175;
	ScreenToClient(&rcWindow);
    m_rcSplitterWnd = rcWindow;
    m_rcStatusBar = CRect(rcWindow.left, rcWindow.bottom, rcWindow.right, rcWindow.bottom + 20);
	m_wndSplitter.MoveWindow(m_rcSplitterWnd);
	m_wndStatusBar.MoveWindow(m_rcStatusBar);
	int width = m_rcStatusBar.Width();
	m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, 0, width/2);
    m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_CAPS, 0, width/6);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_NUM, 0, width/6);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_SCRL, 0, width/6);
}

void CRemoteAdminFrame::OnChangeRightViewStyle(UINT nID)
{
    CRemoteAdminView* pView = (CRemoteAdminView*)m_wndSplitter.GetPane(0, 1);
	ASSERT(pView);
	DWORD dwStyle = -1;
	switch (nID)
	{
	case ID_VIEW_LINEUP:
		{
		    CListCtrl& list = pView->GetListCtrl();
			list.Arrange(LVA_SNAPTOGRID);
		}
		break;
	case ID_VIEW_DETAILS:
		dwStyle = LVS_REPORT;
		break;	
	case ID_VIEW_SMALLICON:
		dwStyle = LVS_SMALLICON;
		break;	
	case ID_VIEW_LARGEICON:
		dwStyle = LVS_ICON;
		break;	
	case ID_VIEW_LIST:
		dwStyle = LVS_LIST;
		break;
	}
	if (dwStyle != -1)
		pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
}

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlTimeSettingDlg dialog


CRemoteControlTimeSettingDlg::CRemoteControlTimeSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteControlTimeSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteControlTimeSettingDlg)
	m_nProcessRefreshTime = 0;
	m_nShutDownDelayTime = 0;
	//}}AFX_DATA_INIT
}


void CRemoteControlTimeSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteControlTimeSettingDlg)
	DDX_Text(pDX, IDC_EDIT_PROCESS_REFRESH, m_nProcessRefreshTime);
	DDV_MinMaxUInt(pDX, m_nProcessRefreshTime, 1, 300);
	DDX_Text(pDX, IDC_EDIT_SHUTDOWN_DELAY, m_nShutDownDelayTime);
	DDV_MinMaxInt(pDX, m_nShutDownDelayTime, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteControlTimeSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CRemoteControlTimeSettingDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlTimeSettingDlg message handlers

void CRemoteControlTimeSettingDlg::OnOK() 
{
	if (!UpdateData())
		return;
	CDialog::OnOK();
}

void CRemoteAdminFrame::OnSettingsTimers() 
{
	CRemoteControlTimeSettingDlg dlg;
	dlg.m_nProcessRefreshTime = m_iUpdateProcessDelay / 1000;
	dlg.m_nShutDownDelayTime = m_iShutdownDelay  / 1000;
	if (dlg.DoModal() == IDCANCEL)
		return;	
	m_iUpdateProcessDelay = dlg.m_nProcessRefreshTime * 1000;
	m_iShutdownDelay = dlg.m_nShutDownDelayTime  * 1000;
}

void CRemoteAdminFrame::OnClose() 
{
	m_bUpdateProcessList = FALSE;
	CFrameWnd::OnClose();
}

void CRemoteAdminFrame::OnSettingsWindowAlwaysontop() 
{
	CMenu* pMenu = GetMenu();
	CMenu* pSubMenu = pMenu->GetSubMenu(1);
	//CString str;
	//pSubMenu->GetMenuString(1, str, MF_BYPOSITION);
	CMenu* pWindowMenu = pSubMenu->GetSubMenu(1);
	//UINT nID = pSubMenu->GetMenuItemID(1);
	//if (nID == (UINT)-1)
	//iCount = pSubMenu->GetMenuItemCount( );
	//iCount = pWindowMenu->GetMenuItemCount( );
    //CMenu* pDestMenu = pWindowMenu->GetSubMenu(0);
	//pWindowMenu->GetMenuString(0, str, MF_BYPOSITION);
	//pWindowMenu->GetMenuString(1, str, MF_BYPOSITION);
	UINT state = pWindowMenu->GetMenuState(ID_SETTINGS_WINDOW_ALWAYSONTOP, MF_BYCOMMAND);
    ASSERT(state != 0xFFFFFFFF);
	
	if (state & MF_CHECKED)
	{
		AfxGetApp()->m_pMainWnd->SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		pWindowMenu->CheckMenuItem(ID_SETTINGS_WINDOW_ALWAYSONTOP, MF_UNCHECKED | MF_BYCOMMAND);
		m_bTopMost = false;
	}
	else
	{
		AfxGetApp()->m_pMainWnd->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		pWindowMenu->CheckMenuItem(ID_SETTINGS_WINDOW_ALWAYSONTOP, MF_CHECKED | MF_BYCOMMAND);
		m_bTopMost = true;
	}
}


//////////////////////////////////////////////////////////////////////
// CMachineInfo Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMachineInfo, CObject, 1)

CMachineInfo::CMachineInfo()
{
    m_strIP = "";
	m_strPwd = "";
	m_strUserName = "";
    m_hPipe = NULL;
	m_hProcessInfoPipe = NULL;
	m_hProcessExecutePipe = NULL;
	m_hProcessKillPipe = NULL;
    m_hRemoteAdminPipe = NULL;
    m_hSysShutDownPipe = NULL;
}

CMachineInfo::~CMachineInfo()
{
    POSITION pos = m_procInfoList.GetHeadPosition();
	while(pos)
	{
		ProcessInfo* pInfo = m_procInfoList.GetNext(pos);
		if (pInfo != NULL)
			delete pInfo;
	}
	m_procInfoList.RemoveAll();
}

CString CMachineInfo::GetIP()
{
    return m_strIP;
}

CString CMachineInfo::GetPassword()
{
    return m_strPwd;
}

CString CMachineInfo::GetUserName()
{
    return m_strUserName;
}

HANDLE CMachineInfo::GetPipe()
{
    return m_hPipe;
}

HANDLE CMachineInfo::GetProcessInfoPipe()
{
    return m_hProcessInfoPipe;
}

HANDLE CMachineInfo::GetProcessExecutePipe()
{
     return m_hProcessExecutePipe;
}

HANDLE CMachineInfo::GetProcessKillPipe()
{
     return m_hProcessKillPipe;
}

HANDLE CMachineInfo::GetSysShutdownPipe()
{
    return m_hSysShutDownPipe;
}

CMachineInfo& CMachineInfo::operator=(CMachineInfo &that)
{
    m_strIP = that.GetIP();
	m_strPwd = that.GetPassword();
	m_strUserName = that.GetUserName();
	return *this;
}

BOOL CMachineInfo::operator == (CMachineInfo& miMachineInfo)
{
    if (m_strIP == miMachineInfo.GetIP() && 
        m_strPwd == miMachineInfo.GetPassword() &&
        m_strUserName == miMachineInfo.GetUserName())
        return TRUE;
    else
        return FALSE;
}

void CMachineInfo::RefreshProcessList(ProcessInfoList &lst)
{
	m_csProcessInfoList.Lock();
	POSITION pos = m_procInfoList.GetHeadPosition();
	ProcessInfo* pInfo, *pInfo2;
	while(pos)
	{
		pInfo = m_procInfoList.GetNext(pos);
		if (pInfo != NULL)
			delete pInfo;
	}
	m_procInfoList.RemoveAll();
	
	pos = lst.GetHeadPosition();
	while(pos)
	{
		pInfo = lst.GetNext(pos);
		if (pInfo != NULL)
		{
			pInfo2 = new ProcessInfo;
			memcpy(pInfo2, pInfo, sizeof(ProcessInfo));
			m_procInfoList.AddTail(pInfo2);
		}
	}
	m_csProcessInfoList.Unlock();
}

void CMachineInfo::SetIP(CString strIP)
{
    m_strIP = strIP;
}

void CMachineInfo::SetPassword(CString strPwd)
{
    m_strPwd = strPwd;
}

void CMachineInfo::SetUserName(CString strUserName)
{
    m_strUserName = strUserName;
}

void CMachineInfo::SetPipe(HANDLE handle)
{
    m_hPipe = handle;
}

void CMachineInfo::SetProcessInfoPipe(HANDLE handle)
{
    m_hProcessInfoPipe = handle;
}

void CMachineInfo::SetProcessExecutePipe(HANDLE handle)
{
    m_hProcessExecutePipe = handle;
}

void CMachineInfo::SetProcessKillPipe(HANDLE handle)
{
    m_hProcessKillPipe = handle;
}

void CMachineInfo::SetSysShutDownPipe(HANDLE handle)
{
    m_hSysShutDownPipe = handle;
}

void CMachineInfo::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if (ar.IsLoading())
    {
        ar >> m_strIP;
        ar >> m_strPwd;
        ar >> m_strUserName;
    }
    else
    {
        ar << m_strIP;
        ar << m_strPwd;
        ar << m_strUserName;
    }
}


void CRemoteAdminFrame::ShowToolTip(CRect rc, CString strTip)
{
	//m_tooltip.RemoveAllTools();
	//m_tooltip.SetNotify();
	//m_tooltip.AddTool(this,	_T(""), rc);
    m_tooltip.ShowHelpTooltip( &rc.CenterPoint(), _T(strTip));
}

BOOL CRemoteAdminFrame::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);//气泡信息显示的消息发送
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CRemoteAdminFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	static ULONG dwTick = GetTickCount();
	CFrameWnd::OnMouseMove(nFlags, point);
	CPoint ptCur;
	GetCursorPos(&ptCur);
	CRect rc(ptCur, CSize(10,10));
	CMachineView* pView = (CMachineView*)m_wndSplitter.GetPane(0, 0);
	if (pView->m_bMouseIn)
	{
		ULONG dw = GetTickCount();
		if (dw - dwTick > 500)
		{
			dwTick = dw;
			ShowToolTip(rc, "OOOOOK");
		}
	}
	else
	{
		dwTick = GetTickCount();
        //m_tooltip.RemoveAllTools();
		ShowToolTip(rc, "");
	}
	//pView->Invalidate();
	//m_tooltip.Invalidate();
}

void CMachineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTreeView::OnMouseMove(nFlags, point);
	CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)GetParent()->GetParent();
	CPoint pt = point;
    ClientToScreen(&pt);
	pFrame->ScreenToClient(&pt);
	pFrame->SendMessage(WM_MOUSEMOVE, nFlags, (pt.y << 16) | pt.x);
	
	if (!m_bMouseIn)
	{
		m_bMouseIn = true;
		TRACKMOUSEEVENT info;
		info.cbSize = sizeof(TRACKMOUSEEVENT);
		info.dwFlags = TME_LEAVE;
		info.hwndTrack = m_hWnd;
		info.dwHoverTime = HOVER_DEFAULT;
		BOOL b = _TrackMouseEvent(&info);
	}
}

LRESULT CMachineView::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bMouseIn = false;
	CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)GetParent()->GetParent();
	CRect rc;
	pFrame->GetClientRect(rc);
	CPoint pt = rc.BottomRight();
	pt.x += 10;
	pt.y += 10;
    pFrame->SendMessage(WM_MOUSEMOVE, 0, (pt.y << 16) | pt.x);
	OutputDebugString("Mouse Leave\n");
    return 0;
}


void CMachineInfo::ClosePipe()
{
    //CloseHandle(m_hPipe);
	CloseHandle(m_hProcessExecutePipe);
	CloseHandle(m_hProcessKillPipe);
	CloseHandle(m_hSysShutDownPipe);
	CloseHandle(m_hProcessInfoPipe);
}

void CMachineInfo::SendEndThreadMessage()
{
    DWORD dwRead    = 0;
    DWORD dwWritten = 0;
    ThreadExitCommand cmd    = {0};
    BOOL bOk        = FALSE;
    cmd.bThreadExit = TRUE;
    //bOk = ::WriteFile(m_hPipe, &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(m_hProcessInfoPipe,    &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(m_hProcessExecutePipe, &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(m_hProcessKillPipe,    &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(m_hSysShutDownPipe,    &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
}

ProcessInfoList* CMachineInfo::GetProcessInfoList()
{
	m_csProcessInfoList.Lock();
    ProcessInfoList* pProcessInfoList = new ProcessInfoList;
    POSITION pos = m_procInfoList.GetHeadPosition();
    while (pos != NULL)
    {
        ProcessInfo* pPe = m_procInfoList.GetNext(pos);
        ProcessInfo* p = new ProcessInfo;
        
		if (p != NULL)
		{
			if (pPe != NULL)
			{
				::memcpy(p, pPe, sizeof(ProcessInfo));
				pProcessInfoList->AddTail(p);
			}
		}
    }
    m_csProcessInfoList.Unlock();
    return pProcessInfoList;
}
//////////////////////////////////////////////////////////////////////
// CRemoteAdministrator Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRemoteAdministrator::CRemoteAdministrator()
{
    m_hCmdPipe = NULL;
	m_ConnectedMachineList.RemoveAll();
	m_PendingConnectionList.RemoveAll();
}

CRemoteAdministrator::~CRemoteAdministrator()
{
	POSITION pos = m_ConnectedMachineList.GetHeadPosition();
	CMachineInfo* pMacInfo;
	while(pos)
	{
		pMacInfo = m_ConnectedMachineList.GetNext(pos);
		if (pMacInfo != NULL)
			delete pMacInfo;
	}
	m_ConnectedMachineList.RemoveAll();

	pos = m_PendingConnectionList.GetHeadPosition();
	CString* pstr;
	while(pos)
	{
		pstr = m_PendingConnectionList.GetNext(pos);
		if (pstr != NULL)
			delete pstr;
	}
	m_PendingConnectionList.RemoveAll();
}


bool CRemoteAdministrator::DeleteFromPendingList(CString strIP)
{
	POSITION pos = m_PendingConnectionList.GetHeadPosition();
	CString* pstr;
	POSITION pos1;
	while(pos)
	{
		pos1 = pos;
		pstr = m_PendingConnectionList.GetNext(pos);
		if (pstr != NULL && (*pstr) == strIP)
		{
			delete pstr;
            m_PendingConnectionList.RemoveAt(pos1);
			return true;
		}
	}
	return false;
}

bool CRemoteAdministrator::RefreshProcessList(CString strIP, ProcessInfoList &lst)
{
    CMachineInfo* pInfo = GetMachineInfo(strIP);
	if (pInfo == NULL)
		return false;
	pInfo->RefreshProcessList(lst);
	return true;
}

CMachineInfo* CRemoteAdministrator::GetMachineInfo(CString strIP)
{
    POSITION pos = m_ConnectedMachineList.GetHeadPosition();
	CMachineInfo* pInfo = NULL;
	while(pos)
	{
		pInfo = m_ConnectedMachineList.GetNext(pos);
		if (pInfo != NULL && pInfo->GetIP() == strIP)
			return pInfo;
	}
	return NULL;
}

bool CRemoteAdministrator::IsConnectionPending(CString strIP)
{
    POSITION pos = m_PendingConnectionList.GetHeadPosition();
	CString* pstr;
	while(pos)
	{
		pstr = m_PendingConnectionList.GetNext(pos);
		if (pstr != NULL && (*pstr) == strIP)
			return true;
	}
	return false;
}

bool CRemoteAdministrator::InstallAndStartService(CString strIP)
{
    SC_HANDLE hSCM = ::OpenSCManager(strIP.GetBuffer(0), NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
        return FALSE;
    SC_HANDLE hService =::OpenService(hSCM, SERVICENAME, SERVICE_ALL_ACCESS);
    if (hService == NULL)
    {
        hService = ::CreateService(hSCM,  SERVICENAME,  LONGSERVICENAME, SERVICE_ALL_ACCESS, 
                        SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,  SERVICE_ERROR_NORMAL,
                        _T("%SystemRoot%\\system32\\")REMOTE_ADMIN_SERVICE_EXE, NULL, NULL,  NULL, 
						NULL,  NULL );
    } 
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }
    if (!::StartService(hService, 0, NULL))
	{
		BOOL bRet = FALSE;
		DWORD dwError = GetLastError();
		if (dwError == ERROR_SERVICE_ALREADY_RUNNING)
            bRet = TRUE;
		else
		{
			CString strError;
	        GetErrorMessage(dwError, strError);
            AfxMessageBox(strError);
		}
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return FALSE;
	}
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
    return TRUE;
}

int CRemoteAdministrator::GetConnectMachineCount()
{
    return m_ConnectedMachineList.GetCount();
}

HANDLE CRemoteAdministrator::GetSysShutDownPipe(CString strIP)
{
    CMachineInfo* pMachineInfo = GetMachineInfo(strIP);

    if (pMachineInfo != NULL)
        return pMachineInfo->GetSysShutdownPipe();
    else
        return NULL;
}

HANDLE CRemoteAdministrator::GetProcessInfoPipe(CString strIP)
{
    CMachineInfo* pMachineInfo = GetMachineInfo(strIP);

    if (pMachineInfo != NULL)
        return pMachineInfo->GetProcessInfoPipe();
    else
        return NULL;
}

HANDLE CRemoteAdministrator::GetProcessExecutePipe(CString strIP)
{
    CMachineInfo* pMachineInfo = GetMachineInfo(strIP);

    if (pMachineInfo != NULL)
        return pMachineInfo->GetProcessExecutePipe();
    else
        return NULL;
}

HANDLE CRemoteAdministrator::GetProcessKillPipe(CString strIP)
{
    CMachineInfo* pMachineInfo = GetMachineInfo(strIP);

    if (pMachineInfo != NULL)
        return pMachineInfo->GetProcessKillPipe();
    else
        return NULL;
}

HANDLE CRemoteAdministrator::GetRemoteAdminPipe(CString strIP)
{
    CMachineInfo* pMachineInfo = GetMachineInfo(strIP);

    if (pMachineInfo != NULL)
        return pMachineInfo->GetPipe();
    else
        return NULL;
}


ProcessInfoList* CRemoteAdministrator::GetProcessInfoList(CString strIP)
{
    CMachineInfo* pMachineInfo = GetMachineInfo(strIP);

    if (pMachineInfo != NULL)
        return pMachineInfo->GetProcessInfoList();
    else
        return NULL;
}

int CRemoteAdministrator::GetPendingConnectionCount()
{
    return m_PendingConnectionList.GetCount();
}

void CRemoteAdministrator::GetConnectHostIP(CStringArray &aHosts)
{
     aHosts.RemoveAll();
	 POSITION pos = m_ConnectedMachineList.GetHeadPosition();
	 CMachineInfo* pInfo;
	 while(pos)
	 {
		 pInfo = m_ConnectedMachineList.GetNext(pos);
		 if (pInfo != NULL)
			 aHosts.Add(pInfo->GetIP());
	 }
}

CString CRemoteAdministrator::GetHostName(CString strIP)
{
	unsigned long ulAddr = ::inet_addr(LPCTSTR(strIP));
	if (ulAddr != INADDR_NONE)
	{
		HOSTENT* pHostEnt    = ::gethostbyaddr((char*)&ulAddr, sizeof(ulAddr), AF_INET);
		if (pHostEnt != NULL)
		   return pHostEnt->h_addr;
	}
    return "";
}

CString CRemoteAdministrator::GetHostIPFromName(CString strName)
{
	unsigned long ulAddr = ::inet_addr(LPCTSTR(strName));
	CString strIP;

	if (ulAddr == INADDR_NONE) // Not a valid IP in dotted format, so can be a string
	{
		HOSTENT* pHostEnt = ::gethostbyname((LPCTSTR)(strName));
		if (pHostEnt != NULL)
		{
			in_addr* addr = (in_addr*)pHostEnt->h_addr_list[0]; 
			
			int ip1 = addr->S_un.S_un_b.s_b1;
            int ip2 = addr->S_un.S_un_b.s_b2;
            int ip3 = addr->S_un.S_un_b.s_b3;
            int ip4 = addr->S_un.S_un_b.s_b4;

			strIP.Format("%d.%d.%d.%d", ip1, ip2, ip3, ip4);
			return strIP;
		}
		else
			return "";
	}
    else
		return strName;	
}

void CRemoteAdministrator::AddConnectedMachine(CMachineInfo *pInfo)
{
    CMachineInfo* p = new CMachineInfo;
	*p = *pInfo;
	m_ConnectedMachineList.AddHead(p);
}

void CRemoteAdministrator::AddPendingMachine(CString strIP)
{
    CString * p = new CString(strIP);
	m_PendingConnectionList.AddHead(p);
}

bool CRemoteAdministrator::IsMachineConnected(CString strIP)
{
    POSITION pos = m_ConnectedMachineList.GetHeadPosition();
	CMachineInfo* pInfo;
	while(pos)
	{
		pInfo = m_ConnectedMachineList.GetNext(pos);
		if (pInfo != NULL && pInfo->GetIP() == strIP)
			return true;
	}
	return false;
}

bool CRemoteAdministrator::ConnectRemoteService(CString strIP, DWORD dwRetry, DWORD dwTimeout)
{
    TCHAR szRemoteAdminPipeName[_MAX_PATH]               = _T("");
    TCHAR szRemoteAdminProcessInfoPipeName[_MAX_PATH]    = _T("");
    TCHAR szRemoteAdminProcessExecutePipeName[_MAX_PATH] = _T("");
    TCHAR szRemoteAdminProcessKillPipeName[_MAX_PATH]    = _T("");
    TCHAR szRemoteAdminSysShutdownPipe[_MAX_PATH]        = _T("");
    HANDLE hCommandPipe = INVALID_HANDLE_VALUE;

    ::sprintf(szRemoteAdminPipeName, _T("\\\\%s\\pipe\\%s"), strIP.GetBuffer(0), REMOTE_ADMIN_PIPE);
    ::sprintf(szRemoteAdminProcessInfoPipeName, _T("\\\\%s\\pipe\\%s"), strIP.GetBuffer(0), REMOTE_ADMIN_PROCESS_INFO_PIPE);
    ::sprintf(szRemoteAdminProcessExecutePipeName, _T("\\\\%s\\pipe\\%s"), strIP.GetBuffer(0), REMOTE_ADMIN_PROCESS_EXECUTE_PIPE);
    ::sprintf(szRemoteAdminProcessKillPipeName, _T("\\\\%s\\pipe\\%s"), strIP.GetBuffer(0), REMOTE_ADMIN_PROCESS_KILL_PIPE);
    ::sprintf(szRemoteAdminSysShutdownPipe, _T("\\\\%s\\pipe\\%s"), strIP.GetBuffer(0), REMOTE_ADMIN_SYS_SHUTDOWN_PIPE);
    //权限
    SECURITY_ATTRIBUTES secattr = { 0 };
	SECURITY_DESCRIPTOR secdesc;
	InitializeSecurityDescriptor(&secdesc, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&secdesc, TRUE, NULL, TRUE);
	secattr.nLength = sizeof(SECURITY_ATTRIBUTES);
	secattr.lpSecurityDescriptor = &secdesc;
	secattr.bInheritHandle = TRUE;

	while(dwRetry--)
    {
        if (::WaitNamedPipe(szRemoteAdminPipeName, 5000))
        {
            hCommandPipe = ::CreateFile(szRemoteAdminPipeName, GENERIC_WRITE | GENERIC_READ, 
                                 0, &secattr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

            ::CloseHandle(hCommandPipe);  
            CMachineInfo* pMachineInfo = GetMachineInfo(strIP);
            ::Sleep(10000);
            if (::WaitNamedPipe(szRemoteAdminProcessInfoPipeName, 5000))
             {
                 hCommandPipe = ::CreateFile(szRemoteAdminProcessInfoPipeName, GENERIC_WRITE | GENERIC_READ, 
                                 0, &secattr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,  NULL );
                 pMachineInfo->SetProcessInfoPipe(hCommandPipe);
             }

             if (::WaitNamedPipe(szRemoteAdminProcessExecutePipeName, 5000))
             {
                 hCommandPipe = ::CreateFile(szRemoteAdminProcessExecutePipeName, GENERIC_WRITE | GENERIC_READ, 
                                 0, &secattr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,   NULL );
                 pMachineInfo->SetProcessExecutePipe(hCommandPipe);
             }

             if (::WaitNamedPipe(szRemoteAdminProcessKillPipeName, 5000))
             {
                 hCommandPipe = ::CreateFile( szRemoteAdminProcessKillPipeName, GENERIC_WRITE | GENERIC_READ, 
                                 0, &secattr,  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
                 pMachineInfo->SetProcessKillPipe(hCommandPipe);
             }

             if (::WaitNamedPipe(szRemoteAdminSysShutdownPipe, 5000))
             {
                 hCommandPipe = ::CreateFile(szRemoteAdminSysShutdownPipe, GENERIC_WRITE | GENERIC_READ, 
                                 0, &secattr,  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,  NULL );
                 pMachineInfo->SetSysShutDownPipe(hCommandPipe);
             }
            break;
         }
         else
            ::Sleep(dwTimeout);
    }
    return hCommandPipe != INVALID_HANDLE_VALUE;
}

bool CRemoteAdministrator::CopyServiceExeToHost(CString strIP)
{
   DWORD dwWritten = 0;
   HMODULE hInstance = ::GetModuleHandle(NULL);
   //找到服务程序的二进制文件资源
   HRSRC hServiceExecutableRes = ::FindResource(hInstance, MAKEINTRESOURCE(IDR_REMOTEADMIN), _T("EXECUTABLES"));
   HGLOBAL hServiceExecutable = ::LoadResource(hInstance, hServiceExecutableRes);
   LPVOID pServiceExecutable = ::LockResource(hServiceExecutable);
   if (pServiceExecutable == NULL)
      return FALSE;
   DWORD dwServiceExecutableSize = ::SizeofResource(hInstance, hServiceExecutableRes);
   TCHAR szServiceExePath[_MAX_PATH];
   ::sprintf(szServiceExePath, _T("\\\\%s\\ADMIN$\\System32\\%s"), strIP.GetBuffer(0),  REMOTE_ADMIN_SERVICE_EXE);
   DeleteFile(szServiceExePath);
   HANDLE hFileServiceExecutable = ::CreateFile(szServiceExePath, GENERIC_WRITE, 0, NULL,
                                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if (hFileServiceExecutable == INVALID_HANDLE_VALUE)
       return FALSE;
   ::WriteFile(hFileServiceExecutable, pServiceExecutable, dwServiceExecutableSize, &dwWritten, NULL);
   ::CloseHandle(hFileServiceExecutable);
   return (dwWritten == dwServiceExecutableSize);
}

void CRemoteAdministrator::DisconnectAllHosts()
{
	CMachineInfo* pMachineInfo = NULL;
    POSITION pos = m_ConnectedMachineList.GetHeadPosition();
    while (pos != NULL)
    {
        pMachineInfo = m_ConnectedMachineList.GetNext(pos);
		if (pMachineInfo == NULL)
			continue;
        pMachineInfo->SendEndThreadMessage();
        pMachineInfo->ClosePipe();
		EstablishAllConnections(pMachineInfo->GetIP(), pMachineInfo->GetUserName(), pMachineInfo->GetPassword(), FALSE);
		delete pMachineInfo;
    }
	m_ConnectedMachineList.RemoveAll();
}

void CRemoteAdministrator::DisconnectAHost(CString strIP)
{
     CMachineInfo* pInfo = NULL;
	 CMachineInfo* p;
	 POSITION pos = m_ConnectedMachineList.GetHeadPosition();
	 POSITION pos1;

	 while(pos)
	 {
		 pos1 = pos;
		 p = m_ConnectedMachineList.GetNext(pos);
		 if (p != NULL && p->GetIP() == strIP)
		 {
			 pInfo = p;
			 break;
		 }
	 }
	if (pInfo)
	{
		pInfo->SendEndThreadMessage();
		pInfo->ClosePipe();
		BOOL bConnectionDeleted = EstablishAllConnections(pInfo->GetIP(), pInfo->GetUserName(), pInfo->GetPassword(), FALSE);
        delete pInfo;
		m_ConnectedMachineList.RemoveAt(pos1);
	}
}

BOOL CRemoteAdministrator::EstablishConnection(CString strResource, CString strUserName, CString strIP, CString strPwd, BOOL bEstablish)
{
	m_cs.Lock();
    TCHAR szRemoteResource[_MAX_PATH];
    DWORD dwRetVal = NO_ERROR;
    ::sprintf(szRemoteResource, _T("\\\\%s\\%s"), strIP.GetBuffer(0), strResource.GetBuffer(0));
    //建立链接
    if (bEstablish) 
    {
        NETRESOURCE nr;
        nr.dwType = RESOURCETYPE_ANY;
        nr.lpLocalName = NULL;
        nr.lpRemoteName = (LPTSTR)&szRemoteResource;
        nr.lpProvider = NULL;
        //HANDLE hToken;
		//BOOL bRet = LogonUser(strUserName.GetBuffer(0), strIP.GetBuffer(0), strPwd.GetBuffer(0), LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken);
        //Establish connection (using username/pwd)
        dwRetVal = ::WNetAddConnection2(&nr, strPwd.GetBuffer(0), strUserName.GetBuffer(0), CONNECT_PROMPT|CONNECT_INTERACTIVE);
    }
    else
       //断开链接
        dwRetVal = ::WNetCancelConnection2(szRemoteResource, 0, NULL);
	DWORD dwError = GetLastError();
	m_cs.Unlock();
    if (dwRetVal == NO_ERROR) 
	    return TRUE; // indicate success
    else
	{
		CString strError;
		GetErrorMessage(dwError, strError);
		return FALSE;
	}
}

BOOL CRemoteAdministrator::EstablishIPCConnection(CString strIP, CString strUserName, CString strPwd, BOOL bEstablish)
{
	CString strResource = _T("IPC$");
	BOOL bConnectionSuccess = EstablishConnection(strResource, strUserName, strIP, strPwd, bEstablish);
    return bConnectionSuccess;
}

BOOL CRemoteAdministrator::EstablishAdminConnection(CString strIP, CString strUserName, CString strPwd, BOOL bEstablish)
{
	CString strResource = _T("ADMIN$");
	BOOL bConnectionSuccess = EstablishConnection(strResource, strUserName, strIP, strPwd, bEstablish);
    return bConnectionSuccess;
}

BOOL CRemoteAdministrator::EstablishAllConnections(CString strRemoteMachineIP, CString strUserName, CString strPwd, BOOL bEstablish)
{
    BOOL bSuccessAdminConnection = EstablishAdminConnection(strRemoteMachineIP, strUserName, strPwd, bEstablish);
    BOOL bSuccessIPCConnection   = EstablishIPCConnection(strRemoteMachineIP, strUserName, strPwd, bEstablish);
    return (bSuccessAdminConnection && bSuccessIPCConnection);
}
/////////////////////////////////////////////////////////////////////////////
// CProgressThread

IMPLEMENT_DYNCREATE(CProgressThread, CWinThread)

CProgressThread::CProgressThread()
{
}

CProgressThread::~CProgressThread()
{
	m_pDoc->SetProgressThread(NULL);
}

BOOL CProgressThread::InitInstance()
{
	CProgressDlg* pDlg = new CProgressDlg;
	pDlg->SetDocument(m_pDoc);
	pDlg->Create(CProgressDlg::IDD);
	pDlg->ShowWindow(SW_SHOW);
	m_pMainWnd = pDlg;
	return TRUE;
}

int CProgressThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
	//{{AFX_MSG_MAP(CProgressThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressThread message handlers

void CMachineDoc::SetProgressThread(CProgressThread *pThread)
{
    m_pVisualProgressThread = pThread;
}

void CMachineDoc::OnCloseDocument() 
{
	m_RemoteAdministrator.DisconnectAllHosts();
	CDocument::OnCloseDocument();
}

void CMachineDoc::DeleteContents() 
{
	m_RemoteAdministrator.DisconnectAllHosts();
	CDocument::DeleteContents();
}

BOOL CMachineDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CMainDlg* pDlg = (CMainDlg*)AfxGetMainWnd();
	CRuntimeClass* pClass = RUNTIME_CLASS(CRemoteControlDlg);
	map<CRuntimeClass*, pair<CDialog*, CRect> >::iterator it = pDlg->m_aChild.find(pClass);
	CRemoteControlDlg* pMyDlg = (CRemoteControlDlg*)it->second.first;
	CRemoteAdminFrame* pFrame = pMyDlg->m_pFrame;
    CMachineView* pMachineView = (CMachineView*)pFrame->m_wndSplitter.GetPane(0, 0);
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pFrame->m_wndSplitter.GetPane(0, 1);
 
	if (pMachineView == NULL || pAdminView == NULL)
		return false;
	pFrame->m_bUpdateProcessList = FALSE;
	::Sleep(3000);

	if (m_pUpdateThread != NULL)
    	m_pUpdateThread = NULL;
    m_RemoteAdministrator.DisconnectAllHosts();
	pFrame->m_bUpdateProcessList = TRUE;

    if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if (m_ConnectedHostList != NULL)
	{
		CMachineInfo* pMachineInfo = NULL;
		POSITION pos = m_ConnectedHostList->GetHeadPosition();
		while (pos != NULL)
		{
			pMachineInfo = m_ConnectedHostList->GetNext(pos);
			ConnectInfo* pConnectInfo     = new ConnectInfo;
			pConnectInfo->pDoc             = this;
			pConnectInfo->pMachineView     = pMachineView;
			pConnectInfo->pAdminView       = pAdminView;
			pConnectInfo->strIP            = pMachineInfo->GetIP();
			pConnectInfo->strPwd           = pMachineInfo->GetPassword();
			pConnectInfo->strUserName      = pMachineInfo->GetUserName();
			AfxBeginThread(AFX_THREADPROC(ConnectToMachine), pConnectInfo);
		}

		pos = m_ConnectedHostList->GetHeadPosition();
		while (pos != NULL)
		{
			pMachineInfo = m_ConnectedHostList->GetNext(pos);
			if (pMachineInfo != NULL)
				delete pMachineInfo;
		}
		delete m_ConnectedHostList;
		m_ConnectedHostList = NULL;
    }

    ConnectInfo* pConnectInfo      = new ConnectInfo;
	pConnectInfo->pDoc             = this;
	pConnectInfo->pMachineView     = pMachineView;
	pConnectInfo->pAdminView       = pAdminView;
	pConnectInfo->strIP            = "";
	pConnectInfo->strPwd           = "";
	pConnectInfo->strUserName      = "";
	if (m_pUpdateThread == NULL)
         m_pUpdateThread = AfxBeginThread(AFX_THREADPROC(UpdateProcessListForAllMachines), pConnectInfo, 
		                                        THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	CreateVisualThread();
	return TRUE;
}

void CMachineDoc::CreateVisualThread()
{
	if (m_pVisualProgressThread == NULL)
	{
		m_pVisualProgressThread = static_cast<CProgressThread*>(::AfxBeginThread(RUNTIME_CLASS(CProgressThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED));
		if (m_pVisualProgressThread != NULL)
		{
			m_pVisualProgressThread->SetDocument(this);
			m_pVisualProgressThread->ResumeThread();
		}
	}
}

void CProgressThread::SetDocument(CMachineDoc *pDoc)
{
    m_pDoc = pDoc;
}

BOOL CMachineDoc::ConnectToRemoteService(CString strIP, CString strUserName, CString strPwd, CMachineView* pMachineView, CRemoteAdminView* pRemoteAdminView)
{
    CMachineInfo* pMachineInfo = new CMachineInfo;
    pMachineInfo->SetUserName(strUserName);
    pMachineInfo->SetIP(strIP);
    pMachineInfo->SetPassword(strPwd);

    m_RemoteAdministrator.AddConnectedMachine(pMachineInfo);

    BOOL bConnectToRemoteService = FALSE;
    bConnectToRemoteService = m_RemoteAdministrator.ConnectRemoteService(strIP, 1, 0);

    if (bConnectToRemoteService)
    {
        pMachineView->ShowNewMachine(strIP, pMachineInfo);
        
        HTREEITEM h = pMachineView->GetTreeItemForText(strIP);
        if (h != NULL)
        {
            pMachineView->GetTreeCtrl().Select(h, TVGN_CARET);
            pRemoteAdminView->GetListCtrl().DeleteAllItems();
            pRemoteAdminView->GetListCtrl().InsertItem(0, _T("Refreshing process list..."));
			pRemoteAdminView->GetListCtrl().SetItemData(0, 0);
            ::Sleep(2000);   
			if (pMachineInfo)
				delete pMachineInfo;
            return TRUE;
        }
    }
    m_RemoteAdministrator.DisconnectAHost(pMachineInfo->GetIP());
	if (pMachineInfo)
		delete pMachineInfo;
    return FALSE;
}

HTREEITEM CMachineView::ShowNewMachine(CString strTextToBeShown, CMachineInfo* pMachineInfo)
{
    TVINSERTSTRUCT tviHelper    = {0};
        
    // Show a new machine in the hierarchy
    tviHelper.hParent			  = m_hMachineViewRoot;
	tviHelper.hInsertAfter		  = TVI_LAST;
	tviHelper.item.mask			  = TVIF_TEXT |
                                    TVIF_IMAGE | 
                                    TVIF_SELECTEDIMAGE | 
                                    TVIF_PARAM;
    tviHelper.item.pszText		  = strTextToBeShown.GetBuffer(0);
	tviHelper.item.iImage		  = MACHINE_IMAGE;
	tviHelper.item.iSelectedImage = MACHINE_IMAGE;
	tviHelper.item.lParam		  = reinterpret_cast<LPARAM>(pMachineInfo);
	
    HTREEITEM hNewTreeItem = GetTreeCtrl().InsertItem(&tviHelper);

    // Expand the root to show the new machine
    GetTreeCtrl().Expand(m_hMachineViewRoot, TVE_EXPAND);

    return hNewTreeItem;
}

HTREEITEM CMachineView::GetTreeItemForText(CString strText)
{
    HTREEITEM hCurrent = GetTreeCtrl().GetNextItem(m_hMachineViewRoot, TVGN_CHILD);

    while (hCurrent != NULL)
    {
       TVITEM item;
       TCHAR szText[1024];
       item.hItem = hCurrent;
       item.mask = TVIF_TEXT | TVIF_HANDLE;
       item.pszText = szText;
       item.cchTextMax = 1024;

       BOOL bWorked = GetTreeCtrl().GetItem(&item);
       
       if (bWorked)
       {
           if (::strcmp(strText.GetBuffer(0), item.pszText) == 0)
           {
               return hCurrent;
           }
       }
       hCurrent = GetTreeCtrl().GetNextItem(hCurrent, TVGN_NEXT);
    }
    return NULL;
}

UINT CMachineDoc::ConnectToMachine(void* pParam)
{
    ConnectInfo* pConnectInfo = reinterpret_cast<ConnectInfo*>(pParam);
    CMachineDoc* pDoc                  = pConnectInfo->pDoc;
    CRemoteAdminView* pAdminView       = pConnectInfo->pAdminView;
    CMachineView* pMachineView         = pConnectInfo->pMachineView;
    CString strIP                      = pConnectInfo->strIP;
    CString strPwd                     = pConnectInfo->strPwd;
	CString strUserName                = pConnectInfo->strUserName;
	CRemoteAdminFrame*    pFrame       = (CRemoteAdminFrame*)pAdminView->GetParent()->GetParent();
	ConnectInfo* pConnectInfo2 =  new ConnectInfo;
    memcpy(pConnectInfo2, pConnectInfo, sizeof(ConnectInfo));
	delete pConnectInfo;

	if (pDoc->m_pUpdateThread == NULL)
         pDoc->m_pUpdateThread = AfxBeginThread(AFX_THREADPROC(UpdateProcessListForAllMachines), pConnectInfo2, 
		                                        THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

    pDoc->m_RemoteAdministrator.AddPendingMachine(strIP);
	BOOL bConnectOk = pDoc->EstablishAllConnections(strIP, strUserName, strPwd, TRUE, pMachineView, pAdminView);

    if (!bConnectOk)
    {
        CString strError, strLog;
		GetErrorMessage(GetLastError(), strError);
        strLog.Format("Machine IP %s: %s", strIP.GetBuffer(0), strError.GetBuffer(0));
		CString * p = new CString(strLog);
		pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
    }
    else
    {
        pDoc->m_pUpdateThread->ResumeThread();
        int iConnected = pDoc->m_RemoteAdministrator.GetConnectMachineCount();    
        if (iConnected == 0) 
            pAdminView->GetListCtrl().DeleteAllItems();
        else 
        {
            HTREEITEM h = pMachineView->GetTreeItemForText(strIP);
            if (h != NULL)
                pAdminView->RefreshProcesses(pDoc, strIP);
        }
    }
 
    pDoc->m_RemoteAdministrator.DeleteFromPendingList(strIP);
    return 0;
}

BOOL CMachineDoc::EstablishAllConnections(CString strIP, CString strUserName, CString strPwd, BOOL bEstablish, CMachineView* pMachineView, CRemoteAdminView* pRemoteAdminView)
{
    BOOL bConnectionSuccess      = FALSE;
    BOOL bCopyServiceExe         = FALSE;
    BOOL bStartAndInstallService = FALSE;
    BOOL bConnectToRemoteService = FALSE;
    CMainApp* pApp = (CMainApp*)AfxGetApp();
	CString strLog;
	CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)pMachineView->GetParent()->GetParent();
    
    bConnectToRemoteService = ConnectToRemoteService(strIP, strUserName, strPwd, pMachineView, pRemoteAdminView);
    if (!bConnectToRemoteService)
    {
        bConnectionSuccess = m_RemoteAdministrator.EstablishAllConnections(strIP, strUserName, strPwd, bEstablish);
		if (!bConnectionSuccess)
		{
			strLog = strIP + ":连接远程主机的服务失败";
			CString * p = new CString(strLog);
		    pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
			pApp->ShowBalloonMsgInTray("错误", strLog);
			return false;
		}
		bCopyServiceExe = m_RemoteAdministrator.CopyServiceExeToHost(strIP);
		if (!bCopyServiceExe)
		{
			strLog = strIP + ":上传服务程序失败";
			CString * p = new CString(strLog);
		    pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
			pApp->ShowBalloonMsgInTray("错误", strLog);
			return false;
		}
			
        bStartAndInstallService = m_RemoteAdministrator.InstallAndStartService(strIP);
		if (!bStartAndInstallService)
		{
			strLog = strIP + ":在远程机器上安装或启动服务失败";
			CString * p = new CString(strLog);
		    pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
			pApp->ShowBalloonMsgInTray("错误", strLog);
			return false;
		}
		  
        ::Sleep(2000);
        bConnectToRemoteService = ConnectToRemoteService(strIP, strUserName, strPwd, pMachineView, pRemoteAdminView);
		if (!bConnectToRemoteService)
		{
			strLog = strIP + ":连接远程主机服务失败 ";
			CString * p = new CString(strLog);
		    pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
			pApp->ShowBalloonMsgInTray("错误", strLog);
			return false;
		}

        if (bConnectionSuccess && bCopyServiceExe && bStartAndInstallService && bConnectToRemoteService)
            return TRUE;            
    }
    return bConnectToRemoteService;
}

void CRemoteAdminView::RefreshProcesses(CMachineDoc* pDoc, CString strIP)
{
    ProcessInfoList* pProcessInfoList = NULL;
    ProcessInfo* pPe                  = NULL;
    POSITION pos                       = NULL;
    TCHAR szProcessID[10]              = _T("");
    TCHAR szThreadCount[10]            = _T(""); 
    TCHAR szMemoryUsage[30]            = _T("");

    pProcessInfoList  = pDoc->m_RemoteAdministrator.GetProcessInfoList(strIP);
	if (pProcessInfoList == NULL)
		return;
    int iProcessCount = pProcessInfoList->GetCount();
    GetListCtrl().DeleteAllItems();
	pDoc->m_RemoteAdministrator.m_cs.Lock();
    
	//CScrollBar* pScrollBar = GetListCtrl().GetScrollBarCtrl(SB_VERT);
	//GetListCtrl().GetScrollBarCtrl(SB_VERT)->SetScrollRange(0, iProcessCount);
	for(int i=0; i<iProcessCount; ++i)
    {
        pos = pProcessInfoList->FindIndex(i);
        pPe = pProcessInfoList->GetAt(pos);
		if (pPe == NULL)
			continue;
        ::sprintf(szProcessID,       "%d", pPe->ProcessEntry.th32ProcessID);
        ::sprintf(szThreadCount,     "%d", pPe->ProcessEntry.cntThreads);
        ::sprintf(szMemoryUsage,     "%d", (pPe->nMemUsage)/1000);
        GetListCtrl().InsertItem(i, pPe->ProcessEntry.szExeFile, 0);
        GetListCtrl().SetItemText(i, 1, szProcessID);
        GetListCtrl().SetItemText(i, 2, szThreadCount);
        GetListCtrl().SetItemText(i, 3, szMemoryUsage);
		ProcessInfo* p2 = new ProcessInfo;
		memcpy(p2, pPe, sizeof(ProcessInfo));
		GetListCtrl().SetItemData(i, (DWORD)p2);
    }

    pos = pProcessInfoList->GetHeadPosition();
    while (pos != NULL)
    {
        pPe = pProcessInfoList->GetNext(pos);
		if (pPe)
			delete pPe;
    }
	pProcessInfoList->RemoveAll();
    delete pProcessInfoList;
    pProcessInfoList = NULL;
    pDoc->m_RemoteAdministrator.m_cs.Unlock();
}

UINT CMachineDoc::UpdateProcessListForAllMachines(LPVOID pParam)
{
	ConnectInfo* pConnectInfo          = reinterpret_cast<ConnectInfo*>(pParam);
    CMachineDoc* pDoc                  = pConnectInfo->pDoc;
    CRemoteAdminView* pAdminView       = pConnectInfo->pAdminView;
    CMachineView* pMachineView         = pConnectInfo->pMachineView;
	CRemoteAdminFrame* pFrame          = (CRemoteAdminFrame*)pAdminView->GetParent()->GetParent();
	CStringArray aHosts;
    OVERLAPPED olOverlapped = {0};
	ProcessInfoList pilProcessInfo;
    UINT iProcessCount		= 0;
	DWORD dwRead			= 0;
	DWORD dwWritten			= 0;
	ThreadExitCommand cmd	= {0};
	BOOL bOk;
	HANDLE hProcessInfoPipe;

	delete pConnectInfo;
    
    while (TRUE)
    {   
        if (pFrame->m_bUpdateProcessList == FALSE)
		{
			pDoc->m_pUpdateThread = NULL;
            return 0;
		}
        pDoc->m_RemoteAdministrator.GetConnectHostIP(aHosts);
		for (int i=0; i<aHosts.GetSize(); ++i)
        {
            hProcessInfoPipe = pDoc->m_RemoteAdministrator.GetProcessInfoPipe(aHosts[i]);
            if (hProcessInfoPipe != NULL)
            {
                pDoc->m_RemoteAdministrator.m_cs.Lock();
				
				cmd.bThreadExit = FALSE;
				bOk = ::WriteFile(hProcessInfoPipe, &cmd, sizeof(ThreadExitCommand), &dwWritten, &olOverlapped);
				if (!bOk)
				   Sleep(400);
                bOk = ::ReadFile(hProcessInfoPipe, &iProcessCount, sizeof(UINT), &dwRead, &olOverlapped);
				if (!bOk)
					Sleep(3000);

				pDoc->m_RemoteAdministrator.m_cs.Unlock();
				
				if (iProcessCount <= 0 || iProcessCount >= INT_MAX)  
				{
					if (aHosts[i] != _T(""))
						pDoc->DisconnectAndReconnectToRemoteService(aHosts[i], pMachineView, pAdminView);					
					continue;
				}
                for (UINT i2 = 0; i2 < iProcessCount; ++i2)
                {
					pDoc->ReceiveProcessFromRemoteMachine(hProcessInfoPipe, pilProcessInfo, aHosts[i], iProcessCount, i2 + 1);       
					if (pFrame->m_bUpdateProcessList == FALSE)
					{
						pDoc->m_pUpdateThread = NULL;
						return 0;
					}
				}
				pDoc->m_RemoteAdministrator.RefreshProcessList(aHosts[i], pilProcessInfo);
				POSITION pos = pilProcessInfo.GetHeadPosition();
				while(pos)
				{
					ProcessInfo* pInfo = pilProcessInfo.GetNext(pos);
					if (pInfo != NULL)
						delete pInfo;
				}
				pilProcessInfo.RemoveAll();
            }
        }

		CString strIP;
		HTREEITEM hSelectedItem = NULL;
        hSelectedItem = pMachineView->GetTreeCtrl().GetSelectedItem();
        TVITEM tvItem = {0};
        tvItem.hItem   = hSelectedItem;
        tvItem.mask    = TVIF_PARAM | TVIF_HANDLE ; 
        pMachineView->GetTreeCtrl().GetItem(&tvItem);
        if (tvItem.lParam == 0)
             strIP = _T("0");
		else
             strIP = pMachineView->GetTreeCtrl().GetItemText(hSelectedItem);
    
		if (strIP != _T("0"))
              pAdminView->RefreshProcesses(pDoc, strIP);
        ::Sleep(pFrame->m_iUpdateProcessDelay);
    }
	pDoc->m_pUpdateThread = NULL;
    return 0;
}

void CMachineDoc::ReceiveProcessFromRemoteMachine(HANDLE hProcessInfoPipe, ProcessInfoList& pilProcessInfo, CString strIP, UINT iProcessCount, UINT iCounter)
{
    m_RemoteAdministrator.m_cs.Lock();
    ProcessInfo* pPe = new ProcessInfo;
	if (pPe != NULL)
    {
	    ::memset(pPe, 0, sizeof(ProcessInfo));
		DWORD dwRead			= 0;
		OVERLAPPED olOverlapped = {0};
        BOOL bOk = ::ReadFile(hProcessInfoPipe, pPe, sizeof(ProcessInfo), &dwRead, &olOverlapped);
		if (!bOk)
			Sleep(500);
		pilProcessInfo.AddTail(pPe);
	}
    m_RemoteAdministrator.m_cs.Unlock();
}

void CMachineDoc::DisconnectAndReconnectToRemoteService(CString strIP, CMachineView* pMachineView, CRemoteAdminView* pRemoteAdminView)
{
    CMachineInfo* pInfo = m_RemoteAdministrator.GetMachineInfo(strIP);
	if (pInfo == NULL)
		return;
	CString strPasswd = pInfo->GetPassword();
	CString strUserName = pInfo->GetUserName();
    CMainApp* pApp = (CMainApp*)AfxGetApp();
	CString strLog;
	CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)pMachineView->GetParent()->GetParent();
	
	if (strPasswd == CString("Could not retrieve the password"))
	{
		strLog = strIP + ":获取密码失败, 断开后重新连接 ";
		CString * p = new CString(strLog);
		pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
		pApp->ShowBalloonMsgInTray("错误", strLog);
		m_RemoteAdministrator.DisconnectAHost(strIP);
	}
	else  // Disconnect and try to reconnect the machine
	{
		strLog = strIP + ":连接失败, 重新连接 ";
		CString * p = new CString(strLog);
		pFrame->SendMessage(WM_SET_STATUSBAR_TEXT, 0, (LPARAM)p);
		pApp->ShowBalloonMsgInTray("错误", strLog);
		m_RemoteAdministrator.DisconnectAHost(strIP);
		/*if (m_RemoteAdministrator.IsMachineConnected(strIP) == FALSE)
		{
		ConnectInfo* pConnectInfo     = new ConnectInfo;
		pConnectInfo->pDoc             = this;
		pConnectInfo->pMachineView     = pMachineView;
		pConnectInfo->pAdminView       = pRemoteAdminView;
		pConnectInfo->strIP            = strIP;
		pConnectInfo->strPwd           = strPasswd;
		pConnectInfo->strUserName      = strUserName;
		if (m_RemoteAdministrator.IsConnectionPending(strIP) == FALSE)
		AfxBeginThread(AFX_THREADPROC(ConnectToMachine), pConnectInfo);
	}*/		
	}
	//MOVE TO HERE
	if (m_RemoteAdministrator.IsMachineConnected(strIP) == FALSE)
	{
		ConnectInfo* pConnectInfo     = new ConnectInfo;
		pConnectInfo->pDoc             = this;
		pConnectInfo->pMachineView     = pMachineView;
		pConnectInfo->pAdminView       = pRemoteAdminView;
		pConnectInfo->strIP            = strIP;
		pConnectInfo->strPwd           = strPasswd;
		pConnectInfo->strUserName      = strUserName;
		if (m_RemoteAdministrator.IsConnectionPending(strIP) == FALSE)
			AfxBeginThread(AFX_THREADPROC(ConnectToMachine), pConnectInfo);
	}	
}

BOOL CMachineView::DestroyWindow() 
{
	m_imglst.DeleteImageList();
	m_font.DeleteObject();
	return CTreeView::DestroyWindow();
}

void CMachineView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
    HICON hIconMachineOnNetwork = ::AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_MACHINE_ON_NETWORK));
    HICON hIconMachine  = ::AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_MACHINE));
   
    m_imglst.Create(20, 20, ILC_COLOR32 | ILC_MASK, 0, 1);
    m_imglst.Add(hIconMachineOnNetwork);
    m_imglst.Add(hIconMachine);
    GetTreeCtrl().SetImageList(&m_imglst, TVSIL_NORMAL);
	
	LOGFONT logfont = { 0 };
	CFont* pFont = GetTreeCtrl().GetFont();
	pFont->GetLogFont(&logfont);
	logfont.lfHeight = 10;
	m_font.CreateFontIndirect(&logfont);
	GetTreeCtrl().SetFont(&m_font);

	TVINSERTSTRUCT item = { 0 };
	CString str = "监控的主机";
	item.hParent= TVI_ROOT;
	item.hInsertAfter = TVI_FIRST;
	item.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	item.item.pszText = str.GetBuffer(0);
	item.item.iImage = MACHINE_IMAGE_ON_NETWORK;
	item.item.iSelectedImage = MACHINE_IMAGE_ON_NETWORK;
	item.item.lParam = 0;
	m_hMachineViewRoot = GetTreeCtrl().InsertItem(&item);
}

BOOL CMachineView::AddMachine(CString strIP, CString strUserName, CString strPassword, CMachineDoc* pDoc, CRemoteAdminView* pAdminView)
{
	if (pDoc->m_RemoteAdministrator.IsMachineConnected(strIP))
		return false;
	ConnectInfo* pInfo = new ConnectInfo;
	pInfo->pDoc = pDoc;
	pInfo->pMachineView = this;
	pInfo->pAdminView = pAdminView;
	pInfo->strIP = strIP;
	pInfo->strUserName = strUserName;
	pInfo->strPwd = strPassword;

	AfxBeginThread(AFX_THREADPROC(CMachineDoc::ConnectToMachine), pInfo);
	return true;
}

void CMachineView::DeleteMachine(CString strIP, CRemoteAdminView *pAdminView)
{
     HTREEITEM h = GetTreeItemForText(strIP);
	 if (h == NULL)
		 return;
	 CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	 pDoc->m_RemoteAdministrator.DisconnectAHost(strIP);
	 GetTreeCtrl().DeleteItem(h);
	 pAdminView->GetListCtrl().DeleteAllItems();
	 GetTreeCtrl().SelectItem(m_hMachineViewRoot);
}

CString CMachineView::GetSelectText()
{
	HTREEITEM hTree = GetTreeCtrl().GetSelectedItem();
	if (hTree == NULL)
		return "0";
	TVITEM item = { 0 };
   item.mask = TVIF_HANDLE|TVIF_PARAM;
   item.hItem = hTree;
   GetTreeCtrl().GetItem(&item);
   if (item.lParam == 0)
	   return "0";
   else
   {
	   return GetTreeCtrl().GetItemText(hTree);
   }

}
/////////////////////////////////////////////////////////////////////////////
// CRemoteLogOnDlg dialog


CRemoteLogOnDlg::CRemoteLogOnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteLogOnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteLogOnDlg)
	m_strUserName = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CRemoteLogOnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteLogOnDlg)
	DDX_Control(pDX, IDC_REMOTEIP, m_wndIP);
	DDX_Text(pDX, IDC_LOGON, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 20);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteLogOnDlg, CDialog)
	//{{AFX_MSG_MAP(CRemoteLogOnDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteLogOnDlg message handlers

void CRemoteLogOnDlg::OnOK() 
{
	if (UpdateData() == false)
		return;
	DWORD dwIP;
	m_wndIP.GetAddress(dwIP);	
	
	if (dwIP == 0)
	{
		AfxMessageBox("请输入有效的主机IP");
		return;
	}
	m_dwIP = htonl(dwIP);
	CDialog::OnOK();
}


LPARAM CMachineView::GetSelectedItemParam()
{
    CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CSplitterWnd* pParent = (CSplitterWnd*)GetParent();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pParent->GetPane(0, 1);
    HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	if (h == NULL)
		return 0;
	TVITEM item;
	item.mask = TVIF_HANDLE | TVIF_PARAM;
	item.hItem = h;
	GetTreeCtrl().GetItem(&item);
	return item.lParam;
}

void CMachineView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_MACHINE);
    CPoint pt = point;
	ClientToScreen(&pt);
	CMenu* pMenu = menu.GetSubMenu(0);
	SetMenuState(pMenu);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
	CTreeView::OnRButtonDown(nFlags, point);
}

void CMachineView::SetMenuState(CMenu *pMenu, int iShutDownMenuIndex)
{
    HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
	    EnableContextMenu(pMenu, false, iShutDownMenuIndex);
	else
        EnableContextMenu(pMenu, true, iShutDownMenuIndex);

}

void CMachineView::EnableContextMenu(CMenu *pMenu, bool bHost, int iShutDownMenuIndex)
{    //如果是根结点
     pMenu->EnableMenuItem(ID_FILE_ADD_MACHINE, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);
     pMenu->EnableMenuItem(ID_FILE_DELETE_MACHINE, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);
	 pMenu->EnableMenuItem(ID_FILE_REFRESHPROCESS, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);
	 pMenu->EnableMenuItem(ID_FILE_EXECUTE_PROCESS, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);
	 CMenu* pSubMenu = pMenu->GetSubMenu(iShutDownMenuIndex);
	 pSubMenu->EnableMenuItem(ID_FILE_SHUTDOWN_HALT, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);
	 pSubMenu->EnableMenuItem(ID_FILE_SHUTDOWN_REBOOT, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);
	 pSubMenu->EnableMenuItem(ID_FILESHUTDOWN_ABORTSHUTDOWN, MF_DISABLED | MF_GRAYED |MF_BYCOMMAND);

	 if (!bHost)
	 {
		 pMenu->EnableMenuItem(ID_FILE_ADD_MACHINE, MF_ENABLED |MF_BYCOMMAND);
		 return;
	 }
	 pMenu->EnableMenuItem(ID_FILE_DELETE_MACHINE, MF_ENABLED |MF_BYCOMMAND);
     pSubMenu->EnableMenuItem(ID_FILE_SHUTDOWN_HALT, MF_ENABLED |MF_BYCOMMAND);
	 pSubMenu->EnableMenuItem(ID_FILE_SHUTDOWN_REBOOT,MF_ENABLED |MF_BYCOMMAND);
	 pSubMenu->EnableMenuItem(ID_FILESHUTDOWN_ABORTSHUTDOWN,MF_ENABLED |MF_BYCOMMAND);
	 pMenu->EnableMenuItem(ID_FILE_REFRESHPROCESS, MF_ENABLED |MF_BYCOMMAND);
	 pMenu->EnableMenuItem(ID_FILE_EXECUTE_PROCESS,MF_ENABLED |MF_BYCOMMAND);
}

void CMachineView::OnKillFocus(CWnd* pNewWnd) 
{
	CTreeView::OnKillFocus(pNewWnd);
	ReleaseCapture();	
}

BOOL CMachineView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= TVS_HASLINES | 
                TVS_LINESATROOT | 
                TVS_HASBUTTONS | 
                TVS_SHOWSELALWAYS;
	return CTreeView::PreCreateWindow(cs);
}

void CMachineView::OnUpdateFileShutdownHalt(CCmdUI* pCmdUI) 
{
   HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
}

void CMachineView::OnUpdateFileShutdownReboot(CCmdUI* pCmdUI) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
}

void CMachineView::OnUpdateFileshutdownAbortshutdown(CCmdUI* pCmdUI) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
}

void CMachineView::OnUpdateFileExecuteProcess(CCmdUI* pCmdUI) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
}

void CMachineView::OnUpdateFileDeleteMachine(CCmdUI* pCmdUI) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
}

void CMachineView::OnUpdateFileAddMachine(CCmdUI* pCmdUI) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(TRUE);
	else
        pCmdUI->Enable(FALSE);
}

void CMachineView::OnUpdateFileRefreshprocess(CCmdUI* pCmdUI) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	DWORD dwParam = GetSelectedItemParam();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)((CSplitterWnd*)GetParent())->GetPane(0, 1);

	if (h == NULL || dwParam == 0 || strIP == "")
		pCmdUI->Enable(FALSE);
	else
        pCmdUI->Enable(TRUE);
}

void CMachineView::OnFileAddMachine() 
{
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CSplitterWnd* pParent = (CSplitterWnd*)GetParent();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pParent->GetPane(0, 1);
	CRemoteLogOnDlg dlg;
    
    if (dlg.DoModal() == IDOK)
    {
		CString strIP = inet_ntoa(*(in_addr*)&dlg.m_dwIP);
        BOOL bOK = AddMachine(strIP, dlg.m_strUserName, dlg.m_strPassword, pDoc, pAdminView);   
		if (bOK)
			pDoc->CreateVisualThread();
    }
}

void CMachineView::OnFileDeleteMachine() 
{
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CSplitterWnd* pParent = (CSplitterWnd*)GetParent();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pParent->GetPane(0, 1);
    HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	if (h == NULL)
		return;
	TVITEM item;
	item.mask = TVIF_HANDLE | TVIF_PARAM;
	item.hItem = h;
	GetTreeCtrl().GetItem(&item);
	if (item.lParam == 0)
		return;
	CString strIP = GetSelectText();
	DeleteMachine(strIP, pAdminView);
}

void CMachineView::OnFileRefreshprocess() 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
    CString strIP = GetSelectText();
	if (h == NULL || strIP == "0" || strIP == "")
		return;
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CSplitterWnd* pParent = (CSplitterWnd*)GetParent();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pParent->GetPane(0, 1);
	pAdminView->RefreshProcesses(pDoc, strIP);
}

void CMachineView::OnFileExecuteProcess() 
{
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CString strIP = GetSelectText();
	if (strIP == "0" || strIP == "")
		return;
	HANDLE hPipe = pDoc->m_RemoteAdministrator.GetProcessExecutePipe(strIP);
	if (hPipe == NULL)
		return;
    CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)GetParent()->GetParent();
    ThreadExitCommand cmd = {0};
    cmd.bThreadExit = FALSE;
    CExecuteRemoteProcessDlg dlg;
    
	dlg.m_strDomain = strIP;
    if (dlg.DoModal() == IDCANCEL)
		return;
    ExecuteCommand ExeCmd = {0};
    ::memcpy(ExeCmd.szDomain,      dlg.m_strDomain.GetBuffer(0),      _MAX_PATH);
    ::memcpy(ExeCmd.szPassword,    dlg.m_strPassword.GetBuffer(0),    _MAX_PATH);
    ::memcpy(ExeCmd.szProcessPath, dlg.m_strExePath.GetBuffer(0), _MAX_PATH);
    ::memcpy(ExeCmd.szUsername,    dlg.m_strUserName.GetBuffer(0),        _MAX_PATH);
	::memcpy(ExeCmd.szCmdLine,     dlg.m_strCmdLine.GetBuffer(0),        _MAX_PATH);
    BOOL bOk = FALSE;
    DWORD dwWritten = 0;

    bOk = ::WriteFile(hPipe, &cmd,     sizeof(ThreadExitCommand),        &dwWritten, NULL);
    bOk = ::WriteFile(hPipe, &ExeCmd,  sizeof(ExecuteCommand), &dwWritten, NULL);
    TCHAR szMessage[_MAX_PATH] = _T("");
    DWORD dwRead = 0;
    bOk = ::ReadFile(hPipe, szMessage, sizeof(szMessage), &dwRead, NULL);
    if (::strcmp(szMessage, _T("")) != 0)
          ::AfxMessageBox(szMessage);
}

void CMachineView::OnFileShutdownHalt() 
{
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CString strIP = GetSelectText();
	if (strIP == "0" || strIP == "")
		return;
	HANDLE hPipe = pDoc->m_RemoteAdministrator.GetSysShutDownPipe(strIP);
	if (hPipe == NULL)
		return;
    CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)GetParent()->GetParent();
    ThreadExitCommand cmd = {0};
    cmd.bThreadExit = FALSE;
    SysShutDownInfo shutdownInfo = {0};
    shutdownInfo.bReboot          = FALSE;
    shutdownInfo.bShutDown        = TRUE;
    shutdownInfo.iTimeToShutDown  = pFrame->m_iShutdownDelay/1000; // we require time in secs.
    DWORD dwWritten = 0;
    DWORD dwRead    = 0;
    BOOL bOk        = FALSE;
    TCHAR szMessage[_MAX_PATH] = _T("");

    bOk = ::WriteFile(hPipe, &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(hPipe, &shutdownInfo,  sizeof(SysShutDownInfo), &dwWritten, NULL);
    bOk = ::ReadFile(hPipe, szMessage, sizeof(szMessage), &dwRead, NULL);
	if (::strcmp(szMessage, _T("")) != 0)
           ::AfxMessageBox(szMessage);
}

void CMachineView::OnFileShutdownReboot() 
{
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CString strIP = GetSelectText();
	if (strIP == "0" || strIP == "")
		return;
	HANDLE hPipe = pDoc->m_RemoteAdministrator.GetSysShutDownPipe(strIP);
	if (hPipe == NULL)
		return;
    CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)GetParent()->GetParent();
    ThreadExitCommand cmd = {0};
    cmd.bThreadExit = FALSE;
    SysShutDownInfo shutdownInfo = {0};
    shutdownInfo.bReboot          = TRUE;
    shutdownInfo.bShutDown        = TRUE;
    shutdownInfo.iTimeToShutDown  = pFrame->m_iShutdownDelay/1000; // we require time in secs.
    DWORD dwWritten = 0;
    DWORD dwRead    = 0;
    BOOL bOk        = FALSE;
    TCHAR szMessage[_MAX_PATH] = _T("");

    bOk = ::WriteFile(hPipe, &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(hPipe, &shutdownInfo,  sizeof(SysShutDownInfo), &dwWritten, NULL);
    bOk = ::ReadFile(hPipe, szMessage, sizeof(szMessage), &dwRead, NULL);
	if (::strcmp(szMessage, _T("")) != 0)
           ::AfxMessageBox(szMessage);
}

void CMachineView::OnFileshutdownAbortshutdown() 
{
    	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CString strIP = GetSelectText();
	if (strIP == "0" || strIP == "")
		return;
	HANDLE hPipe = pDoc->m_RemoteAdministrator.GetSysShutDownPipe(strIP);
	if (hPipe == NULL)
		return;
    CRemoteAdminFrame* pFrame = (CRemoteAdminFrame*)GetParent()->GetParent();
    ThreadExitCommand cmd = {0};
    cmd.bThreadExit = FALSE;
    SysShutDownInfo shutdownInfo = {0};
    shutdownInfo.bShutDown = FALSE;
    DWORD dwWritten = 0;
    DWORD dwRead    = 0;
    BOOL bOk        = FALSE;
    TCHAR szMessage[_MAX_PATH] = _T("");

    bOk = ::WriteFile(hPipe, &cmd,     sizeof(ThreadExitCommand),        &dwWritten, NULL);
    bOk = ::WriteFile(hPipe, &shutdownInfo,  sizeof(SysShutDownInfo), &dwWritten, NULL);
    bOk = ::ReadFile(hPipe, szMessage, sizeof(szMessage), &dwRead, NULL);
    if (::strcmp(szMessage, _T("")) != 0)
           ::AfxMessageBox(szMessage);
}

void CRemoteAdminView::OnFileKillProcess() 
{
    ThreadExitCommand cmd;
    cmd.bThreadExit = FALSE;
    TCHAR szProcessID[10] = _T("");
    ::strcpy(szProcessID, m_strProcessID.GetBuffer(0));
    CMachineView* pMachineView = (CMachineView*)((CSplitterWnd*)GetParent())->GetPane(0, 0);
	CString strIP = pMachineView->GetSelectText();
	CMachineDoc* pDoc = (CMachineDoc*)pMachineView->m_pDocument;
	
	if (strIP == "0" || strIP == "")
		return;
	
    BOOL bOk = FALSE;
    DWORD dwWritten = 0;
    HANDLE hPipe = pDoc->m_RemoteAdministrator.GetProcessKillPipe(strIP);
	if (hPipe == NULL)
		return;
    bOk = ::WriteFile(hPipe, &cmd, sizeof(ThreadExitCommand), &dwWritten, NULL);
    bOk = ::WriteFile(hPipe, szProcessID, 10, &dwWritten, NULL);
    TCHAR szMessage[_MAX_PATH] = _T("");
    DWORD dwRead = 0;
    bOk = ::ReadFile(hPipe, szMessage, sizeof(szMessage), &dwRead, NULL);
    if (::strcmp(szMessage, _T("")) != 0)
        ::AfxMessageBox(szMessage);
}

void CRemoteAdminView::OnUpdateFileKillProcess(CCmdUI* pCmdUI) 
{
	if (m_strProcessID == "" || m_strProcessID == "0")
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CMachineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM h = GetTreeCtrl().GetSelectedItem();
	CString strIP = GetSelectText();
	CMachineDoc* pDoc = (CMachineDoc*)m_pDocument;
	CSplitterWnd* pParent = (CSplitterWnd*)GetParent();
	CRemoteAdminView* pAdminView = (CRemoteAdminView*)pParent->GetPane(0, 1);
	
	if (h == NULL || strIP == "" || strIP == "0")
        pAdminView->GetListCtrl().DeleteAllItems();
	else
		pAdminView->RefreshProcesses(pDoc, strIP);
	CTreeView::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// CExecuteRemoteProcessDlg dialog


CExecuteRemoteProcessDlg::CExecuteRemoteProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExecuteRemoteProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExecuteRemoteProcessDlg)
	m_strCmdLine = _T("");
	m_strDomain = _T("");
	m_strPassword = _T("");
	m_strExePath = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
}


void CExecuteRemoteProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExecuteRemoteProcessDlg)
	DDX_Text(pDX, IDC_EDIT_CMDLINE, m_strCmdLine);
	DDV_MaxChars(pDX, m_strCmdLine, 100);
	DDX_Text(pDX, IDC_EDIT_DOMAIN, m_strDomain);
	DDV_MaxChars(pDX, m_strDomain, 15);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 20);
	DDX_Text(pDX, IDC_EDIT_PROCESS_NAME, m_strExePath);
	DDV_MaxChars(pDX, m_strExePath, 100);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExecuteRemoteProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CExecuteRemoteProcessDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExecuteRemoteProcessDlg message handlers

void CExecuteRemoteProcessDlg::OnOK() 
{
	UpdateData();
	if (m_strExePath == "" || m_strUserName == "" ||m_strDomain == "")
	{
		AfxMessageBox("请设正确的参数");
		return;
	}
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
	m_strPrompt = _T("");
	//}}AFX_DATA_INIT
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS_BAR, m_wndProgress);
	DDX_Text(pDX, IDC_PROMPT, m_strPrompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

void CProgressDlg::SetDocument(CMachineDoc *pDoc)
{
    m_pDoc = pDoc;
}

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_strPrompt.Format("有%d台远程主机正在连接.......", m_pDoc->m_RemoteAdministrator.GetPendingConnectionCount());
	SetTimer(1, 300, NULL);
	return TRUE;  
}

void CProgressDlg::OnTimer(UINT nIDEvent) 
{
	if (m_pDoc->m_RemoteAdministrator.GetPendingConnectionCount() == 0)
		DestroyWindow();
	else
	{
		m_strPrompt.Format("有%d台远程主机正在连接.........", m_pDoc->m_RemoteAdministrator.GetPendingConnectionCount());
		UpdateData(FALSE);
		m_wndProgress.StepIt();
		CDialog::OnTimer(nIDEvent);
	}
}

void CProgressDlg::OnDestroy() 
{
	m_strPrompt = "连接正在完成.....";
	UpdateData(FALSE);
	Sleep(1000);
	KillTimer(1);
	CDialog::OnDestroy();
	delete this;
	AfxEndThread(0);
}

void CRemoteAdminView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags;
    int nItem = GetListCtrl().HitTest(point, &uFlags);
    if (nItem == -1)
	{
	    m_strProcessID = "0";
		return;	
	}
	GetListCtrl().SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	CListView::OnRButtonDown(nFlags, point);
	DWORD dw = GetListCtrl().GetItemData(nItem);
	if (dw == 0)
	{
		m_strProcessID = "0";	
		return;
	}
	char id[20] = { 0 };
	GetListCtrl().GetItemText(nItem, 1, id, 20);
	m_strProcessID = id;

	if (m_strProcessID == "0" || m_strProcessID == "")
		return;

	CMenu menu;
	menu.LoadMenu(IDR_MENU_END_PROCESS);
	CMenu* pMenu = menu.GetSubMenu(0);
	CPoint pt = point;
	ClientToScreen(&pt);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
}

void CRemoteAdminView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
    CHeaderCtrl* pHeader = GetListCtrl().GetHeaderCtrl();
	if (pHeader == NULL)
    {
		GetListCtrl().ModifyStyle(LVS_TYPEMASK, LVS_REPORT|LVS_SINGLESEL+LVS_SHOWSELALWAYS);
		GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT);
		GetListCtrl().InsertColumn(0, "程序", LVCFMT_LEFT, 175);
        GetListCtrl().InsertColumn(1, "进程ID", LVCFMT_LEFT, 100);
		GetListCtrl().InsertColumn(2, "线程数目", LVCFMT_LEFT, 100);
		GetListCtrl().InsertColumn(3, "内存占用(KB)", LVCFMT_LEFT, 175);
	}

	/*if (GetListCtrl().GetScrollBarCtrl(SB_VERT) == NULL)
		GetListCtrl().EnableScrollBarCtrl(SB_VERT);
    GetListCtrl().EnableScrollBar(SB_VERT);*/
    CScrollBar* pScrollBar = GetListCtrl().GetScrollBarCtrl(SB_VERT);
}

void CRemoteAdminView::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->lParam != 0)
	{
		ProcessInfo* pInfo = (ProcessInfo*)pNMListView->lParam;
		delete pInfo;
	}
	*pResult = 0;
}

void CRemoteAdminView::OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->lParam != 0)
	{
		ProcessInfo* pInfo = (ProcessInfo*)pNMListView->lParam;
		delete pInfo;
	}
	*pResult = 0;
}

void CRemoteAdminView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags;
    int nItem = GetListCtrl().HitTest(point, &uFlags);
    if (nItem == -1)
	{
		m_strProcessID = "0";
		return;	
	}
	GetListCtrl().SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	CListView::OnRButtonDown(nFlags, point);
	DWORD dw = GetListCtrl().GetItemData(nItem);
	if (dw == 0)
	{
		m_strProcessID = "0";
		return;
	}
	char id[20] = { 0 };
	GetListCtrl().GetItemText(nItem, 1, id, 20);
	m_strProcessID = id;

	CListView::OnLButtonDown(nFlags, point);
}

void CRemoteAdminView::SetMenuState(CMenu *pMenu)
{
    if (m_strProcessID == "" || m_strProcessID == "0")
		pMenu->EnableMenuItem(ID_FILE_KILL_PROCESS, MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	else
		pMenu->EnableMenuItem(ID_FILE_KILL_PROCESS, MF_BYCOMMAND|MF_ENABLED|MF_GRAYED);
}

LRESULT CRemoteAdminFrame::OnSetStatusBarText(WPARAM wParam, LPARAM lParam)
{
   int index = wParam;
   CString* p = (CString*)lParam;
   m_wndStatusBar.SetPaneText(index, *p);
   delete p;
   return 0;
}

IMPLEMENT_DYNAMIC(CRemoteControlDocTemplate, CSingleDocTemplate)

CRemoteControlDocTemplate::CRemoteControlDocTemplate()
		:CSingleDocTemplate(IDR_MAINFRAME,
		                    RUNTIME_CLASS(CMachineDoc),
		                    RUNTIME_CLASS(CRemoteAdminFrame),       // main SDI frame window
		                    RUNTIME_CLASS(CMachineView))
{
}
