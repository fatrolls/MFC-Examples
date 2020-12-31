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
		if(pDC->IsPrinting())
		{
			CRect rcDest;
			int cxPage=pDC->GetDeviceCaps(HORZRES);
			int cyPage=pDC->GetDeviceCaps(VERTRES);
			int cxInch=pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch=pDC->GetDeviceCaps(LOGPIXELSY);
			rcDest.top=rcDest.left=0;
			rcDest.bottom=(int)
			(
				(
					(double)lpBi->bmiHeader.biHeight*cxPage*cyInch
				)/((double)lpBi->bmiHeader.biWidth*cxInch)
			);
			if(rcDest.bottom > cyPage)
			{
				rcDest.right=(int)
				(
					(
						(double)lpBi->bmiHeader.biWidth*cyPage*cxInch
					)/((double)lpBi->bmiHeader.biHeight*cyInch)
				);
				rcDest.bottom=cyPage;
			}
			else rcDest.right=cxPage;
			::StretchDIBits
			(
				pDC->GetSafeHdc(),
				rcDest.left,
				rcDest.top,
				rcDest.right,
				rcDest.bottom,
				0,
				0,
				lpBi->bmiHeader.biWidth,
				lpBi->bmiHeader.biHeight,
				(LPSTR)lpBi+dwBitOffset,
				lpBi,
				DIB_RGB_COLORS,
				SRCCOPY
			);
		}
		else
		{
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
		}
		pDC->SelectPalette(pPalOld, FALSE);
		::GlobalUnlock(hDib);
	}
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
