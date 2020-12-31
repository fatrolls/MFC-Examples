//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPODRAW.CPP
//
// Implementation of owner-draw objects.

#include "wpp.h"

WPOwnerDrawItem::WPOwnerDrawItem(WPWin *win, UINT t)
{ 
	next = NULL; 
	type = t; 
	assert(win);
	win->addODItem(this);
}

WPOwnerDrawItem* WPODItemList::getItem(LPODITEMSTRUCT &item)
{
	WPOwnerDrawItem* od;
	for (od=first; od; od=od->next) {
		if (od->getType() == item->type && od->getID() == item->id)
			break;
	}
	return od;
}

BOOL WPODItemList::dispatchEvent(WPEvent& event)
{
	if (first==NULL)
		return FALSE;

	LPODITEMSTRUCT odi = (LPODITEMSTRUCT)event.lp;
	WPOwnerDrawItem *item;

	switch (event.msg) {
	case WM_DRAWITEM:
		item = getItem(odi);
		if (item) {
			LPDRAWITEMSTRUCT draw = (LPDRAWITEMSTRUCT)odi;
			WPOwnerDrawDC dc = draw;
			item->paint(dc, (ODDATA)draw->itemData);
			return TRUE;
		}
		break;

	case WM_MEASUREITEM:
		item = getItem(odi);
		if (item) {
			WPPoint dim = 
				item->measure((ODDATA)((LPMEASUREITEMSTRUCT)odi)->itemData);
			((LPMEASUREITEMSTRUCT)odi)->itemWidth  = dim.x;
			((LPMEASUREITEMSTRUCT)odi)->itemHeight = dim.y;
			return TRUE;
		}
		break;

	case WM_DELETEITEM:
		item = getItem(odi);
		if (item==NULL) {
			item->delItem((ODDATA)((LPDELETEITEMSTRUCT)odi)->itemData);
			return TRUE;
		}
		break;

	case WM_COMPAREITEM:
		item = getItem(odi);
		if (item==NULL) {
			event.ret = 
				item->compare((ODDATA)((LPCOMPAREITEMSTRUCT)odi)->itemData1,
					(ODDATA)((LPCOMPAREITEMSTRUCT)odi)->itemData1);
			return TRUE;
		}
		break;

	case WM_VKEYTOITEM:
	case WM_CHARTOITEM:
		// Not supported yet
		break;
	}
	return FALSE;
}

