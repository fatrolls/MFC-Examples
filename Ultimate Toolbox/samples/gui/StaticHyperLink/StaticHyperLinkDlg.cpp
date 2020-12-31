// StaticHyperLinkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StaticHyperLink.h"
#include "StaticHyperLinkDlg.h"
#include "UTSampleAbout.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// message to react on "About" action
static UINT g_nAboutMsgID=RegisterWindowMessage(_T("AboutHyperLink"));
// message to react on "Close" action
static UINT g_nCloseMsgID=RegisterWindowMessage(_T("CloseHyperLink"));

/////////////////////////////////////////////////////////////////////////////
// CStaticHyperLinkDlg dialog

CStaticHyperLinkDlg::CStaticHyperLinkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStaticHyperLinkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStaticHyperLinkDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStaticHyperLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStaticHyperLinkDlg)
	DDX_Control(pDX, IDC_STATIC_HINT, m_ctlStaticHint);
	DDX_Control(pDX, IDC_SAMPLE_CAPTION, m_ctlStaticSampleCaption);
	DDX_Control(pDX, IDC_STATIC_SOLITAIRE, m_ctlStaticSolitaire);
	DDX_Control(pDX, IDC_STATIC_WEB_UT, m_ctlStaticWebUT);
	DDX_Control(pDX, IDC_STATIC_WEB_DUNDAS, m_ctlStaticWebDundas);
	DDX_Control(pDX, IDC_STATIC_FAX, m_ctlStaticFax);
	DDX_Control(pDX, IDC_STATIC_EMAIL_SALES, m_ctlStaticEmailSales);
	DDX_Control(pDX, IDC_STATIC_EMAIL_ANDREI, m_ctlStaticEmailAndrei);
	DDX_Control(pDX, IDC_STATIC_CLOSE, m_ctlStaticClose);
	DDX_Control(pDX, IDC_STATIC_BILL_GATES, m_ctlStaticBillGates);
	DDX_Control(pDX, IDC_STATIC_ABOUT, m_ctlStaticAbout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStaticHyperLinkDlg, CDialog)
	//{{AFX_MSG_MAP(CStaticHyperLinkDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	// map messages with corresponding handlers
	ON_REGISTERED_MESSAGE(g_nAboutMsgID,OnAboutActivated)
	ON_REGISTERED_MESSAGE(g_nCloseMsgID,OnCloseActivated)
	ON_STN_CLICKED(IDC_STATIC_EMAIL_ANDREI, OnStnClickedStaticEmailAndrei)
	ON_STN_CLICKED(IDC_STATIC_FAX, OnStnClickedStaticFax)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticHyperLinkDlg message handlers

BOOL CStaticHyperLinkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	// set new LOGINFO of the font of the COXStaticHyperLink object
	LOGFONT lf;
	GetFont()->GetObject(sizeof(lf), &lf);
	lf.lfUnderline=TRUE;
	lf.lfWeight=1000;
	lf.lfHeight=-18;
	CFont font;
	font.CreateFontIndirect(&lf);
	m_ctlStaticClose.SetTextFont(&font);
	// set action as userdefined 
	// don't forget to set callback message and handle to recipient window
	m_ctlStaticClose.SetAction(ID_HLACTION_USERDEFINED,NULL,NULL,NULL,
		SW_SHOWNORMAL,g_nCloseMsgID,GetSafeHwnd());
//	m_ctlStaticClose.SetLinkCursor(NULL);

	// set action as userdefined 
	// don't forget to set callback message and handle to recipient window
	m_ctlStaticAbout.SetAction(ID_HLACTION_USERDEFINED,NULL,NULL,NULL,
		SW_SHOWNORMAL,g_nAboutMsgID,GetSafeHwnd());

	// open website
	m_ctlStaticWebUT.SetAction(ID_HLACTION_OPEN,_T("www.codeproject.com"));
	// open new e-mail message
	m_ctlStaticBillGates.SetAction(ID_HLACTION_OPEN,_T("mailto:billg@microsoft.com"));
	// open new e-mail message
	m_ctlStaticEmailAndrei.SetAction(ID_HLACTION_OPEN,_T("mailto:info@theUltimateToolbox.com"));
	// open new e-mail message, use window text as address of mail recipient
	m_ctlStaticEmailSales.SetAction(ID_HLACTION_EMAIL);

	// run sol.exe (Solitaire)
	m_ctlStaticSolitaire.SetAction(ID_HLACTION_OPEN,_T("sol.exe"));

	// run dialer.exe (Phone Dialer)
	m_ctlStaticFax.SetAction(ID_HLACTION_OPEN,_T("dialer.exe"));

	// set properties of COXStatic controls
	//
	lf.lfUnderline=FALSE;
	lf.lfItalic=TRUE;
	lf.lfWeight=1000;
	lf.lfHeight=-14;
	UTBStr::tcscpy(lf.lfFaceName, LF_FACESIZE, _T("Times New Roman"));
	m_ctlStaticSampleCaption.SetTextLogFont(&lf);
	m_ctlStaticSampleCaption.SetTextColor(RGB(0,0,128));
	m_ctlStaticSampleCaption.SetShowToolTip(TRUE);
	m_ctlStaticSampleCaption.SetToolTipText(_T("Why do we need tool tip here?"));
	m_ctlStaticSampleCaption.SetFitToText(TRUE);

	if(m_ctlStaticHint.GetTextLogFont(&lf))
	{
		lf.lfWeight=1000;
		lf.lfUnderline=TRUE;
		m_ctlStaticHint.SetTextLogFont(&lf);
	}
	m_ctlStaticHint.SetTextColor(RGB(128,0,0));
	m_ctlStaticHint.SetFitToText(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStaticHyperLinkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME, ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStaticHyperLinkDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStaticHyperLinkDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// "About" action was activated
LONG CStaticHyperLinkDlg::OnAboutActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME, ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();

	return (LONG)1;
}

// "Close" action was activated
LONG CStaticHyperLinkDlg::OnCloseActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	// just close the dialog
	EndDialog(IDOK);

	return (LONG)1;
}

void CStaticHyperLinkDlg::OnStnClickedStaticEmailAndrei()
{
	// TODO: Add your control notification handler code here
}

void CStaticHyperLinkDlg::OnStnClickedStaticFax()
{
	// TODO: Add your control notification handler code here
}
