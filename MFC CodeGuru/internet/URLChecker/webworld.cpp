// Internet.cpp: implementation of the CInternet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "webworld.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define AGENT_NAME "MyBrowser1.0"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWebWorld::CWebWorld()
{
	DWORD dwError;

	// Initialize the Win32 Internet functions 
	m_Session = ::InternetOpen(AGENT_NAME, 
		INTERNET_OPEN_TYPE_PRECONFIG, // Use registry settings. 
		NULL, // Proxy name. NULL indicates use default.
		NULL, // List of local servers. NULL indicates default. 
		0) ;
     
	dwError = GetLastError();
}

CWebWorld::~CWebWorld()
{
	// Closing the session
	::InternetCloseHandle(m_Session);
}

CString CWebWorld::GetWebPage(const CString& Url)
{
	HINTERNET hHttpFile;
	char szSizeBuffer[32];
	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer); 
	DWORD dwFileSize;
	DWORD dwBytesRead;
	BOOL bSuccessful;
	CString Contents;

	// Setting default error message
	Contents = m_ErrorMessage;

	// Opening the Url and getting a Handle for HTTP file	
	hHttpFile = InternetOpenUrl(m_Session, (const char *) Url, NULL, 0,INTERNET_FLAG_RELOAD , 0);

	if (hHttpFile)
	{	
		// Getting the size of HTTP Files
		BOOL bQuery = ::HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer, &dwLengthSizeBuffer, NULL) ;

		if(bQuery==TRUE)
		{	
			// Allocating the memory space for HTTP file contents
			dwFileSize=atol(szSizeBuffer);
			LPSTR szContents = Contents.GetBuffer(dwFileSize);

			// Read the HTTP file 
			BOOL bRead = ::InternetReadFile(hHttpFile, szContents, dwFileSize, &dwBytesRead); 
			
			if (bRead) 
				bSuccessful = TRUE;

			::InternetCloseHandle(hHttpFile); // Close the connection.
		}

	}
	else
	{
		// Connection failed.
		bSuccessful = FALSE;
	} 
	return Contents;
}

void CWebWorld::SetErrorMessage(CString s)
{
	m_ErrorMessage = s;
}
