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
	m_bBitmapLoaded=FALSE;
	m_pBmpOld=NULL;
	m_pPalOld=NULL;
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
	BITMAP bm;

	if(m_bBitmapLoaded == FALSE)return;
	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pPal=pDoc->GetPalette();
	pPalOld=pDC->SelectPalette(pPal, FALSE);
	pDC->RealizePalette();
	
	m_bmpDraw.GetBitmap(&bm);
	pDC->BitBlt
	(
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		&m_dcMem,
		0,
		0,
		SRCCOPY
	);
	
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
	HBITMAP hBmpGray;
	LPBYTE pBits;
	LPBITMAPINFO lpBi;
	LPLOGPALETTE lpLogPal;
	int nSizeCT;
	int i;
	CGDIDoc *pDoc;

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	AfxGetApp()->DoWaitCursor(TRUE);
	lpBi=(LPBITMAPINFO)::GlobalLock(hData);
	ASSERT(lpBi);
	nSizeCT=pDoc->GetColorTableSize(lpBi->bmiHeader.biBitCount);
	pPalDraw=pDoc->GetPalette();
	if(pPalDraw->GetSafeHandle() != NULL)pPalDraw->DeleteObject();
	if(nSizeCT != 0)
	{
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

		VERIFY(pPalDraw->CreatePalette(lpLogPal));
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
	hBmpGray=CreateGrayedBitmap(&m_bmpDraw);
	ASSERT(hBmpGray);
	m_bmpDraw.DeleteObject();
	m_bmpDraw.Attach(hBmpGray);

	m_dcMem.CreateCompatibleDC(&dc);
	ASSERT(m_dcMem.GetSafeHdc());

	if(nSizeCT != 0)
	{
		m_pPalOld=m_dcMem.SelectPalette(pPalDraw, FALSE);
	}
	m_pBmpOld=m_dcMem.SelectObject(&m_bmpDraw);

	m_bBitmapLoaded=TRUE;
	SetScrollSizes
	(
		MM_TEXT,
		CSize(lpBi->bmiHeader.biWidth, lpBi->bmiHeader.biHeight)
	);
	::GlobalUnlock(hData);
	if(nSizeCT != 0)dc.SelectPalette(pPalOld, FALSE);

	Invalidate();
	AfxGetApp()->DoWaitCursor(FALSE);
}

void CGDIView::OnDestroy() 
{
	CleanUp();
	CScrollView::OnDestroy();
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

HBITMAP CGDIView::CreateGrayedBitmap(CBitmap *pBmp)
{
	BITMAP bm;
	CClientDC dc(this);
	CDC dcMono;
	CDC dcColor;
	CBitmap bmpShadow;
	CBitmap bmpHilight;
	CBitmap bmpGray;
	CBitmap *pBmpShadowOld;
	CBitmap *pBmpHilightOld;
	CBitmap *pBmpOld;
	CBrush brush;
	CBrush *pBrOld;

	dcMono.CreateCompatibleDC(&dc);
	dcColor.CreateCompatibleDC(&dc);
	ASSERT(dcMono.GetSafeHdc());
	ASSERT(dcColor.GetSafeHdc());
	pBmp->GetBitmap(&bm);
	bmpShadow.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	bmpHilight.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	bmpGray.CreateCompatibleBitmap(&dc, bm.bmWidth, bm.bmHeight);
	pBmpOld=dcColor.SelectObject(pBmp);

	pBmpShadowOld=dcMono.SelectObject(&bmpShadow);
	dcMono.FillSolidRect(0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));
    dcMono.BitBlt
	(
		0, 0,
		bm.bmWidth-1, bm.bmHeight-1,
        &dcColor,
		1, 1,
		SRCCOPY
	) ;
	dcMono.BitBlt
	(
		0, 0,
		bm.bmWidth, bm.bmHeight,
		&dcColor,
		0, 0,
		MERGEPAINT
	);
	dcMono.SelectObject(pBmpShadowOld);

	pBmpHilightOld=dcMono.SelectObject(&bmpHilight);
	dcMono.BitBlt
	(
		0, 0,
		bm.bmWidth, bm.bmHeight,
		&dcColor,
		0, 0,
		SRCCOPY
	);
	dcMono.BitBlt
	(
		0, 0,
		bm.bmWidth-1, bm.bmHeight-1,
		&dcColor,
		1, 1,
		MERGEPAINT
	);
	dcMono.SelectObject(pBmpHilightOld);

	dcColor.SelectObject(pBmpOld);

	pBmpOld=dcColor.SelectObject(&bmpGray);

	brush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE)) ;
	pBrOld=dcColor.SelectObject(&brush);
	dcColor.PatBlt
	(
		0, 0,
		bm.bmWidth, bm.bmHeight,
		PATCOPY
	);
	dcColor.SelectObject(pBrOld);
	brush.DeleteObject();
	dcColor.SetBkColor(RGB(255, 255, 255));
	dcColor.SetTextColor(RGB(0, 0, 0));

	brush.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
	pBrOld=dcColor.SelectObject(&brush);
	pBmpHilightOld=dcMono.SelectObject(&bmpHilight);
	dcColor.BitBlt
	(
		0, 0,
		bm.bmWidth, bm.bmHeight,
		&dcMono,
		0, 0,
		0x00B8074A
	);
	dcColor.SelectObject(pBrOld);
	brush.DeleteObject();
	dcMono.SelectObject(pBmpHilightOld);

	brush.CreateSolidBrush(::GetSysColor(COLOR_BTNSHADOW));
	pBrOld=dcColor.SelectObject(&brush);
	pBmpShadowOld=dcMono.SelectObject(&bmpShadow);
	dcColor.BitBlt
	(
		0, 0,
		bm.bmWidth, bm.bmHeight,
		&dcMono,
		0, 0,
		0x00B8074A
	);
	dcColor.SelectObject(pBrOld);
	brush.DeleteObject();
	dcMono.SelectObject(pBmpShadowOld);

	dcColor.SelectObject(pBmpOld);

	return (HBITMAP)bmpGray.Detach();
}
