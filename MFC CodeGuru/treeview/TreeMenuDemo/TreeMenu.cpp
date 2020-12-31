// TreeMenu.cpp : implementation file
//

#include "stdafx.h"
#include "TreeMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeMenu

CTreeMenu::CTreeMenu()
{
	m_clr3DFace			= ::GetSysColor(COLOR_3DFACE);
	m_clr3DShadow		= ::GetSysColor(COLOR_3DSHADOW);
	m_clr3DDkShadow		= ::GetSysColor(COLOR_3DDKSHADOW);
	m_clr3DLight		= ::GetSysColor(COLOR_3DLIGHT);
	m_clr3DHilight		= ::GetSysColor(COLOR_3DHILIGHT);
	m_clrSelTextColor	= ::GetSysColor(COLOR_BTNTEXT);
	m_clrSelBkColor		= m_clr3DHilight;
}

CTreeMenu::~CTreeMenu()
{
}


BEGIN_MESSAGE_MAP(CTreeMenu, CCoolTreeCtrl)
	//{{AFX_MSG_MAP(CTreeMenu)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeMenu message handlers
int CTreeMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CCoolTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}



/*
//==================== CUSTOM DRAW ==========================================


// custom draw return flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDRF_DODEFAULT          0x00000000
#define CDRF_NEWFONT            0x00000002
#define CDRF_SKIPDEFAULT        0x00000004


#define CDRF_NOTIFYPOSTPAINT    0x00000010
#define CDRF_NOTIFYITEMDRAW     0x00000020
#if (_WIN32_IE >= 0x0400)
#define CDRF_NOTIFYSUBITEMDRAW  0x00000020  // flags are the same, we can distinguish by context
#endif
#define CDRF_NOTIFYPOSTERASE    0x00000040


// drawstage flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDDS_PREPAINT           0x00000001
#define CDDS_POSTPAINT          0x00000002
#define CDDS_PREERASE           0x00000003
#define CDDS_POSTERASE          0x00000004
// the 0x000010000 bit means it's individual item specific
#define CDDS_ITEM               0x00010000
#define CDDS_ITEMPREPAINT       (CDDS_ITEM | CDDS_PREPAINT)
#define CDDS_ITEMPOSTPAINT      (CDDS_ITEM | CDDS_POSTPAINT)
#define CDDS_ITEMPREERASE       (CDDS_ITEM | CDDS_PREERASE)
#define CDDS_ITEMPOSTERASE      (CDDS_ITEM | CDDS_POSTERASE)
#if (_WIN32_IE >= 0x0400)
#define CDDS_SUBITEM            0x00020000
#endif


// itemState flags
#define CDIS_SELECTED    0x0001
#define CDIS_GRAYED      0x0002
#define CDIS_DISABLED    0x0004
#define CDIS_CHECKED     0x0008
#define CDIS_FOCUS       0x0010
#define CDIS_DEFAULT     0x0020
#define CDIS_HOT         0x0040
#define CDIS_MARKED      0x0080

typedef struct tagNMCUSTOMDRAWINFO
{
    NMHDR hdr;
    DWORD dwDrawStage;
    HDC hdc;
    RECT rc;
    DWORD dwItemSpec;  // this is control specific, but it's how to specify an item.  valid only with CDDS_ITEM bit set
    UINT  uItemState;
    LPARAM lItemlParam;
} NMCUSTOMDRAW, FAR * LPNMCUSTOMDRAW;
*/



void CTreeMenu::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{

	NMTVCUSTOMDRAW *pTVCD = (NMTVCUSTOMDRAW*)pNMHDR;
	
	CDC* pDC = CDC::FromHandle(pTVCD->nmcd.hdc);

	// The rect for the cell gives correct left and right values.
	CRect rect = pTVCD->nmcd.rc;
	
	// By default set the return value to do the default behavior.
	*pResult = 0;

	
	switch( pTVCD->nmcd.dwDrawStage )
		{
		// First stage (for the whole control)
		case  CDDS_PREPAINT: 
			{		
				*pResult = CDRF_NOTIFYITEMDRAW;
			}
			break;

		// Stage three (called for each subitem of the focused item)
		case CDDS_ITEMPREPAINT | CDDS_SUBITEM: 
			{
				*pResult = CDRF_NOTIFYSUBITEMDRAW | CDRF_NOTIFYPOSTPAINT;
			}
			break;

		// Stage four (called for each subitem of the focused item)
		case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM: 
			{
				*pResult = CDRF_SKIPDEFAULT;	
			}
			break;
		
		default: 
			// Stage two handled here. (called for each item)
			if (pTVCD->nmcd.uItemState & CDIS_HOT)
			{
				pDC->Draw3dRect( &rect, m_clr3DHilight, m_clr3DShadow );
				pDC->SetBkColor(GetBkColor());
				pDC->SetTextColor(RGB(0,0,255));
	
				// Tell the control that to draw it again.
				*pResult = CDRF_NOTIFYPOSTPAINT;

			}

			if (pTVCD->nmcd.uItemState & CDIS_SELECTED)
			{
				*pResult = CDRF_SKIPDEFAULT;
			}

			if( (pTVCD->nmcd.uItemState & CDIS_FOCUS) )
			{
				pDC->Draw3dRect( &rect, m_clr3DShadow, m_clr3DHilight );
				pDC->SetBkColor(m_clrSelBkColor);
				pDC->SetTextColor(m_clrSelTextColor);
	
				*pResult = CDRF_NOTIFYPOSTPAINT;
			}	
			
			if( (pTVCD->nmcd.uItemState & CDIS_CHECKED) )
			{
				*pResult = CDRF_DODEFAULT;
			}	
			
			break;
		}
}


void CTreeMenu::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	

	HTREEITEM htiOld = pNMTreeView->itemOld.hItem;
	HTREEITEM htiNew = pNMTreeView->itemNew.hItem;

	if ((htiOld == htiNew) || GetItemState(htiNew, TVIS_EXPANDED) & TVIS_EXPANDED)
		return;

	HTREEITEM htiRoot, htiChild = NULL;
	htiRoot = GetNextItem(htiRoot, TVGN_ROOT);
	while (htiRoot != NULL)
	{
		if (ItemHasChildren(htiRoot) && (ItemHasChildren(htiNew)))
			Expand(htiRoot, TVE_COLLAPSE);
			
		htiRoot = GetNextItem(htiRoot, TVGN_NEXT);
		
	}
	
	if (ItemHasChildren(htiNew))
		Expand(htiNew, TVE_EXPAND );

	*pResult = 0;
}


void CTreeMenu::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT flags;
	HTREEITEM tiSelected = HitTest(point, &flags);

	
	if( (flags & TVHT_ONITEMRIGHT)  || (flags & TVHT_ONITEMINDENT) ||
		(flags & TVHT_ONITEM)		|| (flags & TVHT_ONITEMBUTTON) ) 
	{
		;
	}

	CCoolTreeCtrl::OnLButtonDown(nFlags, point);
}


void CTreeMenu::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	TV_DISPINFO *ptvDispInfo = (TV_DISPINFO *)pNMHDR;
	TV_ITEM	*ptvItem = &ptvDispInfo->item;

	SetItem(ptvItem);

	*pResult = 0;
}