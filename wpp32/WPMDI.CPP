//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPMDI.CPP
//
// Implementation of MDI window classes.

#include "wpp.h"

//////////////////
// We need this window proc for frame windows because
// brain-damaged Microsoft uses one with non-standard arguments.
// 
LONG FAR PASCAL WPDefFrameProc(HWND hwnd, WORD msg, WORD wp, LONG lp)
{
	HWND clientHwnd = GetWindow(hwnd, GW_CHILD);
	return DefFrameProc(hwnd, clientHwnd, msg, wp, lp);
}

//////////////////
// Initialize frame window. 
// Argument is relative position in menu of "Window" popup.
// 
WPMDIFrame::WPMDIFrame(int winMenu, LPCSTR classnm) : WPMainWin(classnm)
{
	createArgs.wndcls.lpfnWndProc = (WNDPROC)WPDefFrameProc;
	createArgs.wndcls.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
	createArgs.style |= WS_CLIPCHILDREN;
	client = NULL;
	winMenuPos = winMenu;
}

//////////////////
// Create frame window: create client window too.
// 
BOOL WPMDIFrame::createWin()
{
	if (WPMainWin::createWin()) {			// create frame window
		client = new WPMDIClient(this);	// create client window
		assert(client);
		return TRUE;
	}
	return FALSE;
}

//////////////////
// Handle command:
//  MDI commands:		do it.
//  File commands:	do Open, New, Close, Exit; pass others to child.
//  Other:				pass to child.
// 
BOOL WPMDIFrame::command(int id, WORD msg)
{
	WPMDIChild *active = activeWin();

	switch (id) {
	case WPIDM_WINCASCADE:	cascade();			return TRUE;
	case WPIDM_WINTILE:		tile();				return TRUE;
	case WPIDM_WINARRANGE:	arrangeIcons();	return TRUE;
	case WPIDM_WINNEXT:		nextWin();			return TRUE;
	case WPIDM_WINCLOSEALL:	closeAll();			return TRUE;

	case WPIDM_FILEOPEN:
	case WPIDM_FILENEW:
	case WPIDM_EXIT:
		break;

	case WPIDM_FILECLOSE:
		if (active)
			active->close();
		return TRUE;

	default:
		if (active && active->command(id, msg))
			return TRUE;
	}
	return WPMainWin::command(id, msg);
}

//////////////////
// Close all child windows.
// 
BOOL WPMDIFrame::closeAll(BOOL force)
{
	WPChildWinList children = client; 
	WPWin *nextwin;
	for (WPWin *cwin=children.first(); cwin; cwin=nextwin) {
		nextwin = children.next();
		if (force || cwin->queryEnd())
			cwin->destroyWin();
		else
			return FALSE;
	}
	return TRUE;
}

//////////////////
// Check if it's ok to kill the app: check each child window.
// 
BOOL WPMDIFrame::queryEnd()
{
	forEachChildWin(client, cwin) {
		if (!cwin->queryEnd())
			return FALSE;
	}
	return TRUE;
}

//////////////////
// Initialize menu. 
// 
BOOL WPMDIFrame::menuInit(WPMenu &menu)
{
	WPMenu mainMenu = this;
	if (menu==mainMenu) {
		WPMDIChild *active = activeWin();

		// Initialize File menu
		BOOL gotFile = active && active->fileName()[0]!=0;
		menu.enableItem(WPIDM_FILESAVE, gotFile && active->fileIsModified());
		menu.enableItem(WPIDM_FILESAVEAS,active!=NULL);
		menu.enableItem(WPIDM_FILEPRINT, active!=NULL);
		menu.enableItem(WPIDM_FILECLOSE, active!=NULL);

		// Initialize Edit menu
		BOOL any = active && active->anySelected();
		menu.enableItem(WPIDM_EDITPASTE, active && active->canPaste());
		menu.enableItem(WPIDM_EDITCUT, any);
		menu.enableItem(WPIDM_EDITCOPY, any);
		menu.enableItem(WPIDM_EDITDELETE, any);
		menu.enableItem(WPIDM_EDITUNDO, active && active->canUndo());

		// Initialize Window menu
		for (int id = WPIDM_WINTILE; id <= WPIDM_WINCLOSEALL; id++)
			menu.enableItem(id, active!=NULL);
		return TRUE;
	}
	return FALSE;
}

//////////////////
// Initialize client window object.
// Note that the constructor actually creates the window too.
// 
WPMDIClient::WPMDIClient(WPMDIFrame *frame) : WPWin("MDICLIENT", frame, 1)
{
	createArgs.style = WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE;

	// Get Window popup menu
	WPMenu menu=frame;
	WPSubMenu submenu(menu, frame->winMenuPos);

	// Set up weird windows structure.
	CLIENTCREATESTRUCT ccs;
	ccs.hWindowMenu = submenu();
	ccs.idFirstChild = 1;
	createArgs.lparam = (LPSTR)&ccs;

	createWin();				// create window

	// Tell application object to translate accelerator keys.
	theApp->mdiClientHwnd = getHwnd();
}

//////////////////
// Initialize MDI child window.
// 
WPMDIChild::WPMDIChild(LPCSTR classnm, WPMDIFrame *frame) : WPMainWin(classnm)
{
	createArgs.parent = frame->clientWin();
	createArgs.wndcls.lpfnWndProc = DefMDIChildProc;
	createArgs.wndcls.lpszMenuName = NULL;
	createArgs.title = NULL;
	createArgs.style = 0;
	noAppQuit=TRUE;			// hack so WPMainWin won't post WM_QUIT msg
}

/////////////////
// Create child window: do weird Windows incantations.
// 
BOOL WPMDIChild::createWin()
{
	MDICREATESTRUCT cs;		// another unnecessary Windows structure

	cs.szClass = (char*)createArgs.wndcls.lpszClassName;
	cs.szTitle = (char*)createArgs.title;
	cs.hOwner = createArgs.wndcls.hInstance;
	cs.x  = createArgs.pos.left;
	cs.y  = createArgs.pos.top;
	cs.cx = createArgs.pos.width();
	cs.cy = createArgs.pos.height();
	cs.style = createArgs.style;
	cs.lParam = NULL;

	// Register window class if it ain't already registered!
	WNDCLASS temp;
	if (!GetClassInfo((HINSTANCE)cs.hOwner, cs.szClass, &temp)) {
		BOOL ret = RegisterClass(&createArgs.wndcls);
		assert(ret);
	}

	// Now create the child window.
	client = (WPMDIClient*)createArgs.parent;
	assert(client);
	HWND newhwnd = (HWND)(client->sendMsg(WM_MDICREATE, 0, &cs));
	linkHwnd(newhwnd);
	return hwnd!=NULL;
}
