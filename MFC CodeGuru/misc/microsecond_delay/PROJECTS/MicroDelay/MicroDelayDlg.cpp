// MicroDelayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MicroSecond.h"
#include "MicroDelay.h"
#include "MicroDelayDlg.h"

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
// CMicroDelayDlg dialog

CMicroDelayDlg::CMicroDelayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMicroDelayDlg::IDD, pParent)
{
    puSec = (CMicroSecond*)new CMicroSecond;

	//{{AFX_DATA_INIT(CMicroDelayDlg)
	m_nLoopCount1 = 0;
	m_nLoopCount2 = 0;
	m_nLoop_per_uSecond = 0;
	m_nMilliSecondPerTenSeconds = 0;
	m_strError = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMicroDelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMicroDelayDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMicroDelayDlg, CDialog)
	//{{AFX_MSG_MAP(CMicroDelayDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DOIT, OnDoit)
	ON_BN_CLICKED(IDC_INITIALIZE, OnInitialize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMicroDelayDlg message handlers

BOOL CMicroDelayDlg::OnInitDialog()
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

void CMicroDelayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMicroDelayDlg::OnPaint() 
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
HCURSOR CMicroDelayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMicroDelayDlg::OnDoit() 
{
   
    BeginWaitCursor();

    DWORD dwStart = GetTickCount();
    
    puSec->MicroDelay(1000000);

    DWORD dwStop = GetTickCount();

    EndWaitCursor();

    m_nMilliSecondPerTenSeconds = dwStop - dwStart;
    
    SetDlgItemInt( IDC_MILLISECOND_TEST, m_nMilliSecondPerTenSeconds, TRUE );

    double dError =  (((double)m_nMilliSecondPerTenSeconds - 1000.0) / 1000.0) * 100.0 ;
    m_strError.Format("%2.1f %%", dError);

    SetDlgItemText ( IDC_MILLISECOND_TEST_ERROR, m_strError);

  //  puSec->TweekLoopPerMicrosecond(dError);


}

void CMicroDelayDlg::OnOK() 
{
    delete puSec;

	CDialog::OnOK();
}


void CMicroDelayDlg::Tweek()
{
    int nRetry = 0;

    BeginWaitCursor();

    do {


    DWORD dwStart = GetTickCount();
    
    puSec->MicroDelay(1000000);

    DWORD dwStop = GetTickCount();


    m_nMilliSecondPerTenSeconds = dwStop - dwStart;
    
    SetDlgItemInt( IDC_MILLISECOND_TEST, m_nMilliSecondPerTenSeconds, TRUE );

    double dError =  (((double)m_nMilliSecondPerTenSeconds - 1000.0) / 1000.0) * 100.0 ;
    
    if ( dError >= 95.0 && dError <= 105.0 )
    {
        break;
    }
    
    m_strError.Format("%2.1f %%", dError);

    SetDlgItemText ( IDC_MILLISECOND_TEST_ERROR, m_strError);

    puSec->TweekLoopPerMicrosecond(dError);

    nRetry ++;
    } while ( nRetry < 10 );

    EndWaitCursor();

}

void CMicroDelayDlg::OnInitialize() 
{
	 Tweek();
}
