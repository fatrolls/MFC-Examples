// RCSeparatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RCSeparator.h"
#include "RCSeparatorDlg.h"
#include "SepDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRCSeparatorDlg dialog

CRCSeparatorDlg::CRCSeparatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRCSeparatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRCSeparatorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRCSeparatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRCSeparatorDlg)
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRCSeparatorDlg, CDialog)
	//{{AFX_MSG_MAP(CRCSeparatorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRCSeparatorDlg message handlers

BOOL CRCSeparatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_wndList.SetGridLines(TRUE);
	m_wndList.SetEditable(TRUE);
	m_wndList.SetColumnHeader("Student ID, 150");
	for (int i = 0; i < 14; i++)
	{
		int nIdx = m_wndList.InsertItem(INT_MAX, "");
		m_wndList.SetItemText(nIdx, 0, i);
		for (int j = 0; j < 1; j++)
		{
			if ((nIdx + 1) % 5 == 0)
			{
				m_wndList.SetItemText(nIdx, j, "Separator");
				m_wndList.SetItemBkColor(nIdx, -1, RGB(128, 128, 128), FALSE);
				m_wndList.SetItemTextColor(nIdx, -1, RGB(255, 255, 255), FALSE);
			}
			else
			{
				m_wndList.SetItemText(nIdx, j, (rand() % 90000) + 10000);
				COLORREF color = ::GetSysColor(COLOR_INFOBK);
				if (nIdx < 5)
					color = RGB(128, 192, 255);
				else if (nIdx < 10)
					color = RGB(128, 255, 128);
				m_wndList.SetItemBkColor(nIdx, -1, color, FALSE);
			}
		}
	}
	
	m_wndList.SetSortSeparator("Separator");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRCSeparatorDlg::OnPaint() 
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
HCURSOR CRCSeparatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRCSeparatorDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CSepDlg dlg(m_wndList.GetSortSeparator() == NULL, m_wndList.GetSortSeparator());
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.UseSep())
			m_wndList.SetSortSeparator(dlg.GetSep());
		else
			m_wndList.SetSortSeparator(NULL);
	}
}
