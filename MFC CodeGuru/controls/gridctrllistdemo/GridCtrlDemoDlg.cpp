// GridCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GridCtrlDemo.h"
#include "GridCtrlDemoDlg.h"

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
	CAboutDlg() : CDialog(IDD_ABOUTBOX) {}
};

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg dialog

CGridCtrlDemoDlg::CGridCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridCtrlDemoDlg::IDD, pParent)
{
	m_OldSize = CSize(-1,-1);

	//{{AFX_DATA_INIT(CGridCtrlDemoDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridCtrlDemoDlg)
	DDX_Control(pDX, IDC_GRID, m_Grid);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGridCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGridCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg message handlers

BOOL CGridCtrlDemoDlg::OnInitDialog()
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CRect rect;
	GetClientRect(rect);
	m_OldSize = CSize(rect.Width(), rect.Height());


	/////////////////////////////////////////////////////////////////////////
	// initialise grid properties
	/////////////////////////////////////////////////////////////////////////

	m_ImageList.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255,255,255));
	m_Grid.SetImageList(&m_ImageList);

	m_Grid.SetEditable(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	try {
		m_Grid.SetRowCount(50);
		m_Grid.SetColumnCount(9);
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	// fill rows/cols with text
	//BOOL SetColumnType(int nCol, int nType);
	for (int row = 0; row < 50; row++)
		for (int col = 0; col < 9; col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (row < 1) {
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				if (col == 0 || col == 1) {
					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.szText.Format(_T("Column %d NOEDIT"),col);
				}
				else if (col == 2 || col == 3) {
					m_Grid.SetColumnType(col, GVET_LISTBOX);
					Item.szText.Format(_T("Column %d LISTBOX"),col);
				}
				else {
					m_Grid.SetColumnType(col, GVET_EDITBOX);
					Item.szText.Format(_T("Column %d EDITBOX"),col);
				}

			} else if (col < 1) {
				Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText.Format(_T("Row %d"),row);
			} else {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				if (col == 2)
					Item.szText.Format(_T("Yes"),row);
				else if (col == 3)
					Item.szText.Format(_T("BBB"),row);
				else
					Item.szText.Format(_T("%d"),row*col);
			}
			m_Grid.SetItem(&Item);

			if (col == (m_Grid.GetFixedColumnCount()-1) && row >= m_Grid.GetFixedRowCount())
				m_Grid.SetItemImage(row, col, row%2);
			//else if (rand() % 10 == 1)
			//	m_Grid.SetItemImage(row, col, 0);
		
		}

	m_Grid.AutoSize();
	m_Grid.SetRowHeight(0, 3*m_Grid.GetRowHeight(0)/2);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGridCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

HCURSOR CGridCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CGridCtrlDemoDlg::OnRowResize() 
{
	UpdateData();
	m_Grid.SetRowResize(TRUE);
}


BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
	CWnd* pWnd = CWnd::FromHandle(hwnd);
	CSize* pTranslate = (CSize*) lParam;

	CGridCtrlDemoDlg* pDlg = (CGridCtrlDemoDlg*) pWnd->GetParent();
	if (!pDlg) return FALSE;

	CRect rect;
	pWnd->GetWindowRect(rect);
	if (hwnd == pDlg->m_Grid.GetSafeHwnd())
		TRACE(_T("Wnd rect: %d,%d - %d,%d\n"),rect.left,rect.top, rect.right, rect.bottom);
	pDlg->ScreenToClient(rect);
	if (hwnd == pDlg->m_Grid.GetSafeHwnd())
		TRACE(_T("Scr rect: %d,%d - %d,%d\n"),rect.left,rect.top, rect.right, rect.bottom);


	if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	{
		if (  ((rect.top >= 7 && pTranslate->cy > 0) || rect.Height() > 20) &&
			  ((rect.left >= 7 && pTranslate->cx > 0) || rect.Width() > 20)   )
			pDlg->m_Grid.MoveWindow(rect.left, rect.top, 
									rect.Width()+pTranslate->cx, 
									rect.Height()+pTranslate->cy, FALSE);
		else
			pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, 
							 rect.Width(), rect.Height(), FALSE);
	}
	else 
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, 
						 rect.Width(), rect.Height(), FALSE);
	}
	pDlg->Invalidate();

	return TRUE;
}

void CGridCtrlDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (cx <= 1 || cy <= 1 ) return;

	CSize Translate(cx - m_OldSize.cx, cy - m_OldSize.cy);

	::EnumChildWindows(GetSafeHwnd(), EnumProc, (LPARAM)&Translate);
	m_OldSize = CSize(cx,cy);
}


void CGridCtrlDemoDlg::CGridEx::FillListItems(int nCol, LPARAM cltList)
{
	CListBox*	pList = (CListBox*)cltList;
	if (nCol == 2)
	{
		pList->AddString("Yes");
		pList->AddString("No");
		pList->AddString("Cancel");
		pList->AddString("Abort");
		pList->AddString("Retry");
		pList->AddString("Accept");
	}
	else if (nCol == 3)
	{
		pList->AddString("AAA");
		pList->AddString("BBB");
		pList->AddString("CCC");
		pList->AddString("DDD");
		pList->AddString("EEE");
		pList->AddString("FFF");
		pList->AddString("GGG");
		pList->AddString("HHH");
		pList->AddString("III");
	}
}
