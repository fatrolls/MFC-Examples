// PukamSoftDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "PukamSoftDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPukamSoftDlg dialog

CPukamSoftDlg::CPukamSoftDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPukamSoftDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPukamSoftDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bAnimating					= FALSE;
	m_pCurrentlyVisibleDialog		= NULL;
	m_pMainMenuDlg					= NULL;
	m_pCustomerInfoDlg				= NULL;
	m_pInwardTransactionsDlg		= NULL;
	m_pOutwardTransactionsDlg		= NULL;
	m_pBillingInfoDlg				= NULL;
	m_pReportsDlg					= NULL;
	m_pTopBandDlg					= NULL;
	m_pLeftNavDlg					= NULL;
	m_bExitStatus					= FALSE;
}

void CPukamSoftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPukamSoftDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPukamSoftDlg, CDialog)
	//{{AFX_MSG_MAP(CPukamSoftDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ACTIVATEAPP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPukamSoftDlg message handlers

BOOL CPukamSoftDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	this->SetWindowText("WareStock Point");

	ShowWindow(SW_SHOWMAXIMIZED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPukamSoftDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
//		CDialog::OnPaint();
		CPaintDC dc(this);
		CRect rcClient;
		GetClientRect(&rcClient);
		dc.FillSolidRect(&rcClient,RGB(200,200,200));
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPukamSoftDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPukamSoftDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(!m_bAnimating) 
	{ 
		m_bAnimating = TRUE;
		SetTimer(1, 0, NULL);  
	}

	DestroyCurrentlyVisibleDialog();
	DestroyTopBand();
	DestroyLeftNav();
}

void CPukamSoftDlg::OnTimer(UINT nIDEvent) 
{
	CRect rect;

	GetWindowRect(&rect);
	ModifyStyle(WS_CAPTION,0);
	if(rect.Height() > 20) 
	{
		SetWindowPos(NULL, rect.left, rect.top+=10, rect.Width(), rect.Height()-20, SWP_SHOWWINDOW);
	}
	else if(rect.Width() > 10)
	{
		SetWindowPos(NULL, rect.left+=20, rect.top, rect.Width()-40, rect.Height(), SWP_SHOWWINDOW);
	}
	else 
	{
		m_bAnimating = FALSE;
		KillTimer(1); 
		SendMessage(WM_CLOSE);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPukamSoftDlg::OnOK()
{
	SendMessage(WM_DESTROY);
}

BOOL CPukamSoftDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			switch(pMsg->wParam)
			{
			case MSG_DISABLETOPLEVELWINDOWS:
			{
				if(m_pCurrentlyVisibleDialog && *m_pCurrentlyVisibleDialog && (*m_pCurrentlyVisibleDialog)->IsWindowVisible() && (*m_pCurrentlyVisibleDialog)->IsWindowEnabled())
				{
					(*m_pCurrentlyVisibleDialog)->EnableWindow(FALSE);
				}
				if(m_pLeftNavDlg && m_pLeftNavDlg->IsWindowVisible() && m_pLeftNavDlg->IsWindowEnabled())
				{
					m_pLeftNavDlg->EnableWindow(FALSE);
				}
				if(m_pTopBandDlg && m_pTopBandDlg->IsWindowVisible() && m_pTopBandDlg->IsWindowEnabled())
				{
					m_pTopBandDlg->EnableWindow(FALSE);
				}
				return TRUE;
			}
			case MSG_ENABLETOPLEVELWINDOWS:
			{
				if(m_pCurrentlyVisibleDialog && *m_pCurrentlyVisibleDialog && (*m_pCurrentlyVisibleDialog)->IsWindowVisible() && (!(*m_pCurrentlyVisibleDialog)->IsWindowEnabled()))
				{
					(*m_pCurrentlyVisibleDialog)->EnableWindow(TRUE);
				}
				if(m_pLeftNavDlg && m_pLeftNavDlg->IsWindowVisible() && (!m_pLeftNavDlg->IsWindowEnabled()))
				{
					m_pLeftNavDlg->EnableWindow(TRUE);
				}
				if(m_pTopBandDlg && m_pTopBandDlg->IsWindowVisible() && (!m_pTopBandDlg->IsWindowEnabled()))
				{
					m_pTopBandDlg->EnableWindow(TRUE);
				}
				return TRUE;
			}
			case MSG_CUSTOMERINFO:
				{
					if(ShowCustomerInfoDlg())
					{
						ShowLeftNav();
						SetLeftNavState(IDC_CUSTOMERINFO_BUTTON);
						DestroyCurrentlyVisibleDialog();
						m_pCurrentlyVisibleDialog = (CDialog**)&m_pCustomerInfoDlg;
						m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());
						//ShowTopBand();
					}
					return TRUE;
				}
			case MSG_INWARDTRANSACTIONS:
				{
					if(ShowInwardTransactionsDlg())
					{
						ShowLeftNav();
						SetLeftNavState(IDC_INWARDTRANSACTIONS_BUTTON);
						DestroyCurrentlyVisibleDialog();
						m_pCurrentlyVisibleDialog = (CDialog**)&m_pInwardTransactionsDlg;
						m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());
						//ShowTopBand();
					}
					return TRUE;
				}
			case MSG_OUTWARDTRANSACTIONS:
				{
					if(ShowOutwardTransactionsDlg())
					{
						ShowLeftNav();
						SetLeftNavState(IDC_OUTWARDTRANSACTIONS_BUTTON);
						DestroyCurrentlyVisibleDialog();
						m_pCurrentlyVisibleDialog = (CDialog**)&m_pOutwardTransactionsDlg;
						m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());
						//ShowTopBand();
					}
					return TRUE;
				}
			case MSG_BILLINGINFO:
				{
					if(ShowBillingInfoDlg())
					{
						ShowLeftNav();
						SetLeftNavState(IDC_BILLINGINFO_BUTTON);
						DestroyCurrentlyVisibleDialog();
						m_pCurrentlyVisibleDialog = (CDialog**)&m_pBillingInfoDlg;
						m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());
						//ShowTopBand();
					}
					return TRUE;
				}
			case MSG_REPORTS:
				{
					if(ShowReportsDlg())
					{
						ShowLeftNav();
						SetLeftNavState(IDC_REPORTS_BUTTON);
						DestroyCurrentlyVisibleDialog();
						m_pCurrentlyVisibleDialog = (CDialog**)&m_pReportsDlg;
						m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());
						//ShowTopBand();
					}
					return TRUE;
				}
			case MSG_MAINMENU:
				{
					HideLeftNav();
					DestroyCurrentlyVisibleDialog();
				
					if(ShowMainMenuDlg())
					{
						//HideLeftNav();
						//DestroyCurrentlyVisibleDialog();
						m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());
						m_pCurrentlyVisibleDialog = (CDialog**)&m_pMainMenuDlg;
					}
					return TRUE;
				}
			case MSG_EXIT:
				m_bExitStatus = TRUE;
				OnOK();
				//PostMessage(WM_DESTROY);
				//PostQuitMessage(0);
				return TRUE;
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

BOOL CPukamSoftDlg::ShowMainMenuDlg()
{
	BOOL bRet = FALSE;
	if (!(m_pMainMenuDlg))// && m_pMainMenuDlg->IsWindowVisible()))
	{
		m_pMainMenuDlg = new CMainMenuDlg;
		m_pMainMenuDlg->Create(IDD_MAINMENU_DIALOG, this);
		bRet = TRUE;
	}
	m_pMainMenuDlg->ShowWindow(SW_SHOWMAXIMIZED);
	return bRet;
}

BOOL CPukamSoftDlg::ShowCustomerInfoDlg()
{
	BOOL bRet = FALSE;
	if (!(m_pCustomerInfoDlg))// && m_pCustomerInfoDlg->IsWindowVisible()))
	{
		m_pCustomerInfoDlg = new CCustomerInfoDlg;
		m_pCustomerInfoDlg->Create(IDD_CUSTOMERINFO_DIALOG, this);
		bRet = TRUE;
	}
	m_pCustomerInfoDlg->ShowWindow(SW_SHOWMAXIMIZED);
	return bRet;
}

BOOL CPukamSoftDlg::ShowInwardTransactionsDlg()
{
	BOOL bRet = FALSE;
	if (!(m_pInwardTransactionsDlg))// && m_pInwardTransactionsDlg->IsWindowVisible()))
	{
		m_pInwardTransactionsDlg = new CInwardTransactionsDlg;
		m_pInwardTransactionsDlg->Create(IDD_INWARDTRANSACTIONS_DIALOG, this);
		bRet = TRUE;
	}
	m_pInwardTransactionsDlg->ShowWindow(SW_SHOWMAXIMIZED);
	return bRet;
}

BOOL CPukamSoftDlg::ShowOutwardTransactionsDlg()
{
	BOOL bRet = FALSE;
	if (!(m_pOutwardTransactionsDlg))// && m_pOutwardTransactionsDlg->IsWindowVisible()))
	{
		m_pOutwardTransactionsDlg = new COutwardTransactionsDlg;
		m_pOutwardTransactionsDlg->Create(IDD_OUTWARDTRANSACTIONS_DIALOG, this);
		bRet = TRUE;
	}
	m_pOutwardTransactionsDlg->ShowWindow(SW_SHOWMAXIMIZED);
	return bRet;
}

BOOL CPukamSoftDlg::ShowBillingInfoDlg()
{
	BOOL bRet = FALSE;
	if (!(m_pBillingInfoDlg))// && m_pBillingInfoDlg->IsWindowVisible()))
	{
		m_pBillingInfoDlg = new CBillingInfoDlg;
		m_pBillingInfoDlg->Create(IDD_BILLINGINFO_DIALOG, this);
		bRet = TRUE;
	}
	m_pBillingInfoDlg->ShowWindow(SW_SHOWMAXIMIZED);
	return bRet;
}

BOOL CPukamSoftDlg::ShowReportsDlg()
{
	BOOL bRet = FALSE;
	if (!(m_pReportsDlg))// && m_pReportsDlg->IsWindowVisible()))
	{
		m_pReportsDlg = new CReportsDlg;
		m_pReportsDlg->Create(IDD_REPORTS_DIALOG, this);
		bRet = TRUE;
	}
	m_pReportsDlg->ShowWindow(SW_SHOWMAXIMIZED);
	return bRet;
}

void CPukamSoftDlg::DestroyCurrentlyVisibleDialog()
{
	if (m_pCurrentlyVisibleDialog)
	{
		if(*m_pCurrentlyVisibleDialog)
		{
			(*m_pCurrentlyVisibleDialog)->DestroyWindow();
			delete *m_pCurrentlyVisibleDialog;
			*m_pCurrentlyVisibleDialog = 0;
		}
		m_pCurrentlyVisibleDialog = 0;
	}
}

BOOL CPukamSoftDlg::ShowTopBand()
{
	BOOL bRet = FALSE;
	if (!(m_pTopBandDlg))// && m_pTopBandDlg->IsWindowVisible()))
	{
		m_pTopBandDlg = new CTopBandDlg;
		m_pTopBandDlg->Create(IDD_TOPBAND_DIALOG, this);
		m_pTopBandDlg->MoveWindow(0,0,1024,94,TRUE);
		bRet = TRUE;
	}
	m_pTopBandDlg->ShowWindow(SW_SHOW);
	m_pTopBandDlg->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	m_pTopBandDlg->ShowAppropriateSubTitle(GetSubTitleID());

	return bRet;
}

void CPukamSoftDlg::DestroyTopBand()
{
	if(m_pTopBandDlg)
	{
		m_pTopBandDlg->DestroyWindow();
		delete m_pTopBandDlg;
		m_pTopBandDlg = 0;
	}
}

UINT CPukamSoftDlg::GetSubTitleID()
{
	UINT nRet = ID_SUBTITLE_UNDEFINED;

	if(m_pCurrentlyVisibleDialog == 0)
	{
		return nRet;
	}

	if(*m_pCurrentlyVisibleDialog == m_pCustomerInfoDlg)
	{
		nRet = ID_SUBTITLE_CI;
	}
	else if(*m_pCurrentlyVisibleDialog == m_pInwardTransactionsDlg)
	{
		nRet = ID_SUBTITLE_IT;
	}
	else if(*m_pCurrentlyVisibleDialog == m_pOutwardTransactionsDlg)
	{
		nRet = ID_SUBTITLE_OT;
	}
	else if(*m_pCurrentlyVisibleDialog == m_pBillingInfoDlg)
	{
		nRet = ID_SUBTITLE_BI;
	}
	else if(*m_pCurrentlyVisibleDialog == m_pReportsDlg)
	{
		nRet = ID_SUBTITLE_RE;
	}

	return nRet;
}

BOOL CPukamSoftDlg::ShowLeftNav()
{
	BOOL bRet = FALSE;
	if (!(m_pLeftNavDlg))// && m_pLeftNavDlg->IsWindowVisible()))
	{
		m_pLeftNavDlg = new CLeftNavDlg;
		m_pLeftNavDlg->Create(IDD_LEFTNAV_DIALOG, this);
		m_pLeftNavDlg->MoveWindow(0,96,262,768,TRUE);
		bRet = TRUE;
	}
	m_pLeftNavDlg->ShowWindow(SW_NORMAL);
	m_pLeftNavDlg->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	return bRet;
}

void CPukamSoftDlg::DestroyLeftNav()
{
	if(m_pLeftNavDlg)
	{
		m_pLeftNavDlg->DestroyWindow();
		delete m_pLeftNavDlg;
		m_pLeftNavDlg = 0;
	}
}

void CPukamSoftDlg::HideLeftNav()
{
	if(m_pLeftNavDlg)
	{
		m_pLeftNavDlg->ShowWindow(SW_HIDE);
		m_pLeftNavDlg->ResetLeftNavState();
	}
}

void CPukamSoftDlg::SetLeftNavState(UINT nID)
{
	m_pLeftNavDlg->SetLeftNavState(nID);
}

void CPukamSoftDlg::OnActivateApp(BOOL bActive, HTASK hTask)
{
	if(!bActive && !m_bExitStatus)
	{
		if(FindWindow(NULL,NULL) == NULL)
		{
					
		}
		else
		{
			//ShowWindow(SW_MINIMIZE);
			ShowWindow(SW_SHOWMINNOACTIVE);
		}
	}
	else
	{
		if(FindWindow(NULL,NULL) == NULL)
		{
			ShowWindow(SW_SHOWMAXIMIZED);
		}
	}
}

int CPukamSoftDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(ShowTopBand() && ShowMainMenuDlg())
	{
		m_pCurrentlyVisibleDialog = (CDialog**)&m_pMainMenuDlg;
	}
	else
	{
		return -1;
	}
		
	return 0;
}