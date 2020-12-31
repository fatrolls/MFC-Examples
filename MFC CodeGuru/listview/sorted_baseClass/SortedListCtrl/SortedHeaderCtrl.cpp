#include "stdafx.h"
#include "SortedHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*----------------------------------------------------------------------------*/


BEGIN_MESSAGE_MAP(CSortedHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CSortedHeaderCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*----------------------------------------------------------------------------*/

const int CSortedHeaderCtrl::NOT_SORTED = -1;

/*----------------------------------------------------------------------------*/

CSortedHeaderCtrl::CSortedHeaderCtrl()
{
	m_nSortCol = NOT_SORTED;
	m_bSortAsc = TRUE;
}

/*----------------------------------------------------------------------------*/

CSortedHeaderCtrl::~CSortedHeaderCtrl()
{
}

/*----------------------------------------------------------------------------*/

int CSortedHeaderCtrl::SetSortImage(int nCol, BOOL bAsc)
{
	int nPrevCol = m_nSortCol;

	m_nSortCol = nCol;
	m_bSortAsc = bAsc;

	SetOwnerDraw(nCol);

	// Invalidate header control so that it gets redrawn
	Invalidate();

	return nPrevCol;
}

/*----------------------------------------------------------------------------*/

BOOL CSortedHeaderCtrl::IsAscSorted()
{
	return m_bSortAsc;
}

/*----------------------------------------------------------------------------*/

int CSortedHeaderCtrl::GetSortedColumn()
{
	return m_nSortCol;
}

/*----------------------------------------------------------------------------*/

void CSortedHeaderCtrl::SetOwnerDraw(int nCol)
{
	HD_ITEM hditem;
	
	hditem.mask = HDI_FORMAT;
	GetItem(nCol, &hditem);
	hditem.fmt |= HDF_OWNERDRAW;
	SetItem(nCol, &hditem);
}

/*----------------------------------------------------------------------------*/

void CSortedHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// Get the column rect
	CRect rcLabel(lpDrawItemStruct->rcItem);
	
	// Draw the background
    pDC->FillRect(rcLabel, &CBrush(::GetSysColor(COLOR_3DFACE)));	

	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = pDC->GetTextExtent(_T(" "), 1).cx*2;

	// Get the column text and format
	TCHAR buf[256];
	HD_ITEM hditem;	

	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;
	
	GetItem(lpDrawItemStruct->itemID, &hditem);

	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS ;

	if (hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if (hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;

	// Adjust the rect if the mouse button is pressed on it
	if (lpDrawItemStruct->itemState == ODS_SELECTED)
	{
		rcLabel.left++;
		rcLabel.top += 2;
		rcLabel.right++;
	}

	// Adjust the rect further if Sort arrow is to be displayed
	if (lpDrawItemStruct->itemID == static_cast<UINT>(m_nSortCol))
	{
		rcLabel.right -= 3 * offset;
	}
	
	rcLabel.left += offset;
	rcLabel.right -= offset;
	
	// Draw column label
	pDC->DrawText(buf, -1, rcLabel, uFormat);

	// Draw the Sort arrow
	if (lpDrawItemStruct->itemID == static_cast<UINT>(m_nSortCol))
	{
		CRect rcIcon(lpDrawItemStruct->rcItem);

		// Set up pens to use for drawing the triangle
		CPen penLight(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen penShadow(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen *pOldPen = pDC->SelectObject(&penLight);

		if (m_bSortAsc)
		{
			// Draw triangle pointing upwards
			pDC->MoveTo(rcIcon.right - 2*offset, offset - 1);
			pDC->LineTo(rcIcon.right - 3*offset/2, rcIcon.bottom - offset);
			pDC->LineTo(rcIcon.right - 5*offset/2-2, rcIcon.bottom - offset);
			pDC->MoveTo(rcIcon.right - 5*offset/2-1, rcIcon.bottom - offset - 1);

			pDC->SelectObject(&penShadow);
			pDC->LineTo(rcIcon.right - 2*offset, offset-2);
		}
		else	
		{
			// Draw triangle pointing downwards
			pDC->MoveTo(rcIcon.right - 3*offset/2, offset-1);
			pDC->LineTo(rcIcon.right - 2*offset-1, rcIcon.bottom - offset + 1);
			pDC->MoveTo(rcIcon.right - 2*offset-1, rcIcon.bottom - offset);

			pDC->SelectObject(&penShadow);
			pDC->LineTo(rcIcon.right - 5*offset/2-1, offset - 1);
			pDC->LineTo(rcIcon.right - 3*offset/2, offset - 1);
		}
		
		// Restore the pen
		pDC->SelectObject(pOldPen);
	}
}

/*----------------------------------------------------------------------------*/
