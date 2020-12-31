// ReportsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "ReportsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportsDlg dialog


CReportsDlg::CReportsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pTableContainerWnd			= 0;
	m_pViewITButton					= 0;
	m_pViewOTButton					= 0;
	m_pViewCIButton					= 0;
	m_nCurrentTableID				= ID_CI_TABLE;
	m_pDeleteButton					= NULL;
}


void CReportsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportsDlg, CDialog)
	//{{AFX_MSG_MAP(CReportsDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportsDlg message handlers

int CReportsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,262,672);
	m_memDC.SelectObject(&m_memBmp);
	m_hBackBmp = LoadGIFEng(((CPukamSoftApp*)AfxGetApp())->GetDLLHandle(),MAKEINTRESOURCE(IDB_LN_STRIP),&m_memBmp);
	PaintMemoryDC();
	CreateFontPageTitle();
	CreateTableContainer();
	CreateControls();
	InitializeControls();

	return 0;
}

BOOL CReportsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );
	DisplayPageTitle();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportsDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);
	dc.FillSolidRect(&rcClient,BLACK);
	dc.StretchBlt(266,96,1024,768,&m_memDC,0,0,4,672,SRCCOPY);
	dc.FillSolidRect(CRect(320-3,175-3,950+3,710+3),RGB(32,26,12));
	dc.FillSolidRect(CRect(320,175,950,710),BLACK);
	CFont* pFont = dc.SelectObject(&m_fontPageTitle);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,18,0));
	dc.TextOut(310,105,m_csPageTitle);
	dc.SelectObject(pFont);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CReportsDlg::CreateTableContainer()
{
	TCHAR szTableTitle[32];
	m_pTableContainerWnd = new CTableContainer;
	m_pTableContainerWnd->Create(NULL,"Table Container",WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CRect(320,177,950,630),this,IDC_TABLECONTAINER,NULL);

	sprintf(szTableTitle,"%s","Customer List");
	m_pTableContainerWnd->CreateTableEng(ID_CI_TABLE);
	m_pTableContainerWnd->SetTableTitle(ID_CI_TABLE,szTableTitle);
	m_pTableContainerWnd->SetTableTitleColor(ID_CI_TABLE,RGB(0,146,159));
	m_pTableContainerWnd->SetColumnTitleLineColor(ID_CI_TABLE,RGB(6,112,121));
	m_pTableContainerWnd->SetRowLineColor(ID_CI_TABLE,RGB(44,173,184));
	m_pTableContainerWnd->PopulateTable(ID_CI_TABLE);

	m_pTableContainerWnd->DrawTable();
	m_pTableContainerWnd->ShowWindow(SW_NORMAL);
}

void CReportsDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_pTableContainerWnd	)
	{
		delete m_pTableContainerWnd;
		m_pTableContainerWnd = 0;
	}

	DestroyControls();
	m_fontPageTitle.DeleteObject();
}

void CReportsDlg::PaintMemoryDC()
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

void CReportsDlg::SetPageTitle(LPCTSTR lpszPageTitle)
{
	m_csPageTitle = lpszPageTitle;
}

void CReportsDlg::CreateFontPageTitle()
{
	LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	strcpy(lf.lfFaceName,"Century Gothic");
	lf.lfHeight = 40;
	lf.lfWeight = FW_BOLD;
	lf.lfQuality = ANTIALIASED_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_MODERN;
	m_fontPageTitle.CreateFontIndirect(&lf);
}

void CReportsDlg::DisplayPageTitle()
{
	TCHAR szTitle[128];
	switch(m_nCurrentTableID)
	{
	case ID_CI_TABLE:
		SetPageTitle("Report | Customer List");
		break;
	case ID_IT_TABLE:
		wsprintf(szTitle,"%s | Inward Transactions",m_pTableContainerWnd->GetPageTitle());
		SetPageTitle(szTitle);
		break;
	case ID_OT_TABLE:
		wsprintf(szTitle,"%s | Outward Transactions",m_pTableContainerWnd->GetPageTitle());
		SetPageTitle(szTitle);
		break;
	}

	InvalidateRect(CRect(200,90,1024,180),TRUE);
}

void CReportsDlg::CreateControls()
{
	m_pViewITButton			= new CSkinnedButton;
	m_pViewOTButton			= new CSkinnedButton;
	m_pViewCIButton			= new CSkinnedButton;
	m_pDeleteButton			= new CSkinnedButton;
}

void CReportsDlg::DestroyControls()
{
	if(m_pViewITButton)
	{
		delete m_pViewITButton;
		m_pViewITButton = 0;
	}
	if(m_pViewOTButton)
	{
		delete m_pViewOTButton;
		m_pViewOTButton = 0;
	}
	if(m_pViewCIButton)
	{
		delete m_pViewCIButton;
		m_pViewCIButton = 0;
	}
	if(m_pDeleteButton != NULL)
	{
		delete m_pDeleteButton;
		m_pDeleteButton = NULL;
	}
}

void CReportsDlg::InitializeControls()
{
	m_pViewITButton->SetImageResource(IDB_RE_IT_NORMAL,IDB_RE_IT_HOVER,IDB_RE_IT_HOVER);
	m_pViewITButton->CreateSkinControl("",CRect(766,651,766+168,651+42),this,IDC_VIEWIT_BUTTON);
	m_pViewOTButton->SetImageResource(IDB_RE_OT_NORMAL,IDB_RE_OT_HOVER,IDB_RE_OT_HOVER);
	m_pViewOTButton->CreateSkinControl("",CRect(749,651,749+185,651+42),this,IDC_VIEWOT_BUTTON);
	m_pViewCIButton->SetImageResource(IDB_RE_CI_NORMAL,IDB_RE_CI_HOVER,IDB_RE_CI_HOVER);
	m_pViewCIButton->CreateSkinControl("",CRect(749,651,749+185,651+42),this,IDC_VIEWCI_BUTTON);
	m_pDeleteButton->SetImageResource(IDB_DELETE_NORMAL,IDB_DELETE_HIT,IDB_DELETE_HIT);
	m_pDeleteButton->CreateSkinControl("",CRect(766,600,766+168,600+42),this,IDC_DELETE_BUTTON);
	m_pViewCIButton->ShowWindow(SW_HIDE);
	m_pViewCIButton->EnableWindow(FALSE);
	m_pViewOTButton->ShowWindow(SW_HIDE);
	m_pViewOTButton->EnableWindow(FALSE);
}

BOOL CReportsDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			switch(LOWORD(pMsg->wParam))
			{
			case MSG_COMMAND:
				{
					switch(HIWORD(pMsg->wParam))
					{
					case IDC_VIEWIT_BUTTON:
						if(m_pTableContainerWnd->DisplayDetailsTable(ID_IT_TABLE))
						{
							m_nCurrentTableID = ID_IT_TABLE;
							DisplayPageTitle();
							m_pTableContainerWnd->UpdateWindow();
							DisplayAppropriateButtons();
						}
						break;
					case IDC_VIEWOT_BUTTON:
						if(m_pTableContainerWnd->DisplayDetailsTable(ID_OT_TABLE))
						{
							m_nCurrentTableID = ID_OT_TABLE;
							DisplayPageTitle();
							DisplayAppropriateButtons();
						}
						break;
					case IDC_VIEWCI_BUTTON:
						m_pTableContainerWnd->DisplayMainTable();
						m_nCurrentTableID = ID_CI_TABLE;
						DisplayPageTitle();
						DisplayAppropriateButtons();
						break;
					case IDC_DELETE_BUTTON:
						m_pTableContainerWnd->DeleteEntry(m_nCurrentTableID);
						break;
					}
					break;
				}
	
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

void CReportsDlg::DisplayAppropriateButtons()
{
	switch(m_nCurrentTableID)
	{
	case ID_CI_TABLE:
		m_pViewCIButton->ShowWindow(SW_HIDE);
		m_pViewCIButton->EnableWindow(FALSE);
		m_pViewITButton->MoveWindow(766,651,168,42,TRUE);
		m_pViewITButton->ShowWindow(SW_NORMAL);
		m_pViewITButton->EnableWindow();
		m_pViewOTButton->ShowWindow(SW_HIDE);
		m_pViewOTButton->EnableWindow(FALSE);
		break;
	case ID_IT_TABLE:
		m_pViewCIButton->MoveWindow(544,651,185,42,TRUE);
		m_pViewCIButton->ShowWindow(SW_NORMAL);
		m_pViewCIButton->EnableWindow();
		m_pViewITButton->ShowWindow(SW_HIDE);
		m_pViewITButton->EnableWindow(FALSE);
		m_pViewOTButton->MoveWindow(749,651,185,42,TRUE);
		m_pViewOTButton->ShowWindow(SW_NORMAL);
		m_pViewOTButton->EnableWindow();
		break;
	case ID_OT_TABLE:
		m_pViewCIButton->MoveWindow(749,651,185,42,TRUE);
		m_pViewITButton->ShowWindow(SW_HIDE);
		m_pViewITButton->EnableWindow(FALSE);
		m_pViewOTButton->ShowWindow(SW_HIDE);
		m_pViewOTButton->EnableWindow(FALSE);
		m_pViewCIButton->ShowWindow(SW_NORMAL);
		m_pViewCIButton->EnableWindow();
		break;
	}
}