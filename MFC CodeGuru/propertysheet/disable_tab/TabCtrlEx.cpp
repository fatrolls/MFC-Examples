/////////////////////////////////////////////////////////////////////////////
// TabCtrlEx.cpp : implementation file
//
// Extended Tab Control
// Copyright (C) 1998 RedCreek Communications
// All rights reserved.
//
// Written by Kevin Lussier (klussier@redcreek.com)
// Version 1.02
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc. to
//    klussier@redcreek.com
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TabCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Define our offsets for drawing
#define TCEX_SELECTED_XOFFSET	7
#define TCEX_SELECTED_YOFFSET	0
#define TCEX_UNSELECTED_XOFFSET	4
#define TCEX_UNSELECTED_YOFFSET	2
#define CXBUTTONMARGIN			2
#define CYBUTTONMARGIN			3

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx

CTabCtrlEx::CTabCtrlEx()
{
}

CTabCtrlEx::~CTabCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlEx)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelchanging)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx message handlers
/////////////////////////////////////////////////////////////////////////////
/*
 * DrawItem
 *
 * Purpose:
 *   This is the function that draws the tab items (bitmaps and text) for
 *   this owner-drawn control
 *
 * Inputs:
 *   LPDRAWITEMSTRUCT lpd: Contains vital drawing information
 *
 * Returns:
 *   Nothing
 *
 * Note:
 *   This function is the heart of the extended tab control. It draws the
 *   items enabled or disabled, with or without images. There are bound to
 *   be flaws here, especially in the drawing code but for simple tabs it
 *   seems to work fairly well.
 */
void CTabCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpd)
{
	// Make sure it's a tab control
	if ( lpd->CtlType != ODT_TAB ) {
		TRACE0( "CTabCtrlEx::DrawItem() - Ignoring non-tab control\r\n" );
		return;
	}

	// Get whether or not this item is enabled
	BOOL bIsEnabled = IsItemEnabled( lpd->itemID );

	// Get this item's text
	TC_ITEM tci;
	memset( &tci, 0, sizeof( TC_ITEM ) );
	tci.mask = TCIF_TEXT | TCIF_IMAGE;
	char buf[255];
	tci.pszText = buf;
	tci.cchTextMax = 255;
	if ( !GetItem( lpd->itemID, &tci ) ) {
		TRACE1( "Failed to get item %d\r\n", lpd->itemID );
		return;
	}

	// Create a CRect
	CRect rect( lpd->rcItem );
	// Draw the background
	FillRect( lpd->hDC, rect, (HBRUSH)(CTLCOLOR_DLG + 1) );
	// Adjust the rectangle
	if ( lpd->itemState & ODS_SELECTED ) {
		// Push it right
		rect.left += TCEX_SELECTED_XOFFSET;
		// Push it down
		rect.top += TCEX_SELECTED_YOFFSET;
	}
	else {
		// Push it right
		rect.left += TCEX_UNSELECTED_XOFFSET;
		// Push it down
		rect.top += TCEX_UNSELECTED_YOFFSET;
	}

	// Set the background mode (paint transparent)
	SetBkMode( lpd->hDC, TRANSPARENT );

	// If this item has an image, draw it
	if ( tci.iImage >= 0 ) {
		// Get the image list
		CImageList *il = GetImageList();
		ASSERT( il != NULL );
		// Figure out where exactly we want to put the bitmap
		CPoint pt( rect.TopLeft() );
		// Adjust the rectangle
		if ( lpd->itemState & ODS_SELECTED ) {
			// Push it down
			pt.y += CYBUTTONMARGIN;
		}
		// Draw it
		CDC hDC;
		hDC.Attach( lpd->hDC );
		if ( bIsEnabled ) {
			il->Draw( &hDC, tci.iImage, pt, ILD_NORMAL );
		}
		else {
			// use DrawState to draw disabled button: must convert to icon
			HICON hIcon = il->ExtractIcon( tci.iImage );
			ASSERT(hIcon);
			hDC.DrawState( pt, CSize(0,0), hIcon, DSS_DISABLED, (HBRUSH)NULL );
			DestroyIcon(hIcon);
		}
		hDC.Detach();
		// Push the text over
		IMAGEINFO ii;
		il->GetImageInfo( tci.iImage, &ii );
		rect.left += (ii.rcImage.right - ii.rcImage.left); // Add the width of the bitmap
		rect.left += CXBUTTONMARGIN; // Plus some separation
	}

	// We will need to remember the current color
	COLORREF origCol;
	// Draw disabled
	if ( bIsEnabled ) {
		// Set the text color for our hilight (remember the original color)
		origCol = SetTextColor( lpd->hDC, GetSysColor( COLOR_BTNTEXT ) );
		// Draw the text
		DrawText( lpd->hDC, buf, -1, rect, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
	}
	// Draw enabled
	else {
		// Set the text color for our hilight (remember the original color)
		origCol = SetTextColor( lpd->hDC, GetSysColor( COLOR_3DHILIGHT ) );
		// Draw the text
		DrawText( lpd->hDC, buf, -1, rect + CPoint(1,1), DT_SINGLELINE | DT_LEFT | DT_VCENTER );
		// Set the text color for our gray text
		SetTextColor( lpd->hDC, GetSysColor( COLOR_GRAYTEXT ) );
		// Draw the text
		DrawText( lpd->hDC, buf, -1, rect, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
	}

	// Restore the original text color
	SetTextColor( lpd->hDC, origCol );
}

LRESULT CTabCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( message == TCM_SETCURSEL ) {
		if ( !IsItemEnabled( wParam ) ) {
			// We only calculate a different selection if the
			// user used CTRL+Tab or CTRL+Shift+Tab. We determine
			// this by checking if the difference between the
			// current and the new selection is 1 (or -1)
			int curSel = GetCurSel(), nCount = GetItemCount();
			int diff = wParam - curSel, adiff = abs( diff );
			if ( adiff == 1 || adiff == (int)wParam || adiff == curSel ) {
				// OK, let's find the next one
				BOOL bNext = ( diff == 1 ) || ( diff < -1 );

				// Find the next enabled item
				int sel = FindNextEnabled( wParam, bNext );
				if ( sel >= 0 ) {
					// Set the current selection to the next enabled
					CTabCtrl::SetCurSel( sel );
					return (LRESULT)0;
				}
			}
			// Return indicating not to select wParam
			return (LRESULT)-1;
		}
	}

	// We could have checked for these keys in a TCN_KEYDOWN handler,
	// but it's just as easy to do it here...

	// Check for and process arrow keys
	if ( message == WM_KEYDOWN ) {
		if ( wParam == VK_RIGHT || wParam == VK_DOWN ) {
			// Get the current selection
			int curSel = GetCurSel();
			// Set the current tab
			SetCurrentTab( curSel < GetItemCount() - 1 ? curSel + 1 : 0 );
			// Return indicating that we processed the message
			return (LRESULT)0;
		}
		if ( wParam == VK_LEFT || wParam == VK_UP ) {
			// Get the current selection
			int curSel = GetCurSel();
			// Set the current tab
			SetCurrentTab( curSel > 0 ? curSel - 1 : GetItemCount() - 1 );
			// Return indicating that we processed the message
			return (LRESULT)0;
		}
	}

	return CTabCtrl::WindowProc(message, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// Message Map Functions
/////////////////////////////////////////////////////////////////////////////
void CTabCtrlEx::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// Get the position of the last message
	DWORD lastPos = GetMessagePos();
	// Convert it to a point
	CPoint point( LOWORD( lastPos ), HIWORD( lastPos ) );
	// Convert the point to client coordinates
	ScreenToClient( &point );
	// Create a hit test
	TC_HITTESTINFO hti;
	hti.pt = point;
	hti.flags = TCHT_ONITEM;
	// See which (if any) tab was hit
	int nItem = HitTest( &hti );
	if ( nItem == -1 ) {
		// Fail the selection change
		*pResult = 1;
		return;
	}
	// Set the result based on whether or not the item is enabled
	BOOL bResult = IsItemEnabled( nItem );

	// If the page is active, then send the kill message to check
	// whether or not the page wants to change
	if ( bResult ) {
		// Send the kill active page message
		bResult = SendKillActive();
	}

	// Return our result (TRUE to stop, FALSE to proceed)
	*pResult = !bResult;
}


/////////////////////////////////////////////////////////////////////////////
// Protected Functions
/////////////////////////////////////////////////////////////////////////////

/*
 * FindNextEnabled
 *
 * Purpose:
 *   Finds the next enabled tab on the control.
 *
 * Inputs:
 *   int nStart: The index of then item to start the search
 *   BOOL bNext: TRUE to search next, FALSE to search previous
 *
 * Returns:
 *   Index of next enabled item found, -1 if no item was found
 */
int CTabCtrlEx::FindNextEnabled( int nStart, BOOL bNext )
{
	// Get the number of item we have
	int i, nCount = GetItemCount();
	// Check if we should go next or back
	if ( bNext ) {
		// Search all the next items
		for ( i = nStart; i < nCount; i++ ) {
			if ( IsItemEnabled( i ) ) {
				// Found one, return it
				return i;
			}
		}
		// We didn't find it, loop and start from the beginning
		for ( i = 0; i < nStart; i++ ) {
			if ( IsItemEnabled( i ) ) {
				// Found one, return it
				return i;
			}
		}
	}
	else {
		// Search all the previous items
		for ( i = nStart; i >= 0; --i ) {
			if ( IsItemEnabled( i ) ) {
				// Found one, return it
				return i;
			}
		}
		// We didn't find it, loop and start from the end
		for ( i = (nCount - 1); i > nStart; --i ) {
			if ( IsItemEnabled( i ) ) {
				// Found one, return it
				return i;
			}
		}
	}
	// Didn't find one
	return -1;
}

/*
 * SetCurrentTab
 *
 * Purpose:
 *   Sets the current tab selection and sends the TCM_SELCHANGE
 *   notification so that the dialog is properly updated
 *
 * Inputs:
 *   int nItem: The item that is to be the current tab
 *
 * Returns:
 *   Nothing
 */
void CTabCtrlEx::SetCurrentTab( int nItem ) 
{
	// Make sure the item is in our range
	if ( nItem < 0 || nItem >= GetItemCount() ) {
		return;
	}

	// Send the kill active page message
	if ( !SendKillActive() ) {
		// The kill message returned that the page should not
		// be changed, so we don't do it
		return;
	}

	// Set the current selection
	SetCurSel( nItem );

	// SetCurSel does not send the TCN_SELCHANGE notification
	m_nmhdr.hwndFrom = GetSafeHwnd(); 
	m_nmhdr.idFrom = GetDlgCtrlID();
	m_nmhdr.code = TCN_SELCHANGE;  
	// Send the message
	SendMessage( WM_NOTIFY, m_nmhdr.idFrom, (LPARAM)&m_nmhdr );
}

/*
 * SendKillActive
 *
 * Purpose:
 *   Sends a kill active message to a property page of a parent
 *   property sheet
 *
 * Inputs:
 *   int nItem: The index of the page to send the kill message to
 *
 * Returns:
 *   TRUE if the kill message succeeds, FALSE otherwise
 */
BOOL CTabCtrlEx::SendKillActive( int nItem )
{
	// Send a message to our parent to kill the current active window
	CWnd *pParent = GetParent();
	if ( pParent->IsKindOf( RUNTIME_CLASS( CPropertySheet ) ) ) {
		// Check if the user wants to use the active page
		if ( nItem == -1 ) {
			nItem = ((CPropertySheet *)pParent)->GetActiveIndex();
		}
		// Get the property page
		CPropertyPage *page = ((CPropertySheet *)pParent)->GetPage( nItem );
#ifdef _DEBUG
		CString txt;
		page->GetWindowText( txt );
		TRACE2( "Sending kill active message to property page #%d (%s)\r\n", nItem, (LPCSTR)txt );
#endif // _DEBUG
		m_nmhdr.hwndFrom = pParent->GetSafeHwnd();
		m_nmhdr.idFrom = pParent->GetDlgCtrlID();
		m_nmhdr.code = PSN_KILLACTIVE;
		// PSN_KILLACTIVE will return TRUE to prevent the page from losing activation
		// and FALSE to to allow it
		return !page->SendMessage( WM_NOTIFY, m_nmhdr.idFrom, (LPARAM)&m_nmhdr );
	}
	// Return success - Send kill active to non-propertysheet does nothing
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Public Functions
/////////////////////////////////////////////////////////////////////////////
/*
 * Install
 *
 * Purpose:
 *   Installs the extended tab control
 *
 * Inputs:
 *   CTabCtrl *pTabCtrl: The tab control that we will subclass
 *
 * Returns:
 *   TRUE if install succeeds, FALSE otherwise
 *
 * Note:
 *   Install() MUST be called, even if the extended tab control is not
 *   subclassing a property sheet tab control. In that case, create
 *   the tab control using its Create() function, and then call install
 *   with a pointer to the control itself. Install() recognizes when
 *   this occurs and does not attempt to subclass itself. The style
 *   bit and image list are still set as normal. In the case where the
 *   tab control is used in a dialog as part of DDX and Create() is not
 *   called directly, Install() must still be called with a pointer to
 *   the extended tab control. Neither of these two cases has actually
 *   been tested by me at this point, but it sounds right. If you try
 *   this and it doesn't work, let me know...
 */
BOOL CTabCtrlEx::Install( CTabCtrl *pTabCtrl )
{
	ASSERT( pTabCtrl );

	TRACE0( "Installing extended tab control\r\n" );
	// Subclass the window, but only if it's not us
	if ( pTabCtrl != this ) {
		// Subclass the tab control
		if ( !SubclassWindow( pTabCtrl->GetSafeHwnd() ) ) {
			TRACE0( "Failed to subclass tab control\r\n" );
			// Return failure
			return FALSE;
		}
	}
	// Get our current style
	DWORD dStyle = pTabCtrl->GetStyle();
	// Add the owner-drawn bit
	dStyle |= TCS_OWNERDRAWFIXED;
	// Set the style
	SetWindowLong( GetSafeHwnd(), GWL_STYLE, dStyle );

	// Return success
	return TRUE;
}

/*
 * Install
 *
 * Purpose:
 *   Installs the extended tab control
 *
 * Inputs:
 *   CPropertySheet *pPropSheet: The property sheet that contains
 *     the tab control that we will subclass
 *
 * Returns:
 *   TRUE if install succeeds, FALSE otherwise
 */
BOOL CTabCtrlEx::Install( CPropertySheet *pPropSheet )
{
	ASSERT( pPropSheet );

	// Call the install function for the tab control
	return( Install( pPropSheet->GetTabControl() ) );
}

/*
 * EnableItem
 *
 * Purpose:
 *   Enabled or disables an item in the tab control
 *
 * Inputs:
 *   int nItem: The item to enable or disable
 *   BOOL bEnable: TRUE to enable the item, FALSE to disable it
 *
 * Returns:
 *   TRUE if function succeeds, FALSE otherwise
 */
BOOL CTabCtrlEx::EnableItem( int nItem, BOOL bEnable )
{
	// Make sure the item is in our range
	if ( nItem < 0 || nItem >= GetItemCount() ) {
		// Return failure
		return FALSE;
	}

	// See if this item is already in our disabled list
	int idx = -1;
	BOOL bIsEnabled = IsItemEnabled( nItem, &idx );

	// Does the caller want to enable or disable this item?
	// If our state is the same as what the user wants to do,
	// then we're done
	if ( bEnable == bIsEnabled ) {
		// Return success
		return TRUE;
	}

	// We come here if we have to add or remove from our list
	if ( bEnable ) {
		// Mark this item as enabled
		ASSERT( idx >= 0 );
		m_disabled.RemoveAt( idx );
	}
	else {
		// Check if this item is the current item. If it is,
		// then we select a new current item (if we can)
		int curSel = GetCurSel();
		if ( nItem == curSel ) {
			// Find the next enabled item
			int sel = FindNextEnabled( nItem < GetItemCount() - 1 ? nItem + 1 : 0, TRUE );
			// If there isn't one or the next one is the
			// one we're trying to disable, then we can't
			// disable this item
			if ( sel < 0 || sel == nItem) {
				// We didn't find an enabled item, return failure
				return FALSE;
			}
			// Set the current selection
//			SetCurSel( sel );
			SetCurrentTab( sel );
		}
		// Mark this item as disabled
		m_disabled.Add( nItem );
	}

	// Invalidate the item
	RECT rect;
	GetItemRect( nItem, &rect );
	InvalidateRect( &rect );
	
	// Return success
	return TRUE;
}

/*
 * IsItemEnabled
 *
 * Purpose:
 *   Specifies whether an item is enabled or disabled
 *
 * Inputs:
 *   int nItem: The item whose enable state we will get
 *
 * Outputs:
 *   int *disabledIdx: The index of the item in the disabled list
 *
 * Returns:
 *   TRUE if the item is enabled, FALSE if it is not
 */
BOOL CTabCtrlEx::IsItemEnabled( int nItem, int *disabledIdx )
{
	// Make sure the item is in our range
	if ( nItem < 0 || nItem >= GetItemCount() ) {
		// Return failure
		return FALSE;
	}

	// Find the item in our list
	int dCount = m_disabled.GetSize();
	for ( int idx = 0; idx < dCount; idx++ ) {
		if ( m_disabled[idx] == (DWORD)nItem ) {
			// Found it, return failure (indicates disabled)
			if ( disabledIdx != NULL ) {
				// Set the disabled index
				*disabledIdx = idx;
			}
			// Return failure
			return FALSE;
		}
	}
	// Didn't find it, return success (indicates enabled)
	return TRUE;
}

/*
 * SetItemImage
 *
 * Purpose:
 *   Adds an image into the tab control's image list and specifies
 *   the item that will use this image
 *
 * Inputs:
 *   int nItem: The item that will be associated with the image
 *   int nResBmp: The resource ID of the image bitmap
 *   int nResMsk: The resource ID of the image mask (also a bitmap resource)
 *
 * Returns:
 *   The index into the image list if successful, -1 otherwise
 */
int CTabCtrlEx::SetItemImage( int nItem, int nResBmp, int nResMsk )
{
	// Make sure the item is in our range
	if ( nItem < 0 || nItem >= GetItemCount() ) {
		// Return failure
		return -1;
	}

	// Get the image list
	CImageList *il = GetImageList();
	if ( il == NULL ) {
		TRACE0( "No image list defined\r\n" );
		return -1;
	}
	// If the user only specified the bitmap and not the mask,
	// we use the bitmap as the mask
	if ( nResMsk == -1 ) {
		TRACE0( "CTabCtrlEx::SetItemImage - No mask specified so using bitmap as mask\r\n" );
		nResMsk = nResBmp;
	}

	// Load the bitmap resource
	CBitmap bitmap;
	if ( !bitmap.LoadBitmap( nResBmp ) ) {
		TRACE0( "Failed to load bitmap\r\n" );
		// Return failure
		return -1;
	}
	// Load the mask resource
	CBitmap mask;
	if ( !mask.LoadBitmap( nResMsk ) ) {
		TRACE0( "Failed to load mask\r\n" );
		// Delete the bitmap object
		bitmap.DeleteObject();
		// Return failure
		return -1;
	}

	// Add this bitmap to our list
	int result = il->Add( &bitmap, &mask );
	
	// Delete the bitmap object
	bitmap.DeleteObject();
	// Delete the mask object
	mask.DeleteObject();

	// Check to see if the image was added
	if ( result == -1 ) {
		TRACE1( "Failed to add bitmap and mask to image list for item %d\r\n", nItem );
		// Return failure
		return -1;
	}
	// Set the item's image index
	TC_ITEM tci;
	memset( &tci, 0, sizeof( TC_ITEM ) );
	tci.mask = TCIF_IMAGE;
	tci.iImage = result;
	if ( !SetItem( nItem, &tci ) ) {
		TRACE1( "Failed to set image for item %d\r\n", nItem );
		// Return failure
		return -1;
	}
	// Return the image index
	return result;
}

/*
 * SetItemImage
 *
 * Purpose:
 *   Adds an image into the tab control's image list and specifies
 *   the item that will use this image
 *
 * Inputs:
 *   int nItem: The item that will be associated with the image
 *   HICON hIcon: An HICON to use as the image
 *
 * Returns:
 *   The index into the image list if successful, -1 otherwise
 */
int CTabCtrlEx::SetItemImage( int nItem, HICON hIcon )
{
	// Make sure the item is in our range
	if ( nItem < 0 || nItem >= GetItemCount() ) {
		// Return failure
		return -1;
	}

	// Get the image list
	CImageList *il = GetImageList();
	if ( il == NULL ) {
		TRACE0( "No image list defined\r\n" );
		return -1;
	}

	// Add this bitmap to our list
	int result = il->Add( hIcon );
	// Check to see if the image was added
	if ( result == -1 ) {
		TRACE1( "Failed to add icon to image list for item %d\r\n", nItem );
		// Return failure
		return -1;
	}
	// Set the item's image index
	TC_ITEM tci;
	memset( &tci, 0, sizeof( TC_ITEM ) );
	tci.mask = TCIF_IMAGE;
	tci.iImage = result;
	if ( !SetItem( nItem, &tci ) ) {
		TRACE1( "Failed to set image for item %d\r\n", nItem );
		// Return failure
		return -1;
	}
	// Return the image index
	return result;
}

void CTabCtrlEx::OnDestroy() 
{
	CTabCtrl::OnDestroy();
}
