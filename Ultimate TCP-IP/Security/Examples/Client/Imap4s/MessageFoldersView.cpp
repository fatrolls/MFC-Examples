// MessageFoldersView.cpp : implementation of the CMessageFoldersView class
//

#include "stdafx.h"
#include "IMAPClient.h"

#include "IMAPClientDoc.h"
#include "MessageFoldersView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageFoldersView

IMPLEMENT_DYNCREATE(CMessageFoldersView, CListView)

BEGIN_MESSAGE_MAP(CMessageFoldersView, CListView)
	//{{AFX_MSG_MAP(CMessageFoldersView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageFoldersView construction/destruction

CMessageFoldersView::CMessageFoldersView()
{
	// TODO: add construction code here

}

CMessageFoldersView::~CMessageFoldersView()
{
}

BOOL CMessageFoldersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMessageFoldersView drawing

void CMessageFoldersView::OnDraw(CDC* pDC)
{
	CIMAPClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMessageFoldersView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CMessageFoldersView printing

BOOL CMessageFoldersView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMessageFoldersView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMessageFoldersView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMessageFoldersView diagnostics

#ifdef _DEBUG
void CMessageFoldersView::AssertValid() const
{
	CListView::AssertValid();
}

void CMessageFoldersView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CIMAPClientDoc* CMessageFoldersView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMAPClientDoc)));
	return (CIMAPClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessageFoldersView message handlers
