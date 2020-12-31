// NumberConversionDemoDlg.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "utsampleabout.h"
#include "NumberConversionDemo.h"
#include "NumberConversionDemoDlg.h"
#include "OxInteger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CNumberConversionDemoDlg dialog

CNumberConversionDemoDlg::CNumberConversionDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNumberConversionDemoDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CNumberConversionDemoDlg)
	m_nBaseIn = -1;
	m_nBaseOut = -1;
	m_nRadixIn = 0;
	m_nRadixOut = 0;
	m_sInput = _T("");
	m_sOutput = _T("");
	m_bSeparated = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CNumberConversionDemoDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumberConversionDemoDlg)
	DDX_Control(pDX, IDC_OUTPUT, m_wndOutput);
	DDX_Control(pDX, IDC_INPUT, m_wndInput);
	DDX_Control(pDX, IDC_RADIX_OUT, m_wndRadixOut);
	DDX_Control(pDX, IDC_RADIX_IN, m_wndRadixIn);
	DDX_Control(pDX, IDC_SPIN_OUT, m_wndSpinOut);
	DDX_Control(pDX, IDC_SPIN_IN, m_wndSpinIn);
	DDX_Radio(pDX, IDC_BINARY_IN, m_nBaseIn);
	DDX_Radio(pDX, IDC_BINARY_OUT, m_nBaseOut);
	DDX_Text(pDX, IDC_RADIX_IN, m_nRadixIn);
	DDX_Text(pDX, IDC_RADIX_OUT, m_nRadixOut);
	DDX_Text(pDX, IDC_INPUT, m_sInput);
	DDX_Text(pDX, IDC_OUTPUT, m_sOutput);
	DDX_Check(pDX, IDC_SEPARATED, m_bSeparated);
	//}}AFX_DATA_MAP
	}

BEGIN_MESSAGE_MAP(CNumberConversionDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CNumberConversionDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OTHER_IN, OnOtherIn)
	ON_BN_CLICKED(IDC_OTHER_OUT, OnOtherOut)
	ON_BN_CLICKED(IDC_BINARY_IN, OnStandardIn)
	ON_BN_CLICKED(IDC_BINARY_OUT, OnStandardOut)
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_DECIMAL_IN, OnStandardIn)
	ON_BN_CLICKED(IDC_HEXADECIMAL_IN, OnStandardIn)
	ON_BN_CLICKED(IDC_OCTAL_IN, OnStandardIn)
	ON_BN_CLICKED(IDC_DECIMAL_OUT, OnStandardOut)
	ON_BN_CLICKED(IDC_HEXADECIMAL_OUT, OnStandardOut)
	ON_BN_CLICKED(IDC_OCTAL_OUT, OnStandardOut)
	ON_BN_CLICKED(IDC_COPY_IN, OnCopyIn)
	ON_BN_CLICKED(IDC_PAST_IN, OnPastIn)
	ON_BN_CLICKED(IDC_COPY_OUT, OnCopyOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberConversionDemoDlg message handlers

BOOL CNumberConversionDemoDlg::OnInitDialog()
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
	
	// Initialization 
	m_wndSpinIn.SetRange((short)COXInteger::m_nMinRadix, (short)COXInteger::m_nMaxRadix);
	m_wndSpinOut.SetRange((short)COXInteger::m_nMinRadix, (short)COXInteger::m_nMaxRadix);

	// Enable other by default
	m_wndRadixIn.EnableWindow(FALSE);
	m_wndSpinIn.EnableWindow(FALSE);
	m_wndRadixOut.EnableWindow(FALSE);
	m_wndSpinOut.EnableWindow(FALSE);
	
	// ... Decimal
	m_nBaseIn = 2; 
	// ... Hex
	m_nBaseOut = 3;  

	m_nRadixIn = 2;
	m_nRadixOut = 2;

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
	}

void CNumberConversionDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAM,ID_DESCRIPTION_FILE);
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

void CNumberConversionDemoDlg::OnPaint() 
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
HCURSOR CNumberConversionDemoDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon;
	}

void CNumberConversionDemoDlg::OnOtherIn() 
	{
	m_wndRadixIn.EnableWindow(TRUE);
	m_wndSpinIn.EnableWindow(TRUE);
	}

void CNumberConversionDemoDlg::OnOtherOut() 
	{
	m_wndRadixOut.EnableWindow(TRUE);
	m_wndSpinOut.EnableWindow(TRUE);
	}

void CNumberConversionDemoDlg::OnStandardIn() 
	{
	m_wndRadixIn.EnableWindow(FALSE);
	m_wndSpinIn.EnableWindow(FALSE);
	}

void CNumberConversionDemoDlg::OnStandardOut() 
	{
	m_wndRadixOut.EnableWindow(FALSE);
	m_wndSpinOut.EnableWindow(FALSE);
	}

void CNumberConversionDemoDlg::OnConvert() 
	{
	if (!UpdateData(TRUE))
		return;

	int nRadixIn = 10;
	int nRadixOut = 10;
	switch (m_nBaseIn)
		{
		case 0:
			nRadixIn = 2;
			break;
		case 1:
			nRadixIn = 8;
			break;
		case 2:
			nRadixIn = 10;
			break;
		case 3:
			nRadixIn = 16;
			break;
		case 4:
			nRadixIn = m_nRadixIn;
			break;
		default:
			TRACE1("CNumberConversionDemoDlg::OnConvert : Unexpected case in switch m_nBaseIn = %i\n", m_nBaseIn);
			ASSERT(FALSE);
			break;
		}

	switch (m_nBaseOut)
		{
		case 0:
			nRadixOut = 2;
			break;
		case 1:
			nRadixOut = 8;
			break;
		case 2:
			nRadixOut = 10;
			break;
		case 3:
			nRadixOut = 16;
			break;
		case 4:
			nRadixOut = m_nRadixOut;
			break;
		default:
			TRACE1("CNumberConversionDemoDlg::OnConvert : Unexpected case in switch m_nBaseOut = %i\n", m_nBaseOut);
			ASSERT(FALSE);
			break;
		}

	COXInteger integer;
	integer.SetStringNumber(m_sInput, nRadixIn);
	m_sOutput = integer.GetStringNumber(nRadixOut, m_bSeparated);

	// Test conversion features
	COXInteger a(_T("7B"), 16);
	COXInteger b(456);
	COXInteger c;

	ASSERT(a == 123);

	c = a + b;
	ASSERT(c == 579);

	a = b / 3;
	ASSERT(a == 152);

	c = c - 79;
	ASSERT(c == 500);
	ASSERT(c.GetStringNumber(2) == _T("111110100"));

	UpdateData(FALSE);
	}

void CNumberConversionDemoDlg::OnCopyIn() 
	{
	m_wndInput.SetSel(0, -1);
	m_wndInput.Copy();
	}

void CNumberConversionDemoDlg::OnPastIn() 
	{
	m_wndInput.SetSel(0, -1);
	m_wndInput.Clear();
	m_wndInput.Paste();
	}

void CNumberConversionDemoDlg::OnCopyOut() 
	{
	m_wndOutput.SetSel(0, -1);
	m_wndOutput.Copy();
	}
