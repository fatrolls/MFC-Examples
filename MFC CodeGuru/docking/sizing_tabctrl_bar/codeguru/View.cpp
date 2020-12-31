// View.cpp : Implementierung der Klasse CDocView
//

#include "stdafx.h"
#include "Demo.h"

#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocView

IMPLEMENT_DYNCREATE(CDocView, CView)

BEGIN_MESSAGE_MAP(CDocView, CView)
	//{{AFX_MSG_MAP(CDocView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocView Konstruktion/Destruktion

CDocView::CDocView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CDocView::~CDocView()
{
}

BOOL CDocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDocView Zeichnen

void CDocView::OnDraw(CDC* pDC)
{
	CDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

/////////////////////////////////////////////////////////////////////////////
// CDocView Diagnose

#ifdef _DEBUG
void CDocView::AssertValid() const
{
	CView::AssertValid();
}

void CDocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDoc* CDocView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoc)));
	return (CDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocView Nachrichten-Handler
