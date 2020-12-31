// RulerBarView.cpp : implementation of the CRulerBarView class
//

#include "stdafx.h"
#include "RulerBar.h"

#include "RulerBarDoc.h"
#include "RulerBarView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerBarView

IMPLEMENT_DYNCREATE(CRulerBarView, CEditView)

BEGIN_MESSAGE_MAP(CRulerBarView, CEditView)
	//{{AFX_MSG_MAP(CRulerBarView)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRulerBarView construction/destruction

CRulerBarView::CRulerBarView()
{
	// TODO: add construction code here

}

CRulerBarView::~CRulerBarView()
{
}

BOOL CRulerBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CRulerBarView drawing

void CRulerBarView::OnDraw(CDC* pDC)
{
	CRulerBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CRulerBarView printing

BOOL CRulerBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CRulerBarView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CRulerBarView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CRulerBarView diagnostics

#ifdef _DEBUG
void CRulerBarView::AssertValid() const
{
	CEditView::AssertValid();
}

void CRulerBarView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CRulerBarDoc* CRulerBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRulerBarDoc)));
	return (CRulerBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRulerBarView message handlers

int CRulerBarView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	VERIFY(m_ruler.Attach(this,TRUE,TRUE));

	UpdateRulerBars();
	
	return 0;
}

void CRulerBarView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	UNREFERENCED_PARAMETER(pSender);
	UNREFERENCED_PARAMETER(lHint);
	UNREFERENCED_PARAMETER(pHint);

	UpdateRulerBars();
}

void CRulerBarView::UpdateRulerBars()
{
	ASSERT(m_ruler.IsAttached());

	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();

	m_ruler.SetShowHorzRulerBar(pMainFrame->m_bShowHorz);
	m_ruler.SetShowVertRulerBar(pMainFrame->m_bShowVert);

	m_ruler.SetVertRulerBarWidth(pMainFrame->m_nSize);
	m_ruler.SetHorzRulerBarHeight(pMainFrame->m_nSize);

	switch(pMainFrame->m_nUnit)
	{
	case 0:
		{
			m_ruler.CalibrateRuler(100,TRUE,FALSE);
			m_ruler.CalibrateRuler(100,FALSE,FALSE);
			m_ruler.RedrawAttached();

			break;
		}
	case 1:
		{
			m_ruler.GetHorzRulerBar()->SetCalibrate(254,FALSE);
			m_ruler.GetVertRulerBar()->SetCalibrate(254,FALSE);
			m_ruler.RedrawAttached();

			break;
		}
	case 2:
		{
			m_ruler.GetHorzRulerBar()->SetCalibrate(2540,FALSE);
			m_ruler.GetVertRulerBar()->SetCalibrate(2540,FALSE);
			m_ruler.RedrawAttached();

			break;
		}
	default:
		ASSERT(FALSE);
	}
}


void CRulerBarView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	UNREFERENCED_PARAMETER(pWnd);

	// TODO: Add your message handler code here
	CMenu menu;
	if(menu.CreatePopupMenu())
	{
		menu.AppendMenu(MF_STRING,ID_VIEW_CUSTOMIZE_RULERS,
			_T("&Customize Ruler Bars"));

		menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,AfxGetMainWnd());
	}
}
