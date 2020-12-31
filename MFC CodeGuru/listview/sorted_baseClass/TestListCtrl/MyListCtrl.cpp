// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TestListCtrl.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl() : CSortedListCtrl(TRUE, TRUE)
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CSortedListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
		ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

/*----------------------------------------------------------------------------*/

void CMyListCtrl::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	if (pDispInfo->item.mask & LVIF_TEXT) {

		CMyItemInfo* pAppItem = reinterpret_cast<CMyItemInfo*>(pDispInfo->item.lParam);

		switch (pDispInfo->item.iSubItem) {

		case 0 :
			lstrcpy (pDispInfo->item.pszText, pAppItem->GetName());
			break;
		case 1 :
			lstrcpy (pDispInfo->item.pszText, pAppItem->GetNumberAsString());
			break;
		}
	}
	*pResult = 0;
}

/*----------------------------------------------------------------------------*/

int CMyListCtrl::CompareItems(CItemInfo *pItemInfo1, CItemInfo *pItemInfo2)
{
	CMyItemInfo *pInfo1 = static_cast<CMyItemInfo*>(pItemInfo1);
	CMyItemInfo *pInfo2 = static_cast<CMyItemInfo*>(pItemInfo2);
	int nResult;

	switch (GetSortedColumn()) 
	{
	case 0 : // Sort on column 'Name'
		nResult = pInfo1->GetName().CompareNoCase(pInfo2->GetName());
		break;
	case 1 : // Sort on column 'Number'
	{
		int Number1 = pInfo1->GetNumber();
		int Number2 = pInfo2->GetNumber();

		if (Number1 < Number2)
		{
			nResult = -1;
		}
		else 
		{
			nResult = (Number1 != Number2);
		}
		break;
	}
	default :
		nResult = 0;
		break;
	}
	return IsAscSorted() ? nResult : -nResult;
}
