// clientsockthread.cpp (uses Winsock calls only)

#include <stdafx.h>
#include "blocksock.h"
#include "utility.h"
#define MAXBUF 50000

CString g_strIPClient;
CString g_strProxy = "ITGPROXY";
BOOL g_bUseProxy = FALSE;

UINT ClientSocketThreadProc(LPVOID pParam)
{
	// sends a blind request, followed by a request for a specific URL
	CHttpBlockingSocket sClient;
	char* buffer = new char[MAXBUF];
	int nBytesReceived = 0;
	// We're doing a blind GET, but we must provide server name if we're using a proxy.
	// A blind GET is supposed to retrieve the server's default HTML document.
	// Some servers don't have a default document but return a document name in the Location header.
	char request[] = "GET %s%s%s HTTP/1.0\r\n";
	char headers[] =
		"User-Agent: Mozilla/1.22 (Windows; U; 32bit)\r\n"
		"Accept: */*\r\n"
		"Accept: image/gif\r\n"
		"Accept: image/x-xbitmap\r\n"
		"Accept: image/jpeg\r\n"
// following line tests server's ability to not send the URL
//		"If-Modified-Since: Wed, 11 Sep 1996 20:23:04 GMT\r\n"
		"\r\n"; // need this
	CSockAddr saServer, saPeer, saTest, saClient;
	try {
		sClient.Create();
		if(!g_strIPClient.IsEmpty()) {
			// won't work if network is assigning us our IP address
			// good only for intranets where client computer has several IP addresses
			saClient = CSockAddr(g_strIPClient);
			sClient.Bind(saClient);
		}
		if(g_bUseProxy) {
			saServer = CBlockingSocket::GetHostByName(g_strProxy, 80);
		}
		else {
			if(g_strServerIP.IsEmpty()) {
				saServer = CBlockingSocket::GetHostByName(g_strServerName, g_nPort);
			}
			else {
				saServer = CSockAddr(g_strServerIP, g_nPort);
			}
		}
		sClient.Connect(saServer);
		sClient.GetSockAddr(saTest);
		TRACE("SOCK CLIENT: GetSockAddr = %s, %d\n", saTest.DottedDecimal(), saTest.Port());
		if(g_bUseProxy) {
			wsprintf(buffer, request, "http://" , (const char*) g_strServerName, g_strFile);
		}
		else {
			wsprintf(buffer, request, "", "", g_strFile);
		}
		sClient.Write(buffer, strlen(buffer), 10);
		sClient.Write(headers, strlen(headers), 10);
		// read all the server's response headers
		do {
			nBytesReceived = sClient.ReadHttpHeaderLine(buffer, MAXBUF, 10);
			TRACE("SOCK CLIENT: %s", buffer);
		} while(strcmp(buffer, "\r\n"));
		// read the server's file
		nBytesReceived = sClient.ReadHttpResponse(buffer, MAXBUF, 10);
		TRACE("SOCK CLIENT: bytes received = %d\n", nBytesReceived);
		if(nBytesReceived == 0) {
			AfxMessageBox("No response recevied. Bad URL?");
		}
		else {
			buffer[nBytesReceived] = '\0';
			::MessageBox(::GetTopWindow(::GetDesktopWindow()), buffer, "WINSOCK CLIENT", MB_OK);
		}

		// could do another request on sClient by calling Close, then Create, etc.
	}
	catch(CBlockingSocketException* e) {
		LogBlockingSocketException(pParam, "CLIENT:", e);
		e->Delete();
	}
	sClient.Close();
	delete [] buffer;
	return 0;
}
