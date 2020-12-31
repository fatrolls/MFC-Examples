// HistoryComboDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "HistoryComboDemo.h"
#include "HistoryComboDemoDlg.h"
#include <afxpriv.h>	// for WM_KICKIDLE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryComboDemoDlg dialog

CHistoryComboDemoDlg::CHistoryComboDemoDlg(CWnd* pParent /*=NULL*/)
	: 
	CDialog(CHistoryComboDemoDlg::IDD, pParent),
	m_wndHistoryCombo(/* COXHistoryCombo::TBPHorizontalRightCenter, 
		FALSE, MAKEINTRESOURCE(IDR_HISTORY_COMBO_TEST) */)
	{
	//{{AFX_DATA_INIT(CHistoryComboDemoDlg)
	m_nType = -1;
	m_bSmallGap = FALSE;
	m_bButton1 = FALSE;
	m_bButton2 = FALSE;
	m_bButton3 = FALSE;
	m_bButton4 = FALSE;
	m_bButton5 = FALSE;
	m_bButton6 = FALSE;
	m_nMaxCount = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CHistoryComboDemoDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistoryComboDemoDlg)
	DDX_Control(pDX, IDC_MAX_COUNT_SPIN, m_wndMaxCountSpin);
	DDX_Control(pDX, IDC_HISTORY_COMBO, m_wndHistoryCombo);
	DDX_Radio(pDX, IDC_SIMPLE, m_nType);
	DDX_Check(pDX, IDC_USE_GAP, m_bSmallGap);
	DDX_Check(pDX, IDC_BUTTON_1, m_bButton1);
	DDX_Check(pDX, IDC_BUTTON_2, m_bButton2);
	DDX_Check(pDX, IDC_BUTTON_3, m_bButton3);
	DDX_Check(pDX, IDC_BUTTON_4, m_bButton4);
	DDX_Check(pDX, IDC_BUTTON_5, m_bButton5);
	DDX_Check(pDX, IDC_BUTTON_6, m_bButton6);
	DDX_Text(pDX, IDC_MAX_COUNT, m_nMaxCount);
	DDV_MinMaxInt(pDX, m_nMaxCount, -1, 100);
	//}}AFX_DATA_MAP
	}

BEGIN_MESSAGE_MAP(CHistoryComboDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CHistoryComboDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MOVE_TOOLBAR, OnMoveToolbar)
	ON_BN_CLICKED(IDC_DROP_LIST, OnStyleChange)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	ON_BN_CLICKED(IDC_DROPDOWN, OnStyleChange)
	ON_BN_CLICKED(IDC_SIMPLE, OnStyleChange)
	ON_EN_CHANGE(IDC_MAX_COUNT, OnChangeMaxCount)
	ON_COMMAND(ID_HISTORY_TEST, OnExtra)
	ON_UPDATE_COMMAND_UI(ID_HISTORY_TEST, OnUpdateExtra)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryComboDemoDlg message handlers

BOOL CHistoryComboDemoDlg::OnInitDialog()
	{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
		{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	// Reflect the current type of combo
	DWORD nComboStyle = m_wndHistoryCombo.GetStyle();
	if ((nComboStyle & CBS_SIMPLE) == CBS_SIMPLE)
		m_nType = 0;
	else if ((nComboStyle & CBS_DROPDOWN) == CBS_DROPDOWN)
		m_nType = 1;
	else if ((nComboStyle & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
		m_nType = 2;
	else
		{
		m_nType = -1;
		TRACE0("CHistoryComboDemoDlg::OnInitDialog : History combo has unknown style\n");
		}

	// Initialize the visibility
	m_bButton1 = m_wndHistoryCombo.IsButtonShown(0);
	m_bButton2 = m_wndHistoryCombo.IsButtonShown(1);
	m_bButton3 = m_wndHistoryCombo.IsButtonShown(2);
	m_bButton4 = m_wndHistoryCombo.IsButtonShown(3);
	m_bButton5 = m_wndHistoryCombo.IsButtonShown(4);
	m_bButton6 = m_wndHistoryCombo.IsButtonShown(5);

	// Initialize the max list count
	m_nMaxCount = m_wndHistoryCombo.GetMaxHistoryCount();
	m_wndMaxCountSpin.SetRange(-1, 100);

	// Use auto persistence
	m_wndHistoryCombo.SetAutoPersistent(_T("History 1"));

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
	}

void CHistoryComboDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINRFAME,ID_DESCRIPTION_FILE);
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

void CHistoryComboDemoDlg::OnPaint() 
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
HCURSOR CHistoryComboDemoDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon;
	}

void CHistoryComboDemoDlg::OnMoveToolbar() 
	{
	if (!UpdateData(TRUE))
		return;

	COXHistoryCombo::EToolbarPosition eToolbarPosition = m_wndHistoryCombo.GetToolbarPosition();
	eToolbarPosition = (COXHistoryCombo::EToolbarPosition)((int)eToolbarPosition + 1);
	if (COXHistoryCombo::TBP_LAST < eToolbarPosition)
		eToolbarPosition = COXHistoryCombo::TBP_FIRST;
	m_wndHistoryCombo.PositionToolbar(eToolbarPosition, m_bSmallGap);
	}

void CHistoryComboDemoDlg::OnStyleChange() 
	{
	if (!UpdateData(TRUE))
		return;

	DWORD nMask = CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST;
	DWORD nNewComboStyle = 0;
	switch(m_nType)
		{
		case 0:
			nNewComboStyle = CBS_SIMPLE;
			break;
		case 1:
			nNewComboStyle = CBS_DROPDOWN;
			break;
		case 2:
			nNewComboStyle = CBS_DROPDOWNLIST;
			break;
		default:
			TRACE1("CHistoryComboDemoDlg::OnStyleChange : Unexpected case in switch : Unknown style\n",
				m_nType);
			ASSERT(FALSE);
			break;
		}

	DWORD nFullOldComboStyle = m_wndHistoryCombo.GetStyle();
	DWORD nOldComboStyle = m_wndHistoryCombo.GetStyle() & nMask;
	if (nOldComboStyle != nNewComboStyle)
		{
		// The type changed, but changing the window style is not sufficient,
		// we have to recreate the window

		// Get the state of the old window
		CRect windowRect;
		m_wndHistoryCombo.GetWindowRect(windowRect);
		ScreenToClient(windowRect);
		if ( nOldComboStyle != CBS_SIMPLE )
			// ... Use a height of 2.8 times the height of the edit (or static) control
			windowRect.bottom = windowRect.top + (windowRect.Height() * 14) / 4;

		// Destroy old window and create new one
		m_wndHistoryCombo.DestroyWindow();
		m_wndHistoryCombo.Create((nFullOldComboStyle & ~nMask) | nNewComboStyle | WS_VSCROLL, 
			windowRect, this, IDC_HISTORY_COMBO);

		// Restore the old state
		m_wndHistoryCombo.SetFont(GetFont());
		// ... The contents is already restored during OnCreate
		//     because we use SetAutoPersistent
		}
	}

LRESULT CHistoryComboDemoDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
	{
	UNUSED(wParam);
	UNREFERENCED_PARAMETER(lParam);

	ASSERT_VALID(this);
	ASSERT(wParam == MSGF_DIALOGBOX);

	BOOL bContinueIdle = TRUE;

	// Pass on to the history combo
	m_wndHistoryCombo.OnIdle();

	return bContinueIdle;
	}


void CHistoryComboDemoDlg::OnSave() 
	{
	m_wndHistoryCombo.SaveContents(_T("History 1"));
	}

void CHistoryComboDemoDlg::OnShow() 
	{
	if (!UpdateData(TRUE))
		return;
	m_wndHistoryCombo.ShowButton(0, m_bButton1);
	m_wndHistoryCombo.ShowButton(1, m_bButton2);
	m_wndHistoryCombo.ShowButton(2, m_bButton3);
	m_wndHistoryCombo.ShowButton(3, m_bButton4);
	m_wndHistoryCombo.ShowButton(4, m_bButton5);
	m_wndHistoryCombo.ShowButton(5, m_bButton6);

	m_wndHistoryCombo.RefreshToolbar();
	}

void CHistoryComboDemoDlg::OnRestore() 
	{
	m_wndHistoryCombo.RestoreContents(_T("History 1"));
	}

void CHistoryComboDemoDlg::OnChangeMaxCount() 
	{
	if (m_wndHistoryCombo.m_hWnd != NULL)
		{
		if (!UpdateData(TRUE))
			return;
		m_wndHistoryCombo.SetMaxHistoryCount(m_nMaxCount);
		}
	}

void CHistoryComboDemoDlg::OnExtra() 
	{
	m_wndHistoryCombo.ResetContent();
	}

void CHistoryComboDemoDlg::OnUpdateExtra(CCmdUI* pCmdUI) 
	{
	pCmdUI->Enable(0 < m_wndHistoryCombo.GetCount());
	}
