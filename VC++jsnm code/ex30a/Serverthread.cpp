// serverthread.cpp

#include <stdafx.h>
#include "blocksock.h"
#include "utility.h"
#define SERVERMAXBUF 5000
#define MAXLINELENGTH 100

//#define USE_TRANSMITFILE // uncomment if you have Windows NT

volatile BOOL g_bListening = FALSE;
volatile UINT g_nPortServer = 80;
CString g_strDirect = "\\vcpp32\\ex30a\\WebSite";
CString g_strIPServer;
CString g_strDefault = "default.htm";
CBlockingSocket g_sListen;

BOOL Parse(char* pStr, char** ppToken1, char** ppToken2)
// really stupid parsing routine
// (must find two tokens, each followed by a space)
{
	*ppToken1 = pStr;
	char* pch = strchr(pStr, ' ');
	if(pch) {
		*pch = '\0';
		pch++;
		*ppToken2 = pch;
		pch = strchr(pch, ' ');
		if(pch) {
			*pch = '\0';
			return TRUE;
		}
	}
	return FALSE;
}

void LogRequest(LPVOID pParam, char* pch, CSockAddr sa)
{	// pParam holds the HWND for the destination window (in another thread)
	CString strGmt = CTime::GetCurrentTime().FormatGmt("%m/%d/%y %H:%M:%S GMT");
	char text1[1000];
	wsprintf(text1, "SERVER CONNECTION # %d: IP addr = %s, port = %d -- %s\r\n",
		g_nConnection, sa.DottedDecimal(), sa.Port(),  (const char*) strGmt);
	strcat(text1, pch);
	::SendMessage((HWND) pParam, EM_SETSEL, (WPARAM) 65534, 65535);
	::SendMessage((HWND) pParam, EM_REPLACESEL, (WPARAM) 0, (LPARAM) text1);
}

CFile* OpenFile(const char* pName)
{
	// if it's really a directory, open the default HTML file
	CFileException e;
	CFile* pFile = new CFile();
	if(*pName == '/') pName++;
	CString strName = pName;
	if(pFile->Open(strName, CFile::modeRead, &e)) {
		return pFile;
	}
	if((e.m_cause == CFileException::accessDenied) ||
			(e.m_cause == CFileException::badPath)) { // directory?
		int nLength;
		// add a / unless it's the "root" directory
		if((nLength = strName.GetLength()) > 1) {
			if(strName[nLength - 1] != '/') {
				strName += '/';
			}
		}
		strName += g_strDefault;
		if(pFile->Open(strName, CFile::modeRead, &e)) {
			return pFile;
		}
	}
	delete pFile;
	return NULL;
}

UINT ServerThreadProc(LPVOID pParam)
{
	CSockAddr saClient;
	CHttpBlockingSocket sConnect;
	char* buffer = new char[SERVERMAXBUF];
	char message[100], headers[500], request1[MAXLINELENGTH],  request2[MAXLINELENGTH];
	char hdrErr[] = "HTTP/1.0 404 Object Not Found\r\n"
				   "Server: Inside Visual C++ SOCK01\r\n"
				   "Content-Type: text/html\r\n"
				   "Accept-Ranges: bytes\r\n"
				   "Content-Length: 66\r\n\r\n" // WinInet wants correct length
				   "<html><h1><body>HTTP/1.0 404 Object Not Found</h1></body></html>\r\n";
	char hdrFmt[] = "HTTP/1.0 200 OK\r\n"
				   "Server: Inside Visual C++ EX30A\r\n"
				   "Date: %s\r\n"
				   "Content-Type: text/html\r\n"
				   "Accept-Ranges: bytes\r\n"
				   "Content-Length: %d\r\n";
	char html1[] = "<html><head><title>Inside Visual C++ \
		               Server</title></head>\r\n"
				   "<body><body background=\"/samples/images/usa1.jpg\">\r\n"
				   "<h1><center>This is a custom home page</center></h1><p>\r\n"
				   "<a href=\"/samples/iisdocs.htm\">Click here for iisdocs.htm.</a><p>\r\n"
				   "<a href=\"/samples/disclaim.htm\">Click here for disclaim.htm.</a><p>\r\n";
					// custom message goes here
	char html2[] = "</body></html>\r\n\r\n";
	CString strGmtNow = CTime::GetCurrentTime().FormatGmt("%a, %d %b %Y %H:%M:%S GMT");
	int nBytesSent = 0;
	CFile* pFile = NULL;
	try {
		if(!g_sListen.Accept(sConnect, saClient)) {
			// view or application closed the listing socket
			g_bListening = FALSE;
			delete [] buffer;
			return 0;
		}
		g_nConnection++;
		AfxBeginThread(ServerThreadProc, pParam, THREAD_PRIORITY_NORMAL);
		// read request from client
		sConnect.ReadHttpHeaderLine(request1, MAXLINELENGTH, 10);
		LogRequest(pParam, request1, saClient);
		char* pToken1; char* pToken2;
		if(Parse(request1, &pToken1, &pToken2)) {
			if(!stricmp(pToken1, "GET")) {
				do { // eat the remaining headers
					sConnect.ReadHttpHeaderLine(request2, MAXLINELENGTH, 10);
					TRACE("SERVER: %s", request2);
				}
				while(strcmp(request2, "\r\n"));
				if(!stricmp(pToken2, "/custom")) { // special request
					// send a "custom" HTML  page
					wsprintf(message, "Hi! you are connection #%d on IP %s, port %d<p>%s",
							g_nConnection, saClient.DottedDecimal(), saClient.Port(), strGmtNow);
					wsprintf(headers, hdrFmt, (const char*) strGmtNow, strlen(html1)
									+ strlen(message) + strlen(html2));
					// no If-Modified
					strcat(headers, "\r\n"); // blank line
					sConnect.Write(headers, strlen(headers), 10);
					sConnect.Write(html1, strlen(html1), 10);
					sConnect.Write(message, strlen(message), 10);
					sConnect.Write(html2, strlen(html2), 10);
				}
				else if(strchr(pToken2, '?')) { // CGI request
					// Netscape doesn't pass function name in a GET
					TRACE("SERVER: CGI request detected %s\n", pToken2);
					// could load and run the ISAPI DLL here
				}
				else { // must be a file
					// assumme this program has already set the default WWW directory
					if((pFile = OpenFile(pToken2)) != NULL) {
						CFileStatus fileStatus;
						pFile->GetStatus(fileStatus);
						CString strGmtMod = fileStatus.m_mtime.FormatGmt("%a, %d %b %Y %H:%M:%S GMT");
						char hdrModified[50];
						wsprintf(hdrModified, "Last-Modified: %s\r\n\r\n", (const char*) strGmtMod);
						DWORD dwLength = pFile->GetLength();
						// Date: , Content-Length:
						wsprintf(headers, hdrFmt,  (const char*) strGmtNow, dwLength);
						strcat(headers, hdrModified);
						nBytesSent = sConnect.Write(headers, strlen(headers), 10);
						TRACE("SERVER: header characters sent = %d\n", nBytesSent);
						// would be a good idea to send the file only if the If-Modified-Since date
						// were less than the file's m_mtime
						nBytesSent = 0;
#ifdef USE_TRANSMITFILE
						if(::TransmitFile(sConnect, (HANDLE) pFile->m_hFile, dwLength,
								0, NULL, NULL, TF_DISCONNECT)) {
							nBytesSent = (int) dwLength;
						}
#else
						DWORD dwBytesRead = 0;
						UINT uBytesToRead;
						// send file in small chunks (5K) to avoid big memory alloc overhead
						while(dwBytesRead < dwLength) {
							uBytesToRead = min(SERVERMAXBUF, dwLength - dwBytesRead);
							VERIFY(pFile->Read(buffer, uBytesToRead) == uBytesToRead);
							nBytesSent += sConnect.Write(buffer, uBytesToRead, 10);
							dwBytesRead += uBytesToRead;
						}
#endif
						TRACE("SERVER: full file sent successfully\n");
					}
					else {
						nBytesSent = sConnect.Write(hdrErr, strlen(hdrErr), 10); // 404 Object Not Found
					}
				}
			}
			else if(!stricmp(pToken1, "POST")) {
				do { // eat the remaining headers thru blank line
					sConnect.ReadHttpHeaderLine(request2, MAXLINELENGTH, 10);
					TRACE("SERVER: POST %s", request2);
				}
				while(strcmp(request2, "\r\n"));
				// read the data line sent by the client
				sConnect.ReadHttpHeaderLine(request2, MAXLINELENGTH, 10);
				TRACE("SERVER: POST PARAMETERS = %s\n", request2);
				LogRequest(pParam, request2, saClient);
				// launch ISAPI DLL here?
				nBytesSent = sConnect.Write(hdrErr, strlen(hdrErr), 10); // 404 error for now
			}
			else {
				TRACE("SERVER: %s (not a GET or POST)\n", pToken1);
				// don't know how to eat the headers
			}
		}
		else {
			TRACE("SERVER: bad request\n");
		}
		sConnect.Close(); // destructor can't close it
	}
	catch(CBlockingSocketException* pe) {
		LogBlockingSocketException(pParam, "SERVER:", pe);
		pe->Delete();
	}
	TRACE("SERVER: file characters sent = %d\n", nBytesSent);
	delete [] buffer;
	if(pFile) delete pFile;
	return 0;
}


