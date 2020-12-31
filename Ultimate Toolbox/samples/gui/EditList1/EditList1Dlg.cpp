// EditList1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "EditList1.h"
#include "EditList1Dlg.h"
#include <afxpriv.h>	// for WM_KICKIDLE


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditList1Dlg dialog
CEditList1Dlg::CEditList1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditList1Dlg::IDD, pParent),
	m_EditListCtrl(COXEditList::TBPHorizontalTopLeft, 
		FALSE /* bAllowDuplicates */, TRUE /* bOrderedList */)
{
	//{{AFX_DATA_INIT(CEditList1Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditList1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditList1Dlg)
	DDX_Control(pDX, IDC_CONTEXT_LIST, m_EditListCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditList1Dlg, CDialog)
	//{{AFX_MSG_MAP(CEditList1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditList1Dlg message handlers

BOOL CEditList1Dlg::OnInitDialog()
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

	VERIFY(m_ContextImageSmall.Create(IDB_IMAGELIST,16,0,RGB(255,0,255)));
	m_ContextImageSmall.SetBkColor(GetSysColor(COLOR_WINDOW));
	// ... Associate the image lists with the context list
	m_EditListCtrl.SetImageList(&m_ContextImageSmall, LVSIL_SMALL);

	// Add the necessary rows
	TCHAR sBuffer[20];
	// Insert the item
	for (int j = 0; j < 10 ; j++)
		{
		wsprintf(sBuffer, _T("ListItem %i"), j + 1);
			m_EditListCtrl.InsertItem(j, sBuffer, 1);
		}
	
	m_EditListCtrl.SetFlatToolbar( TRUE );
	// ... Set focus to the control
	m_EditListCtrl.SetFocus();


	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CEditList1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditList1Dlg::OnPaint() 
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
HCURSOR CEditList1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CEditList1Dlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ((wParam == IDOK) && (::GetFocus() == m_EditListCtrl.m_hWnd))
		{
		// User pressed ENTER while the list of contexts has focus
		// Normally this would activate the default button (IDOK)
		// We change this into editing the current item of the context list
		ASSERT(CWnd::GetFocus() == &m_EditListCtrl);
		m_EditListCtrl.EditNewItem();

		// We processed the message ourselves and will not pass on to base class implementation
		return TRUE;
		}
		
	return CDialog::OnCommand(wParam, lParam);
}

LRESULT CEditList1Dlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
	{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	ASSERT(wParam == MSGF_DIALOGBOX);
	BOOL bContinueIdle = TRUE;

	// Update our controls
//	ConditionalDisable();

	// Update the context list
	m_EditListCtrl.OnIdle();

	return bContinueIdle;
	}

void CEditList1Dlg::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}
