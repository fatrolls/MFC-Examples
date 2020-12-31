//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: MANDEL.CPP
//
// Sample program to generate and display the Mandelbrot Set

#include "prefix.h"
#include <time.h>
#include "mandel.h"
#include "complex.h"

MyApp myApp; // instantiate one and only app

const MAXITERATIONS = 128;	// max number of iterations
const DIVERGE = 4;			// sequence diverges if abs value greater than 4
const MAXNCOLORS = 256;		// maximum number of colors to use
const NSUBDIVISIONS = 20;	// subdivision of little rectangles

//////////////////
// The main window
// 
class Mandelbrot : public WPMainWin {
	COLORREF *colors;			// array of colors used to paint
	COLORREF clrWhite;		// actual color white
	WPMemDC *memdc;			// memory bitmap
	int ncolors;				// number of colors

	WPRect clientBox;			// client area rectangle
	WPRect magnifyBox;		// box to magnify
	WPRect drawBox;			// current box we're drawing
	WPPoint moveRight, moveDown;		// used to translate drawBox

	complex cmin, cmax;		// rectangle in complex plane
	complex delta;				// complex increment
	
	BOOL dragging;				// we are dragging mouse
	BOOL pause;					// we are paused
	BOOL done;					// we are done painting the screen

	void init();				// initialize bitmap and calculation
	COLORREF computePixel(WPPoint p, complex& c);

public:
	Mandelbrot();
	~Mandelbrot();

	// Virtual message functions
	void paint(WPPaintDC& dc);
	BOOL command(int id, WORD msg);
	BOOL mouse(int msg, WPPoint p, WORD flags);
	BOOL sized(WPRect &box, WORD how);
	BOOL doIdle();
	BOOL fileNew();
};

//////////////////
// This class is used to draw the bitmap in the About dialog box.
// 
class BitmapButton : public WPODButton {
	WPBitmap *bitmap;
public:
	BitmapButton(WPWin *pwin, int id, LPCSTR bitmapname) : WPODButton(pwin, id)
		{ bitmap = new WPBitmap(bitmapname); assert((HBITMAP)bitmap); }
	~BitmapButton()				{ delete bitmap; }
	void paint(WPOwnerDrawDC &dc, ODDATA data) 
		{ if ((dc.action & ODA_DRAWENTIRE) && bitmap) 
			dc.drawBitmap(0, 0, bitmap); }
	BOOL gotFocus(WPWin *prev)
		{ if (prev) prev->setFocus(); return TRUE; }
};

//////////////////
// Abouf dialog box: the only thing special is an owner-draw button
// 
class AboutMandel : public WPDialogModal {
public:
	AboutMandel(WPWin *pwin) : WPDialogModal("DLGABOUT",pwin) { run(); }
	void initDlg() { new BitmapButton(this, ID_BITMAP, "AboutBitmap"); }
};

void MyApp::main()
{
	mainWin = new Mandelbrot;
	run();
}

//////////////////
// Create main window
// 
Mandelbrot::Mandelbrot()
{
	createArgs.wndcls.hCursor = NULL;	// we will set our own cursor
	createWin("Mandelbrot Set");	// create window
	time_t ntime;						// seed for random num generator
	srand(time(&ntime));				// ..

	// Allocate array of colors
	WPWinDC dc = this;
	int devcolors = dc.getNUMCOLORS();
	ncolors = devcolors>0 ? min(devcolors, MAXNCOLORS) : MAXNCOLORS;
	colors = new COLORREF [ncolors];

	memdc = NULL;
	dragging = FALSE;
	pause = FALSE;
	done = FALSE;

	fileNew();
}

//////////////////
// Destroy window: destroy bitmap and color array
// 
Mandelbrot::~Mandelbrot()
{
	delete memdc; 
	delete colors;
}

////////////////
// File New command: restore default plane region, pick random colors.
// 
BOOL Mandelbrot::fileNew()
{
	WPWinDC dc = this;
	for (int i=0; i<ncolors; i++)
		colors[i] = 
			dc.nearestColor(RGB(5+rand()%250, 5+rand()%250, 5+rand()%250));
	cmin.set(-2.0, -1.2);	// default region in complex plane
	cmax.set(1.2, 1.2);		// ..to show
	init();
	return TRUE;
}

//////////////////
// Initialize plane region.  
// 
void Mandelbrot::init()
{
	clientBox = this;

	// compute delta value to increment complex number "c"
	//
	delta.real((cmax.real()-cmin.real())/clientBox.width());
	delta.imag((cmax.imag()-cmin.imag())/clientBox.height());

	//////
	// Compute logical y-origin for window.  If the plane region spans
	// both positive and negative y (imaginary) values, we want to
	// take advantage of symmetry by setting the window coords with a 
	// negative y-origin.
	// 
	if (cmin.imag() < 0 && cmax.imag() > 0) 
		clientBox += WPPoint(0, (int)( cmin.imag() / delta.imag()));

	// Create memory bitmap and initialize it to all white.
	WPWinDC dc = this;
	delete memdc;
	memdc = new WPMemDC(&dc, clientBox);
	memdc->whiteOut(clientBox);
	clrWhite = memdc->pixel(0,0); // could get re-mapped
	done = FALSE;

	// Compute size of incremental "draw" box.
	drawBox = clientBox;
	int w = ((drawBox.width() +(NSUBDIVISIONS-1))/NSUBDIVISIONS) | 1;
	int h = ((drawBox.height()+(NSUBDIVISIONS-1))/NSUBDIVISIONS) | 1;
	drawBox.extent(w, h);
	moveRight.set(w, 0);			// moves box right
	moveDown.set(0,h);			// moves box down

	invalidate(TRUE);				// clear screen
}

//////////////////
// Paint: just blast the bitmap to the screen.
// 
void Mandelbrot::paint(WPPaintDC& dc)
{
	WPRect dst = this;
	dc.stretchBlt(dst, *memdc, clientBox);
}

//////////////////
// User re-sized the window.  
// If we're done, just re-paint; otherwise re-initialize bitmap.
// 
BOOL Mandelbrot::sized(WPRect &box, WORD how)
{
	if (!done)					// not done drawing:
		init();					// ..start all over
	return TRUE;
}

//////////////////
// Handle menu command.
// 
BOOL Mandelbrot::command(int id, WORD msg)
{
	switch (id) {
	case WPIDM_ABOUT:
		AboutMandel(this);	// do special "About" dialog
		return TRUE;

	case IDM_PAUSE:
		pause = !pause;
		WPMenu menu = this;
		menu.modify(IDM_PAUSE, IDM_PAUSE, pause ? "&Continue!" : "&Pause!");
		drawMenu();
		return TRUE;
	}
	return WPMainWin::command(id, msg);
}

//////////////////
// Handle mouse message.  
// This implements the drag-select-magnify-region function.
// 
BOOL Mandelbrot::mouse(int msg, WPPoint p, WORD flags)
{
	switch(msg) {
	case WM_LBUTTONDOWN:
		if (!dragging) {
			dragging=TRUE;
			Cursor.clip(this);
			Cursor = IDC_CROSS;
			magnifyBox.origin(p);
			magnifyBox.endpt(p);
		}
		break;
			
	case WM_MOUSEMOVE:
		Cursor = dragging ? IDC_CROSS : IDC_ARROW;
		if (dragging) {
			if (p != magnifyBox.endpt()) {
				WPWinDC dc = this;
				dc.drawFocusRect(magnifyBox);	// erase old focus rect
				magnifyBox.endpt(p);
				dc.drawFocusRect(magnifyBox);	// draw new one
			}
		} 
		break;

	case WM_LBUTTONUP:
		if (!magnifyBox.isEmpty()) {
			magnifyBox.normalize();
			WPRect rect = this;
			REAL xscale = (cmax.real()-cmin.real())/rect.width();
			REAL yscale = (cmax.imag()-cmin.imag())/rect.height();
			cmax.set(cmin.real() + xscale * magnifyBox.right,
						cmin.imag() + yscale * magnifyBox.bottom);
			cmin.set(cmin.real() + xscale * magnifyBox.left,
						cmin.imag() + yscale * magnifyBox.top);
			init();
		}
		Cursor = IDC_ARROW;
		Cursor.unClip();
		dragging = FALSE;
		break;
	}
	return TRUE;
}

//////////////////
// Compute color of pixel and set it in the bitmap. Returns color.
// 
COLORREF Mandelbrot::computePixel(WPPoint p, complex &c)
{
	COLORREF color = memdc->pixel(p);
	if (color == clrWhite) {
		complex z;
		int n;
		for (n = 0; n<MAXITERATIONS; n++) {
			REAL zrr = z.real() * z.real();
			REAL zii = z.imag() * z.imag();
			REAL zir2 = 2 * z.real() * z.imag();
			if (zrr + zii >= DIVERGE)
				break;
			z.real(zrr-zii + c.real());
			z.imag(zir2 + c.imag());
		}
		color = n>=MAXITERATIONS ? COLOR_BLACK : colors[n % ncolors];
		memdc->pixel(p, color);

		if (clientBox.top != 0) {
			p.y = -p.y;						// use symmetry
			memdc->pixel(p, color);
		}
	}
	return color;
}

//////////////////
// Compute next little rectangle of pixels. We take advantage of the fact
// that each colored region is connected: if all the boundary points of a
// box are the same color, we can fill the box with that color and be done
// with it.
// 
BOOL Mandelbrot::doIdle()
{
	if (done || dragging || pause)
		return TRUE;

	WPRect box;
	for (box = drawBox; !box.isEmpty(); --box) {
		// Each iteration of this loop paints the boundary of the box,
		// then shrinks the box one pixel.
		COLORREF color1, color;
		BOOL first = TRUE;
		BOOL allSameColor = TRUE;		// assume boundary points are same color

		// do top edge
		WPPoint p = box.origin();
		REAL creal = cmin.real() + (p.x * delta.real());
		REAL cimag = cmin.imag() + ((p.y-clientBox.top) * delta.imag());
		complex c (creal, cimag);
		for (p.x=box.left; p.x <= box.right; p.x++) {
			color = computePixel(p, c);
			if (first)
				color1 = color;
			else if (color != color1)
				allSameColor = FALSE;
			first = FALSE;
			c.real() += delta.real();
		}
		
		// do bottom edge
		p.y = box.bottom;
		c.real(creal);
		c.imag(cmin.imag() + ((p.y-clientBox.top) * delta.imag()));
		for (p.x=box.left; p.x <= box.right; p.x++) {
			if (computePixel(p, c) != color1)
				allSameColor = FALSE;
			c.real() += delta.real();
		}

		// do left edge
		p.x = box.left;
		c.real(creal);
		c.imag(cimag);
		for (p.y=box.top; p.y<=box.bottom; p.y++) {
			if (computePixel(p, c) != color1)
				allSameColor = FALSE;
			c.imag() += delta.imag();
		}

		// do right side
		p.x = box.right;
		c.real(cmin.real() + (p.x * delta.real()));
		c.imag(cimag);
		for (p.y=box.top; p.y<=box.bottom; p.y++) {
			if (computePixel(p, c) != color1)
				allSameColor = FALSE;
			c.imag() += delta.imag();
		}

		if (allSameColor) {
			// All boundary points are the same color: 
			// fill the box and quit loop.
			if (color==COLOR_BLACK) {
				memdc->blackOut(box);
				if (clientBox.top != 0) {
					// use symmetry
					box.top    = 1-box.top;
					box.bottom = 1-box.bottom;
					memdc->blackOut(box);
				}

			} else {
				WPBrush brush(color);
				memdc->fill(box, brush);
				if (clientBox.top != 0) {
					// use symmetry
					box.top	  = 1-box.top;
					box.bottom = 1-box.bottom;
					memdc->fill(box, brush);
				}
			}
			break;
		} 
	}

	// Now blast the result to window
	WPWinDC dc = this;
	dc.windowOrg(clientBox.origin());
	box = drawBox;
	dc.bitBlt(box, *memdc, box.origin());
	if (clientBox.top != 0) {
		box.top		= 1-box.top;			 // use symmetry
		box.bottom	= 1-box.bottom;
		dc.bitBlt(box, *memdc, box.origin());
	}

	// Move box right; if at edge, move down to start of next row
	// 
	drawBox += moveRight;
	if (drawBox.left >= clientBox.right) {
		drawBox.left = 0;
		drawBox.right = moveRight.x;
		drawBox += moveDown;
		if (clientBox.top !=0 && drawBox.top >= 1) {
			while (drawBox.bottom <= -clientBox.top)
				drawBox += moveDown;
		}
		if (drawBox.top >= clientBox.bottom)
			done = TRUE;
	}
	return TRUE;
}

