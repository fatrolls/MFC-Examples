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
	m_nFixCols = 1;
	m_nFixRows = 1;
	m_nCols = 10;
	m_nRows = 50;
	m_bEditable = TRUE;
	m_bHorzLines = TRUE;
	m_bListMode = FALSE;
	m_bVertLines = TRUE;
	m_bSelectable = TRUE;
	m_bAllowColumnResize = TRUE;
	m_bAllowRowResize = TRUE;
	m_bHeaderSort = TRUE;
	m_bReadOnly = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridCtrlDemoDlg)
	DDX_Control(pDX, IDC_SPIN_ROW, m_RowSpin);
	DDX_Control(pDX, IDC_SPIN_FIXROW, m_FixRowSpin);
	DDX_Control(pDX, IDC_SPIN_FIXCOL, m_FixColSpin);
	DDX_Control(pDX, IDC_SPIN_COL, m_ColSpin);
	DDX_Text(pDX, IDC_EDIT_FIXCOLS, m_nFixCols);
	DDX_Text(pDX, IDC_EDIT_FIXROWS, m_nFixRows);
	DDX_Text(pDX, IDC_EDIT_COLS, m_nCols);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_nRows);
	DDX_Check(pDX, IDC_EDITABLE, m_bEditable);
	DDX_Check(pDX, IDC_HORZ_LINES, m_bHorzLines);
	DDX_Check(pDX, IDC_LISTMODE, m_bListMode);
	DDX_Check(pDX, IDC_VERT_LINES, m_bVertLines);
	DDX_Check(pDX, IDC_ALLOW_SELECTION, m_bSelectable);
	DDX_Check(pDX, IDC_COL_RESIZE, m_bAllowColumnResize);
	DDX_Check(pDX, IDC_ROW_RESIZE, m_bAllowRowResize);
	DDX_Check(pDX, IDC_HEADERSORT, m_bHeaderSort);
	DDX_Check(pDX, IDC_READ_ONLY, m_bReadOnly);
	//}}AFX_DATA_MAP

    // There is a problem with registering the grid as an OLE Drop target
    // in the CGridCtrl::PreSubclassWindow function that only shows itself
    // under win95. To ensure that the grid can accept drag and drop items,
    // we use the DDX_GridControl routine which ensures that CGridCtrl::SubclassWindow
    // is called, and hence the grid will be registered as a drop target.
    //
    // If ANYONE knows a neater way, please let me know. I'm new to this stuff!
	DDX_GridControl(pDX, IDC_GRID, m_Grid);
}

BEGIN_MESSAGE_MAP(CGridCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGridCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_EN_UPDATE(IDC_EDIT_COLS, OnUpdateEditCols)
	ON_EN_UPDATE(IDC_EDIT_FIXCOLS, OnUpdateEditFixcols)
	ON_EN_UPDATE(IDC_EDIT_FIXROWS, OnUpdateEditFixrows)
	ON_EN_UPDATE(IDC_EDIT_ROWS, OnUpdateEditRows)
	ON_BN_CLICKED(IDC_HORZ_LINES, OnGridLines)
	ON_BN_CLICKED(IDC_LISTMODE, OnListmode)
	ON_BN_CLICKED(IDC_EDITABLE, OnEditable)
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnPrintButton)
	ON_BN_CLICKED(IDC_ALLOW_SELECTION, OnAllowSelection)
	ON_BN_CLICKED(IDC_ROW_RESIZE, OnRowResize)
	ON_BN_CLICKED(IDC_COL_RESIZE, OnColResize)
	ON_BN_CLICKED(IDC_FONT_BUTTON, OnFontButton)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_HEADERSORT, OnHeaderSort)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyOrCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_BN_CLICKED(IDC_VERT_LINES, OnGridLines)
	ON_COMMAND(ID_FILE_PRINT, OnPrintButton)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyOrCut)
	ON_BN_CLICKED(IDC_READ_ONLY, OnReadOnly)
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

	// init spin controls
	m_RowSpin.SetRange(0,999);
	m_FixRowSpin.SetRange(0,999);
	m_FixColSpin.SetRange(0,999);
	m_ColSpin.SetRange(0,999);

	OnListmode();

	/////////////////////////////////////////////////////////////////////////
	// initialise grid properties
	/////////////////////////////////////////////////////////////////////////

	m_ImageList.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255,255,255));
	m_Grid.SetImageList(&m_ImageList);

	m_Grid.SetEditable(m_bEditable);
	m_Grid.SetListMode(m_bListMode);
	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

	try {
		m_Grid.SetRowCount(m_nRows);
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
		m_Grid.SetFixedColumnCount(m_nFixCols);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	// fill rows/cols with text
	for (int row = 0; row < m_Grid.GetRowCount(); row++)
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (row < m_nFixRows) {
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.szText.Format(_T("Column %d"),col);
			} else if (col < m_nFixCols) {
				Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText.Format(_T("Row %d"),row);
			} else {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText.Format(_T("%d"),row*col);
			}
			m_Grid.SetItem(&Item);

			if (col == (m_Grid.GetFixedColumnCount()-1) && row >= m_Grid.GetFixedRowCount())
				m_Grid.SetItemImage(row, col, row%2);
			//else if (rand() % 10 == 1)
			//	m_Grid.SetItemImage(row, col, 0);

			if (rand() % 10 == 1)
			{
                COLORREF clr = RGB(rand() % 128+128, rand() % 128+128, rand() % 128+128);
				m_Grid.SetItemBkColour(row, col, clr);
				m_Grid.SetItemFgColour(row, col, RGB(255,0,0));
			}
		}

    m_Grid.SetItemState(1,1, m_Grid.GetItemState(1,1) | GVIS_READONLY);

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

void CGridCtrlDemoDlg::OnUpdateEditCols() 
{
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

    int nOldNumCols = m_Grid.GetColumnCount();

	try { m_Grid.SetColumnCount(m_nCols); }
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}

	m_nCols = m_Grid.GetColumnCount();
	m_nFixCols = m_Grid.GetFixedColumnCount();
	UpdateData(FALSE);

    CString str;
    for (int i = nOldNumCols; i < m_nCols; i++)
    {
        str.Format(_T("Column %d"), i);
        m_Grid.SetItemText(0,i,str);
    }
}

void CGridCtrlDemoDlg::OnUpdateEditFixcols() 
{
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

	try { m_Grid.SetFixedColumnCount(m_nFixCols); }
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}

	m_nCols = m_Grid.GetColumnCount();
	m_nFixCols = m_Grid.GetFixedColumnCount();
	UpdateData(FALSE);
}

void CGridCtrlDemoDlg::OnUpdateEditFixrows() 
{
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

	try { m_Grid.SetFixedRowCount(m_nFixRows); }
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}

	m_nRows = m_Grid.GetRowCount();
	m_nFixRows = m_Grid.GetFixedRowCount();
	UpdateData(FALSE);
}

void CGridCtrlDemoDlg::OnUpdateEditRows() 
{	
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

    int nOldNumRows = m_Grid.GetRowCount();

	try { m_Grid.SetRowCount(m_nRows); }
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}

	m_nRows = m_Grid.GetRowCount();
	m_nFixRows = m_Grid.GetFixedRowCount();
	UpdateData(FALSE);

    CString str;
    for (int i = nOldNumRows; i < m_nRows; i++)
    {
        str.Format(_T("Row %d"), i);
        m_Grid.SetItemText(i,0,str);
    }
}

void CGridCtrlDemoDlg::OnGridLines() 
{
	UpdateData();

	if (!m_bHorzLines && !m_bVertLines)
		m_Grid.SetGridLines(GVL_NONE);
	else if (m_bHorzLines && !m_bVertLines)
		m_Grid.SetGridLines(GVL_HORZ);
	else if (!m_bHorzLines && m_bVertLines)
		m_Grid.SetGridLines(GVL_VERT);
	else 
		m_Grid.SetGridLines(GVL_BOTH);
}

void CGridCtrlDemoDlg::OnListmode() 
{
	UpdateData();
	m_Grid.SetListMode(m_bListMode);

	CWnd* pHeaderSortBtn = GetDlgItem(IDC_HEADERSORT);
	if (pHeaderSortBtn) 
	{
		pHeaderSortBtn->ModifyStyle(m_bListMode?WS_DISABLED:0, m_bListMode? 0:WS_DISABLED);
		pHeaderSortBtn->Invalidate();
	}
}

void CGridCtrlDemoDlg::OnHeaderSort() 
{
	UpdateData();
	m_Grid.SetHeaderSort(m_bHeaderSort);
}

void CGridCtrlDemoDlg::OnEditable() 
{
	UpdateData();
	m_Grid.SetEditable(m_bEditable);
}

void CGridCtrlDemoDlg::OnAllowSelection() 
{
	UpdateData();
	m_Grid.EnableSelection(m_bSelectable);
}

void CGridCtrlDemoDlg::OnRowResize() 
{
	UpdateData();
	m_Grid.SetRowResize(m_bAllowRowResize);
}

void CGridCtrlDemoDlg::OnColResize() 
{
	UpdateData();
	m_Grid.SetColumnResize(m_bAllowColumnResize);
}

void CGridCtrlDemoDlg::OnPrintButton() 
{
	m_Grid.Print();
}

void CGridCtrlDemoDlg::OnFontButton() 
{
	LOGFONT lf;
	m_Grid.GetFont()->GetLogFont(&lf);

	CFontDialog dlg(&lf);
	if (dlg.DoModal() == IDOK) {
		dlg.GetCurrentFont(&lf);

		CFont Font;
		Font.CreateFontIndirect(&lf);
		m_Grid.SetFont(&Font);
		m_Grid.AutoSize();
		Font.DeleteObject();	
	}
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

    //if (::IsWindow(m_Grid.m_hWnd))
    //    m_Grid.ExpandToFit();
}

void CGridCtrlDemoDlg::OnEditCopy() 
{
	m_Grid.OnEditCopy();	
}

void CGridCtrlDemoDlg::OnEditCut() 
{
	m_Grid.OnEditCut();	
}

void CGridCtrlDemoDlg::OnEditPaste() 
{
	m_Grid.OnEditPaste();	
}

void CGridCtrlDemoDlg::OnUpdateEditCopyOrCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Grid.GetSelectedCount() > 0);
}

void CGridCtrlDemoDlg::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // Attach a COleDataObject to the clipboard see if there is any data
    COleDataObject obj;
    pCmdUI->Enable(obj.AttachClipboard() && obj.IsDataAvailable(CF_TEXT)); 
}

void CGridCtrlDemoDlg::OnEditSelectall() 
{
	m_Grid.OnEditSelectAll();
}

void CGridCtrlDemoDlg::OnAppAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CGridCtrlDemoDlg::OnReadOnly() 
{
	UpdateData();
    if (m_bReadOnly)
        m_Grid.SetItemState(1,1, m_Grid.GetItemState(1,1) | GVIS_READONLY);
    else
        m_Grid.SetItemState(1,1, m_Grid.GetItemState(1,1) & ~GVIS_READONLY);
}
