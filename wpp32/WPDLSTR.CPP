//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLSTR.CPP
//
// String dialog implementation.

#include "wpp.h"

//////////////////
// Use byte-alignment when compiling this
// module--required for DLGTEMPLATE & co.
// 
#ifdef _MSC_VER
#pragma pack (1)
#elif defined(__BORLANDC__)
#pragma option -a-
#endif

//////////////////
// Align ptr to DWORD
//
WORD* lpwAlign (WORD* lpIn)
{
  ULONG ul = (ULONG) lpIn;
  ul +=3;
  ul >>=2;
  ul <<=2;
  return (WORD*) ul;
}

////////////////
// Helper routine.  Takes second parameter as Ansi string, copies
// it to first parameter as wide character (16-bits / char) string,
// and returns integer number of wide characters (words) in string
// (including the trailing wide char NULL).
//
int nCopyAnsiToWideChar (LPWORD lpWCStr, LPCSTR lpAnsiIn)
{
  int nChar = 0;
  do {
    *lpWCStr++ = (WORD) *lpAnsiIn;
    nChar++;
  } while (*lpAnsiIn++);
  return nChar;
}

struct DLGTEMPLATETRAILER {
	WORD dlgMenu;
	WORD dlgClass;
	WORD dlgTitle[1];
};

/////////////////
// trailer for dialog items
//
struct DLGITEMTEMPLATETRAILER {
	WORD itemClass[2];	// class atom identifier
	WORD itemTitle[1];	// title (string)
};

// Windows predefined atom names
#define ATOM_BUTTON	0x0080
#define ATOM_EDIT		0x0081
#define ATOM_STATIC	0x0082

//////
// Static definition of dialog box.
// These structures are copied and filled in with
// the necessary variables, e.g., prompt and width, etc.
// 

// First, a few constants to make the code more legible
#define CXBUTTON 30		// width of button
#define CXEDIT   150		// width of edit control
#define CYITEM   13		// height of button or edit control
#define CYSPACE  5		// interline space
#define XMARGIN  5

//////////////////
// Here are the static structures.  Ugh!
// 
static DLGTEMPLATE DlgTemplate = {	
	WS_POPUPWINDOW|DS_MODALFRAME|WS_DLGFRAME, 0, 4, 40, 80, 0, 55
};
static DLGITEMTEMPLATE ItemPrompt = {
	WS_VISIBLE|WS_CHILD|SS_LEFT, 0, XMARGIN, CYSPACE, 0, 8, (WORD)-1
};

static DLGITEMTEMPLATE ItemInput = {
	WS_VISIBLE|WS_CHILD|WS_TABSTOP|WS_BORDER|ES_LEFT|ES_AUTOHSCROLL, 0,
	XMARGIN, 16, CXEDIT, CYITEM, WPIDED_STRING,
};

static DLGITEMTEMPLATE ItemOK = {
	WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_DEFPUSHBUTTON, 0,
	0, 35, CXBUTTON, CYITEM, IDOK
};

static DLGITEMTEMPLATE ItemCancel = {
	WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON, 0,
	0, 35, CXBUTTON, CYITEM, IDCANCEL,
};

//////////////////
// Set caption in dialog template, and return ptr to end
// of header, which is first item template structure.
// 
static DLGITEMTEMPLATE * setDlgCaption(DLGTEMPLATE* pDlg, LPCSTR text)
{
	DLGTEMPLATETRAILER* pt = (DLGTEMPLATETRAILER*)(pDlg+1);
	pt->dlgMenu = 0;
	pt->dlgClass = 0;
	if (!text) 
		text = "";
	WORD* wp = pt->dlgTitle;
	wp += nCopyAnsiToWideChar (wp, text);
	return (DLGITEMTEMPLATE *)lpwAlign(wp);
}

//////////////////
// Set item text.  Returns pointer to next item following this one.
// 
static DLGITEMTEMPLATE* setItemTypeText(DLGITEMTEMPLATE * pItem, 
	WORD iclass, LPCSTR text)
{
	DLGITEMTEMPLATETRAILER* pt = (DLGITEMTEMPLATETRAILER*)(pItem+1);
	pt->itemClass[0] = 0xFFFF;				 // next is atom
	pt->itemClass[1] = iclass;				 // atom identifier

	if (!text) 
		text = "";
	WORD* wp = pt->itemTitle;
	wp += nCopyAnsiToWideChar (wp, text);
	*wp++  = 0;									 // no extra stuff
	return (DLGITEMTEMPLATE *)lpwAlign(wp);
}

//////////////////			
// Create string dialog and run it.
// caller's buffer will be stuffed w/user's input.
// Create dialog box on the fly (Probably the most disgusting 
// function in all of Windows++!).
// 
WPDlgString::WPDlgString(WPWin *pwin, char *buf, int len, 
	LPCSTR pmt, LPCSTR cap) : WPDialogModal(NULL, pwin)
{
	assert(buf && pmt);
	strBuf = buf;
	strLen = len;
	if (cap==NULL)
		cap = "";

	// Create dialog template header.  Build it in App.scratch.
	DLGTEMPLATE *hdr = (DLGTEMPLATE *)theApp->scratch;
	memcpy(hdr, &DlgTemplate,  sizeof(DlgTemplate));

	WPRect box = pmt;					// get text dimensions of prompt
	int pmtHt = 8*box.height();	// convert height to dialog units

	// Compute size and position of dialog box.
	hdr->cx = max(4*box.width(), CXEDIT) + 2*XMARGIN;
	hdr->cy = 3*CYITEM + CYSPACE + pmtHt;

	// Center dialog box in parent window
	box = pwin;				// dimensions of parent window
	hdr->x = (2*box.width())/LOWORD(GetDialogBaseUnits()) - (hdr->cx)/2;
	hdr->y = (4*box.height())/HIWORD(GetDialogBaseUnits()) - (hdr->cy)/2;

	// Create static text control for prompt.
	DLGITEMTEMPLATE *item = setDlgCaption(hdr, cap);
	memcpy(item, &ItemPrompt,  sizeof(ItemPrompt));
	item->cx = hdr->cx-XMARGIN;
	item->cy = pmtHt;
	item = setItemTypeText(item, ATOM_STATIC, pmt);

	// Create edit control for input.
	memcpy(item, &ItemInput,  sizeof(ItemInput));
	item->y = pmtHt + 2*CYSPACE;
	item = setItemTypeText(item, ATOM_EDIT, NULL);

	// Create OK button.
	memcpy(item, &ItemOK,  sizeof(ItemOK));
	int xOK = (hdr->cx - 3*CXBUTTON)/2;
	item->x = xOK;
	item->y = pmtHt + CYITEM + 3*CYSPACE;
	item = setItemTypeText(item, ATOM_BUTTON, "&OK");

	// Create Cancel button.
	memcpy(item, &ItemCancel,  sizeof(ItemCancel));
	item->x = xOK + 2*CXBUTTON;
	item->y = pmtHt + CYITEM + 3*CYSPACE;
	item = setItemTypeText(item, ATOM_BUTTON, "&Cancel");

	int size = ((char*)item) - theApp->scratch;
	memTemplate = (DLGTEMPLATE*)new char [size]; 
	memcpy(memTemplate, theApp->scratch, size);

	createWin();				// run the dialog!
}

//////////////////
// Create string dialog. 
// If we're doing it on-the-fly with DLGTEMPLATE, create using 
// DialogBoxIndirect; otherwise invoke normal createWin function.
// 
BOOL WPDlgString::createWin()
{
	// Run the dialog.
	result = DialogBoxIndirect(theApp->getHinst(), 
		memTemplate,
		GetHwnd(createArgs.parent), 
		theApp->getDlgProc());
	assert(result!=-1);
	return result != -1;
}

//////////////////
// Destroy string dialog: destory memory template
// 
WPDlgString::~WPDlgString()
{
	delete [] (char*)memTemplate;
}

//////////////////
// Initialize dialog: link edit control to caller's string.
// 
void WPDlgString::initDlg()
{
	WPEdit * ed = new WPEdit(this, WPIDED_STRING);
	ed->linkObject(strBuf, strLen);
}
