// MultiComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiCombo.h"
#include "MultiComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiComboDlg dialog

CMultiComboDlg::CMultiComboDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiComboDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiComboDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiComboDlg)
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultiComboDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiComboDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDOK(IDC_COMBO3, OnSelendokCombo3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiComboDlg message handlers

BOOL CMultiComboDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitJCombo();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiComboDlg::OnPaint() 
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
HCURSOR CMultiComboDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMultiComboDlg::InitJCombo()
{
 	CString buf;

	m_combo1.ResetContent();
	m_combo2.ResetContent();
	m_combo3.ResetContent();



	m_combo1.FormatList(1,DT_LEFT,FALSE,NORMAL);
	m_combo2.FormatList(3,DT_LEFT,FALSE,EDGE);
	m_combo3.FormatList(3,DT_LEFT,TRUE,EDGE);

	for (int j = 0;j<=10;j++){

		buf.Format("%d",j);
		m_combo1.AddItem(_T("TEST"),0,j);
		if (j==2)
		m_combo1.AddItem(_T("THIS ITEM WILL SHOW TOOLTIP"),0,j);


		m_combo2.AddItem(buf,0,j);
		m_combo2.AddItem(_T("Column2"),1,j);
		if ((j==2)|| (j==5))
			m_combo2.AddItem(_T("012345678901234567890123456789"),2,j);
		else
			m_combo2.AddItem(_T("Last Column.."),2,j);

		m_combo3.AddItem(buf,0,j);
		m_combo3.AddItem(_T("Column2"),1,j);
		if ((j==2)|| (j==5))
			m_combo3.AddItem(_T("0123456789012345678901234567890123456789"),2,j);
		else
			m_combo3.AddItem(_T("Last Column.."),2,j);


	}

	m_combo1.SetCurSel(0);
	m_combo2.SetCurSel(0);
	m_combo3.SetCurSel(0); 

}

void CMultiComboDlg::OnSelendokCombo3() 
{
	//The check box will get checked on the Current Selection
	// i.e.  SetCurSel()  or SelectList()
	//m_combo3.SelectList(m_combo3.GetCurSel());
	m_combo3.SetCurSel(	m_combo3.GetCurSel());

}
