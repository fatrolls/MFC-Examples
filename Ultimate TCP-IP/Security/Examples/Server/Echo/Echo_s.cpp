// =================================================================
//  class: CUT_EchoServer
//	class: CUT_EchoThread
//  File:  Echo_s.cpp
//  
//  Purpose:
//
//	  ECHO secure server
//       
// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#include "stdafx.h"
#include "Echo_s.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/********************************
CreateInstance
*********************************/
CUT_WSThread * CUT_EchoServer::CreateInstance()
{
    return new CUT_EchoThread;
}

/********************************
ReleaseInstance
*********************************/
void CUT_EchoServer::ReleaseInstance(CUT_WSThread *ptr)
{
    if(ptr != NULL)
        delete ptr;
}

/***************************************************
OnStatus
    This virtual function is called each time we have any
    status information to display.
Params
    StatusText  - status text
Return
    UTE_SUCCESS - success   
****************************************************/
int CUT_EchoServer::OnStatus(LPCTSTR StatusText)
{
    #ifdef UT_DISPLAYSTATUS 
        ctrlHistory->AddLine(StatusText);
	 #endif

    return UTE_SUCCESS;
}
#if defined _UNICODE
// overload for client ascii calls
int CUT_EchoServer::OnStatus(LPCSTR StatusText)
{
    #ifdef UT_DISPLAYSTATUS 
        ctrlHistory->AddLine(StatusText);
	 #endif

    return UTE_SUCCESS;
}
#endif


//=================================================================
//  class: CUT_EchoThread
//=================================================================

/***************************************************
OnMaxConnect
    This member is called when the maximum number of
    connections allowed has already been reached

****************************************************/
void CUT_EchoThread::OnMaxConnect()
{
	// Send error responce 
	Send("Too Many Connections, Please Try Later.",0);

	// Show status
	char szBuffer[1024];
    sprintf(szBuffer,"(%d) Max Connections Reached", m_winsockclass_this->GetNumConnections());
    ((CUT_EchoServer *)m_winsockclass_this)->OnStatus(szBuffer);
	Send(szBuffer);

    ClearReceiveBuffer();
    return;
}

/***************************************************
OnConnect
    This member is called when a connection is made and
    accepted. Do all processing here, since the connection
    is automatically terminated when this function returns.
    Plus the thread that this function runs in is terminated
    as well.
    This function is the main engine that process all clients 
    commands.
PARAM
    NONE
RETURN
    VOID
****************************************************/
void CUT_EchoThread::OnConnect()
{
	CUT_EchoServer  *ptrServer = (CUT_EchoServer *)m_winsockclass_this;
	char            szBuffer[WSS_LINE_BUFFER_SIZE + 1];
	char            ipbuf[32];
	int				nLength = 0;

    // Initialize client IP address
    sprintf(ipbuf, "%d.%d.%d.%d", m_clientSocketAddr.sin_addr.S_un.S_un_b.s_b1,
        m_clientSocketAddr.sin_addr.S_un.S_un_b.s_b2,
        m_clientSocketAddr.sin_addr.S_un.S_un_b.s_b3,
        m_clientSocketAddr.sin_addr.S_un.S_un_b.s_b4);
    
    // Display status - client IP address 
    ptrServer->OnStatus(_T("Client connected:"));
    ptrServer->OnStatus(ipbuf);

	// Send greeting
	Send("*** Ultimate TCP/IP Echo Server Ready ***\r\n");

    // Keep receiving lines from the client until first timeout/error
	// v4.2 change - was while(TRUE)...
    for(;;) 
	{
        // Receive a line from the client
        nLength = ReceiveLine(szBuffer, WSS_LINE_BUFFER_SIZE);

        // Close connection on error
        if(nLength <= 0) 
			return;

		// Display received line in the status window
		ptrServer->OnStatus(_T("Line received from client:"));
		ptrServer->OnStatus(szBuffer);
        
		// Send received line back to the client
		Send(szBuffer);
	}
}

/***********************************************
SocketOnConnected
	Negotiates a secure connection on the specified
	socket.
Params
	s			- a descriptor identifying a socket
	lpszName	- server name 
Return
	UTE_SUCCESS
	UTE_LOAD_SECURITY_LIBRARIES_FAILED
	UTE_OUT_OF_MEMORY
	UTE_NULL_PARAM
	UTE_FAILED_TO_GET_SECURITY_STREAM_SIZE
	UTE_FAILED_TO_CREATE_SECURITY_CREDENTIALS
	UTE_HANDSHAKE_FAILED
************************************************/
int CUT_EchoThread::SocketOnConnected(SOCKET s, const char *lpszName)
{ 
	*m_szLastError = NULL;
	int nResult = CUT_WSThread::SocketOnConnected(s, lpszName);

	// Send error message in the greeting
	if(nResult != UTE_SUCCESS)
	{
		if(*m_szLastError != NULL)
			Send(m_szLastError);
		else
			Send("Connection failed");
		Send("\r\n");
	}

	return nResult;
}

/***********************************************
HandleError
	Virtual function which receives the security 
    errors descriptions. 
Params
    lpszErrorDescription - error description string
Return
    none
************************************************/
void CUT_EchoThread::HandleSecurityError(char *lpszErrorDescription)
{
	CUT_EchoServer  *ptrServer = (CUT_EchoServer *)m_winsockclass_this;
	if(lpszErrorDescription != NULL)
	{
		// Save last security error
		strncpy(m_szLastError, lpszErrorDescription, sizeof(m_szLastError)-1);
		// Add it to the status list
		ptrServer->OnStatus(lpszErrorDescription);
	}
} 

#pragma warning ( pop )