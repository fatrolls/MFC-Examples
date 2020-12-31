// HypLnkExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HypLnkEx.h"
#include "HypLnkExDlg.h"

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
// CHypLnkExDlg dialog

CHypLnkExDlg::CHypLnkExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHypLnkExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHypLnkExDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_bUseHover = FALSE;
	m_bUnderline = TRUE;
	m_bShowURL = TRUE;
	m_bItalic = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHypLnkExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHypLnkExDlg)	
	DDX_Control(pDX, IDC_HYPERLINK1, m_hyperlink1);
	DDX_Control(pDX, IDC_HYPERLINK2, m_hyperlink2);
	DDX_Control(pDX, IDC_HYPERLINK3, m_hyperlink3);
	DDX_Control(pDX, IDC_HYPERLINK4, m_hyperlink4);
	DDX_Control(pDX, IDC_HYPERLINK5, m_hyperlink5);	
	DDX_Check(pDX, IDC_CHECK1, m_bUnderline);	
	DDX_Check(pDX, IDC_CHECK2, m_bUseHover);	
	DDX_Check(pDX, IDC_CHECK3, m_bShowURL);	
	DDX_Check(pDX, IDC_CHECK4, m_bItalic);	
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CHypLnkExDlg, CDialog)
	//{{AFX_MSG_MAP(CHypLnkExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHypLnkExDlg message handlers

BOOL CHypLnkExDlg::OnInitDialog()
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
	
	// Extra initialization
	m_hyperlink5.SetURL("mailto:giancarlo@saria.com");
	m_hyperlink5.ModifyLinkStyle(0, CHyperLink::StyleDownClick);	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHypLnkExDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHypLnkExDlg::OnPaint() 
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
HCURSOR CHypLnkExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHypLnkExDlg::OnCheck1() 
{
	DWORD dwRemove=0L, dwAdd=0L;
	UpdateData();
	if (m_bUnderline)
		dwAdd = CHyperLink::StyleUnderline;
	else
		dwRemove = CHyperLink::StyleUnderline;

	m_hyperlink1.ModifyLinkStyle(dwRemove, dwAdd);
	m_hyperlink2.ModifyLinkStyle(dwRemove, dwAdd);
	m_hyperlink3.ModifyLinkStyle(dwRemove, dwAdd);
	m_hyperlink4.ModifyLinkStyle(dwRemove, dwAdd);
}

void CHypLnkExDlg::OnCheck2() 
{
	DWORD dwRemove=0L, dwAdd=0L;
	UpdateData();
	if (m_bUseHover)
		dwAdd = CHyperLink::StyleUseHover;
	else
		dwRemove = CHyperLink::StyleUseHover;

	m_hyperlink1.ModifyLinkStyle(dwRemove, dwAdd);
	m_hyperlink2.ModifyLinkStyle(dwRemove, dwAdd);
	m_hyperlink3.ModifyLinkStyle(dwRemove, dwAdd);
	m_hyperlink4.ModifyLinkStyle(dwRemove, dwAdd);
}

void CHypLnkExDlg::OnCheck3() 
{	
	UpdateData();
	if (m_bShowURL) {
		m_hyperlink1.SetWindowText(_T("http://www.firstsite.net"));
		m_hyperlink2.SetWindowText(_T("http://www.secondsite.net"));
		m_hyperlink3.SetWindowText(_T("http://www.thirdsite.net"));
		m_hyperlink4.SetWindowText(_T("http://www.fourthsite.net"));
	}
	else {
		m_hyperlink1.SetWindowText(_T("First site"));
		m_hyperlink2.SetWindowText(_T("Second site"));
		m_hyperlink3.SetWindowText(_T("Third site"));
		m_hyperlink4.SetWindowText(_T("Fourth site"));		
	}

}

void CHypLnkExDlg::OnCheck4() 
{
	UpdateData();

	CFont* pFont = m_hyperlink1.GetFont();	
	
	LOGFONT lf;
	if (pFont != NULL) {
		pFont->GetLogFont(&lf);
		lf.lfItalic = m_bItalic;
		m_Font.DeleteObject();
		m_Font.CreateFontIndirect(&lf);		
	}
	
	m_hyperlink1.SetFont(&m_Font);
	m_hyperlink2.SetFont(&m_Font);
	m_hyperlink3.SetFont(&m_Font);
	m_hyperlink4.SetFont(&m_Font);

}
