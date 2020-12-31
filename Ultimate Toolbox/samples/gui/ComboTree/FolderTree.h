// FolderTree.h: interface for the CFolderTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERTREE_H__35306226_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_)
#define AFX_FOLDERTREE_H__35306226_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\INCLUDE\OXShellFolderTree.h"
#include "OXComboPickerCtrl.h"
   
 
class CFolderTree : public COXTreeComboDropDown<COXShellFolderTree>  
{
public:
	CFolderTree();
	virtual BOOL CanSelectItem(HTREEITEM hItem);
	virtual ~CFolderTree();
	virtual CString GetSelectedItemText();
 
};

#endif // !defined(AFX_FOLDERTREE_H__35306226_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_)
