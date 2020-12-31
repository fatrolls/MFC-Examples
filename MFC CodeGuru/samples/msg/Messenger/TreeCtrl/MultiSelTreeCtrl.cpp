///////////////////////////////////////////////////////////////////////////////
// 
// CMultiSelTreeCtrl - Multiple selection tree control (MFC 4.2)
// 
// Bendik Engebretsen (c) 1997 
// bendik@techsoft.no
// http://www.techsoft.no/bendik/
//
// Oct 9,  1997 : Fixed problem with notification to parent (TVN_BEGINDRAG)
// Oct 17, 1997 : Fixed bug with deselection when collapsing node with no sibling
// Nov 5,  1997 : Fixed problem with label editing
// Feb 17, 1998 : Fixed another notfication to parent (TVN_KEYDOWN)
// Apr 27, 1998	: Added TVN_SELCHANGED notification to parent in SelectMultiple()
//

#include "stdafx.h"
#include "MultiSelTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiSelTreeCtrl

BEGIN_MESSAGE_MAP(CMultiSelTreeCtrl, CTreeCtrlEx)
	//{{AFX_MSG_MAP(CMultiSelTreeCtrl)
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_KEYDOWN()
		ON_NOTIFY_REFLECT_EX(TVN_ITEMEXPANDING, OnItemExpanding)
		ON_NOTIFY_REFLECT_EX(NM_SETFOCUS, OnSetfocus)
		ON_NOTIFY_REFLECT_EX(NM_KILLFOCUS, OnKillfocus)
		ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMultiSelTreeCtrl, CTreeCtrlEx)


/////////////////////////////////////////////////////////////////////////////
// CMultiSelTreeCtrl message handlers


///////////////////////////////////////////////////////////////////////////////
// The tree control dosn't support multiple selection. However we can simulate 
// it by taking control of the left mouse click and arrow key press before the
// control gets them, and setting/clearing the TVIS_SELECTED style on the items

void CMultiSelTreeCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	
	UINT nHitFlags = 0;
	CTreeCursor hClickedItem = HitTest( point, &nHitFlags );
	
	// Must invoke label editing explicitly. The base class OnLButtonDown would normally
	// do this, but we can't call it here because of the multiple selection...
	if( nHitFlags & LVHT_ONITEMLABEL )
	{
		if ( hClickedItem == GetSelectedItem() )
		{
			EditLabel( hClickedItem );
			return;
		}
		
		if( nHitFlags & LVHT_ONITEM )
		{
			SetFocus();
			
			m_hClickedItem = hClickedItem;
			
			// Is the clicked item already selected ?
			BOOL bIsClickedItemSelected = GetItemState( hClickedItem, TVIS_SELECTED ) & TVIS_SELECTED;
			
			if ( bIsClickedItemSelected )
			{
				// Maybe user wants to drag/drop multiple items!
				// So, wait until OnLButtonUp() to do the selection stuff. 
				m_bSelectPending = TRUE;
				m_ptClick = point;
			}
			else
			{
				SelectMultiple( hClickedItem, nFlags );
				m_bSelectPending = FALSE;
			}
		}
	}
	else
	{
		CTreeCtrlEx::OnLButtonDown( nFlags, point );
	}
}

void CMultiSelTreeCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	if ( m_bSelectPending )
	{
		// A select has been waiting to be performed here
		SelectMultiple( m_hClickedItem, nFlags );
		m_bSelectPending = FALSE;
	}
	
	m_hClickedItem = CTreeCursor();
	
	CTreeCtrlEx::OnLButtonUp( nFlags, point );
}


void CMultiSelTreeCtrl::OnMouseMove( UINT nFlags, CPoint point )
{
	// If there is a select pending, check if cursor has moved so much away from the 
	// down-click point that we should cancel the pending select and initiate
	// a drag/drop operation instead!
	
	if ( m_hClickedItem )
	{
		CSize sizeMoved = m_ptClick - point;
		
		if ( abs(sizeMoved.cx) > GetSystemMetrics( SM_CXDRAG ) || abs(sizeMoved.cy) > GetSystemMetrics( SM_CYDRAG ) )
		{
			m_bSelectPending = FALSE;
			
			// Notify parent that he may begin drag operation
			// Since we have taken over OnLButtonDown(), the default handler doesn't
			// do the normal work when clicking an item, so we must provide our own
			// TVN_BEGINDRAG notification for the parent!
			
			CWnd* pWnd = GetParent();
			if ( pWnd )
			{
				NM_TREEVIEW tv;
				
				tv.hdr.hwndFrom = GetSafeHwnd();
				tv.hdr.idFrom = GetWindowLong( GetSafeHwnd(), GWL_ID );
				tv.hdr.code = TVN_BEGINDRAG;
				
				tv.itemNew.hItem = m_hClickedItem;
				tv.itemNew.state = GetItemState( m_hClickedItem, 0xffffffff );
				tv.itemNew.lParam = GetItemData( m_hClickedItem );
				
				tv.ptDrag.x = point.x;
				tv.ptDrag.y = point.y;
				
				pWnd->SendMessage( WM_NOTIFY, tv.hdr.idFrom, (LPARAM)&tv );
			}
			
			m_hClickedItem = CTreeCursor();
		}
	}
	
	CTreeCtrlEx::OnMouseMove( nFlags, point );
}


void CMultiSelTreeCtrl::SelectMultiple( CTreeCursor &hClickedItem, UINT nFlags )
{
	// Start preparing an NM_TREEVIEW struct to send a notification after selection is done
	NM_TREEVIEW tv;
	CTreeCursor hOldItem = GetSelectedItem();
	tv.itemOld.hItem = hOldItem;
	tv.itemOld.state = GetItemState( hOldItem, 0xffffffff );
	tv.itemOld.lParam = GetItemData( hOldItem );
	tv.itemOld.mask = TVIF_HANDLE|TVIF_STATE|TVIF_PARAM;
	
	// Action depends on whether the user holds down the Shift or Ctrl key
	if ( nFlags & MK_SHIFT )
	{
		// Select from first selected item to the clicked item
		if ( !m_hFirstSelectedItem )
			m_hFirstSelectedItem=GetSelectedItem();
		
		SelectItems( m_hFirstSelectedItem, hClickedItem );
	}
	else 
	{
		if ( nFlags & MK_CONTROL )
		{
			// Find which item is currently selected
			CTreeCursor hSelectedItem = GetSelectedItem();
			
			// Is the clicked item already selected ?
			BOOL bIsClickedItemSelected = GetItemState( hClickedItem, TVIS_SELECTED ) & TVIS_SELECTED;
			BOOL bIsSelectedItemSelected = GetItemState( hSelectedItem, TVIS_SELECTED ) & TVIS_SELECTED;
			
			// Select the clicked item (this will also deselect the previous one!)
			SelectItem( hClickedItem );
			
			// If the previously selected item was selected, re-select it
			if ( bIsSelectedItemSelected )
				SetItemState( hSelectedItem, TVIS_SELECTED, TVIS_SELECTED );
			
			// We want the newly selected item to toggle its selected state,
			// so unselect now if it was already selected before
			if ( bIsClickedItemSelected )
				SetItemState( hClickedItem, 0, TVIS_SELECTED );
			else
				SetItemState( hClickedItem, TVIS_SELECTED, TVIS_SELECTED );
			
			// Store as first selected item (if not already stored)
			if ( m_hFirstSelectedItem==NULL )
				m_hFirstSelectedItem = hClickedItem;
		}
		else
		{
			// Clear selection of all "multiple selected" items first
			ClearSelection();
			
			// Then select the clicked item
			SelectItem( hClickedItem );
			SetItemState( hClickedItem, TVIS_SELECTED, TVIS_SELECTED );
			
			// Store as first selected item
			m_hFirstSelectedItem = hClickedItem;
		}
	}
	
	// Notify that selection has changed, by sending a TVN_SELCHANGED notification
	CWnd* pWnd = GetParent();
	if ( pWnd )
	{
		tv.hdr.hwndFrom = GetSafeHwnd();
		tv.hdr.idFrom = GetWindowLong( GetSafeHwnd(), GWL_ID );
		tv.hdr.code = TVN_SELCHANGED;
		
		tv.itemNew.hItem = m_hClickedItem;
		tv.itemNew.state = GetItemState( m_hClickedItem, 0xffffffff );
		tv.itemNew.lParam = GetItemData( m_hClickedItem );
		tv.itemNew.mask = TVIF_HANDLE|TVIF_STATE|TVIF_PARAM;
		
		tv.action = TVC_UNKNOWN;
		
		pWnd->SendMessage( WM_NOTIFY, tv.hdr.idFrom, (LPARAM)&tv );
	}
}

void CMultiSelTreeCtrl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
	if ( nChar == VK_UP || nChar == VK_DOWN )
	{
		if ( !( GetKeyState( VK_SHIFT )&0x8000 ) )
		{
			// User pressed arrow key without holding 'Shift':
			// Clear multiple selection and let base class do normal 
			// selection work!
			ClearSelection( TRUE );
			CTreeCtrlEx::OnKeyDown( nChar, nRepCnt, nFlags );
			return;
		}
		
		// Find which item is currently selected
		CTreeCursor hSelectedItem = GetSelectedItem();
		
		CTreeCursor hNextItem;
		if ( nChar==VK_UP )
			hNextItem = GetPrevVisibleItem( hSelectedItem );
		else
			hNextItem = GetNextVisibleItem( hSelectedItem );
		
		if ( hNextItem )
		{
			// If the next item is already selected, we assume user is
			// "moving back" in the selection, and thus we should clear 
			// selection on the previous one
			BOOL bSelect = !( GetItemState( hNextItem, TVIS_SELECTED ) & TVIS_SELECTED );
			
			// Select the next item (this will also deselect the previous one!)
			SelectItem( hNextItem );
			
			// Now, re-select the previously selected item
			if ( bSelect )
				SetItemState( hSelectedItem, TVIS_SELECTED, TVIS_SELECTED );
		}
		
		// Since the base class' OnKeyDown() isn't called in this case,
		// we must provide our own TVN_KEYDOWN notification to the parent
		
		CWnd* pWnd = GetParent();
		if ( pWnd )
		{
			NMTVKEYDOWN tvk;
			
			tvk.hdr.hwndFrom = GetSafeHwnd();
			tvk.hdr.idFrom = GetWindowLong( GetSafeHwnd(), GWL_ID );
			tvk.hdr.code = TVN_KEYDOWN;
			
			tvk.wVKey = (WORD)nChar;
			tvk.flags = 0;
			
			pWnd->SendMessage( WM_NOTIFY, tvk.hdr.idFrom, (LPARAM)&tvk );
		}
	}
	else
		// Behave normally
		CTreeCtrlEx::OnKeyDown( nChar, nRepCnt, nFlags );
}


///////////////////////////////////////////////////////////////////////////////
// I want clicking on an item with the right mouse button to select the item,
// but not if there is currently a multiple selection

void CMultiSelTreeCtrl::OnRButtonDown( UINT nFlags, CPoint point )
{
	UINT nHitFlags = 0;
	CTreeCursor hClickedItem = HitTest( point, &nHitFlags );
	
	if( nHitFlags&LVHT_ONITEM )
	{
		if ( GetSelectedCount() < 2 )
		{
			SelectItem( hClickedItem );
		}
	}
		
	CTreeCtrlEx::OnRButtonDown( nFlags, point );
}


///////////////////////////////////////////////////////////////////////////////
// Get number of selected items

UINT CMultiSelTreeCtrl::GetSelectedCount()
{
	// Only visible items should be selected!
	UINT uCount = 0;
	for (CTreeCursor hItem = GetRootItem(); hItem != NULL; hItem = GetNextVisibleItem( hItem ) )
	{
		if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
		{
			uCount++;
		}
	}
		
		return uCount;
}


///////////////////////////////////////////////////////////////////////////////
// Helpers to list out selected items. (Use similar to GetFirstVisibleItem(), 
// GetNextVisibleItem() and GetPrevVisibleItem()!)

CTreeCursor CMultiSelTreeCtrl::GetFirstSelectedItem()
{
	for ( CTreeCursor hItem = GetRootItem(); hItem != NULL; hItem = GetNextVisibleItem( hItem ) )
	{
		if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
		{
			return hItem;
		}
	}
		
	return CTreeCursor();
}

CTreeCursor CMultiSelTreeCtrl::GetNextSelectedItem( CTreeCursor &hItem )
{
	for ( hItem = GetNextVisibleItem( hItem ); hItem != NULL; hItem = GetNextVisibleItem( hItem ) )
	{
		if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
		{
			return hItem;
		}
	}
		
	return CTreeCursor();
}

CTreeCursor CMultiSelTreeCtrl::GetPrevSelectedItem( CTreeCursor &hItem )
{
	for ( hItem = GetPrevVisibleItem( hItem ); hItem != NULL; hItem = GetPrevVisibleItem( hItem ) )
	{
		if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
		{
			return hItem;
		}
	}
		
	return CTreeCursor();
}


///////////////////////////////////////////////////////////////////////////////
// Select/unselect item without unselecting other items

BOOL CMultiSelTreeCtrl::SelectItemEx(CTreeCursor &hItem, BOOL bSelect/*=TRUE*/)
{
	CTreeCursor hSelItem = GetSelectedItem();
	
	if ( hItem == hSelItem )
	{
		if ( !bSelect )
		{
			SelectItem(NULL);
			return TRUE;
		}
		
		return FALSE;
	}
	
	SelectItem( hItem );
	m_hFirstSelectedItem = hItem;
	
	// Reselect previous "real" selected item which was unselected byt SelectItem()
	if ( hSelItem )
	{
		SetItemState( hSelItem, TVIS_SELECTED, TVIS_SELECTED );
	}
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Select visible items between specified 'from' and 'to' item (including these!)
// If the 'to' item is above the 'from' item, it traverses the tree in reverse 
// direction. Selection on other items is cleared!

BOOL CMultiSelTreeCtrl::SelectItems( CTreeCursor &hFromItem, CTreeCursor &hToItem )
{
	// Determine direction of selection 
	// (see what item comes first in the tree)
	CTreeCursor hItem = GetRootItem();
	
	while ( hItem && hItem != hFromItem && hItem != hToItem )
		hItem = GetNextVisibleItem( hItem );
	
	if ( !hItem )
		return FALSE;	// Items not visible in tree
	
	BOOL bReverse = (hItem == hToItem);
	
	// "Really" select the 'to' item (which will deselect 
	// the previously selected item)
	
	SelectItem( hToItem );
	
	// Go through all visible items again and select/unselect
	
	hItem = GetRootItem();
	BOOL bSelect = FALSE;
	
	while ( hItem )
	{
		if ( hItem == ( bReverse ? hToItem : hFromItem ) )
			bSelect = TRUE;
		
		if ( bSelect )
		{
			if ( !( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED ) )
				SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
		}
		else
		{
			if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
				SetItemState( hItem, 0, TVIS_SELECTED );
		}
		
		if ( hItem == ( bReverse ? hFromItem : hToItem ) )
			bSelect = FALSE;
		
		hItem = GetNextVisibleItem( hItem );
	}
	
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// Clear selected state on all visible items

void CMultiSelTreeCtrl::ClearSelection(BOOL bMultiOnly/*=FALSE*/)
{
	if ( !bMultiOnly )
		SelectItem( NULL );
	
	for ( CTreeCursor hItem = GetRootItem(); hItem != NULL; hItem = GetNextVisibleItem( hItem ) )
	{
		if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
		{
			SetItemState( hItem, 0, TVIS_SELECTED );
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// If a node is collapsed, we should clear selections of its child items 

BOOL CMultiSelTreeCtrl::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	if ( pNMTreeView->action == TVE_COLLAPSE )
	{
		CTreeCursor hItem = GetChildItem( pNMTreeView->itemNew.hItem );
		
		while ( hItem )
		{
			if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
				SetItemState( hItem, 0, TVIS_SELECTED );
			
			// Get the next node: First see if current node has a child
			CTreeCursor hNextItem = GetChildItem( hItem );
			if ( !hNextItem )
			{
				// No child: Get next sibling item
				hNextItem = GetNextSiblingItem( hItem );
				if ( !( hNextItem ) )
				{
					CTreeCursor hParentItem = hItem;
					while ( !hNextItem )
					{
						// No more children: Get parent
						hParentItem = GetParentItem( hParentItem );
						if ( !( hParentItem ) )
							break;
						
						// Quit when parent is the collapsed node
						// (Don't do anything to siblings of this)
						if ( hParentItem == pNMTreeView->itemNew.hItem )
							break;
						
						// Get next sibling to parent
						hNextItem = GetNextSiblingItem( hParentItem );
					}
					
					// Quit when parent is the collapsed node
					if ( hParentItem == pNMTreeView->itemNew.hItem )
						break;
				}
			}
			
			hItem = hNextItem;
		}
	}
	
	*pResult = 0;
	return FALSE;	// Allow parent to handle this notification as well
}


///////////////////////////////////////////////////////////////////////////////
// Ensure the multiple selected items are drawn correctly when loosing/getting
// the focus

BOOL CMultiSelTreeCtrl::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;

	Invalidate();
	*pResult = 0;
	return FALSE;
}

BOOL CMultiSelTreeCtrl::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;

	Invalidate();
	*pResult = 0;
	return FALSE;
}
