//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: MEDIT.CPP
//
// Multi-file editor.

#include "prefix.h"

MyApp myApp; // instantiate one and only app

//////////////////
// Main edit window class--almost identical to WINEDIT.
// 
class EditWin : public WPMDIChild {
	WPMultiEdit *editCtl;	// main edit window
protected:
	BOOL gotFocus(WPWin *prev)
		{ editCtl->setFocus(); return FALSE; }
public:
	EditWin(WPMDIFrame *frame, LPCSTR fname=NULL);
	BOOL sized(WPRect &box, WORD how) 
		{ editCtl->moveWin(box); return FALSE; }

	// File command functions
	BOOL fileIsModified()			{ return editCtl->isModified(); }
	void fileIsModified(BOOL m)	{ editCtl->setModified(m); }
	BOOL fileOpen(LPCSTR fname)		{ return editCtl->load(fname); }
	BOOL fileSave(LPCSTR fname)		{ return editCtl->save(fname); }
	BOOL filePrint(WPDlgPrint &pdlg);
	BOOL filePrintDlg(WPDlgPrint &pdlg);
	BOOL fileNew()						
		{ editCtl->setSel(); editCtl->clear(); return TRUE; }

	// Edit command functions
	BOOL editCut()			{ editCtl->cut(); return TRUE; }
	BOOL editCopy()		{ editCtl->copy(); return TRUE; }
	BOOL editPaste()		{ editCtl->paste(); return TRUE; }
	BOOL editDelete()		{ editCtl->clear(); return TRUE; }
	BOOL editUndo()		{ editCtl->undo(); return TRUE; }
	BOOL canPaste()		{ return Clipboard.available(CF_TEXT); }
	BOOL canUndo()			{ return editCtl->canUndo(); }
	BOOL anySelected()
		{ int beg,end; editCtl->getSel(beg, end); return beg!=end; }
};

//////////////////
// Create new edit window (as MDI child).
// 
EditWin::EditWin(WPMDIFrame *pwin, LPCSTR fname) : WPMDIChild("EDITWIN", pwin)
{
	createArgs.style &= ~WS_VISIBLE;
	createWin();				// create this window

	// Create multi-line edit control
	editCtl = new WPMultiEdit(this, -1);
	createArgs.pos = this;
	createArgs.style |= 
		ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL;
	editCtl->createWin();

	fileInit(fname,"");
	show(pwin->numMDIChildren()==1 ? SW_SHOWMAXIMIZED : SW_SHOW);
	setFocus();
}

//////////////////
// Print the file. Should really check pdlg for num copies, etc.
// 
BOOL EditWin::filePrint(WPDlgPrint &pdlg)
{
	WPLinePrinter p(pdlg);
	p.doAbortDlg(this);
	p.startDoc(fileName());

	char *line = theApp->scratch;
	int nlines = editCtl->numLines();
	for (int i=0; i < nlines && !p.aborted(); i++) {
		int len = editCtl->getLine(i, line, 256);
		p.outLine(line, len);
	}
	p.endDoc();
	return TRUE;
}

//////////////////
// Initialize print dialog
//
BOOL EditWin::filePrintDlg(WPDlgPrint &pdlg)
{
	pdlg.pdlg.Flags |= PD_NOSELECTION | PD_HIDEPRINTTOFILE;
	return TRUE;
}

//////////////////
// Main (MDI Frame) window class.
// 
class EditFrame : public WPMDIFrame {
	int pmtHeight;				// height of prompt line
public:
	EditFrame(LPCSTR fname=NULL);
	BOOL sized(WPRect &box, WORD how);
	BOOL fileOpen(LPCSTR fname)	{ new EditWin(this, fname); return TRUE; }
	BOOL fileNew()					{ new EditWin(this); return TRUE; }
	int getMenuPrompt(char* buf, int id, WORD flags)
		{ return id ? theApp->loadString(id, buf, MAXPROMPTLEN) : 0; }
};

//////////////////
// Initialize main window.
// 
EditFrame::EditFrame(LPCSTR fname) : WPMDIFrame(2 /* "Window" menu pos*/ )
{
	createArgs.style |= CS_DBLCLKS;
	WPWin::createWin("MEDIT");	// create main window

	// Create prompt line
	promptWin = new WPStatic(this, -1);
	createArgs.style |= WS_BORDER;
	promptWin->createWin();
	pmtHeight = tm.tmHeight;

	if (fname && *fname)
		fileOpen(fname);
}

//////////////////
// Main window was re-sized
// 
BOOL EditFrame::sized(WPRect &box, WORD how)
{
	// Adjust client window
	box.height(box.height()-pmtHeight);
	clientWin()->moveWin(box);

	// Adjust prompt line
	WPRect pmtbox;
	pmtbox.origin(0, box.height());
	pmtbox.extent(box.width(), pmtHeight);
	promptWin->moveWin(pmtbox);
	return TRUE;
}

//////////////////
// Main entry point.  Command line argument is name of file to open
// 
void MyApp::main()
{
	char fname[80];
	getCmdLine(fname);
	mainWin = new EditFrame(fname);
	run();
}
