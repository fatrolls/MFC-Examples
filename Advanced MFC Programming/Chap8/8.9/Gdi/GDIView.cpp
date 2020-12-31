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
	LPLOGPALETTE lpLogPal;
	int i;

	lpLogPal=(LPLOGPALETTE) new BYTE[sizeof(LOGPALETTE)+255*sizeof(PALETTEENTRY)];
	lpLogPal->palVersion=0x300;
	lpLogPal->palNumEntries=256;
	for(i=0; i<256; i++)
	{
		*((WORD *)(&(lpLogPal->palPalEntry[i].peRed)))=(WORD)i;
		lpLogPal->palPalEntry[i].peBlue=0;
		lpLogPal->palPalEntry[i].peFlags=PC_EXPLICIT;
	}
	VERIFY(m_palSys.CreatePalette(lpLogPal));
	delete [](BYTE *)lpLogPal;
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
	CBrush brush;
	CBrush *ptrBrushOld;
	CPalette *ptrPalOld;
	CRect rect;
	int i, j;

	CGDIDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(m_palSys.GetSafeHandle());
	ptrPalOld=pDC->SelectPalette(&m_palSys, FALSE);
	pDC->RealizePalette();

	GetClientRect(rect);
	rect.right/=16;
	rect.bottom/=16;

	for(j=0; j<16; j++)
	{
		for(i=0; i<16; i++)
		{
			brush.CreateSolidBrush(PALETTEINDEX(j*16+i));
			ptrBrushOld=pDC->SelectObject(&brush);
			pDC->Rectangle(rect);
			pDC->SelectObject(ptrBrushOld);
			brush.DeleteObject();
			rect.OffsetRect(rect.Width(), 0);
		}
		rect.OffsetRect(-16*rect.Width(), rect.Height());
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
