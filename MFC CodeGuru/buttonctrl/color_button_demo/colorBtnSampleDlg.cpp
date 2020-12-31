// colorBtnSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "colorBtnSample.h"
#include "colorBtnSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const COLORREF CLOUDBLUE = RGB(128, 184, 223);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF BLACK = RGB(1, 1, 1);
const COLORREF DKGRAY = RGB(128, 128, 128);
const COLORREF LTGRAY = RGB(192, 192, 192);
const COLORREF YELLOW = RGB(255, 255, 0);
const COLORREF DKYELLOW = RGB(128, 128, 0);
const COLORREF RED = RGB(255, 0, 0);
const COLORREF DKRED = RGB(128, 0, 0);
const COLORREF BLUE = RGB(0, 0, 255);
const COLORREF DKBLUE = RGB(0, 0, 128);
const COLORREF CYAN = RGB(0, 255, 255);
const COLORREF DKCYAN = RGB(0, 128, 128);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF DKGREEN = RGB(0, 128, 0);
const COLORREF MAGENTA = RGB(255, 0, 255);
const COLORREF DKMAGENTA = RGB(128, 0, 128);




/////////////////////////////////////////////////////////////////////////////
// CColorBtnSampleDlg dialog

CColorBtnSampleDlg::CColorBtnSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorBtnSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorBtnSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorBtnSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBtnSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorBtnSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CColorBtnSampleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorBtnSampleDlg message handlers

BOOL CColorBtnSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	OnCheck2();
/*
	VERIFY(m_btnOK.Attach(IDOK, this, CLOUDBLUE, DKBLUE, DKGRAY, 1));
	VERIFY(m_btnCancel.Attach(IDCANCEL, this, CLOUDBLUE, DKBLUE, DKGRAY, 1));
	VERIFY(m_btnUp.Attach(IDC_BUTTON1, this, CLOUDBLUE, DKBLUE, DKGRAY, 1));
	VERIFY(m_btnDown.Attach(IDC_BUTTON2, this, CLOUDBLUE, DKBLUE, DKGRAY, 1));
	VERIFY(m_btnDelete.Attach(IDC_BUTTON3, this, CLOUDBLUE, DKBLUE, DKGRAY, 1));
	VERIFY(m_btnAdd.Attach(IDC_BUTTON4, this, CLOUDBLUE, DKBLUE, DKGRAY, 1));
	SetWindowText("colorBtn Sample - Bevel=1");
*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorBtnSampleDlg::OnPaint() 
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

HCURSOR CColorBtnSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CColorBtnSampleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
  	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX) {
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(CLOUDBLUE); 
     	return (HBRUSH) B;
  	} 

	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CColorBtnSampleDlg::OnCheck1() 
{
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);	
}

void CColorBtnSampleDlg::OnCheck2() 
{
	VERIFY(m_btnOK.Attach(IDOK, this, CYAN, BLUE, DKCYAN));
	VERIFY(m_btnCancel.Attach(IDCANCEL, this, BLUE, WHITE, DKBLUE));
	VERIFY(m_btnUp.Attach(IDC_BUTTON1, this, RED, WHITE, DKRED)); 
	VERIFY(m_btnDown.Attach(IDC_BUTTON2, this, GREEN, BLUE, DKYELLOW));
	VERIFY(m_btnDelete.Attach(IDC_BUTTON3, this, YELLOW, BLUE, GREEN));
	VERIFY(m_btnAdd.Attach(IDC_BUTTON4, this, MAGENTA, WHITE, DKMAGENTA));
}
