// TabTestView.cpp : implementation of the CTabTestView class
//

#include "stdafx.h"
#include "TabCtrlAdvanced.h"
#include "TabTest.h"

#include "TabTestDoc.h"
#include "TabTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTestView

IMPLEMENT_DYNCREATE(CTabTestView, CView)

BEGIN_MESSAGE_MAP(CTabTestView, CView)
	//{{AFX_MSG_MAP(CTabTestView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTestView construction/destruction

CTabTestView::CTabTestView()
{
	// TODO: add construction code here
	m_pTab = new CTabCtrlAdvanced;
}

CTabTestView::~CTabTestView()
{

	delete m_pTab;
}

BOOL CTabTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTabTestView drawing

void CTabTestView::OnDraw(CDC* pDC)
{
	CTabTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rcClient;
	GetClientRect(rcClient);
	if( ::IsWindow(m_pTab->m_hWnd) )
		m_pTab ->MoveWindow(0,0,rcClient.Width(),rcClient.Height());
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTabTestView printing

BOOL CTabTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTabTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTabTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTabTestView diagnostics

#ifdef _DEBUG
void CTabTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTabTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTabTestDoc* CTabTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabTestDoc)));
	return (CTabTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabTestView message handlers

void CTabTestView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CTabTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CRect rc(0,0,100,100);
	m_pTab-> Create( TCS_FIXEDWIDTH | 
					 TCS_MULTILINE | 
					 WS_CLIPCHILDREN | 
					 WS_VISIBLE /*|
					 TCS_OWNERDRAWFIXED*/ , 
						rc, this, 42);

	// TODO: Add your specialized code here and/or call the base class
	TC_ITEM item;
	CTabItemInfo* pData = new CTabItemInfo;
	pData ->m_strText = "Number One";
	pData ->m_Color   = RGB(0,255,0);

    item. mask			= TCIF_PARAM;
    item. pszText		= NULL;
    item. cchTextMax	= 0;
    item. iImage		= 0;
    item. lParam		= (long)pData;

	m_pTab ->InsertItem( 0, &item );
	
	CTabItemInfo* pData2 = new CTabItemInfo;
	pData2 ->m_strText = "Number Two";
	pData2 ->m_Color   = RGB(0,0,255);

	item. lParam		= (long)pData2;

	m_pTab ->InsertItem( 1, &item );

	
}

BOOL CTabTestView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}


void CTabTestView::OnDestroy() 
{
	for(int ix = 0; ix < m_pTab->GetItemCount(); )
	{
		TC_ITEM item;
		item.mask = TCIF_PARAM;
		m_pTab->GetItem(0,&item);
		CTabItemInfo* pData = (CTabItemInfo*)item. lParam;
		ASSERT( pData-> IsKindOf(RUNTIME_CLASS(CTabItemInfo)) );
		delete pData;
		m_pTab->DeleteItem(0);
	}
	CView::OnDestroy();	
}
