#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIView, CScrollView)

BEGIN_MESSAGE_MAP(CGDIView, CScrollView)
	//{{AFX_MSG_MAP(CGDIView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	m_bBitmapLoaded=FALSE;
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC *pDC)
{
	CPalette *pPal;
	CPalette *pPalOld;
	HGLOBAL hDib;
	LPBITMAPINFO lpBi;
	DWORD dwBitOffset;

	if(m_bBitmapLoaded == FALSE)return;
	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	hDib=pDoc->GetHDib();
	ASSERT(hDib);
	lpBi=(LPBITMAPINFO)::GlobalLock(hDib);
	ASSERT(lpBi);
	pPal=pDoc->GetPalette();
	pPalOld=pDC->SelectPalette(pPal, FALSE);
	pDC->RealizePalette();
	dwBitOffset=
	(
		sizeof(BITMAPINFOHEADER)+
		pDoc->GetColorTableSize
		(
			lpBi->bmiHeader.biBitCount
		)*sizeof(RGBQUAD)
	);
	::SetDIBitsToDevice
	(
		pDC->GetSafeHdc(),
		0,
		0,
		lpBi->bmiHeader.biWidth,
		lpBi->bmiHeader.biHeight,
		0,
		0,
		0,
		lpBi->bmiHeader.biHeight,
		(LPSTR)lpBi+dwBitOffset,
		lpBi,
		DIB_RGB_COLORS
	);
	pDC->SelectPalette(pPalOld, FALSE);
	::GlobalUnlock(hDib);
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
	CScrollView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif

void CGDIView::OnInitialUpdate() 
{
	CGDIDoc *pDoc;
	CPalette *pPalDraw;
	LPBITMAPINFO lpBi;
	LPLOGPALETTE lpLogPal;
	int nSizeCT;
	int i;
	HGLOBAL hData;

	CScrollView::OnInitialUpdate();

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	hData=pDoc->GetHDib();
	if(hData != NULL)
	{
		lpBi=(LPBITMAPINFO)::GlobalLock(hData);
		ASSERT(lpBi);
		nSizeCT=pDoc->GetColorTableSize(lpBi->bmiHeader.biBitCount);

		lpLogPal=(LPLOGPALETTE) new BYTE
		[
			sizeof(LOGPALETTE)+(nSizeCT-1)*sizeof(PALETTEENTRY)
		];
		lpLogPal->palVersion=0x300;
		lpLogPal->palNumEntries=nSizeCT;
		for(i=0; i<nSizeCT; i++)
		{
			lpLogPal->palPalEntry[i].peRed=lpBi->bmiColors[i].rgbRed;
			lpLogPal->palPalEntry[i].peGreen=lpBi->bmiColors[i].rgbGreen;
			lpLogPal->palPalEntry[i].peBlue=lpBi->bmiColors[i].rgbBlue;
			lpLogPal->palPalEntry[i].peFlags=NULL;
		}

		pPalDraw=pDoc->GetPalette();
		if(pPalDraw->GetSafeHandle() != NULL)pPalDraw->DeleteObject();
		VERIFY(pPalDraw->CreatePalette(lpLogPal));
		delete [](BYTE *)lpLogPal;

		::GlobalUnlock(hData);
		m_bBitmapLoaded=TRUE;
		SetScrollSizes
		(
			MM_TEXT,
			CSize(lpBi->bmiHeader.biWidth, lpBi->bmiHeader.biHeight)
		);
		Invalidate();
	}
	else SetScrollSizes(MM_TEXT, CSize(0, 0));
}
