// ReportCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportCtrlDemo.h"
#include "ReportCtrlDemoDlg.h"
#include "popupmenu.h"
#include "statesdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// menu indices
enum { MNU_SELECTION = 0, MNU_CHECKBOX, MNU_POSITION };
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
// CReportCtrlDemoDlg dialog

CReportCtrlDemoDlg::CReportCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportCtrlDemoDlg)
	m_bGridLines = TRUE;
	m_bEditable = TRUE;
	m_bSortable = TRUE;
	m_nChkStyle = RC_CHKBOX_NORMAL;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_pil = NULL;
}

void CReportCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportCtrlDemoDlg)
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	DDX_Check(pDX, IDC_GRIDLINES, m_bGridLines);
	DDX_Check(pDX, IDC_ALLOWEDIT, m_bEditable);
	DDX_Check(pDX, IDC_ALLOWSORT, m_bSortable);
	DDX_Radio(pDX, IDC_CHK_NONE, m_nChkStyle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CReportCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ALLOWEDIT, OnAllowedit)
	ON_COMMAND(ID_SELECTION_ALL, OnSelectionAll)
	ON_COMMAND(ID_SELECTION_INVERT, OnSelectionInvert)
	ON_COMMAND(ID_SELECTION_UNALL, OnSelectionUnall)
	ON_COMMAND(ID_CHECKBOX_ALL, OnCheckboxAll)
	ON_COMMAND(ID_CHECKBOX_INVERT, OnCheckboxInvert)
	ON_COMMAND(ID_CHECKBOX_UNALL, OnCheckboxUnall)
	ON_UPDATE_COMMAND_UI(ID_CHECKBOX_ALL, OnUpdateCheckboxAll)
	ON_UPDATE_COMMAND_UI(ID_CHECKBOX_INVERT, OnUpdateCheckboxInvert)
	ON_COMMAND(ID_POSITION_UP, OnPositionUp)
	ON_UPDATE_COMMAND_UI(ID_POSITION_UP, OnUpdatePositionUp)
	ON_COMMAND(ID_POSITION_DOWN, OnPositionDown)
	ON_UPDATE_COMMAND_UI(ID_POSITION_DOWN, OnUpdatePositionDown)
	ON_COMMAND(ID_POSITION_TOP, OnPositionTop)
	ON_UPDATE_COMMAND_UI(ID_POSITION_TOP, OnUpdatePositionTop)
	ON_COMMAND(ID_POSITION_BOTTOM, OnPositionBottom)
	ON_UPDATE_COMMAND_UI(ID_POSITION_BOTTOM, OnUpdatePositionBottom)
	ON_COMMAND(ID_POSITION_SWAP, OnPositionSwap)
	ON_UPDATE_COMMAND_UI(ID_POSITION_SWAP, OnUpdatePositionSwap)
	ON_BN_CLICKED(IDC_GRIDLINES, OnGridlines)
	ON_BN_CLICKED(IDC_ALLOWSORT, OnAllowsort)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_POSITION, OnPosition)
	ON_BN_CLICKED(IDC_CHK_NONE, OnChkStyle)
	ON_BN_CLICKED(IDC_CHK_NORMAL, OnChkStyle)
	ON_BN_CLICKED(IDC_CHK_SINGLE, OnChkStyle)
	ON_BN_CLICKED(IDC_CHK_DISABLED, OnChkStyle)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ON_CHKBOX, OnCheckBox)
	ON_MESSAGE(WM_ITEM_SORTED, OnItemSorted)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoDlg message handlers

LRESULT CReportCtrlDemoDlg::OnCheckBox(WPARAM wParam, LPARAM lParam)
{
	// Called when the user clicked on a checkbox in the list control
	int nItem = (int)wParam; // Item index
	UINT nMouseEvent  = (UINT)lParam; // Mouse event, usually being WM_LBUTTONDOWN or WM_RBUTTONDOWN

	// TODO: Add your message handler code here
	
	return (LRESULT)0;
}

LRESULT CReportCtrlDemoDlg::OnItemSorted(WPARAM wParam, LPARAM lParam)
{
	// Called when a column of list items have been sorted
	int nColumn = (int)wParam;
	BOOL bAscending = (BOOL)lParam;

	// TODO: Add your message handler code here
	
	return (LRESULT)0;
}

BOOL CReportCtrlDemoDlg::OnInitDialog()
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
	srand((unsigned)time(NULL));

	m_wndList.SetColumnHeader(_T("Student ID, 100; Enroll Date, 150; Score, 80, 2"));

	for (int i = 0; i < 10; i++)
	{
		const int IDX = m_wndList.InsertItem(0, _T(""));
		m_wndList.SetItemText(IDX, 0, rand() % 3000);
		m_wndList.SetItemText(IDX, 1, GenRandDate());
		m_wndList.SetItemText(IDX, 2, (rand() % 51) + 50);
		
		for (int j = 0; j < 2; j++)
			m_wndList.SetItemImage(IDX, j, rand() % 5); // subitem images
		
	}

	m_wndList.SetImageList(IDB_BITMAP1);
	m_wndList.SetHeaderImageList(IDB_BITMAP2);
	m_wndList.SetHeaderImage(0, 0);
	m_wndList.SetHeaderImage(1, 2, FALSE);
	m_wndList.SetHeaderImage(2, 1);
	m_wndList.SetGridLines(TRUE); // SHow grid lines
	m_wndList.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
	m_wndList.SetEditable(TRUE); // Allow sub-text edit
	m_wndList.SortItems(0, TRUE); // sort the 1st column, ascending
	m_bSortable = m_wndList.IsSortable();
	UpdateData(FALSE);
	GetDlgItem(IDC_ALLOWSORT)->EnableWindow(m_wndList.HasColumnHeader());

	// now play some colorful stuff
	
	// Set the 3rd column background color to yellow, text color to blue
	m_wndList.SetItemTextColor(-1, 2, RGB(0, 0, 0));
	m_wndList.SetItemBkColor(-1, 2, RGB(255, 255, 0));

	for (int n = 0; n < m_wndList.GetItemCount(); n++)
	{
		const int SCORE = _ttoi(m_wndList.GetItemText(n, 2)); // student score

		if (SCORE < 60)
		{
			m_wndList.SetItemBkColor(n, -1, ::GetSysColor(COLOR_INFOBK));
			m_wndList.SetItemTextColor(n, -1, RGB(255, 0, 0));
			
			m_wndList.SetItemBkColor(n, 2, RGB(255, 0, 0));
			m_wndList.SetItemTextColor(n, 2, RGB(255, 255, 255));
		}
		else if (SCORE > 90)
		{
			m_wndList.SetItemBkColor(n, -1, RGB(160, 255, 192));
			m_wndList.SetItemTextColor(n, -1, RGB(0, 0, 255));

			m_wndList.SetItemTextColor(n, 2, RGB(255, 255, 255));
			m_wndList.SetItemBkColor(n, 2, RGB(0, 160, 0));
		}
	}	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReportCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReportCtrlDemoDlg::OnPaint() 
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
HCURSOR CReportCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


CString CReportCtrlDemoDlg::GenRandStr()
{
	const CString LETTERS = _T("abcdefghijklm nopqrstuvwxy z0123456789");
	const int LEN = 16;

	CString str;
	for (int i = 0; i < LEN; i++)
	{
		str += LETTERS[rand() % LETTERS.GetLength()];
	}

	return str;
}

COleDateTime CReportCtrlDemoDlg::GenRandDate()
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span(rand() % 3650, rand() % 24, rand() % 60, rand() % 60);
	now -= span;
	return now;
}

void CReportCtrlDemoDlg::OnAllowedit() 
{
	// TODO: Add your control notification handler code here
	m_bEditable = !m_bEditable;
	m_wndList.SetEditable(m_bEditable);
}

void CReportCtrlDemoDlg::OnSelectionAll() 
{
	// TODO: Add your command handler code here	
	m_wndList.SetAllItemStates(GetStatesInput(), RC_ITEM_SELECTED);
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnSelectionInvert() 
{
	// TODO: Add your command handler code here
	m_wndList.InvertItems(RC_INVERT_SELECTION);
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnSelectionUnall() 
{
	// TODO: Add your command handler code here
	m_wndList.SetAllItemStates(GetStatesInput(), RC_ITEM_UNSELECTED);
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnCheckboxAll() 
{
	// TODO: Add your command handler code here
	m_wndList.SetAllItemStates(GetStatesInput(), RC_ITEM_CHECKED);
	m_wndList.SetFocus();	
}

void CReportCtrlDemoDlg::OnCheckboxInvert() 
{
	// TODO: Add your command handler code here
	m_wndList.InvertItems(RC_INVERT_CHECKMARK);
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnCheckboxUnall() 
{
	// TODO: Add your command handler code here
	m_wndList.SetAllItemStates(GetStatesInput(), RC_ITEM_UNCHECKED);
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnUpdateCheckboxAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetCheckboxStyle() != RC_CHKBOX_SINGLE);
}

void CReportCtrlDemoDlg::OnUpdateCheckboxInvert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetCheckboxStyle() != RC_CHKBOX_SINGLE);
}

void CReportCtrlDemoDlg::OnPositionUp() 
{
	// TODO: Add your command handler code here
	m_wndList.MoveUp(m_wndList.GetFirstItem(RC_ITEM_SELECTED));
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnUpdatePositionUp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetSelectedCount() == 1);
}

void CReportCtrlDemoDlg::OnPositionDown() 
{
	// TODO: Add your command handler code here
	m_wndList.MoveDown(m_wndList.GetFirstItem(RC_ITEM_SELECTED));
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnUpdatePositionDown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetSelectedCount() == 1);
}

void CReportCtrlDemoDlg::OnPositionTop() 
{
	// TODO: Add your command handler code here
	m_wndList.MoveToTop(m_wndList.GetFirstItem(RC_ITEM_SELECTED));
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnUpdatePositionTop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetSelectedCount() == 1);
}

void CReportCtrlDemoDlg::OnPositionBottom() 
{
	// TODO: Add your command handler code here
	m_wndList.MoveToBottom(m_wndList.GetFirstItem(RC_ITEM_SELECTED));
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnUpdatePositionBottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetSelectedCount() == 1);
}

void CReportCtrlDemoDlg::OnPositionSwap() 
{
	// TODO: Add your command handler code here
	int nIdx1 = m_wndList.GetFirstItem(RC_ITEM_SELECTED);
	int nIdx2 = m_wndList.GetFirstItem(RC_ITEM_SELECTED, nIdx1);
	m_wndList.SwapItems(nIdx1, nIdx2);
	m_wndList.SetFocus();
}

void CReportCtrlDemoDlg::OnUpdatePositionSwap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_wndList.GetSelectedCount() == 2);
}

void CReportCtrlDemoDlg::OnGridlines() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_wndList.SetGridLines(m_bGridLines);
}

BOOL CReportCtrlDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CReportCtrlDemoDlg::OnAllowsort() 
{
	// TODO: Add your control notification handler code here
	m_bSortable = !m_bSortable;
	m_wndList.SetSortable(m_bSortable);
}

void CReportCtrlDemoDlg::OnSelect() 
{
	// TODO: Add your control notification handler code here
	PopupMenu(IDR_MENU1, MNU_SELECTION, this);
}

void CReportCtrlDemoDlg::OnCheck() 
{
	// TODO: Add your control notification handler code here
	PopupMenu(IDR_MENU1, MNU_CHECKBOX, this);
}

void CReportCtrlDemoDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	m_wndList.DeleteAllItems(GetStatesInput());
}

void CReportCtrlDemoDlg::OnPosition() 
{
	// TODO: Add your control notification handler code here
	PopupMenu(IDR_MENU1, MNU_POSITION, this);
}

void CReportCtrlDemoDlg::OnChkStyle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_wndList.SetCheckboxeStyle(m_nChkStyle);
}

DWORD CReportCtrlDemoDlg::GetStatesInput()
{
	DWORD dwStates = RC_ITEM_NONE;
	CStatesDlg dlg;
	if (dlg.DoModal() == IDOK)
		dwStates = dlg.GetStates();
	return dwStates;
}