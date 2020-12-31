// HardwarePage.cpp : implementation file
//

#include "stdafx.h"
#include "Wiz.h"
#include "HardwarePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHardwarePage dialog


CHardwarePage::CHardwarePage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CHardwarePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHardwarePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHardwarePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHardwarePage)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHardwarePage, CNewWizPage)
	//{{AFX_MSG_MAP(CHardwarePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHardwarePage message handlers

BOOL CHardwarePage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	m_Font.CreateFont(-16, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CHardwarePage::OnWizardFinish()
{
	if (IsDlgButtonChecked(CB_ALLOW_FINISH) == FALSE)
	{
		AfxMessageBox("You must check the box to allow the dialog to finish");
		return FALSE;
	}
	return TRUE;
}
