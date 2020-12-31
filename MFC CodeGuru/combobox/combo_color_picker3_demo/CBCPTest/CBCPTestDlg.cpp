// CBCPTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CBCPTest.h"
#include "CBCPTestDlg.h"

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
// CCBCPTestDlg dialog

CCBCPTestDlg::CCBCPTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCBCPTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCBCPTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCBCPTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCBCPTestDlg)
	DDX_Control(pDX, IDC_COLORPICKER, m_cpcbColorPicker);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCBCPTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCBCPTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DISABLECOLORPICKER, OnDisableColorPicker)
	ON_BN_CLICKED(IDC_GETNAME, OnGetName)
	ON_BN_CLICKED(IDC_GETVALUE, OnGetValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBCPTestDlg message handlers

BOOL CCBCPTestDlg::OnInitDialog()
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

void CCBCPTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCBCPTestDlg::OnPaint() 
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
HCURSOR CCBCPTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCBCPTestDlg::OnDisableColorPicker() 
{
	if( IsDlgButtonChecked( IDC_DISABLECOLORPICKER ) )		// If Disable Button Checked
		m_cpcbColorPicker.EnableWindow( FALSE );			// Disable Control
	else													// If Not
		m_cpcbColorPicker.EnableWindow( TRUE );				// Enable Control

	return;													// Done!
}


void CCBCPTestDlg::OnGetName() 
{
	static	CString	sMessage;

	sMessage.Format( "The Selected Color Name Is:\t%s.", 
			m_cpcbColorPicker.GetSelectedColorName() );		// Build Message
	
	MessageBox( sMessage, "Selected Color",
			MB_ICONINFORMATION );							// Display Message

	return;													// Done!
}


void CCBCPTestDlg::OnGetValue() 
{
	static	CString	sMessage;
	COLORREF		crSelColor = 0;

	crSelColor = m_cpcbColorPicker.GetSelectedColorValue();	// Get Selected Color Value
	sMessage.Format( "The Selected Color Value Is:\n\n"
			"0x%08X Or RGB( 0x%02X, 0x%02X, 0x%02X ).",
			crSelColor, GetRValue( crSelColor ),
			GetGValue( crSelColor ),
			GetBValue( crSelColor ) );						// Build Message

	MessageBox( sMessage, "Selected Color",
			MB_ICONINFORMATION );							// Display Message

	return;													// Done!
}
