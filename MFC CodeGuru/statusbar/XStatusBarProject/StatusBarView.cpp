#include "stdafx.h"
#include "StatusBar.h"

#include "StatusBarDoc.h"
#include "StatusBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CStatusBarView, CView)

BEGIN_MESSAGE_MAP(CStatusBarView, CView)
	//{{AFX_MSG_MAP(CStatusBarView)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CStatusBarView::CStatusBarView()						{ }
CStatusBarView::~CStatusBarView()						{ }
BOOL CStatusBarView::PreCreateWindow(CREATESTRUCT& cs)	{ return CView::PreCreateWindow(cs); }

void CStatusBarView::OnDraw(CDC* pDC)
{
	CStatusBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rect(0, 0, 1000, 1000);
	pDC->DrawText(	"The panes are defined as follows:\n\n"
					"Pane 0:   Message Pane (Mode: Text, Left: Scrollbar, Right: toggle to Bitmap-Mode)\n"
					"Pane 1:   COUNT (Mode: Number, Left: increase, Right: decrease)\n"
					"Pane 2:   CAPS (Mode: Text, Left: HScroll on/off, Right: VScroll on/off)\n"
					"Pane 3:   NUM (Mode: Text, Left: change fontsize, Right: change fontname)\n"
					"Pane 4:   INSERT (Mode: Bitmap,Repeat, Left: HScroll on/off, Right: VScroll on/off)\n"
					"Pane 5:   SCROLL (Mode: Bitmap,Stretch, Left: Counter, Right: Smooth scrollbar\n\n\n"
					"When you doubleclick the panes, the appearance of the pane changes. There are\n"
					"different actions if you use the left or the right mousebutton.",
					rect, DT_LEFT | DT_TOP);
}

BOOL CStatusBarView::OnPreparePrinting(CPrintInfo* pInfo)					{ return DoPreparePrinting(pInfo); }
void CStatusBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)	{}
void CStatusBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)		{}

#ifdef _DEBUG
void CStatusBarView::AssertValid() const									{ CView::AssertValid(); }
void CStatusBarView::Dump(CDumpContext& dc) const							{ CView::Dump(dc); }

CStatusBarDoc* CStatusBarView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusBarDoc)));
	return (CStatusBarDoc*)m_pDocument;
}
#endif //_DEBUG

