// StatusTricksView.cpp : implementation of the CStatusTricksView class
//

#include "stdafx.h"
#include "StatusTricks.h"

#include "StatusTricksDoc.h"
#include "StatusTricksView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksView

IMPLEMENT_DYNCREATE(CStatusTricksView, CView)

BEGIN_MESSAGE_MAP(CStatusTricksView, CView)
	//{{AFX_MSG_MAP(CStatusTricksView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksView construction/destruction
CStatusTricksView::CStatusTricksView()
{
}

CStatusTricksView::~CStatusTricksView()
{
}

BOOL CStatusTricksView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksView drawing

void CStatusTricksView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksView printing
BOOL CStatusTricksView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStatusTricksView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CStatusTricksView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksView diagnostics
#ifdef _DEBUG
void CStatusTricksView::AssertValid() const
{
	CView::AssertValid();
}

void CStatusTricksView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStatusTricksDoc* CStatusTricksView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusTricksDoc)));
	return (CStatusTricksDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksView message handlers
void CStatusTricksView::OnInitialUpdate() 
{
		HD_ITEM		 hItem;		// new header item to insert
		CRect		 client;	// rect binding the client

	// default processing
	CView::OnInitialUpdate();

	// pick up the client rect
	GetClientRect(&client);

	// insert a header item
	hItem.mask = HDI_FORMAT | HDI_WIDTH;
	hItem.cxy = client.Width() / 2;
	hItem.fmt = HDF_OWNERDRAW;
	m_hdrCtrl.InsertItem(0, &hItem);
	m_hdrCtrl.InsertItem(1, &hItem);
}

int CStatusTricksView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
		int			 failure;		// indicates creation failure

	// if default processing is ok
	if ((failure = CView::OnCreate(lpCreateStruct)) != -1)
	{
		// if we can create the header control
		if (m_hdrCtrl.Create(WS_CHILD | WS_VISIBLE | CCS_TOP | CCS_NOMOVEY |
			HDS_BUTTONS | HDS_HORZ, CRect(0, 0, 0, 20), this, IDC_HEADER1))
		{
		}

		// else the header control failed
		else
		{
			failure = -1;
		}
	}
	return failure;
}

void CStatusTricksView::OnSize(UINT nType, int cx, int cy) 
{
	// default processing
	CView::OnSize(nType, cx, cy);

	// if the header control has been created
	if (m_hdrCtrl.m_hWnd)
	{
		// resize the control
		m_hdrCtrl.MoveWindow(0, 0, cx, 20);
	}
}

void CStatusTricksView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
		CDC			 dc;		// dc for drawing the control

	// handle the drawing according to the control needing to be drawn
	switch (nIDCtl)
	{
		case IDC_HEADER1:
			// attach the dc to the supplied dc
			dc.Attach(lpDrawItemStruct->hDC);

			// draw the header control according to the item
			switch (lpDrawItemStruct->itemID)
			{
				case 0:
					dc.DrawText("Doug is King", &lpDrawItemStruct->rcItem, DT_LEFT);
					break;

				case 1:
					dc.DrawText("Bob is a girl", &lpDrawItemStruct->rcItem, DT_LEFT);
					break;
			}

			// restore the dc
			dc.Detach();
			break;

		default:
			// default processing
			CView::OnDrawItem(nIDCtl, lpDrawItemStruct);
			break;
	}
}
