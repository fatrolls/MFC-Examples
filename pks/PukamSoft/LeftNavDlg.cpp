// LeftNavDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "LeftNavDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftNavDlg dialog


CLeftNavDlg::CLeftNavDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLeftNavDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLeftNavDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCustomerInfoButton			= 0;
	m_pInwardTransactionsButton		= 0;
	m_pOutwardTransactionsButton	= 0;
	m_pBillingInfoButton			= 0;
	m_pReportsButton				= 0;
	m_pBGStatic						= 0;
}


void CLeftNavDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeftNavDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeftNavDlg, CDialog)
	//{{AFX_MSG_MAP(CLeftNavDlg)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftNavDlg message handlers

BOOL CLeftNavDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			int nID = HIWORD(pMsg->wParam);
			switch(LOWORD(pMsg->wParam))
			{
			case MSG_COMMAND:
				OnClickNotifyParentHandler(nID);
				break;
			default:
				break;
			}
			return TRUE;
		}
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

int CLeftNavDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,262,672);
	m_memDC.SelectObject(&m_memBmp);
	m_hBackBmp = LoadGIFEng(((CPukamSoftApp*)AfxGetApp())->GetDLLHandle(),MAKEINTRESOURCE(IDB_LN_STRIP),&m_memBmp);
	PaintMemoryDC();
	
	CreateControls();
	InitializeControls();
	
	return 0;
}

void CLeftNavDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();
}

BOOL CLeftNavDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLeftNavDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

//	dc.FillSolidRect(0,0,262,136,RGB(43,16,5));
//	dc.FillSolidRect(0,136,262,672,RGB(95,38,11));
	dc.StretchBlt(0,0,262,672,&m_memDC,0,0,4,672,SRCCOPY);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CLeftNavDlg::CreateControls()
{
	m_pCustomerInfoButton			= new CSkinnedButton;
	m_pInwardTransactionsButton		= new CSkinnedButton;
	m_pOutwardTransactionsButton	= new CSkinnedButton;
	m_pBillingInfoButton			= new CSkinnedButton;
	m_pReportsButton				= new CSkinnedButton;
	m_pBGStatic						= new CSkinnedStatic;
}

void CLeftNavDlg::DestroyControls()
{
	if(m_pCustomerInfoButton)
	{
		delete m_pCustomerInfoButton;
		m_pCustomerInfoButton = 0;
	}
	if(m_pInwardTransactionsButton)
	{
		delete m_pInwardTransactionsButton;
		m_pInwardTransactionsButton = 0;
	}
	if(m_pOutwardTransactionsButton)
	{
		delete m_pOutwardTransactionsButton;
		m_pOutwardTransactionsButton = 0;
	}
	if(m_pBillingInfoButton)
	{
		delete m_pBillingInfoButton;
		m_pBillingInfoButton = 0;
	}
	if(m_pReportsButton)
	{
		delete m_pReportsButton;
		m_pReportsButton = 0;
	}
	if(m_pBGStatic)
	{
		delete m_pBGStatic;
		m_pBGStatic = 0;
	}
}	

void CLeftNavDlg::InitializeControls()
{
	m_pCustomerInfoButton->SetImageResource(IDB_LN_CI_NORMAL, IDB_LN_CI_HOVER, IDB_LN_CI_HOVER);
	m_pCustomerInfoButton->SetShapedFlag(FALSE);

	m_pInwardTransactionsButton->SetImageResource(IDB_LN_IT_NORMAL, IDB_LN_IT_HOVER, IDB_LN_IT_HOVER);
	m_pInwardTransactionsButton->SetShapedFlag(FALSE);

	m_pOutwardTransactionsButton->SetImageResource(IDB_LN_OT_NORMAL, IDB_LN_OT_HOVER, IDB_LN_OT_HOVER);
	m_pOutwardTransactionsButton->SetShapedFlag(FALSE);

	m_pBillingInfoButton->SetImageResource(IDB_LN_BI_NORMAL, IDB_LN_BI_HOVER, IDB_LN_BI_HOVER);
	m_pBillingInfoButton->SetShapedFlag(FALSE);

	m_pReportsButton->SetImageResource(IDB_LN_RE_NORMAL, IDB_LN_RE_HOVER, IDB_LN_RE_HOVER);
	m_pReportsButton->SetShapedFlag(FALSE);
		
	m_pCustomerInfoButton->CreateSkinControl("",CRect(9,75,9+253,75+48),this,IDC_CUSTOMERINFO_BUTTON,FL_BUTTON_TYPE_TOGGLE);
	m_pInwardTransactionsButton->CreateSkinControl("",CRect(9,75+48+9,9+253,75+48+9+48),this,IDC_INWARDTRANSACTIONS_BUTTON,FL_BUTTON_TYPE_TOGGLE);
	m_pOutwardTransactionsButton->CreateSkinControl("",CRect(9,75+48+9+48+9,9+253,75+48+9+48+9+48),this,IDC_OUTWARDTRANSACTIONS_BUTTON,FL_BUTTON_TYPE_TOGGLE);
	m_pBillingInfoButton->CreateSkinControl("",CRect(9,75+48+9+48+9+48+9,9+253,75+48+9+48+9+48+9+48),this,IDC_BILLINGINFO_BUTTON,FL_BUTTON_TYPE_TOGGLE);
	m_pReportsButton->CreateSkinControl("",CRect(9,75+48+9+48+9+48+9+48+9,9+253,75+48+9+48+9+48+9+48+9+48),this,IDC_REPORTS_BUTTON,FL_BUTTON_TYPE_TOGGLE);
	m_pBGStatic->CreateSkinControl("",CRect(0,672-322,262,672),this,IDC_SKINNEDSTATIC);
}

void CLeftNavDlg::PaintMemoryDC()
{
	BITMAP bmpTemp;

	memset(&bmpTemp, 0, sizeof(BITMAP));

	if(m_memDC == NULL)
	{
		return;
	}

	if(m_hBackBmp != NULL)
	{
		::GetObject(m_hBackBmp, sizeof(BITMAP), &bmpTemp);

		::SelectObject(m_memDC.GetSafeHdc(),m_hBackBmp);
	}
}

void CLeftNavDlg::OnClickNotifyParentHandler(int nID)
{
	int nMsg = -1;
	switch(nID)
	{
	case IDC_CUSTOMERINFO_BUTTON:
		nMsg = MSG_CUSTOMERINFO;
		m_pInwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pOutwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pBillingInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pReportsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		break;
	case IDC_INWARDTRANSACTIONS_BUTTON:
		nMsg = MSG_INWARDTRANSACTIONS;
		m_pCustomerInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pOutwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pBillingInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pReportsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		break;
	case IDC_OUTWARDTRANSACTIONS_BUTTON:
		nMsg = MSG_OUTWARDTRANSACTIONS;
		m_pCustomerInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pInwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pBillingInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pReportsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		break;
	case IDC_BILLINGINFO_BUTTON:
		nMsg = MSG_BILLINGINFO;
		m_pCustomerInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pInwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pOutwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pReportsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		break;
	case IDC_REPORTS_BUTTON:
		nMsg = MSG_REPORTS;
		m_pCustomerInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pInwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pOutwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		m_pBillingInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
		break;
	default:
		break;
	}
	::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, nMsg, 0L);
//	SetLeftNavState(nID);
}

void CLeftNavDlg::SetLeftNavState(UINT nID)
{
	switch(nID)
	{
	case IDC_CUSTOMERINFO_BUTTON:
		m_pBGStatic->SetImageResource(IDB_LN_CI_BG);
		m_pBGStatic->Redraw();
		m_pCustomerInfoButton->SetToggleButtonState(BUTTON_STATE_PRESSED);
		break;
	case IDC_INWARDTRANSACTIONS_BUTTON:
		m_pBGStatic->SetImageResource(IDB_LN_IT_BG);
		m_pBGStatic->Redraw();
		m_pInwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_PRESSED);
		break;
	case IDC_OUTWARDTRANSACTIONS_BUTTON:
		m_pBGStatic->SetImageResource(IDB_LN_OT_BG);
		m_pBGStatic->Redraw();
		m_pOutwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_PRESSED);
		break;
	case IDC_BILLINGINFO_BUTTON:
		m_pBGStatic->SetImageResource(IDB_LN_BI_BG);
		m_pBGStatic->Redraw();
		m_pBillingInfoButton->SetToggleButtonState(BUTTON_STATE_PRESSED);
		break;
	case IDC_REPORTS_BUTTON:
		m_pBGStatic->SetImageResource(IDB_LN_RE_BG);
		m_pBGStatic->Redraw();
		m_pReportsButton->SetToggleButtonState(BUTTON_STATE_PRESSED);
		break;
	default:
		break;
	}	
}

void CLeftNavDlg::ResetLeftNavState()
{
	m_pCustomerInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
	m_pInwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
	m_pOutwardTransactionsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
	m_pBillingInfoButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
	m_pReportsButton->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
}

void CLeftNavDlg::OnOK()
{

}

void CLeftNavDlg::OnCancel()
{

}
