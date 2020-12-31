// TabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tab.h"
#include "TabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTabDlg dialog




CTabDlg::CTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	bShowTips = false;
}

void CTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTabDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_DELETE_ITEM, &CTabDlg::OnBnClickedDeleteItem)

	ON_NOTIFY(VSTAB_LBUTTONDOWN,VSTAB_ID,OnVSTabLButtonDown)
	ON_NOTIFY(VSTAB_RBUTTONDOWN,VSTAB_ID,OnVSTabRButtonDown)
	ON_NOTIFY(VSTAB_MOUSEMOVE, VSTAB_ID, OnVSTabMouseMove)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CTabDlg message handlers

BOOL CTabDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	m_ImageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_CLOSE_NORMAL));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_CLOSE_HOT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ADD));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_EDIT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_BLOCK));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_NEW));	//5
	
	CRect rc;
	GetClientRect( &rc );
	rc.top += 100;
	rc.bottom = rc.top + 25;
	rc.left += 20;
	rc.right -= 20;
	m_vsTab.Create(this, rc, VSTAB_ID);
	m_vsTab.SetImageList(&m_ImageList);

	m_ToolTip.Create(&m_vsTab);
	m_ToolTip.AddTool(&m_vsTab);

	m_menu.LoadMenu(IDR_MENU1);
	BCMenu::SetMenuDrawMode(BCMENU_DRAWMODE_XP);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTabDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTabDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabDlg::OnBnClickedButton1()
{
	CString tabTitle;
	int count = m_vsTab.GetItemCount();
	tabTitle.Format(_T("标签页 %d"), count);
	CTDlg *pDlg = new CTDlg;
	pDlg->Create(IDD_DIALOG1, this);
	pDlg->ShowWindow(SW_HIDE);
	pDlg->MoveWindow(0, 130, 500,300);
	pDlg->SetDlgItemText(IDOK, tabTitle);
	m_vsTab.InsertItem(tabTitle, pDlg, 3);
	//所有关于释放pDlg的内存我就懒得写啦
}

void CTabDlg::OnBnClickedDeleteItem()
{
	int nItem = m_vsTab.GetCurSel();
	m_vsTab.DeleteItem(nItem, true);
}

void CTabDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)&&BCMenu::IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			m_menu.MeasureItem(lpMeasureItemStruct);
			setflag=TRUE;
		}
	}
	if(!setflag)CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CTabDlg::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lresult;
	if(BCMenu::IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CDialog::OnMenuChar(nChar, nFlags, pMenu);
	return(lresult);
}

void CTabDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	if(!bSysMenu){
		if(BCMenu::IsMenu(pPopupMenu)) BCMenu::UpdateMenu(pPopupMenu);
	}
	
}

void CTabDlg::OnVSTabLButtonDown(NMHDR* pNMHDR, LRESULT*)
{
	NM_DATA* pData = (NM_DATA*)pNMHDR;


	if (pData->hitArea >= 0)
	{
		for (int i = 0; i < m_vsTab.GetItemCount(); i++)
		{
			m_vsTab.FindItem(i,true)->pWnd->ShowWindow(SW_HIDE);
			if (i == m_vsTab.GetCurSel())
				m_vsTab.FindItem(i,true)->pWnd->ShowWindow(SW_SHOW);
		}
	}
	else if (pData->hitArea == HIT_NEW_ITEM)
	{
		OnBnClickedButton1();
	}
	else if (pData->hitArea == HIT_CLOSE_ITEM)
	{
		OnBnClickedDeleteItem();
	}
	else if (pData->hitArea == HIT_DROP_MENU)
	{
		BCMenu *pMenu;
		pMenu = (BCMenu*)m_menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, 
			pData->hitPoint.x, pData->hitPoint.y, this);
	}

	delete pData;
}

void CTabDlg::OnVSTabRButtonDown(NMHDR* pNMHDR, LRESULT*)
{
	NM_DATA* pData = (NM_DATA*)pNMHDR;

	if (pData->hitArea >= 0)
	{
		m_vsTab.SetCurSel(pData->hitArea);
		BCMenu *pMenu, menu;
		menu.LoadMenu(IDR_MENU2);
		pMenu = (BCMenu*)menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, 
			pData->hitPoint.x, pData->hitPoint.y, this);

	}
	else if (pData->hitArea == HIT_NEW_ITEM)
	{
		//OnBnClickedButton1();
	}
	else if (pData->hitArea == HIT_CLOSE_ITEM)
	{
		//OnBnClickedDeleteItem();
	}
	else if (pData->hitArea == HIT_DROP_MENU)
	{
		//
	}

	delete pData;
}

void CTabDlg::OnVSTabMouseMove(NMHDR* pNMHDR, LRESULT*)
{
	NM_DATA* pData = (NM_DATA*)pNMHDR;

	if (pData->hitArea >= 0)
	{
		m_ToolTip.UpdateTipText(pData->pItem->strItem, &m_vsTab);
	}
	else if (pData->hitArea == HIT_NEW_ITEM)
	{
		m_ToolTip.UpdateTipText("新建新标签页", &m_vsTab);
	}
	else if (pData->hitArea == HIT_CLOSE_ITEM)
	{
		m_ToolTip.UpdateTipText("关闭选中的标签页", &m_vsTab);
	}
	else if (pData->hitArea == HIT_DROP_MENU)
	{
		m_ToolTip.UpdateTipText("显示所有的标签页", &m_vsTab);
	}
	bShowTips = (pData->hitArea!=HIT_OUT_OF_RANGE);
	m_ToolTip.Activate(bShowTips);
	delete pData;
}

BOOL CTabDlg::PreTranslateMessage(MSG* pMsg)
{
	if (NULL != m_ToolTip)
	{
		m_ToolTip.RelayEvent(pMsg);
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CTabDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//m_ToolTip.UpdateTipText(m_vsTab.GetItemText(0), &m_vsTab);

	CDialog::OnMouseMove(nFlags, point);
}
