// VisualStudioLikeDemoView.cpp : implementation of the CVisualStudioLikeDemoView class
//

#include "stdafx.h"
#include "VisualStudioLikeDemo.h"

#include "VisualStudioLikeDemoDoc.h"
#include "VisualStudioLikeDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoView

IMPLEMENT_DYNCREATE(CVisualStudioLikeDemoView, CEditView)

BEGIN_MESSAGE_MAP(CVisualStudioLikeDemoView, CEditView)
	//{{AFX_MSG_MAP(CVisualStudioLikeDemoView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND_IN_FILES, OnUpdateEditFindInFiles)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoView construction/destruction

CVisualStudioLikeDemoView::CVisualStudioLikeDemoView()
{
	// TODO: add construction code here

}

CVisualStudioLikeDemoView::~CVisualStudioLikeDemoView()
{
}

BOOL CVisualStudioLikeDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoView drawing

void CVisualStudioLikeDemoView::OnDraw(CDC* pDC)
{
	CVisualStudioLikeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoView printing

BOOL CVisualStudioLikeDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CVisualStudioLikeDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CVisualStudioLikeDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoView diagnostics

#ifdef _DEBUG
void CVisualStudioLikeDemoView::AssertValid() const
{
	CEditView::AssertValid();
}

void CVisualStudioLikeDemoView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CVisualStudioLikeDemoDoc* CVisualStudioLikeDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVisualStudioLikeDemoDoc)));
	return (CVisualStudioLikeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoView message handlers

void CVisualStudioLikeDemoView::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CVisualStudioLikeDemoView::OnUpdateEditFindInFiles(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}
