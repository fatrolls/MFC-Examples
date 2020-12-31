// PostThread.cpp (uses MFC Wininet calls)

#include <stdafx.h>
#include "PostThread.h"

#define MAXBUF 50000

CString g_strFile = "/scripts/ex31a.dll";
CString g_strServerName = "localhost";
CString g_strParameters;

UINT PostThreadProc(LPVOID pParam)
{
	CInternetSession session;
	CHttpConnection* pConnection = NULL;
	CHttpFile* pFile1 = NULL;
	char* buffer = new char[MAXBUF];
	UINT nBytesRead = 0;
	DWORD dwStatusCode;
	BOOL bOkStatus = FALSE;
	try {
		pConnection = session.GetHttpConnection(g_strServerName, (INTERNET_PORT) 80);
		pFile1 = pConnection->OpenRequest(0, g_strFile + "?ProcessTimesheet", // POST request
				 NULL, 1, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_RELOAD); // no cache
		pFile1->SendRequest(NULL, 0, (LPVOID) (const char*) g_strParameters,
				g_strParameters.GetLength());
		pFile1->QueryInfoStatusCode(dwStatusCode);
		if(dwStatusCode == 200) { // OK status
			// doesn't matter what came back from server -- we're looking for OK status
			bOkStatus = TRUE;
			nBytesRead = pFile1->Read(buffer, MAXBUF - 1);
			buffer[nBytesRead] = '\0'; // necessary for TRACE
			TRACE(buffer);
			TRACE("\n");
		}
	}
	catch(CInternetException* pe) {
		char text[100];
		pe->GetErrorMessage(text, 99);
		TRACE("WinInet exception %s\n", text);
		pe->Delete();
	}
	if(pFile1) delete pFile1; // does the close -- prints a warning
	if(pConnection) delete pConnection; // why does it print a warning?
	delete [] buffer;
	::PostMessage((HWND) pParam, WM_POSTCOMPLETE, (WPARAM) bOkStatus, 0);
	return 0;
}
