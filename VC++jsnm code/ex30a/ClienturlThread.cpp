// clienturlthread.cpp (uses CInternetSession::OpenURL)

#include <stdafx.h>
#include "utility.h"
#define MAXBUF 50000

CString g_strURL = "http://";

UINT ClientUrlThreadProc(LPVOID pParam)
{
	char* buffer = new char[MAXBUF];
	UINT nBytesRead = 0;

	CInternetSession session; // can't get status callbacks for OpenURL
	CStdioFile* pFile1 = NULL; // could call ReadString to get 1 line
	try {
		pFile1 = session.OpenURL(g_strURL, 0, INTERNET_FLAG_TRANSFER_BINARY |
				INTERNET_FLAG_KEEP_CONNECTION);
		// if OpenURL fails, we won't get past here
		nBytesRead = pFile1->Read(buffer, MAXBUF - 1);
		buffer[nBytesRead] = '\0'; // necessary for message box
		char temp[100];
		if(pFile1->Read(temp, 100) != 0) { // makes caching work if read complete
			AfxMessageBox("File overran buffer -- not cached");
		}
		::MessageBox(::GetTopWindow(::GetDesktopWindow()), buffer, "URL CLIENT", MB_OK);
	}
	catch(CInternetException* e) {
		LogInternetException(pParam, e);
		e->Delete();
	}
	if(pFile1) delete pFile1;
	delete [] buffer;
	return 0;
}
