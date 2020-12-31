#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	//{{AFX_MSG_MAP(CGDIView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	m_rgnRect.CreateRectRgn(0, 0, 400, 400);
	m_rgnEllipse.CreateEllipticRgn(50, 50, 350, 350);
	m_rgnRect.CombineRgn(&m_rgnRect, &m_rgnEllipse, RGN_DIFF);
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC* pDC)
{
	CString szText="Clip Region";
	CSize size;
	int i, j;
	UINT uTextAlign;
	CRect rect;
	CPoint pt;
		
	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SelectClipRgn(&m_rgnRect);
	size=pDC->GetTextExtent(szText);
	uTextAlign=pDC->SetTextAlign(TA_UPDATECP);
	GetClientRect(rect);
	pt=CPoint(0, 0);
	for(j=0; j<rect.Height()/size.cy+1; j++)
	{
		pDC->MoveTo(0, pt.y);
		for(i=0; i<rect.Width()/size.cx+1; i++)
		{
			pDC->TextOut(0, pt.y, szText);
		}
		pt.y+=size.cy;
	}
	pDC->SetTextAlign(uTextAlign);
	pDC->SelectClipRgn(NULL);
}

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif
