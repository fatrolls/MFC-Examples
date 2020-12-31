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

	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pPal=pDoc->GetPalette();
	pPalOld=pDC->SelectPalette(pPal, FALSE);
	pDC->RealizePalette();
	pDC->StretchBlt
	(
		0,
		0,
		m_bmInfo.bmWidth,
		m_bmInfo.bmHeight,
		&m_dcMem,
		0,
		0,
		m_bmInfo.bmWidth,
		m_bmInfo.bmHeight,
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
	CClientDC dc(this);
	CGDIDoc *pDoc;
	CBitmap *pBmp;
	CPalette *pPalDraw;
	LPBITMAPINFO lpBi;
	LPLOGPALETTE lpLogPal;
	CPalette *pPalOld;
	int nSizeCT;
	int i;
	HBITMAP hBmp;
	HRSRC hRes;
	HGLOBAL hData;

	CScrollView::OnInitialUpdate();

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	if
	(
		(
			hRes=::FindResource
			(
				AfxGetResourceHandle(),
				MAKEINTRESOURCE(IDB_BITMAP),
				RT_BITMAP
			)
		) != NULL &&
		(
			hData=::LoadResource
			(
				AfxGetResourceHandle(),
				hRes
			)
		) != NULL
	)
	{
		lpBi=(LPBITMAPINFO)::LockResource(hData);
		ASSERT(lpBi);
		switch(lpBi->bmiHeader.biBitCount)
		{
			case 1:
			{
				nSizeCT=2;
				break;
			}
			case 4:
			{
				nSizeCT=16;
				break;
			}
			case 8:
			{
				nSizeCT=256;
				break;
			}
			default: nSizeCT=0;
		}

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
		pPalDraw->CreatePalette(lpLogPal);
		delete [](BYTE *)lpLogPal;

		pPalOld=dc.SelectPalette(pPalDraw, FALSE);
		dc.RealizePalette();
		hBmp=::CreateDIBitmap
		(
			dc.GetSafeHdc(),
			&lpBi->bmiHeader,
			CBM_INIT,
			(LPSTR)lpBi+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*nSizeCT,
			lpBi,
			DIB_RGB_COLORS
		);
		ASSERT(hBmp);
		dc.SelectPalette(pPalOld, FALSE);
		
		pBmp=pDoc->GetBitmap();
		pBmp->Attach(hBmp);
		pBmp->GetBitmap(&m_bmInfo);
		SetScrollSizes(MM_TEXT, CSize(m_bmInfo.bmWidth, m_bmInfo.bmHeight));
		m_dcMem.CreateCompatibleDC(&dc);
		m_pBmpMemOld=m_dcMem.SelectObject(pBmp);
		m_pPalMemOld=m_dcMem.SelectPalette(pPalDraw, FALSE);
		::FreeResource(hData);
	}
}

void CGDIView::OnDestroy() 
{
	m_dcMem.SelectPalette(m_pPalMemOld, FALSE);
	m_dcMem.SelectObject(m_pBmpMemOld);

	CScrollView::OnDestroy();
}
