// GridViewDemoView.cpp : implementation of the CGridViewDemoView class
//

#include "stdafx.h"
#include "GridViewDemo.h"

#include "GridViewDemoDoc.h"
#include "GridViewDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView

IMPLEMENT_DYNCREATE(CGridViewDemoView, CView)

BEGIN_MESSAGE_MAP(CGridViewDemoView, CView)
	//{{AFX_MSG_MAP(CGridViewDemoView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView construction/destruction

CGridViewDemoView::CGridViewDemoView()
{
	m_pGridCtrl = NULL;
}

CGridViewDemoView::~CGridViewDemoView()
{
	if (m_pGridCtrl)
		delete m_pGridCtrl;
}

BOOL CGridViewDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView drawing

void CGridViewDemoView::OnDraw(CDC* pDC)
{
	CGridViewDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView printing

BOOL CGridViewDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGridViewDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGridCtrl)
		m_pGridCtrl->OnBeginPrinting(pDC, pInfo);
}

void CGridViewDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_pGridCtrl)
		m_pGridCtrl->OnPrint(pDC, pInfo);
}

void CGridViewDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGridCtrl)
		m_pGridCtrl->OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView diagnostics

#ifdef _DEBUG
void CGridViewDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGridViewDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGridViewDemoDoc* CGridViewDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGridViewDemoDoc)));
	return (CGridViewDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView message handlers

void CGridViewDemoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->Create(rect, this, 100);

		// fill it up with stuff
		m_pGridCtrl->SetEditable(TRUE);
		m_pGridCtrl->EnableDragAndDrop(TRUE);

		try {
			m_pGridCtrl->SetRowCount(50);
			m_pGridCtrl->SetColumnCount(10);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		// fill rows/cols with text
		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
			for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;
				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					Item.szText.Format(_T("Column %d"),col);
				} else if (col < 1) {
					Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.szText.Format(_T("Row %d"),row);
				} else {
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.szText.Format(_T("%d"),row*col);
				}
				m_pGridCtrl->SetItem(&Item);
		}

		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetRowHeight(0, 3*m_pGridCtrl->GetRowHeight(0)/2);
	}
}

void CGridViewDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}
