//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: GPP.H
//
// Definitions for GPP (Graphics++) objects.

#ifndef GPP_H
#define GPP_H

#include "wpp.h"

DLLCLASS GPShapeList;

//////////////////
// Generic shape, an abstract class
// 
DLLCLASS GPShape {
	GPShape *next;				// next shape in list
	COLORREF edge;				// edge color
	COLORREF fill;				// interior color
	void init()					{ edge = COLOR_BLACK; fill = COLOR_NONE; }
protected:
	static WPRect ClipRect;	// global clipping rectangle
	static BOOL DoClip;		// whether to clip
	WPRect extent;				// extent of shape
	friend GPShapeList;
public:
	GPShape()					{ init(); }
	GPShape(WPRect& r)		{ init(); setExtent(r); }
	virtual ~GPShape()		{ }

	static void Clip(WPRect* r);		// set clipping rectangle

	// Data access
	COLORREF edgeColor()					{ return edge; }
	COLORREF edgeColor(COLORREF c)	{ return edge=c; }
	COLORREF fillColor()					{ return fill; }
	COLORREF fillColor(COLORREF c)	{ return fill=c; }
	void getExtent(WPRect& e)			{ e = extent; }
	void setExtent(WPRect& e)			{ extent = e; }

	// Virtual functions for specific shapes to implement
	virtual void getBounds(WPRect& r);
	virtual void draw(WPDevContext &dc);
	virtual void drawShape(WPDevContext &dc) = 0;
	virtual void invalidate(WPWin *w, BOOL erase=FALSE);
	virtual BOOL hitTest(WPPoint p, int radius);
	virtual int getHandles(WPPoint *buf);
	virtual GPShape* dup()		{ GPShape *s = clone(); 
		if (s) memcpy(s,this,sizeof(GPShape)); return s; }
	virtual GPShape* clone()	{ return NULL; }
};

//////////////////
// Line
// 
DLLCLASS GPLine : public GPShape {
public:
	GPLine(WPRect& r) : GPShape(r)	{ }
	void drawShape(WPDevContext &dc)	
		{ dc.line(extent.origin(), extent.endpt()); }
	int getHandles(WPPoint *buf);
	GPShape* clone()						{ return new GPLine(extent); }
};

//////////////////
// Rectangle
// 
DLLCLASS GPRect : public GPShape {
public:
	GPRect(WPRect &r) : GPShape(r)	{ }
	void drawShape(WPDevContext &dc)	{ dc.rectangle(extent); }
	GPShape* clone()						{ return new GPRect(extent); }
};

//////////////////
// Ellipse
// 
DLLCLASS GPEllipse : public GPShape {
public:
	GPEllipse(WPRect &r) : GPShape(r)	{ }
	void drawShape(WPDevContext &dc)		{ dc.ellipse(extent); }
	GPShape* clone()							{ return new GPEllipse(extent); }
};

//////////////////
// "Hilite" shape.
// 
DLLCLASS GPHilite : public GPShape {
	GPShape *hishape;			// hilighted shape
	WPPoint handles[4];		// size handles
	int nhandles;				// number of handles
	int radius;					// handle radius
public:
	GPHilite(GPShape *obj, int r);
	GPShape *shape()			{ return hishape; }
	void drawShape(WPDevContext &dc);
	BOOL hitTest(WPPoint p, int radius);
	WPPoint anchor(WPPoint p);
	void invalidate(WPWin *w, BOOL erase=FALSE);
};

//////////////////
// List of shapes.  List is implicitly ordered from bottom to top,
// so drawing can be done by navigating the list.
// 
DLLCLASS GPShapeList {
	GPShape *firstShape;		// first (bottom) in list
	GPShape *current;			// transient current for list navigation
public:
	GPShapeList()				{ firstShape = current = NULL; }
	~GPShapeList()				{ deleteAll(); }

	void deleteAll();

	// Navigation methods
	GPShape *operator()()	{ return current; }
	GPShape *next()			{ return current ? current=current->next : NULL; }
	GPShape *first()			{ return current=firstShape; }

	// Add/remove etc.
	GPShape *add(GPShape *obj);
	GPShape *remove(GPShape *obj);
	GPShape *front(GPShape *obj) { return add(remove(obj)); }
	GPShape *back(GPShape *obj)		
		{ remove(obj); obj->next = firstShape; return firstShape = obj; }

	// Miscellaneous
	void paint(WPPaintDC& ps);
	void draw(WPDevContext& dc);
	GPShape* hitTest(WPPoint& p, int radius);
};

//////////////////
// Macro lets you write:
// 
//		forEachGPShape(list, shape)
//			shape->doSomething();
// 
#define forEachGPShape(list, s) \
	GPShape *s; \
	for (s = (list).first(); s; s=(list).next()) 

#endif
