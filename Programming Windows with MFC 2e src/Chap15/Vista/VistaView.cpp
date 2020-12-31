// VistaView.cpp : implementation of the CVistaView class
//

#include "stdafx.h"
#include "Vista.h"

#include "VistaDoc.h"
#include "VistaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVistaView

IMPLEMENT_DYNCREATE(CVistaView, CScrollView)

BEGIN_MESSAGE_MAP(CVistaView, CScrollView)
	//{{AFX_MSG_MAP(CVistaView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVistaView construction/destruction

CVistaView::CVistaView()
{
}

CVistaView::~CVistaView()
{
}

BOOL CVistaView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVistaView drawing

void CVistaView::OnDraw(CDC* pDC)
{
	CVistaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CBitmap* pBitmap = pDoc->GetBitmap ();

    if (pBitmap != NULL) {
        CPalette* pOldPalette;
        CPalette* pPalette = pDoc->GetPalette ();

        if (pPalette != NULL) {
            pOldPalette = pDC->SelectPalette (pPalette, FALSE);
            pDC->RealizePalette ();
        }

        DIBSECTION ds;
        pBitmap->GetObject (sizeof (DIBSECTION), &ds);

        CDC memDC;
        memDC.CreateCompatibleDC (pDC);
        CBitmap* pOldBitmap = memDC.SelectObject (pBitmap);

        pDC->BitBlt (0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, &memDC,
            0, 0, SRCCOPY);

        memDC.SelectObject (pOldBitmap);

        if (pPalette != NULL)
            pDC->SelectPalette (pOldPalette, FALSE);
    }
}

void CVistaView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate ();

    CString string;
    CSize sizeTotal;
    CBitmap* pBitmap = GetDocument ()->GetBitmap ();

	//
	// If a bitmap is loaded, set the view size equal to the bitmap size.
	// Otherwise, set the view's width and height to 0.
	//
    if (pBitmap != NULL) {
        DIBSECTION ds;
        pBitmap->GetObject (sizeof (DIBSECTION), &ds);
        sizeTotal.cx = ds.dsBm.bmWidth;
        sizeTotal.cy = ds.dsBm.bmHeight;
        string.Format (_T ("\t%d x %d, %d bpp"), ds.dsBm.bmWidth,
            ds.dsBm.bmHeight, ds.dsBmih.biBitCount);
    }
    else {
        sizeTotal.cx = sizeTotal.cy = 0;
        string.Empty ();
    }

    AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_STATS, 0,
        (LPARAM) (LPCTSTR) string);
    SetScrollSizes (MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CVistaView diagnostics

#ifdef _DEBUG
void CVistaView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVistaView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVistaDoc* CVistaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVistaDoc)));
	return (CVistaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVistaView message handlers
