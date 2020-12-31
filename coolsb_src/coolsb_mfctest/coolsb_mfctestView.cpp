// coolsb_mfctestView.cpp : implementation of the CCoolsb_mfctestView class
//

#include "stdafx.h"
#include "coolsb_mfctest.h"

#include "coolsb_mfctestDoc.h"
#include "coolsb_mfctestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cool Scroll support
#include "..\coolsb\coolscroll.h"

//#pragma comment(linker, "/NODEFAULTLIB:LIBCD")

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestView

IMPLEMENT_DYNCREATE(CCoolsb_mfctestView, CView)

BEGIN_MESSAGE_MAP(CCoolsb_mfctestView, CView)
	//{{AFX_MSG_MAP(CCoolsb_mfctestView)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestView construction/destruction

CCoolsb_mfctestView::CCoolsb_mfctestView()
{
	// TODO: add construction code here
	xChar = 10;
	yChar = 10;

	nVNumLines = 50;
	nHNumLines = 50;

	nVScrollPos = 0;
	nHScrollPos = 0;
}

CCoolsb_mfctestView::~CCoolsb_mfctestView()
{
}

BOOL CCoolsb_mfctestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestView drawing

void CCoolsb_mfctestView::OnDraw(CDC* pDC)
{
	CCoolsb_mfctestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestView diagnostics

#ifdef _DEBUG
void CCoolsb_mfctestView::AssertValid() const
{
	CView::AssertValid();
}

void CCoolsb_mfctestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCoolsb_mfctestDoc* CCoolsb_mfctestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCoolsb_mfctestDoc)));
	return (CCoolsb_mfctestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestView message handlers

void CCoolsb_mfctestView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nSBCode)
	{
	case SB_LINEUP:		nVScrollPos --;					break;
	case SB_LINEDOWN:	nVScrollPos ++;					break;
	case SB_PAGEUP:		nVScrollPos -= nVScrollPage;	break;
	case SB_PAGEDOWN:	nVScrollPos += nVScrollPage;	break;
	case SB_TOP:		nVScrollPos = 0;				break;
	case SB_BOTTOM:		nVScrollPos = nVScrollMax -1;	break;
	case SB_THUMBTRACK: nVScrollPos = nPos;				break;
	}

	if(nVScrollPos < 0) 
		nVScrollPos = 0;

	if(nVScrollPos > nVScrollMax - nVScrollPage + 1) 
		nVScrollPos = nVScrollMax - nVScrollPage + 1;

	CoolSB_SetScrollPos(m_hWnd, SB_VERT, nVScrollPos, TRUE);
	
	//CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CCoolsb_mfctestView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nSBCode)
	{
	case SB_LINEUP:		nHScrollPos --;					break;
	case SB_LINEDOWN:	nHScrollPos ++;					break;
	case SB_PAGEUP:		nHScrollPos -= nHScrollPage;	break;
	case SB_PAGEDOWN:	nHScrollPos += nHScrollPage;	break;
	case SB_TOP:		nHScrollPos = 0;				break;
	case SB_BOTTOM:		nHScrollPos = nHScrollMax -1;	break;
	case SB_THUMBTRACK: nHScrollPos = nPos;				break;
	}

	if(nHScrollPos < 0) 
		nHScrollPos = 0;

	if(nHScrollPos > nHScrollMax - nHScrollPage + 1) 
		nHScrollPos = nHScrollMax - nHScrollPage + 1;

	CoolSB_SetScrollPos(m_hWnd, SB_HORZ, nHScrollPos, TRUE);
	
//	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCoolsb_mfctestView::SetupScrollbars()
{
	SCROLLINFO si;
	RECT rect;

	GetClientRect(&rect);

	// VERT
	nVScrollPage = min(nVNumLines + 1, (rect.bottom - rect.top) / yChar);
	nVScrollMax  = max(0, nVNumLines );
    nVScrollPos  = min(nVScrollPos, nVScrollMax - nVScrollPage + 1);
	
	si.cbSize	= sizeof(si);
	si.fMask	= SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	si.nMin		= 0;
	si.nMax		= nVScrollMax;
	si.nPos		= nVScrollPos;
	si.nPage	= min(nVScrollPage, nVScrollMax + 1);
	
	CoolSB_SetScrollInfo (m_hWnd, SB_VERT, &si, TRUE);

	// HORZ
	nHScrollPage = min(nHNumLines + 1, (rect.right - rect.left) / xChar);
	nHScrollMax  = max(0, nHNumLines);
    nHScrollPos  = min(nHScrollPos, nHScrollMax - nHScrollPage + 1);
	
	si.cbSize	= sizeof(si);
	si.fMask	= SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	si.nMin		= 0;
	si.nMax		= nHScrollMax;
	si.nPos		= nHScrollPos;
	si.nPage	= min(nHScrollPage, nHScrollMax + 1);
	
	CoolSB_SetScrollInfo (m_hWnd, SB_HORZ, &si, TRUE);
}

int CCoolsb_mfctestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	InitializeCoolSB(m_hWnd);

	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask  = SIF_ALL;
	si.nMin   = 0;
	si.nMax   = 100;
	si.nPage  = 10;
	si.nPos   = 0;

	CoolSB_SetScrollInfo(m_hWnd, SB_HORZ, &si, TRUE);
	CoolSB_SetScrollInfo(m_hWnd, SB_VERT, &si, TRUE);
	CoolSB_SetStyle(m_hWnd, SB_BOTH, CSBS_FLAT);

	return 0;
}

void CCoolsb_mfctestView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetupScrollbars();
	
}
