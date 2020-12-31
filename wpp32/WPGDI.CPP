//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPGDI.CPP
//
// Implementation for Windows++ GDI functions.

#include "wpp.h"
#include <stdarg.h>

//////////////////
// Destroy drawing object, but only if delete flag says so.  
// Internal protected function.
// 
void WPDrawObj::destroy()
{ 
	if (hobj && del) { 
		BOOL res=DeleteObject(hobj); 
		assert(res); 
	} 
	hobj=NULL;
}

//////////////////
// Bitmap constructors
// 

//////////////////
// Create w/specified dimensions
// 
WPBitmap::WPBitmap(WPDevContext* dc, int w, int h)
{
	assert(dc);
	hobj = CreateCompatibleBitmap((*dc)(), w, h);
	assert(hobj);
	del = TRUE;
	init();
}

//////////////////
// Common initializer for all constructors: get width, height of bitmap
// 
void WPBitmap::init()
{
	assert(hobj);
	BITMAP bm;
	getObject(bm);
	ext.x = bm.bmWidth;
	ext.y = bm.bmHeight;
}

//////////////////
// Create bitmap from contents of screen rectangle
// This must be called right after creating a bitmap using the
// default constructor; e.g.
//		WPBitmap foo;
//		foo.copyScreen(myrect);
//
void WPBitmap::copyScreen(WPRect &rc)
{
	WPDisplay dcScreen;		// the whole display

	// Intersect rectangle with screen dimensions
	WPRect rcScreen((WPWin*)NULL);
	rc &= rcScreen;

	// Initialize bitmap to appropriate size
	destroy();
	hobj = CreateCompatibleBitmap(dcScreen, rc.width(), rc.height());
	assert(hobj);
	del = TRUE;
	init();

	// Copy the bits
	WPMemDC dcMem(&dcScreen, this);
	WPRect rcDst(0,0,rc.width(),rc.height());
	dcMem.bitBlt(rcDst, dcScreen, rc.origin());
}

//////////////////
// Parse device name.  If devname is NULL, get printer info.
// 
WPDEVNAME::WPDEVNAME(LPCSTR devname)
{
	if (devname)
		lstrcpy(deviceName, devname);
	else {
		WinIni.get("windows", "device", deviceName, sizeof(deviceName));
		strtok(deviceName,",");
	}
	int len = strlen(deviceName)+1;
	char *rest = deviceName + len;
	WinIni.get("devices", deviceName, rest, sizeof(deviceName)-len);
	driverName = strtok(rest,",");
	outputName = strtok(NULL,",");
}

const MAXSTOCKOBJ = 32;

//////////////////
// Private method to select a display object
// Destroys old selected object if required.
// "which" specifies whether object is a pen, brush, etc.
// "del" specifies whether to delete this object.
// If handle is small integer, assume stock object
// 
HGDIOBJ WPDevContext::select(WHICHOBJ which, HGDIOBJ h, BOOL del, BOOL bgPal)
{
	if ((UINT)h < MAXSTOCKOBJ) {
		h = GetStockObject((int)h);
		del = FALSE;			// never delete stock object!
	}
	assert(h);
	HANDLE old = SelectObject(hdc, (HANDLE)h);
	assert(old);
	WPDrawObj& obj = drawObj[which];
	assert(obj.hobj==NULL || obj.hobj==old);
	obj.destroy();
	obj.set((HANDLE)h, del);
	if (originalObj[which]==NULL)
		originalObj[which]=old;
	anySelected=TRUE;
	return old;
}

//////////////////
// Restore selected display objects (pens, brushes, etc.).
// 
void WPDevContext::restoreSelection()
{
	assert(hdc);
	if (anySelected) {
		for (int i=0; i < NDRAWOBJ; i++) {
			if (originalObj[i]) {
				SelectObject(hdc, originalObj[i]);
				originalObj[i]=NULL;		// don't restore twice!
				drawObj[i].destroy();
			}
		}
	}
}

HFONT WPDevContext::setFont(LPCSTR face, int ptsize, BOOL italic, int bold)
{ 
	int mmOld = mapMode(MM_TWIPS);
	LOGFONT font;
	memset(&font, 0, sizeof(font));
	lstrcpy((char*)font.lfFaceName, face);
	font.lfHeight = -ptsize * 20;
	font.lfWeight = bold;
	font.lfItalic = italic;
	HFONT hOld = (HFONT)select(SELFONT, CreateFontIndirect(&font), TRUE);
	mapMode(mmOld);
	return hOld;
}

WPDevInfo::WPDevInfo(LPCSTR devname)
{	
	WPDEVNAME dv = devname;		// parse device name
	hdc = CreateIC(dv.driverName, dv.deviceName, dv.outputName, NULL);
	assert(hdc); 
}

WPDevInfo::WPDevInfo(LPCSTR devname, LPCSTR driver, LPCSTR output, 
	DEVMODE* devmode) 
{
	hdc = CreateIC(driver, devname, output, devmode);
	assert(hdc); 
}

WPDevInfo::~WPDevInfo()	
{
	if (hdc) {
		BOOL ret = DeleteDC(hdc); 
		assert(ret); 
	} 
}

//////////////////
// printf-like function for device context.
// 
long WPDevContext::printF(WPPoint p, LPSTR format, ...)
{
	char buf[128];

	va_list argptr;
	va_start(argptr, format);
	int len = wvsprintf(buf, format, argptr);
	va_end(argptr);
	return textOut(p.x, p.y, buf, len);
}

//////////////////
// Windows should have provided DrawBitmap, but didn't, so here it is.
// Code is from Petzold.
// 
void WPDevContext::drawBitmap(int x, int y, WPBitmap* bitmap, DWORD rop)
{
	if (bitmap) {
		BITMAP bm;
		bitmap->getObject(bm);
		WPMemDC memdc(this, bitmap);
		WPRect dest;
		dest.origin(x, y);
		WPPoint p(bm.bmWidth, bm.bmHeight);
		DP2LP(&p, 1);
		dest.extent(p.x, p.y);
		p.x = p.y = 0;
		DP2LP(&p, 1);
		bitBlt(dest, memdc, p, rop);
	}
}

//////////////////
// Create Window DC
// 
WPWinDC::WPWinDC(WPWin *w)
{
	assert(w);
	win = w;
	hdc = GetDC((*w)());
	assert(hdc);
}

//////////////////
// Destroy Window DC: use ReleaseDC instead of DeleteDC.
// 
WPWinDC::~WPWinDC()
{
	if (anySelected)
		restoreSelection();
	BOOL ret = ReleaseDC((*win)(), hdc);
	assert(ret);
	hdc=NULL;
}

//////////////////
// Create window DC, including non-client area.
// 
WPNCWinDC::WPNCWinDC(WPWin *w)
{
	assert(w);
	win = w;
	hdc = GetWindowDC((*win)());
	assert(hdc);
}

//////////////////
// Create memory DC from bitmap
// 
WPMemDC::WPMemDC(WPDevContext *dc, WPBitmap *bm)
{
	hdc = CreateCompatibleDC(GetHDC(dc));
	assert(hdc);
	if (bm)
		setBitmap(bm);
	if (dc)
		mapMode(dc->mapMode());
}

//////////////////
// Create memory DC compatible w/existing DC.
// Rectangle says which window in primary DC to map; 
// "mono" flags creates monochrome bitmap.
//
WPMemDC::WPMemDC(WPDevContext *dc, WPRect& winRect, BOOL mono)
{
	hdc = CreateCompatibleDC(GetHDC(dc));
	assert(hdc);

	// Get bitmap dimensions: convert window rect to device coords.
	WPPoint p(winRect.width(), winRect.height());
	if (dc) {
		dc->LP2DP(&p, 1);
		mapMode(dc->mapMode());
	}
	HBITMAP h = 
		CreateCompatibleBitmap((dc && !mono) ? (*dc)() : hdc, p.x, p.y);
	assert(h);
	select(SELBITMAP, h, TRUE);
	windowOrg(winRect.origin()); // window origin = top left corner of rect
}

//////////////////
// Create paint structure. Call Windows BeginPaint function.
// 
WPPaintDC::WPPaintDC(WPWin *w)
{
	assert(w);
	hdc = BeginPaint((*w)(), &ps);
	assert(hdc);
	win = w;
}

//////////////////
// Destroy paint structure. Call Windows EndPaint function.
// 
WPPaintDC::~WPPaintDC()
{
	if (anySelected)
		restoreSelection();
	EndPaint((*win)(), &ps);
	hdc = NULL;
}

WPOwnerDrawDC::WPOwnerDrawDC(LPDRAWITEMSTRUCT draw)
{
	paintRect = draw->rcItem;
	action = draw->itemAction;
	state = draw->itemState;
	hdc = draw->hDC;
	assert(hdc);
}

WPOwnerDrawDC::~WPOwnerDrawDC()	
{
	restoreSelection(); 
	hdc = NULL; 
}

WPDisplayInfo::WPDisplayInfo() : WPDevInfo(NULL,"DISPLAY",NULL,NULL) 
{
}

WPDisplay::WPDisplay() : WPDevContext(NULL, "DISPLAY", NULL, NULL) 
{
}

WPPrinterInfo::WPPrinterInfo() : WPDevInfo(NULL) 
{
}

//////////////////
// Printing stuff
// 
BOOL WPPrinter::Abort;
WPDlgPrintAbort *WPPrinter::DlgAbort=NULL;

//////////////////
// Create printer device context
// 
WPPrinter::WPPrinter(LPCSTR devname, DEVMODE *devmode)
	: WPDevContext(devname, devmode)
{
	assert(hdc);
	pwin = NULL;
	delDC=TRUE; 
}

//////////////////
// Create printer from print dialog.
// 
WPPrinter::WPPrinter(WPDlgPrint& pdlg) : WPDevContext(pdlg.getHDC())
{
	assert(hdc);
	pwin = NULL;
	delDC=FALSE; 
}

//////////////////
// Do abort dialog
// 
int WPPrinter::doAbortDlg(WPWin *w)
{
	pwin = w;
	Abort = FALSE;
	assert(DlgAbort==NULL);
	DlgAbort = new WPDlgPrintAbort(pwin);
	if (pwin)
		pwin->enableWin(FALSE);
	return SetAbortProc(hdc, WPPrintAbortProc);
}

//////////////////
// Do printer STARTDOC function.
// 
int WPPrinter::startDoc(LPCSTR name, LPCSTR output)
{ 
	DOCINFO docinfo;
	docinfo.cbSize = sizeof(DOCINFO);
	docinfo.lpszDocName = name;
	docinfo.lpszOutput = output;
	docinfo.lpszDatatype = NULL;
	docinfo.fwType = 0;
	return StartDoc(hdc, &docinfo);
}

//////////////////
// Destroy printer: destroy abort dialog if it's still there.
// Don't delete the DC if it came from print dialog.
// 
WPPrinter::~WPPrinter()
{
	if (DlgAbort) {
		DlgAbort->destroyWin();
		DlgAbort=NULL;
	}
	if (pwin)
		pwin->enableWin(TRUE);
	if (anySelected)
		restoreSelection();
	if (!delDC)
		hdc=NULL;				// don't delete the DC
}

//////////////////
// Universal print abort procedure.
// 
BOOL CALLBACK WPPrintAbortProc(HDC hdcPrn, int nCode)
{
	MSG msg;
	HWND hDlgAbort = WPWin::GetHwnd(WPPrinter::DlgAbort);
	while (!WPPrinter::Abort && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (!hDlgAbort || !IsDialogMessage(hDlgAbort, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return !WPPrinter::Abort;
}

//////////////////
// Common initializer for all line printer constructors.
// Get text character height, lines per page, etc.
// 
void WPLinePrinter::init()
{
	TEXTMETRIC tm;
	textMetrics(tm);
	yChar = tm.tmHeight + tm.tmExternalLeading;
	nLinesPage = getVERTRES()/yChar-1;
	curLine = 0;
}

const char CONTROL_L = 12;

//////////////////
// Do line output. Automatically eject page properly.
// 
int WPLinePrinter::outLine(LPCSTR buf, int len)
{
	if (curLine==0)
		startPage();
	if (buf[0]==CONTROL_L)	// do form-feed for Control-L
		return formFeed();
	if (curLine >= nLinesPage)
		formFeed();
	textOut(0, yChar*curLine, buf, len);
	curLine++;
	return error();
}
