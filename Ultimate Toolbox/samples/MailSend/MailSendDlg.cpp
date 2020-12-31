// MailSendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MailSend.h"
#include "MailSendDlg.h"
#include "MailEngine.h"

#include "oxmdisp.h"

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
// CMailSendApp

BEGIN_MESSAGE_MAP(CMailSendApp, CWinApp)
	//{{AFX_MSG_MAP(CMailSendApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailSendDlg dialog

CMailSendDlg::CMailSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMailSendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMailSendDlg)
	m_sAddress = _T("");
	m_sContent = _T("");
	m_sPassword = _T("");
	m_sProfile = _T("");
	m_sSubject = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailSendDlg)
	DDX_Control(pDX, IDC_LIST_ATTACHMENTS, m_lbAttachments);
	DDX_Text(pDX, IDC_ADDRESS, m_sAddress);
	DDX_Text(pDX, IDC_CONTENT, m_sContent);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_PROFILE, m_sProfile);
	DDX_Text(pDX, IDC_SUBJECT, m_sSubject);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMailSendDlg, CDialog)
	//{{AFX_MSG_MAP(CMailSendDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_MAIL, OnSendMail)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_BUTTON_ADDATTACHMENT, OnButtonAddattachment)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEATTACHMENT, OnButtonRemoveattachment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailSendDlg message handlers

BOOL CMailSendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_sProfile=_T("Microsoft Outlook");
	m_sAddress=_T("info@theUltimateToolBox.com");
	m_sSubject=_T("Test Mail Send");
	m_sContent=_T("This is a message sent to check the MailSend sample functionality");

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMailSendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMailSendDlg::OnPaint() 
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
HCURSOR CMailSendDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMailSendDlg::OnSendMail() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	
	CStringArray sAttachments;
	for(int nIndex=0; nIndex<m_lbAttachments.GetCount(); nIndex++)
	{
		CString sAttachment;
		m_lbAttachments.GetText(nIndex,sAttachment);
		sAttachments.Add(sAttachment);
	}

	BOOL bResult=theMailEngine.Send(m_sProfile,m_sPassword,
		m_sAddress,m_sSubject,m_sContent,sAttachments);

	if(bResult)
		AfxMessageBox(_T("Message was successfully sent"));
	else
		AfxMessageBox(_T("Failed to send a message"));
}

void CMailSendDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CMailSendDlg::OnButtonAddattachment() 
{
	// TODO: Add your control notification handler code here

	// Ask the user to select a directory
	CFileDialog fileDlg(TRUE);
	if (fileDlg.DoModal()==IDOK)
	{
		CString sAttachment=fileDlg.GetPathName();
		m_lbAttachments.AddString(sAttachment);
		UpdateData(FALSE);
	}
	
}

void CMailSendDlg::OnButtonRemoveattachment() 
{
	// TODO: Add your control notification handler code here
	int nSelItem=m_lbAttachments.GetCurSel();
	if(nSelItem!=LB_ERR)
		m_lbAttachments.DeleteString(nSelItem);
}
