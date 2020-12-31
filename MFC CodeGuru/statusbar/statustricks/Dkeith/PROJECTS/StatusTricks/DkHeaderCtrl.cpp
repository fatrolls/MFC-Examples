// DkHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "StatusTricks.h"
#include "DkHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDkHeaderCtrl

CDkHeaderCtrl::CDkHeaderCtrl()
{
	// indicate user isn't moving any columns around
	m_nDragItem = -1;
	m_bIsTracking = FALSE;
}

CDkHeaderCtrl::~CDkHeaderCtrl()
{
}

BEGIN_MESSAGE_MAP(CDkHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CDkHeaderCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(HDN_BEGINTRACK, OnBeginTrack)
	ON_NOTIFY_REFLECT(HDN_ENDTRACK, OnEndTrack)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDkHeaderCtrl message handlers

void CDkHeaderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
		int			 i;			// general index
		BOOL		 done;		// indicates when search is complete
		CRect		 itemRect;	// rect binding the current item
		HD_ITEM		 hItem;		// information about the current item

	// default processing
	CHeaderCtrl::OnLButtonDown(nFlags, point);

	// if user isn't tracking the header control
	if (!m_bIsTracking)
	{
		// default the item rect to empty (but with the correct height)
		GetClientRect(itemRect);
		itemRect.right = 0;

		// in our requests, we'll want to get the width
		hItem.mask = HDI_WIDTH;

		// for each item in the header control
		for (i = 0, done = FALSE; i < GetItemCount(); i++)
		{
			// pick up the information about this item
			GetItem(i, &hItem);

			// expand the item rect to encompass this item
			itemRect.right += hItem.cxy;

			// if user is in this header region
			if (itemRect.PtInRect(point))
			{
				// indicate we're dragging this header item
				m_nDragItem = i;

				// remember the rect binding this header item
				m_rDragItem = itemRect;

				// remember where the drag started
				m_ptLastDrag = point;

				// discontinue the search for the clicked item
				done = TRUE;

				// set the cursor to the drag cursor
				SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGCURSOR));
				TRACE1("Preparing to drag item #%d\n", i);
			}

			// prepare for the next item
			itemRect.left += hItem.cxy + 1;
		}
	}
}

void CDkHeaderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// default processing
	CHeaderCtrl::OnLButtonUp(nFlags, point);

	// if user was dragging a header
	if (m_nDragItem >= 0)
	{
		// indicate the drag operation is over
		m_nDragItem = -1;

		TRACE1("Dropped item #%d\n", m_nDragItem);
	}
}

void CDkHeaderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// default processing
	CHeaderCtrl::OnMouseMove(nFlags, point);

	// if user is dragging a header
	if (m_nDragItem >= 0)
	{
		TRACE1("Dragging item #%d\n", m_nDragItem);
	}
}

void CDkHeaderCtrl::OnBeginTrack(NMHDR *pNotify, LRESULT *result)
{
	// indicate user is tracking a header
	m_bIsTracking = TRUE;
}

void CDkHeaderCtrl::OnEndTrack(NMHDR *pNotify, LRESULT *result)
{
	// indicate user is finished tracking
	m_bIsTracking = FALSE;
}
