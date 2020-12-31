// UNCListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "URLDemo.h"
#include "UNCListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUNCListDlg dialog


CUNCListDlg::CUNCListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUNCListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUNCListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUNCListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUNCListDlg)
	DDX_Control(pDX, IDCANCEL, m_wndClose);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUNCListDlg, CDialog)
	//{{AFX_MSG_MAP(CUNCListDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUNCListDlg message handlers

void CUNCListDlg::SetSearchUnc(COXIteratorUNC iterUNC, BOOL bFiles, BOOL bDirs, 
	BOOL bRecursive, BOOL bDepthFirst)
	{
	m_iterUNC = iterUNC;
	m_bFiles = bFiles;
	m_bDirs = bDirs;
	m_bRecursive = bRecursive;
	m_bDepthFirst = bDepthFirst;
	}

BOOL CUNCListDlg::OnInitDialog() 
	{
	CDialog::OnInitDialog();
	
	// ... Set a timer so that the list will be filled whan this window is
	//     fully initialized and visisble
	SetTimer(0, 10, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

void CUNCListDlg::OnTimer(UINT nIDEvent) 
	{
	if (!IsWindowVisible())
		// ... Only start the list when we are visible, 
		//     otherwise wait for the next timer event.
		return;

	// ... Kill the running timer
	KillTimer(0);

	m_wndClose.EnableWindow(FALSE);

	int nTopIndex = 0;
	m_iterUNC.Start(m_bFiles, m_bDirs, m_bRecursive, m_bDepthFirst);
	while(!m_iterUNC.IsEmpty())
		{
		m_wndList.AddString(m_iterUNC);
		m_wndList.SetTopIndex(nTopIndex++);
		m_wndList.RedrawWindow(NULL, NULL, RDW_UPDATENOW);
		m_iterUNC++;
		}
	m_iterUNC.End();

	m_wndClose.EnableWindow(TRUE);

	CDialog::OnTimer(nIDEvent);
	}
