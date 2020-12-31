// MDIView.cpp : implementation of the CMDIView class
//

#include "stdafx.h"
#include "MDI.h"
#include "MDIDoc.h"
#include "MDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIView

IMPLEMENT_DYNCREATE(CMDIView, CView)

BEGIN_MESSAGE_MAP(CMDIView, CView)
	//{{AFX_MSG_MAP(CMDIView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, OnEndlabeleditTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIView construction/destruction

CMDIView::CMDIView()
  : m_pTree(0)
{
	TRACE(_T("in CMDIView::CMDIView\n"));
}

CMDIView::~CMDIView()
{
	if (m_pTree)
		delete m_pTree;
	m_pTree = 0;
}

BOOL CMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIView drawing

void CMDIView::OnDraw(CDC* /*pDC*/)
{
	CMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIView printing

BOOL CMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CMDIView diagnostics

#ifdef _DEBUG
void CMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIDoc* CMDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIDoc)));
	return (CMDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIView message handlers

int CMDIView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TRACE(_T("in CMDIView::OnCreate\n"));

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pTree = new CXHtmlTree();
	ASSERT(m_pTree);

	// note:  TVS_NOTOOLTIPS is set in CXHtmlTree::PreCreateWindow()

	DWORD dwStyle = TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | 
					TVS_EDITLABELS | TVS_SHOWSELALWAYS | /*TVS_NOTOOLTIPS |*/
					WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP | WS_BORDER;

	CRect rect(0,0,100,100);

	VERIFY(m_pTree->Create(dwStyle, rect, this, IDC_TREE));

	return 0;
}

void CMDIView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// create image list for level 0 items
	m_Images.Create(IDB_DOGS, 16, 9, RGB(0,255,255));
	m_pTree->SetImageList(&m_Images, TVSIL_NORMAL);

	m_pTree->Initialize(TRUE, TRUE);
	m_pTree->SetSmartCheckBox(TRUE);
	m_pTree->SetHtml(TRUE);
	m_pTree->SetImages(TRUE);

	CXHtmlTree::ConvertAction eConvertAction = CXHtmlTree::NoConvertAction;

#ifdef UNICODE
	eConvertAction = CXHtmlTree::ConvertToUnicode;
#endif

	m_pTree->LoadXmlFromResource(NULL, _T("IDU_DOGS"), _T("TEXT"), eConvertAction);
}

void CMDIView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_pTree && ::IsWindow(m_pTree->m_hWnd))
	{
		// stretch tree to fill window
		m_pTree->MoveWindow(0, 0, cx, cy);
	}
}

void CMDIView::OnEndlabeleditTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE(_T("in CMDIView::OnEndlabeleditTree\n"));
	
	*pResult = TRUE;			// return TRUE to accept edit

	NMTVDISPINFO* pTVDispInfo = (NMTVDISPINFO*) pNMHDR;
	HTREEITEM hItem = pTVDispInfo->item.hItem;
	ASSERT(hItem);

	LPTSTR pszText = pTVDispInfo->item.pszText;
	if (pszText && (*pszText == _T('\0')))
		*pResult = FALSE;		// don't allow empty label
}

//=============================================================================
// OnSelchangedTree
//
// This function shows how to handle TVN_SELCHANGED messages from XHtmlTree.
//
void CMDIView::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
//=============================================================================
{
	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;
	
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	CString strItem = m_pTree->GetItemText(hItem);
	TRACE(_T("in CMDIView::OnSelchangedTree:  <%s>\n"), strItem);

	*pResult = 0;
}
