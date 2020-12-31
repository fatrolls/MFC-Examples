//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPMENU.CPP
//
// Implementation of menu object.
// These functions are all pretty brainless.

#include "wpp.h"

BOOL WPMenu::setBitmaps(int id, WPBitmap* bm0, WPBitmap* bm1, WORD how)
{ 
	return SetMenuItemBitmaps(hmenu, id, how, (*bm0)(), (*bm1)()); 
}

BOOL WPMenu::append(int id, WPBitmap& bm, WORD flags)
{ 
	return AppendMenu(hmenu, MF_BITMAP|flags, id,
		(LPSTR)MAKELONG(bm(),0)); 
}

HMENU WPMenu::appendPopup(LPCSTR text)
{
	HMENU hPopup = CreateMenu();
	if (AppendMenu(hmenu, MF_POPUP, (UINT)hPopup, (LPSTR)text) )
		return hPopup;
	DestroyMenu(hPopup);
	return NULL;
}

BOOL WPMenu::insert(int pos, int id, WPBitmap& bm, WORD flags)
{ 
	return InsertMenu(hmenu, pos, MF_BITMAP|flags, id, 
		(LPSTR)MAKELONG(bm(), 0));
}

HMENU WPMenu::insertPopup(int pos, LPCSTR text, WORD flags)
{
	HMENU hPopup = CreateMenu();
	if (InsertMenu(hmenu, pos, MF_POPUP|flags, (UINT)hPopup, (LPSTR)text) )
		return hPopup;
	DestroyMenu(hPopup);
	return NULL;
}

BOOL  WPMenu::modify(int pos, int id, WPBitmap& bm, WORD flags)
{ 
	return ModifyMenu(hmenu, pos, MF_BITMAP|flags, id, 
		(LPSTR)MAKELONG(bm(), 0));
}
