// ScreenSaverDlg.cpp : implementation file
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//

#include "StdAfx.h"

#include "ScreenSaverWnd.h"
#include "ScreenSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CScreenSaverDlg, CDialog)

// MFC's normal processing would have CDialog and CWnd handle any messages
// not handled by the CScreenSaverDlg.  Some are not appropriate for a
// screen saver's configuration dialog, so we skip CDialog and CWnd in the
// line below, and have all unhandled messages go to the CCmdTarget.
// The WindowProc() below will forward the reasonable messages to CDialog.
//
BEGIN_MESSAGE_MAP(CScreenSaverDlg, CCmdTarget)
	//{{AFX_MSG_MAP(CScreenSaverDlg)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

// There should be only one CScreenSaverDlg instantiated at a time.
// The helper function AfxGetScreenSaverDlg() returns this pointer.
//
/* static */ CScreenSaverDlg* CScreenSaverDlg::sm_pTheConfigureDialog = NULL;

CScreenSaverDlg::CScreenSaverDlg()
{
	ASSERT(!sm_pTheConfigureDialog);
	sm_pTheConfigureDialog = this;
}

CScreenSaverDlg::~CScreenSaverDlg()
{
	sm_pTheConfigureDialog = NULL;
}

/////////////////////////////////////////////////////////////////////////////

void CScreenSaverDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();
}

BOOL CScreenSaverDlg::OnInitDialog()
{
	if (AfxGetScreenSaverWnd())
		AfxGetScreenSaverWnd()->RestoreOptions();

	return CDialog::OnInitDialog();
}

int CScreenSaverDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifdef _DEBUG
	// Screen savers should be TOPMOST to block out any other windows,
	// such as other topmost windows created previously.  However, if you
	// are trying to debug a screen saver, it can get in the way.
	// We remove the topmost status from this window only if we're _DEBUG.
	// 
	SetWindowPos(&CWnd::wndNoTopMost,
		0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif

	return 0;
}

/////////////////////////////////////////////////////////////////////////////

//
// The default message routing is not built to deal with screen saver
// dialogs.  This avoids the default dialog proc from handling anything we
// don't handle.
//

LRESULT CScreenSaverDlg::WindowProc(UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
	return CDialog::WindowProc(uMsg, wParam, lParam);
}

LRESULT CScreenSaverDlg::DefWindowProc(UINT uMsg,
                                       WPARAM wParam,
                                       LPARAM lParam)
{
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////

// ::ScreenSaverConfigureDialog():
// This API must be exported to be recognized as a configurable screen
// saver.  This serves as the dialog message proc called by Windows to
// display the configuration dialog for the screen saver.  Not all messages
// that go to the dialog actually get sent to our proc.
//
BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg,
                                       WPARAM wParam, LPARAM lParam)
{

	// There should be one global instance of a CScreenSaverDlg derivative.
	ASSERT(AfxGetScreenSaverDialog());
	if (!AfxGetScreenSaverDialog())
		return 0L;

	if (!AfxGetScreenSaverDialog()->m_hWnd)
		AfxGetScreenSaverDialog()->Attach(hDlg);

	// MFC does a lot of helpful but nonstandard things with WM_INITDIALOG.
	//
	// Since a screen saver's configuration dialog proc is dictated to us,
	// we need to manually perform the ->OnInitDialog() call ourselves.
	//
	// This is equivalent to MFC4.2's ::AfxDlgProc() [which is not exported
	// nor used by the sanctioned exported public ::AfxCallWndProc()
	// function].
	//
	LRESULT lResult;
	if (uMsg == WM_INITDIALOG)
	{
		// special case for WM_INITDIALOG
		CDialog* pDlg =
			DYNAMIC_DOWNCAST(CDialog,
				CWnd::FromHandlePermanent(hDlg));
		if (pDlg != NULL)
			lResult = pDlg->OnInitDialog();
		else
			lResult = 1;
	}
	else
	{
		lResult =
			AfxCallWndProc(
				AfxGetScreenSaverDialog(),
				AfxGetScreenSaverDialog()->m_hWnd,
		        uMsg, wParam, lParam);
	}

	if (uMsg == WM_NCDESTROY)
	{
		ASSERT(!AfxGetScreenSaverDialog() ||
		       !AfxGetScreenSaverDialog()->m_hWnd);
	}

	return lResult;
}

// ::RegisterDialogClasses():
// This API must be exported to be recognized as a configurable screen
// saver.  It is called upon startup to register any WNDCLASS structures
// that would later be necessary to display a configuration dialog.
//
BOOL WINAPI RegisterDialogClasses(HANDLE hInstance)
{
	// We rely on the default registered window class used by MFC
	// dialogs.  Therefore, we have nothing to do here.
	//
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
