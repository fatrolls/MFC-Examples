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
	int i;
	LPLOGPALETTE lpLogPal;

	lpLogPal=(LPLOGPALETTE) new BYTE[sizeof(LOGPALETTE)+255*sizeof(PALETTEENTRY)];
	lpLogPal->palVersion=0x300;
	lpLogPal->palNumEntries=256;
	for(i=0; i<256; i++)
	{
		lpLogPal->palPalEntry[i].peRed=0;
		lpLogPal->palPalEntry[i].peGreen=0;
		lpLogPal->palPalEntry[i].peBlue=i;
		lpLogPal->palPalEntry[i].peFlags=NULL;
	}
	VERIFY(m_palDraw.CreatePalette(lpLogPal));
	delete [](BYTE *)lpLogPal;
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC *pDC)
{
	CBrush brush;
	CRect rect;
	CPalette *ptrPalOld;
	int i;

	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	ptrPalOld=pDC->SelectPalette(&m_palDraw, FALSE);
	pDC->RealizePalette();

	GetClientRect(rect);
	rect.bottom+=255;
	rect.bottom/=256;
	for(i=0; i<256; i++)
	{
		brush.CreateSolidBrush(PALETTEINDEX(i));
		pDC->FillRect(rect, &brush);
		brush.DeleteObject();
		rect.OffsetRect(0, rect.Height());
	}
	pDC->SelectPalette(ptrPalOld, FALSE);
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
