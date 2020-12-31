// ex27aView.cpp : implementation of the CEx27aView class
//

#include "stdafx.h"
#include "ex27a.h"

#include "ex27aDoc.h"
#include "ex27aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27aView

IMPLEMENT_DYNCREATE(CEx27aView, CView)

BEGIN_MESSAGE_MAP(CEx27aView, CView)
	//{{AFX_MSG_MAP(CEx27aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27aView construction/destruction

CEx27aView::CEx27aView()
{
	// TODO: add construction code here

}

CEx27aView::~CEx27aView()
{
}

BOOL CEx27aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aView drawing

void CEx27aView::OnDraw(CDC* pDC)
{
	CEx27aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFont font;
    font.CreateFont(-500, 0, 0, 0, 400, FALSE, FALSE, 0,
                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS, "Arial");
    CFont* pFont = pDC->SelectObject(&font);
    CRect rectClient;
    GetClientRect(rectClient);
    CSize sizeClient = rectClient.Size();
    pDC->DPtoHIMETRIC(&sizeClient);
    CRect rectEllipse(sizeClient.cx / 2 - 1000,
                     -sizeClient.cy / 2 + 1000,
                      sizeClient.cx / 2 + 1000,
                     -sizeClient.cy / 2 - 1000);
	pDC->Ellipse(rectEllipse);
    pDC->TextOut(0, 0, pDoc->m_strText);
	pDC->SelectObject(pFont);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aView printing

BOOL CEx27aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx27aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx27aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CEx27aView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aView diagnostics

#ifdef _DEBUG
void CEx27aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx27aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx27aDoc* CEx27aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx27aDoc)));
	return (CEx27aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27aView message handlers

void CEx27aView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
    pDC->SetMapMode(MM_HIMETRIC);
}
