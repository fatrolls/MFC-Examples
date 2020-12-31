// MasterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wiz.h"
#include "MasterDlg.h"
#include "NewWizPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMasterDlg dialog


CMasterDlg::CMasterDlg(CWnd* pParent /*=NULL*/)
	: CNewWizDialog(CMasterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMasterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMasterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMasterDlg, CNewWizDialog)
	//{{AFX_MSG_MAP(CMasterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMasterDlg message handlers

BOOL CMasterDlg::OnInitDialog() 
{
	SetPlaceholderID(IDC_SHEETRECT);

	CNewWizDialog::OnInitDialog();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

