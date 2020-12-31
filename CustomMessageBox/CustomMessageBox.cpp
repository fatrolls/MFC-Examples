// CustomMessageBox.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CustomMessageBox.h"
#include "CustomMessageBoxDlg.h"
#include ".\custommessagebox.h"
#include "afxpriv.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomMessageBoxApp

BEGIN_MESSAGE_MAP(CCustomMessageBoxApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCustomMessageBoxApp construction

CCustomMessageBoxApp::CCustomMessageBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCustomMessageBoxApp object

CCustomMessageBoxApp theApp;


// CCustomMessageBoxApp initialization

BOOL CCustomMessageBoxApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CCustomMessageBoxDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CCustomMessageBoxApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{

	// disable windows for modal dialog
	EnableModeless(FALSE);
	HWND hWndTop;
	HWND hWnd = CWnd::GetSafeOwner_(NULL, &hWndTop);

	// WINBUG: re-enable the parent window, so that focus is restored 
	// correctly when the dialog is dismissed.
	if (hWnd != hWndTop)
		EnableWindow(hWnd, TRUE);

	// set help context if possible
	DWORD* pdwContext = NULL;
	if (hWnd != NULL)
	{
		// use app-level context or frame level context
		LRESULT lResult = ::SendMessage(hWnd, WM_HELPPROMPTADDR, 0, 0);
		if (lResult != 0)
			pdwContext = (DWORD*)lResult;
	}
	// for backward compatibility use app context if possible
	if (pdwContext == NULL && this != NULL)
		pdwContext = &m_dwPromptContext;

	DWORD dwOldPromptContext = 0;
	if (pdwContext != NULL)
	{
		// save old prompt context for restoration later
		dwOldPromptContext = *pdwContext;
		if (nIDPrompt != 0)
			*pdwContext = HID_BASE_PROMPT+nIDPrompt;
	}

	// determine icon based on type specified
	if ((nType & MB_ICONMASK) == 0)
	{
		switch (nType & MB_TYPEMASK)
		{
		case MB_OK:
		case MB_OKCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_YESNO:
		case MB_YESNOCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_ABORTRETRYIGNORE:
		case MB_RETRYCANCEL:
			// No default icon for these types, since they are rarely used.
			// The caller should specify the icon.
			break;
		}
	}

#ifdef _DEBUG
	if ((nType & MB_ICONMASK) == 0)
		TRACE(traceAppMsg, 0, "Warning: no icon specified for message box.\n");
#endif

	TCHAR szAppName[_MAX_PATH];
	szAppName[0] = '\0';
	LPCTSTR pszAppName;
	if (this != NULL)
		pszAppName = m_pszAppName;
	else
	{
		pszAppName = szAppName;
		DWORD dwLen = GetModuleFileName(NULL, szAppName, _MAX_PATH);
		if (dwLen == _MAX_PATH)
			szAppName[_MAX_PATH - 1] = '\0';
	}

	int nResult=CBTMessageBox(hWnd,LPSTR(lpszPrompt),LPSTR(pszAppName),nType);

	// restore prompt context if possible
	if (pdwContext != NULL)
		*pdwContext = dwOldPromptContext;

	// re-enable windows
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	EnableModeless(TRUE);

	return nResult;
}

HHOOK hhk;

INT CBTMessageBox(HWND hwnd, LPSTR lpText, LPSTR lpCaption,UINT uType)
{
  hhk = SetWindowsHookEx(WH_CBT, &CBTProc, 0,
                         GetCurrentThreadId());
  return MessageBox(hwnd, lpText, lpCaption, uType);
}

LRESULT CALLBACK CBTProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
  HWND  hChildWnd;    // msgbox is "child"
  CString s=_T("");
  // notification that a window is about to be activated
  // window handle is wParam
  if (nCode == HCBT_ACTIVATE)
  {
    // set window handles
    hChildWnd  = (HWND)wParam;
  	//to get the text of yes button
	UINT result;
    if(GetDlgItem(hChildWnd,IDYES)!=NULL)
	{
	 s.LoadString(IDS_Yes);
     result= SetDlgItemText(hChildWnd,IDYES,s);
	}
    if(GetDlgItem(hChildWnd,IDOK)!=NULL)
	{
	 s.LoadString(IDS_OK);
     result= SetDlgItemText(hChildWnd,IDOK,s);
	}
    // exit CBT hook
    UnhookWindowsHookEx(hhk);
  }
  // otherwise, continue with any possible chained hooks
  else CallNextHookEx(hhk, nCode, wParam, lParam);
  return 0;
}
