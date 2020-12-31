// ZapMailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZapMail.h"
#include "ZapMailDlg.h"

#include "MailMessage.h"
#include "SMTP.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZapMailDlg dialog

CZapMailDlg::CZapMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZapMailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZapMailDlg)
	m_sBody = _T("");
	m_sFrom = _T("");
	m_sServer = _T("");
	m_sSubject = _T("");
	m_sTo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZapMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZapMailDlg)
	DDX_Control(pDX, IDC_EDIT_TO, m_ctlTo);
	DDX_Text(pDX, IDC_EDIT_BODY, m_sBody);
	DDX_Text(pDX, IDC_EDIT_FROM, m_sFrom);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_sServer);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_sSubject);
	DDX_Text(pDX, IDC_EDIT_TO, m_sTo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZapMailDlg, CDialog)
	//{{AFX_MSG_MAP(CZapMailDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDSEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZapMailDlg message handlers

BOOL CZapMailDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZapMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
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

void CZapMailDlg::OnPaint() 
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
HCURSOR CZapMailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZapMailDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	// That's a damn good idea.
	// I think I'll just go ahead and do that.
	UpdateData( TRUE );
	CSMTP smtp( m_sServer );
	CMailMessage msg;
	msg.m_sFrom = m_sFrom;
	msg.AddMultipleRecipients( m_sTo );
	msg.m_sSubject = m_sSubject;
	msg.m_sBody = m_sBody;
	if( !smtp.Connect() )
	{
		AfxMessageBox( smtp.GetLastError() );
		return;
	}
	if( !smtp.SendMessage( &msg ) )
	{
		AfxMessageBox( smtp.GetLastError() );
		return;
	}
	if( !smtp.Disconnect() )
	{
		AfxMessageBox( smtp.GetLastError() );
		return;
	}
	AfxMessageBox( _T( "Message Sent Successfully") );
	m_sTo = "";
	m_sSubject = "";
	m_sBody = "";
	UpdateData( FALSE );
	m_ctlTo.SetFocus();
}
