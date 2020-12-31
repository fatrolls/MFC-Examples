// MyTreeListCtrl.cpp: implementation of the CMyTreeListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TurboDemo.h"
#include "MyTreeListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyTreeListCtrl::CMyTreeListCtrl()
{

}

CMyTreeListCtrl::~CMyTreeListCtrl()
{

}

BEGIN_MESSAGE_MAP(CMyTreeListCtrl, CTreeListCtrl)
	//{{AFX_MSG_MAP(CTreeListDemoDlg)
	ON_NOTIFY_REFLECT( TLN_ITEMEXPANDING,  OnExpanding )
	ON_NOTIFY_REFLECT( TLN_ITEMEXPANDED,  OnExpanded )
	ON_NOTIFY_REFLECT( TLN_ITEMUPDATING, OnUpdating )
	ON_NOTIFY_REFLECT( TLN_ITEMUPDATED, OnUpdated )
	ON_NOTIFY_REFLECT( TLN_BEGINDRAG, OnBeginDrag )
	ON_NOTIFY_REFLECT( TLN_DRAGENTER, OnDragEnter )
	ON_NOTIFY_REFLECT( TLN_DRAGLEAVE, OnDragLeave )
	ON_NOTIFY_REFLECT( TLN_DRAGOVER, OnDragOver )
	ON_NOTIFY_REFLECT( TLN_DROP, OnDrop )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyTreeListCtrl::OnExpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELIST lpnmtl = ( LPNMTREELIST )pNMHDR;
	
	CTreeListItem* pItem = 	lpnmtl->pItem;
	int iCol = lpnmtl->iCol;
	
	CString str = GetItemText( pItem, iCol );
	CString str2 = _T("@@@@@ Expending - ");
	CString str3 = str2 + str;

//	AfxMessageBox( str3 );
	
	*pResult = 0;
}

void CMyTreeListCtrl::OnExpanded(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELIST lpnmtl = ( LPNMTREELIST )pNMHDR;
	
	CTreeListItem* pItem = 	lpnmtl->pItem;
	int iCol = lpnmtl->iCol;
	
	CString str = GetItemText( pItem, iCol );
	CString str2 = _T("@@@@@ ********* - ");
	CString str3 = str2 + str;

//	AfxMessageBox( str3 );

	*pResult = 0;
}

void CMyTreeListCtrl::OnUpdating(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELIST lpnmtl = ( LPNMTREELIST )pNMHDR;
	
	CTreeListItem* pItem = 	lpnmtl->pItem;
	int iCol = lpnmtl->iCol;
	
	CString str = GetItemText( pItem, iCol );
	CString str2 = _T("@@@@@ UpdateColumn - ");
	CString str3 = str2 + str;

	AfxMessageBox( str3 );

	if( str.Compare(_T("0") ) == 0 )
		*pResult = -1;
	else
		*pResult = 0;
}

void CMyTreeListCtrl::OnUpdated(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELIST lpnmtl = ( LPNMTREELIST )pNMHDR;
	
	CTreeListItem* pItem = 	lpnmtl->pItem;
	int iCol = lpnmtl->iCol;
	
	CString str = GetItemText( pItem, 0 );
	CString str2 = _T("@@@@@ UpdateItem - ");
	CString str3 = str2 + str;

	AfxMessageBox( str3 );
	
	if( str.Compare(_T("1") ) == 0 )
		*pResult = -1;
	else
		*pResult = 0;
}

void CMyTreeListCtrl::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELISTDROP lpnm = ( LPNMTREELISTDROP )pNMHDR;

	POSITION pos = GetFirstSelectedItemPosition();
	int i=0;
	while( pos != NULL )
	{
		GetNextSelectedItem( pos );
		i++;
	}

	if( i == 3 )
		*pResult = -1;
}

void CMyTreeListCtrl::OnDragEnter(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELISTDROP lpnm = ( LPNMTREELISTDROP )pNMHDR;

}

void CMyTreeListCtrl::OnDragLeave(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELISTDROP lpnm = ( LPNMTREELISTDROP )pNMHDR;
	SetTargetItem();
}

void CMyTreeListCtrl::OnDragOver(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREELISTDROP lpnm = ( LPNMTREELISTDROP )pNMHDR;

	if( lpnm->pItem->m_nLevel == 2 )
	{
		*pResult = -1;
	}
	else
	{
		*pResult = 0;
	}
}

void CMyTreeListCtrl::OnDrop(NMHDR* pNMHDR, LRESULT* pResult)
{
	AfxMessageBox("Drop OK");
}
