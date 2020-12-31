// PathListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PathList.h"
#include "PathComboBox.h"
#include "PathListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathListDlg dialog

CPathListDlg::CPathListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPathListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPathListDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPathListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPathListDlg)
	DDX_Control(pDX, IDC_CBEX, m_wndCBEx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPathListDlg, CDialog)
	//{{AFX_MSG_MAP(CPathListDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDOK(IDC_CBEX, OnSelEndOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathListDlg message handlers

BOOL CPathListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	//
	// Initialize the ComboBoxEx control.
	//
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory (sizeof (szPath) / sizeof (TCHAR), szPath);
	m_wndCBEx.SetPath (szPath);
	return TRUE;
}

void CPathListDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CPathListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPathListDlg::OnSelEndOK() 
{
	//
	// Display the path just selected from the ComboBoxEx control.
	//
	MessageBox (m_wndCBEx.GetPath ());
}
