// MainMenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "MainMenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainMenuDlg dialog


CMainMenuDlg::CMainMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainMenuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainMenuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pBackgroundStatic				= 0;
	m_pCustomerInfoButton			= 0;
	m_pInwardTransactionsButton		= 0;
	m_pOutwardTransactionsButton	= 0;
	m_pBillingInfoButton			= 0;
	m_pReportsButton				= 0;
}


void CMainMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainMenuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainMenuDlg, CDialog)
	//{{AFX_MSG_MAP(CMainMenuDlg)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainMenuDlg message handlers

int CMainMenuDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,1024,674);
	m_memDC.SelectObject(&m_memBmp);
	m_hBackBmp = LoadGIFEng(((CPukamSoftApp*)AfxGetApp())->GetDLLHandle(),MAKEINTRESOURCE(IDB_MM_STRIP),&m_memBmp);
	PaintMemoryDC();
	CreateControls();
	InitializeControls();

	return 0;
}

BOOL CMainMenuDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainMenuDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();
}

void CMainMenuDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);
	//dc.FillSolidRect(&rcClient,RGB(255,255,255));
	dc.StretchBlt(0,94,1024,674,&m_memDC,0,0,5,674,SRCCOPY);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CMainMenuDlg::OnOK()
{
	int nRetCode = MessageBoxEng(this,MB_MSG_EXITAPPLICATION_CONFIRMATION,MB_YESNO_BUTTON,"Exit Application Confirmation?","");
	if(nRetCode == ID_MB_YES_BUTTON)
	{
		::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MSG_EXIT, 0L);
	}
}

void CMainMenuDlg::DestroyControls()
{
	if(m_pBackgroundStatic)
	{
		delete m_pBackgroundStatic;
		m_pBackgroundStatic = 0;
	}
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
}

void CMainMenuDlg::CreateControls()
{
	m_pBackgroundStatic				= new CSkinnedStatic;
	m_pCustomerInfoButton			= new CSkinnedButton;
	m_pInwardTransactionsButton		= new CSkinnedButton;
	m_pOutwardTransactionsButton	= new CSkinnedButton;
	m_pBillingInfoButton			= new CSkinnedButton;
	m_pReportsButton				= new CSkinnedButton;
}

void CMainMenuDlg::InitializeControls()
{
	m_pBackgroundStatic->SetImageResource(IDB_MM_BACKGROUND);

	m_pCustomerInfoButton->SetImageResource(IDB_MM_CI_NORMAL, IDB_MM_CI_HOVER, IDB_MM_CI_NORMAL);
	m_pCustomerInfoButton->SetShapedFlag(FALSE);

	m_pInwardTransactionsButton->SetImageResource(IDB_MM_IT_NORMAL, IDB_MM_IT_HOVER, IDB_MM_IT_NORMAL);
	m_pInwardTransactionsButton->SetShapedFlag(FALSE);

	m_pOutwardTransactionsButton->SetImageResource(IDB_MM_OT_NORMAL, IDB_MM_OT_HOVER, IDB_MM_OT_NORMAL);
	m_pOutwardTransactionsButton->SetShapedFlag(FALSE);

	m_pBillingInfoButton->SetImageResource(IDB_MM_BI_NORMAL, IDB_MM_BI_HOVER, IDB_MM_BI_NORMAL);
	m_pBillingInfoButton->SetShapedFlag(FALSE);

	m_pReportsButton->SetImageResource(IDB_MM_RE_NORMAL, IDB_MM_RE_HOVER, IDB_MM_RE_NORMAL);
	m_pReportsButton->SetShapedFlag(FALSE);

	m_pBackgroundStatic->CreateSkinControl("",CRect(0,96,868,768),this,IDC_SKINNEDSTATIC);
	m_pCustomerInfoButton->CreateSkinControl("",CRect(1024-361,257,1024,257+62),this,IDC_CUSTOMERINFO_BUTTON);
	m_pInwardTransactionsButton->CreateSkinControl("",CRect(1024-361,257+62+12,1024,257+62+12+62),this,IDC_INWARDTRANSACTIONS_BUTTON);
	m_pOutwardTransactionsButton->CreateSkinControl("",CRect(1024-361,257+62+12+62+12,1024,257+62+12+62+12+62),this,IDC_OUTWARDTRANSACTIONS_BUTTON);
	m_pBillingInfoButton->CreateSkinControl("",CRect(1024-361,257+62+12+62+12+62+12,1024,257+62+12+62+12+62+12+62),this,IDC_BILLINGINFO_BUTTON);
	m_pReportsButton->CreateSkinControl("",CRect(1024-361,257+62+12+62+12+62+12+62+12,1024,257+62+12+62+12+62+12+62+12+62),this,IDC_REPORTS_BUTTON);
}

BOOL CMainMenuDlg::PreTranslateMessage(MSG* pMsg) 
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

void CMainMenuDlg::OnClickNotifyParentHandler(int nID)
{
	int nMsg = -1;
	switch(nID)
	{
	case IDC_CUSTOMERINFO_BUTTON:
		nMsg = MSG_CUSTOMERINFO;
		break;
	case IDC_INWARDTRANSACTIONS_BUTTON:
		nMsg = MSG_INWARDTRANSACTIONS;
		break;
	case IDC_OUTWARDTRANSACTIONS_BUTTON:
		nMsg = MSG_OUTWARDTRANSACTIONS;
		break;
	case IDC_BILLINGINFO_BUTTON:
		nMsg = MSG_BILLINGINFO;
		break;
	case IDC_REPORTS_BUTTON:
		nMsg = MSG_REPORTS;
		break;
	default:
		break;
	}
	::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, nMsg, 0L);
}

void CMainMenuDlg::PaintMemoryDC()
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