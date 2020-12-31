// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ApplicationBar.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
	m_bAutoHide = FALSE;
	m_bOnTop = FALSE;
	m_nEdge=-1;
	//}}AFX_DATA_INIT
}


void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
	DDX_Check(pDX, IDC_CHECK_AUTOHIDE, m_bAutoHide);
	DDX_Check(pDX, IDC_CHECK_ONTOP, m_bOnTop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_BN_CLICKED(IDC_RADIO_LEFT, OnRadioLeft)
	ON_BN_CLICKED(IDC_RADIO_TOP, OnRadioTop)
	ON_BN_CLICKED(IDC_RADIO_RIGHT, OnRadioRight)
	ON_BN_CLICKED(IDC_RADIO_BOTTOM, OnRadioBottom)
	ON_BN_CLICKED(ID_APPLY, OnApply)
	ON_BN_CLICKED(IDC_CHECK_AUTOHIDE, OnCheckAutohide)
	ON_BN_CLICKED(IDC_CHECK_ONTOP, OnCheckOntop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

void COptionsDialog::OnRadioLeft() 
{
	if (m_nEdge == ABE_LEFT)
		return;
	
	m_nEdge=ABE_LEFT;
	EnableApply();
	
}

void COptionsDialog::OnRadioTop() 
{
	if (m_nEdge == ABE_TOP)
		return;
	
	m_nEdge=ABE_TOP;
	EnableApply();
}

void COptionsDialog::OnRadioRight() 
{
	if (m_nEdge == ABE_RIGHT)
		return;
	
	m_nEdge=ABE_RIGHT;
	EnableApply();
	
}

void COptionsDialog::OnRadioBottom() 
{
	if (m_nEdge == ABE_BOTTOM)
		return;
	
	m_nEdge=ABE_BOTTOM;
	EnableApply();
}

void COptionsDialog::OnApply() 
{
	//m_appBar.m_nEdge=m_nEdge;
	if (!::IsWindow(m_appBar.m_hWnd))
	{
		VERIFY(m_appBar.Create(IDD_APPLICATIONBAR_DIALOG,NULL));
		m_appBar.ModifyStyleEx(0,WS_EX_TOOLWINDOW);
		m_appBar.Register(TRUE, m_nEdge);
	}
	else
		m_appBar.SetEdge(m_nEdge);
	UpdateData(TRUE);
	m_appBar.SetAutoHide(m_bAutoHide);

	
}

void COptionsDialog::EnableApply(BOOL bApply)
{
	CWnd* pWnd=GetDlgItem(ID_APPLY);
	pWnd->EnableWindow(bApply);

}

void COptionsDialog::OnCheckAutohide() 
{
	UpdateData();
	if (m_nEdge!=-1)
		EnableApply();
}

void COptionsDialog::OnCheckOntop() 
{
	UpdateData();
	if (m_nEdge!=-1)
		EnableApply();
}

