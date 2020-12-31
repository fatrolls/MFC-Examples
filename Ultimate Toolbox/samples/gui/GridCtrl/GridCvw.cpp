// GridCvw.cpp : implementation of the CGridCtrlView class
//

#include "stdafx.h"
#include "GridCtrl.h"

#include "GridCdoc.h"
#include "GridCvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define SMALL_BITMAP_WIDTH	16
#define SMALL_BITMAP_HEIGHT	16

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlView

IMPLEMENT_DYNCREATE(CGridCtrlView, CFormView)

BEGIN_MESSAGE_MAP(CGridCtrlView, CFormView)
	//{{AFX_MSG_MAP(CGridCtrlView)
	ON_BN_CLICKED(IDC_SET_FONT, OnSetFont)
	ON_BN_CLICKED(IDC_RESET_FONT, OnResetFont)
	ON_BN_CLICKED(IDC_COLOR_BUTTON, OnColorButton)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_SORTABLE, OnSortable)
	ON_BN_CLICKED(IDC_MULCHECK, OnMulcheck)
	ON_BN_CLICKED(IDC_EDITCHECK, OnEditcheck)
	ON_BN_CLICKED(IDC_GRIDLINES, OnGridLines)
	ON_BN_CLICKED(IDC_CHECKABLE, OnCheckable)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_GENERIC1, OnTraceNotification)
	ON_BN_CLICKED(IDC_AUTO_EDIT, OnAutoEdit)
	ON_BN_CLICKED(IDC_SHOW_SELECTION, OnShowSelection)
	ON_EN_CHANGE(IDC_IMAGE_COLUMN, OnChangeImageColumn)
	ON_BN_CLICKED(IDC_HORIZONTAL_GRID, OnHorizontalGrid)
	ON_BN_CLICKED(IDC_VERTICAL_GRID, OnVerticalGrid)
	ON_BN_CLICKED(IDC_GRIDCOLRESIZE, OnGridcolresize)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_BEGINRDRAG, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_DELETEITEM, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_INSERTITEM, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_KEYDOWN, IDC_GENERIC1, OnTraceNotification)
	ON_NOTIFY(LVN_SETDISPINFO, IDC_GENERIC1, OnTraceNotification)
	ON_BN_CLICKED(IDC_RADIOCENTER, OnRadiocenter)
	ON_BN_CLICKED(IDC_RADIOLEFT, OnRadioleft)
	ON_BN_CLICKED(IDC_RADIORIGHT, OnRadioright)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlView construction/destruction

CGridCtrlView::CGridCtrlView()
	: 
	CFormView(CGridCtrlView::IDD),
	m_bInitialized(FALSE)
	{
	//{{AFX_DATA_INIT(CGridCtrlView)
	m_bGridLines = FALSE;
	m_bEditCheck = FALSE;
	m_bMulti = FALSE;
	m_nRegion = 0;
	m_bSort = FALSE;
	m_iNumberOfRows = 5;
	m_iImageColumn = 0;
	m_bCheckable = FALSE;
	m_bAutoEdit = FALSE;
	m_bShowSel = FALSE;
	m_bHorizontal = TRUE;
	m_bVertical = TRUE;
	m_bResize = TRUE;
	//}}AFX_DATA_INIT
	}

CGridCtrlView::~CGridCtrlView()
	{
	}

void CGridCtrlView::DoDataExchange(CDataExchange* pDX)
	{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridCtrlView)
//	DDX_Control(pDX, IDC_COLOR_BUTTON, m_btnCustomize);
	DDX_Control(pDX, IDC_IMAGE_COLUMN_SPIN, m_wndImageColumnSpin);
	DDX_Control(pDX, IDC_NUM_ROWS_SPIN, m_wndNumRowsSpin);
	DDX_Control(pDX, IDC_GENERIC1, m_GridCtrl);
	DDX_Check(pDX, IDC_GRIDLINES, m_bGridLines);
	DDX_Check(pDX, IDC_EDITCHECK, m_bEditCheck);
	DDX_Check(pDX, IDC_MULCHECK, m_bMulti);
	DDX_Radio(pDX, IDC_TEXT_COLOR, m_nRegion);
	DDX_Check(pDX, IDC_SORTABLE, m_bSort);
	DDX_Text(pDX, IDC_NUM_ROWS, m_iNumberOfRows);
	DDV_MinMaxInt(pDX, m_iNumberOfRows, 0, 10000);
	DDX_Text(pDX, IDC_IMAGE_COLUMN, m_iImageColumn);
	DDV_MinMaxInt(pDX, m_iImageColumn, 0, 50);
	DDX_Check(pDX, IDC_CHECKABLE, m_bCheckable);
	DDX_Check(pDX, IDC_AUTO_EDIT, m_bAutoEdit);
	DDX_Check(pDX, IDC_SHOW_SELECTION, m_bShowSel);
	DDX_Check(pDX, IDC_HORIZONTAL_GRID, m_bHorizontal);
	DDX_Check(pDX, IDC_VERTICAL_GRID, m_bVertical);
	DDX_Check(pDX, IDC_GRIDCOLRESIZE, m_bResize);
	//}}AFX_DATA_MAP
	}

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlView diagnostics

#ifdef _DEBUG
void CGridCtrlView::AssertValid() const
	{
	CFormView::AssertValid();
	}

void CGridCtrlView::Dump(CDumpContext& dc) const
	{
	CFormView::Dump(dc);
	}

CGridCtrlDoc* CGridCtrlView::GetDocument() // non-debug version is inline
	{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGridCtrlDoc)));
	return (CGridCtrlDoc*)m_pDocument;
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlView message handlers

void CGridCtrlView::OnInitialUpdate() 
	{
	CFormView::OnInitialUpdate();

	// Add Headers to Grid Control
	for (int i = 0; i < 4 ; i++)
	{
		CString sText;
		sText.Format(_T("Header %d"),i);
		m_GridCtrl.InsertColumn(i, sText);
	}

	// Set the spin ranges
	m_wndNumRowsSpin.SetRange(0, 10000);
	// ... Only four columns (0 - 3)
	m_wndImageColumnSpin.SetRange(0, 3);

	// create the small icon image list	
	m_ImageSmall.Create(IDB_IMAGELIST,16,0,RGB(255,255,255));
	// Associate the image lists with the grid control
	m_GridCtrl.SetImageList(&m_ImageSmall, LVSIL_SMALL);

	m_GridCtrl.SetEqualWidth();

	m_GridCtrl.ShowWindow(SW_SHOW);
	ResizeParentToFit(FALSE);

	m_bInitialized = TRUE;
	}

void CGridCtrlView::OnSetFont() 
	{
	LOGFONT logFont;
	
   memset(&logFont, 0, sizeof(LOGFONT));

                                // Logical font struct
	CFontDialog dlg(&logFont);
	
	if (dlg.DoModal() == IDOK)
		{
		if (dlg.GetSize() > 90)
			AfxMessageBox(_T("This font might not fit the row height"));

		CFont rFont;
   		VERIFY(rFont.CreateFontIndirect(&logFont));

		m_GridCtrl.SetTextFont(&rFont);
		}
	}

void CGridCtrlView::OnResetFont() 
	{
	m_GridCtrl.SetTextFont();
	}

void CGridCtrlView::OnColorButton() 
	{
	if (!UpdateData(TRUE))
		return;

	COLORREF color = 0;

	switch (m_nRegion)
		{
		case 0:
			color = m_GridCtrl.GetTextColor();
			break;
		case 1:
			color = m_GridCtrl.GetTextBkColor();
			break;
		case 2:
			color = m_GridCtrl.GetBkColor();
			break;
		case 3:
			{
			BOOL bGridLines;
			m_GridCtrl.GetGridLines(bGridLines, color);
			}
			break;
		default:
			TRACE1("CGridCtrlView::OnColorButton : Unexpected case in switch 1 : %i\n", m_nRegion);
			ASSERT(FALSE);
			break;
		}

	CColorDialog cdlg(color);
	if (cdlg.DoModal() != IDOK)
		return;
	color = cdlg.GetColor();

	switch (m_nRegion)
		{
		case 0:
			m_GridCtrl.SetTextColor(color);
			break;
		case 1:
			m_GridCtrl.SetTextBkColor(color);
			break;
		case 2:
			m_GridCtrl.SetBkColor(color);
			break;
		case 3:
			{
			BOOL bGridLines;
			COLORREF lineColor;
			m_GridCtrl.GetGridLines(bGridLines, lineColor);
			m_GridCtrl.SetGridLines(bGridLines, color);
			}
			break;
		default:
			TRACE1("CGridCtrlView::OnColorButton : Unexpected case in switch 2 : %i\n", m_nRegion);
			ASSERT(FALSE);
			break;
		}
	
	m_GridCtrl.RedrawWindow();
	}

void CGridCtrlView::OnClear() 
	{
	BeginWaitCursor();

	m_GridCtrl.DeleteAllItems();
	m_GridCtrl.Invalidate();
	
	EndWaitCursor();
	}

void CGridCtrlView::OnInsert() 
	{
	if (!UpdateData(TRUE))
		return;
	
	BeginWaitCursor();
	m_GridCtrl.LockWindowUpdate();
	////////
	// Specify the entire row's column entries. 'lParam' points
	// to the data to be displayed in each column.
	////////
	LV_ITEM lvi;
	lvi.mask       = LVIF_TEXT | LVIF_IMAGE;
	lvi.cchTextMax = 0;
	lvi.lParam     = 0;
	
	int iSubItem;
	TCHAR sBuffer[20];
	// Insert the item
	for (int j = 0; j < m_iNumberOfRows ; j++)
		{
		iSubItem = 0;
		
		lvi.iItem      = j;
		lvi.iSubItem   = 0;
		lvi.iImage	  = 1;
		
		wsprintf(sBuffer, _T("Row%i,Col%i"),j + 1, iSubItem + 1);
		lvi.pszText = sBuffer;
		
		int nRtnValue = m_GridCtrl.InsertItem(&lvi);
		ASSERT(-1 != nRtnValue);
		
		// Note that we're starting from iSubItem '1'
		for (iSubItem = 1; iSubItem < 4; iSubItem++)
			{
			wsprintf(sBuffer, _T("Row%i,Col%i"),j + 1, iSubItem + 1);
			m_GridCtrl.SetItemText(j, iSubItem, sBuffer);
			}
		}
	
	m_GridCtrl.UnlockWindowUpdate();
	EndWaitCursor();	
	}


void CGridCtrlView::OnSortable() 
	{
	if (!UpdateData(TRUE))
		return;

	// ... Show wait cursor (may take a while)
	CWaitCursor wc;

	m_GridCtrl.SetSortable(m_bSort);
	}

void CGridCtrlView::OnMulcheck() 
	{
	if (!UpdateData(TRUE))
		return;

 	m_GridCtrl.SetMultipleSelection(m_bMulti);
	}

void CGridCtrlView::OnEditcheck() 
	{
	if (!UpdateData(TRUE))
		return;

 	m_GridCtrl.SetEditable(m_bEditCheck);
	}

void CGridCtrlView::OnGridLines() 
	{
	if (!UpdateData(TRUE))
		return;

	BOOL bGridLines;
	COLORREF lineColor;
	m_GridCtrl.GetGridLines(bGridLines, lineColor);
	m_GridCtrl.SetGridLines(m_bGridLines, lineColor);
	}


void CGridCtrlView::OnCheckable() 
	{
	if (!UpdateData(TRUE))
		return;

 	m_GridCtrl.SetCheckable(m_bCheckable != 0);
	m_GridCtrl.SetCheckStyle(m_bCheckable == 2 ? BS_AUTO3STATE : BS_AUTOCHECKBOX);
	}


void CGridCtrlView::OnTraceNotification(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
	{
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	static BOOL bAbort = FALSE;

	*pResult = bAbort;
	}


void CGridCtrlView::OnAutoEdit() 
	{
	if (!UpdateData(TRUE))
		return;

 	m_GridCtrl.SetAutoEdit(m_bAutoEdit);
	}

void CGridCtrlView::OnShowSelection() 
	{
	if (!UpdateData(TRUE))
		return;

 	m_GridCtrl.SetShowSelAlways(m_bShowSel);
	}

void CGridCtrlView::OnChangeImageColumn() 
	{
	if (!m_bInitialized || !UpdateData(TRUE))
		return;
	
	if (!m_GridCtrl.SetImageColumn(m_iImageColumn))
		AfxMessageBox(_T("Unable to set desired ImageColumn"));
	}

void CGridCtrlView::OnHorizontalGrid() 
	{
	if (!UpdateData(TRUE))
		return;
	
 	m_GridCtrl.SetGridLineOrientation(m_bHorizontal, m_bVertical);
	}

void CGridCtrlView::OnVerticalGrid() 
	{
	if (!UpdateData(TRUE))
		return;
	
 	m_GridCtrl.SetGridLineOrientation(m_bHorizontal, m_bVertical);
	}


void CGridCtrlView::OnGridcolresize() 
	{
	if (!UpdateData(TRUE))
		return;

 	m_GridCtrl.SetResizing(m_bResize);
	}

void CGridCtrlView::OnRadiocenter() 
	{
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;
	lvc.fmt = LVCFMT_CENTER;

 	m_GridCtrl.SetColumn(1, &lvc);

	m_GridCtrl.RedrawWindow();
	}

void CGridCtrlView::OnRadioleft() 
	{
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;
	lvc.fmt = LVCFMT_LEFT;

 	m_GridCtrl.SetColumn(1, &lvc);
	m_GridCtrl.RedrawWindow();
	}

void CGridCtrlView::OnRadioright() 
	{
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;
	lvc.fmt = LVCFMT_RIGHT;

 	m_GridCtrl.SetColumn(1, &lvc);
	m_GridCtrl.RedrawWindow();
	}
