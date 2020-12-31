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
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	CBitmap bmp;

	m_pPalOld=NULL;
	m_pBmpOld=NULL;
	bmp.LoadBitmap(IDB_BITMAP_GRID);
	ASSERT(bmp.GetSafeHandle());
	m_brGrid.CreatePatternBrush(&bmp);
	ASSERT(m_brGrid.GetSafeHandle());
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC* pDC)
{
	CPalette *pPal;
	CPalette *pPalOld;
	BITMAP bm;
	int nRatio;
	POINT pt;

	if(m_bmpDraw.GetSafeHandle() == NULL)return;
	
	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pPal=pDoc->GetPalette();
	pPalOld=pDC->SelectPalette(pPal, FALSE);
	pDC->RealizePalette();
	nRatio=pDoc->GetRatio();

	pt=GetScrollPosition();

	m_bmpDraw.GetBitmap(&bm);
	pDC->StretchBlt
	(
		0, 0,
		bm.bmWidth*nRatio, bm.bmHeight*nRatio,
		&m_dcMem,
		0, 0,
		bm.bmWidth,	bm.bmHeight,
		SRCCOPY
	);
	if(pDoc->GetGridOn() == TRUE && nRatio > 2)
	{
		CBrush *pBrOld;
		CSize size;
		int i;

		size.cx=bm.bmWidth*nRatio;
		size.cy=bm.bmHeight*nRatio;

		m_brGrid.UnrealizeObject();
		pDC->SetBrushOrg(pt.x%2 ? 1:0, pt.y%2 ? 1:0);
		pBrOld=pDC->SelectObject(&m_brGrid);
		for(i=0; i<bm.bmWidth; i++)
		{
			pDC->PatBlt(i*nRatio, 0, 1, size.cy, PATCOPY);
		}
		for(i=0; i<bm.bmHeight; i++)
		{
			pDC->PatBlt(0, i*nRatio, size.cx, 1, PATCOPY);
		}
		pDC->SelectObject(pBrOld);
	}

	pDC->SelectPalette(pPalOld, FALSE);
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
	HGLOBAL hData;

	CScrollView::OnInitialUpdate();

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	hData=pDoc->GetHDib();
	if(hData != NULL)LoadBitmap(hData);
	else SetScrollSizes(MM_TEXT, CSize(0, 0));
}

void CGDIView::LoadBitmap(HGLOBAL hData)
{
	CPalette *pPalDraw;
	CPalette *pPalOld;
	CClientDC dc(this);
	HBITMAP hBmp;
	LPBYTE pBits;
	LPBITMAPINFO lpBi;
	LPLOGPALETTE lpLogPal;
	int nSizeCT;
	int i;
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	AfxGetApp()->DoWaitCursor(TRUE);
	nRatio=pDoc->GetRatio();
	lpBi=(LPBITMAPINFO)::GlobalLock(hData);
	ASSERT(lpBi);
	nSizeCT=pDoc->GetColorTableSize(lpBi->bmiHeader.biBitCount);
	pPalDraw=pDoc->GetPalette();
	if(nSizeCT != 0)
	{
		lpLogPal=(LPLOGPALETTE) new BYTE
		[
			sizeof(LOGPALETTE)+(nSizeCT-1)*sizeof(PALETTEENTRY)
		];
		for(i=0; i<nSizeCT; i++)
		{
			lpLogPal->palPalEntry[i].peRed=lpBi->bmiColors[i].rgbRed;
			lpLogPal->palPalEntry[i].peGreen=lpBi->bmiColors[i].rgbGreen;
			lpLogPal->palPalEntry[i].peBlue=lpBi->bmiColors[i].rgbBlue;
			lpLogPal->palPalEntry[i].peFlags=NULL;
		}
		pPalDraw->SetPaletteEntries(0, nSizeCT, lpLogPal->palPalEntry);
		delete [](BYTE *)lpLogPal;
		pPalOld=dc.SelectPalette(pPalDraw, FALSE);
		dc.RealizePalette();
	}

	CleanUp();
	hBmp=::CreateDIBSection
	(
		dc.GetSafeHdc(),
		lpBi,
		DIB_RGB_COLORS,
		(void **)&pBits,
		NULL,
		0
	);
	memcpy
	(
		(LPSTR)pBits,
		(LPSTR)lpBi+sizeof(BITMAPINFOHEADER)+nSizeCT*sizeof(RGBQUAD), 
		lpBi->bmiHeader.biSizeImage
	);
	ASSERT(hBmp);
	m_bmpDraw.Attach(hBmp);
	m_dcMem.CreateCompatibleDC(&dc);
	ASSERT(m_dcMem.GetSafeHdc());

	if(nSizeCT != 0)
	{
		m_pPalOld=m_dcMem.SelectPalette(pPalDraw, FALSE);
	}
	m_pBmpOld=m_dcMem.SelectObject(&m_bmpDraw);

	UpdateScrollSizes();
	::GlobalUnlock(hData);
	if(nSizeCT != 0)dc.SelectPalette(pPalOld, FALSE);

	Invalidate();
	AfxGetApp()->DoWaitCursor(FALSE);
}

void CGDIView::CleanUp()
{
	if(m_pPalOld != NULL)
	{
		m_dcMem.SelectPalette(m_pPalOld, FALSE);
		m_pPalOld=NULL;
	}
	if(m_pBmpOld != NULL)
	{
		m_dcMem.SelectObject(m_pBmpOld);
		m_pBmpOld=NULL;
	}
	if(m_dcMem.GetSafeHdc() != NULL)m_dcMem.DeleteDC();
	if(m_bmpDraw.GetSafeHandle() != NULL)m_bmpDraw.DeleteObject();
}

void CGDIView::OnDestroy() 
{
	CleanUp();
	CScrollView::OnDestroy();
}

void CGDIView::UpdateScrollSizes()
{
	BITMAP bm;
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	nRatio=pDoc->GetRatio();

	m_bmpDraw.GetBitmap(&bm);
	SetScrollSizes
	(
		MM_TEXT,
		CSize
		(
			bm.bmWidth*nRatio,
			bm.bmHeight*nRatio
		)
	);
}
