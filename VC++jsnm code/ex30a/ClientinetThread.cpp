// clientinetthread.cpp (uses MFC Wininet calls)

#include <stdafx.h>
#include "utility.h"
#define MAXBUF 50000

HWND g_hMainWnd = 0;
char g_pchStatus[25] = "";
CCriticalSection g_csStatus;

UINT ClientWinInetThreadProc(LPVOID pParam)
{
	CCallbackInternetSession session;
	CHttpConnection* pConnection = NULL;
	CHttpFile* pFile1 = NULL;
	char* buffer = new char[MAXBUF];
	UINT nBytesRead = 0;
	DWORD dwStatus;
	try {
		// username/password doesn't work yet
		if(!g_strServerName.IsEmpty()) {
			pConnection = session.GetHttpConnection(g_strServerName,
					(INTERNET_PORT) g_nPort);
		}
		else {
			pConnection = session.GetHttpConnection(g_strServerIP,
					(INTERNET_PORT) g_nPort);
		}
		pFile1 = pConnection->OpenRequest(1, g_strFile, NULL, 1, NULL, NULL, // GET request
				INTERNET_FLAG_KEEP_CONNECTION); // needed for NT Challenge/Response authentication
				// INTERNET_FLAG_RELOAD forces reload from the server (bypasses client's cache)
		pFile1->SendRequest();
		pFile1->QueryInfoStatusCode(dwStatus);
		TRACE("QueryInfoStatusCode = %d\n", dwStatus);
		nBytesRead = pFile1->Read(buffer, MAXBUF - 1);
		buffer[nBytesRead] = '\0'; // necessary for message box
		char temp[100];
		if(pFile1->Read(temp, 100) != 0) { // makes caching work if read complete
			AfxMessageBox("File overran buffer -- not cached");
		}
		::MessageBox(::GetTopWindow(::GetDesktopWindow()), buffer, "WININET CLIENT", MB_OK);
		// could use existing pFile1 to SendRequest again if we wanted to
	}
	catch(CInternetException* e) {
		LogInternetException(pParam, e);
		e->Delete();
	}
	// could call OpenRequest again on same connection if we wanted to 
	if(pFile1) delete pFile1; // does the close -- prints a warning
	if(pConnection) delete pConnection; // why does it print a warning?
	delete [] buffer;
	g_csStatus.Lock();
	  strcpy(g_pchStatus, ""); // problem with empty string. bug #9897
	g_csStatus.Unlock();
	return 0;
}
