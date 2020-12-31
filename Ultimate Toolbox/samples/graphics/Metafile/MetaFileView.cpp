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
	ON_COMMAND(ID_VIEW_RATIO, OnViewRatio)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RATIO, OnUpdateViewRatio)
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

	m_bMaintainRatio = TRUE;
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
	CRect rectClient;
	GetClientRect( &rectClient);
	if (m_bMaintainRatio)
	{	
		if (! pDoc->m_MetaFile.PlayFile (pDC, &rectClient) )
			AfxMessageBox (_T("Error in OXMetaFile::PlayFile"));
	}
	else
	{	
		if (! pDoc->m_MetaFile.PlayFile (pDC ) )
			AfxMessageBox (_T("Error in OXMetaFile::PlayFile"));
	}
	return ;
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


void CMetaFileView::OnViewRatio() 
{
	// TODO: Add your command handler code here
	
	m_bMaintainRatio = !m_bMaintainRatio;
	InvalidateRect ( NULL );
}

void CMetaFileView::OnUpdateViewRatio(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck ( m_bMaintainRatio );
}
