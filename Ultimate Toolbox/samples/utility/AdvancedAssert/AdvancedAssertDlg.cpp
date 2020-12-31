// AdvancedAssertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdvancedAssert.h"
#include "AdvancedAssertDlg.h"
#include "UTSampleAbout.h"
#include "CustomizeAssertDlg.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// message to react on "About" action
static UINT g_nAboutMsgID=RegisterWindowMessage(_T("AboutAdvancedAssert"));
// message to react on "Close" action
static UINT g_nCloseMsgID=RegisterWindowMessage(_T("CloseAdvancedAssert"));
// message to react on "Customize" action
static UINT g_nCustomizeMsgID=RegisterWindowMessage(_T("CustomizeAdvancedAssert"));
// message to react on "Assertion" text
static UINT g_nAssertionMsgID=RegisterWindowMessage(_T("IncurAssertionAdvancedAssert"));
/////////////////////////////////////////////////////////////////////////////
// CAdvancedAssertDlg dialog

CAdvancedAssertDlg::CAdvancedAssertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedAssertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedAssertDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdvancedAssertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedAssertDlg)
	DDX_Control(pDX, IDC_ASSERTION, m_ctlAssertion);
	DDX_Control(pDX, IDC_CUSTOMIZE, m_ctlCustomize);
	DDX_Control(pDX, IDC_SAMPLE_CAPTION, m_ctlStaticSampleCaption);
	DDX_Control(pDX, IDC_STATIC_ABOUT, m_ctlStaticAbout);
	DDX_Control(pDX, IDC_STATIC_CLOSE, m_ctlStaticClose);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdvancedAssertDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvancedAssertDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	// map messages with corresponding handlers
	ON_REGISTERED_MESSAGE(g_nAboutMsgID,OnAboutActivated)
	ON_REGISTERED_MESSAGE(g_nCloseMsgID,OnCloseActivated)
	ON_REGISTERED_MESSAGE(g_nCustomizeMsgID,OnCustomizeActivated)
	ON_REGISTERED_MESSAGE(g_nAssertionMsgID,OnAssertionActivated)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedAssertDlg message handlers

BOOL CAdvancedAssertDlg::OnInitDialog()
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
	m_ctlStaticClose.SetShowToolTip(FALSE);

	// set action as userdefined 
	// don't forget to set callback message and handle to recipient window
	m_ctlStaticAbout.SetAction(ID_HLACTION_USERDEFINED,NULL,NULL,NULL,
		SW_SHOWNORMAL,g_nAboutMsgID,GetSafeHwnd());
	m_ctlStaticAbout.SetToolTipText(_T("Information about Advanced Asserts"));

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

	// set action as userdefined 
	// don't forget to set callback message and handle to recipient window
	m_ctlCustomize.SetAction(ID_HLACTION_USERDEFINED,NULL,NULL,NULL,
		SW_SHOWNORMAL,g_nCustomizeMsgID,GetSafeHwnd());
	m_ctlCustomize.SetToolTipText(_T("Click here to customize assertion dialog"));

	// set action as userdefined 
	// don't forget to set callback message and handle to recipient window
	GetFont()->GetObject(sizeof(lf), &lf);
	lf.lfUnderline=FALSE;
	m_ctlAssertion.SetTextLogFont(&lf);
	m_ctlAssertion.SetUnvisitedColor(RGB(0,128,128));
	m_ctlAssertion.SetFitToText(FALSE);
	m_ctlAssertion.SetToolTipText(_T("Click here to fire an assertion"));
	m_ctlAssertion.SetAction(ID_HLACTION_USERDEFINED,NULL,NULL,NULL,
		SW_SHOWNORMAL,g_nAssertionMsgID,GetSafeHwnd());

	m_sNote1=AppGetAssertNote1();
	m_sNote2=AppGetAssertNote2();
	m_sEmailAddress="Support[SMTP:support@theUltimateToolbox.com]";
	AppSetAssertEmailAddress(m_sEmailAddress);
	m_bSendMail=AppGetAssertSendState();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdvancedAssertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAdvancedAssertDlg::OnPaint() 
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
HCURSOR CAdvancedAssertDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// "About" action was activated
LONG CAdvancedAssertDlg::OnAboutActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME, ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();

	return (LONG)1;
}

// "Close" action was activated
LONG CAdvancedAssertDlg::OnCloseActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	// just close the dialog
	EndDialog(IDOK);

	return (LONG)1;
}

// "Customize" action was activated
LONG CAdvancedAssertDlg::OnCustomizeActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CCustomizeAssertDlg dlg;
	dlg.m_sNote1=m_sNote1;
	dlg.m_sNote2=m_sNote2;
	dlg.m_sEmailAddress=m_sEmailAddress;
	dlg.m_bSendMail=m_bSendMail;

	switch(dlg.DoModal())
	{
	case IDOK:
	{
		m_sNote1=dlg.m_sNote1;
		m_sNote2=dlg.m_sNote2;
		m_sEmailAddress=dlg.m_sEmailAddress;
		m_bSendMail=dlg.m_bSendMail;
		AppSetAssertEmailAddress(m_sEmailAddress);
		AppSetAssertNote1(m_sNote1);
		AppSetAssertNote2(m_sNote2);
		AppSetAssertSendState(m_bSendMail);	}
		break;
	case IDCANCEL:
	{

	}
		break;
	}

	return (LONG)1;
}

// "Assertion" action was activated
LONG CAdvancedAssertDlg::OnAssertionActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	int nMonth=0  ;
	ASSERT( (nMonth >= 1) && (nMonth <=12) ) ;

#if !(defined(_DEBUG) || defined(BETA))
	AfxMessageBox(_T("The sample was compiled in release mode without declaring \nBETA in the stdafx.h. Assertion won't be activated!"));
#endif

	return (LONG)1;
}

