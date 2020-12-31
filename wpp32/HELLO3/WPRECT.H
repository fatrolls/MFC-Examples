//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPRECT.H
//
// Declarations for WPRect class.

#ifndef WPRECT_H
#define WPRECT_H

#include "wppoint.h"

//////
// Better Windows RECT
// 
class WPRect : public RECT {
public:
	WPRect() { }
	WPRect(POINT o, POINT e)					 { set(o, e); }
	WPRect(int ll, int tt, int rr, int bb)	 { set(ll,tt,rr,bb); }
	WPRect(RECT& rect)							 { *this = rect; }

	void set(POINT o, POINT e)					{ origin(o); endpt(e); }
	void set(int l, int t, int r, int b)	{ origin(l,t); endpt(r,b); }

	int width()				{ return right-left; }
	int height()			{ return bottom-top; }
	int width(int w)		{ right = left+w;  return width(); }
	int height(int h)		{ bottom= top +h;  return height(); }

	void origin(int x, int y)		{ left=x; top=y; }
	void endpt(int x, int y)		{ right=x; bottom=y; }
	void extent(int w, int h)		{ width(w); height(h); }

	WPPoint origin()				{ return WPPoint(left,top); }
	WPPoint endpt()				{ return WPPoint(right,bottom); }
	WPPoint origin(POINT p)		{ origin(p.x, p.y); return origin(); }
	WPPoint endpt(POINT p)		{ endpt (p.x, p.y); return endpt(); }

	void setEmpty()				{ set(0,0,0,0); }
	BOOL isEmpty()					{ return IsRectEmpty(this); }
	BOOL contains(POINT p)		{ return PtInRect(this, p); }
	void inflate(int w, int h)	{ InflateRect(this, w, h); }
	void capture(POINT p)
		{	p.x=min(max(p.x,left),right-1); 
			p.y=min(max(p.y,top), bottom-1); }

	void adjustWinRect(DWORD style, BOOL menu, DWORD exstyle=0)
		{ AdjustWindowRectEx(this, style, menu, exstyle); }

	WPRect& operator= (RECT &rect) { return *this = rect; }

	BOOL operator==(const WPRect& rect2)
		{ return EqualRect(this, &rect2); }

	WPRect& operator+= (POINT p)	
		{ left+=p.x; right+=p.x; top+=p.y; bottom+=p.y; return*this; }
	WPRect& operator-= (POINT p)
		{ left-=p.x; right-=p.x; top-=p.y; bottom-=p.y; return *this; }

	WPRect& operator*= (int m)				
		{ width(width()*m); height(height()*m); return *this; }
	WPRect& operator/= (int m)				
		{ width(width()/m); height(height()/m); return *this; }

	WPRect& operator++ ()		{ inflate(1,1);   return *this; }
	WPRect& operator-- ()		{ inflate(-1,-1); return *this; }

	WPRect& operator*= (const TEXTMETRIC &tm)
		{ origin(origin()*=tm); endpt(endpt()*=tm); return *this; }
};

#endif
