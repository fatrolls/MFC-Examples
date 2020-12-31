// SetupPage.cpp : implementation file
//

#include "stdafx.h"
#include "Wiz.h"
#include "SetupPage.h"
#include "NewWizDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupPage dialog


CSetupPage::CSetupPage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CSetupPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupPage)
	m_strLicense = _T("");
	//}}AFX_DATA_INIT
}


void CSetupPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPage)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_strLicense);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPage, CNewWizPage)
	//{{AFX_MSG_MAP(CSetupPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupPage message handlers

BOOL CSetupPage::OnInitDialog() 
{
	m_strLicense = "This product is copyright blah blah blah...";

	CNewWizPage::OnInitDialog();
	
	m_Font.CreateFont(-16, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);

	CheckRadioButton(RB_ACCEPT, RB_DECLINE, RB_DECLINE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CSetupPage::OnWizardNext()
{
	if (IsDlgButtonChecked(RB_DECLINE))
	{
		AfxMessageBox("You must accept the agreement");
		return -1;
	}
	return 0;
}

void CSetupPage::OnSetActive()
{
	m_pParent->SetTitle("This is the setup wizard");
}

BOOL CSetupPage::OnKillActive()
{
	m_pParent->SetTitle("Setup Kill Active has been called");
	return TRUE;
}
