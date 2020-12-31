//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: GPP.CPP
//
// Implementation of Windows++ Graphics system.

#include "wpp.h"
#include "gpp.h"

WPRect	GPShape::ClipRect;
BOOL		GPShape::DoClip=FALSE;
const		MINBOUNDS = 4;

//////////////////
// Set global clipping rectangle
// 
void GPShape::Clip(WPRect *rect)
{ 
	DoClip = rect != NULL;
	if (rect) {
		ClipRect = *rect;
		ClipRect.normalize();
	}
}

//////////////////
// Get shape's bounding rectangle
// 
void GPShape::getBounds(WPRect& r)
{
	r = extent;
	r.normalize();
	if (r.width()<MINBOUNDS || r.height() < MINBOUNDS)
		r += MINBOUNDS/2;
}

//////////////////
// Draw shape: do clip test, set pen, brush, etc., then call drawShape.
// 
void GPShape::draw(WPDevContext &dc)
{
	if (DoClip) {
		WPRect temp;
		getBounds(temp);
		temp &= ClipRect;		// intersect w/clipping rectangle
		if (temp.isEmpty()) 
			return;
	}

	if (edgeColor()==COLOR_NONE) 
		dc.setPen(NULL_PEN);
	else
		dc.setPen(edgeColor());

	if (fillColor()==COLOR_NONE) 
		dc.setBrush(NULL_BRUSH);
	else
		dc.setBrush(fillColor());

	drawShape(dc);
}

//////////////////
// Test whether shape "touches" specified point.
// Algorithm:
//		First, try to eliminate by testing bounds; if can't eliminate, 
//		render shape into little square and see if any pixels are on.
// 
BOOL GPShape::hitTest(WPPoint p, int radius)
{
	WPSquare hit(p, radius);
	WPRect temp;
	getBounds(temp);
	temp &= hit;				// intersect them
	if (temp.isEmpty())		// point lies totally outside bounds:
		return FALSE;			// ..miss

	// Possible hit: explore further
	WPMemDC dc(NULL, hit);	// screen-compatible DC
	dc.whiteOut(hit);			// set all pixels white
	dc.setBrush(fillColor()==COLOR_NONE ? NULL_BRUSH : BLACK_BRUSH);
	drawShape(dc);				// render into square

	// See if any pixel is on.
	for (int x=hit.left; x<hit.right; x++) {
		for (int y=hit.top; y<hit.bottom; y++) {
			if (dc.pixel(x, y)==0) 
				return TRUE;
		}
	}
	return FALSE;
}

//////////////////
// Invalidate shape in window: invalidate its bounding rectangle.
// 
void GPShape::invalidate(WPWin *win, BOOL erase)
{
	WPRect rect;
	getBounds(rect);
	WPWinDC dc = win;
	dc.LP2DP(rect);
	win->invalidate(rect, erase); 
}

//////////////////
// Get list of handles.
// 
int GPShape::getHandles(WPPoint* pts)
{
	pts[0]=extent.origin();
	pts[1]=extent.topRight();
	pts[2]=extent.endpt();
	pts[3]=extent.bottomLeft();
	return 4;
}

int GPLine::getHandles(WPPoint* pts)
{
	pts[0]=extent.origin();
	pts[1]=extent.endpt();
	return 2;
}

//////////////////
// Create "hilite" shape from given shape.
// 
GPHilite::GPHilite(GPShape *shp, int r)
{
	assert(shp);
	hishape = shp;
	nhandles = shp->getHandles(handles);
	radius = r;
	shp->getExtent(extent);
}

//////////////////
// Do hit test for hilite: TRUE if point lies within one of the handles.
// 
BOOL GPHilite::hitTest(WPPoint p, int radius)
{
	for (int i=0; i<nhandles; i++) {
		WPSquare handle(handles[i], radius);
		if (handle.contains(p))
			return TRUE;
	}
	return FALSE;
}

//////////////////
// Draw the hilite shape: draw each handle.
// 
void GPHilite::drawShape(WPDevContext &dc)
{
	int oldrop = dc.rop2(R2_XORPEN);
	dc.setPen(WHITE_PEN);
	dc.setBrush(WHITE_BRUSH);
	for (int i=0; i<nhandles; i++) {
		WPPoint p = handles[i];
		dc.LP2DP(p);
		WPSquare handle(p, radius);
		int old = dc.mapMode(MM_TEXT);
		dc.rectangle(handle);
		dc.mapMode(old);
	}
	dc.rop2(oldrop);
}

//////////////////
// Invalidate hilite: invalidate each size anchor
// 
void GPHilite::invalidate(WPWin *win, BOOL erase)
{
	WPWinDC dc = win;
	for (int i=0; i<nhandles; i++) {
		WPPoint p = handles[i];
		dc.LP2DP(p);
		WPSquare handle(p, radius);
		win->invalidate(handle, erase);
	}
}

//////////////////
// Determine size anchor given pt. Returns the anchor point.
// This is the handle farthest from the given point.
// 
WPPoint GPHilite::anchor(WPPoint p)
{
	long distance=0;
	int anchor = 0;
	WPPoint delta;
	for (int i=0; i<nhandles; i++) {
		delta = handles[i] - p;
		long d = (long)delta.x*(long)delta.x + (long)delta.y*(long)delta.y;
		if (d > distance) {
			distance = d;
			anchor = i;
		}
	}
	return handles[anchor];
}

//////////////////
// Delete all shapes in list.
// 
void GPShapeList::deleteAll()
{
	GPShape *sNext;
	for (GPShape *s = firstShape; s; s=sNext) {
		sNext = s->next;
		delete s;
	}
	firstShape=current=NULL;
}

//////////////////
// Add shape to end of list, which is front.
// 
GPShape *GPShapeList::add(GPShape *shp)
{
	if (firstShape==NULL)
		firstShape=shp;
	else {
		GPShape *s;
		for (s = firstShape; s->next; s=s->next)
			;	// (run to end of list)
		s->next = shp;
	}
	shp->next = NULL;
	return shp;
}

//////////////////
// Remove shape from list.
// 
GPShape* GPShapeList::remove(GPShape *shp)
{
	if (firstShape==shp)
		firstShape = shp->next;
	else {
		forEachGPShape(*this, s) {
			if (s->next == shp) {
				s->next = shp->next;
				break;
			}
		}
	}
	shp->next=NULL;			// for safety
	return shp;
}

//////////////////
// Draw all shapes in list
// 
void GPShapeList::draw(WPDevContext& dc)
{ 
	forEachGPShape(*this, s)
		s->draw(dc); 
}

//////////////////
// Paint shapes in list. Like draw, but do clipping.
// 
void GPShapeList::paint(WPPaintDC& ps)
{ 
	ps.getPaintRect(GPShape::ClipRect);
	GPShape::ClipRect.normalize();
	BOOL save = GPShape::DoClip;
	GPShape::DoClip = TRUE;
	draw(ps);
	GPShape::DoClip = save;
}

//////////////////
// Do hit-detection for list of shapes: return topmost that hits.
// 
GPShape* GPShapeList::hitTest(WPPoint& p, int radius)
{ 
	GPShape *shp = NULL;
	forEachGPShape(*this, s) {
		if (s->hitTest(p, radius))
			shp = s;
	}
	return shp;
}
