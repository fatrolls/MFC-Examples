// WavTipSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WavTipSample.h"
#include "WavTipSampleDlg.h"
#include "HyperLink.h"

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
	CHyperLink	m_MailLink;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_MAIL_LINK, m_MailLink);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_MailLink.SetURL(_T("mailto:giancarlo@saria.com"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CWavTipSampleDlg dialog

CWavTipSampleDlg::CWavTipSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWavTipSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavTipSampleDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWavTipSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavTipSampleDlg)
	DDX_Control(pDX, IDC_CHECK_TIPSOUND, m_checkTipSound);
	DDX_Control(pDX, IDC_COMBO_TIPSOUND, m_comboTipSound);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWavTipSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CWavTipSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_TIPSOUND, OnCheckTipsound)
	ON_CBN_SELCHANGE(IDC_COMBO_TIPSOUND, OnSelchangeComboTipsound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavTipSampleDlg message handlers

BOOL CWavTipSampleDlg::OnInitDialog()
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
	
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);
		
		// Set the Tip Sound
		m_tooltip.SetPopupSound(IDR_TOOLTIP_SOUND1);
				
		m_tooltip.AddTool(GetDlgItem(IDOK), IDS_OKAY_TOOLTIP);
		m_tooltip.AddTool(GetDlgItem(IDCANCEL), IDS_CANCEL_TOOLTIP);
		m_tooltip.AddTool(GetDlgItem(IDC_COMBO_TIPSOUND), 
			IDS_COMBOBOX_TOOLTIP);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_TIPSOUND), 
			IDS_CHECKBOX_TOOLTIP);		
	}

	m_checkTipSound.SetCheck(TRUE);
	m_comboTipSound.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWavTipSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWavTipSampleDlg::OnPaint() 
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
HCURSOR CWavTipSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWavTipSampleDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);

		return CDialog::PreTranslateMessage(pMsg);
	}
}

void CWavTipSampleDlg::OnCheckTipsound() 
{
	if (!m_checkTipSound.GetCheck())
		m_tooltip.SetPopupSound(NULL);
	else
		OnSelchangeComboTipsound();	
}

void CWavTipSampleDlg::OnSelchangeComboTipsound() 
{	
	switch (m_comboTipSound.GetCurSel()) {
	case 0:
		m_tooltip.SetPopupSound(IDR_TOOLTIP_SOUND1);
		break;
	case 1:
		m_tooltip.SetPopupSound(IDR_TOOLTIP_SOUND2);
		break;
	}
}

void CWavTipSampleDlg::OnOK() 
{
	CAboutDlg dlg;
	dlg.DoModal();
	CDialog::OnOK();
}

void CWavTipSampleDlg::OnCancel() 
{
	CAboutDlg dlg;
	dlg.DoModal();
	CDialog::OnCancel();
}
