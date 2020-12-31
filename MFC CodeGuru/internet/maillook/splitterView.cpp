// splitterView.cpp : implementation of the CSplitterView class
//

#include "stdafx.h"
#include "splitter.h"

#include "splitterDoc.h"
#include "splitterView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterView

IMPLEMENT_DYNCREATE(CSplitterView, CTreeView)

BEGIN_MESSAGE_MAP(CSplitterView, CTreeView)
	//{{AFX_MSG_MAP(CSplitterView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterView construction/destruction

CSplitterView::CSplitterView()
{
	m_pCImageList = NULL;
	m_bInit = FALSE;

}

CSplitterView::~CSplitterView()
{
	if(m_pCImageList)
		delete m_pCImageList;
}

BOOL CSplitterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView drawing

void CSplitterView::OnDraw(CDC* pDC)
{
	CSplitterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CSplitterView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	if(!m_bInit)
	{
		m_bInit = TRUE;
		CTreeCtrl& cThisTree = GetTreeCtrl();

		// load bitmaps for drive types & desktop - ten images
		CBitmap bitmap;
		m_pCImageList = new CImageList();
		// 16x16 pixels, 8 of them
		m_pCImageList->Create(16, 16, ILC_COLOR16, 1, 4);

		bitmap.LoadBitmap(IDB_BITMAP1);
		m_pCImageList->Add( &bitmap, (COLORREF)0x000000);
		bitmap.DeleteObject();			

		cThisTree.SetImageList( m_pCImageList, TVSIL_NORMAL );
		FillThisTree();
	}
}

void CSplitterView::FillThisTree()
{
	CWaitCursor cWait;
	CTreeCtrl& cThisTree = GetTreeCtrl();

	TRACE("--void CMTreeView::FillEmptyTree(void)\n");	
	// form the one and only tree root - the desktop
	TV_INSERTSTRUCT	structInsert;

	// Create Root
	structInsert.hParent = NULL;
	structInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	structInsert.item.iImage = 0; 
	structInsert.item.iSelectedImage = 0; 
	structInsert.item.pszText = (LPSTR)"EMail Folders";
	HTREEITEM hRoot = cThisTree.InsertItem(&structInsert);

	structInsert.hParent = hRoot;
	structInsert.item.pszText = _T("Item");
	structInsert.item.iImage = 0; // IDB_DOC
	structInsert.item.iSelectedImage = 0; //IDB_DOC_OPEN
	for(int i=0;i<100;i++)
		cThisTree.InsertItem(&structInsert);
}
/////////////////////////////////////////////////////////////////////////////
// CSplitterView diagnostics

#ifdef _DEBUG
void CSplitterView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSplitterView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CSplitterDoc* CSplitterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitterDoc)));
	return (CSplitterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitterView message handlers

BOOL CSplitterView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;		
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
