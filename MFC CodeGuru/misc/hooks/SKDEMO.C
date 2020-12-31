/******************************************************************************
Module name: SKDemo.c
Purpose: Demonstrates using a dialog box for an application's main window
******************************************************************************/


#include "Win95ADG.h"          /* See Appendix A for details. */
#include <windows.h>
#include <windowsx.h>
#include <string.h>
#pragma warning(disable: 4001)    /* Single-line comment */
#include ".\hookDLL\hookDLL.h"
#include "resource.h"

#define MYWM_NOTIFYICON		(WM_APP+100)

HICON hMyIcon			= NULL;			// Handle for tray icon
HWND g_hwndLastSubject	= NULL;			// Handle for last peered window.


/////////////////////////////////////////////////////////////////////////////
// Prototype of function
void SKDemo_DrawWindowFrame (HWND hwndSubject)
{
   HDC hdc;
   RECT rc;
   HPEN hpen;
   
   // Retrieve location of window on-screen.
   GetWindowRect(hwndSubject, &rc);

   // Get a device context that allows us to write anywhere within the window.
   // NOTE: GetDC would allow us to write only in the window's client area.
   hdc = GetWindowDC(hwndSubject);

   // Save the original device context attributes.
   SaveDC(hdc);
   
   // To guarantee that the frame will be visible, tell Windows to draw the
   // frame using the inverse screen color.
   SetROP2(hdc, R2_NOT);

   // Create a pen that is three times the width of a nonsizeable border. The
   // color will not be used to draw the frame, so its value could be
   // anything. PS_INSIDEFRAME tells windows that the entire frame should be
   // enclosed within the window.
   hpen = CreatePen(PS_INSIDEFRAME, 3 * GetSystemMetrics(SM_CXBORDER),
      RGB(0, 0, 0));
   SelectObject(hdc, hpen);

   // We must select a NULL brush so that the contents of the window will not
   // be overwritten.
   SelectObject(hdc, GetStockObject(NULL_BRUSH));

   // Draw the frame. Because the device context is relative to the window,
   // the top-left corner is (0, 0) and the lower right corner is (width of
   // window, height of window).
   Rectangle(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top);

   // Restore the original attributes and release the device context.
   RestoreDC(hdc, -1);
   ReleaseDC(hwndSubject, hdc);

   // We can destroy the pen only AFTER we have restored the DC because the DC 
   // must have valid objects selected into it at all times.
   DeleteObject(hpen);
}

///////////////////////////////////////////////////////////////////////////////
void SKDemo_UpdateWindowInfo (HWND hwndDlg, HWND hwndSubject)
{
	HWND hwndEdit = GetDlgItem(hwndDlg, IDC_TARGET_WNDCLASSNAME_EDIT);
	char  szClassName[20];
	
	GetClassName(hwndSubject, szClassName, sizeof(szClassName));
	Edit_SetText(hwndEdit, szClassName);
}
			
///////////////////////////////////////////////////////////////////////////////
void SKDemo_OnRButtonDown (HWND hwnd, BOOL fDbClk, int x, int y, UINT keyFlags)
{
	 BOOL fSW = FALSE;
	 BOOL fTW = FALSE;
	
     // When the user clicks the right mouse button over dialog,
     // check whether there is a radio button being checked, if not, do 
	 // nothing, if there is, go on.
	 
	 // When the user clicks the right mouse button over dialog,
     // the system notifies the parent window by sending the
     // WM_PARENTNOTIFY message. Once here, we enter "peer" mode.
    
     // Send Voyeur's window to the back of the window manager's list.
     // This causes any windows that Voyeur overlaps to become
     // visible, allowing these windows to be "peered" into.
     SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

     // Force all mouse messages to come to this window.
     SetCapture(hwnd);

     // Change the mouse cursor to eyes. This provides a visual indication
     // to the user that Voyeur is "peering."
     SetCursor(LoadCursor(GetWindowInstance(hwnd),
        MAKEINTRESOURCE(IDC_EYES)));

     // Set the window handle of the last viewed window to NULL.
	 g_hwndLastSubject = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void SKDemo_OnMouseMove (HWND hwnd, int x, int y, UINT keyFlags) 
{

   // We must have mouse capture or we would never get here because the edit
   // child window always covers our entire client area.

   // Get the current mouse position in screen coordinates. NOTE: We cannot
   // use the x and y parameters because they are relative to the window's
   // client area.
   DWORD dwMousePos = GetMessagePos();
   POINT ptMouse;
   HWND hwndSubject; 

   // Get the handle of the window under the mouse cursor.
   ptMouse.x = LOWORD(dwMousePos);
   ptMouse.y = HIWORD(dwMousePos);
   hwndSubject = WindowFromPoint(ptMouse);
   
   // If the window is created by us, ignore it.
   if (GetWindowThreadProcessId(hwndSubject, NULL) == GetCurrentThreadId())
      return;
   
   // If our new subject is the same as our last subject, there is no need to
   // update our display.
   if (g_hwndLastSubject == hwndSubject)
      return;

   // Remove the frame, if any, around the currently selected window.
   if (g_hwndLastSubject != NULL)
      SKDemo_DrawWindowFrame(g_hwndLastSubject);

   // Draw a frame around our new window.
   SKDemo_DrawWindowFrame(hwndSubject);

   // Update the window's information. This function is in VoyHelp.C.
   SKDemo_UpdateWindowInfo(hwnd, hwndSubject);

   // Save the handle to the most recent subject window.
   g_hwndLastSubject = hwndSubject;
}


///////////////////////////////////////////////////////////////////////////////

void SKDemo_OnCaptureChanged (HWND hwnd, HWND hwndNewCapture) 
{
   // If we don't "peer" into a window, we don't have to remove its
   // surrounding frame.
   if (g_hwndLastSubject != NULL) 
   {
      SKDemo_DrawWindowFrame(g_hwndLastSubject);

      // Force our window to appear on top of all other windows.
      BringWindowToTop(hwnd);
   }
   g_hwndLastSubject = NULL;
}


///////////////////////////////////////////////////////////////////////////////

void SKDemo_OnRButtonUp (HWND hwnd, int x, int y, UINT keyFlags) 
{
   // We must have mouse capture or we would never get here because the edit
   // child window always covers our entire client area.

   // Allow other windows to receive mouse messages.
   ReleaseCapture();
}


/////////////////////////////////////////////////////////////////////////////////
BOOL TrayMessage(HWND hwnd, DWORD dwMessage, UINT uID, HICON hIcon)
{
    NOTIFYICONDATA tnd;
	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= hwnd;
	tnd.uID			= uID;
	tnd.uFlags		= NIF_MESSAGE|NIF_ICON;
	tnd.uCallbackMessage = MYWM_NOTIFYICON;
	tnd.hIcon		= hIcon;
	
	return (Shell_NotifyIcon(dwMessage, &tnd));

	//if (hIcon)
	//    DestroyIcon(hIcon);
}

void NotifyDelete(HWND hwnd)
{
	if(hMyIcon != NULL)
		TrayMessage(hwnd, NIM_DELETE, IDI_TRAY, hMyIcon);
}


void NotifyAdd(HWND hwnd)
{
	if(hMyIcon != NULL)
		TrayMessage(hwnd, NIM_ADD, IDI_TRAY, hMyIcon);
}

//////////////////////////////////////////////////////////////////////////////
BOOL SKDemo_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
   adgSETDLGICONS(hwnd, IDI_SKDEMO, IDI_SKDEMO);
   return(TRUE);                  // Accepts default focus window.
}


///////////////////////////////////////////////////////////////////////////////
void SKDemo_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) 
{
	char  szClassName[20];
	HWND  hwndEdit;
	
	ZeroMemory(szClassName, 20);
	switch (id) 
	{
		case IDC_BEGIN_HOOK:
			hwndEdit = GetDlgItem(hwnd, IDC_TARGET_WNDCLASSNAME_EDIT);
			Edit_GetText(hwndEdit, szClassName, 19);
			if (szClassName[0] != '\0')
			{
				if (!Hook_Start(szClassName))
				{
					adgMB(__TEXT("Unable to start thread-specific hook"));
					EndDialog(hwnd, IDCANCEL);
				}
			}
			else 
				adgMB(__TEXT("There is nothing to hook on"));
			break;

		case IDC_STOP_HOOK:
			if (!Hook_Stop())
				adgMB(__TEXT("Unable to stop thread-specific hook"));
			break;

		case IDC_HIDE:
			ShowWindow(hwnd, SW_HIDE);
			NotifyAdd(hwnd);
			break;

		case IDCANCEL:              // Allows dialog box to close.
			NotifyDelete(hwnd);
			PostQuitMessage(0);
			break;
	}   
}


///////////////////////////////////////////////////////////////////////////////


void SKDemo_OnQueueSync (HWND hwnd)
{
   adgMB(__TEXT("Got WM_QUEUESYNC message!"));
}


///////////////////////////////////////////////////////////////////////////////

        
BOOL WINAPI SKDemo_DlgProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) 
	{
		// Standard Window's messages
		adgHANDLE_DLGMSG(hwnd, WM_INITDIALOG,		SKDemo_OnInitDialog);
		adgHANDLE_DLGMSG(hwnd, WM_COMMAND,			SKDemo_OnCommand);
		adgHANDLE_DLGMSG(hwnd, WM_RBUTTONDOWN,		SKDemo_OnRButtonDown);
		adgHANDLE_DLGMSG(hwnd, WM_MOUSEMOVE,		SKDemo_OnMouseMove);
		adgHANDLE_DLGMSG(hwnd, WM_RBUTTONUP,		SKDemo_OnRButtonUp);
		adgHANDLE_DLGMSG(hwnd, WM_CAPTURECHANGED,	SKDemo_OnCaptureChanged);

		case MYWM_NOTIFYICON:
			switch (lParam)
			{
				case WM_RBUTTONDOWN:
					ShowWindow(hwnd, SW_SHOW);
					SetForegroundWindow(hwnd);	// make us come to the front
					break;

				default:
					break;
			}
			break;
	}
	return(FALSE);                 // We didn't process the message.
}


///////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain(HINSTANCE hinstExe, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow) 
{
   MSG msg;
   HWND hwnd;

   //adgWARNIFUNICODEUNDERWIN95();
	
   hMyIcon = LoadIcon(hinstExe, MAKEINTRESOURCE(IDI_TRAY));

   // Create a modeless dialog box instead of a modal dialog box because we
   // need to have more control over the message loop processing.
   hwnd = CreateDialog(hinstExe, MAKEINTRESOURCE(IDD_SKDEMO), NULL, SKDemo_DlgProc);
   adgASSERT(IsWindow(hwnd));

   // Continue to loop until a WM_QUIT message comes out of the queue.
   while (GetMessage(&msg, NULL, 0, 0)) 
   {
      // Call IsDialogMessage so that the keyboard can be used to control
      // focus in the dialog box.
      if (!IsDialogMessage(hwnd, &msg)) 
	  {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }
   
   // The application is terminating; destroy the modeless dialog box.
   DestroyWindow(hwnd);
   return(0);
}


//////////////////////////////// End of File //////////////////////////////////
