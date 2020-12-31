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
	ON_WM_ERASEBKGND()
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
	m_pBmpMaskOld=NULL;
	m_pBmpBSOld=NULL;
	m_pPalOld=NULL;
	m_pPalMaskOld=NULL;
	m_pPalBSOld=NULL;
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
	m_dcMemBS.BitBlt
	(
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		pDC,
		0,
		0,
		SRCCOPY
	);
	m_dcMemBS.BitBlt
	(
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		&m_dcMem,
		0,
		0,
		SRCINVERT
	);
	m_dcMemBS.BitBlt
	(
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		&m_dcMemMask,
		0,
		0,
		SRCAND
	);
	m_dcMemBS.BitBlt
	(
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		&m_dcMem,
		0,
		0,
		SRCINVERT
	);
	pDC->BitBlt
	(
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		&m_dcMemBS,
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
	BITMAP bm;

	if(m_bmpBkd.GetSafeHandle() == NULL)
	{
		m_bmpBkd.LoadBitmap(IDB_BITMAPBKD);
		m_bmpBkd.GetBitmap(&bm);
		m_bmpBkd.SetBitmapDimension(bm.bmWidth, bm.bmHeight);
		ASSERT(m_bmpBkd.GetSafeHandle());
	}
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
	int i, j;
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

	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMemMask.CreateCompatibleDC(&dc);
	m_dcMemBS.CreateCompatibleDC(&dc);
	ASSERT(m_dcMem.GetSafeHdc());
	ASSERT(m_dcMemMask.GetSafeHdc());
	ASSERT(m_dcMemBS.GetSafeHdc());

	if(nSizeCT != 0)
	{
		m_pPalOld=m_dcMem.SelectPalette(pPalDraw, FALSE);
		m_pPalMaskOld=m_dcMemMask.SelectPalette(pPalDraw, FALSE);
		m_pPalBSOld=m_dcMemBS.SelectPalette(pPalDraw, FALSE);
	}
	m_bmpMask.CreateCompatibleBitmap
	(
		&dc,
		lpBi->bmiHeader.biWidth,
		lpBi->bmiHeader.biHeight
	);
	m_bmpBS.CreateCompatibleBitmap
	(
		&dc,
		lpBi->bmiHeader.biWidth,
		lpBi->bmiHeader.biHeight
	);
	m_pBmpOld=m_dcMem.SelectObject(&m_bmpDraw);
	m_pBmpMaskOld=m_dcMemMask.SelectObject(&m_bmpMask);
	m_pBmpBSOld=m_dcMemBS.SelectObject(&m_bmpBS);
	for(j=0; j<lpBi->bmiHeader.biHeight; j++)
	{
		for(i=0; i<lpBi->bmiHeader.biWidth; i++)
		{
			if(m_dcMem.GetPixel(i, j) == RGB(255, 255, 255))
			{
				m_dcMemMask.SetPixel(i, j, RGB(255, 255, 255));
			}
			else m_dcMemMask.SetPixel(i, j, RGB(0, 0, 0));
		}
	}

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

BOOL CGDIView::OnEraseBkgnd(CDC* pDC) 
{
	CDC dcMem;
	CBitmap *pBmpOld;
	int i, j;
	int nRepX, nRepY;
	CRect rect;
	CSize size;
	CPoint pt;
	
	pt=GetScrollPosition();
	dcMem.CreateCompatibleDC(pDC);
	pBmpOld=dcMem.SelectObject(&m_bmpBkd);
	size=m_bmpBkd.GetBitmapDimension();
	GetClientRect(rect);
	rect.right+=pt.x;
	rect.bottom+=pt.y;
	nRepX=(rect.Width()+size.cx-1)/size.cx;
	nRepY=(rect.Height()+size.cy-1)/size.cy;
	for(i=0; i<nRepX; i++)
	{
		for(j=0; j<nRepY; j++)
		{
			pDC->BitBlt
			(
				i*size.cx-pt.x,
				j*size.cy-pt.y,
				size.cx,
				size.cy,
				&dcMem,
				0,
				0,
				SRCCOPY
			);
		}
	}
	dcMem.SelectObject(pBmpOld);
	return TRUE;
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
	if(m_pPalMaskOld != NULL)
	{
		m_dcMemMask.SelectPalette(m_pPalMaskOld, FALSE);
		m_pPalMaskOld=NULL;
	}
	if(m_pPalBSOld != NULL)
	{
		m_dcMemBS.SelectPalette(m_pPalBSOld, FALSE);
		m_pPalBSOld=NULL;
	}
	if(m_pBmpOld != NULL)
	{
		m_dcMem.SelectObject(m_pBmpOld);
		m_pBmpOld=NULL;
	}
	if(m_pBmpMaskOld != NULL)
	{
		m_dcMemMask.SelectObject(m_pBmpMaskOld);
		m_pBmpMaskOld=NULL;
	}
	if(m_pBmpBSOld != NULL)
	{
		m_dcMemBS.SelectObject(m_pBmpBSOld);
		m_pBmpBSOld=NULL;
	}
	if(m_dcMem.GetSafeHdc() != NULL)m_dcMem.DeleteDC();
	if(m_dcMemMask.GetSafeHdc() != NULL)m_dcMemMask.DeleteDC();
	if(m_dcMemBS.GetSafeHdc() != NULL)m_dcMemBS.DeleteDC();
	if(m_bmpDraw.GetSafeHandle() != NULL)m_bmpDraw.DeleteObject();
	if(m_bmpMask.GetSafeHandle() != NULL)m_bmpMask.DeleteObject();
	if(m_bmpBS.GetSafeHandle() != NULL)m_bmpBS.DeleteObject();
}