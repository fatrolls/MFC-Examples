// ZipTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZipTest.h"
#include "ZipTestDlg.h"
#include "UnZipDlg.h"
#include "ZipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZipTestDlg dialog

CZipTestDlg::CZipTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZipTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZipTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZipTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZipTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZipTestDlg, CDialog)
	//{{AFX_MSG_MAP(CZipTestDlg)
	ON_BN_CLICKED(IDC_ZIP, OnZip)
	ON_BN_CLICKED(IDC_UNZIP, OnUnzip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZipTestDlg message handlers

BOOL CZipTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZipTestDlg::OnZip() 
{
	CZipDlg dlg(this);

	dlg.DoModal();
}

void CZipTestDlg::OnUnzip() 
{
	CUnzipDlg dlg(this);

	dlg.DoModal();
}
