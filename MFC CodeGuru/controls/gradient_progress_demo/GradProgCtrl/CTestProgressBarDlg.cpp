// CTestProgressBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CTestProgressBar.h"
#include "CTestProgressBarDlg.h"

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



BOOL PeekAndPump()
{
	static MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
		if (!AfxGetApp()->PumpMessage()) {
			::PostQuitMessage(0);
			return FALSE;
		}	
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCTestProgressBarDlg dialog

CCTestProgressBarDlg::CCTestProgressBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCTestProgressBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCTestProgressBarDlg)
	m_nRange = 100;
	m_bShowPercent = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCTestProgressBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTestProgressBarDlg)
	DDX_Control(pDX, IDC_CLR_TEXT, m_cClrText);
	DDX_Control(pDX, IDC_CLR_START, m_cClrStart);
	DDX_Control(pDX, IDC_CLR_END, m_cClrEnd);
	DDX_Control(pDX, IDC_CLR_BKGND, m_cClrBkGnd);
	DDX_Control(pDX, IDC_PROGRESS, m_cProgress);
	DDX_Text(pDX, IDC_RANGE, m_nRange);
	DDX_Check(pDX, IDC_SHOW_PERCENT, m_bShowPercent);
	//}}AFX_DATA_MAP
    DDX_ColourPicker(pDX, IDC_CLR_TEXT, m_clrText);
    DDX_ColourPicker(pDX, IDC_CLR_START, m_clrStart);
    DDX_ColourPicker(pDX, IDC_CLR_END, m_clrEnd);
    DDX_ColourPicker(pDX, IDC_CLR_BKGND, m_clrBk);

}

BEGIN_MESSAGE_MAP(CCTestProgressBarDlg, CDialog)
	//{{AFX_MSG_MAP(CCTestProgressBarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTestProgressBarDlg message handlers

BOOL CCTestProgressBarDlg::OnInitDialog()
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
	// Set the colors to the current progress colors
	m_clrText = m_cProgress.GetTextColor();
	m_clrBk = m_cProgress.GetBkColor();
	m_clrStart = m_cProgress.GetStartColor();
	m_clrEnd = m_cProgress.GetEndColor();
	UpdateData(FALSE);




	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCTestProgressBarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCTestProgressBarDlg::OnPaint() 
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
HCURSOR CCTestProgressBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Test the progress control
void CCTestProgressBarDlg::OnTest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_cProgress.SetRange(0, m_nRange);
	m_cProgress.ShowPercent(m_bShowPercent);

	m_cProgress.SetStartColor(m_clrStart);
	m_cProgress.SetEndColor(m_clrEnd);
	m_cProgress.SetTextColor(m_clrText);
	m_cProgress.SetBkColor(m_clrBk);
	

//	BeginWaitCursor();
	for (int i=0; i <= m_nRange; i++)
	{
		PeekAndPump();
	//	m_cProgress.StepIt();
		m_cProgress.SetPos(i);
	}
}
