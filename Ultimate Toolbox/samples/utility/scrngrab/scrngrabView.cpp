// scrngrabView.cpp : implementation of the CScrngrabView class
//

#include "stdafx.h"
#include "scrngrab.h"

#include "scrngrabDoc.h"
#include "scrngrabView.h"
#include "mainfrm.h"
#include "oxscreengrab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrngrabView

IMPLEMENT_DYNCREATE(CScrngrabView, CFormView)

BEGIN_MESSAGE_MAP(CScrngrabView, CFormView)
	//{{AFX_MSG_MAP(CScrngrabView)
	ON_BN_CLICKED(IDC_CAPT_BUTTON, OnCaptButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_CAPT_BUTTON_ENTIRE, OnCaptButtonEntire)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrngrabView construction/destruction

CScrngrabView::CScrngrabView()
	: CFormView(CScrngrabView::IDD)
{
	//{{AFX_DATA_INIT(CScrngrabView)
	m_nCaptOption = 1;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_bCapturing = FALSE;
}

CScrngrabView::~CScrngrabView()
{
}

void CScrngrabView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrngrabView)
	DDX_Control(pDX, IDC_STATICIMAGE, m_stcImage);
	//}}AFX_DATA_MAP
}

BOOL CScrngrabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScrngrabView diagnostics

#ifdef _DEBUG
void CScrngrabView::AssertValid() const
{
	CFormView::AssertValid();
}

void CScrngrabView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CScrngrabDoc* CScrngrabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrngrabDoc)));
	return (CScrngrabDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScrngrabView message handlers

void CScrngrabView::OnCaptButton() 
{
	if (!UpdateData(TRUE))
		return;
	m_bCapturing = TRUE;

}

void CScrngrabView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFormView::OnLButtonDown(nFlags, point);

	if (m_bCapturing)
		{
		::ReleaseCapture();
		COXScreenGrabber ScreenGrabber;
		ScreenGrabber.GrabTracker(this, point, AfxGetApp()->m_pMainWnd);

		DrawRslt(ScreenGrabber.GetGrabDIB());
		m_bCapturing = FALSE;
		}
}

void CScrngrabView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	ResizeParentToFit(FALSE);
	
}

void CScrngrabView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	CFormView::OnLButtonUp(nFlags, point);
}

void CScrngrabView::OnCaptButtonEntire() 
{
	COXScreenGrabber scr;
	scr.GrabFullWindow(CWnd::FromHandle(::GetDesktopWindow()));
	DrawRslt(scr.GetGrabDIB());
}

void CScrngrabView::DrawRslt(COXDIB *pDib)
{
	CRect rct;
	m_stcImage.GetClientRect(&rct);
	CDC* pDC=m_stcImage.GetDC();
	CSize sz=pDib->GetSize();
	CRect rctDIB(0,0, sz.cx, sz.cy);
	pDib->Paint(pDC,rct,rctDIB);

}
