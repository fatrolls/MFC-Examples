#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_CAPTURE		500

IMPLEMENT_DYNCREATE(CGDIView, CScrollView)

BEGIN_MESSAGE_MAP(CGDIView, CScrollView)
	//{{AFX_MSG_MAP(CGDIView)
	ON_WM_TIMER()
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
	HGLOBAL hDib;
	CPalette *pPal;
	CPalette *pPalOld;
	LPBITMAPINFO lpBi;
	DWORD dwBitOffset;

	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	hDib=pDoc->GetHDib();
	if(hDib != NULL)
	{
		lpBi=(LPBITMAPINFO)::GlobalLock(hDib);
		ASSERT(lpBi);
		pPal=pDoc->GetPalette();
		ASSERT(pPal->GetSafeHandle());
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
}

BOOL CGDIView::OnPreparePrinting(CPrintInfo *pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CGDIView::OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)
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

void CGDIView::PrepareCapture()
{
	SetTimer(TIMER_CAPTURE, 2000, NULL);
}
void CGDIView::Capture()
{
	CRect rect;
	CBitmap bmpCap;
	CBitmap *pBmpOld;
	CWindowDC dc(CWnd::GetDesktopWindow());
	CDC dcMem;
	CGDIDoc *pDoc;
	CWnd *pWnd;
	HWND hWnd;

	pDoc=(CGDIDoc *)GetDocument();
	hWnd=pDoc->GetSelectedWnd();
	if(pWnd == NULL || ::IsWindow(hWnd) == FALSE)
	{
		(CWnd::GetDesktopWindow())->GetClientRect(rect);
	}
	else
	{
		pWnd=CWnd::FromHandle(hWnd);
		pWnd->GetWindowRect(rect);
	}
	dcMem.CreateCompatibleDC(&dc);
	bmpCap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pBmpOld=dcMem.SelectObject(&bmpCap);

	dcMem.BitBlt
	(
		0, 0,
		rect.Width(), rect.Height(),
		&dc,
		rect.left, rect.top,
		SRCCOPY
	);
	((CGDIDoc *)GetDocument())->GetCaptureBitmap(&bmpCap);
	SetScrollSizes(MM_TEXT, CSize(rect.Width(), rect.Height()));
	dcMem.SelectObject(pBmpOld);
}

void CGDIView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_CAPTURE)
	{
		KillTimer(TIMER_CAPTURE);
		Capture();
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_RESTORE);
		Invalidate();
	}
	CScrollView::OnTimer(nIDEvent);
}

void CGDIView::OnInitialUpdate() 
{
	SetScrollSizes(MM_TEXT, CSize(0, 0));
	CScrollView::OnInitialUpdate();
}

void CGDIView::OnPrint(CDC *pDC, CPrintInfo *pInfo) 
{
	HGLOBAL hDib;
	CPalette *pPal;
	CPalette *pPalOld;
	LPBITMAPINFO lpBi;
	DWORD dwBitOffset;
	int nMapMode;
	int nRepX, nRepY;
	int u, v;
	CPoint ptOrg;
	CSize size;
	CRect rect;
	CRect rectDC;

	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	hDib=pDoc->GetHDib();
	if(hDib != NULL)
	{
		nMapMode=pDC->SetMapMode(MM_LOMETRIC);
		rectDC=pInfo->m_rectDraw;
		pDC->DPtoLP(rectDC);

		lpBi=(LPBITMAPINFO)::GlobalLock(hDib);
		ASSERT(lpBi);
		pPal=pDoc->GetPalette();
		ASSERT(pPal->GetSafeHandle());
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

		nRepX=(lpBi->bmiHeader.biWidth-1)/abs(rectDC.Width())+1;
		nRepY=(lpBi->bmiHeader.biHeight-1)/abs(rectDC.Height())+1;
		
		u=(pInfo->m_nCurPage-1)%nRepX;
		v=(pInfo->m_nCurPage-1)/nRepX;
		rect.left=u*abs(rectDC.Width());
		rect.top=v*abs(rectDC.Height());
		if(u == nRepX-1)
		{
			rect.right=
			(
				rect.left+
				abs(rectDC.Width())-
				(nRepX*abs(rectDC.Width())-lpBi->bmiHeader.biWidth)
			);
		}
		else rect.right=rect.left+abs(rectDC.Width());
		if(v == nRepY-1)
		{
			rect.bottom=
			(
				rect.top+
				abs(rectDC.Height())-
				(nRepY*abs(rectDC.Height())-lpBi->bmiHeader.biHeight)
			);
		}
		else rect.bottom=rect.top+abs(rectDC.Height());

		::StretchDIBits
		(
			pDC->GetSafeHdc(),
			0,
			-rect.Height()+1,
			rect.Width(),
			rect.Height(),
			rect.left,
			lpBi->bmiHeader.biHeight-rect.top-1,
			rect.Width(),
			-rect.Height(),
			(LPSTR)lpBi+dwBitOffset,
			lpBi,
			DIB_RGB_COLORS,
			SRCCOPY
		);

		pDC->SelectPalette(pPalOld, FALSE);
		::GlobalUnlock(hDib);
		pDC->SetMapMode(nMapMode);
	}
}

void CGDIView::OnPrepareDC(CDC *pDC, CPrintInfo *pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	if(pInfo != NULL)
	{
		int nMapMode;
		int nNumPages;
		HGLOBAL hDib;
		CRect rect;
		CSize size;
		LPBITMAPINFO lpBi;
		
		nMapMode=pDC->SetMapMode(MM_LOMETRIC);

		CGDIDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);

		hDib=pDoc->GetHDib();
		if(hDib != NULL)
		{
			lpBi=(LPBITMAPINFO)::GlobalLock(hDib);
			ASSERT(lpBi);
			size.cx=lpBi->bmiHeader.biWidth;
			size.cy=lpBi->bmiHeader.biHeight;
			rect.left=rect.top=0;
			rect.right=pDC->GetDeviceCaps(HORZRES);
			rect.bottom=pDC->GetDeviceCaps(VERTRES);
			pDC->DPtoLP(rect);
			nNumPages=((size.cx-1)/abs(rect.Width())+1)*((size.cy-1)/abs(rect.Height())+1);
			pInfo->SetMaxPage(nNumPages);
			::GlobalUnlock(hDib);
		}
		pDC->SetMapMode(nMapMode);
	}
}
