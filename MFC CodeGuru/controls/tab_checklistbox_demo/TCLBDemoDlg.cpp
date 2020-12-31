// TCLBDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCLBDemo.h"
#include "TCLBDemoDlg.h"

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
// CTCLBDemoDlg dialog

CTCLBDemoDlg::CTCLBDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCLBDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCLBDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pFont = new CFont;
}

void CTCLBDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCLBDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCLBDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTCLBDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, OnDefaultRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnEqualRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnDiffRadio)
	ON_BN_CLICKED(IDC_RADIO4, OnDiffFontRadio)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCLBDemoDlg message handlers

void CTCLBDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCLBDemoDlg::OnPaint() 
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
HCURSOR CTCLBDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CTCLBDemoDlg::OnInitDialog()
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
	m_pFont->CreateFont(-20, 0, 0, 0, FW_NORMAL, TRUE, FALSE, FALSE, 
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, FF_SWISS, "Arial" ); 

	m_ctrlCheckListBox.SubclassDlgItem(IDC_LIST1, this);
	int nTabStop = GetDialogUnitNumber() / 7; 
	LPINT lpTabStop = new int[2];
	lpTabStop[0] = nTabStop * 2;
	lpTabStop[1] = nTabStop * 5;
	m_ctrlCheckListBox.SetTabStops(2, lpTabStop);
	delete []lpTabStop;
	AddStringToList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTCLBDemoDlg::AddStringToList()
{
	CString str;
	str.Format(_T("%s\t%s\t%d"), "aaZAaa", "dddaaa", 1);
	m_ctrlCheckListBox.AddString(str);
	str.Format(_T("%s\t%s\t%s"), "AWWWA", "11", "asdAA");
	m_ctrlCheckListBox.AddString(str);
	str.Format(_T("%s\t%s\t%s"), "1Q", "aaa1", "?");
	m_ctrlCheckListBox.AddString(str);
	str.Format(_T("%s\t%s\t%s"), "1a", "1211", "asdf");
	m_ctrlCheckListBox.AddString(str);
	str.Format(_T("%s\t%s\t%s"), "AAQQ", "AWWG", "121");
	m_ctrlCheckListBox.AddString(str);
}

int CTCLBDemoDlg::GetDialogUnitNumber()
{
	CRect rectList;
	m_ctrlCheckListBox.GetWindowRect(&rectList);
	CFont* pFont = m_ctrlCheckListBox.GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	int nBaseUnit = lf.lfWidth;
	if(nBaseUnit == 0)
		nBaseUnit = LOWORD(GetDialogBaseUnits());
	return (rectList.Width() *4) / nBaseUnit;
}

void CTCLBDemoDlg::OnDefaultRadio() 
{
	// TODO: Add your control notification handler code here
	m_ctrlCheckListBox.ResetContent();
	m_ctrlCheckListBox.SetTabStops();  
	AddStringToList();
}

void CTCLBDemoDlg::OnEqualRadio() 
{
	// TODO: Add your control notification handler code here
	m_ctrlCheckListBox.ResetContent();
	int nTabStop = GetDialogUnitNumber() / 3; 
	m_ctrlCheckListBox.SetTabStops(nTabStop);
	AddStringToList();
}

void CTCLBDemoDlg::OnDiffRadio() 
{
	// TODO: Add your control notification handler code here
	m_ctrlCheckListBox.ResetContent();
	int nTabStop = GetDialogUnitNumber() / 6; 
	LPINT lpTabStop = new int[2];
	lpTabStop[0] = nTabStop * 4;
	lpTabStop[1] = nTabStop * 5;
	m_ctrlCheckListBox.SetTabStops(2, lpTabStop);
	AddStringToList();
	delete []lpTabStop;
}

void CTCLBDemoDlg::OnDiffFontRadio() 
{
	// TODO: Add your control notification handler code here
	m_ctrlCheckListBox.SetFont(m_pFont ); 	

	m_ctrlCheckListBox.ResetContent();
	int nTabStop = GetDialogUnitNumber() / 7; 
	LPINT lpTabStop = new int[2];
	lpTabStop[0] = nTabStop * 2;
	lpTabStop[1] = nTabStop * 5;
	m_ctrlCheckListBox.SetTabStops(2, lpTabStop);
	AddStringToList();
	delete []lpTabStop;
}

void CTCLBDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_pFont;
}

