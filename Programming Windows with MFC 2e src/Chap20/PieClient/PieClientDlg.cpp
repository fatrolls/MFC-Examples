// PieClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PieClient.h"
#include "PieClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPieClientDlg dialog

CPieClientDlg::CPieClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPieClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPieClientDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPieClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPieClientDlg)
	DDX_Control(pDX, IDC_SET, m_wndSet);
	DDX_Control(pDX, IDC_GET, m_wndGet);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPieClientDlg, CDialog)
	//{{AFX_MSG_MAP(CPieClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET, OnGet)
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPieClientDlg message handlers

BOOL CPieClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//
	// Start the Automation server.
	//
	BOOL bSuccess = m_autoPie.CreateDispatch (_T ("AutoPie.Application"));

	//
	// If CreateDispatch succeeded, initialize the m_autoChart and
	// m_autoWindow data members to represent the Chart and Window
	// subobjects, respectively. Then initialize the controls in
	// the dialog and make the server window visible.
	//
	if (bSuccess) {
		m_autoChart.AttachDispatch (m_autoPie.GetChart ());
		ASSERT (m_autoChart.m_lpDispatch != NULL);
		m_autoWindow.AttachDispatch (m_autoPie.GetWindow ());
		ASSERT (m_autoWindow.m_lpDispatch != NULL);
		OnGet ();
		m_autoWindow.SetVisible (TRUE);
	}

	//
	// If CreateDispatch failed, let the user know about it.
	//
	else {
		MessageBox (_T ("Error launching AutoPie. Run it once to " \
		"register it on this system and then try again."), _T ("Error"));
		m_wndGet.EnableWindow (FALSE);
		m_wndSet.EnableWindow (FALSE);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPieClientDlg::OnPaint() 
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

HCURSOR CPieClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPieClientDlg::OnGet() 
{
	//
	// Retrieve revenue values from the Automation server and display them.
	//
	SetDlgItemInt (IDC_Q1, m_autoChart.GetRevenue (1));
	SetDlgItemInt (IDC_Q2, m_autoChart.GetRevenue (2));
	SetDlgItemInt (IDC_Q3, m_autoChart.GetRevenue (3));
	SetDlgItemInt (IDC_Q4, m_autoChart.GetRevenue (4));
}

void CPieClientDlg::OnSet() 
{
	//
	// Retrieve the revenue values displayed in the edit controls and provide
	// them to the Automation server.
	//
	m_autoChart.SetRevenue (1, GetDlgItemInt (IDC_Q1));
	m_autoChart.SetRevenue (2, GetDlgItemInt (IDC_Q2));
	m_autoChart.SetRevenue (3, GetDlgItemInt (IDC_Q3));
	m_autoChart.SetRevenue (4, GetDlgItemInt (IDC_Q4));

	//
	// Repaint the pie chart.
	//
	m_autoWindow.Refresh ();	
}
