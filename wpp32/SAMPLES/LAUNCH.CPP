//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: LAUNCH.CPP
//
// This program never registers a window class nor displays a window;
// it just goes right into the dialog.  Demonstrates how to subclass
// the File Open dialog box.  Also shows how to access WIN.INI.

#include "prefix.h"
#include <stdio.h>
#include <direct.h>

MyApp myApp; // instantiate one and only app

const IDM_SETDEBUGGER = 10;

// These keys are used to save stuff in WIN.INI
// 
LPCSTR KEYDIR= "Path";
LPCSTR KEYDEBUGSTR  = "DebugString";		 
LPCSTR KEYSCREENPOSX= "ScreenXPos";
LPCSTR KEYSCREENPOSY= "ScreenYPos";

////////////////
// The Launch dialog is a special case of the file open dialog.
// 
class Launch : public WPDlgFileOpen {
	char dirname[MAXFILENAMELEN];
	char filename[MAXFILENAMELEN];
	char debugString[30];	// debugger program; e.g., "ZDBW /2"
	WPEdit *edFileName;		// edit control for file name
	WPListBox *lbFileName;	// list box for file name
	WPStatic *ssPathName;	// static text of path name
public:	
	void initDlg();			// called for WM_INITDIALOG
	BOOL command(int id, WORD msg);
	Launch();
};

void MyApp::main()
{
	useWININI=TRUE;			// use WIN.INI for profile
	Launch dlg;					// create dialog
	dlg.run();					// ..run it
}

Launch::Launch() : WPDlgFileOpen(NULL, filename, "Launch")
{
	// Read stuff from WIN.INI
	theApp->getProfile(KEYDEBUGSTR, debugString, sizeof(debugString));
	theApp->getProfile(KEYDIR, dirname, sizeof(dirname));

	// Override default OFN data
	ofn.Flags |= OFN_SHOWHELP;
	ofn.lpstrInitialDir = dirname;	// start w/dir from WIN.INI
	ofn.lpstrTitle= "Launch";
	setFilter("EXE (*.EXE)\0*.exe\0COM (*.COM)\0*.com\0");
}

////////////////
// Initialize the dialog box.  Use screen position from WIN.INI,
// set filespec to *.exe, add command to ventilator (system) menu.
// 
void Launch::initDlg()
{
	setPos(theApp->getProfile(KEYSCREENPOSX), 
		theApp->getProfile(KEYSCREENPOSY));

	edFileName = new WPEdit		(this, IDOFN_EDFILENAME);
	lbFileName = new WPListBox (this, IDOFN_LBFILENAME);
	ssPathName = new WPStatic	(this, IDOFN_SSPATHNAME);

	// Change names of buttons
	WPButton *butn = new WPButton(this, IDOFN_PBHELP);
	butn->setText("&Debug");
	butn = new WPButton(this, IDOK);
	butn->setText("&Launch");
	butn = new WPButton(this, IDCANCEL);
	butn->setText("E&xit");

	// Add "Set Debugger" command to system menu
	WPSysMenu sm = this;
	sm.appendSep();
	sm.append(IDM_SETDEBUGGER, "Set Debugger...");
}

BOOL Launch::command(int id, WORD msg)
{
	int err;
	char wincmd[80]="";
	
	switch (id) {
	case IDOK:
	case IDOFN_PBHELP:
		edFileName->getText(filename, sizeof(filename));
		if (filename[0] == 0)					// no file name:
			lbFileName->getSel(filename);		// ..try list box

		// Execute program. Pre-pend debugger string if requested.
		if (id == IDOFN_PBHELP) {
			// pre-pend debugger string to executable file name
			strcat(wincmd, debugString);
			strcat(wincmd, " ");
		}
		strcat(wincmd, filename);
		err = WinExec(wincmd, SW_SHOWNORMAL);
		if (err==2)
			ErrBox("Can't find program \"%s\".", wincmd);
		else if (err <= 32)
			ErrBox("Error %d from WinExec",err);
		return TRUE;				// ( DON'T exit dialog )

	case IDCANCEL:
		{
		// Exit: save stuff in profile
		WPWindowRect pos = this;
		theApp->setProfile(KEYSCREENPOSX, pos.left);	// screen position
		theApp->setProfile(KEYSCREENPOSY, pos.top);		// ..
		theApp->setProfile(KEYDEBUGSTR,	debugString);	// debugger command
		ssPathName->getText(dirname, sizeof(dirname));
		theApp->setProfile(KEYDIR, dirname);
		endDlg(0);
		return TRUE;
		}

	case IDM_SETDEBUGGER:
		{
		WPDlgString dlg(this, debugString, sizeof(debugString),
			"Enter debug command:","Set Debugger");
		return TRUE;
		}
	}
	return WPDlgFileOpen::command(id, msg);
}

