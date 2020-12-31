// MessageBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "MessageBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int g_nArrIcon[MAX_MSG] = {	MB_ICON_CONFIRMATION,
							MB_ICON_CONFIRMATION,
							MB_ICON_INFORMATION,
							MB_ICON_ERROR,
							MB_ICON_ERROR,
							MB_ICON_CONFIRMATION,
							MB_ICON_INFORMATION,
							MB_ICON_ERROR,
							MB_ICON_WARNING,
							MB_ICON_ERROR,
							MB_ICON_WARNING,
							MB_ICON_CONFIRMATION,
							MB_ICON_INFORMATION
						};

CString g_csArrMessageText[MAX_MSG] = 
						{	"Are you sure you want to exit WareStock Point?",
							"Are you sure you want to delete ^?",
							"^ deleted!",
							"Invalid ^ name! Please enter a valid name.",
							"^! Please enter a valid date.",
							"Do you want to save the transaction?",
							"Transaction saved!",
							"Dates in the past are not allowed for this operation.\n Please re-enter the dates.",
							"WareStock Point runs best on screen resolution 1024 X 768!\n Do you wish to continue with your current resolution?",
							"^",
							"^",
							"^",
							"^"
						};

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxDlg dialog


CMessageBoxDlg::CMessageBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pTopBandStatic = 0;
	m_pLeftIconStatic = 0;
	m_pMessageTextStatic = 0;
	m_pButton1 = 0;
	m_pButton2 = 0;

	m_nMessageID = -1;
	m_nButtonType = -1;

}


void CMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageBoxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CMessageBoxDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxDlg message handlers

void CMessageBoxDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	DestroyControls();
	// TODO: Add your message handler code here
	
}

BOOL CMessageBoxDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nResX = ::GetSystemMetrics(SM_CXSCREEN);
	int nResY = ::GetSystemMetrics(SM_CYSCREEN);
	GetClientRect(&m_rcClient);
	
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	int nNewLeft = (nResX-(rcWindow.Width()))/2;
	int nNewTop = (nResY-(rcWindow.Height()))/2;
	MoveWindow(nNewLeft,nNewTop,m_rcClient.Width(),m_rcClient.Height());
	
	CreateControls();
	InitializeScreen();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMessageBoxDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.FillSolidRect(&m_rcClient,RGB(234,233,233));

	CRect rcRect1(m_rcClient.left,m_rcClient.top,m_rcClient.Width(),m_rcClient.top+2);
	dc.FillSolidRect(&rcRect1,RGB(150,150,150));
	
	CRect rcRect2(m_rcClient.left,m_rcClient.top,m_rcClient.left+2,m_rcClient.Height());
	dc.FillSolidRect(&rcRect2,RGB(150,150,150));

	CRect rcRect3(m_rcClient.right-2,m_rcClient.top,m_rcClient.right,m_rcClient.Height());
	dc.FillSolidRect(&rcRect3,RGB(0,0,0));

	CRect rcRect4(m_rcClient.left,m_rcClient.Height()-5,m_rcClient.right,m_rcClient.Height());
	dc.FillSolidRect(&rcRect4,RGB(0,0,0));

	// Do not call CDialog::OnPaint() for painting messages
}

void CMessageBoxDlg::CreateControls()
{
	m_pTopBandStatic = new CSkinnedStatic;
	m_pLeftIconStatic = new CSkinnedStatic;
	m_pMessageTextStatic = new CSkinnedStatic;
}

void CMessageBoxDlg::InitializeScreen()
{
	m_pTopBandStatic->SetImageResource(IDB_MB_TOP_BAND);
	m_pTopBandStatic->CreateSkinControl(m_csTopBandText,CRect(2,2,(m_rcClient.Width()-2),2+38),this,ID_MB_TOP_BAND_STATIC,DRAW_STYLE_TILED);
	m_pTopBandStatic->SetTextAlignment(TEXT_ALIGN_NONE);
	m_pTopBandStatic->SetFontSize(18);
	m_pTopBandStatic->SetFontName("Arial");
	m_pTopBandStatic->SetFontStyle(FONT_BOLD);
	m_pTopBandStatic->SetForegroundColor(RGB(255,252,0));
	m_pTopBandStatic->SetPadding(3,5);

	switch(g_nArrIcon[m_nMessageID])
	{
	case MB_ICON_CONFIRMATION:
		m_pLeftIconStatic->SetImageResource(IDB_MB_CONFIRMATION_ICON);
		break;
	case MB_ICON_ERROR:
		m_pLeftIconStatic->SetImageResource(IDB_MB_ERROR_ICON);
		break;
	case MB_ICON_INFORMATION:
		m_pLeftIconStatic->SetImageResource(IDB_MB_INFORMATION_ICON);
		break;
	case MB_ICON_WARNING:
		m_pLeftIconStatic->SetImageResource(IDB_MB_WARNING_ICON);
		break;
	default:
		break;
	}
	m_pLeftIconStatic->CreateSkinControl("",CRect(15,67,15+32,67+32),this,ID_MB_LEFT_ICON_STATIC);

	m_pMessageTextStatic->CreateSkinControl(m_csMessageText,CRect(50,70,50+353,70+40),this,ID_MB_LEFT_ICON_STATIC);
	m_pMessageTextStatic->SetBackgroundColor(-1,RGB(234,233,233));
	m_pMessageTextStatic->SetTextAlignment(TEXT_ALIGN_CENTER_HORIZ);

	switch(m_nButtonType)
	{
	case MB_OK_BUTTON:
		m_pButton1 = new CSkinnedButton;
		m_pButton1->SetImageResource(IDB_MB_OK_BUTTON,IDB_MB_OK_HOVER_BUTTON,IDB_MB_OK_HIT_BUTTON);
		m_pButton1->CreateSkinControl("",CRect(200,125,200+36,125+25),this,ID_MB_OK_BUTTON);
		break;
	case MB_OKCANCEL_BUTTON:
		m_pButton1 = new CSkinnedButton;
		m_pButton1->SetImageResource(IDB_MB_OK_BUTTON,IDB_MB_OK_HOVER_BUTTON,IDB_MB_OK_HIT_BUTTON);
		m_pButton1->CreateSkinControl("",CRect(170,125,170+36,125+25),this,ID_MB_OK_BUTTON);

		m_pButton2 = new CSkinnedButton;
		m_pButton2->SetImageResource(IDB_MB_CANCEL_BUTTON,IDB_MB_CANCEL_HOVER_BUTTON,IDB_MB_CANCEL_HIT_BUTTON);
		m_pButton2->CreateSkinControl("",CRect(230,125,230+55,125+25),this,ID_MB_CANCEL_BUTTON);
		break;
	case MB_YESNO_BUTTON:
		m_pButton1 = new CSkinnedButton;
		m_pButton1->SetImageResource(IDB_MB_YES_BUTTON,IDB_MB_YES_HOVER_BUTTON,IDB_MB_YES_HIT_BUTTON);
		m_pButton1->CreateSkinControl("",CRect(180,125,180+35,125+25),this,ID_MB_YES_BUTTON);

		m_pButton2 = new CSkinnedButton;
		m_pButton2->SetImageResource(IDB_MB_NO_BUTTON,IDB_MB_NO_HOVER_BUTTON,IDB_MB_NO_HIT_BUTTON);
		m_pButton2->CreateSkinControl("",CRect(230,125,230+32,125+25),this,ID_MB_NO_BUTTON);
		break;
	default:
		break;
	}
}

void CMessageBoxDlg::DestroyControls()
{	
	if(m_pTopBandStatic)	
	{
		delete m_pTopBandStatic;
		m_pTopBandStatic = 0;
	}
	if(m_pLeftIconStatic)	
	{
		delete m_pLeftIconStatic;
		m_pLeftIconStatic = 0;
	}
	if(m_pMessageTextStatic)	
	{
		delete m_pMessageTextStatic;
		m_pMessageTextStatic = 0;
	}
	if(m_pButton1)
	{
		delete m_pButton1;
		m_pButton1 = 0;
	}
	if(m_pButton2)
	{
		delete m_pButton2;
		m_pButton2 = 0;
	}
}


void CMessageBoxDlg::InitializeMessageBox(int nMessageID,int nButtonType, CString csTopBandText, CString csUserText)
{
	m_nMessageID = nMessageID;
	m_nButtonType = nButtonType;
	m_csTopBandText = "   " + csTopBandText;
	m_csUserText = csUserText;
	
	if(csTopBandText == "")
	{
		switch(g_nArrIcon[m_nMessageID])
		{
			case MB_ICON_CONFIRMATION:
				m_csTopBandText = "   Confirmation";
				break;
			case MB_ICON_ERROR:
				m_csTopBandText = "   Error";
				break;
			case MB_ICON_INFORMATION:
				m_csTopBandText = "   Information";
				break;
			case MB_ICON_WARNING:
				m_csTopBandText = "   Warning";
				break;
			default:
				break;
		}
	}

	m_csMessageText = g_csArrMessageText[m_nMessageID];
	m_csMessageText.Replace("^",(LPTSTR)(LPCTSTR)(m_csUserText));
}

BOOL CMessageBoxDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		switch(LOWORD(pMsg->wParam))
		{
		case MSG_COMMAND:
			if (m_nFlags & (WF_MODALLOOP|WF_CONTINUEMODAL))
			{
				EndDialog(HIWORD(pMsg->wParam));
				EndModalLoop(HIWORD(pMsg->wParam));
			}
			return TRUE;
		}
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}