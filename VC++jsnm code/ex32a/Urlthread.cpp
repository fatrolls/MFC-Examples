// urlthread.cpp

#include <stdafx.h>
#include "urlthread.h"
#define MAXBUF 100

CString g_strURL = "http://";
volatile BOOL g_bThreadStarted = FALSE;
CEvent g_eKill;

UINT UrlThreadProc(LPVOID pParam)
{
	g_bThreadStarted = TRUE;
	CString strLine;
	CInternetSession session;
	CStdioFile* pFile1 = NULL;

	try {
		pFile1 = session.OpenURL(g_strURL, 0, INTERNET_FLAG_TRANSFER_BINARY |
				INTERNET_FLAG_KEEP_CONNECTION); // needed for Windows NT c/r authentication
		// Keep displaying text from the URL until the Kill event is received
		while(::WaitForSingleObject(g_eKill.m_hObject, 0) != WAIT_OBJECT_0) {
			// one line at a time
			if(pFile1->ReadString(strLine) == FALSE) break;
			strLine += '\n';
			::SendMessage((HWND) pParam, EM_SETSEL, (WPARAM) 999999, 1000000);
			::SendMessage((HWND) pParam, EM_REPLACESEL, (WPARAM) 0,
						(LPARAM) (const char*) strLine);
			Sleep(250); // Deliberately slow down the transfer
		}
	}
	catch(CInternetException* e) {
		LogInternetException(pParam, e);
		e->Delete();
	}
	if(pFile1 != NULL) delete pFile1; // closes the file -- prints a warning
	g_bThreadStarted = FALSE;
	// Post any message to update the toolbar buttons
	::PostMessage((HWND) pParam, EM_SETSEL, (WPARAM) 999999, 1000000);
	TRACE("Post thread exiting normally\n");
	return 0;
}

void LogInternetException(LPVOID pParam, CInternetException* pe)
{	
	CString strGmt = CTime::GetCurrentTime().FormatGmt("%m/%d/%y %H:%M:% GMT");
	char text1[300], text2[100];
	wsprintf(text1, "\r\nERROR: WinInet error #%d -- %s\r\n   ",
		pe->m_dwError, (const char*) strGmt);
	pe->GetErrorMessage(text2, 99);
	strcat(text1, text2);
	if(pe->m_dwError == 12152) {
		strcat(text1, "  URL not found?\r\n");
	}
	::SendMessage((HWND) pParam, EM_SETSEL, (WPARAM) 999999, 1000000);
	::SendMessage((HWND) pParam, EM_REPLACESEL, (WPARAM) 0, (LPARAM) text1);
}
