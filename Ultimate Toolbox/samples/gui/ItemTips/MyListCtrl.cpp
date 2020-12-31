// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ItemTips.h"
#include "MyListCtrl.h"
#include "DerivedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_bFirstTimeHooking=TRUE;
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DOYOUNEEDITEMTIP,OnNeedItemTip)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers


LRESULT CMyListCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	// hook window as soon as it subclussed standard CListCtrl
	if(m_bFirstTimeHooking && m_ItemTip.GetHookedWnd()!=this)
	{
		m_bFirstTimeHooking=FALSE;
		m_ItemTip.Attach(this);
	}

	return CListCtrl::DefWindowProc(message, wParam, lParam);
}

LRESULT CMyListCtrl::OnNeedItemTip(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	LPNEEDITEMTIPINFO pnitInfo=(LPNEEDITEMTIPINFO)lParam;

	// parent of this window is corresponding property page
	CDerivedDlg* pParentWnd=(CDerivedDlg*)GetParent();

	// if item tip is for an item in the first column and that item is selected 
	// then draw it using system colors for hilited items
	if(pnitInfo->col==0)
	{
		if(GetItemState(pnitInfo->row,LVIS_SELECTED)==LVIS_SELECTED)
		{
			pnitInfo->clrText=::GetSysColor(COLOR_HIGHLIGHTTEXT);
			pnitInfo->clrBackground=::GetSysColor(COLOR_HIGHLIGHT);
		}
	}

	if(pParentWnd->m_bCustomize && pnitInfo->result==ID_NIT_SUCCESS)
	{
		if(!pParentWnd->m_bSmart)
		{
			// change text color, background color
			pnitInfo->clrText=pParentWnd->m_clrText;
			pnitInfo->clrBackground=pParentWnd->m_clrBackground;
		}
		else
		{
			// depending on image associated with the item set text and background colors
			LV_ITEM lvitem;
			lvitem.mask=LVIF_IMAGE;
			lvitem.iItem=pnitInfo->row;
			lvitem.iSubItem=0;
			if(GetItem(&lvitem))
			{
				switch(lvitem.iImage)
				{
				case 0:
					{
						pnitInfo->clrText=COLOR_BLUE;
						pnitInfo->clrBackground=COLOR_YELLOW;
						break;
					}
				case 1:
					{
						pnitInfo->clrText=COLOR_YELLOW;
						pnitInfo->clrBackground=COLOR_RED;
						break;
					}
				case 2:
					{
						pnitInfo->clrText=COLOR_RED;
						pnitInfo->clrBackground=COLOR_BLUE;
						break;
					}
				case 3:
					{
						pnitInfo->clrText=COLOR_RED;
						pnitInfo->clrBackground=COLOR_YELLOW;
						break;
					}
				}
			}
		}
		// change font
		if((HFONT)pParentWnd->m_font)
		{
			pnitInfo->pFont=(LPARAM)(&pParentWnd->m_font);
		}
	}
	return 0;
}

