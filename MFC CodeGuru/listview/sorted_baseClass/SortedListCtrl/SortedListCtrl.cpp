#include "stdafx.h"
#include "SortedListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*----------------------------------------------------------------------------*/

BEGIN_MESSAGE_MAP(CSortedListCtrl, CListCtrl)

	//{{AFX_MSG_MAP(CSortedListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteItem)
	//}}AFX_MSG_MAP

	ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
	ON_MESSAGE(LVM_SETTEXTCOLOR, OnSetTextColor)
	ON_MESSAGE(LVM_SETTEXTBKCOLOR, OnSetTextBkColor)
	ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)

END_MESSAGE_MAP()

/*----------------------------------------------------------------------------*/

const int CSortedListCtrl::NOT_SORTED = CSortedHeaderCtrl::NOT_SORTED;

/*----------------------------------------------------------------------------*/

CSortedListCtrl::CSortedListCtrl(BOOL EnableSorting, BOOL DeleteItemData)
{
	m_bClientWidthSel=FALSE;

	m_cxClient=0;
	m_cxStateImageOffset=0;

	m_clrText=::GetSysColor(COLOR_WINDOWTEXT);
	m_clrTextBk=::GetSysColor(COLOR_WINDOW);
	m_clrBkgnd=::GetSysColor(COLOR_WINDOW);

	m_SeparatorLines = FALSE;
	m_Sorting = EnableSorting;
	m_bFullRowSel = FALSE;
    m_bDeleteItemData = DeleteItemData;
}

/*----------------------------------------------------------------------------*/

CSortedListCtrl::~CSortedListCtrl()
{
}

/*----------------------------------------------------------------------------*/

BOOL CSortedListCtrl::IsAscSorted ()
{
	// Delegate function to header control
	return m_HeaderCtrl.IsAscSorted();
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::EnableSeparatorLines (BOOL Enable)
{
	m_SeparatorLines = Enable;
}

/*----------------------------------------------------------------------------*/

int CSortedListCtrl::GetSortedColumn()
{
	// Delegate function to header control
	return m_HeaderCtrl.GetSortedColumn();
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();

	if (m_Sorting) {
		//Item 0 is the Header Control		
		m_HeaderCtrl.SubclassWindow(::GetDlgItem(m_hWnd,0));
	}
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::SortColumn (int nCol, BOOL bAsc)
{
	if (m_Sorting) {
		// First set the sort order and column and draw the header
		// This must be called before SortItems to set sort order and column 
		if ((GetStyle() & LVS_TYPEMASK) == LVS_REPORT) {
			m_HeaderCtrl.SetSortImage(nCol, bAsc);
		}
		// Now sort all items in column using CListCtrl sorting mechanism
		SortItems(&CallbackCompareItems, reinterpret_cast<LPARAM>(this));
	}
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::ReSort ()
{
    ASSERT(GetSortedColumn() != NOT_SORTED);
    SortColumn(GetSortedColumn(), IsAscSorted());
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	bool bSortAscending;

	// If clicked on already sorted column, reverse sort order
    if(pNMListView->iSubItem == GetSortedColumn()) {
		bSortAscending = !IsAscSorted();
	}
    else {
        bSortAscending = TRUE;
	}
	SortColumn(pNMListView->iSubItem, bSortAscending);

	*pResult = 0;
}

/*----------------------------------------------------------------------------*/

int CALLBACK CSortedListCtrl::CallbackCompareItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParam3)
{
	CSortedListCtrl* pSortedList = reinterpret_cast<CSortedListCtrl *>(lParam3);
	CItemInfo *pItemInfo1 = reinterpret_cast<CItemInfo*>(lParam1);
	CItemInfo *pItemInfo2 = reinterpret_cast<CItemInfo*>(lParam2);

	return pSortedList->CompareItems (pItemInfo1, pItemInfo2);
}

/*----------------------------------------------------------------------------*/

int CSortedListCtrl::CompareItems(CItemInfo *pItemInfo1, CItemInfo *pItemInfo2)
{
	return 0;
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::DrawSeparatorLines() 
{
	if (m_SeparatorLines) {

		// Draw the lines only for LVS_REPORT mode
		if( (GetStyle() & LVS_TYPEMASK) == LVS_REPORT )	
		{
			// Get the number of columns
			CClientDC dc(this );
			CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
			int nColumnCount = pHeader->GetItemCount();

			// The bottom of the header corresponds to the top of the line
			RECT rect;
			pHeader->GetClientRect( &rect );
			int top = rect.bottom;

			// Now get the client rect so we know the line length and
			// when to stop
			GetClientRect( &rect );

			// The border of the column is offset by the horz scroll
			int borderx = 0 - GetScrollPos( SB_HORZ );
			for( int i = 0; i < nColumnCount; i++ )	
			{
				// Get the next border
				borderx += GetColumnWidth( i );

				// if next border is outside client area, break out
				if( borderx >= rect.right ) break;

				// Draw the line.
				dc.MoveTo( borderx-1, top);
				dc.LineTo( borderx-1, rect.bottom );
			}
		}	
	}
}

/*----------------------------------------------------------------------------*/

BOOL CSortedListCtrl::SetFullRowSel(BOOL bFullRowSel)
{
	// no painting during change
	LockWindowUpdate();

	m_bFullRowSel=bFullRowSel;

	BOOL bRet;

	if(m_bFullRowSel)
		bRet=ModifyStyle(0L,LVS_OWNERDRAWFIXED);
	else
		bRet=ModifyStyle(LVS_OWNERDRAWFIXED,0L);

	// repaint window if we are not changing view type
	if(bRet && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		Invalidate();

	// repaint changes
	UnlockWindowUpdate();

	return(bRet);
}

/*----------------------------------------------------------------------------*/

BOOL CSortedListCtrl::GetFullRowSel()
{
	return(m_bFullRowSel);
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags=ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem=lpDrawItemStruct->itemID;
	BOOL bFocus=(GetFocus()==this);
	COLORREF clrTextSave, clrBkSave;
	COLORREF clrImage=m_clrBkgnd;
	static _TCHAR szBuff[MAX_PATH];

	// Same as label offsets in CHeaderCtrl 
	int OFFSET_FIRST = pDC->GetTextExtent(_T(" "), 1 ).cx*2;
	int OFFSET_OTHER = OFFSET_FIRST;

	// get item data

	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem=nItem;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.stateMask=0xFFFF;		// get all state flags
	GetItem(&lvi);

	BOOL bSelected=(bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected=bSelected || (lvi.state & LVIS_DROPHILITED);

	// set colors if item is selected

	CRect rcAllLabels;
	GetItemRect(nItem,rcAllLabels,LVIR_BOUNDS);
	CRect rcLabel;
	GetItemRect(nItem,rcLabel,LVIR_LABEL);
	rcAllLabels.left=rcLabel.left;
	if(m_bClientWidthSel && rcAllLabels.right<m_cxClient)
		rcAllLabels.right=m_cxClient;

	if(bSelected)
	{
		clrTextSave=pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave=pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcAllLabels,&CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
		pDC->FillRect(rcAllLabels,&CBrush(m_clrTextBk));

	// set color and mask for the icon

	if(lvi.state & LVIS_CUT)
	{
		clrImage=m_clrBkgnd;
		uiFlags|=ILD_BLEND50;
	}
	else if(bSelected)
	{
		clrImage=::GetSysColor(COLOR_HIGHLIGHT);
		uiFlags|=ILD_BLEND50;
	}

	// draw state icon

	UINT nStateImageMask=lvi.state & LVIS_STATEIMAGEMASK;
	if(nStateImageMask)
	{
		int nImage=(nStateImageMask>>12)-1;
		pImageList=GetImageList(LVSIL_STATE);
		if(pImageList)
			pImageList->Draw(pDC,nImage,CPoint(rcItem.left,rcItem.top),ILD_TRANSPARENT);
	}

	// draw normal and overlay icon

	CRect rcIcon;
	GetItemRect(nItem,rcIcon,LVIR_ICON);

	pImageList=GetImageList(LVSIL_SMALL);
	if(pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if(rcItem.left<rcItem.right-1)
			ImageList_DrawEx(pImageList->m_hImageList,lvi.iImage,pDC->m_hDC,rcIcon.left,rcIcon.top,16,16,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
	}

	// draw item label

	GetItemRect(nItem,rcItem,LVIR_LABEL);
	rcItem.right-=m_cxStateImageOffset;

	rcLabel=rcItem;
	rcLabel.left+=OFFSET_FIRST;
	rcLabel.right-=OFFSET_FIRST;

	pDC->DrawText(szBuff,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);

	// draw labels for extra columns

	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH;

	for(int nColumn=1; GetColumn(nColumn,&lvc); nColumn++)
	{
		rcItem.left=rcItem.right;
		rcItem.right+=lvc.cx;

		int nRetLen=GetItemText(nItem,nColumn,szBuff,sizeof(szBuff));
		if(nRetLen==0) continue;

		UINT nJustify=DT_LEFT;

		switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
		{
		case LVCFMT_RIGHT:
			nJustify=DT_RIGHT;
			break;
		case LVCFMT_CENTER:
			nJustify=DT_CENTER;
			break;
		default:
			break;
		}

		rcLabel=rcItem;
		rcLabel.left+=OFFSET_OTHER;
		rcLabel.right-=OFFSET_OTHER;

		pDC->DrawText(szBuff,-1,rcLabel,nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);

	}

	// draw focus rectangle if item has focus

	if(lvi.state & LVIS_FOCUSED && bFocus)
		pDC->DrawFocusRect(rcAllLabels);

	// set original colors if item was selected

	if(bSelected)
	{
	        pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}
}

/*----------------------------------------------------------------------------*/

LRESULT CSortedListCtrl::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
	if((int)wParam==LVSIL_STATE)
	{
		int cx, cy;

		if(::ImageList_GetIconSize((HIMAGELIST)lParam,&cx,&cy))
			m_cxStateImageOffset=cx;
		else
			m_cxStateImageOffset=0;
	}

	return(Default());
}

/*----------------------------------------------------------------------------*/

LRESULT CSortedListCtrl::OnSetTextColor(WPARAM wParam, LPARAM lParam)
{
	m_clrText=(COLORREF)lParam;
	return(Default());
}

/*----------------------------------------------------------------------------*/

LRESULT CSortedListCtrl::OnSetTextBkColor(WPARAM wParam, LPARAM lParam)
{
	m_clrTextBk=(COLORREF)lParam;
	return(Default());
}

/*----------------------------------------------------------------------------*/

LRESULT CSortedListCtrl::OnSetBkColor(WPARAM wParam, LPARAM lParam)
{
	m_clrBkgnd=(COLORREF)lParam;
	return(Default());
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	m_cxClient=cx;
	CListCtrl::OnSize(nType, cx, cy);
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::OnPaint() 
{
	// in full row select mode, we need to extend the clipping region
	// so we can paint a selection all the way to the right
	if(m_bClientWidthSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT && GetFullRowSel())
	{
		CRect rcAllLabels;
		GetItemRect(0,rcAllLabels,LVIR_BOUNDS);

		if(rcAllLabels.right<m_cxClient)
		{
			// need to call BeginPaint (in CPaintDC c-tor)
			// to get correct clipping rect
			CPaintDC dc(this);

			CRect rcClip;
			dc.GetClipBox(rcClip);

			rcClip.left=min(rcAllLabels.right-1,rcClip.left);
			rcClip.right=m_cxClient;

			InvalidateRect(rcClip,FALSE);
			// EndPaint will be called in CPaintDC d-tor
		}
	}

	CListCtrl::OnPaint();
	DrawSeparatorLines();

}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CListCtrl::OnSetFocus(pOldWnd);

	// check if we are getting focus from label edit box
	if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
		return;

	// repaint items that should change appearance
	if(m_bFullRowSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);

	// check if we are losing focus to label edit box
	if(pNewWnd!=NULL && pNewWnd->GetParent()==this)
		return;

	// repaint items that should change appearance
	if(m_bFullRowSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::RepaintSelectedItems()
{
	CRect rcItem, rcLabel;

// invalidate focused item so it can repaint properly

	int nItem=GetNextItem(-1,LVNI_FOCUSED);

	if(nItem!=-1)
	{
		GetItemRect(nItem,rcItem,LVIR_BOUNDS);
		GetItemRect(nItem,rcLabel,LVIR_LABEL);
		rcItem.left=rcLabel.left;

		InvalidateRect(rcItem,FALSE);
	}

// if selected items should not be preserved, invalidate them

	if(!(GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem=GetNextItem(-1,LVNI_SELECTED);
			nItem!=-1; nItem=GetNextItem(nItem,LVNI_SELECTED))
		{
			GetItemRect(nItem,rcItem,LVIR_BOUNDS);
			GetItemRect(nItem,rcLabel,LVIR_LABEL);
			rcItem.left=rcLabel.left;

			InvalidateRect(rcItem,FALSE);
		}
	}

// update changes 

	UpdateWindow();
}

/*----------------------------------------------------------------------------*/

void CSortedListCtrl::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if (m_bDeleteItemData) {
		delete (CItemInfo*)pNMListView->lParam;
    }

	*pResult = 0;
}

/*----------------------------------------------------------------------------*/

