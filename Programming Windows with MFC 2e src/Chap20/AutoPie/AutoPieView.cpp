// AutoPieView.cpp : implementation of the CAutoPieView class
//

#include "stdafx.h"
#include "AutoPie.h"

#include "AutoPieDoc.h"
#include "AutoPieView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPieView

IMPLEMENT_DYNCREATE(CAutoPieView, CView)

BEGIN_MESSAGE_MAP(CAutoPieView, CView)
	//{{AFX_MSG_MAP(CAutoPieView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPieView construction/destruction

CAutoPieView::CAutoPieView()
{
	// TODO: add construction code here

}

CAutoPieView::~CAutoPieView()
{
}

BOOL CAutoPieView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPieView drawing

void CAutoPieView::OnDraw(CDC* pDC)
{
	CAutoPieDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rect;
	GetClientRect (&rect);

	//
	// Initialize the mapping mode.
	//
	pDC->SetMapMode (MM_ANISOTROPIC);
	pDC->SetWindowExt (500, 500);
	pDC->SetWindowOrg (-250, -250);
	pDC->SetViewportExt (rect.Width (), rect.Height ());

	//
	// Create a set of brushes.
	//
	CBrush brFillColor[4];
	brFillColor[0].CreateSolidBrush (RGB (255,   0,   0));	// Red
	brFillColor[1].CreateSolidBrush (RGB (255, 255,   0));	// Yellow
	brFillColor[2].CreateSolidBrush (RGB (255,   0, 255));	// Magenta
	brFillColor[3].CreateSolidBrush (RGB (  0, 255, 255));	// Cyan

	//
	// Draw the pie chart.
	//
	int nTotal = 0;
	for (int i=0; i<4; i++)
		nTotal += pDoc->GetRevenue (i);

	int x1 = 0;
	int y1 = -1000;
	int nSum = 0;

	for (i=0; i<4; i++) {
		int nRevenue = pDoc->GetRevenue (i);
		if (nRevenue != 0) {
			nSum += nRevenue;
			int x2 = (int) (sin ((((double) nSum * 2 * PI) /
				(double) nTotal) + PI) * 1000);
			int y2 = (int) (cos ((((double) nSum * 2 * PI) /
				(double) nTotal) + PI) * 1000);
			pDC->SelectObject (&brFillColor[i]);
			pDC->Pie (-200, -200, 200, 200, x1, y1, x2, y2);
			x1 = x2;
			y1 = y2;
		}
	}
	pDC->SelectStockObject (WHITE_BRUSH);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPieView diagnostics

#ifdef _DEBUG
void CAutoPieView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoPieView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoPieDoc* CAutoPieView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoPieDoc)));
	return (CAutoPieDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoPieView message handlers
