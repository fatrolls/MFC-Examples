// PageTestMisc.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageTestMisc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTestMisc property page

IMPLEMENT_DYNCREATE(CPageTestMisc, CPropertyPage)

CPageTestMisc::CPageTestMisc() : CPropertyPage(CPageTestMisc::IDD)
{
	//{{AFX_DATA_INIT(CPageTestMisc)
	m_wrap_text = TRUE;
	m_width_tip = 300;
	//}}AFX_DATA_INIT
	m_bResizedButton = FALSE;
}

CPageTestMisc::~CPageTestMisc()
{
}

void CPageTestMisc::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTestMisc)
	DDX_Check(pDX, IDC_CHECK1, m_wrap_text);
	DDX_Text(pDX, IDC_EDIT1, m_width_tip);
	DDV_MinMaxInt(pDX, m_width_tip, 100, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTestMisc, CPropertyPage)
	//{{AFX_MSG_MAP(CPageTestMisc)
	ON_BN_CLICKED(IDC_BUTTON1, OnRuntimeResize)
	ON_BN_CLICKED(IDC_CHECK1, OnChangeWrapText)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeWidthTip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTestMisc message handlers

BOOL CPageTestMisc::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	//Dynamically created
	CRect rect;
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pButton = new CButton;
	m_pButton->Create(_T("Dynamic button"), WS_CHILD | WS_VISIBLE, rect, this, IDC_BUTTON2);
	
	m_tooltip.Create(this);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("<center><h2>Runtime resize</h2><br><hr color=blue></center><br>Click this button to resize it"));
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO1), _T("<center><h2>Child Window</h2><br><hr color=blue></center><br>A tooltip for a child window"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("<center><h2>Dynamic control</h2><br><hr color=blue></center><br>This control was dynamic created"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), _T("<center><h2>Wrapped Text</h2><br><hr color=blue></center><br><justify><b>C++ Standard Library <font color=red>(STL)</font></b> provides a set of common classes and interfaces that greatly extend the core C++ language. The library, however, is not self-explanatory. To make full use of its components-and to benefit from their power-you need a resource that does far more than list the classes and their functions.</justify><br=2><right><i>C++ Standard Library: A Tutorial and Reference<br>by Nicolai M. Josuttis</i></right>"));

	UpdateData(FALSE);
	OnChangeWidthTip();
	OnChangeWrapText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageTestMisc::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CPageTestMisc::OnRuntimeResize() 
{
	CButton * pButton = (CButton*)GetDlgItem(IDC_BUTTON1);
	CRect rect;
	pButton->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (m_bResizedButton)
	{
		rect.DeflateRect(0, 0, 50, 10);
		m_bResizedButton = FALSE;
	}
	else
	{
		rect.InflateRect(0, 0, 50, 10);
		m_bResizedButton = TRUE;
	}
	pButton->MoveWindow(rect);
}

void CPageTestMisc::OnChangeWrapText() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_wrap_text)
		m_tooltip.SetMaxTipWidth(m_width_tip);
	else
		m_tooltip.SetMaxTipWidth(0);
//	m_tooltip.EnableTextWrap(m_wrap_text);
}

void CPageTestMisc::OnChangeWidthTip() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_tooltip.SetMaxTipWidth(m_width_tip);
}

BOOL CPageTestMisc::OnKillActive() 
{
	m_tooltip.HideTooltip();
	return CPropertyPage::OnKillActive();
}
