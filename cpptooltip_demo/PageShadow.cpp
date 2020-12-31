// PageShadow.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageShadow.h"
#include "CustomizeTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageShadow property page

IMPLEMENT_DYNCREATE(CPageShadow, CPropertyPage)

CPageShadow::CPageShadow() : CPropertyPage(CPageShadow::IDD)
{
	//{{AFX_DATA_INIT(CPageShadow)
	m_darken = 25;
	m_offset_x = 6;
	m_offset_y = 6;
	m_depth_x = 8;
	m_depth_y = 8;
	m_gradient = TRUE;
	m_img_darken = 25;
	m_img_offset_x = 6;
	m_img_offset_y = 6;
	m_img_depth_x = 8;
	m_img_depth_y = 8;
	m_img_gradient = TRUE;
	//}}AFX_DATA_INIT
}

CPageShadow::~CPageShadow()
{
}

void CPageShadow::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageShadow)
	DDX_Text(pDX, IDC_EDIT1, m_darken);
	DDV_MinMaxByte(pDX, m_darken, 0, 100);
	DDX_Text(pDX, IDC_EDIT3, m_offset_x);
	DDX_Text(pDX, IDC_EDIT4, m_offset_y);
	DDX_Text(pDX, IDC_EDIT6, m_depth_x);
	DDX_Text(pDX, IDC_EDIT7, m_depth_y);
	DDX_Check(pDX, IDC_CHECK3, m_gradient);
	DDX_Text(pDX, IDC_EDIT2, m_img_darken);
	DDX_Text(pDX, IDC_EDIT9, m_img_offset_x);
	DDX_Text(pDX, IDC_EDIT10, m_img_offset_y);
	DDX_Text(pDX, IDC_EDIT12, m_img_depth_x);
	DDX_Text(pDX, IDC_EDIT13, m_img_depth_y);
	DDX_Check(pDX, IDC_CHECK6, m_img_gradient);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageShadow, CPropertyPage)
	//{{AFX_MSG_MAP(CPageShadow)
	ON_BN_CLICKED(IDC_CHECK3, OnChangeGradient)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeTooltip)
	ON_BN_CLICKED(IDC_CHECK6, OnImgGradient)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeTooltip)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeTooltip)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeTooltip)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeTooltip)
	ON_EN_CHANGE(IDC_EDIT2, OnImgChange)
	ON_EN_CHANGE(IDC_EDIT9, OnImgChange)
	ON_EN_CHANGE(IDC_EDIT10, OnImgChange)
	ON_EN_CHANGE(IDC_EDIT13, OnImgChange)
	ON_EN_CHANGE(IDC_EDIT12, OnImgChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageShadow message handlers

BOOL CPageShadow::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	UpdateData(FALSE);
	OnChangeGradient();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageShadow::OnChangeGradient() 
{
	UpdateData();
	GetDlgItem(IDC_EDIT6)->EnableWindow(m_gradient);
	GetDlgItem(IDC_EDIT7)->EnableWindow(m_gradient);
	OnChangeTooltip();
}

void CPageShadow::OnChangeTooltip() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetTooltipShadow(m_offset_x, m_offset_y, m_darken, m_gradient, m_depth_x, m_depth_y);
}

void CPageShadow::OnImgGradient() 
{
	UpdateData();
	GetDlgItem(IDC_EDIT12)->EnableWindow(m_img_gradient);
	GetDlgItem(IDC_EDIT13)->EnableWindow(m_img_gradient);
	OnImgChange();
}

void CPageShadow::OnImgChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetImageShadow(m_img_offset_x, m_img_offset_y, m_img_darken, m_img_gradient, m_img_depth_x, m_img_depth_y);
}
