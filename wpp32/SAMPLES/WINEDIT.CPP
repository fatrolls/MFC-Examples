//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WINEDIT.CPP 
// 
// Single file editor.

#include "prefix.h"

MyApp myApp; // instantiate one and only app

//////////////////
// Main edit window class.
// 
class EditWin : public WPMainWin {
	WPMultiEdit *editCtl;	// main edit window
	int pmtHeight;				// height of prompt line font
public:
	EditWin(LPCSTR fname=NULL);

	// Virtual message functions
	BOOL sized(WPRect &box, WORD how);
	BOOL gotFocus(WPWin *prev)		{ editCtl->setFocus(); return FALSE; }

	int getMenuPrompt(char* buf, int id, WORD flags)
		{ return id ? theApp->loadString(id, buf, MAXPROMPTLEN) : 0; }

	// File command functions
	BOOL fileIsModified()			{ return editCtl->isModified(); }
	void fileIsModified(BOOL m)	{ editCtl->setModified(m); }
	BOOL fileOpen(LPCSTR fname)		{ return editCtl->load(fname); }
	BOOL fileSave(LPCSTR fname)		{ return editCtl->save(fname); }
	BOOL fileNew()						
		{ editCtl->setSel(); editCtl->clear(); return TRUE; }
	BOOL filePrint(WPDlgPrint &pdlg);
	BOOL filePrintDlg(WPDlgPrint &pdlg);

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
// Main entry point.  Command line argument is name of file to open
// 
void MyApp::main()
{
	char fname[80];
	getCmdLine(fname);
	mainWin = new EditWin(fname);
	run();
}

//////////////////
// Initialize main window.
// 
EditWin::EditWin(LPCSTR fname)
{
	createWin();				// create main window

	// Create edit control
	editCtl = new WPMultiEdit(this, 1);
	createArgs.style |= WS_VSCROLL;
	editCtl->createWin();

	// Create prompt line
	promptWin = new WPStatic(this, 2);
	promptWin->createWin();
	pmtHeight = tm.tmHeight;

	fileInit(fname, "WINEDIT");
}

//////////////////
// Main window was re-sized
// 
BOOL EditWin::sized(WPRect &box, WORD how)
{
	// Adjust edit control
	box.height(box.height()-pmtHeight);
	editCtl->moveWin(box);

	// Adjust prompt line
	WPRect pmtbox;
	pmtbox.origin(0, box.height());
	pmtbox.extent(box.width(), pmtHeight);
	promptWin->moveWin(pmtbox);

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
