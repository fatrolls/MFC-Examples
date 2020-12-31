// FormatRTFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FormatRTF.h"
#include "LRTFCtrl.h"
#include "FormatRTFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFDlg dialog

CFormatRTFDlg::CFormatRTFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFormatRTFDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormatRTFDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFormatRTFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormatRTFDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFormatRTFDlg, CDialog)
	//{{AFX_MSG_MAP(CFormatRTFDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PB_TOGGLE, OnPbToggle)
	ON_BN_CLICKED(IDC_PB_HIDE, OnPbHide)
	ON_BN_CLICKED(IDC_PB_SHOW, OnPbShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFDlg message handlers

BOOL CFormatRTFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Create RFTEdit
	CRect rectEdit(10, 10, 455, 175);
	m_edRTF.Create(ES_MULTILINE | ES_AUTOHSCROLL |WS_CHILD | 
					WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_LEFT
					| WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL,
					rectEdit, this, IDC_RICHEDIT1);
	
	// Set default char to Courier 10
	CHARFORMAT cfDefault;
	cfDefault.cbSize = sizeof(cfDefault);
	cfDefault.dwEffects = 0; 
	cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE;
	cfDefault.yHeight = -13;  
	strcpy(cfDefault.szFaceName, "Courier New"); 

	m_edRTF.SetDefaultCharFormat(cfDefault);
	
	m_edRTF.SetFocus();

	// fill with some sample code
	CString strTextToShow = ""
		"void CFormatRTFDlg::OnPbToggle()\r\n"
		"{\r\n"
		"	m_edRTF.ToggleFormatChars();\r\n"
		"}\r\n"
		"\r\n"
		"void CFormatRTFDlg::OnPbHide()\r\n"
		"{\r\n"
		"	m_edRTF.DrawFormatChars(FALSE);\r\n"
		"}\r\n";

	m_edRTF.SetWindowText(strTextToShow);

	m_edRTF.DrawFormatChars();

	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFormatRTFDlg::OnPaint() 
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

HCURSOR CFormatRTFDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFormatRTFDlg::OnPbToggle() 
{
	m_edRTF.ToggleFormatChars();
}

void CFormatRTFDlg::OnPbHide() 
{
	m_edRTF.DrawFormatChars(FALSE);
}

void CFormatRTFDlg::OnPbShow() 
{
	m_edRTF.DrawFormatChars();
}
