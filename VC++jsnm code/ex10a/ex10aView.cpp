// ex10aView.cpp : implementation of the CEx10aView class
//

#include "stdafx.h"
#include "ex10a.h"

#include "ex10aDoc.h"
#include "ex10aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10aView

IMPLEMENT_DYNCREATE(CEx10aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx10aView, CScrollView)
	//{{AFX_MSG_MAP(CEx10aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10aView construction/destruction

CEx10aView::CEx10aView()
{
	m_pdcMemory = new CDC;
	m_pBitmap = new CBitmap;
}

CEx10aView::~CEx10aView()
{
	// cleans up the memory device context and the bitmap
	delete m_pdcMemory; // deselects bitmap
	delete m_pBitmap;
}

BOOL CEx10aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx10aView drawing

void CEx10aView::OnDraw(CDC* pDC)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->StretchBlt(20, -20, m_sizeDest.cx, -m_sizeDest.cy,
	                m_pdcMemory, 0, 0,
	                m_sizeSource.cx, m_sizeSource.cy, SRCCOPY);

	pDC->StretchBlt(350, -20, m_sizeSource.cx, -m_sizeSource.cy,
	                m_pdcMemory, 0, 0,
	                m_sizeSource.cx, m_sizeSource.cy, SRCCOPY);
}

void CEx10aView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(800, 1050); // 8-by-10.5 inches
	CSize sizeLine = CSize(sizeTotal.cx / 100, sizeTotal.cy / 100);
	SetScrollSizes(MM_LOENGLISH, sizeTotal, sizeTotal, sizeLine);

	BITMAP bm; // Windows BITMAP data structure; see Win32 help
	if (m_pdcMemory->GetSafeHdc() == NULL) {
		CClientDC dc(this);
		OnPrepareDC(&dc); // necessary
		m_pBitmap->LoadBitmap(IDB_GOLDWEAVE);
		m_pdcMemory->CreateCompatibleDC(&dc);
		m_pdcMemory->SelectObject(m_pBitmap);
		m_pBitmap->GetObject(sizeof(bm), &bm);
		m_sizeSource.cx = bm.bmWidth;
		m_sizeSource.cy = bm.bmHeight;
		m_sizeDest = m_sizeSource;
		dc.DPtoLP(&m_sizeDest);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx10aView printing

BOOL CEx10aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx10aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx10aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx10aView diagnostics

#ifdef _DEBUG
void CEx10aView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx10aView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx10aDoc* CEx10aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx10aDoc)));
	return (CEx10aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10aView message handlers
