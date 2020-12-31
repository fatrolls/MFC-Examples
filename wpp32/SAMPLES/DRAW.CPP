//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: DRAW.CPP
//
// Sample Object-Oriented Graphics Editor using GPP Graphics.

#include "prefix.h"
#include <gpp.h>
#include "draw.h"

MyApp myApp; // instantiate one and only app

const HIT_RADIUS = 7;		// radius for hit test
const HANDLE_RADIUS = 3;	// radius for size handles

enum DRAGSTATE		{ NODRAG=0, DRAGMOVE, DRAGSIZE };
enum MOVESTATE		{ MOVEALL=0, MOVEFIRST, MOVEX, MOVEY, MOVEDIAG };

//////////////////
// Main DRAW window class.
// 
class DrawWin : public WPMainWin {
	static WPRect DfltSize;	// default size for new shapes
	GPShapeList shapes;		// list of shapes
	GPHilite* hilite;			// current hilite (selected) shape
	GPShape* newShape;		// pending new shape

	// Dragging stuff
	DRAGSTATE dragging;		// drag mode (move/size)
	WPPoint	orgPt;			// pt where started dragging
	WPPoint	prevPt;			// previous point in drag
	WPPoint	anchorPt;		// size anchor point
	WPRect	orgBounds;		// original bounds of shape
	
	// Mouse constraint stuff
	WPPoint orgMousePt;
	MOVESTATE motion;
	long ax, ay;

	// Internal methods
	GPShape* setNewShape(GPShape *shp);
	GPHilite* setHilite(GPShape *shp);
	void XORShape(WPDevContext& dc, GPShape *shp);
	void constrainMouse(WORD msg, WPPoint& p, WORD flags);

public:
	DrawWin();
	~DrawWin() { delete newShape; }

	// Virtual message functions
	void paint(WPPaintDC& dc)		{ shapes.paint(dc); }
	BOOL anySelected()				{ return hilite!=NULL; }
	BOOL menuInit(WPMenu &menu);
	BOOL mouse(int msg, WPPoint p, WORD flags);
	BOOL command(int id, WORD msg);
	BOOL fileNew();
	BOOL filePrint(WPDlgPrint &pdlg);
};

// Default size for new shapes: sqaure
WPRect DrawWin::DfltSize(0,0,10,-10);

////////////////
// Program entry point
// 
void MyApp::main()
{
	mainWin = new DrawWin;
	run();
}

DrawWin::DrawWin() : WPMainWin("DRAWWIN")
{ 
	hilite = NULL;
	newShape = NULL;

	createArgs.wndcls.hCursor = NULL;		// I'll set cursor myself
	createArgs.wndcls.style |= CS_OWNDC;	// create my own DC
	createWin("Windows++ DRAW");				// create main window
	WPWinDC dc = this;
	dc.mapMode(MM_LOMETRIC);					// (1 logical unit = .1 mm)
	fileNew();
}

//////////////////
// Draw shape in XOR mode.
// 
void DrawWin::XORShape(WPDevContext& dc, GPShape *shp)
{
	dc.setPen(WHITE_PEN);
	dc.setBrush(NULL_BRUSH);
	dc.rop2(R2_XORPEN);
	shp->drawShape(dc);
	dc.rop2(R2_COPYPEN);
}

//////////////////
// Set the new shape: destroy old one, change cursor.
// 
GPShape* DrawWin::setNewShape(GPShape *shp)
{
	delete newShape; 
	if (shp)
		Cursor = "CrsNew";
	return newShape = shp;
}

//////////////////
// Select new shape. De-select previous one, if any.
// 
GPHilite* DrawWin::setHilite(GPShape *shp)
{
	if (shp != hilite) {
		if (hilite) {
			if (hilite->shape()==shp)
				return hilite;
			// Un-hilite previous shape
			hilite->invalidate(this,TRUE);
			delete shapes.remove(hilite);
			hilite = NULL;
			update();
		}
		if (shp) {
			// Hilite new shape
			hilite = new GPHilite(shp, HANDLE_RADIUS);
			hilite->invalidate(this);
			shapes.add(hilite);
			update();
		}
	}
	return hilite;
}

//////////////////
// Handle mouse action.
// 
BOOL DrawWin::mouse(int msg, WPPoint p, WORD flags)
{
	constrainMouse(msg, p, flags);
		
	GPShape *shp;
	WPWinDC dc = this;		// get window DC..
	dc.DP2LP(p);				// convert mouse to logical coords

	switch(msg) {
	case WM_LBUTTONDOWN:
		if (newShape) {
			// New shape pending: drop it at mouse location
			WPRect extent;
			shp = newShape;					// New shape:
			shp->getExtent(extent);			// get its extent
			extent += p-extent.endpt();	// move to mouse location
			shp->setExtent(extent);			// ..and set
			shapes.add(shp);					// add to shape list..
			shp->draw(dc);						// ..and draw.
		} else
			shp = shapes.hitTest(p, HIT_RADIUS);

		if (setHilite(shp)) {
			if (newShape) {
				shp = hilite;					// so we'll do drag size mode
				newShape=NULL;					// clear
			}

			// If there's a hilited shape, set up drag state
			Cursor = "CrsDrag";
			Cursor.clip(this);
			prevPt = orgPt = p;
			shp->getBounds(orgBounds);
			anchorPt = hilite->anchor(p);

			// Now go into appropriate mode and XOR shape.
			if (shp==hilite) {
				dragging = DRAGSIZE;
				shp=hilite->shape();
			} else
				dragging = DRAGMOVE;
			XORShape(dc, shp);
		}
		break;

	case WM_MOUSEMOVE:
		Cursor = newShape ? "CrsNew" : (dragging ? "CrsDrag" : IDC_ARROW);
		if (dragging && p != prevPt) {
			shp = hilite->shape();			// selected shape
			XORShape(dc,shp);					// XOR (erase) at old location
			WPRect extent;				
			shp->getExtent(extent);
			if (dragging==DRAGMOVE)			// drag move:
				extent += p-prevPt;			//		move extent
			else									// drag size:
				extent.set(anchorPt, p);	//		size extent
			shp->setExtent(extent);			// move the shape
			XORShape(dc, shp);				// XOR (draw) at new location
			prevPt = p;
		}
		break;

	case WM_LBUTTONUP:
		if (dragging) {
			shp = hilite->shape();				// selected shape
			XORShape(dc, shp);					// erase prev location
			if (p != orgPt) {
				dc.LP2DP(orgBounds);
				invalidate(orgBounds, TRUE);
				setHilite(NULL);					// un-hilite (old location)
				shp->invalidate(this);			// repaint
				setHilite(shp);					// re-hilite (new location)
			}
			Cursor = IDC_ARROW;
			Cursor.unClip();
			dragging=NODRAG;
		}
		break;
	}
	return TRUE;
}

//////////////////
// This function implements the mouse chords.
// 
void DrawWin::constrainMouse(WORD msg, WPPoint& p, WORD flags)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
		orgMousePt=p;						// save original mouse pos
		motion = MOVEFIRST;				// this is first motion
		break;

	case WM_MOUSEMOVE:
		if (!dragging || motion==MOVEALL)
			break;

		WPPoint delta = p - orgMousePt;
		if (motion==MOVEFIRST) {
			// This is first mouse motion: determine constraint, if any.
			if (flags & MK_SHIFT)
				motion = (abs(delta.x) > abs(delta.y)) ? MOVEX : MOVEY;

			else if (flags & MK_CONTROL && dragging==DRAGSIZE) {
				WPRect aspect(anchorPt, hilite->anchor(anchorPt));
				if (aspect.width()==0)
					motion = MOVEY;
				else if (aspect.height()==0)
					motion = MOVEX;
				else {
					motion = MOVEDIAG;
					WPWinDC dc = this;
					dc.LP2DP(aspect);
					ax = aspect.width();
					ay = aspect.height();
				}
			} else
				motion = MOVEALL;
		}
		WPPoint newPt = p;
		if (motion==MOVEX)
			newPt.y = orgMousePt.y;		// do horizontal constraint
		else if (motion==MOVEY)
			newPt.x = orgMousePt.x;		// do vertical constraint
		else if (motion==MOVEDIAG) {
			// do diagonal (aspect ratio) constraint
			if (abs(delta.x) > abs(delta.y))
				delta.y = (ay * (long)delta.x) / ax;
			else 
				delta.x = (ax * (long)delta.y) / ay;
			newPt = orgMousePt + delta;
		}
		if (newPt != p) {					// if point was constrained:
			p = newPt;
			clientToScreen(&newPt);		// convert to screen coords
			Cursor = newPt;				// ..and udpate real cursor
		}
		break;
	}
}

//////////////////
// Function to convert Menu ID to COLORREF.
// 
static COLORREF MenuColor(int id)
{
	static COLORREF colorMap[] = {	
		COLOR_BLACK,	COLOR_WHITE,	COLOR_RED, 
		COLOR_GREEN,	COLOR_BLUE,		COLOR_NONE
	};
	if (id<0 || id>=ID_COLORLAST)
		return COLOR_NONE;
	return id==ID_COLORRANDOM ? RGB(rand()&255, rand()&255, rand()&255)
		: colorMap[id];
}

//////////////////
// Handle menu command.
// 
BOOL DrawWin::command(int id, WORD msg)
{
	switch (id) {
	case ID_NEWLINE:
		setNewShape(new GPLine(DfltSize));
		return TRUE;
	case ID_NEWRECT:
		setNewShape(new GPRect(DfltSize));
		return TRUE;
	case ID_NEWELLIPSE:
		setNewShape(new GPEllipse(DfltSize));
		return TRUE;

	case WPIDM_EDITDELETE:
		if (hilite) {
			hilite->shape()->invalidate(this);
			delete shapes.remove(hilite->shape());
			setHilite(NULL);
		}
		return TRUE;
	case ID_EDITDUP:
		if (hilite) {
			GPShape *shp = hilite->shape();
			shapes.add(shp->dup());
			setHilite(shp);
		}
		return TRUE;
	case ID_FRONT:
	case ID_BACK:
		if (hilite) {
			GPShape *shp = hilite->shape();
			if (id==ID_FRONT) {
				shapes.front(shp);		// move to front
				shapes.front(hilite);	// ..but not ahead of hilite
			} else
				shapes.back(hilite->shape());
			shp->invalidate(this);
			update();
		}
		return TRUE;

	default:
		if (id >= ID_EDGE && id<ID_FILL+ID_COLORLAST) {
			if (hilite) {
				GPShape *shp = hilite->shape();
				if (id >= ID_FILL)
					shp->fillColor(MenuColor(id-ID_FILL));
				else
					shp->edgeColor(MenuColor(id-ID_EDGE));
				shp->invalidate(this);
				update();
			}
			return TRUE;
		}
		break;
	}
	return WPMainWin::command(id, msg);
}

//////////////////
// Handle File New command. Set everything to initial state.
// 
BOOL DrawWin::fileNew()
{
	shapes.deleteAll();
	setNewShape(NULL);
	hilite = NULL;
	dragging = NODRAG;
	invalidate(TRUE);
	update();
	return TRUE;
}

//////////////////
// Print shapes. Pretty easy: just draw on printer DC!
// 
BOOL DrawWin::filePrint(WPDlgPrint &pdlg)
{
	WPPrinter p = pdlg;
	p.mapMode(MM_LOMETRIC);
	p.doAbortDlg(this);
	p.startDoc("DRAW");
	shapes.draw(p);
	p.endPage();
	p.endDoc();
	return TRUE;
}

//////////////////
// Initialize menu. 
// Do DRAW-specific commands, then pass to WPMainWin.
// 
BOOL DrawWin::menuInit(WPMenu &menu)
{
	WPMenu mainMenu = this;
	if (menu==mainMenu) {
		WPSubMenu editMenu(menu, 1);
		BOOL any = anySelected();
		for (int i=0; i<NEDITCOMMANDS; i++)
			editMenu.enableItem(i, any, MF_BYPOSITION);
		editMenu.enableItem(POS_NEW, TRUE, MF_BYPOSITION);
	}
	return WPMainWin::menuInit(menu);		// pass along to main win!
}
