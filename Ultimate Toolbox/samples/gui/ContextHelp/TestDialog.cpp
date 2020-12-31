// TestDialog.cpp : implementation file
//

#include "stdafx.h"
#include "contexthelp.h"
#include "TestDialog.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog

const DWORD CTestDialog::m_nHelpIDs[] = 
{
	IDC_BITMAP,		IDH_BITMAP,
	IDC_STATIC2,	IDH_STATIC2,
	IDC_STATIC1,	IDH_STATIC1,
	IDC_EDIT1,		IDH_EDIT1,
	IDC_BUTTON2,	IDH_BUTTON2,
	IDC_CHECK1,		IDH_CHECK1,
	IDC_SCROLLBAR1,	IDH_SCROLLBAR1,
	IDC_COMBO1,		IDH_COMBO1,
	0, 0
};

CTestDialog::CTestDialog(CWnd* pParent /*=NULL*/)
	: COXContextHelpDialog(CTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDialog)
	m_bCheck1 = FALSE;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CTestDialog::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDialog)
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scroll1);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_BUTTON2, m_btTwo);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDialog, COXContextHelpDialog)
	//{{AFX_MSG_MAP(CTestDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDialog message handlers

BOOL CTestDialog::AdjustToolTips() 
{
	//Set up the Tooltip
	BOOL rt = m_Tooltip.AddTool(this, _T("Test Dialog Box"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_btOk, _T("Save Changes"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_btCancel, _T("Cancel Changes"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_btTwo, _T("Another Button"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_combo1, _T("A ComboBox"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_scroll1, _T("A Scroll Bar"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_check1, _T("A Check Box to disable/enable Tooltips"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_edit1, _T("An Edit Field"));
	ASSERT(rt != 0) ;

	return rt;
	}

void CTestDialog::OnCheck1() 
{
	SetTooltipActive(!GetTooltipActive());
}

BOOL CTestDialog::OnInitDialog() 
{
	COXContextHelpDialog::OnInitDialog();
	
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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestDialog::OnPaint() 
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
HCURSOR CTestDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDialog::OnSysCommand(UINT nID, LPARAM lParam)
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


