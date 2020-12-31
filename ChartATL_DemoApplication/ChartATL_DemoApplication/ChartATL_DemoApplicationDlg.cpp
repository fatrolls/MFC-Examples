// ChartATL_DemoApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChartATL_DemoApplication.h"
#include "ChartATL_DemoApplicationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChartATL_DemoApplicationDlg dialog
static int RxValue, TxValue;

CChartATL_DemoApplicationDlg::CChartATL_DemoApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartATL_DemoApplicationDlg::IDD, pParent)
	, m_DispVal1(0)
	, m_DispVal2(0)
	, m_TargetVal1(0)
	, m_TargetVal2(0)
	, m_RBack(0)
	, m_GBack(0)
	, m_BBack(0)
	, m_RHori(0)
	, m_GHori(0)
	, m_BHori(0)
	, m_RVer(0)
	, m_GVer(0)
	, m_BVer(0)
	, m_RChart1(0)
	, m_GChart1(0)
	, m_BChart1(0)
	, m_RChart2(0)
	, m_GChart2(0)
	, m_BChart2(0)
	, m_RefreshSpeed(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChartATL_DemoApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_DispVal1);
	DDX_Text(pDX, IDC_EDIT4, m_DispVal2);
	DDX_Text(pDX, IDC_EDIT1, m_TargetVal1);
	DDX_Text(pDX, IDC_EDIT2, m_TargetVal2);
	DDX_Text(pDX, IDC_EDIT5, m_RBack);
	DDX_Text(pDX, IDC_EDIT6, m_GBack);
	DDX_Text(pDX, IDC_EDIT7, m_BBack);
	DDX_Text(pDX, IDC_EDIT8, m_RHori);
	DDX_Text(pDX, IDC_EDIT9, m_GHori);
	DDX_Text(pDX, IDC_EDIT10, m_BHori);
	DDX_Text(pDX, IDC_EDIT11, m_RVer);
	DDX_Text(pDX, IDC_EDIT12, m_GVer);
	DDX_Text(pDX, IDC_EDIT13, m_BVer);
	DDX_Text(pDX, IDC_EDIT14, m_RChart1);
	DDX_Text(pDX, IDC_EDIT15, m_GChart1);
	DDX_Text(pDX, IDC_EDIT16, m_BChart1);
	DDX_Text(pDX, IDC_EDIT17, m_RChart2);
	DDX_Text(pDX, IDC_EDIT18, m_GChart2);
	DDX_Text(pDX, IDC_EDIT19, m_BChart2);
	DDX_Control(pDX, IDC_COMBO2, m_HoriStyle);
	DDX_Control(pDX, IDC_COMBO3, m_VerStyle);
	DDX_Control(pDX, IDC_COMBO4, m_Chart1Style);
	DDX_Control(pDX, IDC_COMBO5, m_Chart2Style);
	DDX_Control(pDX, IDC_CHARTCTRL1, m_ChartCtrl);
	DDX_Text(pDX, IDC_EDIT20, m_RefreshSpeed);
}

BEGIN_MESSAGE_MAP(CChartATL_DemoApplicationDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CChartATL_DemoApplicationDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CChartATL_DemoApplicationDlg::OnEnChangeEdit1)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_EDIT5, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT7, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit7)
	ON_EN_KILLFOCUS(IDC_EDIT8, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit8)
	ON_EN_KILLFOCUS(IDC_EDIT9, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT10, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit10)
	ON_EN_KILLFOCUS(IDC_EDIT11, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit11)
	ON_EN_KILLFOCUS(IDC_EDIT12, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit12)
	ON_EN_KILLFOCUS(IDC_EDIT13, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit13)
	ON_EN_KILLFOCUS(IDC_EDIT14, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit14)
	ON_EN_KILLFOCUS(IDC_EDIT15, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit15)
	ON_EN_KILLFOCUS(IDC_EDIT16, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit16)
	ON_EN_KILLFOCUS(IDC_EDIT17, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit17)
	ON_EN_KILLFOCUS(IDC_EDIT18, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit18)
	ON_EN_KILLFOCUS(IDC_EDIT19, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit19)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo5)
	ON_EN_CHANGE(IDC_EDIT11, &CChartATL_DemoApplicationDlg::OnEnChangeEdit11)
	ON_EN_KILLFOCUS(IDC_EDIT20, &CChartATL_DemoApplicationDlg::OnEnKillfocusEdit20)
	ON_EN_CHANGE(IDC_EDIT13, &CChartATL_DemoApplicationDlg::OnEnChangeEdit13)
END_MESSAGE_MAP()


// CChartATL_DemoApplicationDlg message handlers

BOOL CChartATL_DemoApplicationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LoadLibrary(_T("ChartATL.dll"));

	UpdateData(TRUE);
	m_TargetVal1 = 100;
	m_TargetVal2 = 150;
	m_RefreshSpeed = 300;
	m_RHori = 0 ;
	m_GHori = 125;
	m_BHori = 0;
	m_RVer = 0;
	m_GVer = 125;
	m_BVer = 0;

	m_RChart1 = 255;
	m_GChart1 = 255;
	m_BChart1 = 0;

	m_RChart2 = 255;
	m_GChart2 = 0;
	m_BChart2 = 0;

	m_HoriStyle.SetCurSel(0);
	m_VerStyle.SetCurSel(0);
	m_Chart1Style.SetCurSel(0);
	m_Chart2Style.SetCurSel(0);

	UpdateData(FALSE);
	SetTimer(1, 500, NULL);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChartATL_DemoApplicationDlg::OnPaint()
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
HCURSOR CChartATL_DemoApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChartATL_DemoApplicationDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CChartATL_DemoApplicationDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	do
	{
		RxValue = rand();
		RxValue = (RxValue % m_TargetVal1);
	}while(RxValue > m_TargetVal1);
	do
	{
		TxValue = rand();
		TxValue = (TxValue % m_TargetVal2);
	}while(TxValue > m_TargetVal2);

	UpdateData(TRUE);
	m_DispVal1 = RxValue;
	m_DispVal2 = TxValue;
	UpdateData(FALSE);
	m_ChartCtrl.UpdateChart(RxValue, TxValue);
	CDialog::OnTimer(nIDEvent);
}

void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit5()
{
	SetBackColor();
	// TODO: Add your control notification handler code here
}

void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit6()
{
	SetBackColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit7()
{
	SetBackColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit8()
{
	SetHoriColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit9()
{
	SetHoriColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit10()
{
	SetHoriColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit11()
{
	SetVerColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit12()
{
	SetVerColor();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit13()
{
	SetVerColor();
	// TODO: Add your control notification handler code here
}

void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit14()
{
	SetChart1Color();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit15()
{
	SetChart1Color();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit16()
{
	SetChart1Color();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit17()
{
	SetChart2Color();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit18()
{
	SetChart2Color();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit19()
{
	SetChart2Color();
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::SetBackColor()
{
	UpdateData(TRUE);
	m_ChartCtrl.put_BackColor(RGB(m_RBack, m_GBack, m_BBack));
	UpdateData(FALSE);
}
void CChartATL_DemoApplicationDlg::SetHoriColor()
{
	UpdateData(TRUE);
	m_ChartCtrl.put_HorizontalLineColor(RGB(m_RHori, m_GHori, m_BHori));
	UpdateData(FALSE);
}
void CChartATL_DemoApplicationDlg::SetVerColor()
{
	UpdateData(TRUE);
	m_ChartCtrl.put_VerticalLineColor(RGB(m_RVer, m_GVer, m_BVer));
	UpdateData(FALSE);						
}
void CChartATL_DemoApplicationDlg::SetChart1Color()
{
	UpdateData(TRUE);
	m_ChartCtrl.put_ChartColor_1(RGB(m_RChart1, m_GChart1, m_BChart1));
	UpdateData(FALSE);						
}									 

void CChartATL_DemoApplicationDlg::SetChart2Color()
{
	UpdateData(TRUE);
	m_ChartCtrl.put_ChartColor_2(RGB(m_RChart2, m_GChart2, m_BChart2));
	UpdateData(FALSE);						
}	
void CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo2()
{
	int Sel;
	Sel = m_HoriStyle.GetCurSel();
	m_ChartCtrl.put_HorizontalLineStyle(LONG (Sel));
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo3()
{
	int Sel;
	Sel = m_VerStyle.GetCurSel();
	m_ChartCtrl.put_VerticalLineStyle(LONG (Sel));
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo4()
{
	int Sel;
	Sel = m_Chart1Style.GetCurSel();
	m_ChartCtrl.put_ChartFillStyle_1(LONG (Sel));
	// TODO: Add your control notification handler code here
}
void CChartATL_DemoApplicationDlg::OnCbnSelchangeCombo5()
{
	int Sel;
	Sel = m_Chart2Style.GetCurSel();
	m_ChartCtrl.put_ChartFillStyle_2(LONG (Sel));
	// TODO: Add your control notification handler code here
}

void CChartATL_DemoApplicationDlg::OnEnChangeEdit11()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CChartATL_DemoApplicationDlg::OnEnKillfocusEdit20()
{
	UpdateData(TRUE);
	m_ChartCtrl.put_RefreshSpeed(m_RefreshSpeed);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}

void CChartATL_DemoApplicationDlg::OnEnChangeEdit13()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
