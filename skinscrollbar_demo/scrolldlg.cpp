// scrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "scroll.h"
#include "scrollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "hyperlink.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_homeSite;
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
	DDX_Control(pDX, IDC_HOMESITE, m_homeSite);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg dialog

CScrollDlg::CScrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollDlg)
	DDX_Control(pDX, IDC_COMBO2, m_cbxTest2);
	DDX_Control(pDX, IDC_LIST2, m_ctrlLC);
	DDX_Control(pDX, IDC_COMBO1, m_cbxTest);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ctrlScroll1);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_ctrlScroll);
	DDX_Control(pDX, IDC_RICHEDIT1, m_ctrlRichEdit);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScrollDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_LC_MODE, OnLcMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg message handlers

BOOL CScrollDlg::OnInitDialog()
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
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	BITMAP bm;
	bmp.GetBitmap(&bm);
	m_hBmpScrollBar=(HBITMAP)bmp.Detach();

	SkinWndScroll(&m_ctrlTree,m_hBmpScrollBar);
	SkinWndScroll(&m_ctrlList,m_hBmpScrollBar);
	SkinWndScroll(&m_ctrlEdit,m_hBmpScrollBar);
	SkinWndScroll(&m_ctrlRichEdit,m_hBmpScrollBar);
	SkinWndScroll(&m_ctrlLC,m_hBmpScrollBar);
	m_cbxTest.SkinScroll(m_hBmpScrollBar);
	m_cbxTest2.SkinScroll(m_hBmpScrollBar);
	m_ctrlScroll.SetBitmap(m_hBmpScrollBar);

	m_ctrlLC.InsertColumn(0,"col1",0,80);
	m_ctrlLC.InsertColumn(1,"col2",0,80);
	char szbuf[50];
	for(int i=0;i<50;i++)
	{
		sprintf(szbuf,"item%d_1",i);
		m_ctrlLC.InsertItem(i,szbuf);
		sprintf(szbuf,"item%d_2",i);
		m_ctrlLC.SetItemText(i,1,szbuf);
	}
	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	si.nMax=100;
	si.nMin=0;
	si.nPage=10;
	si.nPos=5;
	m_ctrlScroll.SetScrollInfo(&si);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScrollDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScrollDlg::OnPaint() 
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
HCURSOR CScrollDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScrollDlg::OnButton1() 
{
	SCROLLINFO si={0};
	si.fMask=SIF_ALL;
	si.cbSize=sizeof(si);
	si.nMax=100;
	si.nMin=50;
	si.nPage=10;
	si.nPos=60;
	m_ctrlScroll1.SetScrollInfo(&si);

	static int s_Count=0;
	char szBuf[50];
	sprintf(szBuf,"item %d",s_Count++);
	m_ctrlList.AddString(szBuf);
}

void CScrollDlg::OnButton2() 
{
	static HTREEITEM hParent=TVI_ROOT;
	hParent=m_ctrlTree.InsertItem("test",hParent);
	m_ctrlTree.EnsureVisible(hParent);
}

void CScrollDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_ctrlEdit.GetSafeHwnd())
	{
		CWnd *pFrm=m_ctrlRichEdit.GetParent()->GetParent();
		pFrm->MoveWindow(cx-150,cy-180,150,180);
	}
}

void CScrollDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(	pScrollBar->m_hWnd==m_ctrlScroll.m_hWnd)
	{
		SCROLLINFO si;
		si.fMask=SIF_ALL;
		m_ctrlScroll.GetScrollInfo(&si,SIF_ALL);
		switch(nSBCode)
		{
		case SB_LINEUP:
			si.nPos--;
			break;
		case SB_LINEDOWN:
			si.nPos++;
			break;
		case SB_PAGEUP:
			si.nPos-=si.nPage;
			break;
		case SB_PAGEDOWN:
			si.nPos+=si.nPage;
			break;
		}
		if(si.nPos>(int)(si.nMax-si.nMin-si.nPage+1)) si.nPos=si.nMax-si.nMin-si.nPage+1;
		if(si.nPos<si.nMin) si.nPos=si.nMin;
		m_ctrlScroll.SetScrollInfo(&si);
	}
}

void CScrollDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(	pScrollBar->m_hWnd==m_ctrlScroll.m_hWnd)
	{
		SCROLLINFO si;
		si.fMask=SIF_ALL;
		m_ctrlScroll.GetScrollInfo(&si,SIF_ALL);
		switch(nSBCode)
		{
		case SB_LINEUP:
			si.nPos--;
			break;
		case SB_LINEDOWN:
			si.nPos++;
			break;
		case SB_PAGEUP:
			si.nPos-=si.nPage;
			break;
		case SB_PAGEDOWN:
			si.nPos+=si.nPage;
			break;
		case SB_THUMBTRACK:
			si.nPos=nPos;
			break;
		}
		if(si.nPos>(int)(si.nMax-si.nMin-si.nPage+1)) si.nPos=si.nMax-si.nMin-si.nPage+1;
		if(si.nPos<si.nMin) si.nPos=si.nMin;
		si.fMask=SIF_POS;
		m_ctrlScroll.SetScrollInfo(&si);
		TRACE("\nPos=%d",si.nPos);
	}
	
}

void CScrollDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DeleteObject(m_hBmpScrollBar);	
}

void CScrollDlg::OnAbout() 
{
	PostMessage(WM_SYSCOMMAND,IDM_ABOUTBOX);	
}

void CScrollDlg::OnButton3() 
{
	char szbuf[50];
	int nCount=m_cbxTest.GetCount();
	for(int i=0;i<5;i++)
	{
		sprintf(szbuf,"newitem%d",i+nCount);
		m_cbxTest.AddString(szbuf);
	}
	m_cbxTest.ShowDropDown(TRUE);
}

void CScrollDlg::OnLcMode() 
{
	static DWORD dwStyle=LVS_ICON;
	DWORD dwOldStyle=dwStyle;
	dwStyle++;
	if(dwStyle>LVS_LIST) dwStyle=LVS_ICON;
	m_ctrlLC.ModifyStyle(dwOldStyle,dwStyle);
}


