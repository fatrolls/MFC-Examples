// TestCTabSheetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestCTabSheet.h"
#include "TestCTabSheetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTestCTabSheetDlg 对话框




CTestCTabSheetDlg::CTestCTabSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCTabSheetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCTabSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabSheet);
}

BEGIN_MESSAGE_MAP(CTestCTabSheetDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCTabSheetDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestCTabSheetDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &CTestCTabSheetDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTestCTabSheetDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CTestCTabSheetDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CTestCTabSheetDlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CTestCTabSheetDlg 消息处理程序

BOOL CTestCTabSheetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	//为TabCtrl控件添加图标
	m_imageList.Create(16, 16, ILC_COLOR32, 1, 1);
	CBitmap bitmap1,bitmap2;
	bitmap1.LoadBitmap(IDB_BITMAP1);
	bitmap2.LoadBitmap(IDB_BITMAP2);
	m_imageList.Add(&bitmap1, RGB(0,0,0));
	m_imageList.Add(&bitmap2, RGB(0,0,0));
	m_TabSheet.SetImageList(&m_imageList);
	
	//给TabCtrl添加页
	m_TabSheet.AddPage(_T("Page1"), &m_Page1, m_Page1.IDD, 0);
	m_TabSheet.AddPage(_T("第二页"), &m_Page2, m_Page2.IDD, 1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestCTabSheetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestCTabSheetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestCTabSheetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestCTabSheetDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TabSheet.EnableTab(1, !m_TabSheet.IsTabEnabled(1));
}

void CTestCTabSheetDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TabSheet.HideTab(!m_TabSheet.IsTabHided());
}

void CTestCTabSheetDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TabSheet.SetItemPos(m_TabSheet.TOP);
}

void CTestCTabSheetDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TabSheet.SetItemPos(m_TabSheet.LEFT);
}

void CTestCTabSheetDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TabSheet.SetItemPos(m_TabSheet.RIGHT);
}

void CTestCTabSheetDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TabSheet.SetItemPos(m_TabSheet.BOTTOM);
}
