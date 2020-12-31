// MetaFileView.cpp : implementation of the CMetaFileView class
//

#include "stdafx.h"
#include "MetaFile.h"

#include "MetaFileDoc.h"
#include "MetaFileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaFileView

IMPLEMENT_DYNCREATE(CMetaFileView, CView)

BEGIN_MESSAGE_MAP(CMetaFileView, CView)
	//{{AFX_MSG_MAP(CMetaFileView)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_DEFAULT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_TOPLEFT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_TOPMIDDLE, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_TOPRIGHT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_MIDDLELEFT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_MIDDLECENTRE, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_MIDDLERIGHT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_BOTTOMLEFT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_BOTTOMCENTRE, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_BOTTOMRIGHT, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_STRETCH, OnAlignment)
	ON_COMMAND_EX(ID_VIEW_ALIGNMENT_FIT, OnAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_DEFAULT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_TOPLEFT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_TOPMIDDLE, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_TOPRIGHT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_MIDDLELEFT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_MIDDLECENTRE, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_MIDDLERIGHT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_BOTTOMLEFT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_BOTTOMLEFT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_BOTTOMRIGHT, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_STRETCH, OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGNMENT_FIT, OnUpdateAlignment)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaFileView construction/destruction

CMetaFileView::CMetaFileView()
{
	// TODO: add construction code here
	m_align = AlignDefault;
}

CMetaFileView::~CMetaFileView()
{
}

BOOL CMetaFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMetaFileView drawing

void CMetaFileView::OnDraw(CDC* pDC)
{
	CMetaFileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	
	// Fill the client area with the metafile
	// Use appropriate alignment options
	CRect rectClient;
	GetClientRect(rectClient);
	pDoc->GetMetaFile().Display(pDC, rectClient, m_align);
}

/////////////////////////////////////////////////////////////////////////////
// CMetaFileView printing

BOOL CMetaFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMetaFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMetaFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMetaFileView diagnostics

#ifdef _DEBUG
void CMetaFileView::AssertValid() const
{
	CView::AssertValid();
}

void CMetaFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMetaFileDoc* CMetaFileView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMetaFileDoc)));
	return (CMetaFileDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMetaFileView message handlers

BOOL CMetaFileView::OnAlignment(UINT nID)
{
	m_align = (METAALIGNMENT)(nID - ID_VIEW_ALIGNMENT_DEFAULT);
	Invalidate();
	return TRUE;
}

void CMetaFileView::OnUpdateAlignment(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio((METAALIGNMENT)(pCmdUI->m_nID - ID_VIEW_ALIGNMENT_DEFAULT)
				== m_align);
}
