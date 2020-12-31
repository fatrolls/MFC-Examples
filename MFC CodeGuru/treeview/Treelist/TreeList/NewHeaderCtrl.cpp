// NewHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TreeList.h"
#include "NewHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewHeaderCtrl

CNewHeaderCtrl::CNewHeaderCtrl()
{
	m_pImageList = NULL;
}

CNewHeaderCtrl::~CNewHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CNewHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CNewHeaderCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewHeaderCtrl message handlers

void CNewHeaderCtrl::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CDC dc;

	dc.Attach( lpDrawItemStruct->hDC );

	// Get the column rect
	CRect rcLabel( lpDrawItemStruct->rcItem );

	// Save DC
	int nSavedDC = dc.SaveDC();

	// Set clipping region to limit drawing within column
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcLabel );
	dc.SelectObject( &rgn );
	rgn.DeleteObject();

	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = dc.GetTextExtent(_T(" "), 1 ).cx*2;


	// Draw image from image list

	// Get the column text and format
	TCHAR buf[256];
	HD_ITEM hditem;
	
	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;

	GetItem( lpDrawItemStruct->itemID, &hditem );

	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
						| DT_VCENTER | DT_END_ELLIPSIS ;

	if( hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if( hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;

	if(!(uFormat & DT_RIGHT))
	{
		// Adjust the rect if the mouse button is pressed on it
		if( lpDrawItemStruct->itemState == ODS_SELECTED )
		{
			rcLabel.left++;
			rcLabel.top += 2;
			rcLabel.right++;
		}

		rcLabel.left += offset;
		rcLabel.right -= offset;

		// Draw column label
		if( rcLabel.left < rcLabel.right )
			dc.DrawText(buf,-1,rcLabel, uFormat);
	}


	int imageIndex;
	if (m_pImageList && 
		m_mapImageIndex.Lookup( lpDrawItemStruct->itemID, imageIndex ) )
	{
		if( imageIndex != -1 )
		{
			if(uFormat & DT_RIGHT)
			// draw to the left of the label
				m_pImageList->Draw(&dc, imageIndex, 
						CPoint( rcLabel.left + offset,offset/3 ),
						ILD_TRANSPARENT );
			else
			// draw to the right
				m_pImageList->Draw(&dc, imageIndex, 
						CPoint( rcLabel.right - dc.GetTextExtent(_T(buf), 1 ).cx*2,offset/3 ),
						ILD_TRANSPARENT );


			// Now adjust the label rectangle
			IMAGEINFO imageinfo;
			if( m_pImageList->GetImageInfo( imageIndex, &imageinfo ) )
			{
				rcLabel.left += offset/2 + 
					imageinfo.rcImage.right - imageinfo.rcImage.left;
			}
		}
	}

	if(uFormat & DT_RIGHT)
	{
		// Adjust the rect if the mouse button is pressed on it
		if( lpDrawItemStruct->itemState == ODS_SELECTED )
		{
			rcLabel.left++;
			rcLabel.top += 2;
			rcLabel.right++;
		}

		rcLabel.left += offset;
		rcLabel.right -= offset;

		// Draw column label
		if( rcLabel.left < rcLabel.right )
			dc.DrawText(buf,-1,rcLabel, uFormat);
	}

	// Restore dc
	dc.RestoreDC( nSavedDC );

	// Detach the dc before returning
	dc.Detach();
}

CImageList* CNewHeaderCtrl::SetImageList( CImageList* pImageList )
{
	CImageList *pPrevList = m_pImageList;
	m_pImageList = pImageList;
	return pPrevList;
}

int CNewHeaderCtrl::GetItemImage( int nItem )
{
	int imageIndex;
	if( m_mapImageIndex.Lookup( nItem, imageIndex ) )
		return imageIndex;
	return -1;
}

void CNewHeaderCtrl::SetItemImage( int nItem, int nImage )
{
	// Save the image index
	m_mapImageIndex[nItem] = nImage;

	// Change the item to ownder drawn
	HD_ITEM hditem;

	hditem.mask = HDI_FORMAT;
	GetItem( nItem, &hditem );
	hditem.fmt |= HDF_OWNERDRAW;
	SetItem( nItem, &hditem );

	// Invalidate header control so that it gets redrawn
	Invalidate();
}
