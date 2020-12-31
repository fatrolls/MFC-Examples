// ProgressBarDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressBarDemo.h"
#include "ProgressBarDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressBarDemoDlg dialog

CProgressBarDemoDlg::CProgressBarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressBarDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressBarDemoDlg)
	m_bShowText = TRUE;
	m_bUserText = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgressBarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressBarDemoDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressBar);
	DDX_Check(pDX, IDC_SHOW_TEXT, m_bShowText);
	DDX_Check(pDX, IDC_USER_TEXT, m_bUserText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgressBarDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressBarDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_SHOW_TEXT, OnShowText)
	ON_BN_CLICKED(IDC_USER_TEXT, OnUserText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressBarDemoDlg message handlers

BOOL CProgressBarDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    m_ProgressBar.SetShowText(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProgressBarDemoDlg::OnPaint() 
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

HCURSOR CProgressBarDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CProgressBarDemoDlg::OnTest() 
{
    m_ProgressBar.SetShowText(m_bShowText);
    m_ProgressBar.SetPos(0);
    m_ProgressBar.SetRange(0,5000);

    for (int i = 0; i < 5000; i++)
    {
        if (m_bShowText && m_bUserText)
        {
            CString str;
            str.Format("Processing completed %d%%", i/50);
            m_ProgressBar.SetWindowText(str);
        }

        m_ProgressBar.StepIt();
    }

    m_ProgressBar.SetPos(0);
    m_ProgressBar.SetShowText(FALSE);
}

void CProgressBarDemoDlg::OnShowText() 
{
    CButton* pButton = (CButton*) GetDlgItem(IDC_SHOW_TEXT);
    if (!pButton) return;

    m_bShowText = pButton->GetCheck();

    pButton = (CButton*) GetDlgItem(IDC_USER_TEXT);
    if (!pButton) return;

    pButton->EnableWindow(m_bShowText);
}

void CProgressBarDemoDlg::OnUserText() 
{
    CButton* pButton = (CButton*) GetDlgItem(IDC_USER_TEXT);
    if (!pButton) return;

    m_bUserText = pButton->GetCheck();
    m_ProgressBar.SetWindowText(NULL);

}
