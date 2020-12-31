// CustomizeTooltip.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "CustomizeTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeTooltip property page

IMPLEMENT_DYNCREATE(CCustomizeTooltip, CDialog)

CCustomizeTooltip::CCustomizeTooltip(CWnd* pParent /*=NULL*/)
: CDialog(CCustomizeTooltip::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgToolMemoryView)
	//}}AFX_DATA_INIT
}

void CCustomizeTooltip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeTooltip)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeTooltip, CDialog)
	//{{AFX_MSG_MAP(CCustomizeTooltip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeTooltip message handlers

BOOL CCustomizeTooltip::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rcSheet;
	
	// Initialize property pages
	m_examples.EnableStackedTabs(TRUE);
	m_examples.AddPage(&m_general);
	m_examples.AddPage(&m_hyperlinks);
	m_examples.AddPage(&m_images);
	m_examples.AddPage(&m_tables);
	m_examples.AddPage(&m_list_tree);
	m_examples.AddPage(&m_misc);
	m_examples.Create(this, WS_CHILD | WS_VISIBLE | WS_TABSTOP);//, WS_EX_CONTROLPARENT);
	m_examples.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	GetDlgItem(IDC_STATIC3)->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );
	m_examples.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );

	// Initialize property pages
	m_sheet.EnableStackedTabs(TRUE);
	m_sheet.AddPage(&m_page_colors);
	m_sheet.AddPage(&m_styles);
	m_sheet.AddPage(&m_page_behaviours);
	m_sheet.AddPage(&m_page_sizes);
	m_sheet.AddPage(&m_page_css_style);
	m_sheet.AddPage(&m_shadow);
	m_sheet.Create(this, WS_CHILD | WS_VISIBLE | WS_TABSTOP);//, WS_EX_CONTROLPARENT);
	m_sheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	GetDlgItem(IDC_STATIC1)->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );
	m_sheet.SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

