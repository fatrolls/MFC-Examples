// dragView.cpp : implementation of the CDragView class
//

#include "stdafx.h"
#include "drag.h"

#include "dragDoc.h"
#include "dragView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragView

IMPLEMENT_DYNCREATE(CDragView, CTreeView)

BEGIN_MESSAGE_MAP(CDragView, CTreeView)
	//{{AFX_MSG_MAP(CDragView)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragView construction/destruction

CDragView::CDragView()
	: m_pDragImage(NULL), 
	  m_htiDrag(NULL), 
	  m_htiDrop(NULL),
	  m_htiOldDrop(NULL),
	  m_bLDragging(false),
	  m_idTimer(0)
{

}

CDragView::~CDragView()
{
}

BOOL CDragView::PreCreateWindow(CREATESTRUCT& cs)
{
	if( CTreeView::PreCreateWindow(cs) == FALSE )
		return FALSE;

	cs.style |= TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDragView drawing

void CDragView::OnDraw(CDC* pDC)
{
	CDragDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CDragView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CTreeCtrl& theTree = GetTreeCtrl();
	
	CImageList* pImage = new CImageList;
	pImage->Create( IDR_IMAGE, 16, 1, ::GetSysColor(COLOR_WINDOW) );
	theTree.SetImageList( pImage, TVSIL_NORMAL );

	TVINSERTSTRUCT insert;
	::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );

	TVITEM item;
	::ZeroMemory( &item, sizeof(TVITEM) );

	item.mask = TVIF_IMAGE|TVIF_TEXT;
	item.pszText = "Root Item";
	item.iImage  = 0;
	insert.hParent = TVI_ROOT;
	insert.hInsertAfter = TVI_LAST;
	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
	
	HTREEITEM hParent = theTree.InsertItem( &insert );

	item.pszText = "Branch";
	insert.hParent = hParent;
	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
	for( int i = 0; i < 10; i++ )
		theTree.InsertItem( &insert );

	item.mask = TVIF_IMAGE|TVIF_TEXT;
	item.pszText = "Root Item";
	item.iImage  = 0;
	insert.hParent = TVI_ROOT;
	insert.hInsertAfter = TVI_LAST;
	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );

	hParent = theTree.InsertItem( &insert );

	item.pszText = "Branch";
	insert.hParent = hParent;
	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
	for( i = 0; i < 10; i++ )
		theTree.InsertItem( &insert );
}

/////////////////////////////////////////////////////////////////////////////
// CDragView diagnostics

#ifdef _DEBUG
void CDragView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDragView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CDragDoc* CDragView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDragDoc)));
	return (CDragDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDragView message handlers

void CDragView::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_htiDrag = pNMTreeView->itemNew.hItem;
	m_htiDrop = NULL;

	m_pDragImage = GetTreeCtrl().CreateDragImage( m_htiDrag );
	if( !m_pDragImage )
		return;

	m_bLDragging = true;

	CPoint pt(0,0);
	
	IMAGEINFO ii;
	m_pDragImage->GetImageInfo( 0, &ii );
	pt.x = (ii.rcImage.right - ii.rcImage.left) / 2;
	pt.y = (ii.rcImage.bottom - ii.rcImage.top) / 2;

	m_pDragImage->BeginDrag( 0, pt );
	pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter(NULL,pt);
	
	SetCapture();

	*pResult = 0;
}

void CDragView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeView::OnLButtonUp(nFlags, point);

	if( m_bLDragging )
	{
		CTreeCtrl& theTree = GetTreeCtrl();

		m_bLDragging = false;

		CImageList::DragLeave(this);
		CImageList::EndDrag();

		ReleaseCapture();

		delete m_pDragImage;

		theTree.SelectDropTarget(NULL);
		m_htiOldDrop = NULL;

		if( m_htiDrag == m_htiDrop )
			return;

		HTREEITEM htiParent = m_htiDrop;
		while( (htiParent = theTree.GetParentItem(htiParent)) != NULL )
		{
			if( htiParent == m_htiDrag ) return;
		}

		theTree.Expand( m_htiDrop, TVE_EXPAND );

		HTREEITEM htiNew = CopyBranch( m_htiDrag, m_htiDrop, TVI_LAST );
		theTree.DeleteItem(m_htiDrag);
		theTree.SelectItem( htiNew );

		if( m_idTimer )
		{
			KillTimer( m_idTimer );
			m_idTimer = 0;
		}
	}
}

void CDragView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTreeView::OnMouseMove(nFlags, point);

	HTREEITEM hti;
	UINT      flags;

	if( m_bLDragging )
	{
		CTreeCtrl& theTree = GetTreeCtrl();
		POINT pt = point;
		ClientToScreen( &pt );
		CImageList::DragMove(pt);
		
		hti = theTree.HitTest(point,&flags);
		if( hti != NULL )
		{
			CImageList::DragShowNolock(FALSE);

			if( m_htiOldDrop == NULL )
				m_htiOldDrop = theTree.GetDropHilightItem();

			theTree.SelectDropTarget(hti);
			
			m_htiDrop = hti;
			
			if( m_idTimer && hti == m_htiOldDrop )
			{
				KillTimer( m_idTimer );
				m_idTimer = 0;
			}
			
			if( !m_idTimer )
				m_idTimer = SetTimer( 1000, 2000, NULL );

			CImageList::DragShowNolock(TRUE);
		}
	}
}

HTREEITEM CDragView::CopyItem
	(
		HTREEITEM hti,
		HTREEITEM htiNewParent,
		HTREEITEM htiAfter // = TVI_LAST
	)
{
	CTreeCtrl& theTree = GetTreeCtrl();

	TVINSERTSTRUCT insert;
	::ZeroMemory(&insert, sizeof(TVINSERTSTRUCT));

	HTREEITEM htiNew = NULL;
	CString text;

	insert.item.hItem = hti;
	insert.item.mask = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	theTree.GetItem(&(insert.item));
	text = theTree.GetItemText( hti );

	insert.item.cchTextMax = text.GetLength();
	insert.item.pszText = text.LockBuffer();

	insert.hParent = htiNewParent;
	insert.hInsertAfter = htiAfter;
	insert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	htiNew = theTree.InsertItem(&insert);
	text.UnlockBuffer();

	theTree.SetItemData( htiNew, theTree.GetItemData( hti ) );
	theTree.SetItemState( htiNew, theTree.GetItemState( hti, TVIS_STATEIMAGEMASK ), TVIS_STATEIMAGEMASK );

	return htiNew;
}

HTREEITEM CDragView::CopyBranch
	(
		HTREEITEM hti,
		HTREEITEM htiNewParent,
		HTREEITEM htiAfter // = TVI_LAST
	)
{
	CTreeCtrl& theTree = GetTreeCtrl();

	HTREEITEM htiChild = NULL;

	HTREEITEM htiNew = CopyItem( hti, htiNewParent, htiAfter );
	htiChild = theTree.GetChildItem( hti );
	while( htiChild != NULL )
	{
		CopyBranch( htiChild, htiNew );
		htiChild = theTree.GetNextSiblingItem( htiChild );
	}

	return htiNew;
}

void CDragView::OnDestroy() 
{
	CImageList* pImage = GetTreeCtrl().GetImageList( TVSIL_NORMAL );
	delete pImage;

	if( m_idTimer )
	{
		KillTimer( m_idTimer );
		m_idTimer = 0;
	}

	CTreeView::OnDestroy();
}

void CDragView::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == m_idTimer )
	{
		CTreeCtrl& theTree = GetTreeCtrl();
		HTREEITEM htiFloat = theTree.GetDropHilightItem();
		if( htiFloat && htiFloat == m_htiDrop )
		{
			if( theTree.ItemHasChildren( htiFloat ) )
				theTree.Expand( htiFloat, TVE_EXPAND );
		}
	}

	CTreeView::OnTimer(nIDEvent);
}
