
// SemiTransparentDialogWithStandardCtrlsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SemiTransparentDialogWithStandardCtrls.h"
#include "SemiTransparentDialogWithStandardCtrlsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About


// CSemiTransparentDialogWithStandardCtrlsDlg dialog


CSemiTransparentDialogWithStandardCtrlsDlg::CSemiTransparentDialogWithStandardCtrlsDlg(CWnd* pParent /*=NULL*/)
	: CImgDialogBase(CSemiTransparentDialogWithStandardCtrlsDlg::IDD
	, IDB_PNG_DLG1
	, _T("PNG")
	, AfxGetResourceHandle()
	, pParent
	)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSemiTransparentDialogWithStandardCtrlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CImgDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlListbox);
}

BEGIN_MESSAGE_MAP(CSemiTransparentDialogWithStandardCtrlsDlg, CImgDialogBase)
	//ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_DEMO2, &CSemiTransparentDialogWithStandardCtrlsDlg::OnBnClickedButtonDemo2)
	ON_BN_CLICKED(IDC_BUTTON2, &CSemiTransparentDialogWithStandardCtrlsDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSemiTransparentDialogWithStandardCtrlsDlg message handlers

BOOL CSemiTransparentDialogWithStandardCtrlsDlg::OnInitDialog()
{
	CImgDialogBase::OnInitDialog();

	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	for( int i = 0; i < 50; i++)
	{
		CString strTemp;
		strTemp.Format( _T("Item %02d"), i);
		m_ctlListbox.AddString(strTemp);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSemiTransparentDialogWithStandardCtrlsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CImgDialogBase::OnPaint();
	}
}

#include "./Demo2Dlg.h"
void CSemiTransparentDialogWithStandardCtrlsDlg::OnBnClickedButtonDemo2()
{
	CDemo2Dlg * pDlg = new CDemo2Dlg();
	pDlg->Create( CDemo2Dlg::IDD, this);
	pDlg->ShowWindow(SW_SHOW);
}

#include "./Demo3Dlg.h"
void CSemiTransparentDialogWithStandardCtrlsDlg::OnBnClickedButton2()
{
	CDemo3Dlg * pDlg = new CDemo3Dlg();
	pDlg->Create( CDemo3Dlg::IDD, this);
	pDlg->ShowWindow(SW_SHOW);
}
