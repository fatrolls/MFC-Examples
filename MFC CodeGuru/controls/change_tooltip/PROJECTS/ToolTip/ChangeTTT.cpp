// ChangeTTT.cpp : implementation file
//

#include "stdafx.h"


#include "ToolTip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeTTT dialog


CChangeTTT::CChangeTTT(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeTTT::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeTTT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChangeTTT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeTTT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeTTT, CDialog)
	//{{AFX_MSG_MAP(CChangeTTT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeTTT message handlers
BOOL CChangeTTT::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CToolTipView *pV = (CToolTipView *)CToolTipView::GetVP();
    CString strTTT;

    strTTT.Format("%s", pV->GetTTT() );
    
    SetDlgItemText (IDC_EDIT1, strTTT);
   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
///////////////////////////////////////////////////////////////////////////
//
void CChangeTTT::OnOK() 
{
    CToolTipView *pV = (CToolTipView *)CToolTipView::GetVP();
    
	CEdit* pEdit = (CEdit*) GetDlgItem(IDC_EDIT1);
    ASSERT(pEdit != NULL);
    
    if( pEdit != NULL)
    {
        CString str;
        pEdit->GetWindowText(str);
		pV->SetNewTTT(str);
	}

	
	CDialog::OnOK();
}
