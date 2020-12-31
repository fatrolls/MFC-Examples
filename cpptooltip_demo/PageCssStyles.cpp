// PageCssStyles.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageCssStyles.h"
#include "CustomizeTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageCssStyles dialog
IMPLEMENT_DYNCREATE(CPageCssStyles, CPropertyPage)


CPageCssStyles::CPageCssStyles() : CPropertyPage(CPageCssStyles::IDD)
{
	//{{AFX_DATA_INIT(CPageCssStyles)
	m_css_styles = _T("");
	m_tag = _T("");
	m_styles = _T("");
	//}}AFX_DATA_INIT
}

CPageCssStyles::~CPageCssStyles()
{
}

void CPageCssStyles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCssStyles)
	DDX_Control(pDX, IDC_EDIT1, m_edit_css_styles);
	DDX_Text(pDX, IDC_EDIT1, m_css_styles);
	DDX_Text(pDX, IDC_EDIT2, m_tag);
	DDX_Text(pDX, IDC_EDIT9, m_styles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCssStyles, CPropertyPage)
	//{{AFX_MSG_MAP(CPageCssStyles)
	ON_BN_CLICKED(IDC_BUTTON1, OnApplyCssStyles)
	ON_BN_CLICKED(IDC_BUTTON2, OnSetIndividualStyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCssStyles message handlers

BOOL CPageCssStyles::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	m_css_styles = (CString)pDialog->m_tooltip.GetCssStyles();
	
	UpdateData(FALSE);

	m_font.CreateFont(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Verdana"));
	m_edit_css_styles.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageCssStyles::OnApplyCssStyles() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetCssStyles(m_css_styles);
}

void CPageCssStyles::OnSetIndividualStyle() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetTextStyle(m_tag, m_styles);
}
