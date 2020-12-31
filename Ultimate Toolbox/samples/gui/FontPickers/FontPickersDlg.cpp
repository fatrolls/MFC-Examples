// FontPickersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontPickers.h"
#include "FontPickersDlg.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontPickersDlg dialog

CFontPickersDlg::CFontPickersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontPickersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontPickersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontPickersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontPickersDlg)
	DDX_Control(pDX, IDC_SEPARATOR_COMBO, m_sepCombo);
	DDX_Control(pDX, IDC_SEPARATOR_BUTTON, m_sepButton);
	DDX_Control(pDX, IDC_COMBO_FONT_PICKER, m_cmbFontPicker);
	DDX_Control(pDX, IDC_BUTTON_FONT_PICKER, m_btnFontPicker);
	//}}AFX_DATA_MAP
	DDX_FontPickerFont(pDX, IDC_BUTTON_FONT_PICKER, &m_font);
}

BEGIN_MESSAGE_MAP(CFontPickersDlg, CDialog)
	//{{AFX_MSG_MAP(CFontPickersDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FONT_PICKER, OnButtonFontPicker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontPickersDlg message handlers

BOOL CFontPickersDlg::OnInitDialog()
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
	m_btnFontPicker.LoadBitmap(IDB_FONT,FALSE,RGB(192,192,192));
	m_btnFontPicker.SetBuddy(IDC_STATIC_FONT_PICKER);
	m_btnFontPicker.SetToolTip(TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFontPickersDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFontPickersDlg::OnPaint() 
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
HCURSOR CFontPickersDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontPickersDlg::OnButtonFontPicker() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_cmbFontPicker.SelectFont(&m_font);
}
