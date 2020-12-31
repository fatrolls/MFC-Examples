//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLPRT.CPP
//
// Print dialog implementation.

#include "wpp.h"

//////////////////
// Create print dialog.
// 
WPDlgPrint::WPDlgPrint(WPWin *pwin) : WPDialogModal(NULL, pwin)
{
	memset(&pdlg, 0, sizeof(pdlg));
	pdlg.lStructSize=sizeof(pdlg);
	pdlg.hwndOwner = GetHwnd(pwin);
	pdlg.Flags = PD_DEFAULT;
}

//////////////////
// Destroy print dialog. 
// Destroy stuff as described in the SDK documentation.
// 
WPDlgPrint::~WPDlgPrint()
{ 
	if (pdlg.hDevMode)
		GlobalFree(pdlg.hDevMode);
	if (pdlg.hDevNames)
		GlobalFree(pdlg.hDevNames);
	if (pdlg.hDC)
		DeleteDC(pdlg.hDC);
}

//////////////////
// Create print abort dialog. Works in conjunction w/WPPrinter.
// 
BOOL WPDlgPrintAbort::command(int id, WORD msg)
{
	if (id==IDCANCEL) {
		WPPrinter::DlgAbort = NULL; 
		WPPrinter::Abort = TRUE;
	}
	return WPDialogModeless::command(id, msg);
}
