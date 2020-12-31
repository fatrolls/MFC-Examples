// =================================================================
//  File:  QuickMailer.h
//
//  Purpose:
//
//      Ultimate TCP/IP Quick Mailer ver 1.0
//      Quickly prepare and send e-mail messages.
//
// =================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#ifndef __QUICKMAILER_H__INCLUDED
#define __QUICKMAILER_H__INCLUDED

#include "resource.h"

#pragma warning ( push,3 )
#include <list> 
#pragma warning ( pop )
#pragma warning ( push,3 )
#pragma warning ( disable : 4018 )
#include <string>
#pragma warning ( pop )
#include "smtp_c.h"
#include "MXLookup.h"

using namespace std;

#define WM_TASKBAR_ICON_NOTIFY          WM_USER + 1000
#define ID_TASKBAR_ICON_QUICK_MAILER    1

// *** Variables decloration ***
UINT        nTimerID        = 0;        // Timer ID
BOOL        bAboutSplash    = TRUE;     // About box splash mode flag
BOOL        bIsHidden       = FALSE;    // Main dialog is hidden flag
BOOL        bMoved          = TRUE;     // Main dialog moved flag
BOOL        bEditMode       = FALSE;    // Recipient edit mode flag
HINSTANCE   hInst;                      // Copy of programs instance
_TCHAR      szSendFrom[100] = {_T("")};     // Send from string
_TCHAR      szHost[100]     = {_T("")};     // SMTP mail server name
_TCHAR      szLastSubjects[10][200];    // Array of 10 last used subjects
DWORD       dwRunAtStartUp  = 0;        // Run at start up flag
UINT        nSubjCount      = 0;        // Number of items in the subjects array
HWND        hwndMainDlg;                // Main dialog handle
WNDPROC     lpPrevListFunc;             // Pointer to the old list control wnd. procedure
RECT        rectMainDlg;                // Main Dialog rect


// *** Dialog box procedures ***
BOOL CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MainProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AddMailRecipientProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK PropertiesProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK NameListProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SendProc(HWND, UINT, WPARAM, LPARAM);

// *** Helper functions ***

// Gets task bar edge
UINT GetTaskBarEdge(RECT rc);

// Executes task bar icon command
void TaskBarIcon(HWND hwndWnd, DWORD dwCmd);

// Runs menu
void RunMenu(HWND hWnd, UINT idMenu, UINT uFlags, int x, int y);

// Checks if any name in the list box is selected
BOOL IsNameSelected();

// Sends mail
int  SendMail(HWND);

// Loads data from registry
void LoadData();

// Saves data into registry
void SaveData();

// Adds new subject to the array of last used subjects
void AddSubject(LPCTSTR lpszSubject);

// Shows main dialog window
void ShowMainDlg(BOOL bState);



// Recipient data structure
typedef struct {    
    _TCHAR    szName[100];        // Name
    _TCHAR    szAddress[MAX_PATH];    // E-mail address
} RecipientData;

typedef list<RecipientData> RECIPIENTDATALIST;

// Name & address data list
RECIPIENTDATALIST   RecipientDataList;
RecipientData       EditCancelData;         

#endif // __QUICKMAILER_H__INCLUDED

