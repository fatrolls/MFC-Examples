// demoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "ximage.h"
#include "MainFrm.h"
#include "demo.h"

#include "demoDoc.h"
#include "demoView.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************/
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CDemoView, CScrollView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_MESSAGE(WM_USER_NEWIMAGE, OnNewImage)
	ON_MESSAGE(WM_USER_PROGRESS, OnNewProgress)
END_MESSAGE_MAP()

/**************************************/
// CDemoView construction/destruction
CDemoView::CDemoView()
{
	SetScrollSizes(MM_TEXT, CSize(0, 0));
   VERIFY(m_brHatch.CreateHatchBrush(HS_DIAGCROSS, RGB(191, 191, 191)));
}
/**************************************/
CDemoView::~CDemoView()
{
}
/**************************************/
BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);
}
/**************************************/
// CDemoView drawing
void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	BOOL bPrinting = pDC->IsPrinting();

	CMemDC* pMemDC = NULL;
	if (!bPrinting) pDC = pMemDC = new CMemDC(pDC);

	if (!bPrinting && m_brHatch.m_hObject){
		CRect rect;
		GetClientRect(&rect);
		rect.right  = max(rect.right , m_totalDev.cx);
		rect.bottom = max(rect.bottom, m_totalDev.cy);
		m_brHatch.UnrealizeObject();
		CPoint pt(0, 0);
		pDC->LPtoDP(&pt);
		pt = pDC->SetBrushOrg(pt.x % 8, pt.y % 8);
		CBrush* old = pDC->SelectObject(&m_brHatch);
		pDC->FillRect(&rect, &m_brHatch);
		pDC->SelectObject(old);
	}

	CxImage* ima = pDoc->GetImage(); 
	if (ima) {
		if (bPrinting) {
			// get size of printer page (in pixels)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			// get printer pixels per inch
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
			// Best Fit case: create a rectangle which preserves the aspect ratio
			//int cx = (int)((double)ima->GetHeight()*cxPage/cxInch);
			int cx = cxPage-200;
			int cy = (int)(((double)ima->GetHeight()*cyInch*cx)
						  /((double)ima->GetWidth()*cxInch));
			// print it!
			ima->Draw(pDC->GetSafeHdc(), CRect(100,100,cx,cy));
		}
		else if (pDoc->GetStretchMode()) {
			CRect rect;
			GetClientRect(&rect);
			ima->Draw(pDC->GetSafeHdc(), rect);
		} else {
			float zoom=pDoc->GetZoomFactor();
			if (zoom==1)
				ima->Draw(pDC->GetSafeHdc());
			else
				ima->Draw(pDC->GetSafeHdc(),
						CRect(0,0,(int)(ima->GetWidth()*zoom),(int)(ima->GetHeight()*zoom)));
		}
	}

	delete pMemDC;
}
/**************************************/
// CDemoView printing
BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}
/**************************************/
void CDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
/**************************************/
void CDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
/**************************************/
// CDemoView diagnostics
#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}
/**************************************/
void CDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
/**************************************/
CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/**************************************/
void CDemoView::GetImageXY(CDemoDoc *pDoc, CxImage *ima, long *x, long *y)
{
	if (!ima || !pDoc) return;

	CPoint point=GetScrollPosition();
	float fx =(float)(*x + point.x);
	float fy =(float)(*y + point.y);

	fx/=pDoc->GetZoomFactor();
	fy/=pDoc->GetZoomFactor();

	if (pDoc->GetStretchMode())	{
		CRect rect;
		GetClientRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		fx *= ima->GetWidth()/(float)width;
		fy *= ima->GetHeight()/(float)height;
	}
	*x = (long)fx;
	*y = (long)fy;
}
/**************************************/
// CDemoView message handlers
/**************************************/
void CDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDemoDoc* pDoc = GetDocument();
	CxImage*  ima  = pDoc->GetImage();
	if (!ima)	return;

	// We'll get the RGB values at the point the user selects
	long x = point.x;
	long y = point.y;
	GetImageXY(pDoc, ima, &x,&y);

	char s[80];
	if (ima->IsInside(x,y))	{
		long yflip = ima->GetHeight() - y - 1;
		sprintf(s,"x: %d y: %d  idx: %d", x, y, ima->GetPixelIndex(x,yflip));
		RGBQUAD rgb=ima->GetPixelColor(x,yflip);
		sprintf(&s[strlen(s)],"  RGB: (%d, %d, %d)", rgb.rgbRed , rgb.rgbGreen , rgb.rgbBlue );

		//Enable these lines if you want draw over the image	
		//if ((nFlags & MK_LBUTTON)==MK_LBUTTON){
		//	ima->SetPixelColor(x,yflip,RGB(rand()/(RAND_MAX/256),rand()/(RAND_MAX/256),rand()/(RAND_MAX/256)));
		//	Invalidate(0);
		//}
	
	} else strcpy(s," ");
	
	CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
	statusBar.SetPaneText(0, s);
	
	CScrollView::OnMouseMove(nFlags, point);
}
/**************************************/
BOOL CDemoView::OnEraseBkgnd(CDC* pDC) 
{
	return 1;
}
/**************************************/
void CDemoView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	
	CDemoDoc* pDoc = GetDocument();
	if (pDoc) pDoc->UpdateStatusBar();
}
/**************************************/
void CDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDemoDoc* pDoc = GetDocument();
	if (pDoc) {
		if (pDoc->GetWaitingClick()){
			pDoc->SetWaitingClick(0);
			CxImage* ima = pDoc->GetImage();
			if (ima) {
				long x = point.x;
				long y = point.y;
				GetImageXY(pDoc, ima, &x,&y);
				if (ima->IsInside(x,y))	{
					pDoc->SubmitUndo();
					long yflip = ima->GetHeight() - y - 1;
					ima->SetTransIndex(ima->GetPixelIndex(x,yflip));
					pDoc->UpdateAllViews(NULL);
				}
			}
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}
/**************************************/
void CDemoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	case WM_USER_NEWIMAGE:
		{
			CDemoDoc* pDoc = GetDocument();
			CxImage*  ima  = pDoc->GetImage();
			int x=(int)(ima->GetWidth()*pDoc->GetZoomFactor());
			int y=(int)(ima->GetHeight()*pDoc->GetZoomFactor());
			SetScrollSizes(MM_TEXT,	CSize(x,y));
			CWnd* pFrame=GetParentFrame();
			if (!(pFrame->IsIconic()||pFrame->IsZoomed())){
				RECT rClient,rMainCl,rFrame,rMainFr;
				((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetClientRect(&rMainCl);
				((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetWindowRect(&rMainFr);
				pFrame->GetClientRect(&rClient);
				pFrame->GetWindowRect(&rFrame);
				pFrame->SetWindowPos(0,0,0,
					(4+rFrame.right-rFrame.left-rClient.right+rClient.left)+
					min(rMainCl.right-(rFrame.left-rMainFr.left+12),x),
					(4+rFrame.bottom-rFrame.top-rClient.bottom+rClient.top)+
					min(rMainCl.bottom-(rFrame.top-rMainFr.top+12),y),
					SWP_NOMOVE|SWP_NOZORDER);
				//ResizeParentToFit(1);
			}
			break;
		}
	default:
		{
			CDemoDoc* pDoc = GetDocument();
			if (pDoc){
				CxImage*  ima  = pDoc->GetImage();
				if (ima){
					if (pDoc->GetStretchMode()) SetScrollSizes(MM_TEXT,	CSize(0,0));
					else SetScrollSizes(MM_TEXT,CSize((int)(ima->GetWidth()*pDoc->GetZoomFactor()),
													  (int)(ima->GetHeight()*pDoc->GetZoomFactor())));
				}
			}
		}
	}
	CScrollView::OnUpdate(pSender, lHint, pHint);
}
/**************************************/
void CDemoView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDM_CXIMAGE1);
	CMenu *pContextMenu=menu.GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
}
/**************************************/
LRESULT CDemoView::OnNewImage(WPARAM wParam, LPARAM lParam)
{
	CDemoDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
	pDoc->UpdateStatusBar();
	return 0;
}
/**************************************/
LRESULT CDemoView::OnNewProgress(WPARAM wParam, LPARAM lParam)
{
	CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
	CString s;
	s.Format("%d %%",(int)wParam);
	statusBar.SetPaneText(2, s);
	statusBar.Invalidate(1);

	CProgressCtrl& progressBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetProgressBar();
	progressBar.SetPos((int)wParam);
	progressBar.Invalidate(1);

	return 0;
}
/**************************************/
