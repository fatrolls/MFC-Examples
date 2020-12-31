#include "stdafx.h"
#include "GDI.h"
#include "MainFrm.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BMP_BKSTORE_SIZE_X		256
#define BMP_BKSTORE_SIZE_Y		256

IMPLEMENT_DYNCREATE(CGDIView, CScrollView)

BEGIN_MESSAGE_MAP(CGDIView, CScrollView)
	//{{AFX_MSG_MAP(CGDIView)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
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
	m_pBmpBKOld=NULL;
	m_pPalBKOld=NULL;
	
	bmp.LoadBitmap(IDB_BITMAP_GRID);
	ASSERT(bmp.GetSafeHandle());
	m_brGrid.CreatePatternBrush(&bmp);
	ASSERT(m_brGrid.GetSafeHandle());
	m_trackerSel.m_nStyle=
	(
		CRectTracker::dottedLine | CRectTracker::resizeOutside
	);
	m_penDot.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
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
	int i, j;
	int nRepX, nRepY;
	CSize size;
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
	size.cx=BMP_BKSTORE_SIZE_X/nRatio;
	size.cy=BMP_BKSTORE_SIZE_Y/nRatio;
	nRepX=(bm.bmWidth-1)/size.cx+1;
	nRepY=(bm.bmHeight-1)/size.cy+1;
	for(j=0; j<nRepY; j++)
	{
		for(i=0; i<nRepX; i++)
		{
			m_dcBKMem.StretchBlt
			(
				0, 0,
				BMP_BKSTORE_SIZE_X, BMP_BKSTORE_SIZE_Y,
				&m_dcMem,
				i*size.cx, j*size.cy,
				size.cx, size.cy,
				SRCCOPY
			);
			if(pDoc->GetGridOn() == TRUE && nRatio > 2)
			{
				CBrush *pBrOld;
				int i;

				m_brGrid.UnrealizeObject();
				pDC->SetBrushOrg(0, 0);
				pBrOld=m_dcBKMem.SelectObject(&m_brGrid);
				for(i=0; i<size.cx; i++)
				{
					m_dcBKMem.PatBlt(i*nRatio, 0, 1, nRatio*size.cy, PATCOPY);
				}
				for(i=0; i<size.cy; i++)
				{
					m_dcBKMem.PatBlt(0, i*nRatio, nRatio*size.cx, 1, PATCOPY);
				}
				m_dcBKMem.SelectObject(pBrOld);
			}
			pDC->BitBlt
			(
				i*size.cx*nRatio, 
				j*size.cy*nRatio,
				(
					(i+1)*size.cx*nRatio > bm.bmWidth*nRatio ? 
					(bm.bmWidth*nRatio-i*size.cx*nRatio):size.cx*nRatio
				),
				(
					(j+1)*size.cy*nRatio > bm.bmHeight*nRatio ?
					(bm.bmHeight*nRatio-j*size.cy*nRatio):size.cy*nRatio
				),
				&m_dcBKMem,
				0,
				0,
				SRCCOPY
			);
		}
	}
	if(!m_trackerSel.m_rect.IsRectEmpty())
	{
		CPoint ptScroll;

		ptScroll=GetScrollPosition();
		m_trackerSel.m_rect.OffsetRect(-ptScroll);
		m_trackerSel.Draw(pDC);
		m_trackerSel.m_rect.OffsetRect(ptScroll);
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
	CClientDC dc(this);
	CGDIDoc *pDoc;
	HGLOBAL hData;
	CPalette *pPalDraw;

	CScrollView::OnInitialUpdate();

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	if(m_dcBKMem.GetSafeHdc() == NULL)
	{
		pPalDraw=pDoc->GetPalette();
		ASSERT(pPalDraw->GetSafeHandle());
		m_dcBKMem.CreateCompatibleDC(&dc);
		m_pPalBKOld=m_dcBKMem.SelectPalette(pPalDraw, FALSE);
		m_bmpBKStore.CreateCompatibleBitmap
		(
			&dc, BMP_BKSTORE_SIZE_X, BMP_BKSTORE_SIZE_Y
		);
		m_pBmpBKOld=m_dcBKMem.SelectObject(&m_bmpBKStore);
	}

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
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->UpdateColorBar();
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
	pDoc->SetLPBits(pBits);
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
	if(m_pBmpBKOld != NULL)
	{
		m_dcBKMem.SelectObject(m_pBmpBKOld);
		m_pBmpBKOld=NULL;
	}
	if(m_pPalBKOld != NULL)
	{
		m_dcBKMem.SelectPalette(m_pPalBKOld, FALSE);
		m_pPalBKOld=NULL;
	}
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

void CGDIView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int nCurrentTool;
	CGDIDoc *pDoc;

	if(m_bmpDraw.GetSafeHandle() != NULL)
	{
		pDoc=(CGDIDoc *)GetDocument();
		nCurrentTool=pDoc->GetCurrentTool();
		SetCapture();
		m_ptMouseDown=NormalizePtPosition(point);
		switch(nCurrentTool)
		{
			case TOOL_FREESEL:
			{
				int nHitTest;

				nHitTest=m_trackerSel.HitTest(point);
				if(nHitTest == CRectTracker::hitNothing)
				{
					m_ptPrevious=point;

					if(m_rgnFreeSel.GetSafeHandle() != NULL)
					{
						m_rgnFreeSel.DeleteObject();
					}
					m_dcMem.MoveTo(m_ptMouseDown);
					m_dcMem.BeginPath();
				}
				else
				{
					int nCount;
					UINT i;
					LPRGNDATA lpRgnData;
					LPRECT lpRect;
					CRect rect;
					CRect rectOrgTracker;
					CRect rectCurTracker;
					CRgn rgn;

					::ReleaseCapture();
					m_trackerSel.Track(this, point);
					ResumeBackupBmp();

					m_rgnFreeSel.GetRgnBox(rectOrgTracker);
					rectCurTracker=NormalizeTrackerRect(m_trackerSel.m_rect);

					nCount=m_rgnFreeSel.GetRegionData(NULL, 0);
					lpRgnData=(LPRGNDATA)new BYTE[nCount];
					m_rgnFreeSel.GetRegionData(lpRgnData, nCount);
					lpRect=(LPRECT)lpRgnData->Buffer;
					for(i=0; i<lpRgnData->rdh.nCount; i++)
					{
						rect=*(lpRect+i);
						rect.OffsetRect(-rectOrgTracker.left, -rectOrgTracker.top);
						rect.left*=rectCurTracker.Width();
						rect.left/=rectOrgTracker.Width();
						rect.right*=rectCurTracker.Width();
						rect.right/=rectOrgTracker.Width();
						rect.top*=rectCurTracker.Height();
						rect.top/=rectOrgTracker.Height();
						rect.bottom*=rectCurTracker.Height();
						rect.bottom/=rectOrgTracker.Height();
						rect.OffsetRect(rectCurTracker.left, rectCurTracker.top);
						*(lpRect+i)=rect;
					}
					lpRgnData->rdh.rcBound=rectCurTracker;
					rgn.CreateFromData(NULL, nCount, lpRgnData);
					delete []lpRgnData;

					m_dcMem.SelectClipRgn(&rgn);
					StretchCopySelection();
					m_dcMem.SelectClipRgn(NULL);
					Invalidate();
				}
				break;
			}
			case TOOL_RECTSEL:
			{
				int nHitTest;

				nHitTest=m_trackerSel.HitTest(point);
				if(nHitTest == CRectTracker::hitNothing)
				{
					m_trackerSel.m_rect.left=m_trackerSel.m_rect.right=point.x+GetScrollPosition().x;
					m_trackerSel.m_rect.top=m_trackerSel.m_rect.bottom=point.y+GetScrollPosition().y;
				}
				else
				{
					::ReleaseCapture();
					m_trackerSel.Track(this, point);
					ResumeBackupBmp();
					StretchCopySelection();
					Invalidate();
				}
				break;
			}
			case TOOL_PEN:
			{
				DrawPoint(m_ptMouseDown);
				pDoc->SetModifiedFlag(TRUE);
				break;
			}
			case TOOL_LINE:
			{
				BackupCurrentBmp();
				DrawPoint(m_ptMouseDown);
				pDoc->SetModifiedFlag(TRUE);
				break;
			}
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CGDIView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int nCurrentTool;
	CGDIDoc *pDoc;
	CPoint pt;

	if(m_bmpDraw.GetSafeHandle() != NULL)
	{
		pDoc=(CGDIDoc *)GetDocument();
		nCurrentTool=pDoc->GetCurrentTool();
		::ReleaseCapture();
		pt=NormalizePtPosition(point);
		switch(nCurrentTool)
		{
			case TOOL_FREESEL:
			{
				CClientDC dc(this);
				CPen *pPenOld;
				CRect rect;

				pPenOld=dc.SelectObject(&m_penDot);
				dc.MoveTo(m_ptPrevious);
				dc.LineTo(point);
				dc.SelectObject(pPenOld);
				m_dcMem.LineTo(pt);
				m_dcMem.CloseFigure();
				m_dcMem.EndPath();
				m_rgnFreeSel.CreateFromPath(&m_dcMem);
				m_rgnFreeSel.GetRgnBox(rect);
				m_trackerSel.m_rect=UnnormalizeTrackerRect(rect);
				BackupCurrentBmp();
				BackupSelection();
				Invalidate(FALSE);
				break;
			}
			case TOOL_RECTSEL:
			{
				CClientDC dc(this);

				if(!m_trackerSel.m_rect.IsRectEmpty())
				{
					dc.DrawFocusRect(m_trackerSel.m_rect);
				}
				m_trackerSel.m_rect.right=point.x+GetScrollPosition().x;
				m_trackerSel.m_rect.bottom=point.y+GetScrollPosition().y;
				BackupCurrentBmp();
				BackupSelection();
				Invalidate(FALSE);
				break;
			}
			case TOOL_PEN:
			{
				if(pt != m_ptMouseDown)
				{
					DrawPoint(point);
					pDoc->SetModifiedFlag(TRUE);
				}
				break;
			}
			case TOOL_LINE:
			{
				ResumeBackupBmp();
				DrawLine(m_ptMouseDown, pt);
				break;
			}
		}
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CGDIView::OnMouseMove(UINT nFlags, CPoint point) 
{
	int nCurrentTool;
	CGDIDoc *pDoc;
	CPoint pt;

	if(m_bmpDraw.GetSafeHandle() != NULL)
	{
		pDoc=(CGDIDoc *)GetDocument();
		nCurrentTool=pDoc->GetCurrentTool();
		pt=NormalizePtPosition(point);
		switch(nCurrentTool)
		{
			case TOOL_FREESEL:
			{
				if(nFlags & MK_LBUTTON)
				{
					CClientDC dc(this);
					CPen *pPenOld;

					pPenOld=dc.SelectObject(&m_penDot);
					dc.MoveTo(m_ptPrevious);
					dc.LineTo(point);
					m_ptPrevious=point;
					dc.SelectObject(pPenOld);
					m_dcMem.LineTo(pt);
				}
				break;
			}
			case TOOL_RECTSEL:
			{
				if(nFlags & MK_LBUTTON)
				{
					CClientDC dc(this);

					if(!m_trackerSel.m_rect.IsRectEmpty())
					{
						dc.DrawFocusRect(m_trackerSel.m_rect);
					}
					m_trackerSel.m_rect.right=point.x;
					m_trackerSel.m_rect.bottom=point.y;
					if(!m_trackerSel.m_rect.IsRectEmpty())
					{
						dc.DrawFocusRect(m_trackerSel.m_rect);
					}
				}
				break;
			}
			case TOOL_PEN:
			{
				if(nFlags & MK_LBUTTON)
				{
					if(pt != m_ptMouseDown)
					{
						DrawPoint(point);
						pDoc->SetModifiedFlag(TRUE);
					}
				}
				break;
			}
			case TOOL_LINE:
			{
				if(nFlags & MK_LBUTTON)
				{
					ResumeBackupBmp();
					DrawLine(m_ptMouseDown, pt);
				}
				break;
			}
		}
	}
	CScrollView::OnMouseMove(nFlags, point);
}

CPoint CGDIView::NormalizePtPosition(CPoint pt)
{
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	nRatio=pDoc->GetRatio();
	pt.Offset(GetScrollPosition());

	return CPoint(pt.x/nRatio, pt.y/nRatio);
}

void CGDIView::DrawPoint(CPoint pt)
{
	int nPalIndex;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	nPalIndex=pDoc->GetFgdIndex();
	m_dcMem.SetPixel(pt, PALETTEINDEX(nPalIndex));
	Invalidate(FALSE);
}

void CGDIView::DrawLine(CPoint ptStart, CPoint ptEnd)
{
	int nPalIndex;
	CGDIDoc *pDoc;
	CPen pen;
	CPen *pPenOld;

	pDoc=(CGDIDoc *)GetDocument();
	nPalIndex=pDoc->GetFgdIndex();
	pen.CreatePen(PS_SOLID, 1, PALETTEINDEX(nPalIndex));
	pPenOld=m_dcMem.SelectObject(&pen);
	m_dcMem.MoveTo(ptStart);
	m_dcMem.LineTo(ptEnd);
	m_dcMem.SelectObject(pPenOld);
	Invalidate(FALSE);
}

void CGDIView::BackupSelection()
{
	CDC dcMem;
	CPalette *pPalOld;
	CPalette *pPal;
	CGDIDoc *pDoc;
	BITMAP bm;
	CBitmap *pBmpOld;
	CRect rect;
	int nBgdIndex;

	if(m_bmpSelBackup.GetSafeHandle() != NULL)m_bmpSelBackup.DeleteObject();
	pDoc=(CGDIDoc *)GetDocument();
	pPal=pDoc->GetPalette();
	ASSERT(pPal->GetSafeHandle());
	nBgdIndex=pDoc->GetBgdIndex();
	dcMem.CreateCompatibleDC(&m_dcMem);
	pPalOld=dcMem.SelectPalette(pPal, FALSE);

	rect=NormalizeTrackerRect(m_trackerSel.m_rect);
	m_bmpDraw.GetBitmap(&bm);
	m_bmpSelBackup.CreateCompatibleBitmap(&m_dcMem, rect.Width(), rect.Height());
	pBmpOld=dcMem.SelectObject(&m_bmpSelBackup);
	dcMem.FillSolidRect(0, 0, rect.Width(), rect.Height(), PALETTEINDEX(nBgdIndex));
	if(rect.left < 0)rect.left=0;
	if(rect.top < 0)rect.top=0;
	if(rect.right >= bm.bmWidth)rect.right=bm.bmWidth-1;
	if(rect.bottom >= bm.bmHeight)rect.bottom=bm.bmHeight-1;
	dcMem.BitBlt
	(
		0, 0,
		rect.Width(), rect.Height(),
		&m_dcMem,
		rect.left, rect.top,
		SRCCOPY
	);

	dcMem.SelectObject(pBmpOld);
	dcMem.SelectPalette(pPal, FALSE);
}

void CGDIView::StretchCopySelection()
{
	CDC dcMem;
	CPalette *pPalOld;
	CPalette *pPal;
	CGDIDoc *pDoc;
	BITMAP bm;
	CBitmap *pBmpOld;
	CRect rect;

	if(m_bmpSelBackup.GetSafeHandle() == NULL)return;

	pDoc=(CGDIDoc *)GetDocument();
	pPal=pDoc->GetPalette();
	ASSERT(pPal->GetSafeHandle());
	dcMem.CreateCompatibleDC(&m_dcMem);
	pPalOld=dcMem.SelectPalette(pPal, FALSE);

	rect=NormalizeTrackerRect(m_trackerSel.m_rect);
	m_bmpSelBackup.GetBitmap(&bm);
	pBmpOld=dcMem.SelectObject(&m_bmpSelBackup);
	m_dcMem.StretchBlt
	(
		rect.left, rect.top,
		rect.Width(), rect.Height(),
		&dcMem,
		0, 0,
		bm.bmWidth, bm.bmHeight,
		SRCCOPY
	);
	dcMem.SelectObject(pBmpOld);
	dcMem.SelectPalette(pPal, FALSE);
}

void CGDIView::BackupCurrentBmp()
{
	CDC dcMem;
	CPalette *pPalOld;
	CPalette *pPal;
	CGDIDoc *pDoc;
	BITMAP bm;
	CBitmap *pBmpOld;

	if(m_bmpBackup.GetSafeHandle() != NULL)m_bmpBackup.DeleteObject();
	pDoc=(CGDIDoc *)GetDocument();
	pPal=pDoc->GetPalette();
	ASSERT(pPal->GetSafeHandle());
	dcMem.CreateCompatibleDC(&m_dcMem);
	pPalOld=dcMem.SelectPalette(pPal, FALSE);

	m_bmpDraw.GetBitmap(&bm);
	m_bmpBackup.CreateCompatibleBitmap(&m_dcMem, bm.bmWidth, bm.bmHeight);
	pBmpOld=dcMem.SelectObject(&m_bmpBackup);
	dcMem.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &m_dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pBmpOld);
	dcMem.SelectPalette(pPal, FALSE);
}

void CGDIView::ResumeBackupBmp()
{
	CDC dcMem;
	CPalette *pPalOld;
	CPalette *pPal;
	CGDIDoc *pDoc;
	BITMAP bm;
	CBitmap *pBmpOld;

	ASSERT(m_bmpBackup.GetSafeHandle() != NULL);
	pDoc=(CGDIDoc *)GetDocument();
	pPal=pDoc->GetPalette();
	ASSERT(pPal->GetSafeHandle());
	dcMem.CreateCompatibleDC(&m_dcMem);
	pPalOld=dcMem.SelectPalette(pPal, FALSE);

	m_bmpDraw.GetBitmap(&bm);
	pBmpOld=dcMem.SelectObject(&m_bmpBackup);
	m_dcMem.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pBmpOld);
	dcMem.SelectPalette(pPalOld, FALSE);
}

BOOL CGDIView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_bmpDraw.GetSafeHandle() != NULL)
	{
		if
		(
			!(
				m_trackerSel.m_rect.IsRectEmpty() != TRUE && 
				m_trackerSel.SetCursor(this, nHitTest) == TRUE
			)
		)
		{
			if
			(
				MouseWithinBitmap() == TRUE && 
				HTVSCROLL != nHitTest && HTHSCROLL != nHitTest
			)
			{
				
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
				return TRUE;
			}
		}
		else return TRUE;
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CGDIView::MouseWithinBitmap()
{
	CPoint point;
	CPoint ptScroll;
	CRect rect;
	CRect rectBmp;
	BITMAP bm;
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	nRatio=pDoc->GetRatio();
	ptScroll=GetScrollPosition();
	::GetCursorPos(&point);
	GetWindowRect(rect);
	point.Offset(-rect.left, -rect.top);
	point.Offset(ptScroll);

	ASSERT(m_bmpDraw.GetSafeHandle());
	m_bmpDraw.GetBitmap(&bm);
	rectBmp=CRect(0, 0, bm.bmWidth*nRatio, bm.bmHeight*nRatio);

	return rectBmp.PtInRect(point);
}

void CGDIView::ResetTracker()
{
	m_trackerSel.m_rect=CRect(0, 0, 0, 0);
}

CRect CGDIView::NormalizeTrackerRect(CRect rect)
{
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	nRatio=pDoc->GetRatio();

	rect.NormalizeRect();
	rect.left/=nRatio;
	rect.top/=nRatio;
	rect.right/=nRatio;
	rect.bottom/=nRatio;
	return rect;
}

CRect CGDIView::UnnormalizeTrackerRect(CRect rect)
{
	CPoint pt;
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	nRatio=pDoc->GetRatio();

	pt=GetScrollPosition();
	rect.left*=nRatio;
	rect.top*=nRatio;
	rect.right*=nRatio;
	rect.bottom*=nRatio;
	rect.OffsetRect(pt);
	return rect;
}

void CGDIView::GetCurrentBitmapInfoHeader(LPBITMAPINFOHEADER lpBi)
{
	BITMAP bm;

	ASSERT(m_bmpDraw.GetSafeHandle() != NULL);
	ASSERT(lpBi != NULL);
	memset((LPSTR)lpBi, 0, sizeof(BITMAPINFOHEADER));
	m_bmpDraw.GetBitmap(&bm);
	lpBi->biSize=sizeof(BITMAPINFOHEADER);
	lpBi->biWidth=bm.bmWidth;
	lpBi->biHeight=bm.bmHeight;
	lpBi->biPlanes=1;
	lpBi->biBitCount=bm.bmBitsPixel;
	lpBi->biCompression=BI_RGB;
	lpBi->biSizeImage=WIDTHBYTES(lpBi->biBitCount*lpBi->biWidth)*lpBi->biHeight;
}

void CGDIView::FillSelectionWithBgdColor()
{
	CPalette *pPalOld;
	CPalette *pPal;
	CGDIDoc *pDoc;

	pDoc=(CGDIDoc *)GetDocument();
	pPal=pDoc->GetPalette();
	ASSERT(pPal->GetSafeHandle());
	pPalOld=m_dcMem.SelectPalette(pPal, FALSE);
	m_dcMem.FillSolidRect
	(
		m_trackerSel.m_rect,
		PALETTEINDEX(pDoc->GetBgdIndex())
	);
	m_dcMem.SelectPalette(pPalOld, FALSE);
}

void CGDIView::ChangeTrackerRectRatio(int nNewRatio)
{
	CRect rect;

	if(!m_trackerSel.m_rect.IsRectEmpty())
	{
		rect=NormalizeTrackerRect(m_trackerSel.m_rect);
		rect.left*=nNewRatio;
		rect.top*=nNewRatio;
		rect.right*=nNewRatio;
		rect.bottom*=nNewRatio;
		m_trackerSel.m_rect=rect;
	}
}

void CGDIView::PasteDIB(HGLOBAL hData)
{
	CClientDC dc(this);
	LPBITMAPINFO lpBi;
	int nRatio;
	CGDIDoc *pDoc;

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	AfxGetApp()->DoWaitCursor(TRUE);
	lpBi=(LPBITMAPINFO)::GlobalLock(hData);
	ASSERT(lpBi);
	if(lpBi->bmiHeader.biBitCount != 8)
	{
		::GlobalUnlock(hData);
		return;
	}

	nRatio=pDoc->GetRatio();

	if(m_bmpSelBackup.GetSafeHandle() != NULL)m_bmpSelBackup.DeleteObject();
	m_bmpSelBackup.CreateCompatibleBitmap
	(
		&dc,
		lpBi->bmiHeader.biWidth,
		lpBi->bmiHeader.biHeight
	);
	::SetDIBits
	(
		dc.GetSafeHdc(),
		(HBITMAP)m_bmpSelBackup.GetSafeHandle(),
		0,
		lpBi->bmiHeader.biHeight,
		(LPVOID)
		(
			(LPSTR)lpBi+
			sizeof(BITMAPINFOHEADER)+
			pDoc->GetColorTableSize
			(
				lpBi->bmiHeader.biBitCount
			)*sizeof(RGBQUAD)
		),
		lpBi,
		DIB_RGB_COLORS
	);
	m_trackerSel.m_rect=CRect
	(
		0, 
		0, 
		nRatio*lpBi->bmiHeader.biWidth,
		nRatio*lpBi->bmiHeader.biHeight
	);
	BackupCurrentBmp();
	StretchCopySelection();
	Invalidate();
	::GlobalUnlock(hData);
	((CMainFrame *)(AfxGetApp()->m_pMainWnd))->SendMessage
	(
		WM_COMMAND, ID_BUTTON_RECTSEL, 0
	);
	AfxGetApp()->DoWaitCursor(FALSE);
}
