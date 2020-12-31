#include "stdafx.h"
#include "TreeCtrlEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW




/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlNode


const CTreeCursor& CTreeCursor::operator =(const CTreeCursor& posSrc)
{
	if(&posSrc != this)
	{
		m_hTreeItem = posSrc.m_hTreeItem;
		m_pTree = posSrc.m_pTree;
	}
	return *this;
}

CTreeCursor CTreeCursor::_Insert(LPCTSTR strItem,int nImageIndex,int nImageSelectedIndex,HTREEITEM hAfter)
{
	TV_INSERTSTRUCT ins;

	memset(&ins,0,sizeof(ins));
	ins.hParent = m_hTreeItem;
	ins.hInsertAfter = hAfter;
	ins.item.mask = TVIF_TEXT;
	ins.item.pszText = (LPTSTR) strItem;
	if(nImageIndex != -1)
	{
		ins.item.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		ins.item.iImage = nImageIndex;
		if(nImageSelectedIndex != -1)
			ins.item.iSelectedImage = nImageSelectedIndex;
		else
			ins.item.iSelectedImage = nImageIndex;
	}
	return CTreeCursor(m_pTree->InsertItem(&ins), m_pTree);
}

int CTreeCursor::GetImageID()
{
	TV_ITEM item;
	item.mask = TVIF_HANDLE | TVIF_IMAGE;
	item.hItem = m_hTreeItem;
	m_pTree->GetItem(&item);
	return item.iImage;
}

CTreeCursor CTreeCursor::Find(CTreeCursor cursor,DWORD dwData)
{
	while(cursor != NULL)
	{
		if(cursor.GetData() == dwData)
			return cursor;

		if(cursor.GetChild() != NULL)
		{
			CTreeCursor res = Find(cursor.GetChild(),dwData);
			if(res != NULL)
				return res;
		}

		cursor = cursor.GetNext(TVGN_NEXT);
	}

	CTreeCursor empty;
    return empty;
}

CTreeCursor CTreeCursor::Find(DWORD dwData) 
{	
	CTreeCursor cursor = GetRoot();
	while(cursor != NULL)
	{
		if(cursor.GetData() == dwData)
			return cursor;

		if(cursor.GetChild() != NULL)
		{
			CTreeCursor res = Find(cursor.GetChild(),dwData);
			if(res != NULL)
				return res;
		}

		cursor = cursor.GetNext(TVGN_NEXT);
	}

	CTreeCursor empty;
    return empty;
}

CTreeCursor CTreeCursor::Find(CTreeCursor cursor,LPCSTR pData)
{
	while(cursor != NULL)
	{
		if(strcmp(cursor.GetText(),pData) == 0)
			return cursor;

		if(cursor.GetChild() != NULL)
		{
			CTreeCursor res = Find(cursor.GetChild(),pData);
			if(res != NULL)
				return res;
		}

		cursor = cursor.GetNext(TVGN_NEXT);
	}

	CTreeCursor empty;
    return empty;
}

CTreeCursor CTreeCursor::Find(LPCSTR pData)
{	
	CTreeCursor cursor = GetRoot();
	while(cursor != NULL)
	{
		if(strcmp(cursor.GetText(),pData) == 0)
			return cursor;

		if(cursor.GetChild() != NULL)
		{
			CTreeCursor res = Find(cursor.GetChild(),pData);
			if(res != NULL)
				return res;
		}

		cursor = cursor.GetNext(TVGN_NEXT);
	}

	CTreeCursor empty;
    return empty;
}

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)
/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx message handlers



