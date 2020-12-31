// SSIDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SystemStateInfo.h"
#include "SSIDialog.h"

#include "SysInfoDialog.h"
#include "NetworkResourcesDialog.h"
#include "ApplicationsDialog.h"
#include "ProcessesDialog.h"
#include "ServicesDialog.h"

#include "OXSysInfo.h"
#include "OXSplashWnd.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define NUMTOPICS			5

/////////////////////////////////////////////////////////////////////////////
// CSSIDialog dialog

CSSIDialog::CSSIDialog(CWnd* pParent /*=NULL*/)	: 
			CDialog(CSSIDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSSIDialog)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	Initialize();
}

void CSSIDialog::Initialize()
{
	m_bInitialized=FALSE;

	m_nActivePage=-1;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// initialize Taskbar Icon
	IniTaskbarIcon();
}

void CSSIDialog::IniTaskbarIcon()
{
	m_TaskbarIcon.Create();
	// When there is only one taskbar icon, you don't need to specify an ID.
	// The ID is useful only when implementing two (or more) taskbar icons, AND you want 
	// to handle mouse messages from both icons within one message handler (therefore, you
	// need that ID to tell which icon posted the msg). However, it might be a good idea to
	// assign an ID, and check the ID in the message handler, especially when you may need
	// to derive your classes (somebody else may add another taskbar icon).

	// Note: you don't need to detroy a taskbar icon. It's done in its own destructor.

	m_TaskbarIcon.m_pPopupOwner = this;
	// let this dialog handle popup menu's message
	// Note: m_pPopupOwner is NOT a member of COXTaskbarIcon.

	m_TaskbarIcon.SetIcon(IDR_MAINFRAME);
	m_TaskbarIcon.SetTooltipText(IDR_MAINFRAME);
	m_TaskbarIcon.Show();
}

void CSSIDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSSIDialog)
	DDX_Control(pDX, IDC_BOTTOMSEPARATOR, m_ctlBottomSeparator);
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_btnRefresh);
	DDX_Control(pDX, IDC_TOPIC, m_ctlTopic);
	DDX_Control(pDX, IDC_SHB_TOPICS, m_shb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSSIDialog, CDialog)
	//{{AFX_MSG_MAP(CSSIDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_CLOSE, OnClose)
	ON_COMMAND(IDM_ABOUTBOX, OnAbout)
	ON_COMMAND(IDM_RESTORE, OnRestore)

	ON_NOTIFY(SHBN_ACTIVATEITEM,IDC_SHB_TOPICS,OnActivateItem)
	ON_NOTIFY(SHBN_CONTEXTMENU, IDC_SHB_TOPICS, OnSHBContextMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSIDialog message handlers

BOOL CSSIDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	COXSplashWnd wndSplash;
	// the fourth parameter is level of tolerance which
	// indicates how much the color can be different from CLR_DEFAULT (which is white) 
	// before it is actaully accepted as a different color 
	// for bitmap that we use in this application value of 150 is the best
	wndSplash.LoadBitmap(IDB_LOGO,CLR_NONE,NULL,0);
	wndSplash.SetUserCancel(FALSE);
	wndSplash.Show(SPLASH_NOTIMER,NULL);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	// Remove standard Restore, Maximize & Minimize items out of system menu.

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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
	
	// TODO: Add extra initialization here

	COXSysInfo m_SysInfo;
	BOOL bIsNTRunning=FALSE;
	m_SysInfo.IsNT(&bIsNTRunning);

	// set text color and font for separator
	static CFont font;
	VERIFY(font.CreatePointFont(140,_T("Times New Roman")));
	m_ctlTopic.SetFont(&font);
	m_ctlTopic.SetTextColor(RGB(128,0,0));

	// setup bitmap button
	VERIFY(m_btnRefresh.LoadBitmap(IDB_BITMAP_REFRESH,FALSE,RGB(255,0,255)));
	m_btnRefresh.SetToolTip(TRUE);
	m_btnRefresh.SetTrackLook(TRUE);
	m_btnRefresh.SetImageOffset(CPoint(0,0));
	m_btnRefresh.SetInnerFocusOffset(CPoint(2,2));

	// create image lists for shortcut bar
	VERIFY(m_ilLarge.Create(IDB_SHB_LARGE,32,11,RGB(255,0,255)));
	VERIFY(m_ilSmall.Create(IDB_SHB_SMALL,16,11,RGB(255,0,255)));

	//	populate shortcut bar
	SHB_GROUPINFO shbGroup;

	HSHBGROUP hGroup=m_shb.InsertGroup(_T("Topics"));
	ASSERT(hGroup!=NULL);
	m_shb.SetLCImageList(hGroup,&m_ilLarge,LVSIL_NORMAL);
	m_shb.SetLCImageList(hGroup,&m_ilSmall,LVSIL_SMALL);
	// insert statements
	// fill standard list controls
	const int nNumTopics=NUMTOPICS-(bIsNTRunning ? 0 : 1);
	TCHAR shbszItems[][20]={_T("System Info"),_T("Network Resources"),
		_T("Applications"), _T("Processes"),_T("Services")/*,_T("DLLs"),
		_T("Device Drivers"),_T("Perfomance")*/};
	for(int nIndex=0; nIndex<nNumTopics; nIndex++)
		VERIFY(m_shb.InsertLCItem(hGroup, nIndex, 
			shbszItems[nIndex], nIndex)==nIndex);
	//////////////////////

	m_shb.SetGroupHeaderHeight(hGroup,0);
	// expand Statements group
	m_shb.ExpandGroup(hGroup);
	

	DWORD dwBarStyle=m_shb.GetBarStyle();
	dwBarStyle|=SHBS_DISABLEDRAGDROPHEADER|SHBS_DISABLEDRAGDROPITEM|
		SHBS_BOLDEXPANDEDGROUP|SHBS_UNDERLINEHOTITEM|
		SHBS_SHOWACTIVEALWAYS|SHBS_INFOTIP;
	dwBarStyle&=~(SHBS_DRAWITEMDRAGIMAGE|SHBS_DRAWHEADERDRAGIMAGE|
		SHBS_AUTOEXPAND|SHBS_ANIMATEEXPAND|SHBS_EDITITEMS|SHBS_EDITHEADERS);
	m_shb.SetBarStyle(dwBarStyle);

	// layout manager 
	//
	m_LayoutManager.Attach(this);
	
	// shortcut bar control
	m_LayoutManager.TieChild(IDC_SHB_TOPICS,
		OX_LMS_TOP|OX_LMS_BOTTOM,OX_LMT_SAME);

	// topic disclaimer
	m_LayoutManager.TieChild(IDC_TOPIC,
		OX_LMS_TOP|OX_LMS_RIGHT|OX_LMS_LEFT,OX_LMT_SAME);

	// "Refresh" button
	m_LayoutManager.TieChild(IDC_BUTTON_REFRESH,
		OX_LMS_TOP|OX_LMS_RIGHT,OX_LMT_SAME);

	// bottom separator
	m_LayoutManager.TieChild(IDC_BOTTOMSEPARATOR,
		OX_LMS_BOTTOM|OX_LMS_RIGHT|OX_LMS_LEFT,OX_LMT_SAME);

	//////////////////////////////////////

	// initialize pages

	// system info
	CSysInfoDialog* pSysInfoDialog=new CSysInfoDialog();
	ASSERT(pSysInfoDialog!=NULL);
	PAGEDIALOG pageDialog(pSysInfoDialog,CSysInfoDialog::IDD);
	m_arrPages.Add(pageDialog);
	//////////////

	// network resources
	CNetworkResourcesDialog* pNetworkResourcesDialog=
		new CNetworkResourcesDialog();
	ASSERT(pNetworkResourcesDialog!=NULL);
	pageDialog.pPageDialog=pNetworkResourcesDialog;
	pageDialog.nTemplateID=CNetworkResourcesDialog::IDD;
	m_arrPages.Add(pageDialog);
	//////////////

	// applications
	CApplicationsDialog* pApplicationsDialog=
		new CApplicationsDialog();
	ASSERT(pApplicationsDialog!=NULL);
	pageDialog.pPageDialog=pApplicationsDialog;
	pageDialog.nTemplateID=CApplicationsDialog::IDD;
	m_arrPages.Add(pageDialog);
	//////////////

	// applications
	CProcessesDialog* pProcessesDialog=
		new CProcessesDialog();
	ASSERT(pProcessesDialog!=NULL);
	pageDialog.pPageDialog=pProcessesDialog;
	pageDialog.nTemplateID=CProcessesDialog::IDD;
	m_arrPages.Add(pageDialog);
	//////////////

	// services
	if(bIsNTRunning)
	{
		CServicesDialog* pServicesDialog=new CServicesDialog();
		ASSERT(pServicesDialog!=NULL);
		pageDialog.pPageDialog=pServicesDialog;
		pageDialog.nTemplateID=CServicesDialog::IDD;
		m_arrPages.Add(pageDialog);
	}
	//////////////

	pageDialog.pPageDialog=NULL;
	//////////////////////////////////////

	m_bInitialized=TRUE;

	COXSHBListCtrl* pListCtrl=m_shb.GetGroupListCtrl(hGroup);
	ASSERT(pListCtrl!=NULL);
	pListCtrl->ActivateItem(0);

	wndSplash.Hide();

	PostMessage(WM_NCACTIVATE,TRUE);

	return FALSE; 
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSSIDialog::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSSIDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSSIDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
		OnAbout();
	else
		CDialog::OnSysCommand(nID, lParam);
}

void CSSIDialog::OnClose()
{
	OnCancel();
}

// handling popup menu commands sent by the taskbar icon object
void CSSIDialog::OnRestore()
{
	SetForegroundWindow();
	PostMessage(WM_SYSCOMMAND,SC_RESTORE);
	ShowWindow(SW_SHOW);
}

void CSSIDialog::OnAbout()
{
	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();
}

void CSSIDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if(nType==SIZE_MINIMIZED)
	{
		m_TaskbarIcon.SetOwner(NULL); // let taskbar icon do it
		// This is only one way to hide the dialog window. In real situation, you may
		// want to try DestroyWindow() to conserve system resource if possible (in this
		// demo, this dialog is the main window).
		ShowWindow(SW_HIDE);
	}
	
	// TODO: Add your message handler code here
	if(m_bInitialized)
	{
		m_LayoutManager.OnSize(cx,cy);

		if(m_nActivePage!=-1)
		{
			CPageDialog* pPageDialog=NULL;
			pPageDialog=m_arrPages[m_nActivePage].pPageDialog;
			ASSERT(pPageDialog!=NULL);
			ASSERT(::IsWindow(pPageDialog->GetSafeHwnd()));

			pPageDialog->MoveWindow(GetPageRect());
		}
	}
}

void CSSIDialog::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnGetMinMaxInfo(lpMMI);

	lpMMI->ptMinTrackSize.x=400;
	lpMMI->ptMinTrackSize.y=300;
}

void CSSIDialog::OnCancel()
{
	m_arrPages.RemoveAll();

	CDialog::OnCancel();
}

void CSSIDialog::OnActivateItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMSHORTCUTBAR pNMSHB=(LPNMSHORTCUTBAR)pNotifyStruct;
	ASSERT(pNMSHB!=NULL);

	if(pNMSHB->nItem!=m_nActivePage && pNMSHB->nItem>=0 && 
		pNMSHB->nItem<m_arrPages.GetSize())
	{
		CPageDialog* pPageDialog=NULL;
		if(m_nActivePage!=-1)
		{
			pPageDialog=m_arrPages[m_nActivePage].pPageDialog;
			ASSERT(pPageDialog!=NULL);
			ASSERT(::IsWindow(pPageDialog->GetSafeHwnd()));
			pPageDialog->ShowWindow(SW_HIDE);
		}

		CRect rectFrame=GetPageRect();

		pPageDialog=m_arrPages[pNMSHB->nItem].pPageDialog;
		ASSERT(pPageDialog!=NULL);
		if(::IsWindow(pPageDialog->GetSafeHwnd()))
		{
			pPageDialog->ShowWindow(SW_SHOW);
			pPageDialog->MoveWindow(rectFrame);
		}
		else
		{
			VERIFY(pPageDialog->
				Create(MAKEINTRESOURCE(m_arrPages[pNMSHB->nItem].nTemplateID),
					this,rectFrame,pNMSHB->nItem));
			ASSERT(::IsWindow(pPageDialog->GetSafeHwnd()));
		}

		pPageDialog->SetFocus();

		m_btnRefresh.EnableWindow(pPageDialog->IsRefreshAvailable());

		m_nActivePage=pNMSHB->nItem;
	}

	ASSERT(m_shb.GetGroupListCtrl(pNMSHB->hGroup)!=NULL);
	CString sTopic=m_shb.GetGroupListCtrl(pNMSHB->hGroup)->
		GetItemText(pNMSHB->nItem,0);
	m_ctlTopic.SetWindowText(sTopic);
	Invalidate();

	*result=0;
}


void CSSIDialog::OnSHBContextMenu(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);
	*pResult=1;
}


CRect CSSIDialog::GetPageRect()
{
	CRect rectTopic;
	m_ctlTopic.GetWindowRect(rectTopic);
	ScreenToClient(rectTopic);

	CRect rectRefreshButton;
	m_btnRefresh.GetWindowRect(rectRefreshButton);
	ScreenToClient(rectRefreshButton);

	CRect rectBottomSeparator;
	m_ctlBottomSeparator.GetWindowRect(rectBottomSeparator);
	ScreenToClient(rectBottomSeparator);

	CRect rectPage(rectTopic.left,
		__max(rectTopic.bottom,rectRefreshButton.bottom)+5,
		rectRefreshButton.right,rectBottomSeparator.top);
	return rectPage;
}


void CSSIDialog::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here

	ASSERT(m_nActivePage>=0 && m_nActivePage<m_arrPages.GetSize());
	m_arrPages[m_nActivePage].pPageDialog->Refresh();
}

BOOL CSSIDialog::PreTranslateMessage(MSG* pMsg) 
{
	ASSERT_VALID(this);

	if (pMsg->message == WM_KEYDOWN)
	{
		if(m_nActivePage!=-1)
		{
			ASSERT(m_nActivePage>=0 && m_nActivePage<m_arrPages.GetSize());
			if(m_arrPages[m_nActivePage].pPageDialog->
				PreTranslateInput(pMsg))
				return TRUE;
		}
	}

	// handle rest with IsDialogMessage
	return CDialog::PreTranslateMessage(pMsg);
}
