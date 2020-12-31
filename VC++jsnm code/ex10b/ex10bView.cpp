// ex10bView.cpp : implementation of the CEx10bView class
//

#include "stdafx.h"
#include "ex10b.h"

#include "ex10bDoc.h"
#include "ex10bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10bView

IMPLEMENT_DYNCREATE(CEx10bView, CScrollView)

BEGIN_MESSAGE_MAP(CEx10bView, CScrollView)
	//{{AFX_MSG_MAP(CEx10bView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10bView construction/destruction

CEx10bView::CEx10bView() : m_sizeEllipse(100, -100),
                           m_pointTopLeft(10, -10),
                           m_sizeOffset(0, 0)
{
	m_bCaptured = FALSE;
	m_pdcMemory = new CDC;
	m_pBitmap   = new CBitmap;
}

CEx10bView::~CEx10bView()
{
	delete m_pBitmap; // already deselected
	delete m_pdcMemory;
}

BOOL CEx10bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx10bView drawing

void CEx10bView::OnDraw(CDC* pDC)
{
	CBrush brushHatch(HS_DIAGCROSS, RGB(255, 0, 0));
	CPoint point(0, 0);                  // logical (0, 0)
	
	pDC->LPtoDP(&point);                 // In device coordinates,
	pDC->SetBrushOrg(point);             //  align the brush with
	                                     //  the window origin
	pDC->SelectObject(&brushHatch);
	pDC->Ellipse(CRect(m_pointTopLeft, m_sizeEllipse));
	pDC->SelectStockObject(BLACK_BRUSH); // Deselect brushHatch
	pDC->Rectangle(CRect(100, -100, 200, -200)); // Test invalid rect
}

void CEx10bView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(800, 1050); // 8-by-10.5 inches
	CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
	CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
	SetScrollSizes(MM_LOENGLISH, sizeTotal, sizePage, sizeLine);
	// creates the memory device context and the bitmap
	if (m_pdcMemory->GetSafeHdc() == NULL) {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		CRect rectMax(0, 0, sizeTotal.cx, -sizeTotal.cy);
		dc.LPtoDP(rectMax);
		m_pdcMemory->CreateCompatibleDC(&dc);
		// makes bitmap same size as display window
		m_pBitmap->CreateCompatibleBitmap(&dc, rectMax.right,
		                                  rectMax.bottom);
		m_pdcMemory->SetMapMode(MM_LOENGLISH);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx10bView printing

BOOL CEx10bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx10bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx10bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx10bView diagnostics

#ifdef _DEBUG
void CEx10bView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx10bView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx10bDoc* CEx10bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx10bDoc)));
	return (CEx10bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10bView message handlers

void CEx10bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rectEllipse(m_pointTopLeft, m_sizeEllipse);
	CRgn  circle;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(rectEllipse);
	circle.CreateEllipticRgnIndirect(rectEllipse);
	if (circle.PtInRegion(point)) {
		// Capturing the mouse ensures subsequent LButtonUp message
		SetCapture();
		m_bCaptured = TRUE;
		CPoint pointTopLeft(m_pointTopLeft);
		dc.LPtoDP(&pointTopLeft);
		m_sizeOffset = point - pointTopLeft;
		// New mouse cursor is active while mouse is captured
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
	}
}

void CEx10bView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) {
		::ReleaseCapture();
		m_bCaptured = FALSE;
	}
}

void CEx10bView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		CRect rectOld(m_pointTopLeft, m_sizeEllipse);
		dc.LPtoDP(rectOld);
		InvalidateRect(rectOld, FALSE);
		m_pointTopLeft = point - m_sizeOffset;
		dc.DPtoLP(&m_pointTopLeft);
		CRect rectNew(m_pointTopLeft, m_sizeEllipse);
		dc.LPtoDP(rectNew);
		InvalidateRect(rectNew, FALSE);
	}
}

void CEx10bView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnPrepareDC(&dc);
	CRect rectUpdate;
	dc.GetClipBox(&rectUpdate);
	CBitmap* pOldBitmap = m_pdcMemory->SelectObject(m_pBitmap);
	m_pdcMemory->SelectClipRgn(NULL);
	m_pdcMemory->IntersectClipRect(&rectUpdate);
	CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
	CBrush* pOldBrush = m_pdcMemory->SelectObject(&backgroundBrush);
	m_pdcMemory->PatBlt(rectUpdate.left, rectUpdate.top,
	                    rectUpdate.Width(), rectUpdate.Height(),
	                    PATCOPY);
	OnDraw(m_pdcMemory);
	dc.BitBlt(rectUpdate.left, rectUpdate.top,
	          rectUpdate.Width(), rectUpdate.Height(),
	          m_pdcMemory, rectUpdate.left, rectUpdate.top,
	          SRCCOPY);
	m_pdcMemory->SelectObject(pOldBitmap);
	m_pdcMemory->SelectObject(pOldBrush);
}
