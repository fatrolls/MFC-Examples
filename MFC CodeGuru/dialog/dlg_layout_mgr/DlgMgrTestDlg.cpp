// DlgMgrTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgMgrTest.h"
#include "DlgMgrTestDlg.h"
#include "Dialog2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrTestDlg dialog

IMPLEMENT_LAYOUT(CDlgMgrTestDlg);

CDlgMgrTestDlg::CDlgMgrTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogMgr(CDlgMgrTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMgrTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgMgrTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogMgr::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMgrTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMgrTestDlg, CDialogMgr)
	//{{AFX_MSG_MAP(CDlgMgrTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrTestDlg message handlers

BOOL CDlgMgrTestDlg::OnInitDialog()
{
	CDialogMgr::OnInitDialog();

	// Load last position from regitry
	Load("MyDialog");

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// definieren the Layout
	CPane*	pane2 = new CPane(CPane::HORIZONTAL);
	pane2->addItem( new CPaneItem( NULL, CPaneBase::GREEDY));
	pane2->addItem( new CPaneItem( IDOK, this, CPaneBase::NORESIZE));
	pane2->addItem( new CPaneItem( IDCANCEL, this, CPaneBase::NORESIZE));

	m_pRootPane = new CPane(CPane::VERTICAL);
	m_pRootPane->addItem( new CPaneItem( IDC_STATIC_1, this, CPaneBase::ABSOLUTE_VERT));
	m_pRootPane->addItem( new CPaneItem( IDC_EDIT1, this, CPaneBase::ABSOLUTE_VERT));
	m_pRootPane->addItem( new CPaneItem( IDC_STATIC_2, this, CPaneBase::ABSOLUTE_VERT));
	m_pRootPane->addItem( new CPaneItem( IDC_LIST1, this));
	m_pRootPane->addItem( pane2, CPaneBase::ABSOLUTE_VERT );


	UpdateLayout();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgMgrTestDlg::OnPaint() 
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
		CDialogMgr::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgMgrTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CDlgMgrTestDlg::DestroyWindow() 
{
	Save("MyDialog");	
	return CDialogMgr::DestroyWindow();
}

void CDlgMgrTestDlg::OnOK() 
{
	Dialog2 dlg;
	dlg.DoModal();

	CDialogMgr::OnOK();
}
