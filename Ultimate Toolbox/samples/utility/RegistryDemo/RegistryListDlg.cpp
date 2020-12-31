// UNCListDlg.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "RegistryDemo.h"
#include "RegistryListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistryListDlg dialog


CRegistryListDlg::CRegistryListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegistryListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegistryListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRegistryListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistryListDlg)
	DDX_Control(pDX, IDCANCEL, m_wndClose);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegistryListDlg, CDialog)
	//{{AFX_MSG_MAP(CRegistryListDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistryListDlg message handlers

void CRegistryListDlg::SetSearchItem(COXIteratorRegistryItem iterItem, BOOL bIncludeValues,
	BOOL bIncludeSubkeys,	BOOL bReversedOrder, BOOL bRecursive,
	BOOL bDepthFirst)
	{
	m_bIncludeValues = bIncludeValues;
	m_bIncludeSubkeys = bIncludeSubkeys;
	m_bReversedOrder = bReversedOrder;
	m_bRecursive = bRecursive;
	m_bDepthFirst = bDepthFirst;
	m_iterItem = iterItem;
	}

BOOL CRegistryListDlg::OnInitDialog() 
	{
	CDialog::OnInitDialog();
	
	// ... Set a timer so that the list will be filled whan this window is
	//     fully initialized and visisble
	SetTimer(0, 10, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

void CRegistryListDlg::OnTimer(UINT nIDEvent) 
	{
	if (!IsWindowVisible())
		// ... Only start the list when we are visible, 
		//     otherwise wait for the next timer event.
		return;

	// ... Kill the running timer
	KillTimer(0);

	m_wndClose.EnableWindow(FALSE);

	int nTopIndex = 0;
	m_iterItem.Start(m_bIncludeValues, m_bIncludeSubkeys, m_bReversedOrder, 
		m_bRecursive, m_bDepthFirst);
	while(!m_iterItem.IsEmpty())
		{
		m_wndList.AddString(m_iterItem.GetFullRegistryItem());
		m_wndList.SetTopIndex(nTopIndex++);
		m_wndList.RedrawWindow(NULL, NULL, RDW_UPDATENOW);
		m_iterItem++;
		}
	m_iterItem.End();

	m_wndClose.EnableWindow(TRUE);

	CDialog::OnTimer(nIDEvent);
	}
