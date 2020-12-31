// PageColors.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "CustomizeTooltip.h"
#include "PageColors.h"
#include "TestPageGeneral.h"
#include ".\pagecolors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define GetTooltipWnd (CCustomizeTooltip*)(GetParent()->GetParent())
/////////////////////////////////////////////////////////////////////////////
// CPageColors property page

IMPLEMENT_DYNCREATE(CPageColors, CPropertyPage)

CPageColors::CPageColors() : CPropertyPage(CPageColors::IDD)
{
	//{{AFX_DATA_INIT(CPageColors)
	m_theme = 1;
	m_effect_bk = 13;
	m_granularity = 5;
	m_border = TRUE;
	m_custom_border = 0;
	m_border_width = 1;
	m_border_height = 1;
	m_transparency = 0;
	//}}AFX_DATA_INIT
}

CPageColors::~CPageColors()
{
}

void CPageColors::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageColors)
	DDX_Control(pDX, IDC_BUTTON4, m_border_color);
	DDX_Control(pDX, IDC_BUTTON3, m_end_bk);
	DDX_Control(pDX, IDC_BUTTON2, m_mid_bk);
	DDX_Control(pDX, IDC_BUTTON1, m_start_bk);
	DDX_CBIndex(pDX, IDC_COMBO2, m_theme);
	DDX_CBIndex(pDX, IDC_COMBO1, m_effect_bk);
	DDX_Text(pDX, IDC_EDIT1, m_granularity);
	DDV_MinMaxByte(pDX, m_granularity, 0, 255);
	DDX_Check(pDX, IDC_CHECK1, m_border);
	DDX_Radio(pDX, IDC_RADIO1, m_custom_border);
	DDX_Text(pDX, IDC_EDIT5, m_border_width);
	DDX_Text(pDX, IDC_EDIT6, m_border_height);
	DDX_Text(pDX, IDC_EDIT7, m_transparency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageColors, CPropertyPage)
	//{{AFX_MSG_MAP(CPageColors)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnChangeColorTheme)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnChangeEffect)
	ON_BN_CLICKED(IDC_CHECK1, OnShowBorder)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEffect)
	ON_EN_CHANGE(IDC_EDIT5, OnSetBorder)
	ON_EN_CHANGE(IDC_EDIT6, OnSetBorder)
	ON_BN_CLICKED(IDC_RADIO1, OnSetBorder)
	ON_BN_CLICKED(IDC_RADIO2, OnSetBorder)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeTransparency)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CPN_SELENDOK, OnChangeColorBk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageColors message handlers

BOOL CPageColors::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	OnChangeColorTheme();
	OnChangeEffect();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LONG CPageColors::OnChangeColorBk(UINT lParam, LONG wParam)
{
	// TODO: Add your control notification handler code here
//	CCustomizeTooltip * pDialog = (CCustomizeTooltip*)(GetParent()->GetParent());
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetColorBk(m_start_bk.GetColour(), m_mid_bk.GetColour(), m_end_bk.GetColour());
	OnSetBorder();
	
/*
	CTestPageGeneral * pPage = (CTestPageGeneral*)pDialog->m_examples.GetActivePage();
	pPage->m_tooltip.SetColorBk(m_start_bk.GetColour(), m_mid_bk.GetColour(), m_end_bk.GetColour());
*/
	return 0L;
}

void CPageColors::OnChangeColorTheme() 
{
	UpdateData();
	switch(m_theme)
	{
	case 0:
		//Standard
		m_start_bk.SetColour(RGB(255, 255, 223));
		m_mid_bk.SetColour(RGB(192, 192, 172));
		m_end_bk.SetColour(RGB(128, 128, 112));
		break;
	case 1:
		//Silver
		m_start_bk.SetColour(RGB(255, 255, 255));
		m_mid_bk.SetColour(RGB(240, 247, 255));
		m_end_bk.SetColour(RGB(192, 192, 208));
		break;
	case 2:
		//Button
		m_start_bk.SetColour(RGB(223, 223, 223));
		m_mid_bk.SetColour(RGB(191, 191, 191));
		m_end_bk.SetColour(RGB(127, 127, 127));
		break;
	case 3:
		//Exotic
		m_start_bk.SetColour(RGB(0, 255, 255));
		m_mid_bk.SetColour(RGB(255, 255, 0));
		m_end_bk.SetColour(RGB(0, 255, 0));
		break;
	case 4:
		//Aqua
		m_start_bk.SetColour(RGB(123, 158, 198));
		m_mid_bk.SetColour(RGB(173, 207, 247));
		m_end_bk.SetColour(RGB(198, 239, 255));
		break;
	case 5:
		//Chrome
		m_start_bk.SetColour(RGB(231, 251, 255));
		m_mid_bk.SetColour(RGB(214, 211, 214));
		m_end_bk.SetColour(RGB(165, 162, 173));
		break;
	case 6:
		//Gold
		m_start_bk.SetColour(RGB(255, 255, 148));
		m_mid_bk.SetColour(RGB(255, 231, 132));
		m_end_bk.SetColour(RGB(255, 207, 0));
		break;
	case 7:
		//Sunny
		m_start_bk.SetColour(RGB(255, 248, 229));
		m_mid_bk.SetColour(RGB(255, 209, 115));
		m_end_bk.SetColour(RGB(255, 156, 0));
		break;
	case 8:
		//Jungle
		m_start_bk.SetColour(RGB(214, 250, 183));
		m_mid_bk.SetColour(RGB(148, 236, 104));
		m_end_bk.SetColour(RGB(4, 202, 0));
		break;
	case 9:
		//Sky
		m_start_bk.SetColour(RGB(203, 233, 254));
		m_mid_bk.SetColour(RGB(88, 175, 241));
		m_end_bk.SetColour(RGB(0, 67, 202));
		break;
	case 10:
		//Fire
		m_start_bk.SetColour(RGB(255, 255, 0));
		m_mid_bk.SetColour(RGB(255, 104, 32));
		m_end_bk.SetColour(RGB(194, 3, 0));
		break;
	}
	OnChangeColorBk();
}

void CPageColors::OnChangeEffect() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetEffectBk(m_effect_bk, m_granularity);
}

void CPageColors::OnShowBorder() 
{
	OnSetBorder();
} //End OnShowBorder

void CPageColors::OnSetBorder() 
{
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	m_border_color.EnableWindow(m_border);
	GetDlgItem(IDC_STATIC1)->EnableWindow(m_border);
	GetDlgItem(IDC_STATIC2)->EnableWindow(m_border);
	GetDlgItem(IDC_RADIO1)->EnableWindow(m_border);
	GetDlgItem(IDC_RADIO2)->EnableWindow(m_border);
	GetDlgItem(IDC_EDIT5)->EnableWindow(m_border);
	GetDlgItem(IDC_EDIT6)->EnableWindow(m_border);
	if (m_border)
	{
		if (!m_custom_border)
			pDialog->m_general.m_tooltip.SetBorder(m_end_bk.GetColour(), m_border_width, m_border_height);
		else
			pDialog->m_general.m_tooltip.SetBorder(m_border_color.GetColour(), m_border_width, m_border_height);
	}
	else
	{
		pDialog->m_general.m_tooltip.HideBorder();
	} //if
} //End OnSetBorder

BOOL CPageColors::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CCustomizeTooltip * pDialog = GetTooltipWnd;
//	pDialog->m_tooltip.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CPageColors::OnChangeTransparency()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetTransparency(m_transparency);
}
