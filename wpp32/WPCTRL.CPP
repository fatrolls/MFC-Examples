//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPCTRL.CPP
//
// Implementation of control window classes.  To reduce compilation time, 
// all control objects (edit, list box, etc.) are implemented here.
// 
#include "wpp.h"
#include <ctype.h>
#include <sys\types.h>
#include <sys\stat.h>

//////////////////
// Create control object.  
// Args like for WPWin: class name, parent win and id.
// 
WPControl::WPControl(LPCSTR classnm, WPWin *pwin, int id, long style)
	: WPWin(classnm, pwin, id)
{ 
	createArgs.style |= style; 
	object = NULL;
	objsiz = 0;
	tryLink();		// link if window already exists
}

//////////////////
// Try to link control to its window.
// 
BOOL WPControl::tryLink()
{
	if (getHwnd())
		return TRUE;
	HWND hwndParent = GetHwnd(createArgs.parent);
	if (hwndParent) {
		HWND hwndChild = GetDlgItem(hwndParent, createArgs.id());
		if (hwndChild) {
			linkHwnd(hwndChild);
			return TRUE;
		} 
	}
	return FALSE;
}

////////////////
// Static helper function, used by button group objects to create 
// button object for each button in the group if none exists.
// 
static WPButton *GetButton(WPWin *pwin, int id)
{
	WPButton *butn = (WPButton*)pwin->getChild(id);
	if (butn==NULL)
		butn = new WPButton(pwin, id);
	assert(butn);
	return butn;
}

//////////////////
// Get selection of radiobutton group.  Returns integer: 0 if 1st 
// button selected, 1 if second, and so on.  Assumes only one
// is selected.
// 
int WPRBGroup::getSel()
{
	WPWin *parent = getParent();
	int id=getID();
	for (int count = 0; count < objsiz; count++) {
		if (GetButton(parent, ++id)->getCheck())
			return count;
	}
	return -1;
}

//////////////////
// Set radiobutton corresponding to enum: 0 sets first button,
// 1 sets second, etc.  All others are turned off.
// 
void WPRBGroup::setSel(int sel)
{
	WPWin *parent = getParent();
	int id=getID();
	for (int count = 0; count < objsiz; count++)
		GetButton(parent, ++id)->setCheck(count==sel);
}

//////////////////
// Checkbox Button Group.
// 

//////////////////
// Check buttons from arary of BOOLs.
// 
void WPCBGroup::setSel(BOOL *barray)
{
	if (barray) {
		WPWin *parent = getParent();
		int id=getID();
		for (int count = objsiz; count > 0; count--)
			GetButton(parent, ++id)->setCheck(*barray++);
	}
}

//////////////////
// Stuff array of BOOLs with current button states.
// 
void WPCBGroup::getSel(BOOL *barray)
{
	if (barray) {
		WPWin *parent = getParent();
		int id=getID();
		for (int count = objsiz; count > 0; count--)
			*barray++ = GetButton(parent, ++id)->getCheck();
	}
}

//////////////////
// Set all buttons in checkbox group on or off.
// 
void WPCBGroup::setAll(BOOL val)
{
	WPWin *parent = getParent();
	int id=getID();	
	for (int count = objsiz; count > 0; count--) {
		WPButton *butn = GetButton(parent, ++id);
		butn->setCheck(val);
	}
}

/////////////////
// Edit Control
// 

//////////////////
// Filter keyboard char through "legalChars".
// 
BOOL WPEdit::kbd(WPEvent& event)
{
	if (legalChars) {
		char c = event.wp;
		if (event.msg==WM_CHAR && ( isprint(c) && !strchr((LPSTR)legalChars,c))) {
			MsgBeep();
			return TRUE;
		}
	}
	return WPControl::kbd(event);
}

//////////////////
// Paste text into edit control.
// 
void WPEdit::paste(BOOL flush)
{
	int beg,end;
	getSel(beg, end);
	sendMsg(WM_PASTE); 
	if (flush) {
		Clipboard.open(this);
		Clipboard.empty(); 
		Clipboard.close(); 
	}
	getSel(end, end);
	setSel(beg, end);
}

//////////////////
// Edit control got focus: select text and do default thing.
// 
BOOL WPEdit::gotFocus(WPWin *prev)
{
	setSel(); 
	return WPControl::gotFocus(prev);
}

//////////////////
// Load contents of file into edit control.
// 
BOOL WPMultiEdit::load(LPCSTR fname)
{
	int ret = FALSE;

	struct stat temp;
	if (stat((char*)fname, &temp) >= 0) {
		DWORD len = temp.st_size;
		LPSTR buf = new char [len+1];
		if (buf) {
			OFSTRUCT of;
			int fd = OpenFile((LPSTR)fname, (LPOFSTRUCT)&of, OF_READ);
			if (fd!=-1) {
				_lread(fd, buf, len);
				_lclose(fd);
				buf[len]=0;
				setText(buf);
				ret = TRUE;
			} else 
				ErrBox("Unable to open file '%s'.", fname);
			delete [] buf;

		} else
			ErrBox("File too big.");
	}
	return ret;
}

//////////////////
// Write contents of edit control to file.
// 
BOOL WPMultiEdit::save(LPCSTR fname)
{
	assert(*fname);
	DWORD len = getText();
	LPSTR buf = new char [len];
	if (buf) {
		OFSTRUCT of;

		getText(buf, len);
		int fd = OpenFile((LPSTR)fname, (LPOFSTRUCT)&of, OF_CREATE);
		if (fd!=-1) {
			_lwrite(fd, buf, len);
			_lclose(fd);

		} else 
			ErrBox("Unable to open file '%s'.", fname);

		delete [] buf;
		return TRUE;

	} else
		ErrBox("File too big.");
	return FALSE;
}

//////////////////
// List/Combo Box.  
//

void WPListBox::setList(WPListData *l, int selected, BOOL redraw)
{
	if ((list = l) != NULL) {
		reset();					// erase contents
		char buf[80];
		setReDraw(FALSE);
		for (BOOL more = list->firstItem(); more; more=list->nextItem()) {
			DWORD data = list->getItemText(buf, sizeof(buf));
			int item = append(buf);
			if (item!=LB_ERR)
				setItemData(item, data);
		}
		setReDraw(TRUE);
		if (redraw)
			invalidate();
	}
	setSel(selected);
}

//////////////////
// Combo is same as for list box; they should really be derived from 
// common base class to avoid duplicate code, but I was lazy.
// 
void WPComboBox::setList(WPListData *l, int selected, BOOL redraw)
{
	if ((list = l) != NULL) {
		reset();					// erase contents
		char buf[80];
		setReDraw(FALSE);
		for (BOOL more = list->firstItem(); more; more=list->nextItem()) {
			DWORD data = list->getItemText(buf, sizeof(buf));
			int item = append(buf);
			if (item!=LB_ERR)
				setItemData(item, data);
		}
		setReDraw(TRUE);
		if (redraw)
			invalidate();
	}
	setSel(selected);
}

//////////////////
// Handle scrollbar message.
// 
void WPScrollBar::handleMsg(int msg, int thumbPos)
{
	int pos = scrollPos();
	switch (msg) {
	case SB_LINEUP:
		pos -= lineIncr;
		break;
	case SB_LINEDOWN:
		pos += lineIncr;
		break;
	case SB_PAGEUP:
		pos -= pageIncr;
		break;
	case SB_PAGEDOWN:
		pos += pageIncr;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		pos = thumbPos;
		break;
	}
	scrollPos(pos);
}

//////////////////
// Use GDI functions to update screen for a static icon.
// 
void WPStaticIcon::updateScreen()
{
	if (object) {
		WPWinDC dc = this;
		dc.drawIcon(0, 0, (HICON)object);
	}
}
