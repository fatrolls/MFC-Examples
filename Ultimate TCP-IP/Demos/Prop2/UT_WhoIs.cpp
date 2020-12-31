// UT_WhoIsPage.cpp: implementation of the CUT_WhoIsPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UT_WhoIs.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )


#define HISTORY_YELLOW RGB(220,255,220)
#define HISTORY_BLACK		RGB(0,0,0)
#define HISTORY_WHITE RGB(255,255,255)

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

*/

myClient::myClient()
{
	m_parent = NULL;
}

myClient::~myClient(){
}


BOOL myClient::IsAborted() {
	return m_parent->m_bAbort;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUT_WhoIsPage::CUT_WhoIsPage(LPTSTR title):CUCPage(IDD_WHO_IS,title)
{
	m_bAbort = FALSE;
	m_HistoryCtrl.SetTimeStampFormat(_T("%c"));


}

CUT_WhoIsPage::~CUT_WhoIsPage()
{

}


void CUT_WhoIsPage::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{

	//attach the history window to the control
	m_HistoryCtrl.AttachHistoryWindow(m_hWnd,IDC_WHO_IS_HISTORY);
	//set the maximum length of the buffer of this window
	m_HistoryCtrl.SetHistoryLength(500);
	// set the font for the history window
	m_hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
	m_HistoryCtrl.SetFont(m_hFont);

	//IDC_WhoIsPage_QUERY
	//setup the controls
	SetDlgItemText(m_hWnd, IDC_WHOISSERVER,_T("whois.networksolutions.com"));
	//setup the controls
	SetDlgItemText(m_hWnd, IDC_WHOIS_QUERY,_T("Ultimate TCP/IP.com"));

	// default log file
	SetDlgItemText(m_hWnd, IDC_WHOIS_LOG_FILE,_T("session.txt"));

	// disable the file name window
	EnableWindow(GetDlgItem(m_hWnd,IDC_WHOIS_LOG_FILE),FALSE);

	m_bEnableLogChecked = FALSE;
	m_hThread = NULL;





}

void CUT_WhoIsPage::OnHelp(LPARAM lParam){


	HELPINFO hInfo = *((LPHELPINFO) lParam);    

	::WinHelp((HWND)hInfo.hItemHandle, _T("DSITools.hlp"),
		HELP_WM_HELP, (DWORD)(ULONG_PTR)(LPVOID)dwWhoIsHelpMap);


}

void CUT_WhoIsPage::OnClicked(int controlId)
{
	switch (controlId)
	{
	case IDC_WHOIS_ABOUT:
		{
			::WinHelp(m_hWnd, _T("DSITools.hlp"),
				HELP_CONTENTS,0);
			return;
		}
		// if the user clicked on the log to file check box
		//enable the log to file for the history control
	case IDC_WHOIS_ENABLE_LOOG:
		{
			if (m_bEnableLogChecked == FALSE)
				// enable the file name window
				m_bEnableLogChecked = TRUE;
			else
			{// Disable the Append to log file edit
				m_bEnableLogChecked = FALSE;
				// just disable the log
				m_HistoryCtrl.EnableLog (m_bEnableLogChecked);
			}

			EnableWindow(GetDlgItem(m_hWnd,IDC_WHOIS_LOG_FILE),m_bEnableLogChecked);
			break;
		}
	case IDC_WHO_IS_BTN:
		{
			if (m_hThread == NULL)
			{

				m_bAbort = FALSE;
				// Create a new thread
				SetDlgItemText(m_hWnd ,IDC_WHO_IS_BTN,_T("&Stop"));
				m_hThread = (HANDLE) _beginthread((void (__cdecl *)(void *))WhoIsThread,NULL,	reinterpret_cast<void*>(this));
			}
			else
			{
				m_bAbort = TRUE;
			}
			// Call Who is thread
			break;
		}
	}
}



unsigned __stdcall CUT_WhoIsPage::WhoIsThread(void * pThis){


	CUT_WhoIsPage *pThisObject = static_cast<CUT_WhoIsPage*>(pThis );



	_TCHAR	szNameServer[256];
	char	szResponseLine[2*MAX_PATH];
	_TCHAR	szLookupQuery[256];
	_TCHAR	szLogFileName[MAX_PATH];



	// Get the data for Query
	GetDlgItemText(pThisObject->m_hWnd,IDC_WHOISSERVER,szNameServer,256);
	GetDlgItemText(pThisObject->m_hWnd,IDC_WHOIS_QUERY,szLookupQuery,256);

	if (pThisObject->m_bEnableLogChecked)
	{
		// get the name of the file to log to
		GetDlgItemText(pThisObject->m_hWnd,IDC_WHOIS_LOG_FILE,szLogFileName,MAX_PATH-1);
		if (_tcslen(szLogFileName) <1)
		{
			int iAnswer = IDOK;
			iAnswer = MessageBox(pThisObject->m_hWnd,_T("Log file name is not present, Continue without logging?"),_T("Verify"),MB_OKCANCEL);
			if (iAnswer != IDOK   )
				return 0;

		}
		else
		{
			// set up the log file if needed
			pThisObject->m_HistoryCtrl.SetLogName (szLogFileName);
			pThisObject->m_HistoryCtrl.EnableLog (pThisObject->m_bEnableLogChecked);


		}

	}

	//clear the history window
	pThisObject->m_HistoryCtrl.ClearHistory();

	_TCHAR szDisplayString[MAX_PATH];
	_sntprintf(szDisplayString, MAX_PATH-1, _T("Results of WhoIs query \"%s\":"), szLookupQuery);
	pThisObject->m_HistoryCtrl.AddStampedLine(_T(""));
	pThisObject->m_HistoryCtrl.AddLine(szDisplayString);
	pThisObject->m_HistoryCtrl.AddLine(_T(""));

	int			retCode = UTE_SUCCESS;
	myClient *client = (myClient *)new myClient ;
	client->m_parent = pThisObject;

	int			nPort = 43; // The who is Port number
	int			nSeconds = 10;
	COLORREF	rfTextColor =HISTORY_BLACK;
	COLORREF	rfBackColor =HISTORY_YELLOW;

	// connect to the whois server
	if ((retCode = (client->Connect (nPort,szNameServer,10)))==UTE_SUCCESS)
	{
		// send the domain name as a line 
// v4.2 TODO("TD Send as line!! - using AC() for now.")
		if ( (client->SendAsLine (AC(szLookupQuery),(int)_tcslen(szLookupQuery),MAX_PATH)) >0)
		{
			// the responses are ascii line so let recieve them as lines
			while (client->ReceiveLine (szResponseLine,sizeof(szResponseLine)-1,nSeconds) >0)
			{
				// display each line as we recieve them
				if (strlen(szResponseLine ) <3)
					rfBackColor = HISTORY_WHITE;
				CUT_StrMethods::RemoveCRLF(szResponseLine);
				pThisObject->m_HistoryCtrl.AddLine(szResponseLine,rfTextColor,rfBackColor);
			}

		}
		client->CloseConnection ();				
	}
	delete client;

	pThisObject->m_HistoryCtrl.AddLine(_T(""));
	pThisObject->m_HistoryCtrl.AddLine(CUT_ERR::GetErrorString(retCode));
	pThisObject->m_HistoryCtrl.AddLine(_T("-----------------------------"));
	pThisObject->m_HistoryCtrl.AddLine(_T(" "));

	SetDlgItemText(pThisObject->m_hWnd ,IDC_WHO_IS_BTN,_T("&Who Is?"));
	pThisObject->m_hThread = NULL;

	return 0;

}

#pragma warning ( pop )