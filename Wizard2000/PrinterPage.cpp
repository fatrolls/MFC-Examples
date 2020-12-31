// PrinterPage.cpp : implementation file
//

#include "stdafx.h"
#include "Wiz.h"
#include "PrinterPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrinterPage dialog


CPrinterPage::CPrinterPage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CPrinterPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrinterPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrinterPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrinterPage)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrinterPage, CNewWizPage)
	//{{AFX_MSG_MAP(CPrinterPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterPage message handlers

BOOL CPrinterPage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	// for this page, we will use the base classes' large font
	m_CaptionCtrl.SetFont(&m_LargeFont, TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CPrinterPage::OnQueryCancel()
{
	if (AfxMessageBox("Are you sure you want to cancel?", MB_YESNO | MB_ICONQUESTION) == IDNO) return FALSE;
	return TRUE;
}