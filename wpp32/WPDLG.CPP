//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLG.CPP
//
// Dialog implementation.

#include "wpp.h"

/////////////////
// This is THE dialog procedure used for all Windows++ dialog boxes
// 
BOOL DLLFUNC CALLBACK WPDlgProc(HWND hdlg, UINT msg, WPARAM wp, LPARAM lp)
{
	WPDialog *dlg;

	if (msg == WM_INITDIALOG) {
		dlg = WPDialog::NewDialog;		// dialog obj passed as global (ugh!)
		assert(dlg);						// it better exist
		WPDialog::NewDialog = NULL;	// safety: don't re-init
		dlg->linkHwnd(hdlg);				// link to window
		return dlg->init();				// call init function

	} else {
		// Got some message other than WM_INITDIALOG
		dlg = (WPDialog*)WPWin::GetWin(hdlg);
		if (dlg==NULL)
			return FALSE;
	}
	WPEvent event(msg, wp, lp);
	return dlg->dispatchEvent(event);
}

// This global is used to identify which dialog object should
// be linked when processing WM_INITDIALOG.
// Famous quote: "I can't program without globals." -BTB
// 
WPDialog * WPDialog::NewDialog = NULL;

//////////////////
// Create dialog box.  
// 
WPDialog::WPDialog(LPCSTR resname, WPWin *pwin, WPControlMap *map, void *obj) 
	: WPWin(NULL, pwin)
{ 
	NewDialog = this;			// set global so WPDlgProc knows to link me
	templateName = resname;
	ctlmap = map;
	object = obj;
	result = 0;
	focusID = 0;
	modified = FALSE;
}

//////////////////
// Initialize dialog. 
// This private function is used interally by Windows++ only.
// 
BOOL WPDialog::init()
{ 
	modified = FALSE;
	linkObject(object, FALSE);	// link controls to underlying object
	initDlg();						// call app-specific public virtual function
	updateScreen();				// copy object->screen
	return focusID==0;
}

//////////////////
// Link object to dialog. ctlmap specifies the structure of the object, 
// and which controls are linked to which data members. The last entry
// in the table specifies the initial focus control ID.
// 
void WPDialog::linkObject(void *obj, BOOL redisplay)
{
	object = obj;
	if (!ctlmap)
		return;

	// Loop over control map, linking each control one at a time.
	WPControlMap* map;
	for (map = ctlmap; map->newfn; map++) {
		int id = map->id;
		HWND chwnd = GetDlgItem(getHwnd(), id);
		if (chwnd==NULL) {
			// Control doesn't exist in dialog!
			ErrBox("Error: ID %d is in control map but not dialog!", id);
			continue;
		}
		WPControl *ctl = (WPControl*)GetWin(chwnd);
		if (ctl==NULL)								// if control (W++ object) no exist:
			ctl = (*map->newfn)(this, id);	// create one.
		assert(ctl);

		// Now link the control to its data object.
		if (object && map->len > 0)
			ctl->linkObject((char*)object + map->offset, map->len);
		else
			ctl->linkObject(NULL, 0);
	}
	focusID = map->id;		// last id = initial focus
	if (redisplay)				// redisplay requested:
		updateScreen();		// update all the controls on screen
}

//////////////////
// Update the screen: just udpate each control.
// 
void WPDialog::updateScreen()
{
	forEachChildWin(this, cwin) {
		((WPControl*)cwin)->updateScreen();
		if (cwin->getID()==focusID)
			cwin->setFocus();
	}
}

//////////////////
// Update the data object: update from each control.
// 
void WPDialog::updateObject()
{
	modified = TRUE;
	forEachChildWin(this, cwin)
		((WPControl*)cwin)->updateObject();
}

//////////////////
// Handle menu command.  
// Default behavior for modal dialog box:
// OK:		update the underlying object, then end the dialog.
// CANCEL:	end dialog, without updating.
// 
BOOL WPDialog::command(int id, WORD msg)
{
	switch (id) {
	case IDCANCEL:
		if (queryEnd())
			endDlg(id);
		return TRUE;
	case IDOK:
		updateObject();		// copy dialog box ==> data
		endDlg(id);				// and quit
		return TRUE;
	}
	return WPWin::command(id, msg);
}

//////////////////
// Handle scroll message: pass to scrollbar object.
// 
BOOL WPDialog::scrolled(int msg, int id, int thumbPos)
{
	WPScrollBar *sb = (WPScrollBar *)getChild(id);
	if (sb)
		sb->handleMsg(msg, thumbPos);
	return sb!=NULL;
}

//////////////////
// Handle "rare" messages for dialogs. 
// The only ones we do are those for owner-draw items.
// 
BOOL WPDialog::other(WPEvent &event)
{ 
	if (odItems.dispatchEvent(event))
		return event.msg == WM_COMPAREITEM ? event.ret : TRUE;
	return WPWin::other(event);
}

void WPDialog::loadError()
{
	ErrBox("Couldn't load dialog: %s.", templateName);
	assert(FALSE);
}

//////////////////
// Create modal dialog box.
// 
BOOL WPDialogModal::createWin()
{
	result = DialogBox(theApp->getHinst(), 
		(LPSTR)templateName, 
		GetHwnd(createArgs.parent),
		theApp->getDlgProc());
	if (result==-1)
		loadError();
	return result != -1;
}

//////////////////
// Modeless dialog.
// 
WPDialogModeless::WPDialogModeless(LPCSTR resname, WPWin *pwin, 
	WPControlMap *map, void *obj) : WPDialog(resname, pwin, map, obj) 
{ 
	theApp->addDialog(this);		// Tell App we exist!
}

WPDialogModeless::~WPDialogModeless()
{ 
	theApp->removeDialog(this);	// Tell App we're gone now.
}

//////////////////
// Create modeless dialog box.
// 
BOOL WPDialogModeless::createWin()
{
	HWND dlgHwnd = CreateDialog(theApp->getHinst(), 
		(LPSTR)templateName, 
		GetHwnd(createArgs.parent),
		theApp->getDlgProc());
	if (dlgHwnd==NULL)
		loadError();
	return dlgHwnd != NULL;
}
