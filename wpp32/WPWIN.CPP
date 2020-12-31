//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPWIN.CPP
//
// Implementation of base window class for all window objects.

#include "wpp.h"

// this property links a window to its object
char WP_WINPTR[] =  "w+";

WINCREATEARGS WPWin::createArgs;
TEXTMETRIC WPWin::tm;
WPWin *WPWin::NewWin = NULL;

////////////////////////////////////////////////////////////////
// This is THE Window Proc used for all Windows++ windows!
// The only message it actually handles is WM_DESTROY, to which it
// responds by destroying the linked Windows++ object.  Windows++
// programs should now NEVER DELETE WINDOWS OBJECTS, and window 
// object must always be created with "new", not on the stack.
// 
LRESULT DLLFUNC CALLBACK WPWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	WPWin* win = WPWin::GetWin(hwnd);
	assert(win);

	if (msg==WM_DESTROY) {	// got WM_DESTROY:
		if (win->deletable)
			delete win;			// call virtual destructor
		else
			win->unLinkHwnd();
		return 0;
	}
	WPEvent event(msg, wp, lp);	// create an event object on the stack
	return win->msgProc(event);	// call virtual message proc
}

////////////////
// Always allocate from local heap so we can store 
// 16-bit offset in window property list.  
// Also, store ptr in NewWin so constructor can mark as deletable.
// 
void* WPWin::operator new(size_t size)
{ 	
	return NewWin = (WPWin*)new char[size];
} 

void WPWin::operator delete(void* ptr)
{ 
	assert(((WPWin*)ptr)->deletable);
	delete [] (char*)ptr;
}

//////////////////
// Initialize WPWin instance.
// 
WPWin::WPWin(LPCSTR classnm, WPWin* pwin, int id)
{
	oldProc = NULL;
	hwnd = NULL;
	deletable = this==NewWin;
	NewWin=NULL;

	// set default registration args
	createArgs.wndcls.lpszClassName = (LPSTR)classnm;
	createArgs.wndcls.style = CS_HREDRAW | CS_VREDRAW;
	createArgs.wndcls.lpfnWndProc = DefWindowProc;
	createArgs.wndcls.cbClsExtra = 0;
	createArgs.wndcls.cbWndExtra = 0;
	createArgs.wndcls.hInstance = theApp->getHinst();
	createArgs.wndcls.hIcon = NULL;
	createArgs.wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	createArgs.wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	createArgs.wndcls.lpszMenuName = NULL;

	// set default creation args
	createArgs.title = NULL;
	createArgs.style = createArgs.exstyle = 0;
	createArgs.pos.origin(CW_USEDEFAULT, CW_USEDEFAULT);
	createArgs.pos.extent(CW_USEDEFAULT, CW_USEDEFAULT);
	createArgs.hmenu = (HMENU)id;
	createArgs.parent = pwin;
	createArgs.lparam = NULL;
	if (pwin)
		// child window: set style and chain to list
		createArgs.style = WS_CHILDWINDOW | WS_VISIBLE;
}

//////////////////
// Link object to a real (Windows) window.
// 
void WPWin::linkHwnd(HWND newhwnd)
{
	assert(hwnd==NULL);						// better not be already linked!
	assert(IsWindow(newhwnd));				// better have a real HWND!
	hwnd = newhwnd;							// store Window handle
	setProp(WP_WINPTR, (HANDLE)this);	// store ourself in window prop

	//////
	// Now "hook" the window's window proc--i.e., subclass it, saving
	// the original window procedure.
	// 
	oldProc = (WNDPROC)GetWindowLong(hwnd, GWL_WNDPROC);
	SetWindowLong(hwnd, GWL_WNDPROC, (LONG)theApp->getWndProc());

	if (hwnd) {
		WPWinDC dc = this;
		dc.textMetrics(tm);
	}
}

//////////////////
// Get window object from window handle (HWND)
// 
WPWin* WPWin::GetWin(HWND hwnd)
{ 
	if (hwnd==NULL) 
		return NULL;
	assert(IsWindow(hwnd));
	return (WPWin*) GetProp(hwnd, WP_WINPTR);
}

////////////////
// Destroy window: unlink it.
// 
WPWin::~WPWin()
{
	unLinkHwnd();
}

//////////////////
// Unlink a window.
// 
void WPWin::unLinkHwnd()
{
	if (hwnd) {								// if linked:
		if (oldProc) {
			// restore old window proc
			SetWindowLong(hwnd, GWL_WNDPROC, (LONG)oldProc);
			oldProc = NULL;				// just to be safe!
		}
		assert(GetWin(hwnd)==this);	// double-check for safety
		removeProp(WP_WINPTR);			// free up window property
		hwnd = NULL;						// goodbye window handle!
	}
}

//////////////////
// Create window using current values in createArgs.
// 
BOOL WPWin::createWin()
{
	// Note: window (HWND) might already exist if attached to a dialog control
	// 
	if (hwnd==NULL) {
		LPCSTR classnm = createArgs.wndcls.lpszClassName;
		assert(classnm);
		HINSTANCE hinst = createArgs.wndcls.hInstance;
		assert(hinst);
		WNDCLASS temp;

		// Register window class if it ain't already registered!
		if (!GetClassInfo(hinst, classnm, &temp) &&	// try module..
			!GetClassInfo(NULL, classnm, &temp)) {		// ..and built-in

			BOOL ret = RegisterClass(&createArgs.wndcls);
			assert(ret);
		}

		HWND newhwnd = CreateWindowEx(createArgs.exstyle,
			classnm,
			(LPSTR)createArgs.title,
			createArgs.style, 
			createArgs.pos.left,
			createArgs.pos.top,
			createArgs.pos.width(),
			createArgs.pos.height(),
			GetHwnd(createArgs.parent),
			createArgs.hmenu, 
			hinst,
			createArgs.lparam);
		linkHwnd(newhwnd);
	}
	return hwnd!=NULL;
}

//////////////////
// Virtual message procedure handles messages sent from Windows.
// 
LONG WPWin::msgProc(WPEvent &event)
{ 
	switch (event.msg) {
	case WM_QUERYENDSESSION:
		return queryEnd();
	case WM_QUERYOPEN:
		return queryMaximize();
	}
	return dispatchEvent(event) ? event.ret : dfltMsgProc(event); 
}

//////////////////
// Dispatch message to appropriate virtual function
// 
BOOL WPWin::dispatchEvent(WPEvent &event)
{
	switch (event.msg) {
	case WM_PAINT:
		return paint();
	case WM_GETMINMAXINFO:
		return getMinMaxInfo((LPMINMAXINFO)event.lp);
	case WM_ACTIVATE:
		return activated(event.wp, HIWORD(event.lp));
	case WM_ENABLE:
		return enabled(event.wp);
	case WM_SETFOCUS:
		return gotFocus(GetWin((HWND)event.wp));
	case WM_KILLFOCUS:
		return killedFocus(GetWin((HWND)event.wp));
	case WM_HSCROLL:
	case WM_VSCROLL:
	    {
		HWND sbhwnd = (HWND)HIWORD(event.lp);
		int id = sbhwnd ? GetDlgCtrlID(sbhwnd) : 
			event.msg==WM_VSCROLL ? WPIDSB_VERT : WPIDSB_HORZ;
		return scrolled(event.wp, id, LOWORD(event.lp));
	    }
	case WM_KEYDOWN:	case WM_KEYUP:	case WM_CHAR:	case WM_DEADCHAR:
		return kbd(event);

	case WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:	case WM_RBUTTONUP: case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:	case WM_MBUTTONUP: case WM_MBUTTONDBLCLK:
	case WM_MOUSEMOVE:
		return mouse(event.msg,
			WPPoint(LOWORD(event.lp), HIWORD(event.lp)), event.wp);

	case WM_MOVE:
		return moved(LOWORD(event.lp), HIWORD(event.lp));
	case WM_SIZE:
	    {
		WPRect box = this;
		box.extent(LOWORD(event.lp), HIWORD(event.lp));
		return sized(box, event.wp);
	    }
	case WM_COMMAND:
		return command(LOWORD(event.wp), HIWORD(event.wp));
	case WM_SYSCOMMAND:
		return command(LOWORD(event.wp), 0);

	case WM_INITMENU:
	    {
		WPMenu menu = (HMENU)event.wp;
		return menuInit(menu);
	    }
	case WM_MENUSELECT:
		return menuSelected(event.wp, LOWORD(event.lp));

	case WM_CLOSE:
		return closed();
	case WM_TIMER:
		return timer(event.wp);
	}
	return other(event);
}

int WPWin::numChildren()
{
	int n = 0;
	forEachChildWin(this, c)
		n++;
	return n;
}

//////////////////
// Move iterator to first child window.
// 
WPWin * WPChildWinList::first()
{
	HWND hwnd = GetWindow((*pwin)(), GW_CHILD);
	cwin = WPWin::GetWin(hwnd);
	return cwin ? cwin : nextWPWin(hwnd); 
}

//////////////////
// Get next Windows++ sibling window.
// (Skip windows w/no WPWin object.)
// 
WPWin * WPChildWinList::nextWPWin(HWND hwnd)
{
	while (hwnd) {
		hwnd = GetWindow(hwnd, GW_HWNDNEXT);
		if ((cwin = WPWin::GetWin(hwnd))!=NULL)
			return cwin;
	}
	return NULL;
}

void WPWin::clientToScreen(WPRect *rc)
{
	POINT o = rc->origin();
	POINT e = rc->endpt();
	clientToScreen(&o);
	clientToScreen(&e);
	rc->origin(o);
	rc->endpt(e);
}

void WPWin::screenToClient(WPRect *rc)
{
	POINT o = rc->origin();
	POINT e = rc->endpt();
	screenToClient(&o);
	screenToClient(&e);
	rc->origin(o);
	rc->endpt(e);
}

void WPWin::notifyParent(WORD msg)
{
	if (getParent()) 
		getParent()->sendMsg(WM_COMMAND, MAKELONG(getID(), msg), hwnd);
}

