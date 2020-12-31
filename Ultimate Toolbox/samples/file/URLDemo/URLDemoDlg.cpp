// URLDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "URLDemo.h"
#include "URLDemoDlg.h"
#include "OXURL.h"
#include "OXIteratorUNC.h"
#include "OXCheck.h"
#include "UNCListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CURLDemoDlg dialog

CURLDemoDlg::CURLDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CURLDemoDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CURLDemoDlg)
	m_sBaseName = _T("");
	m_sDirectory = _T("");
	m_sExtension = _T("");
	m_sFile = _T("");
	m_nPort = 0;
	m_sProtocol = _T("");
	m_sServer = _T("");
	m_sShare = _T("");
	m_sURL_UNC = _T("");
	m_bURLPart = FALSE;
	m_bIncludeDirs = FALSE;
	m_bIncludeFiles = TRUE;
	m_bRecursive = FALSE;
	m_bDepthFirst = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CURLDemoDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CURLDemoDlg)
	DDX_Text(pDX, IDC_BASE_NAME, m_sBaseName);
	DDX_Text(pDX, IDC_DIRECTORY, m_sDirectory);
	DDX_Text(pDX, IDC_EXTENSION, m_sExtension);
	DDX_Text(pDX, IDC_FILE, m_sFile);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Text(pDX, IDC_PROTOCOL, m_sProtocol);
	DDX_Text(pDX, IDC_SERVER, m_sServer);
	DDX_Text(pDX, IDC_SHARE, m_sShare);
	DDX_Text(pDX, IDC_URL_UNC, m_sURL_UNC);
	DDX_Check(pDX, IDC_URL_PART, m_bURLPart);
	DDX_Check(pDX, IDC_INCLUDE_DIRS, m_bIncludeDirs);
	DDX_Check(pDX, IDC_INCLUDE_FILES, m_bIncludeFiles);
	DDX_Check(pDX, IDC_RECURSIVE, m_bRecursive);
	DDX_Check(pDX, IDC_DEPTH_FIRST, m_bDepthFirst);
	//}}AFX_DATA_MAP
	}

BEGIN_MESSAGE_MAP(CURLDemoDlg, CDialog)
//{{AFX_MSG_MAP(CURLDemoDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_COMBINE_URL, OnCombineURL)
ON_BN_CLICKED(IDC_SPLIT_URL, OnSplitURL)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_COMBINE_UNC, OnCombineUNC)
	ON_BN_CLICKED(IDC_SPLIT_UNC, OnSplitUNC)
	ON_BN_CLICKED(IDC_LIST, OnList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CURLDemoDlg message handlers

BOOL CURLDemoDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
	}

void CURLDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
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

void CURLDemoDlg::OnPaint() 
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
HCURSOR CURLDemoDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon;
	}

void CURLDemoDlg::OnSplitURL() 
	{
	if (!UpdateData(TRUE))
		return;

	COXURL URL;
	URL = m_sURL_UNC;

	// Get the result
	m_sProtocol = URL.Protocol();
	m_nPort = URL.Port();
	m_sServer = URL.UNC().Server();
	m_sShare = URL.UNC().Share();
	m_sDirectory = URL.UNC().Directory();
	m_sFile = URL.UNC().File();
	m_sBaseName = URL.UNC().Base();
	m_sExtension = URL.UNC().Extension();
	m_bURLPart = URL.UNC().URLPart();

	// Get the input parameters again 
	m_sURL_UNC = URL;

	m_sShare.Empty();

	UpdateData(FALSE);
	}

void CURLDemoDlg::OnCombineURL() 
	{
	if (!UpdateData(TRUE))
		return;

	COXURL URL;
	URL.Protocol() = m_sProtocol;
	URL.Port() = m_nPort;
	URL.UNC().Server() = m_sServer;
	URL.UNC().Share() = m_sShare;
	URL.UNC().Directory() = m_sDirectory;
	URL.UNC().File() = m_sFile;

	// Get the result
	m_sURL_UNC = URL;

	// Get the input parameters again 
	m_sProtocol = URL.Protocol();
	m_nPort = URL.Port();
	m_sServer = URL.UNC().Server();
	m_sShare = URL.UNC().Share();
	m_sDirectory = URL.UNC().Directory();
	m_sFile = URL.UNC().File();
	m_sBaseName = URL.UNC().Base();
	m_sExtension = URL.UNC().Extension();
	m_bURLPart = URL.UNC().URLPart();

	UpdateData(FALSE);
	}

void CURLDemoDlg::OnCombineUNC() 
	{
	if (!UpdateData(TRUE))
		return;

	COXUNC UNC;
	UNC.Server() = m_sServer;
	UNC.Share() = m_sShare;
	UNC.Directory() = m_sDirectory;
	UNC.File() = m_sFile;
	UNC.URLPart() = m_bURLPart;

	// Get the result

	// Visual C++ 5.0 reports error C2593: 'operator =' is ambiguous
	//  m_sURL_UNC = UNC;
	//  There are indeeds two ways to intepret the assignment
	//  One is to convert COXUNC to const COXUNC
	//  The other is to convert COXUNC to LPCTSTR
	// Appearently both are of equal importance in VC 5.0
	m_sURL_UNC =UNC;

	// Get the input parameters again 
	m_sServer = UNC.Server();
	m_sShare = UNC.Share();
	m_sDirectory = UNC.Directory();
	m_sFile = UNC.File();
	m_sBaseName = UNC.Base();
	m_sExtension = UNC.Extension();
	m_bURLPart = UNC.URLPart();

	m_sProtocol.Empty();
	m_nPort = 0;

	UpdateData(FALSE);
	}

void CURLDemoDlg::OnSplitUNC() 
	{
	if (!UpdateData(TRUE))
		return;

	COXUNC UNC;
	UNC = m_sURL_UNC;
	UNC.URLPart() = m_bURLPart;

	m_sServer = UNC.Server();
	m_sShare = UNC.Share();
	m_sDirectory = UNC.Directory();
	m_sFile = UNC.File();
	m_sBaseName = UNC.Base();
	m_sExtension = UNC.Extension();
	m_bURLPart = UNC.URLPart();

	// Get the input parameters again 
	// Visual C++ 5.0 reports error C2593: 'operator =' is ambiguous
	//  m_sURL_UNC = UNC;
	//  There are indeeds two ways to intepret the assignment
	//  One is to convert COXUNC to const COXUNC&
	//  The other is to convert COXUNC to LPCTSTR
	// Appearently both are of equal importance in VC 5.0
	m_sURL_UNC = UNC;

	m_sProtocol.Empty();
	m_nPort = 0;

	UpdateData(FALSE);
	}

void CURLDemoDlg::OnTest() 
	{

	INIT_CHECK();
	UNREFERENCED_PARAMETER(_v);
	UNREFERENCED_PARAMETER(_cv);

	RESET_NUMBER("CURLDemoDlg::OnTest : Iteration");
		{
		COXIteratorUNC iter;
		iter = _T("C:\\Temp\\*.*");
		iter.Start();
		while(!iter.IsEmpty())
			{
			TRACE1("- %s\n", (LPCTSTR)iter);
			iter++;
			}
		}

	SHOW_RESULT();
	}


void CURLDemoDlg::OnList() 
	{
	if (!UpdateData(TRUE))
		return;

	CUNCListDlg UNCListDlg;
	UNCListDlg.SetSearchUnc((LPCTSTR)m_sURL_UNC, m_bIncludeFiles, m_bIncludeDirs, 
		m_bRecursive, m_bDepthFirst);
	UNCListDlg.DoModal();
	}
