// ButtonsTextList.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonsTextList.h"
#include "afxadv.h"
#include "BCGToolbarButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonsTextList

CButtonsTextList::CButtonsTextList()
{
}

CButtonsTextList::~CButtonsTextList()
{
}


BEGIN_MESSAGE_MAP(CButtonsTextList, CListBox)
	//{{AFX_MSG_MAP(CButtonsTextList)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonsTextList message handlers

void CButtonsTextList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonDown(nFlags, point);

	int iIndex = GetCurSel ();
	if (iIndex == LB_ERR)
	{
		return;
	}

	//-------------------------------------------
	// Be sure that we realy click into the item!
	//-------------------------------------------
	CRect rect;
	GetItemRect (iIndex, &rect);

	if (!rect.PtInRect (point))
	{
		return;
	}

	//-----------------------------------------------------------
	// Trigger mouse up event (to change selection notification):
	//-----------------------------------------------------------
	SendMessage (WM_LBUTTONUP, nFlags, MAKELPARAM (point.x, point.y));

	//---------------------
	// Get selected button:
	//---------------------
	CBCGToolbarButton* pButton = (CBCGToolbarButton*) GetItemData (iIndex);
	ASSERT_VALID(pButton);

	//--------------------------------------
	// Prepare clipboard data and start drag:
	//--------------------------------------
	COleDataSource srcItem;

	pButton->m_bDragFromCollection = TRUE;
	pButton->PrepareDrag (srcItem);
	pButton->m_bDragFromCollection = FALSE;

	srcItem.DoDragDrop ();
}
