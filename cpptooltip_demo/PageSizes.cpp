// PageSizes.cpp : implementation file
//

#include "stdafx.h"
#include "CPPToolTip_demo.h"
#include "PageSizes.h"
#include "CustomizeTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSizes property page

IMPLEMENT_DYNCREATE(CPageSizes, CPropertyPage)

CPageSizes::CPageSizes() : CPropertyPage(CPageSizes::IDD)
{
	//{{AFX_DATA_INIT(CPageSizes)
	m_margin_cx = 0;
	m_margin_cy = 0;
	m_rounded_cx = 0;
	m_rounded_cy = 0;
	m_anchor_width = 0;
	m_anchor_height = 0;
	m_anchor_offset = 0;
	m_offset_cx = 0;
	m_offset_cy = 0;
	//}}AFX_DATA_INIT
}

CPageSizes::~CPageSizes()
{
}

void CPageSizes::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSizes)
	DDX_Text(pDX, IDC_EDIT1, m_margin_cx);
	DDX_Text(pDX, IDC_EDIT3, m_margin_cy);
	DDX_Text(pDX, IDC_EDIT4, m_rounded_cx);
	DDX_Text(pDX, IDC_EDIT5, m_rounded_cy);
	DDX_Text(pDX, IDC_EDIT6, m_anchor_width);
	DDX_Text(pDX, IDC_EDIT7, m_anchor_height);
	DDX_Text(pDX, IDC_EDIT8, m_anchor_offset);
	DDX_Text(pDX, IDC_EDIT11, m_offset_cx);
	DDX_Text(pDX, IDC_EDIT12, m_offset_cy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSizes, CPropertyPage)
	//{{AFX_MSG_MAP(CPageSizes)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeSize)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSizes message handlers

BOOL CPageSizes::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	//Get default sizes
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	m_margin_cx = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_MARGIN_CX);
	m_margin_cy = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_MARGIN_CY);
	m_rounded_cx = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_ROUNDED_CX);
	m_rounded_cy = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_ROUNDED_CY);
	m_anchor_width = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_WIDTH_ANCHOR);
	m_anchor_height = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_HEIGHT_ANCHOR);
	m_anchor_offset = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_MARGIN_ANCHOR);
	m_offset_cx = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_OFFSET_ANCHOR_CX);
	m_offset_cy = pDialog->m_general.m_tooltip.GetSize(CPPToolTip::PPTTSZ_OFFSET_ANCHOR_CY);
		
	UpdateData(FALSE);
	OnChangeSize();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSizes::OnChangeSize() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	UINT nID = (UINT)LOWORD(GetCurrentMessage()->wParam);
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	switch (nID)
	{
	case IDC_EDIT1: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_MARGIN_CX, m_margin_cx); break;
	case IDC_EDIT3: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_MARGIN_CY, m_margin_cy); break;
	case IDC_EDIT4: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_ROUNDED_CX, m_rounded_cx); break;
	case IDC_EDIT5: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_ROUNDED_CY, m_rounded_cy); break;
	case IDC_EDIT6: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_WIDTH_ANCHOR, m_anchor_width); break;
	case IDC_EDIT7: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_HEIGHT_ANCHOR, m_anchor_height); break;
	case IDC_EDIT8: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_MARGIN_ANCHOR, m_anchor_offset); break;
	case IDC_EDIT11: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_OFFSET_ANCHOR_CX, m_offset_cx); break;
	case IDC_EDIT12: pDialog->m_general.m_tooltip.SetSize(CPPToolTip::PPTTSZ_OFFSET_ANCHOR_CY, m_offset_cy); break;
	}
}
