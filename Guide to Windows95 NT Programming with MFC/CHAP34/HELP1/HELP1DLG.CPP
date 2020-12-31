///////////////////////////////////////////////////////////////////
//  Header  : HELP1DLG.CPP
//
//  Purpose : Implementation of the main dialog windows for the 
//            HELP1 program. Shows how to use WinHelp Help files 
//            in an MFC program.
//            
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-31-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "help1.h"
#include "help1dlg.h"
#include "resource.h"

///////////////////////////////////////////////////////////////////
// CAboutDlg dialog
///////////////////////////////////////////////////////////////////

class CAboutDlg : public CDialog
{
// Construction
public:
   CAboutDlg(CWnd* pParent = NULL);   // standard constructor
   enum { IDD = IDD_ABOUTBOX };
};

// Inline constructor
inline CAboutDlg::CAboutDlg(CWnd* pParent) : 
   CDialog(CAboutDlg::IDD, pParent) { }

///////////////////////////////////////////////////////////////////
//  CHelp1Dlg dialog
///////////////////////////////////////////////////////////////////

// Message map for CHelp1Dlg
BEGIN_MESSAGE_MAP(CHelp1Dlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTNHELP, OnBtnHelpClick)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CHelp1Dlg dialog
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CHelp1Dlg::CHelp1Dlg() - constructor

CHelp1Dlg::CHelp1Dlg(CWnd* pParent) : CDialog(CHelp1Dlg::IDD, pParent)
{
	// Load an icon
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

///////////////////////////////////////////////////////////////////
// CHelp1Dlg::DoDataExchange()

void CHelp1Dlg::DoDataExchange(CDataExchange* pDX)
{ 
   CDialog::DoDataExchange(pDX); 
}

///////////////////////////////////////////////////////////////////
// CHelp1Dlg::OnBtnHelpClick()

void CHelp1Dlg::OnBtnHelpClick()
{
   // Show the Help Contents dialog
   AfxGetApp()->WinHelp(0L, HELP_FINDER);
}

///////////////////////////////////////////////////////////////////
// CHelp1Dlg::OnInitDialog()

BOOL CHelp1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add the "About..." menu item to the System menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// get a copy of the System menu
   CMenu* pSysMenu = GetSystemMenu(FALSE);
	
   CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  
	SetIcon(m_hIcon, TRUE);			// Set big icon   (32 x 32)
	SetIcon(m_hIcon, FALSE);		// Set small icon (16 x 16)
	
	return TRUE;  
}

///////////////////////////////////////////////////////////////////
// CHelp1Dlg::OnSysCommand()

void CHelp1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

///////////////////////////////////////////////////////////////////
// CHelp1Dlg::OnDestroy()

void CHelp1Dlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);  // Kill WinHelp
	CDialog::OnDestroy();
}
                              
///////////////////////////////////////////////////////////////////
