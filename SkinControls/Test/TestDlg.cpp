
// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDuiManager = new CDUIManager;
	m_bMouseHover = false;
}

CTestDlg::~CTestDlg()
{
	SafeDelete(m_pDuiManager);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
	DDX_Control(pDX, IDC_RADIO3, m_tab1);
	DDX_Control(pDX, IDC_RADIO4, m_tab2);
	DDX_Control(pDX, IDC_CHECK2, m_checkbtn);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_STA_CLICK, m_staClick);
	DDX_Control(pDX, IDC_STA_SEP, m_staSep);
	DDX_Control(pDX, IDC_STA_LINK, m_link);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_TAB1, m_tabctrl);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	//DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CTestDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STA_CLICK, &CTestDlg::OnStnClickedStaClick)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_DUI_MESSAGE, OnDuiMessage)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// 消息解释
BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_SkinToolTipHelper.GetInterface() != NULL) m_SkinToolTipHelper->RelayEvent(pMsg);

	return __super::PreTranslateMessage(pMsg);
}

// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_btnCancel.SetButtonImage(L"btn_start.png", BF_PNG, true);

	m_tab1.SetButtonImage(L"btn_setting_tab.bmp", BF_BMP, true);
	m_tab2.SetButtonImage(L"btn_setting_tab.bmp", BF_BMP, true);

	m_checkbtn.SetButtonImage(L"btn_audio_control.bmp", BF_BMP, true);

	m_staSep.SetSeperator(true);

	m_tabctrl.InsertItem(0, L"tab1");
	m_tabctrl.InsertItem(1, L"tab2");

	 m_GifAnimation.SetAnimationInfo(m_hWnd, CPoint(0, 0), RGB(255, 255, 255));
	 m_GifAnimation.LoadFromFile(L"startup_processbar.gif");
	 m_GifAnimation.Play();

	 // 提示控件
	m_SkinToolTipHelper.CreateInstance();
	if (m_SkinToolTipHelper.GetInterface() != NULL)
	{
		m_SkinToolTipHelper->Create(this);
		/*m_SkinToolTipHelper->SetBehaviour(PPTOOLTIP_NOCLOSE_OVER | PPTOOLTIP_CLOSE_LEAVEWND | PPTOOLTIP_DISABLE_AUTOPOP);
		m_SkinToolTipHelper->AddTool(&m_staSet, _T("To open URL click <b><a href=\"http://www.codeproject.com\">link</a></b>"));*/
	}

	// directui controls
	m_pDuiManager->SetOwnerWnd(this);
	//CDUIGroupBox* pGroupBox = new CDUIGroupBox;
	//pGroupBox->CreateControl(5, m_pDuiManager, CRect(10, 235, 530, 390), L"DirectUI");
	//m_pDuiManager->AddControl(pGroupBox);
	/*CDUIButton* pButton = new CDUIButton;
	pButton->CreateControl(1, m_pDuiManager, CRect(0, 0, 0, 0));
	pButton->SetPos(50, 250, 93, 41);
	pButton->SetImage(L"btn_start.png", BF_PNG);
	m_pDuiManager->AddControl(pButton);
	pButton = new CDUIButton;
	pButton->CreateControl(2, m_pDuiManager, CRect(0, 0, 0, 0));
	pButton->SetPos(150, 250, 93, 41);
	pButton->SetImage(L"btn_start.png", BF_PNG);
	m_pDuiManager->AddControl(pButton);
	CDUILabel* pLabel = new CDUILabel;
	pLabel->CreateControl(3, m_pDuiManager, CRect(50, 335, 150, 349), L"测试Label");
	m_pDuiManager->AddControl(pLabel);
	pLabel = new CDUILabel;
	pLabel->CreateControl(4, m_pDuiManager, CRect(160, 335, 280, 349), L"测试HyperLink");
	pLabel->SetHyperLink(true, RGB(0,0,255), RGB(250,0,0));
	m_pDuiManager->AddControl(pLabel);

	CDUICheckBox* pCheckBox = new CDUICheckBox;
	pCheckBox->CreateControl(5, m_pDuiManager, CRect(0, 0, 0, 0), L"checkbox");
	pCheckBox->SetPos(290, 250, 100, 14);
	pCheckBox->SetImage(L"checkbox.bmp", BF_BMP);
	pCheckBox->SetCheck();
	m_pDuiManager->AddControl(pCheckBox);

	CDUIRadioBox* pRadioBox = new CDUIRadioBox;
	pRadioBox->CreateControl(6, m_pDuiManager, CRect(0, 0, 0, 0), L"radio1");
	pRadioBox->SetPos(290, 290, 100, 14);
	pRadioBox->SetImage(L"checkbox.bmp", BF_BMP);
	pRadioBox->SetGroup(1);
	pRadioBox->SetCheck();
	m_pDuiManager->AddControl(pRadioBox);

	pRadioBox = new CDUIRadioBox;
	pRadioBox->CreateControl(7, m_pDuiManager, CRect(0, 0, 0, 0), L"radio2");
	pRadioBox->SetPos(290, 320, 100, 14);
	pRadioBox->SetImage(L"checkbox.bmp", BF_BMP);
	pRadioBox->SetGroup(1);
	m_pDuiManager->AddControl(pRadioBox);

	pRadioBox = new CDUIRadioBox;
	pRadioBox->CreateControl(8, m_pDuiManager, CRect(0, 0, 0, 0), L"radio3");
	pRadioBox->SetPos(400, 290, 100, 14);
	pRadioBox->SetImage(L"checkbox.bmp", BF_BMP);
	pRadioBox->SetGroup(2);
	pRadioBox->SetCheck();
	m_pDuiManager->AddControl(pRadioBox);

	pRadioBox = new CDUIRadioBox;
	pRadioBox->CreateControl(9, m_pDuiManager, CRect(0, 0, 0, 0), L"radio4");
	pRadioBox->SetPos(400, 320, 100, 14);
	pRadioBox->SetImage(L"checkbox.bmp", BF_BMP);
	pRadioBox->SetGroup(2);
	m_pDuiManager->AddControl(pRadioBox);

	CDUISlider* pSlider = new CDUISlider;
	pSlider->CreateControl(10, m_pDuiManager, CRect(300, 350, 424, 368));
	pSlider->SetBgImage(L"slider1.png", BF_PNG);
	pSlider->SetProgressImage(L"slider2.png", BF_PNG);
	pSlider->SetThumbImage(L"thumb.png", BF_PNG);
	m_pDuiManager->AddControl(pSlider);*/

	CDUIDialogBuilder dlgbuilder;
	dlgbuilder.Create(L"duitest.xml", L"window", m_pDuiManager);

	SetWindowPos(NULL, 0, 0, m_pDuiManager->GetWndSize().cx, m_pDuiManager->GetWndSize().cy, SWP_NOMOVE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CPaintDC dc(this);
		m_GifAnimation.Draw(&dc);
		m_pDuiManager->PaintControls(&dc);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnBnClickedCancel()
{
	ShowMsgBox(L"你确定要退出？");
	OnCancel();
}

void CTestDlg::OnBnClickedOk()
{
	CSkinMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(0, 0, L"测试测试测试");
	menu.AppendMenu(0, 0, L"测试测试测试");
	menu.AppendMenu(0, 0, L"测试测试测试");
	CRect rc;
	m_btnOK.GetWindowRect(rc);
	menu.TrackPopupMenu(0, rc.left, rc.top, this);
}

void CTestDlg::OnStnClickedStaClick()
{
	if (m_SkinToolTipHelper.GetInterface() != NULL)
	{
		CRect rect;
		m_staClick.GetWindowRect(rect);
		CPoint pt = rect.CenterPoint();
		m_SkinToolTipHelper->ShowHelpTooltip(&pt, _T("<table><tr><td><left><icon idres=128 width=16 height=16><h2> 提示</h2><br>对不起，您现在还不是VIP会员，暂时无法使用VIP功能。<b><a href=\"http://www.codeproject.com\">升级为VIP会员</a></b></td></tr></table>"));
	}
}

void CTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseHover == false)
	{
		// 注册消息
		m_bMouseHover = true;
		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize = sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags = TME_LEAVE;
		TrackMouseEvent.hwndTrack = GetSafeHwnd();
		TrackMouseEvent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);
	}
	m_pDuiManager->OnMouseMove(point);

	CSkinDialog::OnMouseMove(nFlags, point);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_pDuiManager->OnLButtonDown(point);

	CSkinDialog::OnLButtonDown(nFlags, point);
}

void CTestDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_pDuiManager->OnLButtonUp(point);

	CSkinDialog::OnLButtonUp(nFlags, point);
}

LRESULT CTestDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bMouseHover = false;
	m_pDuiManager->OnMouseLeave();
	return 0;
}

LRESULT CTestDlg::OnDuiMessage(WPARAM wParam, LPARAM lParam)
{
	switch ((UINT)wParam)
	{
	case 1:
		AfxMessageBox(L"1");
		break;
	case 2:
		AfxMessageBox(L"2");
		break;
	case 4:
		AfxMessageBox(L"HYPERLINK");
		break;
	case 10:
		{
			CDUISlider* pSlider = (CDUISlider*)lParam;
			CString str;
			str.Format(L"%d", pSlider->GetValue());
			AfxMessageBox(str);
			break;
		}
	}
	return 0;
}

BOOL CTestDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	if (m_pDuiManager->OnMouseCursor(point))
	{
		return TRUE;
	}

	return CSkinDialog::OnSetCursor(pWnd, nHitTest, message);
}
