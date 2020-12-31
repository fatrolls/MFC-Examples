// splashView.cpp : Implementierung der Klasse CSplashView
//

#include "stdafx.h"
#include "splash.h"

#include "splashDoc.h"
#include "splashView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashView

IMPLEMENT_DYNCREATE(CSplashView, CView)

BEGIN_MESSAGE_MAP(CSplashView, CView)
	//{{AFX_MSG_MAP(CSplashView)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashView Konstruktion/Destruktion

CSplashView::CSplashView()
{
}

CSplashView::~CSplashView()
{
}

BOOL CSplashView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplashView Zeichnen

void CSplashView::OnDraw(CDC* pDC)
{
	CSplashDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CSplashView Drucken

BOOL CSplashView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CSplashView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CSplashView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CSplashView Diagnose

#ifdef _DEBUG
void CSplashView::AssertValid() const
{
	CView::AssertValid();
}

void CSplashView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplashDoc* CSplashView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplashDoc)));
	return (CSplashDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplashView Nachrichten-Handler
