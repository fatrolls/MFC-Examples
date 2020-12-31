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
	LOGFONT lf;
	CFont font;
	CFont *pFtOld;
	CBrush brush;
	CBrush *pBrOld;
	int nNumPts;
	int i;
	LPPOINT lpPoints;
	POINT pt;
	LPBYTE lpTypes;
	CSize size;

	CGDIDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight=400;
	lstrcpy(lf.lfFaceName, "Times New Roman");
	font.CreateFontIndirect(&lf);
	pFtOld=pDC->SelectObject(&font);

	brush.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 0));
	pBrOld=pDC->SelectObject(&brush);

	pDC->BeginPath();
	pDC->TextOut(0, 0, "Path");
	pDC->EndPath();

	nNumPts=pDC->GetPath(NULL, NULL, 0);
	ASSERT(nNumPts != -1);
	lpPoints=(LPPOINT)::GlobalAlloc(GPTR, nNumPts*sizeof(POINT));
	ASSERT(lpPoints);
	lpTypes=(LPBYTE)::GlobalAlloc(GPTR, nNumPts);
	ASSERT(lpTypes);
	pDC->GetPath(lpPoints, lpTypes, nNumPts);

	size=pDC->GetTextExtent("Path");
	for(i=0; i<nNumPts; i++)
	{
		pt=lpPoints[i];
		pt.y-=pt.y*pt.x/size.cx;
		lpPoints[i]=pt;
	}
	
	pDC->BeginPath();
	for(i=0; i<nNumPts; i++)
	{
		switch(lpTypes[i])
		{
			case PT_MOVETO : 
			{
				pDC->MoveTo(lpPoints[i].x, lpPoints[i].y); 
				break;
			}
			case PT_LINETO | PT_CLOSEFIGURE:
			case PT_LINETO: 
			{
				pDC->LineTo(lpPoints[i].x, lpPoints[i].y);
				break;
			}
			case PT_BEZIERTO | PT_CLOSEFIGURE:
			case PT_BEZIERTO:
			{
				pDC->PolyBezierTo(&lpPoints[i], 3);
				i+=2;
				break;
			}
		}
	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();

	pDC->SelectObject(pBrOld);
	pDC->SelectObject(pFtOld);

	::GlobalFree(lpPoints);
	::GlobalFree(lpTypes);
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
