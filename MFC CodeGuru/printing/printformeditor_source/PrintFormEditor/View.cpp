// View.cpp : implementation of the View class
//

#include "stdafx.h"
#include "PrintFormEditor.h"

#include "Doc.h"
#include "View.h"

#include "MainFrm.h"

#include "PagerSizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// View

IMPLEMENT_DYNCREATE(View, CView)

BEGIN_MESSAGE_MAP(View, CView)
	//{{AFX_MSG_MAP(View)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_TOOL_ARROW, OnToolArrow)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_ARROW, OnUpdateToolArrow)
	ON_COMMAND(IDC_TOOL_BORDER, OnToolBorder)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_BORDER, OnUpdateToolBorder)
	ON_COMMAND(IDC_TOOL_CHECK, OnToolCheck)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_CHECK, OnUpdateToolCheck)
	ON_COMMAND(IDC_TOOL_EDIT, OnToolEdit)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_EDIT, OnUpdateToolEdit)
	ON_COMMAND(IDC_TOOL_IMAGE, OnToolImage)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_IMAGE, OnUpdateToolImage)
	ON_COMMAND(IDC_TOOL_LINE, OnToolLine)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_LINE, OnUpdateToolLine)
	ON_COMMAND(IDC_TOOL_RADIO, OnToolRadio)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_RADIO, OnUpdateToolRadio)
	ON_COMMAND(IDC_TOOL_RECT, OnToolRect)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_RECT, OnUpdateToolRect)
	ON_COMMAND(IDC_TOOL_SOTTOREPORT, OnToolSottoreport)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_SOTTOREPORT, OnUpdateToolSottoreport)
	ON_COMMAND(IDC_TOOL_STATIC, OnToolStatic)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_STATIC, OnUpdateToolStatic)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(IDC_TOOL_VLINE, OnToolVline)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_VLINE, OnUpdateToolVline)
	ON_COMMAND(IDC_TOOL_HLINE, OnToolHline)
	ON_UPDATE_COMMAND_UI(IDC_TOOL_HLINE, OnUpdateToolHline)
	ON_COMMAND(IDC_PAPER_SIZE, OnPaperSize)
	ON_COMMAND(IDC_PROPERTY, OnProperty)
	ON_UPDATE_COMMAND_UI(IDC_PROPERTY, OnUpdateProperty)
	ON_COMMAND(ID_GFX_PROPERTY, OnGfxProperty)
	ON_UPDATE_COMMAND_UI(ID_GFX_PROPERTY, OnUpdateGfxProperty)
	ON_WM_DESTROY()
	ON_COMMAND(ID_ALIGN_BOTTOM, OnAlignBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BOTTOM, OnUpdateAlignBottom)
	ON_COMMAND(ID_ALIGN_LEFT, OnAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_LEFT, OnUpdateAlignLeft)
	ON_COMMAND(ID_ALIGN_RIGHT, OnAlignRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_RIGHT, OnUpdateAlignRight)
	ON_COMMAND(ID_ALIGN_TOP, OnAlignTop)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_TOP, OnUpdateAlignTop)
	ON_COMMAND(ID_SIZE_ALL, OnSizeAll)
	ON_UPDATE_COMMAND_UI(ID_SIZE_ALL, OnUpdateSizeAll)
	ON_COMMAND(ID_SIZE_HORZ, OnSizeHorz)
	ON_UPDATE_COMMAND_UI(ID_SIZE_HORZ, OnUpdateSizeHorz)
	ON_COMMAND(ID_SIZE_VERT, OnSizeVert)
	ON_UPDATE_COMMAND_UI(ID_SIZE_VERT, OnUpdateSizeVert)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// View construction/destruction

View::View()
{
	iScy = GetSystemMetrics(SM_CYVTHUMB);
	iScx = GetSystemMetrics(SM_CXHTHUMB);
	iRx = 18;
	iRy = 18;

	pGridPen1 = new CPen(PS_SOLID, 1, RGB(192,192,192));
	pGridPen2 = new CPen(PS_DASHDOT, 1, RGB(192,192,192));

	cr3dFace = GetSysColor(COLOR_3DFACE);

	iType = -1;
	pTracker = NULL;
	iGridStep = 50;
	iDiv = 2;

}

View::~View()
{
	if (pGridPen1) delete pGridPen1;
	if (pGridPen2) delete pGridPen2;
	if (pTracker)  delete pTracker;
}

BOOL View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// View drawing

void View::OnDraw(CDC* pDC)
{
	Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int x = wndHBar.GetSafeHwnd() ? wndHBar.GetScrollPos() : 0;
	int y = wndVBar.GetSafeHwnd() ? wndVBar.GetScrollPos() : 0;

	CRect rc;
	GetClientRect(rc);

	CDC MemDC, *origDc = pDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	CBitmap * obm = MemDC.SelectObject(&bmp);

	pDC = &MemDC;

	int idcs = pDC->SaveDC();

	CRgn rgn;
	CRect rc1(rc);
	rc1.left += iRx + 2;
	rc1.top  += iRy + 2;
	rc1.bottom -= iScy;
	rc1.right  -= iScx;

	CRect bdrRc1(rc);

	bdrRc1.left += iRx;
	bdrRc1.top  += iRy;
	bdrRc1.right = bdrRc1.left + 2;
	bdrRc1.bottom -= iScy;

	pDC->FillSolidRect(bdrRc1, cr3dFace);

	bdrRc1 = rc;

	bdrRc1.left += iRx;
	bdrRc1.top  += iRy;
	bdrRc1.right-= iScx;
	bdrRc1.bottom = bdrRc1.top + 2;

	pDC->FillSolidRect(bdrRc1, cr3dFace);

	
	rgn.CreateRectRgnIndirect(&rc1);
	pDC->SelectClipRgn(&rgn);
	rgn.DeleteObject();

	int maxx = rc.Width();
	int maxy = rc.Height();
	if (pDoc->rcPaper.Width() / iDiv  + iRx < maxx) maxx = pDoc->rcPaper.Width() / iDiv + iRx ;
	if (pDoc->rcPaper.Height() / iDiv + iRy < maxy) maxy = pDoc->rcPaper.Height() / iDiv + iRy;

	CRect rcx(rc1.left, rc1.top, maxx, maxy);
	
	pDC->FillSolidRect(rc1, cr3dFace);
	pDC->FillSolidRect(rcx, GetSysColor(COLOR_WINDOW));

	int t;

	CPen * op = pDC->SelectObject(pGridPen1);

	for (t = iRx; t <= pDoc->rcPaper.Width() / iDiv; t += 100 / iDiv)
	{
		if (t - x > 0 && t - x < rc.right)
		{
			pDC->MoveTo(t - x, rc.top);
			pDC->LineTo(t - x, maxy);
		}
		if (t - x > rc.right) break;
	}
	for (t = iRy; t <= pDoc->rcPaper.Height() / iDiv; t += 100 / iDiv)
	{
		if (t - y > 0 && t - y < rc.bottom)
		{
			pDC->MoveTo(rc.left, t - y);
			pDC->LineTo(maxx, t - y);
		}
		if (t - y > rc.bottom) break;
	}

	pDC->SelectObject(pGridPen2);

	for (t = iRx + 50 / iDiv; t <= pDoc->rcPaper.Width() / iDiv; t += 100 / iDiv)
	{
		if (t - x > 0 && t - x < rc.right)
		{
			pDC->MoveTo(t - x, rc.top);
			pDC->LineTo(t - x, maxy);
		}
		if (t - x > rc.right) break;
	}
	for (t = iRy + 50 / iDiv; t <= pDoc->rcPaper.Height() / iDiv; t += 100 / iDiv)
	{
		if (t - y > 0 && t - y < rc.bottom)
		{
			pDC->MoveTo(rc.left, t - y);
			pDC->LineTo(maxx, t - y);
		}
		if (t - y > rc.bottom) break;
	}

	for (t = 0; t < pDoc->iFormObj; t++)
	{
		pDoc->ppObjs[t]->Draw(pDC, x - iRx - 2, y - iRy - 2, iDiv);
	}

	pDC->SelectObject(op);
	pDC->RestoreDC(idcs);

	origDc->BitBlt(rc1.left-2,rc1.top-2,rc1.Width()+2,rc1.Height()+2,&MemDC,rc1.left-2,rc1.top-2,SRCCOPY);
	pDC = origDc;
	MemDC.SelectObject(obm);


	pDC->FillSolidRect(CRect(0,0,iRx,iRy), cr3dFace);
	pDC->Draw3dRect(CRect(2,2,iRx-2,iRy-2), GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHIGHLIGHT));
	pDC->Draw3dRect(CRect(3,3,iRx-3,iRy-3), GetSysColor(COLOR_3DHIGHLIGHT), GetSysColor(COLOR_3DSHADOW));
	pDC->FillSolidRect(CRect(7,7,iRx-7,iRy-7), RGB(0,0,0));

	pDC->FillSolidRect(CRect(rc.right - iScx,rc.bottom - iScy,rc.right,rc.bottom), cr3dFace);

	pDC->DrawFrameControl(CRect(rc.right - iScx,rc.bottom - iScy,rc.right,rc.bottom), DFC_SCROLL, DFCS_SCROLLSIZEGRIP);

}

/////////////////////////////////////////////////////////////////////////////
// View printing

BOOL View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation

	return DoPreparePrinting(pInfo);
}

void View::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	pDC->SetMapMode(MM_LOMETRIC);
}

void View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	Doc* pDoc = GetDocument();

	pDC->SetMapMode(MM_LOMETRIC);

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		pDoc->ppObjs[t]->Print(pDC, pDoc->rcPaper.TopLeft());
	}
	
//	CView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// View diagnostics

#ifdef _DEBUG
void View::AssertValid() const
{
	CView::AssertValid();
}

void View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Doc* View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Doc)));
	return (Doc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// View message handlers

void View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	ModifyStyle(0, WS_CLIPCHILDREN);
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0/*WS_EX_STATICEDGE*/, SWP_FRAMECHANGED);

	CRect rc;
	GetClientRect(rc);
	
	CRect brc(rc.left, rc.bottom - iScy, rc.right - iScx, rc.bottom);
	wndHBar.Create(WS_CHILD|WS_VISIBLE|SBS_HORZ|SBS_BOTTOMALIGN/*|SBS_SIZEBOXBOTTOMRIGHTALIGN|SBS_SIZEBOX*/, brc, this, IDC_HBAR);
	brc.SetRect(rc.right - iScx, rc.top, rc.right, rc.bottom - iScy);
	wndVBar.Create(WS_CHILD|WS_VISIBLE|SBS_VERT|SBS_RIGHTALIGN, brc, this, IDC_VBAR);

	brc.SetRect(rc.left + iRx, rc.top, rc.right - iScx, rc.top + iRy);
	wndHRuler.Create("", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, brc, this, IDC_HRULER);
	wndHRuler.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);

	brc.SetRect(0, iRy, iRx, rc.bottom - iScy);
	wndVRuler.Create("", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, brc, this, IDC_VRULER);
	wndVRuler.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);

	Doc * pDoc = GetDocument();
	SetPaperRect(pDoc->rcPaper);
}

void View::DoSize(int cx, int cy)
{
	Doc * pDoc = GetDocument();

	if (::IsWindow(wndHBar.GetSafeHwnd()))
	{
		CRect brc(0, cy - iScy, cx - iScx, cy);
		wndHBar.SetWindowPos(0, brc.left, brc.top, brc.Width(), brc.Height(), SWP_NOZORDER);

		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_PAGE|SIF_RANGE;
		si.nPage = cx - iRx - iScx;
		si.nMin = 0;//pDoc->rcPaper.left / iDiv;
		si.nMax = pDoc->rcPaper.Width() / iDiv; //pDoc->rcPaper.right / iDiv;
		wndHBar.SetScrollInfo(&si);
	}
	if (::IsWindow(wndVBar.GetSafeHwnd()))
	{
		CRect brc(cx - iScx, 0, cx, cy - iScy);
		wndVBar.SetWindowPos(0, brc.left, brc.top, brc.Width(), brc.Height(), SWP_NOZORDER);

		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask  = SIF_PAGE|SIF_RANGE;
		si.nPage = cy - iRy - iScy;
		si.nMin = 0;//pDoc->rcPaper.top / iDiv;
		si.nMax = pDoc->rcPaper.Height() / iDiv;//pDoc->rcPaper.bottom / iDiv;
		wndVBar.SetScrollInfo(&si);
	}
	if (::IsWindow(wndHRuler.GetSafeHwnd()))
	{
		CRect brc(iRx, 0, cx - iScx, iRy);

		wndHRuler.SetWindowPos(0, brc.left, brc.top, brc.Width(), brc.Height(), SWP_NOZORDER);
		int x = wndHBar.GetScrollPos();
		wndHRuler.SetPos(x);
	}
	if (::IsWindow(wndVRuler.GetSafeHwnd()))
	{
		CRect brc(0, iRy, iRx, cy - iScy);

		wndVRuler.SetWindowPos(0, brc.left, brc.top, brc.Width(), brc.Height(), SWP_NOZORDER);
		int y = wndVBar.GetScrollPos();
		wndVRuler.SetPos(y);
	}

}

void View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	DoSize(cx,cy);
}

void View::SetPaperRect(const CRect & rc)
{
	Doc * pDoc = GetDocument();
	pDoc->rcPaper = rc;

	if (::IsWindow(wndHBar.GetSafeHwnd())) wndHBar.SetScrollRange(0, rc.Width() / iDiv);
	if (::IsWindow(wndHRuler.GetSafeHwnd())) wndHRuler.SetRange(0, rc.Width());

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_PAGE;
	si.nPage = rc.Width();
	if (::IsWindow(wndHBar.GetSafeHwnd())) wndHBar.SetScrollInfo(&si);

	si.nPage = rc.Height();

	if (::IsWindow(wndVBar.GetSafeHwnd())) 
	{
		wndVBar.SetScrollRange(0, rc.Height() / iDiv);
		wndVBar.SetScrollInfo(&si);
	}

	if (::IsWindow(wndVRuler.GetSafeHwnd())) wndVRuler.SetRange(0, rc.Height());

	CRect crc;
	GetClientRect(crc);
	DoSize(crc.Width(), crc.Height());

}

void View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int x = wndHBar.GetScrollPos();
	int xOrig = x;

	switch (nSBCode)//LOBYTE(nScrollCode))
	{
		case SB_TOP:	x = 0;			break;
		case SB_BOTTOM:	x = wndHBar.GetScrollLimit(); break;
		case SB_LINEUP:	x -= 1;			break;
		case SB_LINEDOWN: x += 1;		break;
		case SB_PAGEUP:
			{
				CRect rcClient;
				GetClientRect(&rcClient);
				x -= rcClient.Width();	
				if (x<0) x = 0;
				break;
			}
		case SB_PAGEDOWN:
			{
				CRect rcClient;
				GetClientRect(&rcClient);
				x += rcClient.Width();	
				if (x>wndHBar.GetScrollLimit()) x = wndHBar.GetScrollLimit();
				break;
			}

		case SB_THUMBTRACK:	x = nPos;	break;
	}
	wndHBar.SetScrollPos(x);
	wndHRuler.SetPos(x);

	Invalidate();
}

void View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int x = wndVBar.GetScrollPos();
	int xOrig = x;

	switch (nSBCode)//LOBYTE(nScrollCode))
	{
		case SB_TOP:	x = 0;			break;
		case SB_BOTTOM:	x = wndVBar.GetScrollLimit(); break;
		case SB_LINEUP:	x -= 1;			break;
		case SB_LINEDOWN: x += 1;		break;
		case SB_PAGEUP:
			{
				CRect rcClient;
				GetClientRect(&rcClient);
				x -= rcClient.Height();	
				if (x<0) x = 0;
				break;
			}
		case SB_PAGEDOWN:
			{
				CRect rcClient;
				GetClientRect(&rcClient);
				x += rcClient.Height();	
				if (x>wndVBar.GetScrollLimit()) x = wndVBar.GetScrollLimit();
				break;
			}

		case SB_THUMBTRACK:	x = nPos;	break;
	}
	wndVBar.SetScrollPos(x);
	wndVRuler.SetPos(x);

	Invalidate();

}

BOOL View::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

void View::OnToolArrow() 
{
	iType = -1;
}

void View::OnUpdateToolArrow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == -1);
}

void View::OnToolBorder() 
{
	iType = pfoFrame;
}

void View::OnUpdateToolBorder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoFrame);
}

void View::OnToolCheck() 
{
	iType = pfoCheck;
	
}

void View::OnUpdateToolCheck(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void View::OnToolEdit() 
{
	iType = pfoEdit;
}

void View::OnUpdateToolEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoEdit);
}

void View::OnToolImage() 
{
	iType = pfoImage;
	
}

void View::OnUpdateToolImage(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoImage);
}

void View::OnToolLine() 
{
	iType = pfoLine;
}

void View::OnUpdateToolLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoLine);
}

void View::OnToolRadio() 
{
	iType = pfoRadio;
}

void View::OnUpdateToolRadio(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void View::OnToolRect() 
{
	iType = pfoRect;
}

void View::OnUpdateToolRect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoRect);
}

void View::OnToolSottoreport() 
{
	iType = pfoSubForm;
}



void View::OnToolVline() 
{
	iType = pfoVLine;
}

void View::OnUpdateToolVline(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoVLine);
}

void View::OnToolHline() 
{
	iType = pfoHLine;
}

void View::OnUpdateToolHline(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoHLine);
}

void View::OnUpdateToolSottoreport(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoSubForm);
}

void View::OnToolStatic() 
{
	Doc * pDoc = GetDocument();

	iType = pfoStatic;
}

void View::OnUpdateToolStatic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iType == pfoStatic);
}

void View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (GetCapture() == this) ReleaseCapture();

	if (CRect(0,0,iRx,iRy).PtInRect(point))
	{
		CView::OnLButtonUp(nFlags, point);
		return;
	}

	if (pTracker) delete pTracker;
	pTracker = NULL;

	Doc * pDoc = GetDocument();

	CPoint pt(point);
//	FixPoint(pt);
	
	RealPoint(ptTrack);
	RealPoint(pt);

	if (iType >= 0)
	{
		FixPoint(ptTrack);
		FixPoint(pt);
	}

	CRect rc(ptTrack.x, ptTrack.y, pt.x, pt.y);
	rc.NormalizeRect();

	if (rc.Width() > 1 && rc.Height() > 1)
	{
		if (pDoc->GetSelectedCount() > 0) pDoc->ClearSelection();
	}

	{
		if (iType >= 0 && rc.Width() > 4 && rc.Height() > 4)//!(rc.IsRectEmpty()))
		{
			CPrintFormObject * ob = pDoc->AddObject(iType);
			ob->iType = iType;
			ob->rc = rc;
		}
		else
		{
			if (!(nFlags&MK_SHIFT))
			{
				pDoc->ClearSelection();
			}
			if (GfxIsProp2())
			{
				CGfxProperty * pg = GfxGetProp2();
				pg->DoIt();
			}
			if (pDoc->SelectObject(rc))
			{
				if (GfxIsProp2())
				{
					CGfxProperty * pg = GfxGetProp2();
					
					if (!(pg->pDocument == pDoc && pg->pWnd == this))
					{
						pg->ClearTabArray();

						dlgSheet1.pDoc = pDoc;
						dlgSheet1.pView = this;
						dlgSheet2.pDoc = pDoc;
						dlgSheet2.pView = this;
						dlgSheet3.pDoc = pDoc;
						dlgSheet3.pView = this;

						dlgSheet1.Create(CPropPage1::IDD, pg);
						dlgSheet2.Create(CPropPage2::IDD, pg);
						dlgSheet3.Create(CPropPage3::IDD, pg);

						pg->pDocument = pDoc;
						pg->pWnd = this;

						pg->AddPage(&dlgSheet1, "Generale");
						pg->AddPage(&dlgSheet2, "Ids");
						pg->AddPage(&dlgSheet3, "Other");

						pg->SetCurSel(0);
					}
					else
					{
	//					pg->DoIt();
						dlgSheet1.UpdateData(false);
						dlgSheet2.UpdateData(false);
						dlgSheet3.UpdateData(false);
					}
				}
			}
		}
	}
/*	else
	{
		if (pDoc->GetSelectedCount() > 0) pDoc->ClearSelection();
	}
*/
	if (pDoc->GetSelectedCount() <= 0)
	{
		if (GfxIsProp2())
		{
			CGfxProperty * pg = GfxGetProp2();
			if (pg->pDocument == pDoc && pg->pWnd == this)
				pg->ClearTabArray();
		}
	}


	Invalidate();	

	CView::OnLButtonUp(nFlags, point);
}

void View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	Doc * pDoc = GetDocument();

	if (CRect(0,0,iRx,iRy).PtInRect(point))
	{
		if (pDoc->GetSelectedCount() == pDoc->iFormObj)
		{			
			pDoc->ClearSelection();
		}
		else
		{
			for (int t = 0; t < pDoc->iFormObj; t++)
				pDoc->ppObjs[t]->bSelected = true;
		}
		Invalidate();

		CView::OnLButtonDown(nFlags, point);
		return;
	}

	if (pTracker) delete pTracker;

	ptTrack = point;

	if (iType < 0)// && pDoc->GetSelectedCount() > 0)
	{
		CPoint trk(point);
		RealPoint(trk);
		CRect rcTrk;
		int idx;
		iSizingHit = pDoc->HitTest(trk, rcTrk, idx);
		bSizing = false;
		if (iSizingHit >= 0 && iSizingHit != CRectTracker::hitMiddle)
		{
			if (!(pDoc->ppObjs[idx]->bSelected))
			{
				CView::OnLButtonDown(nFlags, point);
				return;
			}
			CPoint pt1(rcTrk.TopLeft());
			CPoint pt2(rcTrk.BottomRight());
			ScaledPoint(pt1);
			ScaledPoint(pt2);
			rcSizing = CRect(pt1.x, pt1.y, pt2.x, pt2.y);
			pTracker = new CRectTracker(rcSizing, CRectTracker::hatchedBorder);
			pTracker->m_nHandleSize = 4;
			if (pTracker->Track(this, point))
			{
				CRect nrc(pTracker->m_rect);
				CPoint pt3(nrc.TopLeft());
				CPoint pt4(nrc.BottomRight());
				RealPoint2(pt3);
				RealPoint2(pt4);
				FixPoint(pt3);
				FixPoint(pt4);
				nrc.SetRect(pt3.x, pt3.y, pt4.x, pt4.y);
				nrc.NormalizeRect();
				pDoc->ppObjs[idx]->rc = nrc;

				if (GfxIsProp2())
				{
					CGfxProperty * pg = GfxGetProp2();
					if (pg->pDocument == pDoc && pg->pWnd == this)
					pg->DoIt();
				}
				Invalidate();
			}
			delete pTracker;
			pTracker = NULL;
			CView::OnLButtonDown(nFlags, point);
			return;
		}
		else
		{
			pTracker = new CRectTracker(CRect(point.x, point.y, point.x, point.y), CRectTracker::hatchedBorder);
			pTracker->m_nHandleSize = 4;
			CClientDC dc(this);
			ptTrack = point;
//			FixPoint(ptTrack);
			pTracker->DrawTrackerRect(CRect(ptTrack.x, ptTrack.y, ptTrack.x, ptTrack.y), this, &dc, this);
		}
	}
	else
	{
		if (!(nFlags&MK_SHIFT))
		{
			if (pDoc->GetSelectedCount() > 0)
			{
				pDoc->ClearSelection();
				Invalidate();
			}
		}

		pTracker = new CRectTracker(CRect(point.x, point.y, point.x, point.y), CRectTracker::hatchedBorder);
		pTracker->m_nHandleSize = 4;
		CClientDC dc(this);
		ptTrack = point;
		FixPoint(ptTrack);
		pTracker->DrawTrackerRect(CRect(ptTrack.x, ptTrack.y, ptTrack.x, ptTrack.y), this, &dc, this);
	}
	SetCapture();
	
	CView::OnLButtonDown(nFlags, point);
}

void StatusBarMessage(char* fmt, ...)
{
	if (AfxGetApp() != NULL && AfxGetApp()->m_pMainWnd != NULL) 
	{
		char buffer[256];
		CStatusBar* pStatus = (CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);
		va_list argptr;
		va_start(argptr, fmt);
		vsprintf(buffer, fmt, argptr);
		va_end(argptr);
		if (pStatus != NULL) 
		{
			pStatus->SetPaneText(0, buffer);
			pStatus->UpdateWindow();
		}
	}
}

void View::OnMouseMove(UINT nFlags, CPoint point) 
{
	{
		CPoint pt1(point);
		ClientToScreen(&pt1);
		CPoint pt2(pt1);
		wndHRuler.ScreenToClient(&pt1);
		wndHRuler.DrawMouse(pt1.x);
		wndVRuler.ScreenToClient(&pt2);
		wndVRuler.DrawMouse(pt2.y);
	}

	if (pTracker)
	{
		CPoint pt(point);
		if (iType >= 0)	FixPoint2(pt);

		{
			CRect rc(ptTrack.x, ptTrack.y, pt.x, pt.y);
			rc.NormalizeRect();
			if (!(rc.IsRectEmpty()))
			{
				CClientDC dc(this);
				pTracker->DrawTrackerRect(rc, this, &dc, this);
			}
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void View::FixPoint(CPoint & pt)
{
	return;

	int px = wndHBar.GetScrollPos() / iDiv - iRx - 2;
	int py = wndVBar.GetScrollPos() / iDiv - iRy - 2;

	int x = pt.x;// + px;
	int r = x % iGridStep;
	if (r < iGridStep / 2) pt.x -= r;
	else pt.x += (iGridStep - r);

	int y = pt.y;// + py;
	r = y % iGridStep;

	if (r < iGridStep / 2) pt.y -= r;
	else pt.y += (iGridStep - r);

}

void View::FixPoint2(CPoint & pt)
{
	return;

	int px = wndHBar.GetScrollPos() / iDiv - iRx - 2;
	int py = wndVBar.GetScrollPos() / iDiv - iRy - 2;

	CPoint pt1(pt);
//	RealPoint(pt1);

	int x = pt1.x + px;
	int r = x % iGridStep;
	if (r < iGridStep / 2) pt.x -= r;
	else pt.x += (iGridStep - r);

	int y = pt1.y + py;
	r = y % iGridStep;

	if (r < iGridStep / 2) pt.y -= r;
	else pt.y += (iGridStep - r);
}

void View::FixRect(CRect & rc)
{
	return;

	CPoint pt = rc.TopLeft();
	FixPoint(pt);
	CPoint pt1 = rc.BottomRight();
	FixPoint(pt1);
	rc.SetRect(pt.x, pt.y, pt1.x, pt1.y);
}

void View::RealPoint(CPoint & pt)
{
	int px = wndHBar.GetScrollPos() * iDiv;
	int py = wndVBar.GetScrollPos() * iDiv;
	CPoint pt1((pt.x - iRx - 2) * iDiv + px, (pt.y - iRy - 2) *iDiv + py);
	pt = pt1;
}

void View::RealPoint2(CPoint & pt)
{
	int px = wndHBar.GetScrollPos() * iDiv;
	int py = wndVBar.GetScrollPos() * iDiv;

//	CPoint pt1((pt.x) * iDiv + px, (pt.y) *iDiv + py);
	CPoint pt1((pt.x - iRx - 2) * iDiv + px, (pt.y - iRy - 2) *iDiv + py);
	pt = pt1;
}

void View::ScaledPoint(CPoint & pt)
{
	pt.x /= iDiv;
	pt.y /= iDiv;

	pt.x -= wndHBar.GetScrollPos() - iRx - 2;
	pt.y -= wndVBar.GetScrollPos() - iRy - 2;
}

BOOL View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	Doc * pDoc = GetDocument();

	if (iType < 0 && pDoc->GetSelectedCount() > 0)
	{
		if (pTracker)
		{
			if (pTracker->SetCursor(this, nHitTest)) return true;
		}
		else
		{			
			CPoint trk(GetMessagePos());
			ScreenToClient(&trk);
			RealPoint(trk);
			CRect rcTrk;
			int idx;
			if (pDoc->HitTest(trk, rcTrk, idx) >= 0)
			{
				if (pDoc->ppObjs[idx]->bSelected)
				{
					CPoint pt1(rcTrk.TopLeft());
					CPoint pt2(rcTrk.BottomRight());
					ScaledPoint(pt1);
					ScaledPoint(pt2);
					CRect rcSizing1 = CRect(pt1.x, pt1.y, pt2.x, pt2.y);
					pTracker = new CRectTracker(rcSizing1, CRectTracker::resizeInside);
					pTracker->m_nHandleSize = 4;
					bool bres = pTracker->SetCursor(this, nHitTest) ? true : false;
					delete pTracker;
					pTracker = NULL;				
					if (bres) return true;
				}
			}
		}
	}
	
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void View::OnEditCut() 
{
	Doc * pDoc = GetDocument();
	pDoc->CopySelected();
	pDoc->RemoveSelected();
	Invalidate();
}

void View::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnEditCopy() 
{
	Doc * pDoc = GetDocument();
	pDoc->CopySelected();
}

void View::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnEditPaste() 
{
	Doc * pDoc = GetDocument();
	pDoc->PasteClip();
	Invalidate();
}

void View::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(iClipFormObj > 0);
}

void View::OnPaperSize() 
{
	Doc * pDoc = GetDocument();
	CPagerSizeDlg dlg;
	dlg.iTop = pDoc->rcPaper.top;
	dlg.iLeft = pDoc->rcPaper.left;
	dlg.iRight = pDoc->rcPaper.right;
	dlg.iBottom = pDoc->rcPaper.bottom;
	dlg.csPageName = pDoc->name;

	if (dlg.DoModal() == IDOK)
	{
		CRect rc(dlg.iLeft, dlg.iTop, dlg.iLeft + dlg.iRight, dlg.iTop + dlg.iBottom);
		SetPaperRect(rc);
		pDoc->name = dlg.csPageName;
		CPapersBar * pb = GfxGetPaperList();
		pb->wndList.SetItemText(pDoc->iSelpage, 0, dlg.csPageName);
		Invalidate();
	}
}

void View::OnProperty() 
{
	CPropDlg * pProp = GfxGetProp();
	
	pProp->SetObject(GetDocument(), this);
}

void View::OnUpdateProperty(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GfxIsProp());
}

void View::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (bActivate)
	{
		Doc * pDoc = GetDocument();
		CPapersBar * pb = GfxGetPaperList();
		pb->pDoc = pDoc;

		pDoc->FillList();
	}

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void View::OnGfxProperty() 
{
	CGfxProperty * pg = GfxGetProp2();
	Doc * pDoc = GetDocument();

	if (!(pg->pDocument == pDoc && pg->pWnd == this))
	{
		pg->ClearTabArray();

		if (pDoc->GetSelectedCount() > 0)
		{
			dlgSheet1.pDoc = pDoc;
			dlgSheet1.pView = this;
			dlgSheet2.pDoc = pDoc;
			dlgSheet2.pView = this;
			dlgSheet3.pDoc = pDoc;
			dlgSheet3.pView = this;

			dlgSheet1.Create(CPropPage1::IDD, pg);
			dlgSheet2.Create(CPropPage2::IDD, pg);
			dlgSheet3.Create(CPropPage3::IDD, pg);

			pg->pDocument = pDoc;
			pg->pWnd = this;

			pg->AddPage(&dlgSheet1, "Generale");
			pg->AddPage(&dlgSheet2, "Ids");
			pg->AddPage(&dlgSheet3, "Other");

			pg->SetCurSel(0);
		}
	}
	else
	{
		if (pDoc->GetSelectedCount() <= 0)
			pg->ClearTabArray();
	}
}

void View::OnUpdateGfxProperty(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GfxIsProp2());
}

void View::OnDestroy() 
{
	if (GfxIsProp2())
	{
		CGfxProperty * pg = GfxGetProp2();
		Doc * pDoc = GetDocument();
		if (pg->pDocument == pDoc && pg->pWnd == this) pg->ClearTabArray();
	}

	CView::OnDestroy();
}

void View::OnAlignBottom() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.left > pDoc->ppObjs[t]->rc.left) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				int h = pDoc->ppObjs[t]->rc.Height();
				pDoc->ppObjs[t]->rc.bottom = rc.bottom;
				pDoc->ppObjs[t]->rc.top = pDoc->ppObjs[t]->rc.bottom - h;
			}
		}
	}
	Invalidate();
}

void View::OnUpdateAlignBottom(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnAlignLeft() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top > pDoc->ppObjs[t]->rc.top) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				int w = pDoc->ppObjs[t]->rc.Width();
				pDoc->ppObjs[t]->rc.left = rc.left;
				pDoc->ppObjs[t]->rc.right = pDoc->ppObjs[t]->rc.left + w;
			}
		}
	}
	Invalidate();
}

void View::OnUpdateAlignLeft(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnAlignRight() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top > pDoc->ppObjs[t]->rc.top) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				int w = pDoc->ppObjs[t]->rc.Width();
				pDoc->ppObjs[t]->rc.right = rc.right;
				pDoc->ppObjs[t]->rc.left = pDoc->ppObjs[t]->rc.right - w;
			}
		}
	}
	Invalidate();
}

void View::OnUpdateAlignRight(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnAlignTop() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.left > pDoc->ppObjs[t]->rc.left) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				int h = pDoc->ppObjs[t]->rc.Height();
				pDoc->ppObjs[t]->rc.top = rc.top;
				pDoc->ppObjs[t]->rc.bottom = pDoc->ppObjs[t]->rc.top + h;
			}
		}
	}
	Invalidate();
}

void View::OnUpdateAlignTop(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnSizeAll() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top > pDoc->ppObjs[t]->rc.top) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top == pDoc->ppObjs[t]->rc.top && rc.left > pDoc->ppObjs[t]->rc.left) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
			{
				pDoc->ppObjs[t]->rc.top = pDoc->ppObjs[t]->rc.bottom - rc.Height();
				pDoc->ppObjs[t]->rc.right = pDoc->ppObjs[t]->rc.left + rc.Width();
			}
		}
	}
	Invalidate();
}

void View::OnUpdateSizeAll(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnSizeHorz() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top > pDoc->ppObjs[t]->rc.top) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top == pDoc->ppObjs[t]->rc.top && rc.left > pDoc->ppObjs[t]->rc.left) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
				pDoc->ppObjs[t]->rc.right = pDoc->ppObjs[t]->rc.left + rc.Width();
		}
	}
	Invalidate();
}

void View::OnUpdateSizeHorz(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnSizeVert() 
{
	Doc * pDoc = GetDocument();

	bool b = false;
	CRect rc;

	for (int t = 0; t < pDoc->iFormObj; t++)
	{
		if (pDoc->ppObjs[t]->bSelected)
		{
			if (!b) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top > pDoc->ppObjs[t]->rc.top) rc = pDoc->ppObjs[t]->rc;
			else if (rc.top == pDoc->ppObjs[t]->rc.top && rc.left > pDoc->ppObjs[t]->rc.left) rc = pDoc->ppObjs[t]->rc;
			b = true;
		}
	}
	if (b)
	{
		for (t = 0; t < pDoc->iFormObj; t++)
		{
			if (pDoc->ppObjs[t]->bSelected)
				pDoc->ppObjs[t]->rc.top = pDoc->ppObjs[t]->rc.bottom - rc.Height();
		}
	}
	Invalidate();
}

void View::OnUpdateSizeVert(CCmdUI* pCmdUI) 
{
	Doc * pDoc = GetDocument();
	pCmdUI->Enable(pDoc->GetSelectedCount() > 0);
}

void View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pt(point);
	ClientToScreen(&pt);
	((CMainFrame *) AfxGetMainWnd())->DoTrackMenu(IDR_POPS, 0, AfxGetMainWnd(), pt);
	
	CView::OnRButtonDown(nFlags, point);
}
