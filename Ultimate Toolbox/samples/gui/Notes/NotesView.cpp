// NotesView.cpp : implementation of the CNotesView class
//

#include "stdafx.h"
#include "Notes.h"

#include "NotesDoc.h"
#include "NotesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotesView

IMPLEMENT_DYNCREATE(CNotesView, COXNotesEditView)

BEGIN_MESSAGE_MAP(CNotesView, COXNotesEditView)
	//{{AFX_MSG_MAP(CNotesView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, COXNotesEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, COXNotesEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, COXNotesEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotesView construction/destruction

CNotesView::CNotesView()
{
	// TODO: add construction code here

}

CNotesView::~CNotesView()
{
}

BOOL CNotesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COXNotesEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNotesView drawing

void CNotesView::OnDraw(CDC* pDC)
{
	UNUSED_ALWAYS(pDC);
	CNotesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CNotesView printing

BOOL CNotesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNotesView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	COXNotesEditView::OnBeginPrinting(pDC, pInfo);
}

void CNotesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNotesView diagnostics

#ifdef _DEBUG
void CNotesView::AssertValid() const
{
	COXNotesEditView::AssertValid();
}

void CNotesView::Dump(CDumpContext& dc) const
{
	COXNotesEditView::Dump(dc);
}

CNotesDoc* CNotesView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNotesDoc)));
	return (CNotesDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNotesView message handlers

void CNotesView::OnChangeCursor(HCURSOR* phCursor, UINT nPosition)
{
	UNUSED_ALWAYS(phCursor);
	UNUSED_ALWAYS(nPosition);

}


int CNotesView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXNotesEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetWindowText(CLIENT_TEXT);
	SetBookmark(10,0);
	SetBookmark(40,2);
	SetBookmark(90,3);
	return 0;
}