#include "stdafx.h"
#include "App.h"
#include "MessageBoxX.h"
#include "MessageBoxDlg.h"

#ifdef CMESSAGEBOXX_HTML_SUPPORT
#ifndef QHTM_H
#include <qhtm.h> //If you get a compilation error on this line, then you need to download, install and possible purchase a license for QHTM (http://www.gipsysoft.com/qhtm/)
#endif
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMessageBoxApp, CWinApp)
END_MESSAGE_MAP()

CMessageBoxApp::CMessageBoxApp()
{
}

CMessageBoxApp theApp;

BOOL CMessageBoxApp::InitInstance()
{
#ifdef CMESSAGEBOXX_HTML_SUPPORT
  if (!QHTM_Initialize(AfxGetInstanceHandle()))
  {
    CString sMsg;
    sMsg.Format(_T("Failed to initialize QHTM, Error:%d"), ::GetLastError());
    AfxMessageBox(sMsg, MB_OK | MB_ICONSTOP);
    return FALSE;
  }
#endif

  {
    CMessageBoxX msg(_T("This is the Text"));
    //msg.DoModal();

    CMessageBoxX msg2(IDS_STRING3, NULL, MB_YESNO);
    //msg2.DoModal();

    CMessageBoxX msg3(_T(""), NULL, MB_ABORTRETRYIGNORE);
    msg3.SetText(IDS_STRING4, _T("Replacement"), 25);
    msg3.SetCaption(IDS_STRING5, _T("Replacement"));
    //msg3.DoModal();

    CMessageBoxX msg4(_T(""));
    msg4.SetText(IDS_STRING6, _T("Replacement 1"), _T("Replacement 2"), 23);
    msg4.SetCaption(IDS_STRING7, _T("Replacement 1"), _T("Replacement 2"));
    msg4.SetUserIcon(IDR_MAINFRAME);
    //msg4.DoModal();

    CMessageBoxX msg5(IDS_STRING3, NULL, MB_YESNO, NULL, IDS_STRING3);
    msg5.SetCaption(IDS_STRING3);
    msg5.SetCaption(_T("A Caption"));
    msg5.SetParent((CWnd*) NULL);
    msg5.SetParent((HWND) NULL);
    msg5.SetParent((CWnd*) CWnd::GetDesktopWindow());
    msg5.SetParent((HWND) GetDesktopWindow());
    //msg5.DoModal();

    CMessageBoxX msg6(_T("This message box should time out to OK in 15 seconds"), NULL, MB_OKCANCEL);
    msg6.SetTimeout(15, IDOK);
    //int nResponse = msg6.DoModal();

    CMessageBoxX msg7(_T("This message box should have a disabled ok button for 5 seconds"), NULL, MB_OK);
    msg7.SetDisabledButton(5, 2);
    //nResponse = msg7.DoModal();

    CMessageBoxX msg8(_T("This message box should have a disabled ok button for 5 seconds"), NULL, MB_OKCANCEL);
    msg8.SetDisabledButton(5, IDOK);
    //int nResponse = msg8.DoModal();

    CMessageBoxX msg9(_T("This message box should have a disabled cancel button for 5 seconds"), NULL, MB_OKCANCEL);
    msg9.SetDisabledButton(5, IDCANCEL);
    //nResponse = msg9.DoModal();

    CMessageBoxX msg10(_T("This message box should have a disabled cancel button for 5 seconds and should timeout in 8 seconds"), NULL, MB_OKCANCEL);
    msg10.SetDisabledButton(5, IDCANCEL);
    msg10.SetTimeout(8, IDCANCEL);
    //nResponse = msg10.DoModal();

    CMessageBoxDlg mainDlg;
    m_pMainWnd = &mainDlg;
    mainDlg.DoModal();
  }

	return FALSE;
}
