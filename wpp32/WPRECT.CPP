//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPRECT.CPP
//
// Implementation of rectangle object.

#include "wpp.h"

//////////////////
// Make sure that left <= right and top <= bottom.
// 
void WPRect::normalize()
{
	if (left > right) {
		int r = right;
		right = left;
		left = r;
	}
	if (top > bottom) {
		int b = bottom;
		bottom = top;
		top = b;
	}
}

//////////////////
// Assign WPRect to a Window: get the window rectangle.
// If win ptr is NULL, get whole screen dimensions.
// 
WPRect& WPRect::operator=(WPWin *win)
{
	if (win)
		win->getClientRect(*this); 
	else
		set(0, 0, GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN));
	return *this;
}

//////////////////
// Intersect rectangle with another rectangle.
// 
BOOL WPRect::operator&= (const RECT& rect2)
{ 
	RECT dest;
	BOOL nonempty = IntersectRect(&dest, this, &rect2);
	*this = dest;
	return nonempty;
}

//////////////////
// Union rectangle with another rectangle.
// 
BOOL WPRect::operator|= (const RECT& rect2)
{ 
	RECT dest;
	BOOL nonempty = UnionRect(&dest, this, &rect2);
	*this = dest;
	return nonempty;
}

////////////////
// WPWinRect: get window rectangle instead of client area.
// 
WPWindowRect& WPWindowRect::operator=(WPWin *win)
{
	win->getWindowRect(*this); 
	return *this;
}

//////////////////
// Get dimensions of text string, in character units.
// Sets origin=(0,0)
// width	 =	num chars in longest line
// height =	num lines
// 
WPRect& WPRect::operator=(LPCSTR text)
{
	setEmpty();
	if (text && *text) {
		int nlines = 0;
		int maxwid = 0;
		for (;;) {
			nlines++;
			LPSTR end = strchr((LPSTR)text, '\n');
			if (end==NULL)
				break;
			maxwid = max(maxwid, end-text);
			text = end+1;
		} 
		maxwid = max(maxwid, lstrlen(text));
		width(maxwid);
		height(nlines);
	}
	return *this;
}

