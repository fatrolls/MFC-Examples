// ScrollDemoView.cpp : implementation of the CScrollDemoView class
//

#include "stdafx.h"
#include "ScrollDemo.h"

#include "ScrollDemoDoc.h"
#include "ScrollDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoView

IMPLEMENT_DYNCREATE(CScrollDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CScrollDemoView, CScrollView)
	//{{AFX_MSG_MAP(CScrollDemoView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoView construction/destruction

CScrollDemoView::CScrollDemoView()
{
	m_font.CreatePointFont (80, _T ("MS Sans Serif"));
}

CScrollDemoView::~CScrollDemoView()
{
}

BOOL CScrollDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoView drawing

void CScrollDemoView::OnDraw(CDC* pDC)
{
	CScrollDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    //
    // Draw the grid lines.
    //
	CSize size = GetTotalSize ();
    CPen pen (PS_SOLID, 0, RGB (192, 192, 192));
    CPen* pOldPen = pDC->SelectObject (&pen);

    for (int i=0; i<99; i++) {
        int y = (i * m_nCellHeight) + m_nCellHeight;
        pDC->MoveTo (0, y);
        pDC->LineTo (size.cx, y);
    }

    for (int j=0; j<26; j++) {
        int x = (j * m_nCellWidth) + m_nRibbonWidth;
        pDC->MoveTo (x, 0);
        pDC->LineTo (x, size.cy);
    }

    pDC->SelectObject (pOldPen);
    
    //
    // Draw the bodies of the rows and column headers.
    //
    CBrush brush;
    brush.CreateStockObject (LTGRAY_BRUSH);

    CRect rcTop (0, 0, size.cx, m_nCellHeight);
    pDC->FillRect (rcTop, &brush);
    CRect rcLeft (0, 0, m_nRibbonWidth, size.cy);
    pDC->FillRect (rcLeft, &brush);

    pDC->MoveTo (0, m_nCellHeight);
    pDC->LineTo (size.cx, m_nCellHeight);
    pDC->MoveTo (m_nRibbonWidth, 0);
    pDC->LineTo (m_nRibbonWidth, size.cy);

    pDC->SetBkMode (TRANSPARENT);

    //
    // Add numbers and button outlines to the row headers.
    //
    for (i=0; i<99; i++) {
        int y = (i * m_nCellHeight) + m_nCellHeight;
        pDC->MoveTo (0, y);
        pDC->LineTo (m_nRibbonWidth, y);

        CString string;
        string.Format (_T ("%d"), i + 1);

        CRect rect (0, y, m_nRibbonWidth, y + m_nCellHeight);
        pDC->DrawText (string, &rect, DT_SINGLELINE |
            DT_CENTER | DT_VCENTER);

        rect.top++;
        pDC->Draw3dRect (rect, RGB (255, 255, 255),
            RGB (128, 128, 128));
    }

    //
    // Add letters and button outlines to the column headers.
    //
    for (j=0; j<26; j++) {
        int x = (j * m_nCellWidth) + m_nRibbonWidth;
        pDC->MoveTo (x, 0);
        pDC->LineTo (x, m_nCellHeight);

        CString string;
        string.Format (_T ("%c"), j + 'A');

        CRect rect (x, 0, x + m_nCellWidth, m_nCellHeight);
        pDC->DrawText (string, &rect, DT_SINGLELINE |
            DT_CENTER | DT_VCENTER);

        rect.left++;
        pDC->Draw3dRect (rect, RGB (255, 255, 255),
            RGB (128, 128, 128));
    }

	//
	// Draw address labels into the individual cells.
	//
	CRect rect;
	pDC->GetClipBox (&rect);
	int nStartRow = max (0, (rect.top - m_nCellHeight) / m_nCellHeight);
	int nEndRow = min (98, (rect.bottom - 1) / m_nCellHeight);
	int nStartCol = max (0, (rect.left - m_nRibbonWidth) / m_nCellWidth);
	int nEndCol = min (25, ((rect.right + m_nCellWidth - 1) -
		m_nRibbonWidth) / m_nCellWidth);

	for (i=nStartRow; i<=nEndRow; i++)
		for (j=nStartCol; j<=nEndCol; j++)
			DrawAddress (pDC, i, j);

	//
	// Draw the cell pointer.
	//
	DrawPointer (pDC, m_nCurrentRow, m_nCurrentCol, TRUE);
}

void CScrollDemoView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	m_nCurrentRow = 0;
	m_nCurrentCol = 0;
	m_bSmooth = FALSE;

    CClientDC dc (this);
    m_nCellWidth = dc.GetDeviceCaps (LOGPIXELSX);
    m_nCellHeight = dc.GetDeviceCaps (LOGPIXELSY) / 4;
    m_nRibbonWidth = m_nCellWidth / 2;

    int nWidth = (26 * m_nCellWidth) + m_nRibbonWidth;
    int nHeight = m_nCellHeight * 100;
	SetScrollSizes (MM_TEXT, CSize (nWidth, nHeight));
}

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoView diagnostics

#ifdef _DEBUG
void CScrollDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScrollDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CScrollDemoDoc* CScrollDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollDemoDoc)));
	return (CScrollDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoView message handlers

void CScrollDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);

	//
	// Convert the click point to logical coordinates.
	//
	CPoint pos = point;
	CClientDC dc (this);
	OnPrepareDC (&dc);
	dc.DPtoLP (&pos);

	//
	// If a cell was clicked, move the cell pointer.
	//
	CSize size = GetTotalSize ();
	if (pos.x > m_nRibbonWidth && pos.x < size.cx &&
		pos.y > m_nCellHeight && pos.y < size.cy) {

		int row = (pos.y - m_nCellHeight) / m_nCellHeight;
		int col = (pos.x - m_nRibbonWidth) / m_nCellWidth;
		ASSERT (row >= 0 && row <= 98 && col >= 0 && col <= 25);

		DrawPointer (&dc, m_nCurrentRow, m_nCurrentCol, FALSE);
		m_nCurrentRow = row;
		m_nCurrentCol = col;
		DrawPointer (&dc, m_nCurrentRow, m_nCurrentCol, TRUE);
	}
}

void CScrollDemoView::DrawPointer(CDC *pDC, int row, int col, BOOL bHighlight)
{
	CRect rect;
	GetCellRect (row, col, &rect);
	CBrush brush (bHighlight ? RGB (0, 255, 255) :
		::GetSysColor (COLOR_WINDOW));
	pDC->FillRect (rect, &brush);
	DrawAddress (pDC, row, col);
}

void CScrollDemoView::DrawAddress(CDC *pDC, int row, int col)
{
	CRect rect;
	GetCellRect (row, col, &rect);

	CString string;
	string.Format (_T ("%c%d"), col + _T ('A'), row + 1);

	pDC->SetBkMode (TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject (&m_font);
	pDC->DrawText (string, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SelectObject (pOldFont);
}

void CScrollDemoView::GetCellRect(int row, int col, LPRECT pRect)
{
	pRect->left = m_nRibbonWidth + (col * m_nCellWidth) + 1;
	pRect->top = m_nCellHeight + (row * m_nCellHeight) + 1;
	pRect->right = pRect->left + m_nCellWidth - 1;
	pRect->bottom = pRect->top + m_nCellHeight - 1;
}
