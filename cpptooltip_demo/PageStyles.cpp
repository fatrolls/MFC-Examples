// PageStyles.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageStyles.h"
#include "CustomizeTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageStyles property page

IMPLEMENT_DYNCREATE(CPageStyles, CPropertyPage)

CPageStyles::CPageStyles() : CPropertyPage(CPageStyles::IDD)
{
	//{{AFX_DATA_INIT(CPageStyles)
	m_anchor_placement = 0;
	//}}AFX_DATA_INIT
}

CPageStyles::~CPageStyles()
{
}

void CPageStyles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageStyles)
	DDX_Radio(pDX, IDC_RADIO1, m_anchor_placement);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageStyles, CPropertyPage)
	//{{AFX_MSG_MAP(CPageStyles)
	ON_BN_CLICKED(IDC_RADIO1, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO2, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO3, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO4, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO5, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO6, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO7, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO8, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO9, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO10, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO11, OnChangePlacement)
	ON_BN_CLICKED(IDC_RADIO12, OnChangePlacement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageStyles message handlers

BOOL CPageStyles::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	switch (pDialog->m_general.m_tooltip.GetDirection())
	{
	case PPTOOLTIP_TOPEDGE_LEFT:
		m_anchor_placement = 6;
		break;
	case PPTOOLTIP_TOPEDGE_RIGHT:
		m_anchor_placement = 8;
		break;
	case PPTOOLTIP_TOPEDGE_CENTER:
		m_anchor_placement = 7;
		break;
	case PPTOOLTIP_BOTTOMEDGE_LEFT:
		m_anchor_placement = 9;
		break;
	case PPTOOLTIP_BOTTOMEDGE_RIGHT:
		m_anchor_placement = 11;
		break;
	case PPTOOLTIP_BOTTOMEDGE_CENTER:
		m_anchor_placement = 10;
		break;
	case PPTOOLTIP_LEFTEDGE_TOP:
		m_anchor_placement = 0;
		break;
	case PPTOOLTIP_LEFTEDGE_BOTTOM:
		m_anchor_placement = 2;
		break;
	case PPTOOLTIP_LEFTEDGE_VCENTER:
		m_anchor_placement = 1;
		break;
	case PPTOOLTIP_RIGHTEDGE_TOP:
		m_anchor_placement = 3;
		break;
	case PPTOOLTIP_RIGHTEDGE_BOTTOM:
		m_anchor_placement = 5;
		break;
	case PPTOOLTIP_RIGHTEDGE_VCENTER:
		m_anchor_placement = 4;
		break;
	}
	UpdateData(FALSE);
	OnChangePlacement();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageStyles::OnChangePlacement() 
{
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	DWORD dwDirection = 0;
	switch (m_anchor_placement)
	{
	case 0:
		dwDirection = PPTOOLTIP_LEFTEDGE_TOP;
		break;
	case 1:
		dwDirection = PPTOOLTIP_LEFTEDGE_VCENTER;
		break;
	case 2:
		dwDirection = PPTOOLTIP_LEFTEDGE_BOTTOM;
		break;
	case 3:
		dwDirection = PPTOOLTIP_RIGHTEDGE_TOP;
		break;
	case 4:
		dwDirection = PPTOOLTIP_RIGHTEDGE_VCENTER;
		break;
	case 5:
		dwDirection = PPTOOLTIP_RIGHTEDGE_BOTTOM;
		break;
	case 6:
		dwDirection = PPTOOLTIP_TOPEDGE_LEFT;
		break;
	case 7:
		dwDirection = PPTOOLTIP_TOPEDGE_CENTER;
		break;
	case 8:
		dwDirection = PPTOOLTIP_TOPEDGE_RIGHT;
		break;
	case 9:
		dwDirection = PPTOOLTIP_BOTTOMEDGE_LEFT;
		break;
	case 10:
		dwDirection = PPTOOLTIP_BOTTOMEDGE_CENTER;
		break;
	case 11:
		dwDirection = PPTOOLTIP_BOTTOMEDGE_RIGHT;
		break;
	}
	pDialog->m_general.m_tooltip.SetDirection(dwDirection);
}
