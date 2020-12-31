//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPMAIN.CPP
//
// Implementation for WPMainWin.

#include "wpp.h"

//////////////////
// Init Main Window object: set up default createArgs.
// Use module name as default main window class name
// 
WPMainWin::WPMainWin(LPCSTR classnm) : WPWin(classnm)
{
	filename[0]=0;
	keyRepeat = 0;
	noAppQuit = FALSE;		// only used by MDI Child
	caption = NULL;
	fnFilter=NULL; 
	modified = FALSE;
	promptWin = NULL;

	// Set default creation args
	createArgs.title = createArgs.wndcls.lpszClassName;
	createArgs.style = WS_OVERLAPPEDWINDOW;

	// Use "AppIcon" and "AppMenu" if any.
	createArgs.wndcls.lpszMenuName = "AppMenu";
	createArgs.wndcls.hIcon = theApp->loadIcon("AppIcon");
	if (createArgs.wndcls.hIcon==NULL)
		createArgs.wndcls.hIcon = theApp->loadIcon(IDI_APPLICATION);
}

////////////////
// Destructor: post quit message to Windows.
// This happens automatically when the main window is destroyed!
// 
WPMainWin::~WPMainWin()
{ 
	if (!noAppQuit)			// (if not MDI child):
		theApp->quit();		// quit
}

//////////////////
// Handle low-level commands for main app window, such as 
// Exit, About and so on.
// 
BOOL WPMainWin::command(int id, WORD msg)
{
	char temp[MAXFILENAMELEN];

	switch (id) {
	case WPIDM_EXIT:
	case WPIDM_FILECLOSE:
		close();
		return TRUE;

	case WPIDM_ABOUT:
	    {
		WPDialogModal aboutBox("DLGABOUT", this);
		if (aboutBox.run()==-1)
			MsgBeep();
		return TRUE;
	    }
//	case WPIDM_MEMSTATS:
//		WPApp::ShowAllStats();
//		return TRUE;

	case WPIDM_FILENEW:
		if (fileKillConfirm() && fileNew())
			fileName("");
		return TRUE;

	case WPIDM_FILEOPEN:
		if (fileKillConfirm()) {
			WPDlgFileOpen openDlg(this, temp);
			openDlg.setFilter(fnFilter);
			if (openDlg.run() && fileOpen(temp))
				fileName(temp);
		}
		return TRUE;

	case WPIDM_FILESAVE:
		if (fileName()[0]) {
			if (fileSave(fileName()))
				fileIsModified(FALSE);
			return TRUE;
		}
		// no filename: fall through

	case WPIDM_FILESAVEAS:
	    {
		WPDlgFileSaveAs saveDlg(this, temp);
		saveDlg.setFilter(fnFilter);
		if (saveDlg.run() && fileSave(temp))
			fileName(temp);
		return TRUE;
	    }
	case WPIDM_FILEPRINT:
	    {
		WPDlgPrint pdlg = this;						 // create print dialog
		if (filePrintDlg(pdlg) && pdlg.run())	 // let app change PRINTDLG
			filePrint(pdlg);							 // print!
		setFocus();
		return TRUE;
	    }
	case WPIDM_EDITCUT:		return editCut();
	case WPIDM_EDITCOPY:		return editCopy();
	case WPIDM_EDITPASTE:	return editPaste();
	case WPIDM_EDITDELETE:	return editDelete();
	case WPIDM_EDITUNDO:		return editUndo();
	}
	return FALSE;
}

//////////////////
// Handle low-level keyboard messages: for now, all we do is 
// translate arrow keys to cursor movement.  Note that all this
// is built-in, so applications never have to bother with it.
// 
BOOL WPMainWin::kbd(WPEvent& event)
{
	int key = event.wp;
	switch (event.msg) {
	case WM_KEYDOWN:
		keyRepeat += LOWORD(event.lp);

		if (Keyboard.isArrowKey(key)) {
			// Got arrow key: move cursor
			WPPoint pt = Cursor();
			screenToClient(&pt);

			switch (key) {
			case VK_LEFT:	pt.x -= keyRepeat;	break;
			case VK_RIGHT:	pt.x += keyRepeat;	break;
			case VK_UP:		pt.y -= keyRepeat;	break;
			case VK_DOWN:	pt.y += keyRepeat;	break;
			}

			// Don't move outside our window's client area
			WPRect rect = this;
			rect.capture(pt);
			clientToScreen(&pt);
			Cursor = pt;
			return TRUE;
		}
		break;

	case WM_KEYUP:
		keyRepeat = 1;							 // Clear repeat count
		break;
	}
	return FALSE;
}

//////////////////
// Main window was activated: show the cursor if there's no mouse.
// 
BOOL WPMainWin::activated(WORD state, BOOL minimized)
{
	if (!Mouse.present() && !minimized)
		Cursor.show(state);
	setFocus();
	return TRUE;
}

//////////////////
// Got WM_CLOSE message:
// 
BOOL WPMainWin::closed()
{
	// automatically destroy window when close message received
	if (queryEnd())
		destroyWin();
	return TRUE;
}

//////////////////
// Handle paint message.
// Get paint struct and pass to app-specific virtual function.
// 
BOOL WPMainWin::paint()
{
	WPPaintDC ps = this;
	paint(ps);
	return TRUE;
}

//////////////////
// Initialize standard menu commands (File, Edit, etc)
// 
BOOL WPMainWin::menuInit(WPMenu &menu)
{
	WPMenu mainMenu = this;
	if (menu==mainMenu) {

		// Initialize File menu
		BOOL gotFile = fileName()[0]!=0;
		menu.enableItem(WPIDM_FILESAVE, gotFile && fileIsModified());

		// Initialize Edit menu
		BOOL any = anySelected();
		menu.enableItem(WPIDM_EDITPASTE, canPaste());
		menu.enableItem(WPIDM_EDITCUT, any);
		menu.enableItem(WPIDM_EDITCOPY, any);
		menu.enableItem(WPIDM_EDITDELETE, any);
		menu.enableItem(WPIDM_EDITUNDO, canUndo());
		return TRUE;
	}
	return FALSE;
}

//////////////////
// Handle WM_MENUSELECT message.
// If there's a prompt window, invoke app to get the text, then
// display it in the prompt window.
//
BOOL WPMainWin::menuSelected(int id, WORD flags)
{
	if (promptWin) {
		char* buf = theApp->scratch;
		*buf=0;
		getMenuPrompt(buf, id, flags);
		promptWin->invalidate(TRUE);;
		promptWin->setText(buf);
	}
	return TRUE;
}

//////////////////
// Initialize file name.
// 
void WPMainWin::fileInit(LPCSTR fname, LPCSTR cap)
{
	fileCaption(cap);
	if (fname && *fname) 
		fileOpen(fname);
	fileName(fname);
}

//////////////////
// Set file name.
// 
void WPMainWin::fileName(LPCSTR fname)
{
	if (fname && *fname)
		lstrcpy(filename, fname);
	else 
		filename[0]=0;

	fileIsModified(FALSE);
	if (caption) {
		char *buf = theApp->scratch;
		sprintf(buf,"%s %s", caption, filename[0] ? filename : "(untitled)" );
		setText(buf);
	}
}

//////////////////
// Do confirmation before over-writing current file.
// 
BOOL WPMainWin::fileKillConfirm()
{
	if (!fileIsModified())
		return TRUE;
	LPCSTR fname = fileName();

	char buf[MAXFILENAMELEN+40]="Save changes";
	if (fname[0]) {
		lstrcat(buf," to ");
		lstrcat(buf, fname);
	}
	strcat(buf,"?");
	MsgBeep();
	int answer = MsgBox(buf, caption, MB_YESNOCANCEL | MB_ICONQUESTION);
	if (answer==IDYES) {
		char temp[MAXFILENAMELEN];
		if (fname[0]==0) {
			WPDlgFileSaveAs saveDlg(this, temp);
			saveDlg.setFilter(fnFilter);
			if (!saveDlg.run())
				return FALSE;
			fname = temp;
		}
		return fileSave(fname);
	}
	return answer==IDNO;
}

BOOL WPMainWin::other(WPEvent &event)
{ 
	if (odItems.dispatchEvent(event))
		return event.msg == WM_COMPAREITEM ? event.ret : TRUE;
	return WPWin::other(event);
}
