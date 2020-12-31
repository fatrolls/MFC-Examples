// EXTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "include/eivaafx.h"

//#include "TreeCtrlResource.h"
#include "IXTreeItem.h"
#include "EXTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EXTreeCtrl
IMPLEMENT_DYNAMIC(EXTreeCtrl, EXWaitingTreeCtrl )

EXTreeCtrl::EXTreeCtrl() : m_hActiveItem(NULL)
{
	m_bContextMenuActivated = false;
	m_pDragImage = NULL;
	m_bLDragging = FALSE;
	m_hitemDrag = m_hitemDrop = NULL;;

	m_bDontSend = false;

	m_pIconImageList = NULL;

	m_pTreeListener = NULL;

//	m_bSelectionWasInitializedByMyself = true;

}

EXTreeCtrl::~EXTreeCtrl()
{
	if(m_pIconImageList)
	{
		m_pIconImageList->DeleteImageList();
		delete m_pIconImageList;
		m_pIconImageList = NULL;
	}

}

BEGIN_MESSAGE_MAP(EXTreeCtrl, EXWaitingTreeCtrl)
	//{{AFX_MSG_MAP(EXTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteItem)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EXTreeCtrl message handlers

BOOL EXTreeCtrl::PopulateItem(HTREEITEM hParent)
{
	IXTreeItem *pItem = NULL;

	if (hParent == TVI_ROOT && m_pRootMember != NULL)	// TOP FRAME
	{
		pItem = m_pRootMember;
	}
	else
	{
		pItem = (IXTreeItem *)GetItemData(hParent);
	}

	SetPopulationCount(0, 0);
	InsertItems(hParent,pItem);

	// set to full
	SetPopulationCount(1, 1);

	return TRUE;
}

void EXTreeCtrl::SetRootMember(IXTreeItem *pRootMember)
{
	m_pRootMember = pRootMember;
}

void EXTreeCtrl::OnViewRefresh()
{
	HTREEITEM hItem = TVI_ROOT;
	hItem = GetSelectedItem();
	RefreshSubItems(hItem);
}

BOOL EXTreeCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= /*TVS_DISABLEDRAGDROP |*/ TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS | TVS_SHOWSELALWAYS;
	return EXWaitingTreeCtrl::PreCreateWindow(cs);
}

void EXTreeCtrl::AddItem(HTREEITEM hParent, IXTreeItem *pItem/*pITreeItem*/)
{
	CString str;

	// update items count
	IncreasePopulation();

//	EBaseItem * pItem = new EBaseItem(pITreeItem);

	// prepare to insert a new item
	TVINSERTSTRUCT ins;
	ZeroMemory(& ins, sizeof(ins));

	ins.hParent = hParent;
	ins.hInsertAfter = TVI_LAST;
	// set index to stored data
	ins.item.lParam = (LPARAM)(pItem);
	// use stored resource to display text
	str = pItem->GetLabel();
	ins.item.pszText = (LPTSTR)(LPCTSTR)str;
	// set other item features
	ins.item.cChildren = pItem->IsExpandable();
	ins.item.iImage = pItem->GetImage();
	ins.item.iSelectedImage = pItem->GetSelectedImage();

//	ins.item.mask = TVIF_CHILDREN | TVIF_IMAGE | TVIF_PARAM | TVIF_TEXT;
	ins.item.mask = TVIF_CHILDREN | TVIF_IMAGE | TVIF_PARAM | TVIF_TEXT | TVIF_SELECTEDIMAGE;

	InsertItem(& ins);
}

bool EXTreeCtrl::InsertItems(HTREEITEM hParent, IXTreeItem *pParentTreeMember)
{
	if(hParent == TVI_ROOT)
	{
		AddItem(hParent, pParentTreeMember);
	}
	else
	{
		std::list<IXTreeItem *> lITreeMembers;
		if( pParentTreeMember->GetChildElements(lITreeMembers))
		{
			std::list<IXTreeItem *>::iterator It;			
			for(It = lITreeMembers.begin();It != lITreeMembers.end();It++)
			{
				AddItem(hParent, (*It));
			}
		}
	} 
	return true;
}

IXTreeItem* EXTreeCtrl::h2p(HTREEITEM h)
{
	return (IXTreeItem*)GetItemData(h);
}

HTREEITEM EXTreeCtrl::FindItemInSubTree( HTREEITEM hSubTreeRoot , IXTreeItem *pITreeItem )
{
	TRACE("searching subtree {%s} for data {%s}\n" , h2p(hSubTreeRoot)->GetLabel() , pITreeItem->GetLabel() );

	ASSERT( hSubTreeRoot!=NULL );

	HTREEITEM h=hSubTreeRoot;

	if( h != NULL )
	{
		if( h2p(h)==pITreeItem )	//root itself?
		{
			Select( h , TVGN_CARET );
			EnsureVisible( h );			
		}
		else
		{
			h = GetChildItem(h);	//first child

			while( h!=NULL )
			{
				HTREEITEM q = FindItemInSubTree( h , pITreeItem );

				if( q!=NULL )
				{
					h = q;
					break;
				}

				h = GetNextSiblingItem(h);
			}
		}
	}

	return h;
}

HTREEITEM EXTreeCtrl::FindItem(HTREEITEM hti, HTREEITEM hItem)
{
	if(hti == NULL)
		return NULL;		

	if(hti == hItem)
	{
		Select( hti, TVGN_CARET);
		EnsureVisible( hti );			
		return hti;
	}

	hti = GetChildItem( hti );	
	do	
	{		
		HTREEITEM hti_res;
		if((hti_res = FindItem( hti, hItem)) !=NULL )
		return hti_res; 
	} while( (hti = GetNextSiblingItem( hti )) != NULL );		
	return NULL;
}

IXTreeItem* EXTreeCtrl::GetSelectedTreeItem(void)
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
		return (IXTreeItem*)GetItemData( hItem );

	return NULL;
}

void EXTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bLDragging)
		return;

//	if( m_bSelectionWasInitializedByMyself )
//	{

		NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
		IXTreeItem* pItem = GetSelectedTreeItem();

		if (pItem)
		{
			if( m_pTreeListener != NULL )
			{
				m_pTreeListener->TreeNodeSelected(pItem);
			}
		}
//	}

	*pResult = 0;
}
/*
LRESULT EXTreeCtrl::SendUpdate(UINT nMessage, LPARAM nITreeMember)
{
	if(m_bDontSend)
		return 0;

	CWnd *pWnd;// = GetParentFrame();

	if((pWnd = GetParentFrame()) != NULL)
	{
		CView* pView = AS_RUNTIME_CLASS(GetParent(), CView);
 		return pWnd->SendMessage(WM_TREECTRL_SELCHANGED, (LPARAM)pView, nITreeMember);
	}
	else if((pWnd = GetParent()))
	{
 		return pWnd->SendMessage(WM_TREECTRL_SELCHANGED, (LPARAM)this, nITreeMember);
	}

	return 0;
}
*/
/*
EBaseItem* EXTreeCtrl::GetBaseItem(HTREEITEM hTi)
{
	if(!hTi)
	{
		// First see if an item is active
		if(m_hActiveItem)
		{
			hTi = m_hActiveItem;
			SelectItem(hTi);
			m_hActiveItem = 0;
		}
		else
		{
			if(m_bContextMenuActivated)
			{
				hTi = GetRootItem();
			}
			else
			{
				// Try to get active item
				hTi = GetSelectedItem();
			}
		}

		if(!hTi)
		{
			hTi = GetRootItem();
		}
	}

	if(hTi)
	{
		return reinterpret_cast < EBaseItem * > (GetItemData(hTi));
	}
	return NULL;
}
*/
void EXTreeCtrl::ExpandTree(HTREEITEM hItem,bool bIncludeSub)
{
	if(hItem == NULL)
		hItem = GetRootItem();

	if(hItem)
	{
		Expand(hItem,TVE_EXPAND);

		if(bIncludeSub)
		{
			HTREEITEM ChildItem = GetChildItem(hItem);
			while(ChildItem != NULL)
			{
				Expand(ChildItem,TVE_EXPAND);
				ExpandTree(ChildItem,true);
				ChildItem = GetNextItem(ChildItem,TVGN_NEXT);
			}
		}
	}

/*
	if(hItem == NULL)
		return;		

	Expand(hItem,TVE_EXPAND);
	HTREEITEM ChildItem = GetChildItem(hItem);
	do	
	{
		Expand(ChildItem,TVE_TOGGLE);		
	} 
	while( (ChildItem = GetNextSiblingItem( ChildItem )) != NULL );		
*/
}

void EXTreeCtrl::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TVITEM& item = ((NM_TREEVIEW*)pNMHDR)->itemOld;

	// free memory
	if (item.lParam != 0)
	{
//		delete reinterpret_cast < EBaseItem * > (item.lParam);
//		delete reinterpret_cast < IXTreeItem * > (item.lParam);
	}
	
	*pResult = 0;
}

void EXTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	ScreenToClient(&point);

	UINT uFlags;
	
	m_bContextMenuActivated = true;
	HTREEITEM hTreeItem = HitTest( point, &uFlags );
//	if(hTreeItem && hTreeItem != GetRootItem())
	if(hTreeItem)
	{
		Select(hTreeItem,TVGN_CARET);
		ClientToScreen(&point);

//		EBaseItem * pItem = (EBaseItem *)GetItemData(hTreeItem);
//		if(pItem && pItem->m_pITreeMember)
		IXTreeItem *pItem = (IXTreeItem *)GetItemData(hTreeItem);
		if(pItem)
		{
			if( m_pTreeListener != NULL )
			{
				m_pTreeListener->TreeNodeSelected(pItem);
			}

			EXMenu menu;
			menu.CreatePopupMenu();
			pItem->GetPopupMenu(menu);

			if(menu.m_hMenu != NULL)
			{
				menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, AfxGetMainWnd());
			}
		}
	}

}

void EXTreeCtrl::InitTree( IXTreeItem* pRoot , int nIconsBitmap )
{
	SetRootMember(pRoot);

	if(m_pIconImageList==NULL)
	{
		if( nIconsBitmap!=0 )
		{
//--------------
			int nBtnWidth = 16;
			m_pIconImageList = new CImageList;
			CBitmap		cBitmap;
			BITMAP		bmBitmap;
			
			HANDLE      hImage = LoadImage( AfxGetResourceHandle() , MAKEINTRESOURCE(nIconsBitmap) , IMAGE_BITMAP , 0 , 0 , LR_DEFAULTSIZE | LR_CREATEDIBSECTION );

			if( cBitmap.Attach(hImage) && cBitmap.GetBitmap(&bmBitmap) )
			{
				CSize		cSize(bmBitmap.bmWidth, bmBitmap.bmHeight); 
				int			nNbBtn	= cSize.cx/nBtnWidth;
				RGBTRIPLE*	rgb		= (RGBTRIPLE*)(bmBitmap.bmBits);
				COLORREF	rgbMask	= RGB(255,0,255);	//RGB(rgb[0].rgbtRed, rgb[0].rgbtGreen, rgb[0].rgbtBlue);
				
				if (!m_pIconImageList->Create(nBtnWidth, cSize.cy, ILC_COLOR24|ILC_MASK, nNbBtn, 0))
					return;
				
				if (m_pIconImageList->Add(&cBitmap, rgbMask) == -1)
					return;

//				SendMessage(uToolBarType, 0, (LPARAM)m_pIconImageList->m_hImageList);

//				m_pIconImageList->Detach(); 
				cBitmap.Detach();

				SetImageList( m_pIconImageList, TVSIL_NORMAL );
			}

//--------------
//			m_pIconImageList = new CImageList;
//			m_pIconImageList->Create( nIconsBitmap , 16 , 1 , RGB(255,255,255) );
//			SetImageList( m_pIconImageList, TVSIL_NORMAL );
//--------------
		}
	}

	RefreshSubItems(TVI_ROOT);
}

void EXTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE0("EXTreeCtrl::OnRClick()\n");
	// Send WM_CONTEXTMENU to self
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_hWnd, GetMessagePos());
	// Mark message as handled and suppress default handling
	*pResult = 1;
}

HTREEITEM EXTreeCtrl::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
        TV_INSERTSTRUCT	tvstruct;
        HTREEITEM	hNewItem;
        CString	sText;

        // get information of the source item
        tvstruct.item.hItem = hItem;
        tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | 
                                TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        GetItem(&tvstruct.item);  
        sText = GetItemText( hItem );
        
        tvstruct.item.cchTextMax = sText.GetLength();
        tvstruct.item.pszText = sText.LockBuffer();

        // Insert the item at proper location
        tvstruct.hParent = htiNewParent;
        tvstruct.hInsertAfter = htiAfter;
        tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
        hNewItem = InsertItem(&tvstruct);
        sText.ReleaseBuffer();

        // Now copy item data and item state.
        SetItemData( hNewItem, GetItemData( hItem ));
        SetItemState( hNewItem, GetItemState( hItem, TVIS_STATEIMAGEMASK ), 
                                                        TVIS_STATEIMAGEMASK );

//		ins.item.lParam = (LPARAM)(pItem);

        // Call virtual function to allow further processing in derived class
      //  OnItemCopied( hItem, hNewItem );

        return hNewItem;
}


void EXTreeCtrl::Moveup()
{
	// Get Item
	HTREEITEM hItem = GetDropHilightItem();
	if(hItem) 
		SelectItem(hItem);
	else
		hItem = GetSelectedItem();

	// Get previous item
	HTREEITEM hSibling = GetNextItem(hItem,TVGN_PREVIOUS);

	if(hSibling != NULL)
	{

		// Get previous to previous item
		HTREEITEM hNewItem=NULL;
		HTREEITEM hItemBefore = GetNextItem(hSibling,TVGN_PREVIOUS);
		
		if(hItemBefore != NULL)
		{
			// Insert before item
			hNewItem = CopyItem(hItem,GetParentItem(hItem),hItemBefore);
			
			// Don't delete item data
			SetItemData(hItem, NULL);
			DeleteItem(hItem);
			SelectItem(hNewItem);
		}
		else
		{
			// Insert at start
			hNewItem = CopyItem(hItem,GetParentItem(hItem),TVI_FIRST);

			// Don't delete item data
			SetItemData(hItem, NULL);
			DeleteItem(hItem);
			SelectItem(hNewItem);
		}
		
		if(hNewItem)
			RefreshSubItems(hNewItem);
	}
}

void EXTreeCtrl::Movedown() 
{
	// Get Item
	HTREEITEM hItem = GetDropHilightItem();
	if(hItem) 
		SelectItem(hItem);
	else
		hItem = GetSelectedItem();

	// Get next item
	HTREEITEM hNewItem=NULL;
	HTREEITEM hSibling = GetNextItem(hItem,TVGN_NEXT);

	if(hSibling != NULL)
	{
		// Insert before item
		hNewItem = CopyItem(hItem,GetParentItem(hItem),hSibling);

		// Don't delete item data
		SetItemData(hItem, NULL);
		DeleteItem(hItem);
		SelectItem(hNewItem);
	}
	else
	{
		// Insert at start
		hNewItem = CopyItem(hItem,GetParentItem(hItem),TVI_LAST);

		// Don't delete item data
		SetItemData(hItem, NULL);
		DeleteItem(hItem);
		SelectItem(hNewItem);
	}
	if(hNewItem)
		RefreshSubItems(hNewItem);
}


void EXTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_bContextMenuActivated = false; // Hack

	HTREEITEM	hitem;
	UINT		flags;

	if (m_bLDragging)
	{
		POINT pt = point;
		ClientToScreen( &pt );
		CImageList::DragMove(pt);
		if ((hitem = HitTest(point, &flags)) != NULL)
		{
			CImageList::DragShowNolock(FALSE);
			SelectDropTarget(hitem);
			m_hitemDrop = hitem;
			CImageList::DragShowNolock(TRUE);
		}
	}

	EXWaitingTreeCtrl::OnMouseMove(nFlags, point);
}

void EXTreeCtrl::SelectDataItem(IXTreeItem *pITreeItem)
{
	if( pITreeItem==GetSelectedTreeItem() )	//dont select the same again!
	{
		return;
	}

//--------------

	// Create Parent list
	std::list<IXTreeItem *> lParents;
	std::list<IXTreeItem *>::iterator It, ItLast;

	if(pITreeItem == NULL)
	{
		SelectItem(NULL);
		return;
	}		

	TRACE("parent-stack:\n");
	pITreeItem->GetParentList(lParents);

	TRACE("Found %i generations of parents to selected item\n",lParents.size());

	HTREEITEM hItem = GetRootItem();
	HTREEITEM hLastItem = hItem;
	It = lParents.begin();

	if( h2p(hItem)!=(*It) )		//root at top of parent stack!
	{
		SelectItem(0);
	}
	else
	{
		while( It!=lParents.end() )
		{
			//
			// current h must be the p in the parent list. if this is not the case, the
			// p reported a parent, that didn't list p as a child when expanding!
			//

			ASSERT( (*It) == h2p(hItem) );	//make sure parent lists all it's children!

			//
			// expand the node
			//

			TRACE( "expanding parent {%s}\n" , h2p(hItem)->GetLabel() );
			Expand(hItem,TVE_EXPAND);

			if( (*It)==pITreeItem )
			{
				break;
			}

			//
			// find the h of the child
			//

			It++;	//next generation...

			if( It!=lParents.end() )
			{
				IXTreeItem* pChild = *It;

				hItem = GetChildItem(hItem);	//search for the item that contains next ITreeItem

				while( hItem!=NULL )
				{
					if( h2p(hItem)==pChild )
					{
						break;					//break search and continue treating this child as the next parent
					}

					hItem = GetNextSiblingItem(hItem);
				}
			}
		}

		if(hItem)
		{
			EnsureVisible(hItem);
			SelectItem(hItem);
		}
	}

}

//bool EXTreeCtrl::BuildTreePath( IXTreeItem* pNode , std::list<IXTreeItem*>& List , IXTreeItem* pParent )
//{
//	bool bChildFound = false;
//
//	std::list<IXTreeItem*> ChildList;
//	pParent->GetChildElements(ChildList);
//
//	std::list<IXTreeItem*>::iterator iter = ChildList.begin();
//	std::list<IXTreeItem*>::iterator iend = ChildList.end();
//
//	while(iter!=iend)
//	{
//		IXTreeItem* pChild = *iter;
//
//		if( pChild==pNode )
//		{
//			List.push_front(pChild);
//			bChildFound = true;
//			break;
//		}
//		else
//		{
//			bChildFound = BuildTreePath(pNode,List,pChild);
//
//			if( bChildFound )
//			{
//				List.push_front(pParent);
//				break;
//			}
//		}
//
//		iter++;
//	}
//
//
//	return bChildFound;
//
//
//}



void EXTreeCtrl::RefreshDataItem(IXTreeItem *pITreeItem)
{
	HTREEITEM hItem = NULL;
	if(pITreeItem)
	{
		hItem = FindItemInSubTree(GetRootItem(),pITreeItem);
	}
	else
	{
		// Get Item
		hItem = GetSelectedItem();
	}			
	
	if(hItem)
	{
		IXTreeItem *pTree = (IXTreeItem*)GetItemData( hItem );
//		EBaseItem *pBase = (EBaseItem*)GetItemData( hItem );
//		IXTreeItem *pTree = pBase->m_pITreeMember;

		HTREEITEM hParentItem;
		if(hItem != GetRootItem())
			hParentItem = GetParentItem(hItem);
		else
			hParentItem = hItem;

		if(hParentItem)
		{
			RefreshSubItems(hParentItem);
			ExpandTree(hParentItem);
		
			// Find new item
			hItem = FindItemInSubTree(hParentItem,pTree);

			EnsureVisible(hItem);
			SelectItem(hItem);
		}
	}
}

void EXTreeCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
 
	// Limit text to 127 characters
	GetEditControl()->LimitText(127);
	
	*pResult = 0;
}

void EXTreeCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = FALSE;

	char buf[1024];
	CString str;

	GetEditControl()->GetLine(0,buf,1024);
	str = buf;

	HTREEITEM hItem = GetSelectedItem();
/*	EBaseItem * pItem = (EBaseItem *)GetItemData(hItem);
	if(pItem && pItem->m_pITreeMember)
	{
		if(pItem->m_pITreeMember->CanEditLabel())
		{
			pItem->m_pITreeMember->SetLabel(str);
			*pResult = TRUE;
		}
	}*/
	IXTreeItem *pItem = (IXTreeItem *)GetItemData(hItem);
	if(pItem)
	{
		if(pItem->CanEditLabel())
		{
			pItem->SetLabel(str);
			*pResult = TRUE;
		}
	}
}

void EXTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	m_hitemDrag = pNMTreeView->itemNew.hItem;
	m_hitemDrop = NULL;

	m_pDragImage = CreateDragImage(m_hitemDrag);  // get the image list for dragging
	// CreateDragImage() returns NULL if no image list
	// associated with the tree view control
	if( !m_pDragImage )
		return;

	m_bLDragging = TRUE;
	m_pDragImage->BeginDrag(0, CPoint(-15,-15));
	POINT pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter(NULL, pt);
	SetCapture();
}

void EXTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	EXWaitingTreeCtrl::OnLButtonUp(nFlags, point);
	if (m_bLDragging)
	{
		m_bLDragging = FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();

		delete m_pDragImage;

		// Remove drop target highlighting
		SelectDropTarget(NULL);

		if( m_hitemDrag == m_hitemDrop )
			return;

		// If Drag item is an ancestor of Drop item then return
		HTREEITEM htiParent = m_hitemDrop;
		while( (htiParent = GetParentItem( htiParent )) != NULL )
		{
			if( htiParent == m_hitemDrag ) return;
		}

		// Move in data...
		bool bRes = false;
		HTREEITEM htiPrevParent	= GetParentItem( m_hitemDrag );
/*		EBaseItem * pFromParentItem = (EBaseItem *)GetItemData(htiPrevParent);
		EBaseItem * pToParentItem = (EBaseItem *)GetItemData(m_hitemDrop);
		EBaseItem * pDraggedItem = (EBaseItem *)GetItemData(m_hitemDrag);

		if(pFromParentItem && pFromParentItem->m_pITreeMember &&
		   pToParentItem && pToParentItem->m_pITreeMember &&
		   pDraggedItem && pDraggedItem->m_pITreeMember)
		{
			bRes = pDraggedItem->m_pITreeMember->MoveItem(pFromParentItem->m_pITreeMember,pToParentItem->m_pITreeMember);
		}*/
		IXTreeItem * pFromParentItem = (IXTreeItem *)GetItemData(htiPrevParent);
		IXTreeItem * pToParentItem = (IXTreeItem *)GetItemData(m_hitemDrop);
		IXTreeItem * pDraggedItem = (IXTreeItem *)GetItemData(m_hitemDrag);

		if(pFromParentItem && pToParentItem && pDraggedItem)
		{
			bRes = pDraggedItem->MoveItem(pFromParentItem,pToParentItem);
		}
		if(!bRes)
			return;

		// Move in tree
		Expand( m_hitemDrop, TVE_EXPAND ) ;
		HTREEITEM htiNew = CopyBranch( m_hitemDrag, m_hitemDrop, TVI_LAST );
		SelectItem( htiNew );

		if(m_hitemDrop)
			RefreshSubItems(m_hitemDrop);
	}
}

// CopyBranch           - Copies all items in a branch to a new location
// Returns              - The new branch node
// htiBranch            - The node that starts the branch
// htiNewParent - Handle of the parent for new branch
// htiAfter             - Item after which the new branch should be created
HTREEITEM EXTreeCtrl::CopyBranch( HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter /*= TVI_LAST*/ )
{
        HTREEITEM hChild;

        HTREEITEM hNewItem = CopyItem( htiBranch, htiNewParent, htiAfter );
        hChild = GetChildItem(htiBranch);
        while( hChild != NULL)
        {
                // recursively transfer all the items
                CopyBranch(hChild, hNewItem,TVI_FIRST);  
                hChild = GetNextSiblingItem( hChild );
        }

		// Don't delete item data only treeitem..
		SetItemData(htiBranch, NULL);
		DeleteItem(htiBranch);

        return hNewItem;
}
