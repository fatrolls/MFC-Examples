
#ifndef IXTREEITEM_H
#define IXTREEITEM_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "EXMenu.h"
#include <list>

class IXTreeItem
{

public:	

	//
	// For item that are leafs...
	//

	virtual CString		GetLabel()												{return "<Please override GetLabel() in TreeItem>"; }
	virtual short		GetImage()												{ return 0; }
	virtual short		GetSelectedImage()										{ return GetImage(); }

	//
	// And additionally, if item has children
	//

	virtual bool		IsExpandable()											{return false;}
	virtual int			GetNumChildren()										{return 0;}
	virtual bool		GetChildElements(std::list<IXTreeItem*> &lITreeItems)	{return false;}

	//
	//
	//

	virtual void		GetPopupMenu(EXMenu &menu)								{}
//	virtual bool		MoveDown(IXTreeItem *pTreeItem)							{return false;}
//	virtual bool		MoveUp(IXTreeItem *pTreeItem)							{return false;}
	virtual void		SetLabel(CString sLabel)								{}
	virtual bool		CanEditLabel()											{return false;}
	virtual void		GetParentList(std::list<IXTreeItem*> &lParents)			{}
	virtual bool		MoveItem(IXTreeItem *pFromItem, IXTreeItem *pToItem)	{return false;}

};

#endif
