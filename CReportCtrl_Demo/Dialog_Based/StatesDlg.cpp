// StatesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "reportctrldemo.h"
#include "StatesDlg.h"
#include "ReportCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatesDlg dialog


CStatesDlg::CStatesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatesDlg)
	m_bAll = FALSE;
	m_bChecked = FALSE;
	m_bFocused = FALSE;
	m_bSelected = FALSE;
	m_bUnfocused = FALSE;
	m_bUnchecked = FALSE;
	m_bUnselected = FALSE;
	//}}AFX_DATA_INIT
	m_dwStates = RC_ITEM_NONE;
}


void CStatesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatesDlg)
	DDX_Check(pDX, IDC_ALL, m_bAll);
	DDX_Check(pDX, IDC_CHECKED, m_bChecked);
	DDX_Check(pDX, IDC_FOCUSED, m_bFocused);
	DDX_Check(pDX, IDC_SELECTED, m_bSelected);
	DDX_Check(pDX, IDC_UNFOCUSED, m_bUnfocused);
	DDX_Check(pDX, IDC_UNCHECKED, m_bUnchecked);
	DDX_Check(pDX, IDC_UNSELECTED, m_bUnselected);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatesDlg, CDialog)
	//{{AFX_MSG_MAP(CStatesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatesDlg message handlers

void CStatesDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_dwStates = RC_ITEM_NONE;
	UpdateData(TRUE);
	if (m_bAll)
		m_dwStates |= RC_ITEM_ALL;

	if (m_bSelected)
		m_dwStates |= RC_ITEM_SELECTED;

	if (m_bUnselected)
		m_dwStates |= RC_ITEM_UNSELECTED;

	if (m_bChecked)
		m_dwStates |= RC_ITEM_CHECKED;

	if (m_bUnchecked)
		m_dwStates |= RC_ITEM_UNCHECKED;

	if (m_bFocused)
		m_dwStates |= RC_ITEM_FOCUSED;

	if (m_bUnfocused)
		m_dwStates |= RC_ITEM_UNFOCUSED;

	EndDialog(IDOK);
}

DWORD CStatesDlg::GetStates() const
{
	return m_dwStates;
}
