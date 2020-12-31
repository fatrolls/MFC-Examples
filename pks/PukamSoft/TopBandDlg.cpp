// TopBandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "TopBandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTopBandDlg dialog


CTopBandDlg::CTopBandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTopBandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTopBandDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pTitleMainStatic				= 0;
	m_pTitleCIStatic				= 0;
	m_pTitleITStatic				= 0;
	m_pTitleOTStatic				= 0;
	m_pTitleBIStatic				= 0;
	m_pTitleREStatic				= 0;
	m_pPipeStatic					= 0;
	m_pCloseButton					= 0;
	m_pHomeButton					= NULL;
}


void CTopBandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTopBandDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTopBandDlg, CDialog)
	//{{AFX_MSG_MAP(CTopBandDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTopBandDlg message handlers

int CTopBandDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,1024,94);
	m_memDC.SelectObject(&m_memBmp);
	m_hBackBmp = LoadGIFEng(((CPukamSoftApp*)AfxGetApp())->GetDLLHandle(),MAKEINTRESOURCE(IDB_TB_STRIP),&m_memBmp);
	PaintMemoryDC();
	CreateControls();
	InitializeControls();
	return 0;
}

BOOL CTopBandDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ModifyStyleEx( WS_EX_APPWINDOW, 0 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTopBandDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.StretchBlt(0,0,1024,94,&m_memDC,0,0,2,94,SRCCOPY);
	// Do not call CDialog::OnPaint() for painting messages
}

void CTopBandDlg::PaintMemoryDC()
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

void CTopBandDlg::CreateControls()
{
	m_pTitleMainStatic				= new CSkinnedStatic;
	m_pTitleCIStatic				= new CSkinnedStatic;
	m_pTitleITStatic				= new CSkinnedStatic;
	m_pTitleOTStatic				= new CSkinnedStatic;
	m_pTitleBIStatic				= new CSkinnedStatic;
	m_pTitleREStatic				= new CSkinnedStatic;
	m_pPipeStatic					= new CSkinnedStatic;
	m_pCloseButton					= new CSkinnedButton;
	m_pHomeButton					= new CSkinnedButton;
}

void CTopBandDlg::DestroyControls()
{
	if(m_pTitleMainStatic)
	{
		delete m_pTitleMainStatic;
		m_pTitleMainStatic = 0;
	}
	if(m_pTitleCIStatic)
	{
		delete m_pTitleCIStatic;
		m_pTitleCIStatic = 0;
	}
	if(m_pTitleITStatic)
	{
		delete m_pTitleITStatic;
		m_pTitleITStatic = 0;
	}
	if(m_pTitleOTStatic)
	{
		delete m_pTitleOTStatic;
		m_pTitleOTStatic = 0;
	}
	if(m_pTitleBIStatic)
	{
		delete m_pTitleBIStatic;
		m_pTitleBIStatic = 0;
	}
	if(m_pTitleREStatic)
	{
		delete m_pTitleREStatic;
		m_pTitleREStatic = 0;
	}
	if(m_pPipeStatic)
	{
		delete m_pPipeStatic;
		m_pPipeStatic = 0;
	}
	if(m_pCloseButton)
	{
		delete m_pCloseButton;
		m_pCloseButton = 0;
	}
	if(m_pHomeButton != NULL)
	{
		delete m_pHomeButton;
		m_pHomeButton = NULL;
	}
}

void CTopBandDlg::InitializeControls()
{
	m_pTitleMainStatic->SetImageResource(IDB_TB_TITLEMAIN);
	m_pPipeStatic->SetImageResource(IDB_TB_PIPE);
	m_pTitleCIStatic->SetImageResource(IDB_TB_SUBTITLECI);
	m_pTitleITStatic->SetImageResource(IDB_TB_SUBTITLEIT);
	m_pTitleOTStatic->SetImageResource(IDB_TB_SUBTITLEOT);
	m_pTitleBIStatic->SetImageResource(IDB_TB_SUBTITLEBI);
	m_pTitleREStatic->SetImageResource(IDB_TB_SUBTITLERE);
	m_pCloseButton->SetImageResource(IDB_TB_CLOSE,IDB_TB_CLOSE,IDB_TB_CLOSE);
	m_pHomeButton->SetImageResource(IDB_TB_HOME,IDB_TB_HOME,IDB_TB_HOME);

	m_pTitleMainStatic->CreateSkinControl("",CRect(15,26,15+398,26+39),this,IDC_SKINNEDSTATIC);
	m_pPipeStatic->CreateSkinControl("",CRect(1024-36,24,1024-33,24+30),this,IDC_SKINNEDSTATIC);
	m_pTitleCIStatic->CreateSkinControl("",CRect(1024-176,29,1024-176+127,29+18),this,IDC_SKINNEDSTATIC);
	m_pTitleITStatic->CreateSkinControl("",CRect(1024-311,29,1024-311+259,29+18),this,IDC_SKINNEDSTATIC);
	m_pTitleOTStatic->CreateSkinControl("",CRect(1024-339,29,1024-339+287,29+18),this,IDC_SKINNEDSTATIC);
	m_pTitleBIStatic->CreateSkinControl("",CRect(1024-135,29,1024-135+83,29+18),this,IDC_SKINNEDSTATIC);
	m_pTitleREStatic->CreateSkinControl("",CRect(1024-139,29,1024-139+88,29+18),this,IDC_SKINNEDSTATIC);
	m_pCloseButton->CreateSkinControl("",CRect(1024-105,72,1024-105+68,72+22),this,IDC_CLOSE_BUTTON);
	m_pHomeButton->CreateSkinControl("",CRect(1024-145,74,1024-145+18,74+17),this,IDC_HOME_BUTTON);
}

void CTopBandDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();	
}

void CTopBandDlg::ShowAppropriateSubTitle(UINT nSubTitleID)
{
	switch(nSubTitleID)
	{
	case ID_SUBTITLE_CI:
		m_pPipeStatic->ShowWindow(SW_NORMAL);
		m_pTitleCIStatic->ShowWindow(SW_NORMAL);
		m_pTitleITStatic->ShowWindow(SW_HIDE);
		m_pTitleOTStatic->ShowWindow(SW_HIDE);
		m_pTitleBIStatic->ShowWindow(SW_HIDE);
		m_pTitleREStatic->ShowWindow(SW_HIDE);
		break;
	case ID_SUBTITLE_IT:
		m_pPipeStatic->ShowWindow(SW_NORMAL);
		m_pTitleITStatic->ShowWindow(SW_NORMAL);
		m_pTitleCIStatic->ShowWindow(SW_HIDE);
		m_pTitleOTStatic->ShowWindow(SW_HIDE);
		m_pTitleBIStatic->ShowWindow(SW_HIDE);
		m_pTitleREStatic->ShowWindow(SW_HIDE);
		break;
	case ID_SUBTITLE_OT:
		m_pPipeStatic->ShowWindow(SW_NORMAL);
		m_pTitleOTStatic->ShowWindow(SW_NORMAL);
		m_pTitleCIStatic->ShowWindow(SW_HIDE);
		m_pTitleITStatic->ShowWindow(SW_HIDE);
		m_pTitleBIStatic->ShowWindow(SW_HIDE);
		m_pTitleREStatic->ShowWindow(SW_HIDE);
		break;
	case ID_SUBTITLE_BI:
		m_pPipeStatic->ShowWindow(SW_NORMAL);
		m_pTitleBIStatic->ShowWindow(SW_NORMAL);
		m_pTitleCIStatic->ShowWindow(SW_HIDE);
		m_pTitleITStatic->ShowWindow(SW_HIDE);
		m_pTitleOTStatic->ShowWindow(SW_HIDE);
		m_pTitleREStatic->ShowWindow(SW_HIDE);
		break;
	case ID_SUBTITLE_RE:
		m_pPipeStatic->ShowWindow(SW_NORMAL);
		m_pTitleREStatic->ShowWindow(SW_NORMAL);
		m_pTitleCIStatic->ShowWindow(SW_HIDE);
		m_pTitleITStatic->ShowWindow(SW_HIDE);
		m_pTitleOTStatic->ShowWindow(SW_HIDE);
		m_pTitleBIStatic->ShowWindow(SW_HIDE);
		break;
	case ID_SUBTITLE_UNDEFINED:
	default:
		m_pTitleCIStatic->ShowWindow(SW_HIDE);
		m_pTitleITStatic->ShowWindow(SW_HIDE);
		m_pTitleOTStatic->ShowWindow(SW_HIDE);
		m_pTitleBIStatic->ShowWindow(SW_HIDE);
		m_pTitleREStatic->ShowWindow(SW_HIDE);
		m_pPipeStatic->ShowWindow(SW_HIDE);
		break;
	}
}

BOOL CTopBandDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			int nID = HIWORD(pMsg->wParam);
			switch(LOWORD(pMsg->wParam))
			{
			case MSG_COMMAND:
				{
					switch(nID)
					{
					case IDC_CLOSE_BUTTON:
						::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MSG_EXIT, 0L);
						break;
					case IDC_HOME_BUTTON:
						::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MSG_MAINMENU, 0L);
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

void CTopBandDlg::OnOK()
{

}

void CTopBandDlg::OnCancel()
{

}
