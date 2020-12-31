#include "stdafx.h"
#include "CButtonST_Demo.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	// Make our buttons a CButtonST buttons
	DDX_Control(pDX, IDC_BTNSTLOGO, m_btnSTLogo);
	DDX_Control(pDX, IDC_BTNFACE, m_btnFace);
}

BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	//{{AFX_MSG_MAP(CDlgAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// SoftechSoftware logo button
	m_btnSTLogo.m_bShowDisabledBitmap = FALSE;
	m_btnSTLogo.SetBitmaps(IDB_STLOGO, RGB(255, 255, 255));
	// Face button
	m_btnFace.m_bShowDisabledBitmap = FALSE;
	m_btnFace.SetBitmaps(IDB_FACE, RGB(0, 255, 0));
	
	// Write class version
	CString sVersion;
	sVersion.Format(_T("CButtonST v%s"), CButtonST::GetVersionC());
	GetDlgItem(IDC_VERSION)->SetWindowText(sVersion);

	return TRUE;
} // End of OnInitDialog

void CDlgAbout::OnOK()
{
} // End of OnOK

void CDlgAbout::OnCancel()
{
} // End of OnCancel
