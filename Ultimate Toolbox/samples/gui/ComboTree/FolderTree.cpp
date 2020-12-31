// FolderTree.cpp: implementation of the CFolderTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FolderTree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFolderTree::CFolderTree()
{

}

CFolderTree::~CFolderTree()
{
}

BOOL CFolderTree::CanSelectItem(HTREEITEM hItem)
{
	if (hItem)
	{
		CString sFullPath=GetFullPath(hItem);
		return (sFullPath.IsEmpty()==FALSE);
	}
	return FALSE;
}

CString CFolderTree::GetSelectedItemText()
{

	CString sResult;
	HTREEITEM hItem=GetSelectedItem();
	if (hItem)
		sResult=GetFullPath(hItem);
	return sResult;

}


