//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPPOINT.H
//
// Declarations for WPPoint structure.

#ifndef WPPOINT_H
#define WPPOINT_H

#ifndef WPPDEFS_H
#include "wppdefs.h"
#endif

//////////////////
// Better POINT structure.
// 
struct WPPoint : public POINT {
	WPPoint(int xx=0, int yy=0)	{ set(xx, yy); }
	WPPoint(const POINT& p)			{ set(p); }

	void set(int xx=0, int yy=0)	{ x=xx; y=yy; }
	void set(POINT p)					{ set(p.x, p.y); }
	
	BOOL operator==(POINT p)		{ return x==p.x && y==p.y; }
	BOOL operator!=(POINT p)		{ return x!=p.x || y!=p.y; }

	WPPoint& operator++ ()			{ x++; y++; return *this; }
	WPPoint& operator-- ()			{ x--; y--; return *this; }

	WPPoint operator+ (POINT p)	{ return WPPoint(x+p.x, y+p.y); }
	WPPoint operator- (POINT p)	{ return WPPoint(x-p.x, y-p.y); }

	WPPoint& operator+= (POINT p)	{ x+=p.x; y+=p.y; return *this; }
	WPPoint& operator-= (POINT p)	{ x-=p.x; y-=p.y; return *this; }
	WPPoint& operator*= (int m)	{ x*=m; y*=m; return *this; }
	WPPoint& operator/= (int m)	{ x/=m; y/=m; return *this; }

	WPPoint& operator*= (const TEXTMETRIC &tm)
		{ x*=tm.tmAveCharWidth; y*=tm.tmHeight; return *this; }

	WPPoint& operator= (POINT p)	{ set(p); return *this; }
};

#endif
