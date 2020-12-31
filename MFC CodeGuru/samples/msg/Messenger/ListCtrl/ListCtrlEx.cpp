
#include "stdafx.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW


/////////////////////////////////////////////////////////////////////////////
// CListItem

const CListItem& CListItem::operator =(const CListItem& posSrc)
{
	if(&posSrc != this)
	{
		m_pList = posSrc.m_pList;
		Copy((const PLV_ITEM)&(posSrc.m_ListItem));
	}
	return *this;
}

void CListItem::Copy(PLV_ITEM pListItem)
{
	m_ListItem = *pListItem;
	Text(pListItem->pszText);
}


LPCSTR CListItem::Text(LPCSTR text)
{
	m_szText = text;
	m_ListItem.pszText = (LPSTR)(LPCSTR)m_szText;
	m_ListItem.cchTextMax = m_szText.GetLength();

	return Text();
}


/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx() : CListCtrl()
{ 
}

CListCtrlEx::~CListCtrlEx()
{ 
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

CListItem CListCtrlEx::GetItem(int nItem,int nSubItem)
{
	LV_ITEM lvi;
	static TCHAR pszText[2048];

	ZeroMemory(&lvi,sizeof(lvi));
	 // Initialize LV_ITEM members that are common to all items. 
    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE; 
    lvi.pszText = pszText;   // app. maintains text 
	lvi.cchTextMax = sizeof(pszText);
	lvi.stateMask = 0xFFFF;		// get all state flags
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;

	if(CListCtrl::GetItem(&lvi) == 0)
		ZeroMemory(&lvi,sizeof(lvi));
	return CListItem(&lvi,this);
}


BOOL CListCtrlEx::AddColumn(LPCTSTR strItem,int nItem,int nSubItem,int nMask,int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPTSTR) strItem;
	lvc.cx = GetStringWidth(lvc.pszText) + 15;
	if(nMask & LVCF_SUBITEM)
	{
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem,&lvc);
}

BOOL CListCtrlEx::AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex)
{
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;
	if(nImageIndex != -1)
	{
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage |= LVIF_IMAGE;
	}
	if(nSubItem == 0)
		return InsertItem(&lvItem);
	return SetItem(&lvItem);
}

// SelItemRange - Selects/Deselect a range of items
// Returns              - The number of new items selected
// bSelect              - TRUE to select, FALSE to deselect
// nFirstItem           - index of first item to select
// nLastItem            - index of last item to select
int CListCtrlEx::SelItemRange(BOOL bSelect, int nFirstItem, int nLastItem)
{
        // make sure nFirstItem and nLastItem are valid
        if( nFirstItem >= GetItemCount() || nLastItem >= GetItemCount() )
                return 0;

        int nItemsSelected = 0;
        int nFlags = bSelect ? 0 : LVNI_SELECTED;
        int nItem = nFirstItem - 1;
        while( (nItem = GetNextItem( nItem, nFlags )) >=0
                        && nItem <= nLastItem )
        {
                nItemsSelected++;
                SetItemState(nItem, bSelect ? LVIS_SELECTED : 0, LVIS_SELECTED );
        }
        return nItemsSelected;
}

/////////////////////////////////////////////////////////////////////////////
//	set extended styles
void CListCtrlEx::SetExtendedStyles(DWORD dwExStyle)
{
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));
}
