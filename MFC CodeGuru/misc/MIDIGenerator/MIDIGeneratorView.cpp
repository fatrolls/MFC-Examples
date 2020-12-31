// MIDIGeneratorView.cpp : implementation of the CMIDIGeneratorView class
//

#include "stdafx.h"
#include "MIDIGenerator.h"

#include "MIDIGeneratorDoc.h"
#include "MIDIGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorView

IMPLEMENT_DYNCREATE(CMIDIGeneratorView, CView)

BEGIN_MESSAGE_MAP(CMIDIGeneratorView, CView)
	//{{AFX_MSG_MAP(CMIDIGeneratorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorView construction/destruction

CMIDIGeneratorView::CMIDIGeneratorView()
{
	// TODO: add construction code here

}

CMIDIGeneratorView::~CMIDIGeneratorView()
{
}

BOOL CMIDIGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorView drawing

void CMIDIGeneratorView::OnDraw(CDC* pDC)
{
	CMIDIGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorView diagnostics

#ifdef _DEBUG
void CMIDIGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CMIDIGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMIDIGeneratorDoc* CMIDIGeneratorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMIDIGeneratorDoc)));
	return (CMIDIGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorView message handlers
