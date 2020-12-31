// IOCPS.cpp: implementation of the IOCPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOCPS.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "mswsock.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IOCPS::IOCPS()
{
	m_bOneIPPerConnection=FALSE;
	m_bShutDown=FALSE;
	WSADATA wsaData;
	m_iWSAInitResult=WSAStartup(MAKEWORD(2,2), &wsaData);	
	m_socListen=NULL;
	m_pListenThread=NULL;
	m_iMaxNumberOfFreeContext=2;
	m_bAcceptConnections=TRUE;
	m_bServerStarted=FALSE;
	m_iMaxNumConnections=1201;
	m_bAcceptJobs=TRUE;
	m_nOfWorkers=2;
	m_nPortNumber=999;
	m_sServerVersion=IOCPSERVERVERSION;
	m_NumberOfActiveConnections=0;
	m_bSendInOrder=FALSE;
	m_bReadInOrder=FALSE;
	m_iNumberOfPendlingReads=3;
}

IOCPS::~IOCPS()
{
	ShutDown();
	if(m_iWSAInitResult == NO_ERROR)
		WSACleanup();	
}




/*
* Start the Client/Server.
* 
*
*/


BOOL IOCPS::Start(int nPort,int iMaxNumConnections,int iMaxIOWorkers,int nOfWorkers,int iMaxNumberOfFreeBuffer,int iMaxNumberOfFreeContext, BOOL bOrderedSend, BOOL bOrderedRead, int iNumberOfPendlingReads)
{
	m_iMaxNumberOfFreeBuffer=iMaxNumberOfFreeBuffer;
	m_iMaxNumConnections=iMaxNumConnections;
	m_nPortNumber=nPort;
	m_iMaxIOWorkers=iMaxIOWorkers;
	m_nOfWorkers=nOfWorkers;
	m_iMaxNumberOfFreeContext=iMaxNumberOfFreeContext;
	m_bShutDown=FALSE;
	m_bReadInOrder=bOrderedRead;
	m_bSendInOrder=bOrderedSend;
	m_iNumberOfPendlingReads=iNumberOfPendlingReads;
	return Startup();
}

BOOL IOCPS::Startup()
{
	// Some special cleanup 
#if defined SIMPLESECURITY	
	m_OneIPPerConnectionList.RemoveAll();
	m_BanIPList.RemoveAll();
#endif


	CString msg;
	AppendLog(m_sServerVersion);
	AppendLog("---------------------------------");
	AppendLog("Starting system..");


	m_NumberOfActiveConnections=0;


	if ( m_iWSAInitResult != NO_ERROR )
	{
		AppendLog("Error at WSAStartup, Winsock 2.0 is not supported. Supported only in WinXP, Win2k and WinNT");
		return FALSE;	
	}else
	{
		AppendLog("Winsock 2.0 successfully loaded.");
	}

	BOOL bRet=TRUE;
	m_bAcceptConnections=TRUE;

	if ( !m_bServerStarted )
	{
		m_bShutDown=FALSE;
		/*
		*	When using multiple pendling reads (eg m_iNumberOfPendlingReads>1) 
		*  with multiple IOworkers (eg m_iMaxIOWorkers>1), the order of the 
		*  packages are broken, because of IOCP internal design, Furthermore there is no 
		*  Performance gain to have multiple pendling reads if we use more than one IO-worker.
		*  The throughput is going upp because of serveral pendling reads, but is going down because of 
		*  the ordering part. 
		*/
		if ( m_iMaxIOWorkers>1 ) // we have some sort of bugg somewhere.. 
			m_iNumberOfPendlingReads=1;

		if(m_iNumberOfPendlingReads<=0)
			m_iNumberOfPendlingReads=1;

		msg.Format("Maximum nr of simultaneous connections: %i",m_iMaxNumConnections);
		AppendLog(msg);


		msg.Format("Number of pendling asynchronous reads: %d",m_iNumberOfPendlingReads);
		AppendLog(msg);



		// No need to make in order read or write
		if ( m_iMaxIOWorkers==1 )
		{
			m_bReadInOrder=FALSE;
			m_bSendInOrder=FALSE;
		}

		// If we have several Penling Reads and Several IO workers. We must read in order. 
		if ( m_iNumberOfPendlingReads>1&&m_iMaxIOWorkers>1 )
		{
			m_bReadInOrder=TRUE;
			m_bSendInOrder=TRUE;
		}

		if ( m_bSendInOrder )
			AppendLog("Send ordering initialized. (Decreases the performance by ~3%)");

		if ( m_bReadInOrder )
			AppendLog("Read ordering initialized.(Decreases the performance by ~3%)");

		// The map must be empty
		m_ContextMap.RemoveAll();
		m_ContextMap.InitHashTable(m_iMaxNumConnections);

		// Create the CompletionPort used by IO Worker Threads.  
		bRet&=CreateCompletionPort();
		if( bRet)
		{
			AppendLog("Completionport successfully created.");		
		}
		// Config the Listner.. 
		if ( m_nPortNumber>0 )
		{
			bRet&=SetupListner();

			if( bRet )
			{
				AppendLog("Connection listner thread successfully started.");		
			}
		}
		// Setup the IOWorkers.. 
		bRet&=SetupIOWorkers();


		if ( bRet )
		{
			msg.Format("Successfully started %i Input Output Worker thread(s).",m_nIOWorkers );
			AppendLog(msg);
		}
		// Start the logical Workers. (SetWorkes can be callen in runtime..). 
		bRet&=SetWorkers(m_nOfWorkers);

		if ( bRet )
		{
			msg.Format("Successfully started %i logical Worker(s).",m_nOfWorkers);
			AppendLog(msg);
		}

		// Accept incoming Job. 
		m_bAcceptJobs=TRUE;
		m_bServerStarted=TRUE;

	}

	if ( bRet )
	{
		if ( m_nPortNumber>0 )
		{
			msg.Format("Server successfully started.");
			AppendLog(msg);
			msg.Format("Waiting for clients on adress: %s, port:%i.",GetHostIP(),m_nPortNumber);
			AppendLog(msg);	
		}
		else 
		{
			msg.Format("Client successfully started.");
			AppendLog(msg);	

		}
	}

	return bRet; 	
}

/*
* Used to determine which connection to accept and deny. 	
* By using this callback function we can refuse connections 
* in lower kernel mode, we don't respond with ACK when the remote 
* connection connects with SYN. This means that the remote attacker
* would not know if he/she is blocked or the server is down. 
*
*/
#ifdef SIMPLESECURITY
int CALLBACK IOCPS::ConnectAcceptCondition(IN LPWSABUF lpCallerId,
										   IN LPWSABUF lpCallerData,
										   IN OUT LPQOS lpSQOS,
										   IN OUT LPQOS lpGQOS,
										   IN LPWSABUF lpCalleeId,
										   OUT LPWSABUF lpCalleeData,
										   OUT GROUP FAR *g,
										   IN DWORD dwCallbackData)
{

	sockaddr_in* pCaller=(sockaddr_in*)lpCallerId->buf;
	sockaddr_in* pCallee=(sockaddr_in*)lpCalleeId->buf;

	IOCPS* pThis = reinterpret_cast<IOCPS*>(dwCallbackData);

	// Do not take connections from ourself. 
	/*	if ( pCaller->sin_addr.S_un.S_addr == inet_addr("127.0.0.1") ) 
	{

	return CF_REJECT;
	}
	*/
	if ( pThis->IsInBannedList(pCaller) || pThis->IsAlreadyConnected(pCaller) )
	{
		// 
		// Do not send ACK, the attacker do not know if the server 
		// exist or not. 
		// 
		return CF_REJECT;
	}

	return CF_ACCEPT;
}
#endif

UINT IOCPS::ListnerThreadProc(LPVOID pParam)
{
	IOCPS* pThis = reinterpret_cast<IOCPS*>(pParam);
	if ( pThis )
	{
		while ( !pThis->m_bShutDown )
		{


			DWORD dwRet;
			dwRet = WSAWaitForMultipleEvents(1,
				&pThis->m_hEvent,
				FALSE,
				100,
				FALSE);

			if(pThis->m_bShutDown)
				break;

			// Om Det inte hände något hoppa upp så att vi kollar om vi ska dö. 
			if (dwRet == WSA_WAIT_TIMEOUT)
				continue;

			//
			// Titta på vad som har hänt.. 
			//
			WSANETWORKEVENTS events;
			int nRet = WSAEnumNetworkEvents(pThis->m_socListen,
				pThis->m_hEvent,
				&events);

			if (nRet == SOCKET_ERROR)
			{
				TRACE(_T("WSAEnumNetworkEvents error %ld\n"),WSAGetLastError());
				break;
			}
			if ( events.lNetworkEvents & FD_ACCEPT)
			{
				if ( events.iErrorCode[FD_ACCEPT_BIT] == 0&&pThis->m_bAcceptConnections&&!pThis->m_bShutDown)
				{
					//SOCKADDR_IN	SockAddr;
					SOCKET		clientSocket=INVALID_SOCKET;
					int			nRet=-1;
					int			nLen=-1;
					//
					// accept the new socket descriptor
					//
					nLen = sizeof(SOCKADDR_IN);
#ifdef SIMPLESECURITY
					clientSocket = WSAAccept(pThis->m_socListen,
						NULL,
						&nLen,ConnectAcceptCondition,(DWORD)pThis); 
#else
					clientSocket = WSAAccept(pThis->m_socListen,
						NULL,
						&nLen,0,0); 
#endif




					if (clientSocket == SOCKET_ERROR)
					{
						nRet = WSAGetLastError();
						if (nRet != WSAEWOULDBLOCK)
						{
							//
							// Just log the error and return
							//
							CString msg;
							msg.Format("Wsaaccept() error: %s",pThis->ErrorCode2Text(WSAGetLastError()));
							pThis->AppendLog(msg);
						}
					}else
						pThis->AssociateIncomingClientWithContext(clientSocket);
				}
				else
				{
					TRACE(_T("Unknown network event error %ld\n"),WSAGetLastError());
					break;

				}	
			}	
		}
	}
	TRACE("Listner Died!\r\n");
	return 0xdead;

}

UINT IOCPS::IOWorkerThreadProc(LPVOID pParam)
{
	IOCPS* pThis = reinterpret_cast<IOCPS*>(pParam);
	if ( pThis )
	{
		DWORD dwIoSize;
		ClientContext* lpClientContext;
		CIOCPBuffer *pOverlapBuff;
		bool bError=false;
		HANDLE hCompletionPort = pThis->m_hCompletionPort;
		LPOVERLAPPED lpOverlapped;
		//pOverlapPlus = CONTAINING_RECORD(lpOverlapped, MYOVERLAPPEDPLUS, m_ol);
		while ( !bError )
		{
			pOverlapBuff=NULL;
			lpClientContext=NULL;
			// Get a completed IO request.
			BOOL bIORet = GetQueuedCompletionStatus(
				hCompletionPort,
				&dwIoSize,
				(LPDWORD) &lpClientContext,
				&lpOverlapped, INFINITE);
			// Simulate workload (for debugging, to find possible reordering)
			//Sleep(20);



			// If Something whent wrong..
			if (!bIORet)  
			{
				DWORD dwIOError = GetLastError();
				if(dwIOError != WAIT_TIMEOUT) // It was not an Time out event we wait for ever (INFINITE) 
				{	
					TRACE(_T("GetQueuedCompletionStatus errorCode: %i, %s\n"),WSAGetLastError(),pThis->ErrorCode2Text(dwIOError));			
					// if we have a pointer & This is not an shut down.. 
					//if (lpClientContext!=NULL && pThis->m_bShutDown == false)
					if (lpClientContext!=NULL)
					{
						/*
						* ERROR_NETNAME_DELETED Happens when the communication socket
						* is cancelled and you have pendling WSASend/WSARead that are not finished. 
						* Then the Pendling I/O (WSASend/WSARead etc..) is cancelled and we return with 
						* ERROR_NETNAME_DELETED.. 
						*/
						if(dwIOError==ERROR_NETNAME_DELETED) 
						{

							//TRACE("ERROR_NETNAME_DELETED\r\n");
							pThis->DisconnectClient(lpClientContext); 
							TRACE(">IOWORKER1 (%x)\r\n",lpClientContext);
							pThis->ReleaseClientContext(lpClientContext); //Later Implementati

						}else
						{ // Should not get here if we do: disconnect the client and cleanup & report. 

							pThis->AppendLog(pThis->ErrorCode2Text(dwIOError)); 
							pThis->DisconnectClient(lpClientContext); 
							TRACE(">IOWORKER2 (%x)\r\n",lpClientContext);
							pThis->ReleaseClientContext(lpClientContext); //Should we do this ? 
						}
						// Clear the buffer if returned. 
						pOverlapBuff=NULL;
						if(lpOverlapped!=NULL)
							pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CIOCPBuffer, m_ol);
						if(pOverlapBuff!=NULL)
							pThis->ReleaseBuffer(pOverlapBuff);			
						continue;
					}
					// We shall never come here  
					// anyway this was an error and we should exit the worker thread
					bError = true;
					pThis->AppendLog(pThis->ErrorCode2Text(dwIOError)); 
					pThis->AppendLog("IOWORKER KILLED BECAUSE OF ERROR IN GetQueuedCompletionStatus");

					pOverlapBuff=NULL;
					if(lpOverlapped!=NULL)
						pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CIOCPBuffer, m_ol);
					if(pOverlapBuff!=NULL)
						pThis->ReleaseBuffer(pOverlapBuff);
					continue;
				}
			}



			if(bIORet && lpOverlapped && lpClientContext) 
			{
				pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CIOCPBuffer, m_ol);
				if(pOverlapBuff!=NULL)
					pThis->ProcessIOMessage(pOverlapBuff, lpClientContext, dwIoSize);
			}	

			if(lpClientContext==NULL&&pOverlapBuff==NULL&&pThis->m_bShutDown)
			{
				TRACE("lpClientContext==NULL \r\n"); 
				bError=true;
			}


			//pThis->ReleaseBuffer(pOverlapBuff);// from previous call

		} 

	}

	TRACE("IOWorker Died!\r\n");
	return 0xdead;
}

/*
* AssociateIncomingClientWithContext
* 
* This function do the Following: 
* 1) Does some simpleSecutity Stuff (e.g one connection per client, etc..)
* 2) Allocates an Context for the Socket. 
* 3) Configures the Socket. 
* 4) Associate the Socket and the context with the completion port. 
* 5) Fires an IOInitialize So the IOWORKERS Start to work on the connection. 
*/

BOOL IOCPS::AssociateIncomingClientWithContext(SOCKET clientSocket)
{	
	if (clientSocket == INVALID_SOCKET)
	return FALSE;


	if (m_bShutDown || !m_bAcceptConnections)
	{
		closesocket(clientSocket);
		return FALSE;
	} 

	//
	// Close connection if we have reached the maximum nr of connections... 	
	// 	
	m_ContextMapLock.Lock(); // Mus lock the m_ContextMapLock Protect (m_NumberOfActiveConnections) ??
	if(m_NumberOfActiveConnections>=m_iMaxNumConnections)
	{

		//
		// Disconnect. 
		//
		LINGER lingerStruct;
		lingerStruct.l_onoff = 1;
		lingerStruct.l_linger = 0;
		setsockopt( clientSocket, SOL_SOCKET, SO_LINGER,
			(char *)&lingerStruct, sizeof(lingerStruct) );

		//
		// Now close the socket handle. This will do an abortive or graceful close, as requested. 
		CancelIo((HANDLE) clientSocket);

		closesocket( clientSocket );
		clientSocket = INVALID_SOCKET;

		CString msg;
		msg.Format("Maximum number of Connection is reached. ");
		AppendLog(msg);

	}
	m_ContextMapLock.Unlock();

	if (clientSocket == INVALID_SOCKET)
		return FALSE; 
	// Create the Client context to be associated with the completion port
	ClientContext* pContext = AllocateContext();

	if(pContext!=NULL)
	{

		pContext->m_Socket = clientSocket;
		// M_ID is Used for Delete(). Should we remove this soon ? 
		pContext->m_ID=clientSocket;

		/* 
		* TCP_NODELAY	BOOL=TRUE Disables the "nagle algorithm for send coalescing" which delays
		* short packets in the hope that the application will send more data and allow
		* it to combine them into a single one to improve network efficiency.
		*/
		const char chOpt = 1;
		int nErr = setsockopt(pContext->m_Socket, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(char));
		if (nErr == -1)
		{
			CString msg;
			msg.Format("setsockopt() error: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			TRACE(">AcceptIncomingClient(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			return FALSE;
		}

		if(AddClientContext(pContext))
		{	
			// Associate the new socket with a completion port.
			if (!AssociateSocketWithCompletionPort(clientSocket, m_hCompletionPort, (DWORD) pContext))
			{
				CString msg;
				msg.Format("AssociateSocketWithCompletionPort Failed: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return FALSE;
			}

			// Trigger first IO Completion Request
			// Otherwise the Worker thread will remain blocked waiting for GetQueuedCompletionStatus...
			// The first message that gets queued up is ClientIoInitializing - see ThreadPoolFunc and 
			// IO_MESSAGE_HANDLER

			// Important!! EnterIOLoop must notify that the socket and the structure  
			// pContext have an Pendling IO operation ant should not be deleted.
			// This is nessesary to avoid Access violation. 
			//
			EnterIOLoop(pContext);

			CIOCPBuffer *pOverlapBuff =AllocateBuffer(IOInitialize);
			if(pOverlapBuff!=NULL)
			{
				BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pOverlapBuff->m_ol);

				if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
				{            
					ReleaseBuffer(pOverlapBuff);
					DisconnectClient(pContext);
					TRACE(">IOInitialize AcceptIncomingClient(%x)\r\n",pContext);
					ReleaseClientContext(pContext);
					return FALSE;
				}
			}
			else
			{
				CString msg;
				msg.Format("ERROR Could not allocate memory for buffer in Acceptincoming: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return FALSE;
			}
		}else
		{
			CString msg;
			msg.Format("ERROR HASHMAP AddClientContext failed.  %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			return FALSE;
		}
	}else
	{
		CString msg;
		msg.Format("ERROR Could not allocate memory for Context in Acceptincoming: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket(clientSocket);
		return FALSE;
	}
	return TRUE;
}


BOOL IOCPS::AssociateSocketWithCompletionPort(SOCKET socket, HANDLE hCompletionPort, DWORD dwCompletionKey)
{
	HANDLE h = CreateIoCompletionPort((HANDLE) socket, hCompletionPort, dwCompletionKey, 0);
	return h == hCompletionPort;
}





/*
* Adds the A client context to the Context Map.
*
*
*/

BOOL IOCPS::AddClientContext(ClientContext *mp)
{

	m_ContextMapLock.Lock();
	unsigned int KeyID=mp->m_Socket;

	//
	// Check if we already have a such key. 
	//
	ClientContext *pTempContext=NULL;
	pTempContext=(ClientContext*)m_ContextMap[KeyID];
	if(pTempContext!=NULL)
	{
		CString msg;
		msg.Format("Dublicate Key! Disconnecting incoming client.");
		AppendLog(msg);
		AbortiveClose(mp);
		m_ContextMapLock.Unlock();
		return FALSE;
	}

	//
	// Add it to the Map. 
	//

	// What if this fail ? 
	mp->m_ID=KeyID;
	m_ContextMap[KeyID]=mp;
	m_NumberOfActiveConnections++;
	m_ContextMapLock.Unlock();
	return TRUE;
}



/*
* Closes all the Sockets and removes all the buffer and ClientContext.  
*
*/ 
void IOCPS::FreeClientContext()
{
	m_ContextMapLock.Lock();
	// First Delete all the objekts.
	POSITION pos = m_ContextMap.GetStartPosition ();
	while (pos != NULL) 
	{
		unsigned int iKey;
		ClientContext *pContext=NULL;
		m_ContextMap.GetNextAssoc (pos, iKey,pContext);
		if(pContext)
		{
			// Socket open we have to kill it.. 
			if(pContext->m_Socket>=0)
			{
				LINGER lingerStruct;
				lingerStruct.l_onoff = 1;
				lingerStruct.l_linger = 0;
				setsockopt( pContext->m_Socket, SOL_SOCKET, SO_LINGER,
					(char *)&lingerStruct, sizeof(lingerStruct) );
				// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
				CancelIo((HANDLE) pContext->m_Socket);
				//while (!HasOverlappedIoCompleted((LPOVERLAPPED)pContext)) 
				//	Sleep(2);
				closesocket( pContext->m_Socket );

			}
			pContext->m_Socket = INVALID_SOCKET;


			ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
#ifdef TRANSFERFILEFUNCTIONALITY		
			if (pContext->m_File.m_hFile != (unsigned int)INVALID_HANDLE_VALUE)
			{

				pContext->m_File.Close();
			}
#endif

			ReleaseBufferMap(&pContext->m_ReadBufferMap);
			ReleaseBufferMap(&pContext->m_SendBufferMap);


			delete pContext;

			CString msg;
			msg.Format("Removed Client=%s.", GetHostKeyName(iKey));
			AppendLog(msg);

		}
	}
	// Now remove all the keys.. 
	m_ContextMap.RemoveAll();
	m_ContextMapLock.Unlock(); 

	//
	// Remove The stuff in FreeContext list
	// 
	m_bAcceptConnections=FALSE;
	m_FreeContextListLock.Lock();
	ClientContext *pContext=NULL;
	pos = m_FreeContextList.GetHeadPosition ();
	while (pos != NULL) 
	{
		pContext = (ClientContext *)m_FreeContextList.GetNext (pos);
		if(pContext!=NULL)
		{
			pContext->m_Socket = INVALID_SOCKET;
			if(pContext)
				delete pContext;
			pContext=NULL;
		}
	}
	m_FreeContextList.RemoveAll();
	m_FreeContextListLock.Unlock();

}


void IOCPS::ProcessIOMessage(CIOCPBuffer *pOverlapBuff, ClientContext *pContext, DWORD dwSize)
{

	if(pOverlapBuff==NULL)
		return;

	//	Sleep(rand()%50);
	switch (pOverlapBuff->GetOperation())
	{

	case IOInitialize :
		OnInitialize(pContext,dwSize,pOverlapBuff);
		break;

	case IORead :
		OnRead(pContext,pOverlapBuff);
		break;	


	case IOReadCompleted :
		OnReadCompleted(pContext,dwSize,pOverlapBuff);
		break;


	case IOWrite :
		OnWrite(pContext,dwSize,pOverlapBuff);
		break;

	case IOWriteCompleted :
		OnWriteCompleted(pContext,dwSize,pOverlapBuff);
		break;

	case IOZeroByteRead : //  Workaround the the WSAENOBUFS error problem..See OnZeroByteRead. 
		OnZeroByteRead(pContext,pOverlapBuff);
		break;

	case IOZeroReadCompleted : //  Workaround the the WSAENOBUFS error problem.. 
		OnZeroByteReadCompleted(pContext,dwSize,pOverlapBuff);
		break;
#if defined TRANSFERFILEFUNCTIONALITY
	case IOTransmitFileCompleted : //  Workaround the the WSAENOBUFS error problem.. 
		OnTransmitFileCompleted(pContext,pOverlapBuff);
		break;
#endif

	case IOPostedPackage : 
		OnPostedPackage(pContext,pOverlapBuff);
		break;


	default:
		ReleaseBuffer(pOverlapBuff);
		break;

	} 
}

void IOCPS::OnInitialize(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{
	// Do some init here.. 

	// Notify new connection. 
	pContext->m_ContextLock.Lock();
	NotifyNewConnection(pContext);
	pContext->m_ContextLock.Unlock();
	/*
	Operations using the IO completion port will always complete in the order that they were submitted.
	Therefore we start A number of pendling read loops (R) and at last a Zero byte read to avoid the WSAENOBUFS problem.  	
	The number of m_iNumberOfPendlingReads should not be so big that we get the WSAENOBUFS problem. 
	*/
	// A ZeroByteLoop. EnterIOLoop is not needed here. Already done in previus call.
	AZeroByteRead(pContext,pOverlapBuff);
	
	// m_iNumberOfPendlingReads=1 by default. 
	for(int i=0;i<m_iNumberOfPendlingReads;i++)
	{
		EnterIOLoop(pContext); // One for each Read Loop
		ARead(pContext);
	}

}

void IOCPS::OnRead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff)
{
	// issue a read request 
	if(pContext&&!m_bShutDown)
	{
		if(pOverlapBuff==NULL)
		{
			pOverlapBuff=AllocateBuffer(IOReadCompleted);
			if(pOverlapBuff==NULL)
			{

				CString msg;
				msg.Format("FAILED TO Allocate buffer memory in OnRead %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return;
			}
		}
		if(pOverlapBuff!=NULL)
		{
			pOverlapBuff->SetOperation(IOReadCompleted);
			pOverlapBuff->SetupRead();
			if(m_bReadInOrder)
				MakeOrderdRead(pContext,pOverlapBuff);
			else
			{
				DWORD dwIoSize=0;
				ULONG			ulFlags = MSG_PARTIAL;
				UINT nRetVal = WSARecv(pContext->m_Socket, 
					pOverlapBuff->GetWSABuffer(),
					1,
					&dwIoSize, 
					&ulFlags,
					&pOverlapBuff->m_ol, 
					NULL);
				if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
				{
					if(WSAGetLastError()!=WSAENOTSOCK)
					{
#ifndef _DEBUG
						// Remove Unnecessary disconnect messages in release mode.. 
						if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
#endif
						{
							CString msg;
							msg.Format("Disconnect in Onread Possible Socket Error: %s",ErrorCode2Text(WSAGetLastError()));
							AppendLog(msg);
						}
					}
					ReleaseBuffer(pOverlapBuff);
					TRACE(">OnRead(%x)\r\n",pContext);
					DisconnectClient(pContext);
					ReleaseClientContext(pContext);
				}
			}
		}
	}
}


void IOCPS::OnPostedPackage(ClientContext *pContext, CIOCPBuffer *pOverlapBuff)
{
	if( !pContext )
	{
		AppendLog("FATAL ERROR OnPostedPackage pContext=NULL");
		return; 
	}

	if ( pOverlapBuff)
	{
		UINT nSize = 0;
		memmove(&nSize,pOverlapBuff->GetBuffer(),MINIMUMPACKAGESIZE);
		pContext->m_ContextLock.Lock();
		NotifyReceivedPackage(pOverlapBuff,nSize,pContext);
		pContext->m_ContextLock.Unlock();
		ReleaseBuffer(pOverlapBuff);
	}
	ReleaseClientContext(pContext);// Exit IOLoop	
}

void IOCPS::OnReadCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{

	if (dwIoSize == 0||pOverlapBuff==NULL)
	{
		CString msg;
		msg.Format("Disconnection in OnReadCompleted (dwIoSize == 0||pOverlapBuff==NULL) errcode: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		TRACE(">OnReadCompleted1(%x)\r\n",pContext);
		DisconnectClient(pContext);
		ReleaseClientContext(pContext);
		ReleaseBuffer(pOverlapBuff);
		return;
	}


	if(pContext)
	{
		//
		// Process The package assuming that it have a heap of size (MINIMUMPACKAGESIZE) 
		// That contains the size of the message. 
		//
		/*
		* Lock the context so that no other thread enters “ProcessPackage” function, 
		* this is necessary to process the package in order. (When IOCP is used with 
		* several working IO threads the packages can be processed in wrong order (even 
		* if the TCP protocol guarantees ordered stream) because of the operative 
		* system process scheduling.
		* Comment and source code Added 9/10/2005
		*/
		//pContext->m_ContextLock.Lock(); 
		//
		// Insure That the Packages arrive in order. 
		//
		if(m_bReadInOrder)
			pOverlapBuff=GetNextReadBuffer(pContext,pOverlapBuff);


		while(pOverlapBuff!=NULL)
		{
			//TRACE("R> %i\r\n",pOverlapBuff->GetSequenceNumber());

			// Mark that we are Using the buffer..
			pOverlapBuff->Use(dwIoSize);
#ifdef TRANSFERFILEFUNCTIONALITY
			if(!pContext->m_bFileReceivedMode)
#endif
				ProcessPackage(pContext,dwIoSize,pOverlapBuff);
#ifdef TRANSFERFILEFUNCTIONALITY
			else
				AddToFile(pContext,dwIoSize,pOverlapBuff);
#endif
			IncreaseReadSequenceNumber(pContext);
			pOverlapBuff=NULL;
			if(m_bReadInOrder)
				pOverlapBuff=GetNextReadBuffer(pContext);
		}
		ARead(pContext);
	}
}


/*
* Transmitted file Completed. 
*
*/
#if defined TRANSFERFILEFUNCTIONALITY
void IOCPS::OnTransmitFileCompleted(ClientContext *pContext, CIOCPBuffer *pOverlapBuff)
{
	pContext->m_ContextLock.Lock();
	NotifyFileCompleted(pContext);
	DisableSendFile(pContext);
	pContext->m_ContextLock.Unlock();
	ReleaseClientContext(pContext);// Exit IOLoop
	// pContext May not exist here. 
}

#endif


/*
* Assumes that Packages arrive with A MINIMUMPACKAGESIZE header and builds Packages that  
* are noticed by the virtual function NotifyReceivedPackage 
*
*/


void IOCPS::ProcessPackage(ClientContext *pContext, DWORD dwIoSize, CIOCPBuffer *pOverlapBuff)
{
	//
	// We may have Several Pending reads. And therefor we have to 
	// check and handle partial Messages.  
	//

	//
	// First handle partial packages. 
	//
	CIOCPBuffer *pBuffPartialMessage=NULL;
	pBuffPartialMessage=pContext->m_pBuffOverlappedPackage;

	// if we had a partial message in previous message process. 
	if ( pBuffPartialMessage!=NULL )
	{

		// Check how big the message is...
		UINT nUsedBuffer=pBuffPartialMessage->GetUsed();

		if ( nUsedBuffer < MINIMUMPACKAGESIZE )
		{
			//Header to small.. 
			UINT nHowMuchIsNeeded=MINIMUMPACKAGESIZE-nUsedBuffer;
			// too little Data to determine the size. 
			if ( nHowMuchIsNeeded > pOverlapBuff->GetUsed() )
			{
				AddAndFlush(pOverlapBuff,pBuffPartialMessage,pOverlapBuff->GetUsed());
				// Release the buffer if not used. 
				if ( pOverlapBuff!=NULL )
				{
					ReleaseBuffer(pOverlapBuff);
				}
				return; // wait for more data..
			}else
				AddAndFlush(pOverlapBuff,pBuffPartialMessage,nHowMuchIsNeeded);
		}
		// Check how big the message is...
		nUsedBuffer=pBuffPartialMessage->GetUsed();
		if ( nUsedBuffer >= MINIMUMPACKAGESIZE )
		{
			// Get The size.. 
			UINT nSize = 0;
			UINT nHowMuchIsNeeded=0;
			memmove(&nSize,pBuffPartialMessage->GetBuffer(),MINIMUMPACKAGESIZE);
			// The Overlapped Package is good. Never send packages bigger that the MAXIMUMPACKAGESIZE-MINIMUMPACKAGESIZE
			if ( nSize<=(MAXIMUMPACKAGESIZE-MINIMUMPACKAGESIZE) )
			{
				nHowMuchIsNeeded=nSize-(nUsedBuffer-MINIMUMPACKAGESIZE);
				// If we need just a little data add it.. 
				if ( nHowMuchIsNeeded<=pOverlapBuff->GetUsed() )
				{
					// Add the remain into pBuffPartialMessage. 
					AddAndFlush(pOverlapBuff,pBuffPartialMessage,nHowMuchIsNeeded);
					NotifyReceivedPackage(pBuffPartialMessage,nSize,pContext);
					ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
					pContext->m_pBuffOverlappedPackage=NULL;
				}else
				{
					// Put everything in.. 
					AddAndFlush(pOverlapBuff,pBuffPartialMessage,pOverlapBuff->GetUsed());
				}

			}
			else
			{
				CString msg;
				msg.Format("Package size error > MAXIMUMPACKAGESIZE-MINIMUMPACKAGESIZE: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
				ReleaseBuffer(pOverlapBuff);
				pOverlapBuff=NULL;
				ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
				pContext->m_pBuffOverlappedPackage=NULL;
#ifdef SIMPLESECURITY
				AddToBanList(pContext->m_Socket);
#endif
				DisconnectClient(pContext);
				return;

			}
		}
	}


	//
	// Process the incoming byte stream in pOverlapBuff
	//
	bool done;
	do 
	{
		UINT nUsedBuffer=pOverlapBuff->GetUsed();
		done=true;	
		if ( nUsedBuffer >= MINIMUMPACKAGESIZE )
		{
			UINT nSize = 0;
			memmove(&nSize,pOverlapBuff->GetBuffer(),MINIMUMPACKAGESIZE);
			// We Have a full Package..
			if ( nSize==nUsedBuffer-MINIMUMPACKAGESIZE )
			{
				NotifyReceivedPackage(pOverlapBuff,nSize,pContext);
				pOverlapBuff->EmptyUsed();
				done = true;
			}else if ( nUsedBuffer-MINIMUMPACKAGESIZE >nSize )
			{
				// We have more data 
				CIOCPBuffer *pBuff=SplitBuffer(pOverlapBuff,nSize+MINIMUMPACKAGESIZE);
				NotifyReceivedPackage(pBuff,nSize,pContext);
				ReleaseBuffer(pBuff);
				// loop again, we may have another complete message in there...
				done = false;
			}else if ( nUsedBuffer-MINIMUMPACKAGESIZE<nSize && nSize<MAXIMUMPACKAGESIZE)
			{
				//
				// The package is overlapped between this byte chunk stream and the next. 
				//
				pContext->m_pBuffOverlappedPackage=pOverlapBuff;
				pOverlapBuff=NULL;
				TRACE("new Partial Buffer >\r\n");
				done=true;
			}else if ( nSize>MAXIMUMPACKAGESIZE )
			{			
				//pOverlapBuff->DUMP();
				CString msg;
				msg.Format("Messagesize error: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
#ifdef SIMPLESECURITY
				AddToBanList(pContext->m_Socket);
#endif
				ReleaseBuffer(pOverlapBuff);
				pOverlapBuff=NULL;
				DisconnectClient(pContext);
				break; 
			}
		}else if( nUsedBuffer>0 )
		{   //  Header  too small. 
			// nUsedBuffer < MINIMUMPACKAGESIZE
			// Add it to to the package overlapped buffer. 	
			// Let the remain be handled later. 
			pContext->m_pBuffOverlappedPackage=pOverlapBuff;
			pOverlapBuff=NULL;
			done=true;
		}
	} while ( !done );
	// Release the buffer if not used. 
	if ( pOverlapBuff!=NULL )
	{
		ReleaseBuffer(pOverlapBuff);
	}
}



void IOCPS::OnWrite(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{
	if(pContext!=NULL&&pContext->m_Socket!=INVALID_SOCKET)
	{	
		//pContext->m_ContextLock.Lock();
		if(m_bSendInOrder)
			pOverlapBuff=GetNextSendBuffer(pContext,pOverlapBuff);
#ifdef _DEBUG
		if(pOverlapBuff==NULL)
			TRACE("Write not in order (%x)\r\n",pContext);
#endif 		
		while(pOverlapBuff!=NULL)
		{

			/*
			* Comments about bug in OnWrite() added 051227.. 
			* 
			* This BUG was difficult to find. The bug was found after  6 hours of 
			* extensive debugging  with several debug tools as Rational Test Suite, 
			* SoftICe , VC++ DEBUG, GLOWCODE, etc.  I Found that in some rarely bizarre 
			* cases  (when a client rapidly disconnect & reconnect, etc..)  we get an 
			* access violation , etc. First of all we had one ReleaseClientContext to many 
			* in OnWrite() which caused access violation. Second when I remove it, I found 
			* that sometimes the client specific data (e.g. ClientContext) does not removed/relesed 
			* from memory, even if the client is disconnected. The reason in not 
			* intuitive and do not ask me how I figured it out. The problem occurs 
			* when an send is not ordered (see http://www.codeproject.com/internet/iocp_server_client.asp, 
			* section "3.6.2 The package reordering problem" for more information ) and 
			* we call the function GetNextSendBuffer(pContext,pOverlapBuff); (above) in Onwrite(..), 
			* to get the correct buffer to process. At exactly this point the remote client disconnects
			* and this leads to the bug. Now I got tired of explaining this hassling stuff, so lets 
			* go to the business the fix is below.. 
			*
			*   
			*/  


			pOverlapBuff->SetOperation(IOWriteCompleted);
			pOverlapBuff->SetupWrite();	
			ULONG ulFlags = MSG_PARTIAL;
			DWORD dwSendNumBytes = 0;

			int nRetVal = WSASend(pContext->m_Socket, 
				pOverlapBuff->GetWSABuffer(),
				1,
				&dwSendNumBytes, 
				ulFlags,
				&pOverlapBuff->m_ol, 
				NULL);

			if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING ) 
			{
				if(WSAGetLastError()!=WSAENOTSOCK)
				{
#ifndef _DEBUG
					// Remove Unnecessary disconnect messages in release mode.. 
					if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
#endif	
					{	
						CString msg;
						msg.Format("Error in OnWrite..: %s",ErrorCode2Text(WSAGetLastError()));
						AppendLog(msg);
					}
				}
				ReleaseBuffer(pOverlapBuff);
				DisconnectClient(pContext);
				pOverlapBuff=NULL;
				/* "the bug fix 051227": Check if we need to go out of some more pending IO.
				(if our send is not processed in order) */ 	
				IncreaseSendSequenceNumber(pContext);
				if(m_bSendInOrder&&!m_bShutDown)
					pOverlapBuff=GetNextSendBuffer(pContext);
				TRACE(">OnWrite(%x)\r\n",pContext);
				ReleaseClientContext(pContext); 	// pContext may not exist after this call 	
				//break; // removed due to fix. 
			}else
			{
				IncreaseSendSequenceNumber(pContext);
				//TRACE("W> %i\r\n",pOverlapBuff->GetSequenceNumber());
				pOverlapBuff=NULL;
				if(m_bSendInOrder&&!m_bShutDown)
					pOverlapBuff=GetNextSendBuffer(pContext);
			}
		}

	}else
	{
		TRACE(">OnWrite2(%x)\r\n",pContext);
		ReleaseBuffer(pOverlapBuff);
		ReleaseClientContext(pContext); //Later Implementation 
	}

}



void IOCPS::OnWriteCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{
	if(pContext!=NULL)
	{

		if (pOverlapBuff!=NULL)
		{
			if(pOverlapBuff->GetUsed()!=dwIoSize)
			{

				CString msg;
				msg.Format("The whole message was not Sent.: %s",ErrorCode2Text(WSAGetLastError()));
				ReleaseBuffer(pOverlapBuff);
				AppendLog(msg);
			}else
			{
				pContext->m_ContextLock.Lock();
				NotifyWriteCompleted(pContext,dwIoSize,pOverlapBuff);
				pContext->m_ContextLock.Unlock();
				ReleaseBuffer(pOverlapBuff);
			}

		}
		//
		// We have finished a Complete LOOP, if no pending IO is in the competition port remove the client. 
		// We have always a Read request in the IO port if we have a Connection 
		//
		//TRACE(">OnWriteCompleted()\r\n");
		//ExitIOLoop(pContext);
		ReleaseClientContext(pContext);
	}
}



BOOL IOCPS::ASend(int ClientId, CIOCPBuffer *pOverlapBuff)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(ClientId);
	if (pContext == NULL)
	{
		m_ContextMapLock.Unlock();
		ReleaseBuffer(pOverlapBuff);
		return FALSE;
	}
	bRet=ASend(pContext,pOverlapBuff); // if ASend(pContext,..) Fails, ASend Takes Care of The buffer.. 
	m_ContextMapLock.Unlock();
	return bRet;
}



/*
* Functions are used to post an buffer into the IOCP port 	
* This functions can be used instead of the  function addJob(..) (thread worker Queue). 
* The function post an puffer into IOCP. (simulates an received package)  
* This function is nessesary to split heavy computation operation into several 
* parts. (automate machine) 
*
*/

BOOL IOCPS::PostPackage(int iClientId, CIOCPBuffer *pOverlapBuff)
{

	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(iClientId);
	if (pContext == NULL)
	{
		m_ContextMapLock.Unlock();
		ReleaseBuffer(pOverlapBuff);
		return FALSE;
	}
	bRet=PostPackage(pContext,pOverlapBuff); // if ASend(pContext,..) Fails, ASend Takes Care of The buffer.. 
	m_ContextMapLock.Unlock();
	return bRet;
}


BOOL IOCPS::PostPackage(ClientContext *pContext,CIOCPBuffer *pOverlapBuff)
{
	if( pContext==NULL ||! m_bServerStarted )
	{
		if ( pOverlapBuff )
			ReleaseBuffer(pOverlapBuff);
		return FALSE;
	}

	if ( pContext->m_Socket!=INVALID_SOCKET && pOverlapBuff!=NULL )
	{
		EnterIOLoop(pContext); 	
		pOverlapBuff->SetOperation(IOPostedPackage);
		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, pOverlapBuff->GetUsed(), (DWORD) pContext, &pOverlapBuff->m_ol);
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
			TRACE(">POST(%x) FAILED.. \r\n",pContext);
			ReleaseClientContext(pContext); // Because of EnterIOLoop. 
			return FALSE;
		}
		return TRUE;
	}

	// Some Thing is Wrong Release the buffer and return. 
	if ( pOverlapBuff )
	{
		ReleaseBuffer(pOverlapBuff);
		pOverlapBuff=NULL;
	}

	return FALSE;
}



BOOL IOCPS::ASendToAll(CIOCPBuffer *pBuff)
{

	if(pBuff==NULL)
		return FALSE;

	BOOL bRet=TRUE;
	m_ContextMapLock.Lock();
	POSITION pos = m_ContextMap.GetStartPosition ();
	while (pos != NULL) 
	{
		unsigned int iKey;
		ClientContext *pContext=NULL;
		m_ContextMap.GetNextAssoc (pos, iKey,pContext);
		if(pContext!=NULL)
		{
			CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
			if(pOverlapBuff!=NULL)
			{
				if(pOverlapBuff->AddData(pBuff->GetBuffer(),pBuff->GetUsed()))
				{
					if(!ASend(pContext,pOverlapBuff))
					{
						//ReleaseBuffer(pOverlapBuff);
						bRet&=FALSE;
					}

				}else
				{
					CString msg;
					msg.Format("Buffer Error in  ASendToAll, AddData Failed: %s",ErrorCode2Text(WSAGetLastError()));
					AppendLog(msg);
					ReleaseBuffer(pOverlapBuff);
					bRet&=FALSE;
					break;	
				}
			}else
			{
				CString msg;
				msg.Format("Could not allocate memory ASendToAll: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
				bRet=FALSE;
				break;
			}
		}
	}
	m_ContextMapLock.Unlock(); 
	ReleaseBuffer(pBuff);
	return bRet;
}


/*
*	Returns a Client in ContextMap 
* (OBS! NOT THREAD SAFE) 
* Always call this function when you have lock the ClientContext: 
* m_ContextLock.Lock();
* // Some Code... 
* pContext=FindClient(iID);
* // Some Code.. 
* m_ContextLock.Unlock();
*/

ClientContext* IOCPS::FindClient(unsigned int iClient)
{
	ClientContext* pCC=NULL;	
	if(iClient<=0)
		return NULL;
	pCC=(ClientContext*)m_ContextMap[iClient];
	return pCC;
}

CString IOCPS::GetHostKeyName(SOCKET socket)
{
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);

	BOOL bResult = getpeername(socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);

	// return bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
	//TRACE("GetHostKeyName-> Socket nr: %i\r\n",socket);
	CString szReturn;

	if (bResult != INVALID_SOCKET)
		szReturn.Format("%d>%s_%d",socket,inet_ntoa(sockAddr.sin_addr), sockAddr.sin_port);
	else
		szReturn.Empty();

	return szReturn;
}




CString IOCPS::GetHostAddress(SOCKET socket)
{
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);

	BOOL bResult = getpeername(socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
	CString szReturn;

	if (bResult != INVALID_SOCKET)
		szReturn.Format("%s", inet_ntoa(sockAddr.sin_addr));
	else
		szReturn.Empty();

	return szReturn;
}


/*
* Makes An Asyncorn Send. 
*
*/
BOOL IOCPS::ASend(ClientContext *pContext,CIOCPBuffer *pOverlapBuff)
{
	if(pContext==NULL||!m_bServerStarted)
		return FALSE;
	// We must be safe before we start doing things. 
#ifdef TRANSFERFILEFUNCTIONALITY
	if(pContext->m_Socket!=INVALID_SOCKET&&pOverlapBuff!=NULL&&!pContext->m_bFileSendMode)
#else
	if(pContext->m_Socket!=INVALID_SOCKET&&pOverlapBuff!=NULL)
#endif
	{
		//
		// Important!! Notifies that the socket and the structure  
		// pContext have an Pending IO operation ant should not be deleted.
		// This is necessary to avoid Access violation. 
		//
		EnterIOLoop(pContext); 

		//
		// If we are sending in order
		//
		if(m_bSendInOrder)
			SetSendSequenceNumber(pContext,pOverlapBuff); 


		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, pOverlapBuff->GetUsed(), (DWORD) pContext, &pOverlapBuff->m_ol);
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
			TRACE(">ASend(%x)\r\n",pContext);
			ReleaseClientContext(pContext); // Because of EnterIOLoop. 
			return FALSE;
		}
		return TRUE;
	}
	// Some Thing is Wrong Release the buffer and return. 
	ReleaseBuffer(pOverlapBuff);
	pOverlapBuff=NULL;
	return FALSE;
}
/*
* Disconnects the Client. 
*
*
*/

void IOCPS::DisconnectClient(ClientContext *pContext, BOOL bGraceful)
{	
	if(pContext!=NULL)
	{	
		pContext->m_ContextLock.Lock();
		BOOL bDisconnect=pContext->m_Socket!=INVALID_SOCKET;
		pContext->m_ContextLock.Unlock();
		// If we have an active  socket close it. 
		if(bDisconnect)
		{		

			//
			// Remove it From m_ContextMap. 
			//
			m_ContextMapLock.Lock();
			BOOL bRet=FALSE;
			//Remove it from the m_ContextMapLock,, 
			if(m_ContextMap[pContext->m_Socket]!=NULL)
			{
				bRet=m_ContextMap.RemoveKey(pContext->m_Socket);
				if(bRet)
					m_NumberOfActiveConnections--;
			}	
			m_ContextMapLock.Unlock();


			TRACE("Client %i, Disconnected %x.\r\n",pContext->m_Socket,pContext);

			pContext->m_ContextLock.Lock();
			// Notify that we are going to Disconnect A client. 
			NotifyDisconnectedClient(pContext);
			pContext->m_ContextLock.Unlock();

#ifdef SIMPLESECURITY
			if(m_bOneIPPerConnection)
			{

				//
				//  Remove the IP address from list.. 
				//	

				sockaddr_in sockAddr;
				memset(&sockAddr, 0, sizeof(sockAddr));
				int nSockAddrLen = sizeof(sockAddr);	
				int iResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);


				if (iResult != INVALID_SOCKET)
				{
					void* pVoid=(void*)sockAddr.sin_addr.S_un.S_addr; 
					m_OneIPPerConnectionLock.Lock();
					POSITION pos=m_OneIPPerConnectionList.Find(pVoid);
					if ( pos!=NULL )
					{
						m_OneIPPerConnectionList.RemoveAt(pos); 
					}
					m_OneIPPerConnectionLock.Unlock();	
				}

			}
#endif	

			//
			// If we're supposed to abort the connection, set the linger value
			// on the socket to 0.
			//
			if ( !bGraceful ) 
			{

				LINGER lingerStruct;
				lingerStruct.l_onoff = 1;
				lingerStruct.l_linger = 0;
				setsockopt( pContext->m_Socket, SOL_SOCKET, SO_LINGER,
					(char *)&lingerStruct, sizeof(lingerStruct) );
			}
			//
			// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
			CancelIo((HANDLE) pContext->m_Socket);
			closesocket( pContext->m_Socket );
			pContext->m_Socket = INVALID_SOCKET;

		}
#ifdef _DEBUG 
		TRACE("Context %x is is disconnected but not removed from Context map \r\n",pContext);
#endif 
	}
}




void IOCPS::DisconnectClient(unsigned int iID)
{
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(iID);
	if (pContext == NULL)
	{
		m_ContextMapLock.Unlock();
		return;
	}
	DisconnectClient(pContext);	
	m_ContextMapLock.Unlock();

}

void IOCPS::ReleaseBufferMap(BufferMap *map)
{	
	POSITION pos = map->GetStartPosition ();
	while (pos != NULL) 
	{
		unsigned int iKey;
		CIOCPBuffer *pBuffer=NULL;
		map->GetNextAssoc (pos, iKey,pBuffer);
		if(pBuffer!=NULL)
			ReleaseBuffer(pBuffer);
	}
	map->RemoveAll();
}




/*
* Same as Disconnect Client but we does not try to 
* remove the context from the Context Map m_ContextMap.
*
*/

void IOCPS::AbortiveClose(ClientContext *mp)
{
	// Notify that we are going to Disconnect A client. 
	NotifyDisconnectedClient(mp);

	// If we have an active  socket close it. 
	if(mp->m_Socket>=0)
	{

		LINGER lingerStruct;
		lingerStruct.l_onoff = 1;
		lingerStruct.l_linger = 0;
		setsockopt( mp->m_Socket, SOL_SOCKET, SO_LINGER,
			(char *)&lingerStruct, sizeof(lingerStruct) );	
		//
		// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
		CancelIo((HANDLE) mp->m_Socket);
		closesocket( mp->m_Socket );
		mp->m_Socket = INVALID_SOCKET;
	}

	// Move the Context to the free context list or kill it. 
	m_FreeContextListLock.Lock();
	if(m_FreeContextList.GetCount()<m_iMaxNumberOfFreeContext||m_iMaxNumberOfFreeContext==0)
		m_FreeContextList.AddHead((void*)mp);
	else
	{
		if(mp)
			delete mp;
	}
	m_FreeContextListLock.Unlock();

}


/*
* Closes the Server and frees the memory. 
*
*
* We are leaking some small amount of memory (OVERLAPPEDSTRUKTUR)
*
*
*/

// Error in Disconnect.. (some how we have to wait until the Competionport is finished with the data). 

void IOCPS::ShutDown()
{
	CString msg;
	if(m_bServerStarted)
	{
#if defined SIMPLESECURITY	
		m_OneIPPerConnectionLock.Lock();
		if(!m_OneIPPerConnectionList.IsEmpty())
			m_OneIPPerConnectionList.RemoveAll();
		m_OneIPPerConnectionLock.Unlock();

		m_BanIPLock.Lock();
		m_BanIPList.RemoveAll();
		m_BanIPLock.Unlock();
#endif

		AppendLog("Shutdown initialized.");

		m_bAcceptConnections=FALSE;

		AppendLog("Sending shutdown signal to logical worker threads.");
		ShutDownWorkers();

		// We Let the IOWorker Take care of the last packets and die. 
		AppendLog("Disconnecting all the Connections...");
		DisconnectAll();



		AppendLog("Sending shutdown signal to IO worker threads.");
		m_bShutDown=TRUE;
		ShutDownIOWorkers();


		AppendLog("Closing Completion port..");
		// Close the CompletionPort and stop any more requests (Stops the Listner) 
		CloseHandle(m_hCompletionPort);
		if(m_nPortNumber>0)
		{
			AppendLog("Closing listner thread.");
			WSACloseEvent(m_hEvent);
			closesocket(m_socListen);
		}
		AppendLog("Deallocate memory used for Clients. ");
		FreeClientContext();
		AppendLog("Deallocate memory used for Buffers. ");
		FreeBuffers();

		m_bServerStarted=FALSE;
	}
}









/* 
OnZeroByteRead(ClientContext *pContext) the workaround 
the WSAENOBUFS error problem.  


This Bugg was a very difficult one.. When I stresstested this server code the
server hung after a while. I first thougt that this was a memleak problem or 
deadlock problem. But after a some hours I found that it is because of the system 
WSAENOBUFS error. 

With every overlapped send or receive operation, it is probable that 
the data buffers submitted will be locked. When memory is locked, it 
cannot be paged out of physical memory. The operating system imposes 
a limit on the amount of memory that may be locked. When this limit 
is reached, overlapped operations will fail with the WSAENOBUFS error. 
If a server posts many overlapped receives on each connection, this 
limit will be reached as the number of connections grow. If a server a
nticipates handling a very high number of concurrent clients, the server 
can post a single zero byte receive on each connection. Because there is 
no buffer associated with the receive operation, no memory needs to be 
locked. With this approach, the per-socket receive buffer should be left 
intact because once the zero-byte receive operation completes, the server 
can simply perform a non-blocking receive to retrieve all the data buffered 
in the socket's receive buffer. There is no more data pending when the 
non-blocking receive fails with WSAEWOULDBLOCK. This design would be for 
servers that require the maximum possible concurrent connections while 
sacrificing the data throughput on each connection.
Of course, the more you are aware of how the clients will be interacting 
with the server, the better. In the previous example, a non-blocking receive 
is performed once the zero-byte receive completes to retrieve the buffered 
data. If the server knows that clients send data in bursts, then once the 
zero-byte receive completes, it may post one or more overlapped receives 
in case the client sends a substantial amount of data 
(greater than the per-socket receive buffer that is 8 KB by default). */
void IOCPS::OnZeroByteRead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff)
{

	if(pContext)
	{
		// issue a Zeroread request 
		DWORD dwIoSize=0;
		ULONG			ulFlags = MSG_PARTIAL;
		if(pOverlapBuff==NULL)
		{
			pOverlapBuff=AllocateBuffer(IOZeroReadCompleted);
			if(pOverlapBuff==NULL)
			{

				CString msg;
				msg.Format("FAILED TO Allocate buffer memory in OnZeroByteRead: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return; 
			}
		}
		pOverlapBuff->SetOperation(IOZeroReadCompleted);
		pOverlapBuff->SetupZeroByteRead();


		UINT nRetVal = WSARecv(pContext->m_Socket, 
			pOverlapBuff->GetWSABuffer(),
			1,
			&dwIoSize, 
			&ulFlags,
			&pOverlapBuff->m_ol, 
			NULL);

		if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
		{
			if(WSAGetLastError()!=WSAENOTSOCK)
			{
#ifndef _DEBUG
				// Remove Unnecessary disconnect messages in release mode.. 
				if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
#endif	
				{
					CString msg;
					msg.Format("Disconnect in ZeroByteRead Possible Socket Error: %s",ErrorCode2Text(WSAGetLastError()));
					AppendLog(msg);
				}
			}
			ReleaseBuffer(pOverlapBuff);
			TRACE(">OnZeroByteRead(%x)\r\n",pContext);
			DisconnectClient(pContext);			
			ReleaseClientContext(pContext); //Later Implementation 
		}
	}

}

void IOCPS::OnZeroByteReadCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{

	if(pContext)
	{
		// Make a Loop. 
		AZeroByteRead(pContext,pOverlapBuff);	
	}
}


/*
* Makes a asynchrony Read by posting a IORead message into completion port 
* who invoces a Onread.
*
* The read is not made directly to distribute CPU power fairly between the connections. 
*/

BOOL IOCPS::ARead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff)
{

	if (pContext == NULL)
		return FALSE;

	if(pContext->m_Socket!=INVALID_SOCKET )
	{
		if(pOverlapBuff==NULL) 
			pOverlapBuff=AllocateBuffer(IORead);
		
			
		if(pOverlapBuff==NULL) 
		{			
		  AppendLog("AllocateBuffer(IORead) == NULL.");
		  ReleaseClientContext(pContext);
		  return FALSE;
		}

		pOverlapBuff->SetOperation(IORead);
		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pOverlapBuff->m_ol);  	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
			TRACE(">ARead(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			return FALSE;
		}

	}else
	{
		TRACE(">ARead2(%x)\r\n",pContext);
		ReleaseBuffer(pOverlapBuff);
		ReleaseClientContext(pContext);// Take care of it.
		return FALSE;
	}
	return TRUE;
}

/*
* A workaround the WSAENOBUFS error problem. (For more info please see OnZeroBytesRead  
* 
* Unlock the memory used by the OVELAPPED struktures. 
*
*/
BOOL IOCPS::AZeroByteRead(ClientContext *pContext, CIOCPBuffer *pOverlapBuff)
{
	if (pContext == NULL)
		return FALSE;

	if(pContext->m_Socket!=INVALID_SOCKET )
	{
		if(pOverlapBuff==NULL) 
			pOverlapBuff=AllocateBuffer(IOZeroByteRead);
		
		if(pOverlapBuff==NULL) 
		{			
		  AppendLog("AllocateBuffer(IOZeroByteRead) == NULL.");
		  ReleaseClientContext(pContext);
		  return FALSE;
		}

		pOverlapBuff->SetOperation(IOZeroByteRead);

		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pOverlapBuff->m_ol); 	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
			DisconnectClient(pContext);
			TRACE(">OnZeroByteRead(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			CString msg;
			msg.Format("Disconnect in AZeroByteRead Possible Socket Error: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			return FALSE;
		}

	}else
	{
		TRACE(">OnZeroByteRead2(%x)\r\n",pContext);
		ReleaseBuffer(pOverlapBuff);
		ReleaseClientContext(pContext);// Take care of it.
		return FALSE;
	}
	return TRUE;
}




CString IOCPS::ErrorCode2Text(DWORD dw)
{
	CString error="";
	// Put your own common error text here (give more explaination etc..) 
	switch(dw)
	{
	case WSAEFAULT:
		error="WSAEFAULT	The buf parameter is not completely contained in a valid part of the user address space.";
		break; 
	case WSAENOTCONN:
		error="WSAENOTCONN	The socket is not connected."; 
		break;
	case WSAEINTR:
		error="WSAEINTR	The (blocking) call was canceled through WSACancelBlockingCall.	"; 
		break;
	case WSAENOTSOCK:
		error=" WSAENOTSOCK	The descriptor s is not a socket."; 
		break; 
	case WSANOTINITIALISED:
		error="WSANOTINITIALISED: A successful WSAStartup call must occur before using this function.";
		break; 
	case WSAENETDOWN:
		error="WSAENETDOWN	The network subsystem has failed."; 
		break;
	case WSAEINPROGRESS:
		error="WSAEINPROGRESS	A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; 
		break;
	case WSAENETRESET:
		error=" WSAENETRESET	The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress."; 
		break; 
	case WSAEOPNOTSUPP:
		error="WSAEOPNOTSUPP	MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.	"; 
		break; 
	case WSAESHUTDOWN:
		error="WSAESHUTDOWN	The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH."; 
		break;
	case WSAEWOULDBLOCK:
		error=" WSAEWOULDBLOCK	The socket is marked as nonblocking and the receive operation would block.	"; 
		break; 
	case WSAEMSGSIZE:
		error=" WSAENOTSOCK		The message was too large to fit into the specified buffer and was truncated."; 
		break;
	case WSAEINVAL:
		error="WSAEINVAL	The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.	"; 
	case WSAECONNABORTED:
		error=" 	WSAECONNABORTED	The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable."; 
		break; 
	case WSAETIMEDOUT:
		error="WSAETIMEDOUT	The connection has been dropped because of a network failure or because the peer system failed to respond.	"; 
		break; 
	case WSAECONNRESET:
		//error="WSAECONNRESET	The virtual circuit was reset by the remote side executing a hard or abortive close."; 
		error="WSAECONNRESET Connection dropped..";
		break;

	default:
		error="";  
		break;
	}

	// Use system format..  
	if(error.IsEmpty())
	{
		LPVOID lpMsgBuf;
		error="";
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );
		error.Format("%s",lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	return error;
}


/*
* Notifyes that this Client Context Strukture is currently in the 
* IOCompetetion lopp and are used by a another thread. 
* This funktion and ExitIOLoop is used to avoid possible Access Violation 
*/
void IOCPS::EnterIOLoop(ClientContext *pContext)
{
	if(pContext!=NULL)
	{
		pContext->m_ContextLock.Lock();
		pContext->m_nNumberOfPendlingIO++;
		pContext->m_ContextLock.Unlock();
	}
}

/*
* Notifies that the ClientContext is no longer in used by thread x, and 
* have been removed from the competition port. This function decreses the  
* m_nNumberOfPendlingIO and returns it. 
* 
* if it return zero (0) then it is safe to delete the structure from the heap. 
*/


int IOCPS::ExitIOLoop(ClientContext *pContext)
{
	int nNumberOfPendlingIO=0;
	if(pContext!=NULL)
	{
		pContext->m_ContextLock.Lock();
		pContext->m_nNumberOfPendlingIO--;
		nNumberOfPendlingIO=pContext->m_nNumberOfPendlingIO;
#ifdef _DEBUG
		if(nNumberOfPendlingIO<0)
		{
			TRACE("Strange nNumberOfPendlingIO ERROR\r\n");
		}
		if(pContext->m_Socket==INVALID_SOCKET)
			TRACE("ExitIOLoop->nNumberOfPendlingIO %i, Socket: %i (%x)\r\n", pContext->m_nNumberOfPendlingIO,pContext->m_Socket,pContext);
#endif
		pContext->m_ContextLock.Unlock();

	}
	return nNumberOfPendlingIO; 
}


/*
* Just fakes that the client side have closed the connection.. 
* We leave everyting to the IOWorkers to handle with Disconnectclient. 
*/
void IOCPS::DisconnectAll()
{
	m_ContextMapLock.Lock();
	// First Delete all the objects.
	int numberofItems=m_ContextMap.GetCount();
	POSITION pos = m_ContextMap.GetStartPosition ();
	while (pos != NULL) 
	{
		unsigned int iKey;
		ClientContext *pContext=NULL;
		m_ContextMap.GetNextAssoc (pos, iKey,pContext);
		DisconnectClient(pContext);
	}
	m_ContextMapLock.Unlock(); 

#ifdef _DEBUG
	m_BufferListLock.Lock();
	int nSize=m_BufferList.GetCount();

	if(nSize>0)
	{
		TRACE("Warning Buffer is still in use even if all users are gone. %i Buffers are inuse state. \r\n",nSize);
		/*afxDump.SetDepth( 2 );
		afxDump << "Buffer: " << &m_BufferList << "\n";*/
		CIOCPBuffer *pBuff=NULL;
		POSITION pos = m_BufferList.GetHeadPosition ();
		while (pos != NULL) 
		{
			pBuff = (CIOCPBuffer *)m_BufferList.GetNext (pos);
			if(pBuff)
			{
				TRACE("pBuff(%x)->GetOperation()=%i\r\n",pBuff,pBuff->GetOperation());
			}
		}


	}else
		TRACE("BUFFER is now Empty\r\n");
	m_BufferListLock.Unlock();

#endif

}






/*
* Shuttingdown the IOWOrkers.. 
* 
* We put a NULL in CompletionPort and set the m_bShutDown FLAG.
* Then we wait for the IOWorkes to finish the works in the CompletionPort and exit. 
*
*/



void IOCPS::ShutDownIOWorkers()
{
	DWORD dwExitCode;
	m_bShutDown=TRUE;
	// Should wait for All IOWorkers to Shutdown.. 
	BOOL bIOWorkersRunning=TRUE;
	CWinThread* pThread=NULL;
	while(bIOWorkersRunning)
	{
		// Send Empty Message into CompletionPort so that the threads die. 
		if(bIOWorkersRunning)
			PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) NULL, NULL);
		//	Sleep(60);
		// Check if the IOWorkers are terminated.. 	
		POSITION pos = m_IOWorkerList.GetHeadPosition ();
		while (pos != NULL) 
		{
			pThread = (CWinThread* )m_IOWorkerList.GetNext (pos);
			if(pThread)
			{
				if (::GetExitCodeThread (pThread->m_hThread, &dwExitCode)&&dwExitCode == STILL_ACTIVE) 
					bIOWorkersRunning=TRUE;
				else
					bIOWorkersRunning=FALSE;
			}

		}

	}
	m_IOWorkerList.RemoveAll();

}






/*
* Sets the number of Workers (NOT IOWorkers that deals with Send/Receive  
*
*/




BOOL IOCPS::SetWorkers(int nThreads)
{
	int iNumberToKill=0;
	int iNumberToStart=0;

	m_WorkerThreadMapLock.Lock();
	int iNumberOfThreads=m_WorkerThreadMap.GetCount();
	m_WorkerThreadMapLock.Unlock();

	if(nThreads<iNumberOfThreads)
		iNumberToKill=iNumberOfThreads-nThreads;
	else
		iNumberToStart=nThreads-iNumberOfThreads;

	// No interference while admin the threads. 
	BOOL bAcceptJobs=m_bAcceptJobs;
	m_bAcceptJobs=FALSE;





	//
	// if nThreads is bigger than our current thread count, remove all excess threads
	//

	//
	// Kill some of the workers. 
	// ej helt klart... 

	m_WorkerThreadMapLock.Lock();
	POSITION pos = m_WorkerThreadMap.GetStartPosition ();
	while (pos != NULL&&iNumberToKill>0) 
	{
		WORD strKey;
		CWinThread* pThread=NULL;
		m_WorkerThreadMap.GetNextAssoc (pos, strKey,(void *&)pThread);
		if(pThread)
		{

			HANDLE hThread = pThread->m_hThread;

			// notify the thread that it should die. 
			pThread->m_hThread=INVALID_HANDLE_VALUE;  
			// now let the thread terminate itself

			//::GetExitCodeThread(hThread, &dwExit) && (dwExit != 0xdead)

			::ResumeThread(hThread);


			DWORD dwExit = NULL;
			while(::GetExitCodeThread(hThread, &dwExit) && (dwExit != 0xdead))
			{
				::Sleep(50);	// give it a chance to finish
			}
			::CloseHandle (hThread);
			iNumberToKill--;
			m_WorkerThreadMap.RemoveKey(strKey);
			delete[] pThread;
		}	
	}
	m_WorkerThreadMapLock.Unlock();

	//
	// Start some Workers. 
	//
	m_WorkerThreadMapLock.Lock();
	while (iNumberToStart>0) 
	{
		CWinThread* pWorkerThread=AfxBeginThread(IOCPS::WorkerThreadProc, (void*)this,
			THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);  
		pWorkerThread->m_bAutoDelete=FALSE;  
		if(pWorkerThread)
		{
			pWorkerThread->ResumeThread();
			m_WorkerThreadMap[(WORD)pWorkerThread->m_nThreadID]=(void*)pWorkerThread;
			iNumberToStart--;
		}else
			return FALSE;
	}

	m_WorkerThreadMapLock.Unlock();
	m_bAcceptJobs=bAcceptJobs;
	return TRUE;
}

UINT IOCPS::WorkerThreadProc(LPVOID pParam)
{
	IOCPS* pPoolServer= reinterpret_cast<IOCPS*>(pParam);
	CWinThread* pThis=NULL;
	if(pPoolServer)
		pThis=pPoolServer->GetWorker((WORD)::GetCurrentThreadId());

	if(pThis)
	{


		TRACE("Thread %i is alive.\r\n",::GetCurrentThreadId());
		JobItem *pJob=NULL;
		while(pThis->m_hThread!=INVALID_HANDLE_VALUE)	
		{
			pJob=NULL;	
			pJob=pPoolServer->GetJob();
			if(pJob) 
			{
				pPoolServer->ProcessJob(pJob,pPoolServer);
				pPoolServer->FreeJob(pJob);
			}else
				::SuspendThread(::GetCurrentThread());
		}


	}
	TRACE("Thread %i RIP.\r\n",::GetCurrentThreadId());
	return 0xdead;
}



/*
* Returns a Worker in the Worker Pool..
*
*/


CWinThread* IOCPS::GetWorker(WORD WorkerID)
{
	CWinThread* pWorker=NULL;
	m_WorkerThreadMapLock.Lock();
	pWorker=(CWinThread*)m_WorkerThreadMap[WorkerID];
	m_WorkerThreadMapLock.Unlock();
	return pWorker;
}




/*
* Closes all the logic Workers and emptys the workqueue. 
*
*
*/


void IOCPS::ShutDownWorkers()
{
	//Close The Workers. 
	m_bAcceptJobs=FALSE;
	SetWorkers(0);
	m_WorkerThreadMapLock.Lock();
	m_WorkerThreadMap.RemoveAll();
	m_WorkerThreadMapLock.Unlock();

	// Empty the JobQueue. 

	JobItem *pJob=NULL;
	m_JobQueueLock.Lock();
	POSITION pos = m_JobQueueList.GetHeadPosition ();
	while (pos != NULL) 
	{
		pJob = (JobItem *)m_JobQueueList.GetNext (pos);
		FreeJob(pJob);
	}
	m_JobQueueList.RemoveAll();
	m_JobQueueLock.Unlock();

}

inline void IOCPS::FreeJob(JobItem *pJob)
{
	if(pJob)
		delete pJob;
}


/*
* Adds a job to the jobqueue and wakes someone upp to do the job. 
*
*
*
*/

BOOL IOCPS::AddJob(JobItem *pJob)
{
	BOOL bRetur=FALSE;
	if(m_bAcceptJobs&&pJob!=NULL)
	{
		m_JobQueueLock.Lock();
		bRetur= (m_JobQueueList.AddHead((void*)pJob)!=NULL);
		m_JobQueueLock.Unlock();
		//
		// Wake someone upp to do the job..
		if(bRetur)
		{
			m_WorkerThreadMapLock.Lock();
			POSITION pos = m_WorkerThreadMap.GetStartPosition ();
			while (pos != NULL) 
			{
				WORD strKey;
				CWinThread* pThread=NULL;
				m_WorkerThreadMap.GetNextAssoc (pos, strKey,(void *&)pThread);
				if(pThread)
				{
					if(pThread->ResumeThread()==1) // Some one wake up. 
						break;
				}	
			}
			m_WorkerThreadMapLock.Unlock();

		}
		return bRetur; 
	}
	return FALSE;
}


/*
* Gets a Job from the queue. 
*
*/ 

JobItem* IOCPS::GetJob()
{
	JobItem* pJob=NULL;
	m_JobQueueLock.Lock();
	if(!m_JobQueueList.IsEmpty())
		pJob=(JobItem*)m_JobQueueList.RemoveTail();
	m_JobQueueLock.Unlock();
	return pJob; 
}


/*
* Virtual Function who Processes a Job. Used to do rare heavy computation or 
* calls that blocks the calling thread for a while. 
*/
void IOCPS::ProcessJob(JobItem *pJob,IOCPS* pServer)
{
}
/*
*	Called when a write is completed, this function is ofen used
*  for progressbars etc (e.g indicates how much is send in bytes) 
*/

void IOCPS::NotifyWriteCompleted(ClientContext *pContext, DWORD dwIoSize, CIOCPBuffer *pOverlapBuff)
{
	// The pOverlapBuff Buffer are Successfully sended. 
}

/*
*	An package is received.. 
*/

void IOCPS::NotifyReceivedPackage(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext)
{

}



/*
* AllocateContext. Creates a context in the heap with new or reuse context 
* which is in the m_FreeContextList linked list. 
*
*/

ClientContext* IOCPS::AllocateContext()
{

	ClientContext* pContext = NULL;

	if ( !m_bShutDown )
	{
		m_FreeContextListLock.Lock();
		BOOL bGetFromBuff=m_FreeContextList.IsEmpty();

		if ( bGetFromBuff )
		{
			pContext=new ClientContext();
		}else
		{
			pContext=(ClientContext *)m_FreeContextList.RemoveHead();
		}

		m_FreeContextListLock.Unlock();
	}

	pContext->m_ContextLock.Lock();
	pContext->m_ID=0;
	pContext->m_Socket=INVALID_SOCKET;
	pContext->m_nNumberOfPendlingIO=0;
	pContext->m_SendSequenceNumber=pContext->m_ReadSequenceNumber=0;
	pContext->m_CurrentSendSequenceNumber=pContext->m_CurrentReadSequenceNumber=0;
	pContext->m_pBuffOverlappedPackage=NULL;

	if ( !pContext->m_SendBufferMap.IsEmpty() )
		pContext->m_SendBufferMap.RemoveAll();

	if (!pContext->m_ReadBufferMap.IsEmpty() )
		pContext->m_ReadBufferMap.RemoveAll();

#ifdef TRANSFERFILEFUNCTIONALITY	
	pContext->m_bFileSendMode=FALSE;
	pContext->m_bFileReceivedMode=FALSE;
	pContext->m_iMaxFileBytes=-1;
	pContext->m_iFileBytes=-1;

	if (pContext->m_File.m_hFile != (unsigned int)INVALID_HANDLE_VALUE)
		pContext->m_File.Close();
#endif	

	NotifyNewClientContext(pContext);
	pContext->m_ContextLock.Unlock();

	return pContext;
}




/*
* Allocates an unique buffer for nType operation.(from m_FreeBufferList if possible) 
* The allocated buffer is placed in the m_BufferList. 
*
*/

CIOCPBuffer *IOCPS::AllocateBuffer(int nType)
{
	CIOCPBuffer *pBuff=NULL;
	//
	// Try to Get a buffer from the freebuffer list.  
	//

	m_FreeBufferListLock.Lock();
	int dummy=m_FreeBufferList.GetCount();
	if(!m_FreeBufferList.IsEmpty())
	{
		pBuff=(CIOCPBuffer *)m_FreeBufferList.RemoveHead();
	}
	m_FreeBufferListLock.Unlock();

	// We have to create a new buffer. 
	if(pBuff==NULL)
	{
		pBuff= new CIOCPBuffer();
		if( !pBuff )
		{ 

			CString msg;
			msg.Format("Error new CIOCPBuffer(); failed in AllocateBuffer %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			return NULL;	
		}	
	}

	if(pBuff!=NULL) 
	{
		pBuff->EmptyUsed();
		pBuff->SetOperation(nType);
		pBuff->SetSequenceNumber(0);
		// Add the buffer to the buffer list. 
		POSITION pos=NULL;
		m_BufferListLock.Lock();
		pos=m_BufferList.AddHead((void*)pBuff);
		if( pos !=NULL )
			pBuff->SetPosition(pos);
		else
		{	
			CString msg;
			msg.Format(" Error m_BufferList.AddHead((void*)pBuff) failed in AllocateBuffer: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			delete pBuff;
			m_BufferListLock.Unlock();
			return NULL;
		}
		m_BufferListLock.Unlock();
		return pBuff;
	}

	return NULL; 
}


/*
* ReleaseBuffer releases the buffer (put it into freebufferlist or just delete it). 
*
*/


BOOL IOCPS::ReleaseBuffer(CIOCPBuffer *pBuff)
{
	if(pBuff==NULL)
		return FALSE;
	// First Remove it from the BufferList. 
	m_BufferListLock.Lock();
	POSITION pos=pBuff->GetPosition();
	//TRACE("Buffer %i is going to be released.\n",pBuff);
	if(pos==NULL)
	{

		CString msg;
		msg.Format("FATAL ERROR pBuff->GetPosition(); returned NULL in ReleaseBuffer: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		m_BufferListLock.Unlock();
		return FALSE;
	}

	m_BufferList.RemoveAt(pos);
	//TRACE("Buffer %i is released.\n",pBuff);
	m_BufferListLock.Unlock();

	//
	// Add it to the FreeBufferList or delete it. 
	//
	m_FreeBufferListLock.Lock();
	if(m_iMaxNumberOfFreeBuffer==0||m_FreeBufferList.GetCount()<m_iMaxNumberOfFreeBuffer)
	{
		pos=m_FreeBufferList.AddHead((void*)pBuff);
		pBuff->SetPosition(NULL);
	}else
	{
		// Delete the buffer. 
		if ( pBuff!=NULL )
			delete pBuff;
	}
	m_FreeBufferListLock.Unlock();
	pBuff=NULL;
	return TRUE;
}






/* 
* Releases the Client Context. (put it into freeClientContext or delete it)
*
*/

inline BOOL IOCPS::ReleaseClientContext(ClientContext *pContext)
{
	BOOL bRet=FALSE;	
	if(pContext!=NULL)
	{

		// 
		// We are removing this pContext from the penling IO port. 
		// 
		int nNumberOfPendlingIO=ExitIOLoop(pContext);

		// We Should not get an EnterIOLoopHere Because the client are disconnected. 

#ifdef _DEBUG		
		if(nNumberOfPendlingIO<0)
		{
			TRACE("FATAL ERROR AccessViolation possible\r\n");
			TRACE("Releasing %i(%x) nNumberOfPendlingIO=%i.\r\n",pContext->m_Socket,pContext,nNumberOfPendlingIO);
		}
		ASSERT(nNumberOfPendlingIO>=0);
#endif
		// If no one else is using this pContext and we are the only owner. Delete it. 
		if(nNumberOfPendlingIO==0)
		{
			//
			// Remove it From m_ContextMap. 
			//

			pContext->m_ContextLock.Lock();
			NotifyContextRelease(pContext);
			ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
#ifdef TRANSFERFILEFUNCTIONALITY		
			if (pContext->m_File.m_hFile != (unsigned int)INVALID_HANDLE_VALUE)
			{

				pContext->m_File.Close();
			}
			pContext->m_bFileSendMode=FALSE;
			pContext->m_bFileReceivedMode=FALSE;
			pContext->m_iMaxFileBytes=-1;
#endif

			ReleaseBufferMap(&pContext->m_ReadBufferMap);
			ReleaseBufferMap(&pContext->m_SendBufferMap);
			// Added. 
			pContext->m_CurrentReadSequenceNumber=0;
			pContext->m_ReadSequenceNumber=0;
			pContext->m_SendSequenceNumber=0;
			pContext->m_CurrentSendSequenceNumber=0;
			pContext->m_ContextLock.Unlock();

			// Move the Context to the free context list (if Possible). 
			m_FreeContextListLock.Lock();	
			if(m_FreeContextList.GetCount()<m_iMaxNumberOfFreeContext||m_iMaxNumberOfFreeContext==0)
			{	
				bRet=m_FreeContextList.AddHead((void*)pContext)!=NULL;
				TRACE("Putting (%x) in Freecontext list nNumberOfPendlingIO=%i.\r\n",pContext,nNumberOfPendlingIO);

			}else // Or just delete it. 
			{
				if(pContext)
				{
					TRACE("Context (%x) RIP\r\n",pContext);
					pContext->m_Socket = INVALID_SOCKET;
					delete pContext;
					pContext=NULL;
				}
			}
			m_FreeContextListLock.Unlock();
			return TRUE; 	
		}
	}
	return FALSE; 
}





/*
* Deletes all the buffers.. 
* OBS! this function should not be called if there is any pending operations. 
*
*
*/


void IOCPS::FreeBuffers()
{
	//Free the buffer in the Free buffer list.. 
	CIOCPBuffer *pBuff=NULL;
	m_FreeBufferListLock.Lock();
	POSITION pos = m_FreeBufferList.GetHeadPosition ();
	while (pos != NULL) 
	{
		pBuff = (CIOCPBuffer *)m_FreeBufferList.GetNext (pos);
		if(pBuff)
		{
			delete pBuff;
		}
	}
	m_FreeBufferList.RemoveAll();
	m_FreeBufferListLock.Unlock();

	// Free the buffers in the Occupied buffer list (if any).  

	pos=NULL;
	m_BufferListLock.Lock();
	pos = m_BufferList.GetHeadPosition ();
	while (pos != NULL) 
	{
		pBuff = (CIOCPBuffer *)m_BufferList.GetNext (pos);
		if(pBuff)
		{

			//CString msg;
			//msg.Format("Removed overlap Buffer (type %i).",pBuff->GetOperation());
			//AppendLog(msg);

			delete pBuff;
		}
	}
	m_BufferList.RemoveAll();
	m_BufferListLock.Unlock();

}

/*
* Move to CIOBUFFER ? 
*/
CIOCPBuffer * IOCPS::SplitBuffer(CIOCPBuffer *pBuff, UINT nSize)
{
	CIOCPBuffer *pBuff2=NULL;
	pBuff2=AllocateBuffer(0);
	if(pBuff2==NULL)
		return NULL;
	pBuff2->SetSequenceNumber(pBuff->GetSequenceNumber());


	if(!pBuff2->AddData(pBuff->GetBuffer(),nSize))
	{
		delete pBuff2;
		return NULL;
	}

	if(!pBuff->Flush(nSize))
	{
		delete pBuff2;
		return NULL;
	}

	return pBuff2;
}


/*
* Adds the nSize bytes from pFromBuff to pToBuff, and 
* removes the data from pFromBuff.  
*
*/


BOOL IOCPS::AddAndFlush(CIOCPBuffer *pFromBuff, CIOCPBuffer *pToBuff, UINT nSize)
{
	if(pFromBuff==NULL||pToBuff==NULL||nSize<=0)
		return FALSE;

	if(!pToBuff->AddData(pFromBuff->GetBuffer(),nSize))
	{
		return FALSE;
	}

	if(!pFromBuff->Flush(nSize))
	{
		return FALSE;
	}
	return TRUE;
}

/*
* Setups the listner..  
*
*/
BOOL IOCPS::SetupListner()
{

	m_socListen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);	
	if ( m_socListen == INVALID_SOCKET )
	{

		CString msg;
		msg.Format("Could not create listen socket: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		return FALSE;
	}



	// Event for handling Network IO
	m_hEvent = WSACreateEvent();
	if ( m_hEvent == WSA_INVALID_EVENT )
	{	
		CString msg;
		msg.Format("WSACreateEvent() error : %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket(m_socListen);
		return FALSE;
	}


	// The listener is ONLY interested in FD_ACCEPT
	// That is when a client connects to or IP/Port
	// Request async notification
	int nRet = WSAEventSelect(m_socListen,
		m_hEvent,
		FD_ACCEPT);

	if ( nRet == SOCKET_ERROR )
	{

		CString msg;
		msg.Format("WSAAsyncSelect() error: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket(m_socListen);
		return FALSE;
	}


	SOCKADDR_IN		saServer;		


	// Listen on our designated Port#
	saServer.sin_port = htons(m_nPortNumber);

	// Fill in the rest of the address structure
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;

	// bind our name to the socket
	nRet = bind(m_socListen, 
		(LPSOCKADDR)&saServer, 
		sizeof(struct sockaddr));

	if ( nRet == SOCKET_ERROR )
	{

		CString msg;
		msg.Format("bind() error : %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket(m_socListen);
		return FALSE;
	}

	// Set the socket to listen
	//nRet = listen(m_socListen, nConnections);
	nRet=listen(m_socListen, 5);
	if ( nRet == SOCKET_ERROR )
	{

		CString msg;
		msg.Format("listen() error: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket(m_socListen);
		return FALSE;
	}

	m_bAcceptConnections=TRUE;
	m_pListenThread =
		AfxBeginThread(IOCPS::ListnerThreadProc, (void*)this,
		THREAD_PRIORITY_NORMAL);

	if ( !m_pListenThread )
	{

		CString msg;
		msg.Format("Error Could not start the ListnerThreadProc: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		return FALSE;
	}
	return TRUE; 
}




/*
* Creates the  Completion Port m_hCompletionPort used by 
* IO worker Threads. 
*/
BOOL IOCPS::CreateCompletionPort()
{
	SOCKET s;	

	//
	// First open a temporary socket that we will use to create the
	// completion port.  In NT 3.51 it will not be necessary to specify
	// the FileHandle parameter of CreateIoCompletionPort()--it will
	// be legal to specify FileHandle as NULL.  However, for NT 3.5
	// we need an overlapped file handle.
	//

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if ( s == INVALID_SOCKET ) 
	{	
		CString msg;
		msg.Format("Error Could not start Create Socket in CreateCompletionPort: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		return FALSE;
	}


	// Create the completion port that will be used by all the workers
	// threads.
	m_hCompletionPort = CreateIoCompletionPort( (HANDLE)s, NULL, 0, 0 );
	if ( m_hCompletionPort == NULL ) 
	{	
		CString msg;
		msg.Format("CreateIoCompletionPort Failed: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket( s );
		return FALSE;
	}

	closesocket( s );
	return TRUE;
}


/*
* Starts the IOWorkers. 
*
*/

BOOL IOCPS::SetupIOWorkers()
{
	CWinThread* pWorkerThread=NULL;
	for(int i=0; i<m_iMaxIOWorkers;i++)
	{
		pWorkerThread=AfxBeginThread(IOCPS::IOWorkerThreadProc, (void*)this,
			THREAD_PRIORITY_NORMAL);
		if(pWorkerThread)
			m_IOWorkerList.AddHead((void*)pWorkerThread);
		else
		{

			CString msg;
			msg.Format("Error Couldnot start worker: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);

			return FALSE;
		}
	}
	m_nIOWorkers=m_IOWorkerList.GetCount();
	return TRUE; 
}




/*
* Returns the local IP Adress.. 
*/


CString IOCPS::GetHostIP()
{
	CString sRet="";
	hostent* thisHost;
	char* ip;
	thisHost = gethostbyname("");
	ip = inet_ntoa (*(struct in_addr *)*thisHost->h_addr_list);
	sRet=ip;
	return ip; 
}

/*
* Return The number of Connections. 
*/
int IOCPS::GetNumberOfConnections()
{
	int iRet=0;
	m_ContextMapLock.Lock();
	iRet=m_NumberOfActiveConnections;
	m_ContextMapLock.Unlock();
	return iRet;
}

/*
* Connects to a IP Adress. 
*
*/
BOOL IOCPS::Connect(const CString &strIPAddr, int nPort)
{

	if (m_bShutDown)
		return FALSE; 

	SOCKADDR_IN	SockAddr;
	SOCKET		clientSocket=INVALID_SOCKET;
	int			nRet=-1;
	int			nLen=-1;

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET)
	{

		CString msg;
		msg.Format("Connect()->socket() Could not create  socket: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		return FALSE;
	}
	// Clear the SockAddr. 
	memset(&SockAddr,0,sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = inet_addr(strIPAddr);
	SockAddr.sin_port = htons(nPort);
	nRet = connect(clientSocket,(sockaddr*)&SockAddr, sizeof(SockAddr));

	if (nRet == SOCKET_ERROR &&
		WSAGetLastError() != WSAEWOULDBLOCK)
	{
		CString msg;
		msg.Format("Connection Error: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		closesocket(clientSocket);
		return FALSE;
	}else
		return AssociateIncomingClientWithContext(clientSocket);
}


/*
* Used to avoid inorder packaging. 
* Returns The inorder Buffer or NULL if not processed. 
*
*/
CIOCPBuffer* IOCPS::GetNextSendBuffer(ClientContext *pContext,CIOCPBuffer *pBuff)
{
	// We must have a ClientContext to begin with. 
	if (pContext==NULL)
		return NULL;

	pContext->m_ContextLock.Lock();

	CIOCPBuffer* pRetBuff=NULL;
	// We have a buffer
	if (pBuff!=NULL)
	{
		// Is the Buffer inorder ? 
		unsigned int iBufferSequenceNumber=pBuff->GetSequenceNumber();
		if (iBufferSequenceNumber==pContext->m_CurrentSendSequenceNumber)
		{
			//TRACE("GetNextSendBuffer()_1: m_SendSequenceNumber= %i, m_CurrentSendSequenceNumber=%i\r\n",pContext->m_SendSequenceNumber,pContext->m_CurrentSendSequenceNumber); 

			// Unlock the Context Lock. 
			pContext->m_ContextLock.Unlock();
			// return the Buffer to be processed. 
			return pBuff;
		}
		TRACE("OutOforder: SS: %i, CurrentS: %i, pkg: %i\r\n",pContext->m_SendSequenceNumber,pContext->m_CurrentSendSequenceNumber,iBufferSequenceNumber); 
		//
		// Check if we already have a such key. 
		//
		pRetBuff=NULL;
		pRetBuff=(CIOCPBuffer*) pContext->m_SendBufferMap[iBufferSequenceNumber];
		if(pRetBuff!=NULL)
		{
			CString msg;
			msg.Format("Dublicate Key! in SendbufferMap");
			AppendLog(msg);
			pContext->m_ContextLock.Unlock();
			return NULL;
		}

		//
		// Add it to the Map. 
		//

		// What if this fail?
		pContext->m_SendBufferMap[iBufferSequenceNumber]=pBuff;
	}

	// return the Ordered Context. 
	pRetBuff=NULL;
	pRetBuff=pContext->m_SendBufferMap[pContext->m_CurrentSendSequenceNumber];
	if(pRetBuff!=NULL)
	{
		pContext->m_SendBufferMap.RemoveKey(pContext->m_CurrentSendSequenceNumber);
		TRACE("GetNextSendBuffer()_2: m_SendSequenceNumber= %i, m_CurrentSendSequenceNumber=%i\r\n",pContext->m_SendSequenceNumber,pContext->m_CurrentSendSequenceNumber); 
	}

	pContext->m_ContextLock.Unlock();
	return pRetBuff;
}

// Sets the Send Sequence number to the Buffer.  

void IOCPS::SetSendSequenceNumber(ClientContext *pContext,CIOCPBuffer *pBuff)
{
	if (pContext!=NULL&&pBuff!=NULL)
	{
		pContext->m_ContextLock.Lock();
		pBuff->SetSequenceNumber(pContext->m_SendSequenceNumber);
		pContext->m_SendSequenceNumber=(pContext->m_SendSequenceNumber+1)%MAXIMUMSEQUENSENUMBER;
		//TRACE("SetSendSequenceNumber(): m_SendSequenceNumber= %i, m_CurrentSendSequenceNumber=%i\r\n",pContext->m_SendSequenceNumber,pContext->m_CurrentSendSequenceNumber); 
		pContext->m_ContextLock.Unlock();
	}
}

/*
* Used to avoid in order packaging. 
* Returns The in order Buffer or NULL if not processed. 
* Same as GetReadBuffer
*/

CIOCPBuffer * IOCPS::GetNextReadBuffer(ClientContext *pContext, CIOCPBuffer *pBuff)
{
	// We must have a ClientContext to begin with. 
	if (pContext==NULL)
		return NULL;
	pContext->m_ContextLock.Lock();
	CIOCPBuffer* pRetBuff=NULL;
	// We have a buffer
	if (pBuff!=NULL)
	{

		// Is the Buffer inorder ? 
		unsigned int iBufferSequenceNumber=pBuff->GetSequenceNumber();
		if (iBufferSequenceNumber==pContext->m_CurrentReadSequenceNumber)
		{

			//TRACE("GetNextReadBuffer()_1: m_ReadSequenceNumber= %i, m_CurrentReadSequenceNumber=%i\r\n",pContext->m_ReadSequenceNumber,pContext->m_CurrentReadSequenceNumber); 

			// Unlock the Context Lock. 
			pContext->m_ContextLock.Unlock();
			// return the Buffer to be processed. 
			return pBuff;
		}
		TRACE("OutOforderRead: SS: %i, CurrentS: %i, pkg: %i\r\n",pContext->m_ReadSequenceNumber,pContext->m_CurrentReadSequenceNumber,iBufferSequenceNumber); 
		//
		// Check if we already have a such key. 
		//
		pRetBuff=NULL;
		//Changed 081220 
		pContext->m_ReadBufferMap.Lookup(iBufferSequenceNumber,pRetBuff);
		//pRetBuff=pContext->m_ReadBufferMap[iBufferSequenceNumber];
		// end of change 
		if(pRetBuff!=NULL)
		{
			CString msg;
			msg.Format("Dublicate Key! in ReadbufferMap");
			AppendLog(msg);
			pContext->m_ContextLock.Unlock();
			return NULL;
		}

		//
		// Add it to the Map. 
		//

		// What if this fail?
		pContext->m_ReadBufferMap[iBufferSequenceNumber]=pBuff;
		pRetBuff=NULL;
		//Changed 081220 
		pContext->m_ReadBufferMap.Lookup(iBufferSequenceNumber,pRetBuff);
		//pRetBuff=pContext->m_ReadBufferMap[iBufferSequenceNumber];
		// end of change 
		if(pRetBuff==NULL)
		{
			CString msg;
			msg.Format("ERROR CAN NOT SAVE INTO BUFFER!!!");
			AppendLog(msg);
			pContext->m_ContextLock.Unlock();
			return NULL;
		}
	}

	// return the Ordered Buffer. 
	pRetBuff=NULL;
	pRetBuff=pContext->m_ReadBufferMap[pContext->m_CurrentReadSequenceNumber];
	if(pRetBuff!=NULL)
	{
		if(!pContext->m_ReadBufferMap.RemoveKey(pContext->m_CurrentReadSequenceNumber))
			TRACE("FATAL ERROR pContext->m_ReadBufferMap.RemoveKey(pContext->m_CurrentReadSequenceNumber) FAILED\r\n");
		// increase or reset the sequence number 
		//if(pContext->m_CurrentReadSequenceNumber==pContext->m_ReadSequenceNumber-1)
		//	pContext->m_CurrentReadSequenceNumber=pContext->m_ReadSequenceNumber=0;
		//else
		//	pContext->m_CurrentReadSequenceNumber++; // Increase
		TRACE("GetNextReadBuffer()_2: m_ReadSequenceNumber= %i, m_CurrentReadSequenceNumber=%i\r\n",pContext->m_ReadSequenceNumber,pContext->m_CurrentReadSequenceNumber); 
	}

	pContext->m_ContextLock.Unlock();
	return pRetBuff;
}

/*
* Sets the Sequence number to a Buffer and adds the sequence buffer. 
*/
void IOCPS::MakeOrderdRead(ClientContext *pContext, CIOCPBuffer *pBuff)
{
	if (pContext!=NULL&&pBuff!=NULL)
	{
		//pContext->m_ContextLock.Lock();

		pBuff->SetSequenceNumber(pContext->m_ReadSequenceNumber);
		//TRACE("MakeOrderdRead> %i\r\n",pBuff->GetSequenceNumber());
		DWORD dwIoSize=0;
		ULONG ulFlags = MSG_PARTIAL;
		UINT nRetVal = WSARecv(pContext->m_Socket, 
			pBuff->GetWSABuffer(),
			1,
			&dwIoSize, 
			&ulFlags,
			&pBuff->m_ol, 
			NULL);

		if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
		{

			if(WSAGetLastError()!=WSAENOTSOCK)
			{
				CString msg;
				msg.Format("Disconnect in Onread Possible Socket Error: %s",ErrorCode2Text(WSAGetLastError()));
				AppendLog(msg);
			}
			//pContext->m_ContextLock.Unlock();
			ReleaseBuffer(pBuff);
			TRACE(">MakeOrderdRead(%x)\r\n",pContext);
			DisconnectClient(pContext);
			ReleaseClientContext(pContext);
		}else
		{
			pContext->m_ReadSequenceNumber=(pContext->m_ReadSequenceNumber+1)%MAXIMUMSEQUENSENUMBER;
			//pContext->m_ContextLock.Unlock();
		}
	}
}

/*
* Perpares for Sendfile Transfer. 
*
* Blocks all other kind of sends. 
*/
#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::PrepareSendFile(SOCKET clientSocket, CString Filename)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext=NULL;
	pContext = FindClient(clientSocket);
	if(pContext!=NULL)
		bRet=PrepareSendFile(pContext, (LPCTSTR)Filename);
	m_ContextMapLock.Unlock();
	return bRet;
}
#endif

/*
* Perpares the for Filetransfer. 
*
* No other type of sends must be made when transfering files.   
*
* 1) The Function opens the specefied file.  
* 2) Sends a package (se below) that contains information about the file to the Client. 
* Se below. [sizeheader 4b|type of package 1b|Size of file 4b|.. filename..]. 
* 3) The actual transfer begins when the client sends a "start transfer package". 
*
*/
#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::PrepareSendFile(ClientContext *pContext, LPCTSTR lpszFilename)
{
	if(pContext!=NULL)
	{    // Already in send mode
		if(pContext->m_bFileSendMode)
			return FALSE;

		//
		// Open the file for write.. 
		//

		pContext->m_ContextLock.Lock();
		pContext->m_bFileSendMode=TRUE;
		// close file if it's already open
		if (pContext->m_File.m_hFile != (int)INVALID_HANDLE_VALUE)
		{
			pContext->m_File.Close();
		}

		// open source file
		//if (!pContext->m_File.Open(lpszFilename, CFile::modeRead | CFile::typeBinary | CFile::osSequentialScan))
		if (!pContext->m_File.Open(lpszFilename, CFile::modeRead | CFile::typeBinary ))
		{
			pContext->m_ContextLock.Unlock();
			return FALSE;
		}

		pContext->m_iMaxFileBytes=(unsigned int)pContext->m_File.GetLength();
		pContext->m_iFileBytes=0;
		pContext->m_ContextLock.Unlock();

		//
		// Send Filepakage info. 
		//

		CString sFileName="";
		UINT iFileSize=0;

		sFileName=pContext->m_File.GetFileName();
		iFileSize=pContext->m_iMaxFileBytes;
		CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
		if(pOverlapBuff)
		{
			if(pOverlapBuff->CreatePackage(1,iFileSize,sFileName))
			{

				//
				// If we are sending in order
				//
				if(m_bSendInOrder)
					SetSendSequenceNumber(pContext,pOverlapBuff); 

				//
				// Important!! Notifies Pending the socket and the structure  
				// pContext have an Pending IO operation ant should not be deleted.
				// This is necessary to avoid Access violation. 
				//
				EnterIOLoop(pContext); 
				BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, pOverlapBuff->GetUsed(), (DWORD) pContext, &pOverlapBuff->m_ol);
				if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
				{            
					ReleaseBuffer(pOverlapBuff);
					TRACE(">PrepareSendFile(%x)",pContext);
					ReleaseClientContext(pContext); // Not disconnect because we did EnterIOLoop
					return FALSE;
				}
				return TRUE;

			}else
			{
				AppendLog("Error CreatePackage(1,iFileSize,sFileName) FAILED..");
				ReleaseBuffer(pOverlapBuff);
				return FALSE;
			}
		}else
		{
			CString msg;
			msg.Format("Could not allocate memory in PrepareSendFile: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			DisconnectClient(pContext);
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}
#endif

#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::DisableSendFile(SOCKET clientSocket)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = NULL;
	pContext=FindClient(clientSocket);
	if(pContext!=NULL)
		bRet=DisableSendFile(pContext);
	m_ContextMapLock.Unlock();
	return bRet;
}
#endif


#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::DisableSendFile(ClientContext *pContext)
{
	pContext->m_ContextLock.Lock();
	// close file if it's already open
	//if (pContext->m_File.m_hFile != INVALID_HANDLE_VALUE)
	if (pContext->m_File.m_hFile != (int)INVALID_HANDLE_VALUE)
	{
		pContext->m_File.Close();
	}
	pContext->m_iMaxFileBytes=0;
	pContext->m_iFileBytes=0;
	pContext->m_bFileSendMode=FALSE;
	pContext->m_ContextLock.Unlock();
	return TRUE;
}
#endif

#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::DisableReceiveFile(ClientContext *pContext)
{
	pContext->m_ContextLock.Lock();
	// close file if it's already open
	//if (pContext->m_File.m_hFile != INVALID_HANDLE_VALUE)
	if (pContext->m_File.m_hFile != (int)INVALID_HANDLE_VALUE)
	{
		pContext->m_File.Close();
	}
	pContext->m_iMaxFileBytes=0;
	pContext->m_iFileBytes=0;
	pContext->m_bFileReceivedMode=FALSE;
	pContext->m_ContextLock.Unlock();
	return TRUE;
}

BOOL IOCPS::DisableReceiveFile(SOCKET clientSocket)
{

	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = NULL;
	pContext=FindClient(clientSocket);
	if(pContext!=NULL)
		bRet=DisableReceiveFile(pContext);
	m_ContextMapLock.Unlock();
	return bRet;
}

#endif
/*
* Start to save the incoming data to a file instead of processing it in package process. 
*/
#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::PrepareReceiveFile(ClientContext *pContext, LPCTSTR lpszFilename,DWORD dwFileSize)
{
	if(pContext!=NULL)
	{

		pContext->m_ContextLock.Lock();
		// close file if it's already open
		//if (pContext->m_File.m_hFile != INVALID_HANDLE_VALUE)
		if (pContext->m_File.m_hFile != (int)INVALID_HANDLE_VALUE)
		{
			pContext->m_File.Close();
		}

		// open source file
		//if (!pContext->m_File.Open(lpszFilename, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyWrite| CFile::osSequentialScan |CFile::typeBinary))
		if (!pContext->m_File.Open(lpszFilename, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyWrite |CFile::typeBinary))
		{
			pContext->m_iFileBytes=0;
			pContext->m_iMaxFileBytes=0;
			pContext->m_bFileReceivedMode=FALSE;
			pContext->m_ContextLock.Unlock();
			return FALSE;
		}

		pContext->m_iMaxFileBytes=dwFileSize;
		pContext->m_iFileBytes=0;
		pContext->m_bFileReceivedMode=TRUE;
		pContext->m_ContextLock.Unlock();

		return TRUE;
	}
	return FALSE;
}

BOOL IOCPS::PrepareReceiveFile(SOCKET clientSocket, LPCTSTR lpszFilename,DWORD dwFileSize)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = NULL;
	pContext=FindClient(clientSocket);
	if(pContext!=NULL)
		bRet=PrepareReceiveFile(pContext,lpszFilename,dwFileSize);
	m_ContextMapLock.Unlock();
	return bRet;
}

#endif
/*
* AddToFile adds the received bytes to the file. 
*/
#if defined TRANSFERFILEFUNCTIONALITY
void IOCPS::AddToFile(ClientContext *pContext, DWORD dwIoSize, CIOCPBuffer *pOverlapBuff)
{
	if (pContext->m_File.m_hFile != NULL)
	{
		pContext->m_ContextLock.Lock();
		int iBytesLeft=(int)pContext->m_iMaxFileBytes-pContext->m_iFileBytes;
		// We have two cases.

		// The buffer contains only data to be written to the buffer. 
		if(iBytesLeft>=dwIoSize)
		{
			pContext->m_File.Write(pOverlapBuff->GetBuffer(), dwIoSize );
			pContext->m_iFileBytes+=dwIoSize;
			// We are finished. 
			if(pContext->m_iFileBytes==pContext->m_iMaxFileBytes)
			{
				NotifyFileCompleted(pContext);  
				pContext->m_File.Close();
				pContext->m_bFileReceivedMode=FALSE;
			}
			ReleaseBuffer(pOverlapBuff);
		}else
		{
			/* 
			We have overlapped filedata and package data
			[..filedata|Pkg..pkg]
			*/
			CIOCPBuffer *pBuffFileRemain=AllocateBuffer(0);
			if(pBuffFileRemain!=NULL)
			{

				//pOverlapBuff->DUMP();
				// Add the rest to the buffer. 
				AddAndFlush(pOverlapBuff,pBuffFileRemain,iBytesLeft);
				TRACE("BUffer after pBuffFileRemain>\r\n");
				//pOverlapBuff->DUMP();
				// Write it.
				pContext->m_File.Write(pBuffFileRemain->GetBuffer(), iBytesLeft );
				pContext->m_iFileBytes+=iBytesLeft;
				ReleaseBuffer(pBuffFileRemain);
				// We are finished. 
				if(pContext->m_iFileBytes==pContext->m_iMaxFileBytes)
				{
					NotifyFileCompleted(pContext);  
					pContext->m_File.Close();
					pContext->m_bFileReceivedMode=FALSE;
				}
				// Let the remain to be processed. 
				ProcessPackage(pContext,dwIoSize-iBytesLeft,pOverlapBuff);
			}else
			{
				pContext->m_ContextLock.Unlock();
				AppendLog("Error could not allocate buffer");
				ReleaseBuffer(pOverlapBuff);
				DisconnectClient(pContext);
				return; 
			}
		}
		pContext->m_ContextLock.Unlock();
	}
}
#endif 



/*
* Increase the Read Sequence Number. 
*
*/

void IOCPS::IncreaseReadSequenceNumber(ClientContext *pContext)
{
	if (pContext!=NULL)
	{
		pContext->m_ContextLock.Lock();
		// increase or reset the sequence number 
		pContext->m_CurrentReadSequenceNumber=(pContext->m_CurrentReadSequenceNumber+1)%MAXIMUMSEQUENSENUMBER;
		pContext->m_ContextLock.Unlock();
	}
}


void IOCPS::IncreaseSendSequenceNumber(ClientContext *pContext)
{
	if (pContext!=NULL)
	{
		pContext->m_ContextLock.Lock();
		// increase or reset the sequence number 
		pContext->m_CurrentSendSequenceNumber=(pContext->m_CurrentSendSequenceNumber+1)%MAXIMUMSEQUENSENUMBER;
		pContext->m_ContextLock.Unlock();
	}
}


void IOCPS::NotifyDisconnectedClient(ClientContext *pContext)
{

}

void IOCPS::NotifyNewConnection(ClientContext *pcontext)
{

}

void IOCPS::NotifyNewClientContext(ClientContext *pContext)
{
	// Add some init here 	
}

void IOCPS::NotifyContextRelease(ClientContext *pContext)
{
	// add some extra clean up here. 
}

void IOCPS::AppendLog(CString msg)
{
}



BOOL IOCPS::IsStarted()
{
	return m_bServerStarted;
}



void IOCPS::NotifyFileCompleted(ClientContext *pcontext)
{
	// pcontext is locked here. 
#ifdef TRANSFERFILEFUNCTIONALITY
	TRACE("FILE FINISHED"); 
	TRACE("%s> %d of %d.\r\n",pcontext->m_File.GetFileTitle(),pcontext->m_iFileBytes,pcontext->m_iMaxFileBytes);
#endif
}



#if defined TRANSFERFILEFUNCTIONALITY
BOOL IOCPS::StartSendFile(ClientContext *pContext)
{
	if(pContext!=NULL&&pContext->m_Socket!=INVALID_SOCKET)
	{	
		pContext->m_ContextLock.Lock();
		pContext->m_bFileSendMode=TRUE;
		pContext->m_ContextLock.Unlock();
		CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
		if(pOverlapBuff!=NULL)
		{
			EnterIOLoop(pContext);
			pOverlapBuff->SetOperation(IOTransmitFileCompleted);
			TRACE("Making a Asyncroun TransmitFile in the Kernel.\r\n");
			int nRetVal = TransmitFile(pContext->m_Socket,
				(HANDLE)pContext->m_File.m_hFile,
				(DWORD)pContext->m_iMaxFileBytes,
				0,
				&pOverlapBuff->m_ol,
				NULL,
				0);
			//TP_USE_KERNEL_APC);

			if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING ) 
			{

				if(WSAGetLastError()!=WSAENOTSOCK)
				{
					CString msg;
					msg.Format("Error in On TransmitFile..: %s",ErrorCode2Text(WSAGetLastError()));
					AppendLog(msg);
				}
				ReleaseBuffer(pOverlapBuff);
				//DisconnectClient(pContext);
				TRACE(">StartSendFile(%x)\r\n",pContext);
				ReleaseClientContext(pContext); //Later Implementation 

			}
			TRACE("Pendling Transmit is Successfull..\r\n");
			return TRUE;
		}else
		{
			CString msg;
			msg.Format("Could not allocate memory ASend: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			TRACE(">StartSendFile2(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			return FALSE;
		}

	}
	return FALSE;
}

BOOL IOCPS::StartSendFile(SOCKET clientSocket)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = NULL;
	pContext=FindClient(clientSocket);
	if(pContext!=NULL)
		bRet=StartSendFile(pContext);
	m_ContextMapLock.Unlock();
	return bRet;

}

#endif






/*
* Disconnect the accepted socket immediately, if an aktive connection     
* already exist with the same IP. 
*
*/ 
#if defined SIMPLESECURITY	

/*
* 	IsAlreadyConnected(sockaddr_in* pCaller)
*
*  Returns TRUE if we already have a connection with the specified 
*	address. Add the CLient to the list othervise.  
*  
*	This function is used with ConnectAcceptCondition and
*  #DEFINE SIMPLESECURITY to block multiple connections from the
*  same IP.  
*/

inline BOOL IOCPS::IsAlreadyConnected(sockaddr_in* pCaller)
{
	// We don't use ordinary covert IP to string and string compare 
	// FIXME: Whats happens when we hav 64bit processor

	// Load the value of IP (32bit) inside the 
	// a void pointer of size 32. 

	if ( !m_bOneIPPerConnection )
		return FALSE;

	void* pVoid=(void*)pCaller->sin_addr.S_un.S_addr; 
	m_OneIPPerConnectionLock.Lock();
	POSITION pos=m_OneIPPerConnectionList.Find(pVoid);

	// If it is in the list return TRUE else add it to the list.. 
	if ( pos!=NULL )
	{
		m_OneIPPerConnectionLock.Unlock();
		return TRUE;
	}else
	{
		m_OneIPPerConnectionList.AddHead(pVoid);

	}
	m_OneIPPerConnectionLock.Unlock();
	return FALSE; 
}

/*
* 	IsInBannedList(sockaddr_in* pCaller)
*
*  Returns TRUE if the user is inside the bannedIP list adress.
*
*	This function is used with ConnectAcceptCondition and
*  #DEFINE SIMPLESECURITY to block connections that behave badly. 
*  
*  The remote end will not receive any notification and will think 
*  that the system is down. 
*/
BOOL IOCPS::IsInBannedList(sockaddr_in* pCaller)
{

	// We don't use ordinary covert IP to string and string compare 
	// FIXME: Whats happens when we hav 64bit processor

	// Load the value of IP (32bit) inside the 
	// a void pointer of size 32. 
	void* pVoid=(void*)pCaller->sin_addr.S_un.S_addr; 

	m_BanIPLock.Lock();
	if ( !m_BanIPList.IsEmpty() )
	{
		POSITION pos=m_BanIPList.Find(pVoid);
		// The Client is in the banned list refuse
		if ( pos!=NULL )
		{
			m_BanIPLock.Unlock();
			return TRUE;
		}
	}
	m_BanIPLock.Unlock();

	return FALSE; 
}



void IOCPS::AddToBanList(SOCKET &Socket)
{
	/*	CString sIP="";
	//
	//  Get the incoming connection IPadress
	//
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);

	BOOL bResult = getpeername(Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);

	if (bResult != INVALID_SOCKET)
	sIP.Format("%s",inet_ntoa(sockAddr.sin_addr));

	if(sIP=="")
	return;
	m_BanIPLock.Lock();
	if(	Socket != INVALID_SOCKET)
	m_BanIPList.AddHead(sIP);
	m_BanIPLock.Unlock();

	CString msg="";
	msg.Format("%s banned because of bad messagesize.",sIP);
	AppendLog(msg);
	*/
	//
	//  Get the incoming connection IPadress
	//
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	UINT nResult = getpeername(Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
	if ( nResult != INVALID_SOCKET)
	{
		m_BanIPLock.Lock();
		// We save our unsigned Long inside a Void pointer of size 32. 
		void * pData=(void*) sockAddr.sin_addr.S_un.S_addr;
		m_BanIPList.AddHead(pData);
		m_BanIPLock.Unlock();

		CString msg="";
		msg.Format("%s banned because of bad messagesize.",inet_ntoa(sockAddr.sin_addr));
		AppendLog(msg);


	}
}


void IOCPS::ClearBanList()
{
	m_BanIPLock.Lock();
	if(!m_BanIPList.IsEmpty())
	{
		m_BanIPList.RemoveAll();
		CString msg="";
		msg.Format("Banned IP List Cleared.");
		AppendLog(msg);
	}
	m_BanIPLock.Unlock();
}

void IOCPS::OneIPPerConnection(BOOL bVal)
{
	m_bOneIPPerConnection=bVal;
}
#endif

/*
When you are developing serverapplication you may whant to protect your server 
againsd SYN attacks.. 

The SYN flooding attack protection feature of TCP detects symptoms of SYN flooding and responds by reducing the time server spends on connection requests that it cannot acknowledge.

Specifically, TCP shortens the required interval between SYN-ACK (connection request acknowledgements) retransmissions. (TCP retransmits SYN-ACKS when they are not answered.) As a result, the allotted number of retransmissions is consumed quicker and the unacknowledgeable connection request is discarded faster.

The SYN attack protection is obtained by setting some values in the windows registery before you 
start the server. Using this windows XP and Windows NT own protection is easy. 

The registry key "SynAttackProtect" causes Transmission Control Protocol (TCP) to 
adjust retransmission of SYN-ACKS. When you configure this value, the connection 
responses time out more quickly in the event of a SYN attack 
(a type of denial of service attack).

Below you can see the default values. 

0 (default) - typical protection against SYN attacks 
1 - better protection against SYN attacks that uses the advanced values below. 
2 (recommended) - best protection against SYN attacks. 


TcpMaxHalfOpen - default value is "100" 
Determines how many connections the server can maintain in the half-open (SYN-RCVD) state before TCP/IP initiates SYN flooding attack protection.
TcpMaxHalfOpenRetried - default value is "80" 
Determines how many connections the server can maintain in the half-open (SYN-RCVD) state even after a connection request has been retransmitted. If the number of exceeds the value of this entry, TCP/IP initiates SYN flooding attack protection.

TcpMaxPortsExhausted - default value is "5" 
Determines how many connection requests the system can refuse before TCP/IP initiates SYN flooding attack protection. The system must refuse all connection requests when its reserve of open connection ports runs out.

TcpMaxConnectResponseRetransmissions - default value is "3"

Determines how many times TCP retransmits an unanswered SYN-ACK (connection request acknowledgment). TCP retransmits acknowledgments until they are answered or until this value expires. This entry is designed to minimize the effect of denial-of-service attacks (also known as SYN flooding) on the server.


The Function below manipulates these values, restart of the machine is needed to, maintain the effects!
*/

BOOL IOCPS::XPNTSYNFloodProtection(int iValue, int iTcpMaxHalfOpen, int iTcpMaxHalfOpenRetried,int iTcpMaxPortsExhausted,int iTcpMaxConnectResponseRetransmissions)
{
	CString sKey_PATH="\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
	CString sKey_SynAttackProtect="SynAttackProtect";
	CString sKey_TcpMaxHalfOpen="TcpMaxHalfOpen";
	CString sKey_TcpMaxHalfOpenRetried="TcpMaxHalfOpenRetried";
	CString sKey_TcpMaxPortsExhausted="TcpMaxPortsExhausted";
	CString sKey_TcpMaxConnectResponseRetransmissions="TcpMaxConnectResponseRetransmissions";


	HKEY    hKey;
	DWORD   val=0;
	LONG	r=0;
	BOOL bRet=TRUE;

	//
	// Set the sKey_SynAttackProtect
	//
	val=iValue;
	if (RegOpenKey(HKEY_LOCAL_MACHINE, sKey_PATH, &hKey) != ERROR_SUCCESS)
		if (RegCreateKey(HKEY_LOCAL_MACHINE, sKey_SynAttackProtect, &hKey) != ERROR_SUCCESS)
			return FALSE;
	r = RegSetValueEx(hKey, sKey_SynAttackProtect, 0, REG_DWORD, (BYTE *)&val, sizeof(val));
	RegCloseKey(hKey);
	bRet&= (r == ERROR_SUCCESS);

	//
	// Special Parameters is used.
	//
	if(iValue==1)
	{
		//
		// Set the sKey_SynAttackProtect
		//
		val=iTcpMaxHalfOpenRetried;
		if (RegOpenKey(HKEY_LOCAL_MACHINE, sKey_PATH, &hKey) != ERROR_SUCCESS)
			if (RegCreateKey(HKEY_LOCAL_MACHINE, sKey_TcpMaxHalfOpen, &hKey) != ERROR_SUCCESS)
				return FALSE;
		r = RegSetValueEx(hKey, sKey_TcpMaxHalfOpen, 0, REG_DWORD, (BYTE *)&val, sizeof(val));
		RegCloseKey(hKey);
		bRet&= (r == ERROR_SUCCESS);

		//
		// Set the sKey_TcpMaxHalfOpenRetried
		//
		val=iTcpMaxHalfOpenRetried;
		if (RegOpenKey(HKEY_LOCAL_MACHINE, sKey_PATH, &hKey) != ERROR_SUCCESS)
			if (RegCreateKey(HKEY_LOCAL_MACHINE, sKey_TcpMaxHalfOpenRetried, &hKey) != ERROR_SUCCESS)
				return FALSE;
		r = RegSetValueEx(hKey, sKey_TcpMaxHalfOpenRetried, 0, REG_DWORD, (BYTE *)&val, sizeof(val));
		RegCloseKey(hKey);
		bRet&= (r == ERROR_SUCCESS);


		//
		// Set the sKey_TcpMaxPortsExhausted
		//
		val=iTcpMaxPortsExhausted;
		if (RegOpenKey(HKEY_LOCAL_MACHINE, sKey_PATH, &hKey) != ERROR_SUCCESS)
			if (RegCreateKey(HKEY_LOCAL_MACHINE, sKey_TcpMaxPortsExhausted, &hKey) != ERROR_SUCCESS)
				return FALSE;
		r = RegSetValueEx(hKey, sKey_TcpMaxPortsExhausted, 0, REG_DWORD, (BYTE *)&val, sizeof(val));
		RegCloseKey(hKey);
		bRet&= (r == ERROR_SUCCESS);


		//
		// Set sKey_TcpMaxConnectResponseRetransmissions
		//
		val=iTcpMaxConnectResponseRetransmissions;
		if (RegOpenKey(HKEY_LOCAL_MACHINE, sKey_PATH, &hKey) != ERROR_SUCCESS)
			if (RegCreateKey(HKEY_LOCAL_MACHINE, sKey_TcpMaxConnectResponseRetransmissions, &hKey) != ERROR_SUCCESS)
				return FALSE;
		r = RegSetValueEx(hKey, sKey_TcpMaxConnectResponseRetransmissions, 0, REG_DWORD, (BYTE *)&val, sizeof(val));
		RegCloseKey(hKey);
		bRet&= (r == ERROR_SUCCESS);

	}

	return bRet;

}


