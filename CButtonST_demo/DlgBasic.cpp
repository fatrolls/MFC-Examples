#include "stdafx.h"
#include "CButtonST_Demo.h"
#include "DlgBasic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgBasic::CDlgBasic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBasic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBasic)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgBasic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBasic)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	// Make our buttons a CButtonST buttons
	DDX_Control(pDX, IDC_BTNSTANDARD, m_btnStandard);
	DDX_Control(pDX, IDC_BTNHALLOWEEN, m_btnHalloween);
	DDX_Control(pDX, IDC_BTNKEYMANAGER, m_btnKeyManager);
	DDX_Control(pDX, IDC_BTNDISABLED, m_btnDisabled);
	DDX_Control(pDX, IDC_BTNLAMP, m_btnLamp);
	DDX_Control(pDX, IDC_BTNZIP, m_btnZip);
	DDX_Control(pDX, IDC_BTNJPEG, m_btnJpeg);
	DDX_Control(pDX, IDC_BTNCDROM, m_btnCDRom);
	DDX_Control(pDX, IDC_BTNTOOLTIP, m_btnTooltip);
	DDX_Control(pDX, IDC_BTNSEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BTNBACK, m_btnBack);
	DDX_Control(pDX, IDC_BTNNEXT, m_btnNext);
}

BEGIN_MESSAGE_MAP(CDlgBasic, CDialog)
	//{{AFX_MSG_MAP(CDlgBasic)
	ON_BN_CLICKED(IDC_BTNDISABLED, OnBtnDisabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgBasic::OnInitDialog() 
{
	short	shBtnColor = 30;

	CDialog::OnInitDialog();

	// Standard button
	m_btnStandard.SetIcon(IDI_EOAPP);
	m_btnStandard.SetFlat(FALSE);
	// Halloween button
	m_btnHalloween.SetIcon(IDI_HALLOWEEN2, IDI_HALLOWEEN1);
	// 48x48 icon button
	m_btnKeyManager.SetIcon(IDI_KEYMANAGER);
	m_btnKeyManager.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	// Disabled button
	m_btnDisabled.SetIcon(IDI_SOUND);
	m_btnDisabled.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	// Lamp button
	m_btnLamp.SetIcon(IDI_LAMP1, (int)BTNST_AUTO_GRAY);
	m_btnLamp.DrawBorder(FALSE);
	// Zip button
	m_btnZip.SetIcon(IDI_ZIP1, 16, 16, IDI_ZIP1, 32, 32);
	m_btnZip.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	// Jpeg button
	m_btnJpeg.SetIcon(IDI_JPEG);
	m_btnJpeg.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnJpeg.EnableBalloonTooltip();
	m_btnJpeg.SetTooltipText(_T("This is a balloon tooltip"));
	// CDRom button
	m_btnCDRom.SetIcon(IDI_CDROM);
	m_btnCDRom.DrawBorder(FALSE);
	// Tooltip button
	m_btnTooltip.SetIcon(IDI_BALOON);
	m_btnTooltip.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnTooltip.SetTooltipText(_T("This is a tooltip.\r\nMultiline!"));
	// Search button
	m_btnSearch.SetIcon(IDI_SEARCH1, (int)BTNST_AUTO_GRAY);
	m_btnSearch.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnSearch.SetAlign(CButtonST::ST_ALIGN_VERT);
	// Back button
	m_btnBack.SetIcon(IDI_LEFT6);
	m_btnBack.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnBack.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
#ifdef	BTNST_USE_SOUND
	m_btnBack.SetSound(MAKEINTRESOURCE(IDR_WAVHOVER), ::GetModuleHandle(NULL));
#endif
	// Next button
	m_btnNext.SetIcon(IDI_RIGHT6);
	m_btnNext.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnNext.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_btnNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
#ifdef	BTNST_USE_SOUND
	m_btnNext.SetSound(MAKEINTRESOURCE(IDR_WAVHOVER), ::GetModuleHandle(NULL));
#endif

	return TRUE;
} // End of OnInitDialog

void CDlgBasic::OnOK()
{
} // End of OnOK

void CDlgBasic::OnCancel()
{
} // End of OnCancel

void CDlgBasic::OnBtnDisabled() 
{
	// Change button text
	m_btnDisabled.SetWindowText(_T("Disabled"));
	// Disable the button
	m_btnDisabled.EnableWindow(FALSE);
} // End of OnBtnDisabled
