// TestBed.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestBed.h"
#include "Label.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp

BEGIN_MESSAGE_MAP(CTestBedApp, CWinApp)
	//{{AFX_MSG_MAP(CTestBedApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp construction

CTestBedApp::CTestBedApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestBedApp object

CTestBedApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp initialization

BOOL CTestBedApp::InitInstance()
{

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CAboutDlg dlg;
	dlg.DoModal();

	return FALSE;
}


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_LINK, m_link);
	DDX_Control(pDX, IDC_FLASH, m_flash);
	DDX_Control(pDX, IDC_MONTY, m_monty);
	DDX_Control(pDX, IDC_FSIZE, m_fsize);
	DDX_Control(pDX, IDC_SUNKEN, m_sunken);
	DDX_Control(pDX, IDC_BORDER, m_border);
	DDX_Control(pDX, IDC_BOLD, m_bold);
	DDX_Control(pDX, IDC_TULINE, m_uline);
	DDX_Control(pDX, IDC_TCOLOR, m_tcolor);
	DDX_Control(pDX, IDC_ITALICS, m_italics);
	DDX_Control(pDX, IDC_FNAME, m_fname);
	DDX_Control(pDX, IDC_BCOLOR, m_bcolor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp commands

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_fname.SetFontName("System");
	m_fsize.SetFontSize(14);
	m_uline.SetFontUnderline(TRUE);
	m_tcolor.SetTextColor(RGB(255,0,0));
	m_bcolor.SetBkColor(RGB(0,255,255));
	m_italics.SetFontItalic(TRUE);
	m_bold.SetFontBold(TRUE);
	m_border.SetBorder(TRUE);
	m_sunken.SetSunken(TRUE);

	m_monty
		.SetFontName("Arial")
		.SetFontSize(12)
		.SetTextColor(RGB(255,255,0))
		.SetFontUnderline(TRUE)
		.SetBkColor(RGB(0,0,0))
		.SetFontItalic(TRUE)
		.SetFontBold(TRUE)
		.SetBorder(TRUE)
		.SetSunken(TRUE);

	
	m_flash.SetBkColor(RGB(0,0,0));
	m_flash.SetTextColor(RGB(255,0,0));
	m_flash.SetFontBold(TRUE);
	m_flash.FlashBackground(TRUE);

	m_flash.SetTextColor(RGB(0,255,0));

	m_link.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



