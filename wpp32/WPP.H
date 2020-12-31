//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992, 1993 Paul DiLascia.
// FILE: WPP.H
//
// Main include file for Windows++ library.
// Contains all definitions for Windows++

#ifndef WPP_H
#define WPP_H

#define STRICT	// strict type-checking for windows.h

#ifdef RC_INVOKED
#include "windows.h"
#else

#if defined (_MSC_VER) 
#	if (_MSC_VER < 1000)
#		error "Requires MS C/C++ 10.0 or greater"
#	endif
#elif defined (__BORLANDC__)
#	if (__BORLANDC__ < 0x500)
#		error "Requires Borland C/C++ 5.0 or greater"
#	endif
#else
#	error "Unsupported compiler."
#endif

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <commdlg.h>
#endif

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPID.H
//
#define WPIDSB_VERT		-1	// "control ID" for vertical scroll bar
#define WPIDSB_HORZ		-2	// "control ID" for horizontal scroll bar

////////////////
// Base dialog ID: after IDOK, IDCANCEL, etc.
// Applications should use control IDs starting here, but less 
// than WPPIDBASE
// 
#define WPID_APPLICATION	10	

////////////////
// IDs for built-in commands and controls.
// 
#define WPPIDBASE				5000
#define WPIDM_EXIT			(WPPIDBASE + 0)
#define WPIDM_FILENEW		(WPPIDBASE + 1)
#define WPIDM_FILEOPEN		(WPPIDBASE + 2)
#define WPIDM_FILESAVE		(WPPIDBASE + 3)
#define WPIDM_FILESAVEAS	(WPPIDBASE + 4)
#define WPIDM_FILEPRINT		(WPPIDBASE + 5)
#define WPIDM_FILECLOSE		(WPPIDBASE + 6)
#define WPIDM_FILEPRINTSETUP (WPPIDBASE + 7)

#define WPIDM_EDITCUT		(WPPIDBASE + 10)
#define WPIDM_EDITCOPY		(WPPIDBASE + 11)
#define WPIDM_EDITPASTE		(WPPIDBASE + 12)
#define WPIDM_EDITDELETE	(WPPIDBASE + 13)
#define WPIDM_EDITUNDO		(WPPIDBASE + 14)
#define WPIDM_EDITSELALL	(WPPIDBASE + 15)

#define WPIDM_ABOUT			(WPPIDBASE + 20)
#define WPIDM_DEBUG			(WPPIDBASE + 21)
#define WPIDM_MEMSTATS		(WPPIDBASE + 22)

#define WPIDM_WINTILE		(WPPIDBASE + 30)
#define WPIDM_WINCASCADE	(WPPIDBASE + 31)
#define WPIDM_WINARRANGE	(WPPIDBASE + 32)
#define WPIDM_WINCLOSEALL	(WPPIDBASE + 33)
#define WPIDM_WINNEXT		(WPPIDBASE + 34)
#define WPIDM_WINPREV		(WPPIDBASE + 35)

// IDs for built-in dialog controls
#define WPIDED_STRING		(WPPIDBASE + 50)

//////////////////
// IDs for controls in COMMDLG.DLL.
// 
#define IDOFN_EDFILENAME	1152
#define IDOFN_LBFILENAME	1120
#define IDOFN_SSPATHNAME	1088
#define IDOFN_PBHELP			1038
#define IDOFN_CBREADONLY	1040

#ifdef RC_INVOKED
//////////////////
// Helpful RC file macros to define CUA-compliant commands.
//

// File Menu
#define	FileNew		"&New\tCtrl+N",		WPIDM_FILENEW
#define	FileOpen		"&Open...\tCtrl+O",	WPIDM_FILEOPEN
#define	FileSave		"&Save\tCtrl+S",		WPIDM_FILESAVE
#define	FileSaveAs	"Save &As...",			WPIDM_FILESAVEAS
#define	FilePrint	"&Print...\tCtrl+P", WPIDM_FILEPRINT
#define	FilePrintSetup "Print Setup...",	WPIDM_FILEPRINTSETUP
#define	FileClose	"&Close",				WPIDM_FILECLOSE
#define	FileExit		"E&xit",					WPIDM_EXIT 

// Edit menu
#define	EditUndo		"&Undo\tCtrl+Z",		WPIDM_EDITUNDO
#define	EditCut		"Cu&t\tCtrl+X",		WPIDM_EDITCUT
#define	EditCopy		"&Copy\tCtrl+C",		WPIDM_EDITCOPY
#define	EditPaste	"&Paste\tCtrl+V",		WPIDM_EDITPASTE
#define	EditDelete	"&Delete\tCtrl+DEL",	WPIDM_EDITDELETE
#define	EditSelAll	"Select &All\tCtrl+A",WPIDM_EDITSELALL

// Help menu
#define	HelpAbout	"&About...",	WPIDM_ABOUT

// Window
#define	WindowCascade	"&Cascade\tShift+F5",	WPIDM_WINCASCADE
#define	WindowTile		"&Tile\tShift+F4",		WPIDM_WINTILE
#define	WindowArrange	"Arrange &Icons",			WPIDM_WINARRANGE
#define	WindowCloseAll "Close &All",				WPIDM_WINCLOSEALL

// Accelerators
#define	AccFileNew		"^N",   WPIDM_FILENEW
#define	AccFileOpen		"^O",   WPIDM_FILEOPEN
#define	AccFilePrint	"^P",   WPIDM_FILEPRINT
#define	AccFileSave		"^S",   WPIDM_FILESAVE

#define	AccEditUndo		"^Z", WPIDM_EDITUNDO
#define	AccEditCut		"^X", WPIDM_EDITCUT
#define	AccEditCopy		"^C", WPIDM_EDITCOPY
#define	AccEditPaste	"^V", WPIDM_EDITPASTE
#define	AccEditDelete	VK_DELETE, WPIDM_EDITDELETE, CONTROL, VIRTKEY
#define	AccEditSelAll	"^A", WPIDM_EDITSELALL

#define	AccWinCascade	VK_F5, WPIDM_WINCASCADE, SHIFT, VIRTKEY
#define	AccWinTile		VK_F4, WPIDM_WINTILE, SHIFT, VIRTKEY
#define	AccWinNext		VK_F6, WPIDM_WINNEXT, CONTROL, VIRTKEY
#define	AccWinPrev		VK_F6, WPIDM_WINPREV, CONTROL, SHIFT, VIRTKEY

#define	AccMemStats		"Z", WPIDM_MEMSTATS, SHIFT, CONTROL, VIRTKEY

#else // if not RC_INVOKED

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPPDEFS.H
//
// Basic Windows++ type definitions, constants, etc.

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <commdlg.h>


const MAXINT = 0x7fff;
const MAXFILENAMELEN = 128;
const MAXSTRLEN = 256;

//////////////////
// Roll our own assert macro for uniformity between compilers.
// 
#undef assert
#ifdef NODEBUG
#	define assert(ignore)	((void) 0)
#	define TRACE				((void) 0)
#else
#	define assert(x)	((void)((x) || (DoAssert(#x,__FILE__,__LINE__),1)))
#	define TRACE ::WPTrace
#endif

//////////////////
// Stuff to make DLL classes work
//
#if defined(WPPDLL)
#	define DLLFUNC __declspec( dllexport )
#	define DLLCLASS class __declspec ( dllexport )
#elif defined(USEDLL)
#	define DLLFUNC  __declspec ( dllimport )
#	define DLLCLASS class __declspec ( dllimport )
#else
#	define DLLFUNC
#	define DLLCLASS class
#endif

// Define min, max: should use templates, but they don't work well
// with 'const' declarations.
//
#define max(a,b)	(((a) > (b)) ? (a) : (b))
#define min(a,b)	(((a) < (b)) ? (a) : (b))

//////////////////
// Global non-class-member functions
// 
extern void	DLLFUNC DoAssert(LPCSTR msg, LPCSTR file, unsigned line);
extern int	DLLFUNC ErrBox(LPCSTR format, ...);
extern void DLLFUNC WPTrace(LPCSTR pszFormat, ...);

//////////////////
// Useful MsgBox and MsgBeep functions.
// 
inline int MsgBox(LPCSTR text, LPCSTR caption="", int type=MB_OK) 
{ return MessageBox(NULL, text, caption, type); }

inline void MsgBeep(WORD type=0) 
{ MessageBeep(type); }

//////////////////
// All the classes are declared below, without being defined.
// This is so we can make forward references to class types in
// function arguments, etc., (before the class is actually defined).
// 
DLLCLASS WPApp;
DLLCLASS WPWin;
DLLCLASS WPMainWin;
DLLCLASS WPMenu;
DLLCLASS WPDialog;
DLLCLASS WPDialogModal;
DLLCLASS WPDialogModeless;
DLLCLASS WPDlgFileOpen;
DLLCLASS WPDlgPrint;
DLLCLASS WPDlgPrintAbort;
DLLCLASS WPDlgString;
DLLCLASS WPControl;
DLLCLASS WPButton;
DLLCLASS WPListBox;
DLLCLASS WPDevInfo;
DLLCLASS WPDevContext;
DLLCLASS WPPrinter;
DLLCLASS WPPaintDC;
DLLCLASS WPODItemList;
DLLCLASS WPOwnerDrawItem;
DLLCLASS WPOwnerDrawDC;
DLLCLASS WPMDIFrame;
DLLCLASS WPMDIClient;
DLLCLASS WPMDIChild;
DLLCLASS WPRegion;
DLLCLASS WPPen;
DLLCLASS WPBrush;
DLLCLASS WPBitmap;
DLLCLASS	WPEvent;

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPPOINT.H
//
// Declarations for WPPoint structure, the Windows++ analog of POINT.

//////////////////
// Better POINT structure.
// 
DLLCLASS WPPoint : public POINT {
public:
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

DLLCLASS WPSize : public SIZE {
public:
	WPSize(int x=0, int y=0)	{ cx=x; cy=y; }
	WPSize(const SIZE& sz)		{ cx=sz.cx; cy=sz.cy; }

	BOOL operator==(const WPSize& sz)		{ return cx==sz.cx && cy==sz.cy; }
	BOOL operator!=(const WPSize& sz)		{ return !(*this==sz); }

	WPSize& operator++ ()						{ cx++; cy++; return *this; }
	WPSize& operator-- ()						{ cx--; cy--; return *this; }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPRECT.H
//
// Declarations for WPRect class.

//////
// Better Windows RECT
// 
DLLCLASS WPRect : public RECT {
public:
	WPRect()										{ left=right=top=bottom=0; }
	WPRect(POINT o, POINT e)				{ set(o, e); }
	WPRect(int l, int t, int r, int b)	{ set(l,t,r,b); }
	WPRect(const RECT& rect)				{ *this = rect; }
	WPRect(WPWin *win)						{ *this = win; }
	WPRect(LPCSTR text)						{ *this = text; }

	void normalize();

	void set(POINT o, POINT e)					{ origin(o); endpt(e); }
	void set(int l, int t, int r, int b)	{ origin(l,t); endpt(r,b); }

	int width()				{ return right-left; }
	int height()			{ return bottom-top; }
	int width(int w)		{ right = left+w;  return width(); }
	int height(int h)		{ bottom= top +h;  return height(); }

	void origin(int x, int y)		{ left=x; top=y; }
	void endpt(int x, int y)		{ right=x; bottom=y; }

	WPPoint origin()				{ return WPPoint(left,top); }
	WPPoint endpt()				{ return WPPoint(right,bottom); }
	WPPoint origin(POINT p)		{ origin(p.x, p.y); return origin(); }
	WPPoint endpt(POINT p)		{ endpt (p.x, p.y); return endpt(); }

	WPSize extent()				{ return WPSize(width(), height()); }
	void extent(int w, int h)	{ width(w); height(h); }
	void extent(WPSize sz)		{ width(sz.cx); height(sz.cy); }

	WPPoint topRight()			{ return WPPoint(right, top); }
	WPPoint bottomLeft()			{ return WPPoint(left, bottom); }

	void setEmpty()				{ set(0,0,0,0); }
	BOOL isEmpty()					{ return IsRectEmpty(this); }
	BOOL contains(POINT p)		{ return PtInRect(this, p); }
	void inflate(int w, int h)	{ InflateRect(this, w, h); }
	void capture(POINT p)
		{	p.x=min(max(p.x,left),right-1); 
			p.y=min(max(p.y,top), bottom-1); }

	WPPoint center()				
		{ return WPPoint((left+right)/2, (top+bottom)/2); }

	void adjustWinRect(DWORD style, BOOL menu, DWORD exstyle=0)
		{ AdjustWindowRectEx(this, style, menu, exstyle); }

	WPRect& operator= (WPWin *win);
	WPRect& operator= (LPCSTR text);
	WPRect& operator= (const RECT &rect)
		{ *((RECT*)this) = rect; return *this; }

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
	WPRect& operator+= (int n)	{ inflate(n,n);   return *this; }
	WPRect& operator-= (int n)	{ inflate(-n,-n); return *this; }

	WPRect& operator*= (const TEXTMETRIC &tm)
		{ origin(origin()*=tm); endpt(endpt()*=tm); return *this; }

	int operator&= (const RECT& rect2);
	int operator|= (const RECT& rect2);
};

//////////////////
// A square is a special kind of rectangle.
// 
DLLCLASS WPSquare : public WPRect {
public:
	WPSquare(WPPoint p, int radius) { set(p, radius); }
	void set(WPPoint p, int r)
		{ origin(p.x-r, p.y-r); endpt(p.x+r, p.y+r); }
};

//////////////////
// This subclass is identical to WPRect in all respects except that the
// constructor and assignment for a WPWin gets the entire window
// rectangle rather than just the client area.
// 
DLLCLASS WPWindowRect : public WPRect {
public:
	WPWindowRect(WPWin *win)		{ *this = win; }
	WPWindowRect& operator= (WPWin *win);
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPAPP.H
//
// Definitions for the application class, WPApp.

//////////////////
// Class used to represent a Windows module.  
// Essentially, it's just a module instance handle.
// 
DLLCLASS WPModule {
protected:
	char modname[16];			// module name
	HINSTANCE hinst;			// module handle

public:
	WPModule(HINSTANCE h=NULL)	
		{ hinst = h; modname[0]=0; }
	WPModule(LPCSTR nm)
		{ strcpy(modname, nm); hinst = GetModuleHandle(modname); }
	~WPModule() { }

	HINSTANCE getHinst()				{ return hinst; }
	HINSTANCE operator()()			{ return hinst; }

 	LPCSTR getName();
	int getFileName(char *buf, int buflen)
		{ return GetModuleFileName(hinst, buf, buflen); }
	
	FARPROC getProcAddress(LPCSTR procname)
		{ return GetProcAddress(hinst, procname); }

	HMENU loadMenu(LPCSTR name)			
		{ return LoadMenu(hinst, name); }
	HBITMAP loadBitmap(LPCSTR name)		
		{ return LoadBitmap(hinst, name); }
	HBITMAP loadBitmap(int id)			
		{ return LoadBitmap(hinst, MAKEINTRESOURCE(id)); }
	HICON loadIcon(LPCSTR name)		
		{ return LoadIcon(HIWORD(name) ? hinst : NULL, name); }
	HICON loadIcon(int id)		
		{ return LoadIcon(hinst, MAKEINTRESOURCE(id)); }
	HCURSOR loadCursor(LPCSTR name)
		{ return LoadCursor(HIWORD(name) ? hinst : NULL, name); }
	HCURSOR loadCursor(int id)		
		{ return LoadCursor(hinst, MAKEINTRESOURCE(id)); }
	int loadString(int id, LPSTR buf, int len=MAXSTRLEN)
		{ return LoadString(hinst, id, buf, len); }

	HRSRC findResource(LPCSTR name, LPCSTR type)
		{ return FindResource(hinst, name, type); }
	int loadResource(LPCSTR name, LPCSTR type, LPSTR buf, int len);
	int loadResource(int id, LPCSTR type, LPSTR buf, int len)
		{ return loadResource(MAKEINTRESOURCE(id), type, buf, len); }
};

//////////////////
// Used to represent a library module (e.g., a DLL).
// 
DLLCLASS WPLibrary : public WPModule {
public:
	WPLibrary(LPCSTR libname);
	~WPLibrary()	{ if (hinst) FreeLibrary(hinst); }
};

//////////////////
// Application object. 
// There is exactly one application for each Windows++ program.  
// It stores the module instance handle.
// Each app must derive from WPApp and provide a "main" function.  
// The application object also manages the application's memory.
// 
DLLCLASS WPApp : public WPModule {
protected:
	static WPApp* pTheApp;	// ptr to one-and-only app
	LPCSTR cmdLine;			// windows command line
	HINSTANCE pinst;			// previous instance handle
	int cmdShow;				// how to show window
	int exitCode;				// returned from WinMain
	WPMainWin *mainWin;		// main application window
	WNDPROC wndProc;			// ptr to app's window procedure
	DLGPROC dlgProc;			// ptr to app's dialog procedure

	HWND mdiClientHwnd;		// MDI client win, if any
	WPDialogModeless *dialogs; // list of modeless dialogs
	HACCEL accel;				// accelerator table, if any
	BOOL useWININI;			// use WIN.INI for profile

	virtual void init(HINSTANCE h, HINSTANCE p, LPCSTR cmd, int show);
	virtual void main()=0;
	virtual void run();

	void makeIniFileName(char *buf);

	friend int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
	friend WPMDIClient;
public:
	char scratch[1024];			// transient buffer anyone can use

	WPApp();
	~WPApp();

	static WPApp* getApp()		{ return pTheApp; }

	// Access
	void getCmdLine(char *buf)	{ strcpy(buf, cmdLine); }
	HINSTANCE getPrevInst()		{ return pinst; }
	BOOL first()					{ return pinst==NULL; }
	WNDPROC getWndProc()			{ return wndProc; }
	DLGPROC getDlgProc()			{ return dlgProc; }

	// Miscellaneous
	void quit(int ret=0)			{ PostQuitMessage(ret); }
	void addDialog(WPDialogModeless *dlg);
	void removeDialog(WPDialogModeless *dlg);
	HACCEL loadAccel(LPCSTR acname)
		{ return accel = LoadAccelerators(hinst, acname); }

	// Application profile file
	int  getProfile(LPCSTR key,char *buf,int len,LPCSTR dflt="",LPCSTR app=NULL);
	int  getProfile(LPCSTR key, int dflt=0, LPCSTR app=NULL);
	BOOL setProfile(LPCSTR key, LPCSTR val, LPCSTR app=NULL);
	BOOL setProfile(LPCSTR key, int val,  LPCSTR app=NULL);
};

#define theApp (WPApp::getApp())

#ifndef WPPDLL

////////////////
// Here's a declaration for an app class you can use--just instantiate
// and implement MyApp::main
//
class MyApp : public WPApp {
	virtual void main();
};

#endif

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPWIN.H
//
// Defnitions for WPWin, THE base window class 
// from which all window classes are derived.

//////////////////
// Event object, used to pass msg, wParam, and lParam
// 
DLLCLASS WPEvent : public MSG {
public:
	UINT    msg;	// the message
	WPARAM  wp;		// word parameter
	LPARAM  lp;		// long parameter
	LRESULT ret;   // return code

	WPEvent(UINT m, WPARAM w=0, LPARAM l=0) { msg=m; wp=w; lp=l; ret=0; }
	~WPEvent() { }

	WPPoint screenPos()	{ return GetMessagePos(); }
	DWORD time()			{ return GetMessageTime(); }
};

//////////////////
// This structure is used to specify the Windows registration
// and creation arguments before creating an actual window.
// 
DLLCLASS WINCREATEARGS {
public:
	WNDCLASS wndcls;		// Windows class registration struct
	LPCSTR title;				// window's title
	DWORD style;			// style (WS_OVERLAPPED, etc.)
	DWORD exstyle;			// extended style (Windows 3.0)
	WPRect pos;				// window position (x,y,w,h)
	HMENU hmenu;			// menu handle
	WPWin* parent;			// parent window
	LPSTR lparam;			// create parm
	int id()					{ return (int)hmenu; }
};

BOOL		DLLFUNC CALLBACK WPDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT	DLLFUNC CALLBACK WPWndProc(HWND, UINT, WPARAM, LPARAM);

//////////////////
// This is THE base window class, from which all window classes
// are derived.  It provides methods corresponding to most Windows
// functions that take a window handle (HWND).
// 
DLLCLASS WPWin {
protected:
	static WPWin* NewWin;	// window being created
	WNDPROC oldProc;			// original window proc
	HWND hwnd;					// window handle
	BOOL deletable;			// window can be deleted

	void linkHwnd(HWND newhwnd);
	void unLinkHwnd();

	// Message procedure stuff
	LONG dfltMsgProc(WPEvent& e)
		{ return CallWindowProc(oldProc, hwnd, e.msg, e.wp, e.lp); }
	virtual LONG msgProc(WPEvent& event);
	BOOL dispatchEvent(WPEvent& event);

	friend BOOL		CALLBACK WPDlgProc(HWND, UINT, WPARAM, LPARAM);
	friend LRESULT	CALLBACK WPWndProc(HWND, UINT, WPARAM, LPARAM);
	friend WPDialog;
	friend WPControl;
	friend WPMDIChild;
	friend WPMDIFrame;

public:
	WPWin(LPCSTR classnm, WPWin* pwin=NULL, int id=0);
	virtual ~WPWin();

	// Class-wide globals
	static WINCREATEARGS createArgs;	// window creation args
	static TEXTMETRIC tm;				// text metrics for last created window

	// Overloaded new & delete
	void *operator new(size_t size);
	void operator delete(void *ptr);

	// Get handles/win ptr
	HWND getHwnd()							{ return hwnd; }
	HWND operator()()						{ return hwnd; }
	static HWND GetHwnd(WPWin* win)	{ return win ? win->hwnd : NULL; }
	static WPWin* GetWin(HWND hwnd);

	// Create/destroy
	BOOL createWin(LPCSTR title)
		{ createArgs.title = title; return createWin(); }
	virtual BOOL createWin();
	virtual void destroyWin()			{ DestroyWindow(hwnd); }

	// Static (global) functions
	static WPWin* GetActiveWin()	{ return GetWin(GetActiveWindow()); }
	static WPWin* GetFocusWin()	{ return GetWin(GetFocus()); }
	static WPWin* FindWin(LPCSTR clsnm, LPCSTR winnm)
		{ return GetWin(FindWindow(clsnm, winnm)); }
	static WPWin* WinFromPoint(WPPoint p)	
		{ return GetWin(WindowFromPoint(p)); }

	// Various flavors of SendMessage
	DWORD sendMsg(WPEvent& e)
		{ return SendMessage(hwnd, e.msg, e.wp, e.lp); }
	DWORD sendMsg(UINT msg, WPARAM wp=0, LPARAM lp=0) 
		{ return SendMessage(hwnd, msg, wp, lp); }
	DWORD sendMsg(UINT msg, WPARAM wp, void* lp) 
		{ return SendMessage(hwnd, msg, wp, (LPARAM)lp); }
	DWORD sendMsg(UINT msg, WPARAM wp, LPCSTR str) 
		{ return SendMessage(hwnd, msg, wp, (LPARAM)str); }

	// Properties
	HANDLE getProp(LPCSTR kwd)				{ return GetProp(hwnd, kwd); }
	void setProp(LPCSTR kwd, HANDLE val)	{ SetProp(hwnd, kwd, val); }
	void removeProp(LPCSTR kwd)				{ RemoveProp(hwnd, kwd); }

	// Parent/child stuff
	int getID()						{ return GetWindowLong(hwnd, GWL_ID); }
	WPWin* getParent()			{ return GetWin(GetParent(hwnd)); }
	void setParent(WPWin* pwin){ SetParent(hwnd, pwin->hwnd); }
	BOOL childExists(int id)	{ return GetDlgItem(hwnd, id)!=NULL; }
	int numChildren();
	WPWin* getTopChild()			{ return GetWin(GetTopWindow(hwnd)); }
	WPWin* getChild(int id)		{ return GetWin(GetDlgItem(hwnd, id)); }
	WPWin* childFromPoint(WPPoint p)
		{ return GetWin(ChildWindowFromPoint(hwnd, p)); }
	void notifyParent(WORD msg);

	// Rectangles
	void getClientRect(WPRect& rect)		{ GetClientRect(hwnd, &rect); }
	void getWindowRect(WPRect& rect)		{ GetWindowRect(hwnd, &rect); }
	BOOL getUpdateRect(WPRect& rect, BOOL erase=FALSE)
		{ return GetUpdateRect(hwnd, &rect, erase); }

	// Validate/invalidate
	void validate()	
		{ ValidateRect(hwnd, NULL); }
	void validate(WPRect& rect)	
		{ rect.normalize(); ValidateRect(hwnd, &rect); }

	void invalidate(BOOL erase=FALSE)
		{ InvalidateRect(hwnd, NULL, erase); }
	void invalidate(WPRect& rect, BOOL erase=FALSE)
		{ rect.normalize(); InvalidateRect(hwnd, &rect, erase); }

	// Position/size
	void setPos(int x, int y)
		{ SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE|SWP_NOZORDER); }
	void setSize(int w, int h)
		{ SetWindowPos(hwnd, NULL, 0, 0, w, h, SWP_NOMOVE|SWP_NOZORDER); }
	void moveWin(WPRect& box, BOOL repaint=TRUE)
		{ MoveWindow(hwnd,
			box.left, box.top, box.width(), box.height(), repaint); }

	// Z-order
	void setAfter(WPWin* after)
		{ SetWindowPos(hwnd, GetHwnd(after),0,0,0,0,SWP_NOSIZE|SWP_NOMOVE); }
	void bringToTop()		{ BringWindowToTop(hwnd); }
	void bringToBottom()
		{ SetWindowPos(hwnd,(HWND)1,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE); }

	// Timer
	int setTimer(int id, int msec, TIMERPROC func=NULL)
		{ return SetTimer(hwnd, id, msec, func); }
	BOOL killTimer(int id)
		{ return	KillTimer(hwnd, id); }	

	int msgBox(LPCSTR text, LPCSTR caption="", UINT style=MB_OK)
		{ return MessageBox(hwnd, text, caption, style); }
	int warning(LPCSTR text, UINT style=MB_OK)
		{ return msgBox(text, "Warning!", style|MB_ICONQUESTION); }
	int errBox(LPCSTR text, LPCSTR caption=NULL, 
		UINT style=MB_OK|MB_ICONEXCLAMATION)
		{ return MessageBox(hwnd, text, caption, style); }

	// Coordinates
	void clientToScreen(POINT* p)		{ ClientToScreen(hwnd, p); }
	void screenToClient(POINT* p)		{ ScreenToClient(hwnd, p); }
	void clientToScreen(WPRect *rc);
	void screenToClient(WPRect *rc);

	void scrollWin(int x,int y)
		{ ScrollWindow(hwnd, x, y, NULL, NULL); }
	void scrollWin(int x,int y, WPRect* scrollRect=NULL, WPRect* clipRect=NULL)
		{ ScrollWindow(hwnd, x, y, scrollRect, clipRect); }

	// Miscellaneous
	void setFocus()						{ SetFocus(hwnd); }
	void setReDraw(BOOL val)			{ sendMsg(WM_SETREDRAW,val); }
	void update()							{ UpdateWindow(hwnd); }
	BOOL show(int how=SW_SHOW)			{ return ShowWindow(hwnd, how); }
	BOOL hide()								{ return ShowWindow(hwnd, SW_HIDE); }
	void showOwnedPopups(BOOL show)	{ ShowOwnedPopups(hwnd, show); }

	void setText(LPCSTR text)	{ SetWindowText(hwnd, text); }
	int getText()					{ return GetWindowTextLength(hwnd); }
	int getText(LPSTR buf, int buflen)
		{ return GetWindowText(hwnd, buf, buflen); }

	void close()				{ sendMsg(WM_CLOSE); }
	void minimize()			{ CloseWindow(hwnd); }
	void maximize()			{ ShowWindow(hwnd, SW_SHOWMAXIMIZED); }
	BOOL isMinimized()		{ return IsIconic(hwnd); }
	BOOL isMaximized()		{ return IsZoomed(hwnd); }
	BOOL openIcon()			{ return OpenIcon(hwnd); }
	BOOL isIconic()			{ return IsIconic(hwnd); }
	BOOL enableWin(BOOL b)	{ return EnableWindow(hwnd, b); }
	BOOL isEnabled()			{ return IsWindowEnabled(hwnd); }
	BOOL isVisible()			{ return IsWindowVisible(hwnd); }
	BOOL isZoomed()			{ return IsZoomed(hwnd); }
	BOOL flash(BOOL invert=TRUE)
		{ return FlashWindow(hwnd, invert); }
	int getClassName(LPSTR buf, int buflen)
		{ return GetClassName(hwnd, buf, buflen); }

	LONG style()				{ return GetWindowLong(hwnd, GWL_STYLE); }
	LONG style(LONG style)	{ return SetWindowLong(hwnd, GWL_STYLE, style);}

	void setMenu(HMENU hmenu)	{ SetMenu(hwnd, hmenu); }
	void drawMenu()				{ DrawMenuBar(hwnd); }

	// Add owner-draw item
	virtual void addODItem(WPOwnerDrawItem* od)	{ assert(FALSE); }

	// Virtual message functions corresponding to WM_ messages.
 	virtual BOOL activated(WORD state, BOOL iconic) { return FALSE; }
	virtual BOOL closed()								{ return FALSE; }
	virtual BOOL command(int id, WORD msg)			{ return FALSE; }
	virtual BOOL enabled(BOOL state)					{ return FALSE; }
	virtual BOOL getMinMaxInfo(LPMINMAXINFO mmi) { return FALSE; }
	virtual BOOL gotFocus(WPWin *prev)				{ return FALSE; }
	virtual BOOL kbd(WPEvent& event)					{ return FALSE; }
	virtual BOOL killedFocus(WPWin *next)			{ return FALSE; }
	virtual BOOL menuInit(WPMenu &menu)				{ return FALSE; }
	virtual BOOL menuSelected(int id, WORD flags){ return FALSE; }
	virtual BOOL mouse(int msg, WPPoint p, WORD flags)	
		{ return FALSE; }
	virtual BOOL moved(int x, int y)					{ return FALSE; }
	virtual BOOL paint()									{ return FALSE; }
	virtual BOOL queryEnd()								{ return TRUE; }
	virtual BOOL queryMaximize()						{ return TRUE; }
	virtual BOOL scrolled(int msg, int id, int thumbPos) { return FALSE; }
	virtual BOOL sized(WPRect &box, WORD how)		{ return FALSE; }
	virtual BOOL timer(int id)							{ return FALSE; }
	virtual BOOL other(WPEvent &event)				{ return FALSE; }
};

//////////////////
// Class used to navigate the child windows of a window.
// 
DLLCLASS WPChildWinList {
protected:
	WPWin *pwin;	// parent window;
	WPWin *cwin;	// current child
	WPWin *nextWPWin(HWND hwnd);
public:
	WPChildWinList(WPWin *p)	{ pwin=p; cwin=NULL; }

	WPWin * first();
	WPWin * next()
		{ return cwin = nextWPWin(WPWin::GetHwnd(cwin)); }
};

//////////////////
// Clever little macro lets you write:
// 
//		forEachChildWin(parent, child)
//			child->doSomething();
// 
#define forEachChildWin(pwin, cwin) \
	WPChildWinList _children = pwin; \
	for (WPWin *cwin=_children.first(); cwin; cwin=_children.next()) 


////////////////
// This class handles deferred window positioning.
// 
DLLCLASS WPDeferWinPos {
	HDWP posInfo;
public:
	WPDeferWinPos(int nWins)	{ posInfo = BeginDeferWindowPos(nWins); }
	~WPDeferWinPos()				{ EndDeferWindowPos(posInfo); }

	void move(WPWin* win, WPRect& pos, 
		WORD flags=SWP_NOREDRAW|SWP_NOZORDER, WPWin* after=NULL)
		{ posInfo = DeferWindowPos(posInfo, (*win)(), 
				WPWin::GetHwnd(after),
				pos.left, pos.top, pos.width(), pos.height(), flags); }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPGLOB.H
//
// Windows++ global object definitions.
// Each global object is declared here and instantiated in WINMAIN.CPP.

//////////////////
// Global mouse object.  There's only one: Mouse.
// Use this object to get/set mouse parameters, capture the mouse, etc.
// 
DLLCLASS WPMouse {
public:
	WPWin* capture()							
		{ return WPWin::GetWin(GetCapture()); }
	WPWin* capture(WPWin *win)				
		{ return WPWin::GetWin(SetCapture((*win)())); }

	void release()								{ ReleaseCapture(); }
	WORD getDoubleClickTime()				{ return GetDoubleClickTime(); }
	void setDoubleClickTime(WORD msec)	{ SetDoubleClickTime(msec); }
	BOOL swapButtons(BOOL swap)			{ return SwapMouseButton(swap); }
	BOOL swapButtons()			{ return GetSystemMetrics(SM_SWAPBUTTON); }
	BOOL present()					{ return GetSystemMetrics(SM_MOUSEPRESENT); }
};
extern WPMouse Mouse;

//////////////////
// Global Keyboard object, used to get info about the keyboard.
// 
DLLCLASS WPKeyboard {
public:
	int codePage()						{ return GetKBCodePage(); }
	int type()							{ return GetKeyboardType(0); }
	int subType()						{ return GetKeyboardType(1); }
	int numFnKeys()					{ return GetKeyboardType(2); }
	int keyName(LONG lparam, char *buf, int buflen)
		{ return GetKeyNameText(lparam, buf, buflen); }
	int state(int vkey)				{ return GetKeyState(vkey); }
	void getState(BYTE* buf)		{ GetKeyboardState(buf); }
	void setState(BYTE* buf)		{ SetKeyboardState(buf); }
	BOOL isArrowKey(int key);
};
extern WPKeyboard Keyboard;

/////////////////
// Global Cursor.  Use it to move, hide, show, etc. the cursor.
// 
DLLCLASS WPCursor {
public:
	HCURSOR operator= (HCURSOR hc)	{ return SetCursor(hc); }
	HCURSOR operator= (LPCSTR name)	{ return *this=theApp->loadCursor(name); }
	HCURSOR operator= (int id)			{ return *this=theApp->loadCursor(id); }

	void setPos(int x, int y)			{ SetCursorPos(x, y); }
	void getPos(WPPoint& p)				{ GetCursorPos(&p); }

	WPPoint operator()()					{ WPPoint p; getPos(p); return p; }
	WPPoint operator= (WPPoint p)		{ SetCursorPos(p.x, p.y); return p; }

	void clip(WPWin *win);
	void clip(WPRect &rect)				{ ClipCursor(&rect); }
	void unClip()							{ ClipCursor(NULL); }
	void show(BOOL val)					{ ShowCursor(val); }

	void operator++()		{ show(TRUE); }
	void operator--()		{ show(FALSE); }
};
extern WPCursor Cursor;

//////////////////
// This class encapsulates the wait (hourglass) cursor.
// 
DLLCLASS WPWaitCursor {
	HCURSOR save;
public:
	WPWaitCursor(WPWin *win)
		{ Mouse.capture(win); save = Cursor = IDC_WAIT; }
	~WPWaitCursor()
		{ Cursor = save; Mouse.release(); }
};

//////////////////
// Global Caret resource, similar to cursor.
// 
DLLCLASS WPCaret {
public:
	void create(WPWin *win, WPBitmap& bm);
	void create(WPWin *win, int w, int h, BOOL gray=FALSE) 
		{ CreateCaret((*win)(), (HBITMAP)(gray==TRUE), w, h); }

	void hide(WPWin *win)				{ HideCaret((*win)()); }
	void show(WPWin *win)				{ ShowCaret((*win)()); }
	void getPos(WPPoint& p)				{ GetCaretPos(&p); }
	void setPos(int x, int y)			{ SetCaretPos(x, y); }
	void setBlinkTime(WORD msec)		{ SetCaretBlinkTime(msec); }
	WORD getBlinkTime()					{ return GetCaretBlinkTime(); }
	void destroy()							{ DestroyCaret(); }

	WPPoint operator()()					{ WPPoint p; getPos(p); return p; }
	WPPoint operator= (WPPoint p)		{ SetCaretPos(p.x, p.y); return p; }
};
extern WPCaret Caret;

//////////////////
// This global object represents the WIN.INI file.  
// Use it to read/write from WIN.INI.
// 
DLLCLASS WPWinIni {
public:
	int get(LPCSTR app, LPCSTR key, char *buf, int buflen, LPCSTR dflt="")
		{ return GetProfileString(app, key ? key : NULL, dflt, buf, buflen); }

	int get(LPCSTR app, LPCSTR key, int dflt=0)
		{ return GetProfileInt(app, key, dflt); }

	int getPrinterName(char* buf, int len);

	BOOL set(LPCSTR app, LPCSTR key, LPCSTR val)
		{ return WriteProfileString(app, key, val); }
	BOOL set(LPCSTR app, LPCSTR key, int val)
		{ char buf[16];
		  itoa(val, buf, 10);
		  return WriteProfileString(app, key, buf); }

	int getKeys(LPCSTR app, char *buf, int buflen)
		{ return GetProfileString(app, NULL, "", buf, buflen); }

};
extern WPWinIni WinIni;

//////////////////
// Clipboard. More of the same.
// 
DLLCLASS WPClipboard {
public:	
	BOOL open(WPWin *win)		{ return OpenClipboard((*win)()); }
	BOOL close()					{ return CloseClipboard(); }
	BOOL available(WORD fmt)	{ return IsClipboardFormatAvailable(fmt); }
	int getData(WORD fmt, LPSTR buf, int buflen);
	int setData(WORD fmt, LPSTR buf, int buflen);
	BOOL empty()					{ return EmptyClipboard(); }
	int numFormats()				{ return CountClipboardFormats(); }

	int formatName(WORD fmt, char *buf, int buflen)
		{ return GetClipboardFormatName(fmt, buf, buflen); }
	int getPriorityFormat(UINT *priorityList, int len)
		{ return GetPriorityClipboardFormat(priorityList, len); }
	WORD registerFormat(LPCSTR name)
		{ return RegisterClipboardFormat(name); }
};
extern WPClipboard Clipboard;

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPODRAW.H
//
// Definitions for owner-draw items.

/////////////////
// Generic header for all windows XXXXITEMSTRUCT's
// 
struct ODITEMSTRUCT {
	UINT type;		// item type (ODT_BUTTON, etc.)
	UINT id;			// (control id)
};
typedef ODITEMSTRUCT* LPODITEMSTRUCT;

typedef void* ODDATA;					 // any pointer for draw item

//////////////////
// Generic owner draw item used for list box, button, etc.
// 
DLLCLASS WPOwnerDrawItem {
	WPOwnerDrawItem *next;
	UINT type;
	friend class WPODItemList;
public:
	WPOwnerDrawItem(WPWin *win, UINT t);

	UINT getType() { return type; }
	virtual UINT getID() = 0;

	virtual void paint(WPOwnerDrawDC &dc, ODDATA data) = 0;
	virtual WPPoint measure(ODDATA data) { return WPPoint(0,0); };
	virtual int compare(ODDATA data1, ODDATA data2) { return 0; };
	virtual void delItem(ODDATA data) { };
};

//////////////////
// Object to hold a list of owner draw items.
// 
DLLCLASS WPODItemList {
protected:
	WPOwnerDrawItem *first;
	WPOwnerDrawItem* getItem(LPODITEMSTRUCT &item);
public:
	WPODItemList() { first = NULL; }
	void add(WPOwnerDrawItem *od) { od->next = first; first = od; }
	BOOL dispatchEvent(WPEvent& event);
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPMAIN.H
//
// Definitions for WPMainWin, which represents a main window.

const MAXPROMPTLEN = 80;

//////////////////
// Main application window. Each application has one.
// 
DLLCLASS WPMainWin : public WPWin {
protected:
	char filename[MAXFILENAMELEN];
	WPODItemList odItems;	// owner-draw items, if any
	int keyRepeat;				// key repeat for cursor movement
	BOOL noAppQuit;			// don't call app quit (for MDI);

	LPCSTR caption;			// window caption prefix
	LPCSTR fnFilter;			// file name filter
	BOOL modified;				// whether file modified
	BOOL fileKillConfirm();	// do file confirmation
	friend WPMDIChild;

protected:
	WPWin *promptWin;			// menu prompt window
	
public:
	WPMainWin(LPCSTR clsnm = "MAINWIN");
	~WPMainWin();

	// Inline functions to access data members
	void fileNameFilter(LPCSTR filt)	{ fnFilter = filt; }
	LPCSTR fileNameFilter()				{ return fnFilter; }
	void fileCaption(LPCSTR cap)			{ caption = cap; }
	void fileInit(LPCSTR fname, LPCSTR cap=NULL);

	// Miscellaneous
	BOOL other(WPEvent &event);
	void addODItem(WPOwnerDrawItem* od)		{ odItems.add(od); }
	virtual BOOL doIdle()						{ return FALSE; }
	virtual int getMenuPrompt(char* buf, int id, WORD flags) 
		{ return 0; }

	// Virtual message functions for main window.
	BOOL command(int id, WORD msg);
	BOOL menuInit(WPMenu &menu);
	BOOL menuSelected(int id, WORD flags);
	BOOL kbd(WPEvent& event);
	BOOL activated(WORD state, BOOL minimized);
	BOOL closed();
	BOOL queryEnd()	{	return fileKillConfirm(); }
	BOOL paint();
	virtual void paint(WPPaintDC& dc) { }

	// Virtual functions to perform File commands.
	virtual void fileName(LPCSTR fn);
	virtual LPCSTR fileName()					{ return filename; }
	virtual BOOL fileIsModified()			{ return modified; }
	virtual void fileIsModified(BOOL m)	{ modified=m; }
	virtual BOOL fileNew()					{ return FALSE; }
	virtual BOOL fileOpen(LPCSTR fname)	{ return FALSE; }
	virtual BOOL fileSave(LPCSTR fname)	{ return FALSE; }
	virtual BOOL filePrint(WPDlgPrint &pdlg)		{ return FALSE; }
	virtual BOOL filePrintDlg(WPDlgPrint &pdlg)	{ return TRUE; }

	// Virtual functions to perform Edit commands.
	virtual BOOL editCut()					{ return FALSE; }
	virtual BOOL editCopy()					{ return FALSE; }
	virtual BOOL editPaste()				{ return FALSE; }
	virtual BOOL editDelete()				{ return FALSE; }
	virtual BOOL editUndo()					{ return FALSE; }
	virtual BOOL anySelected()				{ return FALSE; }
	virtual BOOL canUndo()					{ return FALSE; }
	virtual BOOL canPaste()					{ return FALSE; }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPCTRL.H
//
// Control class definitions.

//////////////////
// Generic control, an abstract class. 
// Specifc controls are all derived from this class.
// 
DLLCLASS WPControl : public WPWin {
protected:
	void linkObject(void *obj, int siz) { object=obj; objsiz=siz; }
	BOOL tryLink();
	friend WPDialog;

	void *object;				// pointer to unknown object
	int objsiz;					// size of object
	WPControl(LPCSTR  classnm, WPWin *pwin, int id, long style=0);
public:
	// virtual functions defined by each specific control
	virtual void updateObject() = 0;
	virtual void updateScreen() = 0;
	BOOL createWin() 
		{ return tryLink() ? TRUE : WPWin::createWin(); }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPLIST.H
//
// List box definitions.

//////////////////
// Generic list data.
// 
DLLCLASS WPListData {
public:
	virtual BOOL firstItem() = 0;
	virtual BOOL nextItem() = 0;
	virtual DWORD getItemText(char *buf, int len)=0;
};

#define LBS_DEFAULT	 (WS_BORDER | LBS_NOTIFY | LBS_USETABSTOPS | WS_VSCROLL)
#define LBS_DEFAULTOD (LBS_DEFAULT | LBS_OWNERDRAWVARIABLE)

//////////////////
// List box.
// 
DLLCLASS WPListBox : public WPControl {
	WPListData *list;			// the list
public:
	WPListBox(WPWin *pwin, int id, long sty=LBS_DEFAULT) 
		: WPControl("ListBox", pwin, id, sty) { }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPListBox(pwin, id); }

	void setList(WPListData *l, int sel=0, BOOL redraw=TRUE);

	// General control functions
	void linkObject(int *pint)	{ object=pint; }
	void updateScreen()			{ if (object) setSel(*((int*)object)); }
	void updateObject()			{ if (object) *((int*)object) = getSel(); }

	// Miscellaneous list box functions
	int count()						{ return sendMsg(LB_GETCOUNT); }
	void reset()					{ sendMsg(LB_RESETCONTENT); }
	int setTop(int item)			{ return sendMsg(LB_SETTOPINDEX, item); }
	void delItem(int index)		{ sendMsg(LB_DELETESTRING, index); }
	int append(LPCSTR text)		{ return sendMsg(LB_ADDSTRING, 0, text); }
	int insert(LPCSTR text, int where)
		{ return sendMsg(LB_INSERTSTRING, where, text); }
	DWORD getItemData(int item)
		{ return sendMsg(LB_GETITEMDATA, item); }
	int setItemData(int item, DWORD data)
		{ return sendMsg(LB_SETITEMDATA, item, data); }

	// Get/set selection
	int getSel()					{ return sendMsg(LB_GETCURSEL); }
	void setSel(int sel)			{ sendMsg(LB_SETCURSEL, sel); }
	int setSel(LPCSTR text, int start=-1)
		{ return sendMsg(LB_SELECTSTRING, start, text); }
	int getSel(char *buf)
		{ return (int)sendMsg(LB_GETTEXT, getSel(), buf); }
	void setTabStops(int *tabs, int len)
		{ sendMsg(LB_SETTABSTOPS, len, tabs); }
};

//////////////////
// Owner-draw list box, multiply derived from list box and owner-draw item.
// 
DLLCLASS WPODListBox : public WPListBox, public WPOwnerDrawItem {
public:
	WPODListBox(WPWin* pwin, int id, long sty=LBS_DEFAULTOD) 
		: WPListBox(pwin, id, sty), WPOwnerDrawItem(pwin, ODT_LISTBOX) { }
	UINT getID() { return WPWin::getID(); }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPBUTN.H
//
// Button definitions.

//////////////////
// Button object.  Underlying data is BOOL.
// 
DLLCLASS WPButton : public WPControl {
public:
	WPButton(WPWin *pwin, int id, long sty=BS_PUSHBUTTON)
		: WPControl("Button", pwin, id, sty)	{ }

	static WPControl* New(WPWin* pwin, int id) 
		{ return new WPButton(pwin, id); }

	// General control functions
	void updateScreen()				{ if (object) setCheck(*((BOOL*)object)); }
	void updateObject()				{ if (object) *((BOOL*)object)=getCheck(); }
	void linkObject(BOOL *pbool)	{ object=pbool; }

	// "Brainless" Windows functions
	BOOL getCheck()				{ return sendMsg(BM_GETCHECK); }
	void setCheck(BOOL state)	{ sendMsg(BM_SETCHECK, state); }
};

//////////////////
// Radiobutton group.  Underlying data is integer (enum).
// 
DLLCLASS WPRBGroup : public WPControl {
public:
	WPRBGroup(WPWin *pwin, int id, long sty=BS_GROUPBOX) 
		: WPControl("Button", pwin, id, sty) { }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPRBGroup(pwin, id); }

	// General control functions
	void linkObject(int *pint, int nButtons)
		{ object=pint; objsiz = nButtons; }
	void updateScreen()			{ if (object) setSel(*((int*)object)); }
	void updateObject()			{ if (object) *((int*)object) = getSel(); }

	// Get/set selection
	int getSel();
	void setSel(int sel);
};

//////////////////
// Checkbox group.  Underlying data is array of BOOLs.
// 
DLLCLASS WPCBGroup : public WPControl {
public:
	WPCBGroup(WPWin *pwin, int id, long sty=BS_GROUPBOX) 
		: WPControl("Button", pwin, id, sty) { }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPCBGroup(pwin, id); }

	// General control functions
	void updateScreen()			{ if (object) setSel((BOOL*)object); }
	void updateObject()			{ if (object) getSel((BOOL*)object); }
	void linkObject(BOOL *array, int nButtons)	
		{ object=array; objsiz = nButtons; }

	// Get/set selection
	void setSel(BOOL *barray);
	void getSel(BOOL *barray);
	void setAll(BOOL val);
};

//////////////////
// Owner-draw button, multiply derived from button and owner-draw item.
// 
DLLCLASS WPODButton : public WPButton, public WPOwnerDrawItem {
public:
	WPODButton(WPWin* pwin, int id) : WPButton(pwin, id, BS_OWNERDRAW), 
		WPOwnerDrawItem(pwin, ODT_BUTTON) { }
	UINT getID() { return WPWin::getID(); }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPCOMBO.H
//
// Combo box definitions.

#define CBS_DEFAULT	 (WS_BORDER | CBS_AUTOHSCROLL | CBS_SIMPLE)
#define CBS_DEFAULTOD (CBS_DEFAULT | CBS_OWNERDRAWVARIABLE)

//////////////////
// Combo Box
// 
DLLCLASS WPComboBox : public WPControl {
	WPListData *list;			// the list
public:
	WPComboBox(WPWin *pwin, int id, long sty=CBS_DEFAULT) 
		: WPControl("ComboBox", pwin, id, sty) { list = NULL; }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPComboBox(pwin, id); }

	void setList(WPListData *l, int sel=0, BOOL redraw=TRUE);

	// General control functions
	void linkObject(char* buf, int len)		
		{ object=buf; objsiz=len; }
	void updateObject()	
		{ if (object) getText((char*)object, objsiz); }
	void updateScreen()	
		{ if (object) { setText((char*)object); setMaxLen(objsiz-1); } }

	// List Box functions
	int count()						{ return sendMsg(CB_GETCOUNT); }
	void reset()					{ sendMsg(CB_RESETCONTENT); }
	void delItem(int index)		{ sendMsg(CB_DELETESTRING, index); }
	int append(LPCSTR text)		{ return sendMsg(CB_ADDSTRING, 0, text); }
	int insert(LPCSTR text, int i)	
		{ return sendMsg(CB_INSERTSTRING, i, text); }
	DWORD getItemData(int item)
		{ return sendMsg(CB_GETITEMDATA, item); }
	int setItemData(int item, DWORD data)
		{ return sendMsg(CB_SETITEMDATA, item, data); }

	// Get/set selection
	int getSel()					{ return sendMsg(CB_GETCURSEL); }
	void setSel(int sel)			{ sendMsg(CB_SETCURSEL, sel); }
	int setSel(LPCSTR text, int start=-1)
		{ return sendMsg(CB_SELECTSTRING, start, text); }
	int getSel(char *buf)
		{ return (int)sendMsg(CB_GETLBTEXT, getSel(), buf); }

	// Edit control functions
	LONG getTextSel()	{ return sendMsg(CB_GETEDITSEL); }
	LONG getTextSel(int& beg, int& end)	
		{ LONG x = getTextSel(); beg=LOWORD(x); end=HIWORD(x); return x; }
	void setTextSel(int beg=0, int end=MAXINT)
		{ sendMsg(CB_SETEDITSEL, 0, MAKELONG(beg, end)); }
	BOOL setMaxLen(int len)
		{ return sendMsg(CB_LIMITTEXT, len); }

	// Combo Box
	void showDropDown(BOOL show)		{ sendMsg(CB_SHOWDROPDOWN, show); }
};

//////////////////
// Owner-draw combo box, multiply derived from combo box and owner-draw item.
// 
DLLCLASS WPODComboBox : public WPComboBox, public WPOwnerDrawItem {
public:
	WPODComboBox(WPWin* pwin, int id, long sty=CBS_DEFAULTOD) 
		: WPComboBox(pwin, id, sty), WPOwnerDrawItem(pwin, ODT_COMBOBOX) { }
	UINT getID() { return WPWin::getID(); }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPEDIT.H
//
// Edit control definitions.

#define ES_DEFAULT		(WS_BORDER | ES_LEFT | ES_AUTOHSCROLL)
#define ES_DEFAULTMULTI	(ES_DEFAULT | ES_MULTILINE | ES_AUTOVSCROLL)

//////////////////
// Your basic edit control.  Underlying data is string.
// 
DLLCLASS WPEdit : public WPControl {
	LPCSTR legalChars;			// user can only type these chars
public:
	WPEdit(WPWin *pwin, int id, long style=ES_DEFAULT)
		: WPControl("Edit", pwin, id, style) { legalChars=NULL; }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPEdit(pwin, id); }

	void setLegalChars(LPCSTR s)		{ legalChars=s; }

	// Virtual WPWin functions overridden for edit controls
	BOOL gotFocus(WPWin *prev);
	BOOL kbd(WPEvent& event);

	// General control functions
	void linkObject(char* buf, int len) 
		{ object=buf; objsiz=len; }
	void updateObject()			
		{ if (object) getText((char*)object, objsiz); }
	void updateScreen()		
		{ if (object) { setText((char*)object); setMaxLen(objsiz-1); } }

	// Windows-related functions
	BOOL canUndo()				{ return sendMsg(EM_CANUNDO); }
	BOOL undo()					{ return sendMsg(EM_UNDO); }
	void emptyUndo()			{ sendMsg(EM_EMPTYUNDOBUFFER); }
	BOOL isModified()			{ return sendMsg(EM_GETMODIFY); }
	void setModified(BOOL m){ sendMsg(EM_SETMODIFY, m); }
	void getRect(WPRect &r)	{ sendMsg(EM_GETRECT, 0, (LONG)&r); }
	
	// Set/get selection
	void setSel(int beg=0, int end=MAXINT)
		{ sendMsg(EM_SETSEL, beg, end); }
	void getSel(int& beg, int& end)	
		{ sendMsg(EM_GETSEL, (WPARAM)&beg, (LPARAM)&end); }

	// Miscellaneous
	void setPasswordChar(char c)	{ sendMsg(EM_SETPASSWORDCHAR, c); }
	void replaceSel(char *text)	{ sendMsg(EM_REPLACESEL, 0, text); }
	void setMaxLen(int len)			{ sendMsg(EM_LIMITTEXT, len); }

	// The following are used to simplify the Edit commands
	void cut()		{ sendMsg(WM_CUT); }
	void copy()		{ sendMsg(WM_COPY); }
	void clear()	{ sendMsg(WM_CLEAR); }
	void paste(BOOL flush=TRUE);
};

//////////////////
// Multi-line edit control is subclass of generic edit control.
// 
DLLCLASS WPMultiEdit : public WPEdit {
public:
	WPMultiEdit(WPWin *pwin, int id, long sty=ES_DEFAULTMULTI)
		: WPEdit(pwin, id, sty) { }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPMultiEdit(pwin, id); }

	// Virtual WPWin functions overridden for multi edit
	BOOL gotFocus(WPWin *prev)		{ return WPControl::gotFocus(prev); }

	// Windows functions for multi-edit controls only
	int numLines()						{ return sendMsg(EM_GETLINECOUNT); }
	int getLine(int nLine, char *buf, int len)
		{ *((WORD*)buf) = len; return sendMsg(EM_GETLINE, nLine, buf); }
	int lineFromChar(int pos)		{ return sendMsg(EM_LINEFROMCHAR, pos); }
	int linePos(int nLine)			{ return sendMsg(EM_LINEINDEX, nLine); }
	int lineLenFromPos(int pos)	{ return sendMsg(EM_LINELENGTH, pos); }
	int lineLen(int nLine)			{ return lineLenFromPos(linePos(nLine)); }
	void lineScroll(int h, int v)	{ sendMsg(EM_LINESCROLL, 0, MAKELONG(v,h)); }
	void setRect(WPRect &rect, BOOL repaint=TRUE)
		{ sendMsg(repaint ? EM_SETRECT : EM_SETRECTNP, 0, (LONG)&rect); }
	BOOL format(BOOL crlf)			{ return sendMsg(EM_FMTLINES, crlf); }
	void setTabStops(int *tabs, int len)
		{ sendMsg(EM_SETTABSTOPS, len, tabs); }

	// load/save operations
	BOOL load(LPCSTR fname);
	BOOL save(LPCSTR fname);
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPSBAR.H
//
// Scroll Bar definitions.

//////////////////
// Scroll bar, used for dialog controls.
// Underlying data is integer.
// 
DLLCLASS WPScrollBar : public WPControl {
protected:
	int sbtype;
	int pageIncr;
	int lineIncr;
	HWND getScrollHwnd()			{ return getHwnd(); }
public:
	WPScrollBar(WPWin *pwin, int id, long sty=0)
		: WPControl("ScrollBar", pwin, id, sty)
		{ sbtype = SB_CTL; lineIncr = pageIncr = 1; }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPScrollBar(pwin, id); }

	void pageSize(int n)			{ pageIncr = n; }
	int pageSize()					{ return pageIncr; }
	void lineSize(int n)			{ lineIncr = n; }
	int lineSize()					{ return lineIncr; }

	// General control functions
	void linkObject(int* pint)	{ object=pint; }
	void updateScreen()			{ if (object) scrollPos(*((int*)object),TRUE); }
	void updateObject()			{ if (object) *((int*)object) = scrollPos(); }

	// Windows-related scrollbar functions
	int scrollPos() 
		{ return GetScrollPos(getScrollHwnd(), sbtype); }
	int scrollPos(int pos, BOOL redraw=TRUE)
		{ return SetScrollPos(getScrollHwnd(), sbtype, pos, redraw); }
	void getScrollRange(int& min, int& max)
		{ GetScrollRange(getScrollHwnd(), sbtype, (LPINT)&min, (LPINT)&max); }
	void setScrollRange(int min, int max, BOOL redraw=TRUE)
		{ SetScrollRange(getScrollHwnd(), sbtype, min, max, redraw); }
	void showScrollBar(BOOL show)
		{ ShowScrollBar(getScrollHwnd(), sbtype, show); }

	void handleMsg(int msg, int thumbPos);
};

//////////////////
// Vertical scroll bar, used for windows with scroll bars.
// 
DLLCLASS WPVScrollBar : public WPScrollBar {
	HWND getScrollHwnd()		{ return GetHwnd(getParent()); }
public:
	WPVScrollBar(WPWin *pwin, int id) : WPScrollBar(pwin, id, SBS_VERT) 
		{ sbtype = SB_VERT; }
};

//////////////////
// Horizontal scroll bar, used for windows with scroll bars.
// 
DLLCLASS WPHScrollBar : public WPScrollBar {
	HWND getScrollHwnd()		{ return GetHwnd(getParent()); }
public:
	WPHScrollBar(WPWin *pwin, int id) : WPScrollBar(pwin, id, SBS_HORZ)
		{ sbtype = SB_HORZ; }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPSTATIC.H
//
// Static control definitions.

#define SS_DEFAULT		(SS_LEFT | SS_NOPREFIX)
#define SS_DEFAULTICON	(SS_ICON)

//////////////////
// Static control. Underlying data is string. A static has no
// updateObject operation, since the text can't be altered!
// 
DLLCLASS WPStatic : public WPControl {
public:
	WPStatic(WPWin *pwin, int id, long sty=SS_DEFAULT)
		: WPControl("Static", pwin, id, sty) { }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPStatic(pwin, id); }

	// General control functions
	void linkObject(char* buf)	{ object=buf; objsiz=strlen(buf); }
	void updateScreen()			{ if (object) setText((char*)object); }
	void updateObject()			{ /* static is read-only */ }
};

//////////////////
// Static icon. Like normal static control, but underlying data is HICON.
// 
DLLCLASS WPStaticIcon : public WPStatic {
public:
	WPStaticIcon(WPWin *pwin, int id, long sty=SS_DEFAULTICON) 
		: WPStatic(pwin, id, sty) { }

	static WPControl* New(WPWin* pwin, int id)
		{ return new WPStaticIcon(pwin, id); }

	// General control functions
	void linkObject(HICON hicon)	{ object = (void*)hicon; }
	void updateScreen();
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLG.H
//
// Dialog box defnitions.

typedef WPControl* pWPControl;
typedef pWPControl (*NEWCTLFN) (WPWin*, int);

//////////////////
// Structure used to map controls to underlying data.
// Used to build table-driven dialogs.
// 
struct WPControlMap {
	NEWCTLFN newfn;			// function to create instance of control
	int id;						// control ID
	int offset;					// offset of data
	int len;						// length of data
	friend WPDialog;
};

//////////////////
// Macros used to initialize static control maps
// 
#ifndef offsetof
#define offsetof(typ,mbr)	((size_t)((char *)&((typ *)0)->mbr - (char *)0))
#endif
#define cmCust(fn, id, typ, mbr)	\
	{ fn,id,offsetof(typ,mbr),sizeof(((typ *)0)->mbr) },

#define cmEdit(id, typ, mbr)		cmCust(WPEdit::New, id, typ, mbr)
#define cmButn(id, typ, mbr)		cmCust(WPButton::New, id, typ, mbr)
#define cmCmbo(id, typ, mbr)		cmCust(WPComboBox::New, id, typ, mbr)
#define cmList(id, typ, mbr)		cmCust(WPListBox::New, id, typ, mbr)
#define cmSbar(id, typ, mbr)		cmCust(WPScrollBar::New, id, typ, mbr)
#define cmRBgp(id, typ, mbr,n)	{ WPRBGroup::New, id, offsetof(typ,mbr), n },
#define cmCBgp(id, typ, mbr,n)	{ WPCBGroup::New, id, offsetof(typ,mbr), n },
#define cmPush(id)					{ WPButton::New, id, NULL, 0 },
#define cmEnd(id)						{ NULL, id }

//////////////////
// Base class used for all dialogs.
// 
DLLCLASS WPDialog : public WPWin {
protected:
	static WPDialog* NewDialog;	// global: dialog being initialized
	WPControlMap *ctlmap;			// control map links data to controls
	void *object;						// underlying data object
	BOOL modified;						// dialog modified
	WPODItemList odItems;			// owner-draw items, if any

	BOOL init();

	friend BOOL CALLBACK WPDlgProc(HWND, UINT, WPARAM, LPARAM);

	LPCSTR templateName;		// name of resource template
	int focusID;				// ID of control to receive initial focus
	int result;					// IDOK,IDCANCEL, etc.
	void endDlg(int code)	{ result=code; destroyWin(); }
	void loadError();
	LONG msgProc(WPEvent &event) { return dfltMsgProc(event); }

public:
	WPDialog(LPCSTR resname, WPWin *pwin=NULL, 
		WPControlMap *map=NULL, void* obj=NULL);

	void linkObject(void *obj, BOOL redisplay=TRUE);
	void* getObject()			{ return object; }
	BOOL isModified()			{ return modified; }
	void isModified(BOOL m)	{ modified=m; }

	// Virtual WPWin functions overridden for dialog boxes
	BOOL scrolled(int msg, int id, int thumbPos);
	BOOL command(int id, WORD msg);
	BOOL closed() { command(IDCANCEL, BN_CLICKED); return FALSE; }
	BOOL other(WPEvent &event);

	// New virtual functions defined for dialog boxes
	virtual void initDlg() { }
	virtual void updateObject();
	virtual void updateScreen();

	// Miscellaneous functions
	int run()							{ createWin(); return result; }
	void mapRect(WPRect& r)			{ MapDialogRect(getHwnd(), &r); }
	int returnCode()					{ return result; }
	WPControl *getControl(int id)	{ return (WPControl*)getChild(id); }
	int defaultID()					{ return LOWORD(sendMsg(DM_GETDEFID)); }
	void defaultID(int id)			{ sendMsg(DM_SETDEFID, id); }
	void addODItem(WPOwnerDrawItem* od) { odItems.add(od); }
};

//////////////////
// Modal dialog box.
// 
DLLCLASS WPDialogModal : public WPDialog {
public:
	WPDialogModal(LPCSTR resname, WPWin *pwin=NULL, WPControlMap *map=NULL, 
		void* obj=NULL) : WPDialog(resname, pwin, map, obj) { }
	BOOL createWin();
	void destroyWin() { EndDialog(getHwnd(), result); }
};

//////////////////
// Modeless dialog box.
// 
DLLCLASS WPDialogModeless : public WPDialog {
	WPDialogModeless* next;	// next modeless dlg in app
	friend WPApp;
public:
	WPDialogModeless(LPCSTR resname, WPWin *pwin=NULL, 
		WPControlMap *map=NULL, void *obj=NULL);
	~WPDialogModeless();
	BOOL createWin();
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLFILE.H
//
// File Dialog definitions.

//////////////////
// File Open dialog.
// 
DLLCLASS WPDlgFileOpen : public WPDialogModal {
protected:
	OPENFILENAME ofn;
	char tempbuf[MAXFILENAMELEN];
	char *filename;
public:
	WPDlgFileOpen(WPWin *pwin, char* fname, LPCSTR title=NULL);

	BOOL createWin();
	void destroyWin() { sendMsg(WM_COMMAND, IDABORT, result); }
	BOOL command(int id, WORD msg)	{ return FALSE; }

	void setFilter(LPCSTR filt)
		{ if (filt) ofn.lpstrFilter=(LPSTR)filt; }
	void setDir(LPCSTR dir)
		{ ofn.lpstrInitialDir=(LPSTR)dir; }
};

//////////////////
// File Save As dialog. 
// Like File Open, but uses different COMMDLG subroutine.
// 
DLLCLASS WPDlgFileSaveAs : public WPDlgFileOpen {
public:
	WPDlgFileSaveAs(WPWin *pwin, char* fname, LPCSTR title=NULL);
	BOOL createWin();
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLPRT.H
//
// Printer dialog definitions.

// Default flags for COMMDLG print dialog: get printer DC.
const DWORD PD_DEFAULT = PD_RETURNDC;

//////////////////
// Print dialog box.
// 
DLLCLASS WPDlgPrint : public WPDialogModal {
public:
	PRINTDLG pdlg;				// Windows COMMDLG structure
	HDC getHDC()				{ return pdlg.hDC; }

	WPDlgPrint(WPWin *pwin);
	~WPDlgPrint();
	void destroyWin()			{ sendMsg(WM_COMMAND, IDABORT); }
	BOOL createWin()			{ return result = PrintDlg(&pdlg); }

	// Functions to get results of print dialog from COMMDLG structure.
	DWORD	flags()				{ return pdlg.Flags; }
	void	flags(DWORD f)		{ pdlg.Flags = f; }
	WORD	fromPage()			{ return pdlg.nFromPage; }
	void	fromPage(WORD p)	{ pdlg.nFromPage = p; }
	WORD	toPage()				{ return pdlg.nToPage; }
	void	toPage(WORD p)		{ pdlg.nToPage = p; }
	WORD	minPage()			{ return pdlg.nMinPage; }
	void	minPage(WORD p)	{ pdlg.nMinPage = p; }
	WORD	maxPage()			{ return pdlg.nMaxPage; }
	void	maxPage(WORD p)	{ pdlg.nMaxPage = p; }
	WORD	nCopies()			{ return pdlg.nCopies; }
	void	nCopies(WORD n)	{ pdlg.nCopies = n; }
};

//////////////////
// Print Abort dialog
// 
DLLCLASS WPDlgPrintAbort : public WPDialogModeless {
public:	
	WPDlgPrintAbort(WPWin *pwin, LPCSTR resname="DLGPRINTABORT")
		: WPDialogModeless(resname, pwin) { createWin(); }
	BOOL command(int id, WORD msg);
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLSTR.H
//
// String dialog defnitions.

//////////////////
// Generic "string" dialog gets a string of text from user.
// 
DLLCLASS WPDlgString : public WPDialogModal {
	DLGTEMPLATE* memTemplate;		// template for DialogBoxIndirect
	char	*strBuf;						// caller's buffer
	int strLen;							// length
public:	
	WPDlgString(WPWin *pwin, char *buf, int len, LPCSTR prompt, LPCSTR cap=NULL);
	WPDlgString(WPWin *pwin, char *buf, int len, LPCSTR resname)
		: WPDialogModal(resname, pwin) { memTemplate = NULL; createWin(); }
	~WPDlgString();
	BOOL createWin();
	void initDlg();
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPMENU.H
//
// Menu definitions.

// Default way to manipulate menu items is by command id, not position.
#define MF_DFLTPOS	MF_BYCOMMAND

//////////////////
// Menu class
// 
DLLCLASS WPMenu {
protected:
	HMENU hmenu;					// Windows handle to menu
public:
	WPMenu()							{ hmenu = CreateMenu(); }
	WPMenu(HMENU h)				{ hmenu=h; }
	WPMenu(MENUITEMTEMPLATEHEADER& t):
		hmenu(LoadMenuIndirect((void *)&t)) {}

	WPMenu(WPWin *win)			{ hmenu = GetMenu(win->getHwnd()); }

	void destroy()					{ DestroyMenu(hmenu); }
	HMENU operator()()			{ return hmenu; }
	WPMenu& operator=(HMENU h)	{ hmenu=h; return *this; }
	BOOL operator==(WPMenu &m)	{ return hmenu==m.hmenu; }

	int count()						{ return GetMenuItemCount(hmenu); }
	int itemID(int pos)			{ return GetMenuItemID(hmenu, pos); }
	WORD state(int id, WORD how=MF_DFLTPOS)
		{ return GetMenuState(hmenu, id, how); }
	int getText(int id, char *buf, int buflen, WORD how=MF_DFLTPOS)
		{ return GetMenuString(hmenu, id, buf, buflen, how); }

	BOOL checkItem(int id, BOOL chk, WORD how=MF_DFLTPOS)
		{ return CheckMenuItem(hmenu, id, 
			chk  ? (how|MF_CHECKED) : (how|MF_UNCHECKED)); }
	BOOL enableItem(int id, BOOL enab, WORD how=MF_DFLTPOS)
		{ return EnableMenuItem(hmenu, id, 
			enab  ? (how|MF_ENABLED) : (how|MF_GRAYED)); }
	BOOL hiliteItem(WPWin *win, int id, BOOL hi, WORD how=MF_DFLTPOS)
		{ return HiliteMenuItem((*win)(), hmenu, id, 
			hi  ? (how|MF_HILITE) : (how|MF_UNHILITE)); }

	BOOL trackPopup(WPWin *win, WPPoint p)
		{ return TrackPopupMenu(hmenu, 0, p.x, p.y, 0, (*win)(), NULL); }
	BOOL setBitmaps(int id, WPBitmap* bm0, WPBitmap* bm1, 
		WORD how=MF_DFLTPOS);

	BOOL append(int id, LPCSTR text, WORD flags=0) 
		{ return AppendMenu(hmenu, MF_STRING|flags, id, text); }
	BOOL append(WPMenu& popup, LPCSTR text)
		{ return AppendMenu(hmenu, MF_POPUP, (UINT)popup(), text); }
	BOOL append(int id, WPBitmap& bm, WORD flags=0);
	BOOL appendSep() 
		{ return AppendMenu(hmenu, MF_SEPARATOR, 0, NULL); }
	HMENU appendPopup(LPCSTR text);

	BOOL insert(int pos, int id, LPCSTR text, WORD flags=MF_DFLTPOS) 
		{ return InsertMenu(hmenu, pos, MF_STRING|flags, id, text); }
	BOOL insert(int pos, WPMenu& popup, LPCSTR text, WORD flags=MF_DFLTPOS)
		{ return InsertMenu(hmenu, pos, MF_POPUP|flags, (UINT)popup(), text); }
	BOOL insert(int pos, int id, WPBitmap& bm, WORD flags=MF_DFLTPOS);
	BOOL insertSep(int pos, WORD flags=MF_DFLTPOS)
		{ return InsertMenu(hmenu, pos, MF_SEPARATOR|flags, 0, NULL); }
	HMENU insertPopup(int pos, LPCSTR text, WORD flags=MF_DFLTPOS);

	BOOL modify(int pos, int id, LPCSTR text, WORD flags=MF_DFLTPOS) 
		{ return ModifyMenu(hmenu, pos, MF_STRING|flags, id, text); }
	BOOL modify(int pos, WPMenu& popup, LPCSTR text, WORD flags=MF_DFLTPOS)
		{ return ModifyMenu(hmenu, pos, MF_POPUP|flags, (UINT)popup(), text); }
	BOOL modify(int pos, int id, WPBitmap& bm, WORD flags=MF_DFLTPOS);

	BOOL remove(int pos, WORD flags=MF_DFLTPOS)
		{ return RemoveMenu(hmenu, pos, flags); }
	BOOL deleteItem(int pos, WORD flags=MF_DFLTPOS)
		{ return DeleteMenu(hmenu, pos, flags); }
};

//////////////////
// Submenu.
// 
DLLCLASS WPSubMenu : public WPMenu {
public:
	WPSubMenu(WPMenu& menu, int pos) : WPMenu(GetSubMenu(menu(),pos)) { }
};

//////////////////
// Popup menu.
// 
DLLCLASS WPPopupMenu : public WPMenu {
public:	
	WPPopupMenu()	: WPMenu(CreatePopupMenu())	{ }
};

////////////////
// System menu.
// 
DLLCLASS WPSysMenu : public WPMenu {
public:
	WPSysMenu(WPWin *w) : WPMenu(GetSystemMenu((*w)(), FALSE)) { }
	void revert(WPWin *w)	{ hmenu = GetSystemMenu((*w)(), TRUE); }
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPGDI.H
//
// GDI (Graphics Device Interface) definitions.

const DWORD	COLOR_RED	= RGB(0xFF,0,0);
const DWORD	COLOR_GREEN	= RGB(0,0xFF,0);
const DWORD	COLOR_BLUE	= RGB(0,0,0xFF);
const DWORD COLOR_BLACK = 0;
const DWORD COLOR_WHITE = 0x00FFFFFF;
const DWORD COLOR_NONE	= 0xFFFFFFFF;

//////////////////
// This little structure is used to parse the driver and output names
// from WIN.INI, given a device name.  It makes it easier to create device 
// contexts to printers and other devices.
// 
struct WPDEVNAME {
	char	deviceName[50];	// device name
	char* driverName;			// parsed driver name
	char* outputName;			// output file (e.g., LPT1:)
	WPDEVNAME(LPCSTR devname);
};

//////////////////
// Base class for all drawing objects (pen, brush, etc.)
// 
DLLCLASS WPDrawObj {
protected:
	HGDIOBJ hobj;						// Windows handle
	BOOL del;							// whether to delete

	void set(HGDIOBJ h, BOOL d)	{ hobj = h; del = d; }
	void destroy();

	WPDrawObj()							{ hobj=NULL; del=FALSE; }
	WPDrawObj(HGDIOBJ h, BOOL d)	{ set(h, d); }
	~WPDrawObj()						{ destroy(); }

	friend WPDevContext;
public:
	HGDIOBJ operator()()				{ return hobj; }
	operator HGDIOBJ()				{ return hobj; }
};
	
//////////////////
// Pen object
// 
DLLCLASS WPPen : public WPDrawObj {
public:
	// Constructors
	WPPen(int id) : WPDrawObj(GetStockObject(id), FALSE) { }
	WPPen(COLORREF color, int style=PS_SOLID, int wid=1 )
		: WPDrawObj(CreatePen(style, wid, color), TRUE) { }
	WPPen(LPLOGPEN data)	: WPDrawObj(CreatePenIndirect(data), TRUE) { }

	void getObject(LOGPEN& data)
		{ GetObject(hobj, sizeof(LOGPEN), (LPSTR)&data); }
	HPEN operator()()				{ return (HPEN)hobj; }
	operator HPEN()				{ return (HPEN)hobj; }
};

//////////////////
// Bitmap object.
// 
DLLCLASS WPBitmap : public WPDrawObj {
	WPPoint ext;				// width, height of bitmap
	void init();
public:
	WPBitmap(LPCSTR name) : WPDrawObj(theApp->loadBitmap(name), TRUE) 
		{ init(); }
	WPBitmap(int id) : WPDrawObj(theApp->loadBitmap(id), TRUE) 
		{ init(); }
	WPBitmap(WPDevContext* dc, int w, int h);

	WPBitmap() { }
	void copyScreen(WPRect& rc);

	WPPoint extent()	{ return ext; }

	DWORD getBits(LPSTR buf,int len)	
		{ return GetBitmapBits((HBITMAP)hobj, len, buf); }
	LONG setBits(LPSTR buf,int len)	
		{ return SetBitmapBits((HBITMAP)hobj,len,buf); }

	void getObject(BITMAP& data)
		{ GetObject(hobj, sizeof(BITMAP), (LPSTR)&data); }
	HBITMAP operator()()				{ return (HBITMAP)hobj; }
	operator HBITMAP()				{ return (HBITMAP)hobj; }
};

//////////////////
// Brush object
// 
DLLCLASS WPBrush : public WPDrawObj {
public:
	// Constructors
	WPBrush(int id) : WPDrawObj(GetStockObject(id), FALSE) { }
	WPBrush(COLORREF color) : WPDrawObj(CreateSolidBrush(color), TRUE)	{ }
	WPBrush(COLORREF c, int h)	: WPDrawObj(CreateHatchBrush(h, c), TRUE)	{ }
	WPBrush(LOGBRUSH &lb) : WPDrawObj(CreateBrushIndirect(&lb), TRUE)		{ }
	WPBrush(WPBitmap *bm) : WPDrawObj(CreatePatternBrush((*bm)()), TRUE) { }

	void getObject(LOGBRUSH& data)
		{ GetObject(hobj, sizeof(LOGBRUSH), (LPSTR)&data); }
	HBRUSH operator()()				{ return (HBRUSH)hobj; }
	operator HBRUSH()					{ return (HBRUSH)hobj; }
};

//////////////////
// Font object
// 
DLLCLASS WPFont : public WPDrawObj {
public:
	// Constructors
	WPFont(LOGFONT &lf) : WPDrawObj(CreateFontIndirect(&lf), FALSE) { }
	void getObject(LOGFONT& data)
		{ GetObject(hobj, sizeof(LOGFONT), (LPSTR)&data); }
};
/////////////////				
// Class to represent an information context 
// is also the base class for all kinds of device contexts.
// 
DLLCLASS WPDevInfo {
protected:
	HDC hdc;						// Windows handle to DC
public:
	WPDevInfo() { hdc=NULL; }
	WPDevInfo(LPCSTR devname);
	WPDevInfo(LPCSTR devname, LPCSTR driver, LPCSTR output, DEVMODE* devmode);
	virtual ~WPDevInfo();

	static HDC GetHDC(WPDevInfo *dc)	{ return dc ? dc->hdc : NULL; }
	HDC operator()()			{ return hdc; }
	operator HDC()				{ return hdc; }
	int getCap(int cap)		{ return GetDeviceCaps(hdc, cap); }

	// Brainless fns for various device capabilities
	int getDRIVERVERSION()	{ return getCap(DRIVERVERSION); }
	int getTECHNOLOGY()		{ return getCap(TECHNOLOGY); }
	int getHORZSIZE()			{ return getCap(HORZSIZE); }
	int getVERTSIZE()			{ return getCap(VERTSIZE); }
	int getHORZRES()			{ return getCap(HORZRES); }
	int getVERTRES()			{ return getCap(VERTRES); }
	int getBITSPIXEL()		{ return getCap(BITSPIXEL); }
	int getPLANES()			{ return getCap(PLANES); }
	int getNUMBRUSHES()		{ return getCap(NUMBRUSHES); }
	int getNUMPENS()			{ return getCap(NUMPENS); }
	int getNUMMARKERS()		{ return getCap(NUMMARKERS); }
	int getNUMFONTS()			{ return getCap(NUMFONTS); }
	int getNUMCOLORS()		{ return getCap(NUMCOLORS); }
	int getPDEVICESIZE()		{ return getCap(PDEVICESIZE); }
	int getCURVECAPS()		{ return getCap(CURVECAPS); }
	int getLINECAPS()			{ return getCap(LINECAPS); }
	int getPOLYGONALCAPS()	{ return getCap(POLYGONALCAPS); }
	int getTEXTCAPS()			{ return getCap(TEXTCAPS); }
	int getCLIPCAPS()			{ return getCap(CLIPCAPS); }
	int getRASTERCAPS()		{ return getCap(RASTERCAPS); }
	int getASPECTX()			{ return getCap(ASPECTX); }
	int getASPECTY()			{ return getCap(ASPECTY); }
	int getASPECTXY()			{ return getCap(ASPECTXY); }
	int getLOGPIXELSX()		{ return getCap(LOGPIXELSX); }
	int getLOGPIXELSY()		{ return getCap(LOGPIXELSY); }
	int getSIZEPALETTE()		{ return getCap(SIZEPALETTE); }
	int getNUMRESERVED()		{ return getCap(NUMRESERVED); }
	int getCOLORRES()			{ return getCap(COLORRES); }
};

//////////////////
// Information about the display
// 
DLLCLASS WPDisplayInfo : public WPDevInfo {
public:
	WPDisplayInfo();
};

//////////////////
// Information about the printer
// 
DLLCLASS WPPrinterInfo : public WPDevInfo {
public:	
	WPPrinterInfo();
};

//////////////////
// Device context base class
// 
DLLCLASS WPDevContext : public WPDevInfo {
protected:
	//////////////////
	// Each type of drawing object has an ID, used as offset to store
	// handle in a table.
	// 
	enum WHICHOBJ { SELPEN=0, SELBRUSH, SELBITMAP, SELFONT, SELRGN, SELPALETTE,
		NDRAWOBJ };
protected:
	WPDrawObj drawObj[NDRAWOBJ];	// current selected drawing objects
	HANDLE originalObj[NDRAWOBJ];	// original drawing objects

	const int* tabs;			// array of tab stops (logical x-coords)
	int ntabs;					// number of tab stops
	int tabOrg;					// relative x-origin of tabs
	int err;						// last error code from Escape

	void init(HDC h)			// common initializer for all constructors
		{ memset((void*)this,0,sizeof(WPDevContext)); hdc = h; }

protected:
	BOOL anySelected;			// whether any new objects are selected

	WPDrawObj* getDrawObj(WHICHOBJ which)	{ return &drawObj[which]; }
	void restoreSelection();
	HGDIOBJ select(WHICHOBJ which, HANDLE h, BOOL d, BOOL pgPal=TRUE);
	HGDIOBJ select(WHICHOBJ which, WPDrawObj *obj, BOOL bgPal=TRUE)
		{ return select(which, obj->hobj, FALSE, bgPal); }
	
public:
	WPDevContext(HDC h=NULL)	{ init(h); }
	WPDevContext(LPCSTR devname, DEVMODE* ini=NULL)
		{ WPDEVNAME dv = devname;
			init(CreateDC(dv.driverName, dv.deviceName, dv.outputName, ini)); }
	WPDevContext(LPCSTR devname, LPCSTR driver, LPCSTR output, DEVMODE* ini)
		{ init(CreateDC((LPSTR)driver, (LPSTR)devname,
			(LPSTR)output, ini)); }
	~WPDevContext() 
		{ if (hdc && anySelected) restoreSelection(); }

	int error()										{ return err; }
	void setTabOrigin(int o)					{ tabOrg = o; }
	void setTabs(int *tabArray, int len)	{ tabs=tabArray; ntabs=len; }

	// Pen
	WPPen *getPen()						{ return (WPPen*)getDrawObj(SELPEN); }
	HPEN setPen(WPPen *pen)				{ return (HPEN)select(SELPEN, pen); }
	HPEN setPen(HPEN h)					{ return (HPEN)select(SELPEN, h, FALSE); }
	HPEN setPen(int stock)
		{ return (HPEN)select(SELPEN, (HANDLE)stock, FALSE); }
	HPEN setPen(COLORREF color, int style=PS_SOLID, int wid=1)
		{ return (HPEN)select(SELPEN, CreatePen(style, wid, color), TRUE); }

	// Brush
	WPBrush *getBrush()				{ return (WPBrush*)getDrawObj(SELBRUSH); }
	HBRUSH setBrush(WPBrush* b)	{ return (HBRUSH)select(SELBRUSH, b); }
	HBRUSH setBrush(HBRUSH h)		{ return (HBRUSH)select(SELBRUSH, h,FALSE); }
	HBRUSH setBrush(int stock)		
		{ return (HBRUSH)select(SELBRUSH, (HANDLE)stock, FALSE); }
	HBRUSH setBrush(COLORREF color)		
		{ return (HBRUSH)select(SELBRUSH, CreateSolidBrush(color), TRUE); }
	HBRUSH setBrushHatch(COLORREF color, int hatch)	
		{ return (HBRUSH)select(SELBRUSH,CreateHatchBrush(hatch,color),TRUE);}

	UINT realizePalette()			{ return RealizePalette(hdc); }

	HFONT setFont(LPCSTR face, int ptSize, BOOL ital=FALSE, int bold=FW_NORMAL);
	// Logical/device coords
	BOOL DP2LP(WPPoint *pts, int n)		{ return DPtoLP(hdc,pts,n); }
	BOOL LP2DP(WPPoint *pts, int n)		{ return LPtoDP(hdc,pts,n); }
	BOOL DP2LP(WPPoint& p)					{ return DP2LP(&p, 1); }
	BOOL LP2DP(WPPoint& p)					{ return LP2DP(&p, 1); }
	BOOL DP2LP(WPRect& r)					{ return DP2LP((WPPoint*)&r, 2); }
	BOOL LP2DP(WPRect& r)					{ return LP2DP((WPPoint*)&r, 2); }

	// Brainless GDI functions
	BOOL arc(WPRect& box, WPPoint beg, WPPoint end)
		{ return Arc(hdc, box.left, box.top, box.right, box.bottom,
			beg.x, beg.y, end.x, end.y); }

	BOOL bitBlt(WPRect& box, WPDevContext& srcDC, 
		WPPoint srcPt, DWORD rop = SRCCOPY)
		{ return BitBlt(hdc, box.left, box.top, box.width(), box.height(),
			srcDC.hdc, srcPt.x, srcPt.y, rop); }

	BOOL chord(WPRect& box, WPPoint p1, WPPoint p2)
		{ return Chord(hdc,box.left,box.top,box.right,box.bottom,
				p1.x, p1.y, p2.x, p2.y); }

	void drawBitmap(int x, int y, WPBitmap* bm, DWORD rop = SRCCOPY);
	void drawIcon(int x, int y, HICON hicon) 
		{ DrawIcon(hdc, x, y, hicon); }
	void drawIcon(WPPoint p, HICON hicon) 
		{ drawIcon(p.x, p.y, hicon); }
	int drawText(WPRect& rect, LPCSTR text, WORD format=0, int len=-1)
		{	return DrawText(hdc, text, len, &rect, format); }
	BOOL grayString(WPRect& r, LPSTR text, WPBrush& brush)
		{ return GrayString(hdc, brush(), NULL, NULL, strlen(text),
			r.left,r.top,r.width(),r.height()); }
	void drawFocusRect(WPRect &rect)
		{ DrawFocusRect(hdc, &rect); }

	BOOL ellipse(WPRect &box)
		{ return Ellipse(hdc,box.left,box.top,box.right,box.bottom); }

	int excludeClipRect(WPRect& box)
		{ return ExcludeClipRect(hdc,box.left,box.top,
			box.right,box.bottom); }
	int excludeUpdateRgn(WPWin *win)
		{ return ExcludeUpdateRgn(hdc, (*win)()); }
	int getClipBox(WPRect& box)	{ return GetClipBox(hdc,&box); }
	int intersectClipRect(WPRect& box)
		{ return IntersectClipRect(hdc,box.left,box.top,
			box.right,box.bottom); }

	int escape(int func, int nbytes=0, LPSTR in=NULL, LPSTR out=NULL)
		{ return err = Escape(hdc, func, nbytes, in, out); }

	BOOL charWidth(WORD c1, WORD c2, int *widths)
		{ return GetCharWidth(hdc, c1, c2, (LPINT)widths); }

	int offsetClipRgn(int x, int y)	{ return OffsetClipRgn(hdc, x, y); }
	int offsetClipRgn(WPPoint p)		{ return OffsetClipRgn(hdc, p.x, p.y); }

	BOOL fill(WPPoint p, COLORREF color, WORD how)
		{ return ExtFloodFill(hdc, p.x, p.y, color, how); }
	BOOL fill(WPPoint p, COLORREF color)
		{ return FloodFill(hdc, p.x, p.y, color); }
	BOOL fill(WPRect& rect, WPBrush& brush)
		{ return FillRect(hdc, &rect, brush()); }
	int fillMode()						{ return GetPolyFillMode(hdc); }
	int fillMode(int mode)			{ return SetPolyFillMode(hdc, mode); }

	DWORD getAspectRatio(WPSize& sz)
		{ return GetAspectRatioFilterEx(hdc,&sz); }
	COLORREF bkColor()				{ return GetBkColor(hdc); }
	COLORREF	bkColor(COLORREF c)	{ return SetBkColor(hdc,c); }
	int bkMode()						{ return GetBkMode(hdc); }
	int bkMode(int mode)				{ return SetBkMode(hdc,mode); }

	POINT brushOrg()			
		{ POINT p; GetBrushOrgEx(hdc, &p); return p; }
	BOOL  brushOrg(int x, int y, POINT* pPrevOrg=NULL)
		{ return SetBrushOrgEx(hdc, x, y, pPrevOrg); }
	BOOL  brushOrg(POINT p, POINT* pPrevOrg=NULL)
		{ return SetBrushOrgEx(hdc, p.x, p.y, pPrevOrg); }

	int mapMode()						{ return GetMapMode(hdc); }
	int mapMode(int m)				{ return SetMapMode(hdc,m); }

	COLORREF nearestColor(COLORREF color)
		{ return GetNearestColor(hdc, color); }

	POINT getPos()							
		{ POINT p; GetCurrentPositionEx(hdc, &p); return p; }
	POINT getDCOrg()						
		{ POINT p; GetDCOrgEx(hdc, &p); return p; }

	COLORREF pixel(int x, int y)		{ return GetPixel(hdc, x, y); }
	COLORREF pixel(WPPoint p)			{ return GetPixel(hdc, p.x, p.y); }
	COLORREF pixel(int x, int y, COLORREF color) 
		{ return SetPixel(hdc, x, y, color); }
	COLORREF pixel(WPPoint p, COLORREF color)
		{ return SetPixel(hdc, p.x, p.y, color); }

	int rop2()								{ return GetROP2(hdc); }
	int rop2(int rop)						{ return SetROP2(hdc, rop); }

	int stretchBltMode()					{ return GetStretchBltMode(hdc); }
	int stretchBltMode(int mode)		{ return SetStretchBltMode(hdc, mode); }

	WORD textAlign()						{ return GetTextAlign(hdc); }
	WORD textAlign(WORD align)			{ return SetTextAlign(hdc, align); }
	int textCharExtra()					{ return GetTextCharacterExtra(hdc); }
	int textCharExtra(int e)			{ return SetTextCharacterExtra(hdc, e); }
	DWORD textColor()						{ return GetTextColor(hdc); }
	DWORD textColor(COLORREF c)		{ return SetTextColor(hdc, c); }
	DWORD textExtent(LPCSTR text, int len)
		{ return GetTabbedTextExtent(hdc, text, len, ntabs, (LPINT)tabs); }
	DWORD textExtent(LPCSTR text)
		{ return textExtent(text, strlen(text)); }
	int textFace(LPSTR buf, int len)			
		{ return GetTextFace(hdc, len, buf); }
	BOOL textMetrics(TEXTMETRIC &tm)
		{ return GetTextMetrics(hdc, (LPTEXTMETRIC)&tm); }

	// Viewport and window
	void viewportOrg(WPPoint p)		{ SetViewportOrgEx(hdc, p.x, p.y, NULL); }
	void viewportExt(WPPoint p)		{ SetViewportExtEx(hdc, p.x, p.y, NULL); }
	void windowOrg(WPPoint p)			{ SetWindowOrgEx  (hdc, p.x, p.y, NULL); }
	void windowExt(WPPoint p)			{ SetWindowExtEx  (hdc, p.x, p.y, NULL); }
	WPPoint viewportOrg()	{ POINT p; GetViewportOrgEx(hdc, &p);  return p; }
	WPSize  viewportExt()	{ SIZE sz; GetViewportExtEx(hdc, &sz); return sz; }
	WPPoint windowOrg()		{ POINT p; GetWindowOrgEx  (hdc, &p);  return p; }
	WPSize  windowExt()		{ SIZE sz; GetWindowExtEx  (hdc, &sz); return sz; }

	void invert(WPRect &rect)			{ InvertRect(hdc, &rect); }

	BOOL lineTo(int x, int y)			{ return LineTo(hdc, x, y); }
	BOOL lineTo(const POINT& p)		{ return lineTo(p.x, p.y); }
	BOOL moveTo(int x, int y, POINT* prev=NULL)
		{ return MoveToEx(hdc, x, y, prev); }
	BOOL moveTo(const POINT& p, POINT* prev=NULL)
		{ return moveTo(p.x, p.y, prev); }
	BOOL line(const POINT& a, const POINT& b)	
		{ moveTo(a); return lineTo(b); }

	BOOL frame(WPRect& rect, WPBrush& brush)
		{ return FrameRect(hdc, &rect, brush()); }

	BOOL patBlt(WPRect &box, DWORD rop=PATCOPY)
		{ return PatBlt(hdc,box.left,box.top,box.width(),box.height(),rop);}
	BOOL pie(WPRect& box, WPPoint beg, WPPoint end)
		{ return Pie(hdc, box.left, box.top, box.right, box.bottom,
			beg.x, beg.y, end.x, end.y); }
	BOOL polygon (WPPoint *pts, int n) { return Polygon (hdc, pts, n); }
	BOOL polyline(WPPoint *pts, int n) { return Polyline(hdc, pts, n); }
	BOOL polyPolygon(WPPoint *pts, int* counts, int nPoly)
		{ return PolyPolygon(hdc, pts, (LPINT)counts, nPoly); }
	BOOL ptVisible(int x, int y)		{ return PtVisible(hdc, x, y); }
	BOOL ptVisible(WPPoint p)			{ return PtVisible(hdc, p.x, p.y); }

	BOOL rectangle(WPRect &box)
		{ return Rectangle(hdc,box.left,box.top,box.right,box.bottom); }
	BOOL rectVisible(WPRect& rect)	{ return RectVisible(hdc,&rect); }
	BOOL restore(int saved=-1)			{ return RestoreDC(hdc,saved); }
	BOOL roundRect(WPRect& box, int w, int h)
		{ return RoundRect(hdc, box.left, box.top, 
			box.right, box.bottom, w, h); }

	int save()								{ return SaveDC(hdc); }

	DWORD setMapperFlags(DWORD flags){ return SetMapperFlags(hdc, flags); }

	int setTextJustification(int nBreakExtra, int nBreakCount)
		{ return SetTextJustification(hdc, nBreakExtra, nBreakCount); }

	BOOL stretchBlt(WPRect &d, 
		WPDevContext& srcDC, WPRect &s, DWORD rop=SRCCOPY)
		{ return StretchBlt(hdc, d.left, d.top, d.width(), d.height(),
			srcDC.hdc, s.left, s.top, s.width(), s.height(), rop); }

	long textOut(int x, int y, LPCSTR text, int len) 
		{ return TabbedTextOut(hdc,x,y,text,len,ntabs,(LPINT)tabs,tabOrg); }
	long textOut(int x, int y, LPCSTR text)
		{ return textOut(x, y, text, strlen(text)); }
	long printF(WPPoint p, LPSTR format, ...);

	int updateColors() { return UpdateColors(hdc); }

	// Useful new functions
	void whiteOut(WPRect rect)	{ patBlt(rect, WHITENESS); }
	void blackOut(WPRect rect)	{ patBlt(rect, BLACKNESS); }
};

//////////////////
// Subclass for window device context
// 
DLLCLASS WPWinDC : public WPDevContext {
protected:
	WPWin *win;							// the window
	WPWinDC() { win = NULL; }		// no-arg constructor is private
public:
	WPWinDC(WPWin *);
	~WPWinDC();
};

//////////////////
// Subclass for window DC, including non-client area.
// 
DLLCLASS WPNCWinDC : public WPWinDC {
public:
	WPNCWinDC(WPWin *w);
};

//////////////////
// Memory device context
// 
DLLCLASS WPMemDC : public WPDevContext {
public:
	WPMemDC(WPDevContext* dc, WPBitmap *bm);
	WPMemDC(WPDevContext* dc, WPRect &winRect, BOOL mono=FALSE);

	HANDLE setBitmap(WPBitmap *bm) { return select(SELBITMAP, bm); }
	WPBitmap *getBitmap()			 { return (WPBitmap*)getDrawObj(SELBITMAP); }
};

////////////////
// The display DC
// 
DLLCLASS WPDisplay : public WPDevContext {
public:
	WPDisplay();
};

//////////////////
// Printer device context.
// 
DLLCLASS WPPrinter : public WPDevContext {
	static WPDlgPrintAbort *DlgAbort;	// abort dialog
	static BOOL Abort;						// abort flag
	WPWin *pwin;				// parent window
	BOOL delDC;					// delete DC?

	friend BOOL CALLBACK WPPrintAbortProc(HDC hdcPrn, int nCode);
	friend WPDlgPrintAbort;
public:	
	WPPrinter(LPCSTR devname=NULL, DEVMODE* devmode=NULL);
	WPPrinter(WPDlgPrint& pdlg);
	~WPPrinter();

	int doAbortDlg(WPWin *w);
	BOOL aborted()					{ return Abort; }
	int startDoc(LPCSTR name, LPCSTR output=NULL);
	int startPage()				{ return StartPage(hdc); }
	int endPage()					{ return EndPage(hdc); }
	int endDoc()					{ return EndDoc(hdc); }
};

//////////////////
// Printer subclass to do simple line printing.
// 
DLLCLASS WPLinePrinter : public WPPrinter {
	int nLinesPage;			// num lines per page
	int yChar;					// height of char
	int curLine;				// current line number
	void init();
public:	
	WPLinePrinter(LPCSTR devname=NULL) : WPPrinter(devname) { init(); }
	WPLinePrinter(WPDlgPrint& pdlg)	: WPPrinter(pdlg)		{ init(); }

	int outLine(LPCSTR buf, int len);
	int formFeed()	{ curLine=0; return endPage(); }
	int endDoc()	{ if (curLine>0) endPage(); return WPPrinter::endDoc(); }
};

//////////////////
// Paint structure, analogous to Windows' PAINTSTRUCT.
// 
DLLCLASS WPPaintDC : public WPDevContext {
public:	
	PAINTSTRUCT ps;			// Windows structure
	WPWin *win;					// Windows++ window

	WPPaintDC(WPWin *win);
	~WPPaintDC();
	BOOL bkRedrawn()						{ return ps.fErase; }
	void getPaintRect(WPRect &box)	{ box = ps.rcPaint; }
};

//////////////////
// Device context for owner-draw controls and menus.
// 
DLLCLASS WPOwnerDrawDC : public WPDevContext {
public:	
	WPRect paintRect;
	WORD action;
	WORD state;
	WPOwnerDrawDC(LPDRAWITEMSTRUCT draw);
	~WPOwnerDrawDC();
};

//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPMDI.H
//
// MDI (Multiple Document Interface) definitions.

//////////////////
// MDI client window. 
// 
DLLCLASS WPMDIClient : public WPWin {
protected:
	WPMDIClient(WPMDIFrame *pwin);
	~WPMDIClient()		{ theApp->mdiClientHwnd = NULL; }

	WPMDIChild* activeWin()
		{ return (WPMDIChild*)GetWin((HWND)LOWORD(sendMsg(WM_MDIGETACTIVE))); }
	friend WPMDIFrame;
};

//////////////////
// MDI Child window. It's derived from WPMainWin in order to inherit all 
// the stuff for the File, Edit, etc. commands--even though the
// Frame window is really the main window.
// 
DLLCLASS WPMDIChild : public WPMainWin {
	WPMDIClient* client;		// client window
public:
	WPMDIChild(LPCSTR classnm, WPMDIFrame *frame);
	BOOL createWin();
	void destroyWin()			
		{ client->sendMsg(WM_MDIDESTROY, (WPARAM)getHwnd()); }
	void maximize()			
		{ client->sendMsg(WM_MDIMAXIMIZE, (WPARAM)getHwnd()); }
	void restore()				
		{ client->sendMsg(WM_MDIRESTORE, (WPARAM)getHwnd()); }
	void activate()			
		{ client->sendMsg(WM_MDIACTIVATE, (WPARAM)getHwnd()); }
	WPMDIFrame *frameWin()	
		{ return (WPMDIFrame *)client->getParent(); }
};

//////////////////
// MDI Frame window.
// 
DLLCLASS WPMDIFrame : public WPMainWin {
	WPMDIClient *client;		// ptr to client window
	int winMenuPos;			// relative pos of "Window" menu
	friend WPMDIClient;
	friend WPMDIChild;
public:	
	WPMDIFrame(int winMenu, LPCSTR classnm = "MDIFRAME");
	~WPMDIFrame()					{ closeAll(TRUE); }

	WPMDIClient* clientWin()	{ return client; }
	WPMDIChild* activeWin()		{ return client->activeWin(); }

	BOOL createWin();

	// Brainless functions
	void cascade()			{ client->sendMsg(WM_MDICASCADE); }
	void tile()				{ client->sendMsg(WM_MDITILE); }
	void arrangeIcons()	{ client->sendMsg(WM_MDIICONARRANGE); }
	void nextWin()			{ client->sendMsg(WM_MDINEXT); }
	int numMDIChildren()	{ return client->numChildren(); }
	BOOL closeAll(BOOL force=FALSE);

	// Virtual message functions
	BOOL menuInit(WPMenu &menu);
	BOOL command(int id, WORD msg);
	BOOL queryEnd();
};

#endif	// RC_INVOKED

#endif	// WPP_H
