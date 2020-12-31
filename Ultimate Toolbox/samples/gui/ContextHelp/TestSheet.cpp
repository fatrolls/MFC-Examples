// TestSheet.cpp : implementation file
//

#include "stdafx.h"
#include "ContextHelp.h"
#include "TestSheet.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestSheet dialog

const DWORD CTestSheet::m_nHelpIDs[] = 
{
	0, 0
};

CTestSheet::CTestSheet(UINT nIDCaption, CWnd *pParentWnd, 
	UINT iSelectPage) : COXContextHelpPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTestSheet::CTestSheet(LPCTSTR pszCaption, CWnd *pParentWnd, 
	UINT iSelectPage) : COXContextHelpPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSheet::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertySheet::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSheet)
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDOK, m_btOk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestSheet, COXContextHelpPropertySheet)
	//{{AFX_MSG_MAP(CTestSheet)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSheet message handlers

BOOL CTestSheet::AdjustToolTips() 
{
	//Set up the Tooltip
	BOOL rt = m_Tooltip.AddTool(this, _T("COXContextHelpPropertySheet"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_btOk, _T("Save Changes"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_btCancel, _T("Cancel Changes"));
	ASSERT(rt != 0) ;

	return rt;
}

BOOL CTestSheet::OnInitDialog()
{
	CPropertySheet::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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
	// TODO: Add extra initialization here
	static CFont font;
	if (font.m_hObject != NULL)
		font.CreatePointFont(-16,_T("Times New Roman"));
	SetFont(&font);
	

	return TRUE; 
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSheet::OnPaint() 
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
		CPropertySheet::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSheet::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestSheet::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		COXContextHelpPropertySheet::OnSysCommand(nID, lParam);
	}
}

