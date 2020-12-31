// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx
CHeaderCtrlEx::CHeaderCtrlEx()
	: marker_rect(0,0,0,0)
{
	m_pWidth = NULL;
	m_bDragging = FALSE;
	m_bCheckForDrag = FALSE;
	m_fpDragCol = NULL;
	m_pOwnerWnd = NULL;
	m_bDragEnable = false;
}

CHeaderCtrlEx::CHeaderCtrlEx(CWnd *pWnd, void (CWnd::*fpDragCol)(int, int))
	: marker_rect(0,0,0,0)
{
	m_pWidth = NULL;
	m_bDragging = FALSE;
	m_bCheckForDrag = FALSE;
	m_fpDragCol = fpDragCol;
	m_pOwnerWnd = pWnd;
	m_bDragEnable = false;
}

CHeaderCtrlEx::~CHeaderCtrlEx()
{
}

BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlEx)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//	Public Properties
//
//	EnableDrag(bool bDrag=true):	Enable or disable column header dragging
//
/////////////////////////////////////////////////////////////////////////////

bool CHeaderCtrlEx::EnableDrag(bool bDrag)
{
	bool bOld = m_bDragEnable;
	m_bDragEnable = bDrag;

	return bOld;
}

//End Properties
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx message handlers

void CHeaderCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bDragEnable) {
		if( (MK_LBUTTON & nFlags) == 0)	{
			// The left mouse button is not pressed - so reset flags
			m_bCheckForDrag = FALSE;
			m_bDragging = FALSE;
		}
		else if( m_bDragging ) {
			// Get column number that falls under the mouse
			int i=0, cx = 0;
			if( point.x > 0 )
				for( i = 0; i < GetItemCount(); i++ ) {
					if( point.x >= cx && point.x < cx + m_pWidth[i] )
						break;
					cx += m_pWidth[i];
				}
			if( i != m_nDropPos ) {
				m_nDropPos = i;
				CRect rect;
				GetWindowRect( &rect );
				// Invalidate area occupied by previous marker
				InvalidateRect( &marker_rect );

				// Draw a new marker
				CClientDC dc(this);
				POINT pts[3];
				pts[0].x = cx;
				pts[1].x = cx - rect.Height()/4;
				pts[2].x = cx + rect.Height()/4;
				pts[0].y = rect.Height();
				pts[1].y = pts[2].y = rect.Height()/2;
				dc.Polygon( pts, 3 );

				// save marker information
				marker_rect.left = cx - (rect.Height()/4 + 1);
				marker_rect.top = rect.Height() - (rect.Height()/2 + 1);
				marker_rect.right = cx + (rect.Height()/4 + 1);	
				marker_rect.bottom = rect.Height() + 1;
			}
			return;
		}
		else if( m_bCheckForDrag ) {
			// The mouse button was pressed over a column header
			// and now the mouse has moved - so start drag
			m_bCheckForDrag = FALSE;
			m_bDragging = TRUE;
			m_nDropPos = m_nDragCol;
			SetCapture();

			// Store information for later use
			int iCount = GetItemCount();
			HD_ITEM hd_item;
			m_pWidth = new int[iCount];
			for( int i = 0; i < iCount; i++ ) {
				hd_item.mask = HDI_WIDTH;
				GetItem( i, &hd_item );
				m_pWidth[i] = hd_item.cxy;
			}
			return;
		}
	}
	
	CHeaderCtrl::OnMouseMove(nFlags, point);
}

void CHeaderCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bDragEnable) {
		// Determine if mouse was pressed over a column header
		HD_HITTESTINFO hd_hittestinfo;
		hd_hittestinfo.pt = point;
		SendMessage(HDM_HITTEST, 0, (LPARAM)(&hd_hittestinfo));
		if( hd_hittestinfo.flags == HHT_ONHEADER )	{
			m_nDragCol = hd_hittestinfo.iItem;
			m_bCheckForDrag = TRUE;
		}
	}

	CHeaderCtrl::OnLButtonDown(nFlags, point);
}

void CHeaderCtrlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bDragEnable) {
		ASSERT( m_pOwnerWnd != NULL && m_fpDragCol != NULL );
		if( m_bDragging ) {
			m_bDragging = FALSE;
			delete[] m_pWidth;
			ReleaseCapture();
			Invalidate();
				// Call the callback function.
			if( m_nDragCol != m_nDropPos && m_nDragCol != m_nDropPos -1 )
				(m_pOwnerWnd->*m_fpDragCol)( m_nDragCol, m_nDropPos );
		}
	}

	CHeaderCtrl::OnLButtonUp(nFlags, point);
}

void CHeaderCtrlEx::SetCallback( CWnd* pWnd, void (CWnd::*fpDragCol)(int, int) )
{
	m_fpDragCol = fpDragCol;
	m_pOwnerWnd = pWnd;
}

//End CHeaderCtrlEx
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

//Constructor for the list data structure
CListCtrlEx::ListData::ListData(const DWORD dwOld, const CString &strTxt, const COleDateTime Start)
{
	dwOldData = dwOld;
	strText = strTxt;
	BaseTime = Start;
}

CListCtrlEx::CListCtrlEx()
{
	nSortedCol		= -1; 
	bSortAscending	= TRUE;
	m_nNumCols		= 0;
	m_pTypes		= NULL;
	m_ctStart.SetStatus(COleDateTime::invalid);
	m_bSort			= false;
	m_nHighlight	= HIGHLIGHT_NORMAL;

	m_headerctrl.SetCallback( this, (void (CWnd::*)(int, int))DragColumn );
}

CListCtrlEx::~CListCtrlEx()
{
	delete m_pTypes;
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(HDN_ITEMCLICKA, 0, OnHeaderClicked) 
	ON_NOTIFY(HDN_ITEMCLICKW, 0, OnHeaderClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//Public Properties
//
//	SetHighlightType(int hilite):		Set highlight type
//	EnableSort(bool bSort=true):		Enable sorting by column
//	SetColumnTypes(unsigned char* pColTypes, unsigned nColCnt):
//										Set the column sort types									
//	EnableHeaderDrag(bool bDrag=true}:	Enable column header dragging
//	SetBaseTime(CString strTime):		Set the base time for 24hr clock
//
/////////////////////////////////////////////////////////////////////////////

int CListCtrlEx::SetHighlightType(int hilite)
{
	int oldhilite = m_nHighlight;
	if( hilite <= HIGHLIGHT_ROW )
	{
		m_nHighlight = hilite;
		//set to ownerdraw for full row highlighting
		if(hilite > HIGHLIGHT_NORMAL)
			ModifyStyle(0, LVS_OWNERDRAWFIXED);
		Invalidate();
	}	
	
	return oldhilite;
}

bool CListCtrlEx::EnableSort(bool bSort)
{
	bool bOldSort = m_bSort;
	m_bSort = bSort;

	return bOldSort;
}

bool CListCtrlEx::SetColumnTypes(unsigned char* pColTypes, unsigned nColCnt)
{
	delete m_pTypes;
	m_pTypes = new unsigned char[nColCnt];
	if(m_pTypes == NULL) {
		m_nNumCols = 0;
		return false;
	}

	for(unsigned i=0; i<nColCnt; i++) {
		if(pColTypes[i] > LVEX_LAST) {
			m_nNumCols = 0;
			delete m_pTypes;
			return false;
		}
		m_pTypes[i] = pColTypes[i];
	}

	m_nNumCols = nColCnt;

	return true;
}

bool CListCtrlEx::EnableHeaderDrag(bool bDrag)
{
	return m_headerctrl.EnableDrag(bDrag);
}

bool CListCtrlEx::SetBaseTime(CString strTime)
{
	COleDateTime ctNew;
	//there can only be one base time for all columns
	//this function should only be called once
	ASSERT(m_ctStart.GetStatus() == COleDateTime::invalid);

	ctNew.ParseDateTime(strTime);
	if(ctNew.GetStatus() != COleDateTime::invalid) {
		m_ctStart = ctNew;
		return true;
	}

	return false;
}

//End Properties
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Highlighting
//
/////////////////////////////////////////////////////////////////////////////

void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);	
	int nItem = lpDrawItemStruct->itemID;
	CImageList* pImageList;	// Save dc state	
	int nSavedDC = pDC->SaveDC();
	CBrush WndBrush(::GetSysColor(COLOR_WINDOW));
	CBrush HltBrush(::GetSysColor(COLOR_HIGHLIGHT));

	// Get item image and state info	
	LV_ITEM lvi;
	lvi.mask = LVIF_IMAGE | LVIF_STATE;	
	lvi.iItem = nItem;	
	lvi.iSubItem = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags	
	GetItem(&lvi);

	// Should the item be highlighted
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)
				|| ( (lvi.state & LVIS_SELECTED)			
				&& ((GetFocus() == this)
				|| (GetStyle() & LVS_SHOWSELALWAYS))));

	// Get rectangles for drawing	
	CRect rcBounds, rcLabel, rcIcon;
	GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
	GetItemRect(nItem, rcLabel, LVIR_LABEL);	
	GetItemRect(nItem, rcIcon, LVIR_ICON);
	CRect rcCol( rcBounds ); 
	CString sLabel = GetItemText( nItem, 0 );

	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = pDC->GetTextExtent(_T(" "), 1 ).cx*2;	
	CRect rcHighlight;
	CRect rcWnd;	
	int nExt;	
	switch(m_nHighlight)	{	
	case HIGHLIGHT_NORMAL: 
		nExt = pDC->GetOutputTextExtent(sLabel).cx + offset;		
		rcHighlight = rcLabel;
		if( rcLabel.left + nExt < rcLabel.right )
			rcHighlight.right = rcLabel.left + nExt;		
		break;	
	case HIGHLIGHT_ALLCOLUMNS:
		rcHighlight = rcBounds;		
		rcHighlight.left = rcLabel.left;		
		break;	
	case HIGHLIGHT_ROW:
		GetClientRect(&rcWnd);		
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;		
		rcHighlight.right = rcWnd.right;		
		break;
	default:	
		rcHighlight = rcLabel;	
	}	
	
	// Draw the background color
	if( bHighlight )	{		
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rcHighlight, &HltBrush);	
	}	
	else
		pDC->FillRect(rcHighlight, &WndBrush);	

	// Set clip region	
	rcCol.right = rcCol.left + GetColumnWidth(0);	
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rcCol);	
	pDC->SelectClipRgn(&rgn);
	rgn.DeleteObject();	
	
	// Draw state icon	
	if (lvi.state & LVIS_STATEIMAGEMASK)	{
		int nImage = ((lvi.state & LVIS_STATEIMAGEMASK)>>12) - 1;
		pImageList = GetImageList(LVSIL_STATE);		
		if (pImageList) {
			pImageList->Draw(pDC, nImage,
				CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);		
		}	
	}	

	// Draw normal and overlay icon	
	pImageList = GetImageList(LVSIL_SMALL);
	if (pImageList)	{		
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		pImageList->Draw(pDC, lvi.iImage, 			
			CPoint(rcIcon.left, rcIcon.top),
			(bHighlight?ILD_BLEND50:0) | ILD_TRANSPARENT | nOvlImageMask );	
	}		
	// Draw item label - Column 0	
	rcLabel.left += offset/2;
	rcLabel.right -= offset;
	pDC->DrawText(sLabel,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
				| DT_VCENTER | DT_END_ELLIPSIS);	
	
	// Draw labels for remaining columns
	LV_COLUMN lvc;	
	lvc.mask = LVCF_FMT | LVCF_WIDTH;
	if(m_nHighlight == HIGHLIGHT_NORMAL)	// Highlight only first column	
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));	
	}	
	rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
							rcBounds.right;	rgn.CreateRectRgnIndirect(&rcBounds);
	pDC->SelectClipRgn(&rgn);				   
	for(int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)	{
		rcCol.left = rcCol.right;		
		rcCol.right += lvc.cx;

		// Draw the background if needed		
		if( m_nHighlight == HIGHLIGHT_NORMAL )
			pDC->FillRect(rcCol, &HltBrush);
		sLabel = GetItemText(nItem, nColumn);		
		if (sLabel.GetLength() == 0)
			continue;		
		
		// Get the text justification		
		UINT nJustify = DT_LEFT;
		switch(lvc.fmt & LVCFMT_JUSTIFYMASK)		
		{		
		case LVCFMT_RIGHT:
			nJustify = DT_RIGHT;			
			break;		
		case LVCFMT_CENTER:			
			nJustify = DT_CENTER;
			break;		
		default:			
			break;		
		}		
		rcLabel = rcCol;		
		rcLabel.left += offset;
		rcLabel.right -= offset;
		pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE | 
					DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);	
	}

	// Draw focus rectangle if item has focus
	if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
		pDC->DrawFocusRect(rcHighlight);		
	
	// Restore dc	
	pDC->RestoreDC( nSavedDC );
	WndBrush.DeleteObject();
	HltBrush.DeleteObject();
}

void CListCtrlEx::OnPaint() 
{	
	// in full row select mode, we need to extend the clipping region
	// so we can paint a selection all the way to the right
	if (m_nHighlight == HIGHLIGHT_ROW &&
		(GetStyle() & LVS_TYPEMASK) == LVS_REPORT )	{
		CRect rcBounds;
		GetItemRect(0, rcBounds, LVIR_BOUNDS);
		CRect rcClient;
		GetClientRect(&rcClient);
		if(rcBounds.right < rcClient.right)		{
			CPaintDC dc(this);
			CRect rcClip;
			dc.GetClipBox(rcClip);
			rcClip.left = min(rcBounds.right-1, rcClip.left);
			rcClip.right = rcClient.right;
			InvalidateRect(rcClip, FALSE);
		}
	}
	
	CListCtrl::OnPaint();
}

void CListCtrlEx::OnSetFocus(CWnd* pOldWnd) 
{
	CListCtrl::OnSetFocus(pOldWnd);
	
	// check if we are getting focus from label edit box
	if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
		return;
	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();
}

void CListCtrlEx::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	
	// check if we are losing focus to label edit box
	if(pNewWnd != NULL && pNewWnd->GetParent() == this)
		return;
	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
		RepaintSelectedItems();
}

void CListCtrlEx::RepaintSelectedItems()
{
	CRect rcBounds, rcLabel;

	// Invalidate focused item so it can repaint 
	int nItem = GetNextItem(-1, LVNI_FOCUSED);

	if(nItem != -1)
	{
		GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
		GetItemRect(nItem, rcLabel, LVIR_LABEL);
		rcBounds.left = rcLabel.left;

		InvalidateRect(rcBounds, FALSE);
	}

	// Invalidate selected items depending on LVS_SHOWSELALWAYS
	if(!(GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem = GetNextItem(-1, LVNI_SELECTED);
			nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
		{
			GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
			GetItemRect(nItem, rcLabel, LVIR_LABEL);
			rcBounds.left = rcLabel.left;

			InvalidateRect(rcBounds, FALSE);
		}
	}

	UpdateWindow();
}

//places check marks in state icon boxes when clicked
void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags = 0;
	int nHitItem = HitTest(point, &uFlags);

	BOOL bHit = FALSE;
	if (uFlags & LVHT_ONITEMSTATEICON)
		bHit = TRUE;

	if (bHit) {
		UINT nState = GetItemState(nHitItem, LVIS_STATEIMAGEMASK);
		if(nState == INDEXTOSTATEIMAGEMASK(1))
			SetItemState(nHitItem, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
		else
			SetItemState(nHitItem, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
	}
	
	CListCtrl::OnLButtonDown(nFlags, point);
}

//End Hilighting
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//Sorting by columns
//
//////////////////////////////////////////////////////////////////////

void CListCtrlEx::OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

	if(phdn->iButton == 0 && m_bSort)// Button is the left mouse button 
	{
		// User clicked on header using left mouse button
		if(phdn->iItem == nSortedCol)
			bSortAscending = !bSortAscending;
		else
			bSortAscending = TRUE;

		nSortedCol = phdn->iItem;
		int NumItems = GetItemCount();	

		// replace Item data with pointer to ListData structure
		for (int i = 0; i < NumItems; i++)	{
			DWORD dwData = GetItemData(i); // save current data to restore it later
			CString strText = GetItemText(i, nSortedCol);
			
			SetItemData(i, (DWORD)new ListData(dwData, strText, m_ctStart));	
		}

		SortItems(Compare, bSortAscending | (m_pTypes[nSortedCol] << 8));

		for(i=0; i<NumItems; i++) {
			ListData* pData = (ListData*)GetItemData(i);
			SetItemData(i, pData->dwOldData);
			delete pData;

		}
	}
	*pResult = 0;
}

int CALLBACK CListCtrlEx::Compare(LPARAM lParam1, LPARAM lParam2, LPARAM 
								 lParSortAsc)
{
	CString str1 = ((ListData*)lParam1)->strText;
	CString str2 = ((ListData*)lParam2)->strText;

	unsigned char Type = unsigned char(lParSortAsc >> 8);

	// restore data type and sort order from lParamSort
	// if lParamSort positive - ascending sort order, negative - descending
	int  sOrder = (lParSortAsc & 0xFF) ? 1 : -1; 
	COleDateTime t1, t2, bTime = ((ListData*)lParam1)->BaseTime;	
	
	switch (Type)	{
	//Date time column(s) with 24 hr base time	
	case  LVEX_TIME_BASE://most people will never use this		
		if (t1.ParseDateTime(str1) && t2.ParseDateTime(str2))
		{
			if(bTime.GetStatus() != COleDateTime::invalid && 
				t1 < bTime)
			{
				t1 += COleDateTimeSpan(1, 0, 0, 0);
			}
			if(bTime.GetStatus() != COleDateTime::invalid &&
				t2 < bTime)
			{
				t2 += COleDateTimeSpan(1, 0, 0, 0);
			}
		
			return (t1 < t2 ? -1 : 1 )*sOrder;
		}
		else			
			return 0;
	//Date time column(s) no base time
	case  LVEX_TIME:
		if (t1.ParseDateTime(str1) && t2.ParseDateTime(str2))
			return (t1 < t2 ? -1 : 1 )*sOrder;		
		else			
			return 0;
	//integer number columns
	case  LVEX_NUM:		
		return (atol(str1) - atol(str2))*sOrder;
	//float number columns
	case  LVEX_NUM_FLOAT:
		return (atof(str1) < atof(str2) ? -1 : 1)*sOrder;
	//text columns (no case)
	case  LVEX_NOCASE:		
		return str1.CompareNoCase(str2)*sOrder;
	//text columns (case sensitive)
	case LVEX_CASE:
		return (str1.Compare(str2))*sOrder;	
	}

	return 0;
}

//End Sorting
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//Drag Column Headers
//
//////////////////////////////////////////////////////////////////////

void CListCtrlEx::DragColumn(int source, int dest)
{	
	TCHAR sColText[160];

	// Insert a column at dest
	LV_COLUMN lv_col;
	lv_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv_col.pszText = sColText;
	lv_col.cchTextMax = 159;
	GetColumn( source, &lv_col );
	lv_col.iSubItem = dest;
	InsertColumn( dest, &lv_col );

	// Adjust source col number since it might have changed 
	// because a new column was inserted
	if( source > dest )
		source++;

	// Moving a col to position 0 is a special case	
	if( dest == 0 )
		for( int i = GetItemCount()-1; i > -1 ; i-- )
			SetItemText(i, 1, GetItemText( i, 0) );	
		
	// Copy sub item from source to dest
	for( int i = GetItemCount()-1; i > -1 ; i-- )
		SetItemText(i, dest, GetItemText( i, source ) );

	// Delete the source column, but not if it is the first	
	if( source != 0 )
		DeleteColumn( source );
	else {
		// If source col is 0, then copy col# 1 to col#0
		// and then delete col# 1
		GetColumn( 1, &lv_col );
		lv_col.iSubItem = 0;
		SetColumn( 0, &lv_col );
		for( int i = GetItemCount()-1; i > -1 ; i-- )
			SetItemText(i, 0, GetItemText( i, 1) );
		DeleteColumn( 1 );
	}
	
	Invalidate();
}

void CListCtrlEx::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();
	
	// Add initialization code
	m_headerctrl.SubclassWindow( ::GetDlgItem(m_hWnd,0) );
}

//End Drag Headers
//////////////////////////////////////////////////////////////////////////

