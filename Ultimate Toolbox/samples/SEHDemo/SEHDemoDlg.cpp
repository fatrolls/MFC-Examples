// SEHDemoDlg.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================


#include "stdafx.h"
#include "utsampleabout.h"
#include "SEHDemo.h"
#include "SEHDemoDlg.h"
#include "OXSEH.h"
#include <eh.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSEHDemoDlg dialog

CSEHDemoDlg::CSEHDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSEHDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSEHDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSEHDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSEHDemoDlg)
	DDX_Control(pDX, IDC_TRAP_FL, m_wndFPTrap);
	DDX_Control(pDX, IDC_TRAP, m_wndTrap);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSEHDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSEHDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ACCESS_VIOLATION, OnAccessViolation)
	ON_BN_CLICKED(IDC_TRAP, OnTrap)
	ON_BN_CLICKED(IDC_ZERO_FLOAT, OnZeroFloat)
	ON_BN_CLICKED(IDC_ZERO_INTEGER, OnZeroInteger)
	ON_BN_CLICKED(IDC_TRAP_FL, OnTrapFl)
	ON_BN_CLICKED(IDC_BREAKPOINT, OnBreakpoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSEHDemoDlg message handlers

BOOL CSEHDemoDlg::OnInitDialog()
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

void CSEHDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSEHDemoDlg::OnPaint() 
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
HCURSOR CSEHDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSEHDemoDlg::OnAccessViolation() 
	{
 	TRY
 		{
		// Use invalid virtual memory address
		int* pa = (int*)0x123;
		*pa = 0;
		}
	CATCH(COXSEHMemoryException, px)
		{
		if (px->GetCause() == EXCEPTION_ACCESS_VIOLATION)
			if (px->IsInfoAvailable())
				{
				CString sMsg;
				sMsg.Format(_T("Access violation trapped with TRY, CATCH while trying to %s at address 0x%8.8lX"),
					!px->GetReadWriteFlag() ? _T("READ") : _T("WRITE"), px->GetAddress());
				AfxMessageBox(sMsg);
				}
			else
				AfxMessageBox(_T("Access violation trapped with TRY, CATCH"));
		else
			AfxMessageBox(_T("Unknown memory exception trapped with TRY, CATCH"));
		}
	END_CATCH
	}

void CSEHDemoDlg::OnZeroFloat() 
	{
 	TRY
 		{
		// Divide by zero
		double x = 1.0;
		double a = 0.0;
		x = x / a;
		}
	CATCH(COXSEHMathException, px)
		{
		if (px->GetCause() == EXCEPTION_FLT_DIVIDE_BY_ZERO)
			AfxMessageBox(_T("Float divide by zero trapped with TRY, CATCH"));
		else
			AfxMessageBox(_T("Unknown math exception trapped with TRY, CATCH"));
		}
	END_CATCH
	}

void CSEHDemoDlg::OnZeroInteger() 
	{
 	TRY
 		{
		// Divide by zero
		int x = 1;
		int a = 0;
		x = x / a;
		}
	CATCH(COXSEHMathException, px)
		{
		if (px->GetCause() == EXCEPTION_INT_DIVIDE_BY_ZERO)
			AfxMessageBox(_T("Integer divide by zero trapped with TRY, CATCH"));
		else
			AfxMessageBox(_T("Unknown math exception trapped with TRY, CATCH"));
		}
	END_CATCH
	}

void CSEHDemoDlg::OnBreakpoint() 
	{
	TRY
 		{
		// Debug break : This can only be catched when not running in debugger
		DebugBreak();
		}
	CATCH(COXSEHSpecialException, px)
		{
		if (px->GetCause() == EXCEPTION_BREAKPOINT)
			AfxMessageBox(_T("Breakpoint trapped with TRY, CATCH"));
		else
			AfxMessageBox(_T("Unknown special exception trapped with TRY, CATCH"));
		}
	END_CATCH
	}

void CSEHDemoDlg::OnTrap() 
	{
	if (m_wndTrap.GetCheck() & 0x0001)
		if (m_wndFPTrap.GetCheck() & 0x0001)
			COXSEHException::EnableSEHTrapping(TRUE);
		else
			COXSEHException::EnableSEHTrapping(FALSE);
	else
		COXSEHException::DisableSEHTrapping();
	}

void CSEHDemoDlg::OnTrapFl() 
	{
	// If already trapping : turn of temporary so we can change the FP parameter
	if (COXSEHException::IsSEHTrappingEnabled())
		COXSEHException::DisableSEHTrapping();
	// (Re-)enable SEH trapping
	if (m_wndFPTrap.GetCheck() & 0x0001)
		COXSEHException::EnableSEHTrapping(TRUE);
	else
		COXSEHException::EnableSEHTrapping(FALSE);
	// Make sure SEH is checked
	m_wndTrap.SetCheck(0x0001);
	}



