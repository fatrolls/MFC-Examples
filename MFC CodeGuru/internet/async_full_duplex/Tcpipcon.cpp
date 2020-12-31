#include "stdafx.h"
#include "tcpipcon.h"

CTcpIpConnection::CTcpIpConnection() :
	CInOutConnection()
{
	m_waitForReplyOnConnection = FALSE;
	InSocket = INVALID_SOCKET;
	OutSocket = INVALID_SOCKET;
}

CTcpIpConnection::~CTcpIpConnection()
{
	if (InSocket != INVALID_SOCKET) closesocket(InSocket);
	if (OutSocket != INVALID_SOCKET) closesocket(OutSocket);
}

void CTcpIpConnection::ResetConnection()
{
	if (InSocket != INVALID_SOCKET) closesocket(InSocket);
	InSocket = INVALID_SOCKET;
	if (OutSocket != INVALID_SOCKET) closesocket(OutSocket);
	OutSocket = INVALID_SOCKET;
	CInOutConnection::ResetConnection();
}

BOOL CTcpIpConnection::InitConnection(SOCKET inSocket, SOCKET outSocket)
{
	InSocket = inSocket;
	OutSocket = outSocket;
	BOOL bl = TRUE;
	unsigned long blength = 256;
	unsigned long bpr = 0;
	setsockopt(InSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&bl, sizeof(BOOL));
	setsockopt(OutSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&bl, sizeof(BOOL));
	setsockopt(InSocket, IPPROTO_TCP, SO_KEEPALIVE, (const char*)&bl, sizeof(BOOL));
	setsockopt(OutSocket, IPPROTO_TCP, SO_KEEPALIVE, (const char*)&bl, sizeof(BOOL));
	return TRUE;
}

void CTcpIpConnection::SetTerminate()
{
	if (InSocket!=INVALID_SOCKET) closesocket(InSocket);
	InSocket = INVALID_SOCKET;
	if (OutSocket!=INVALID_SOCKET) closesocket(OutSocket);
	OutSocket = INVALID_SOCKET;
	CInOutConnection::SetTerminate();
}

//client part of the connection
void* CTcpIpConnection::GetConnectionMessage(DWORD portNo, DWORD& length)
{
	DWORD* t = new DWORD;
	*t = portNo;
	length = sizeof(DWORD);
	return (void*)t;
}

BOOL CTcpIpConnection::ConnectionMessageValid(void* msg, DWORD& length)
{
	return TRUE;
}

BOOL CTcpIpConnection::ConnectToServer(char* serverName, int _port)
{
#ifndef _DEBUG
	try{
#endif
	if (IsConnectionValid()) return TRUE;
	//create socket for server connection
	SOCKET ServerSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sai;
	memset(&sai, 0, sizeof(sockaddr_in));
	sai.sin_port = htons(_port);
	sai.sin_family = AF_INET;
	sai.sin_addr.s_addr = inet_addr(serverName);
	if(INADDR_NONE == sai.sin_addr.s_addr)
	{

		hostent *Hostent = gethostbyname(serverName);
		if (Hostent == NULL)
		{
			closesocket(ServerSock);
			return FALSE;
		};
		sai.sin_addr.s_addr = ((struct in_addr FAR *)(Hostent->h_addr))->s_addr;
	};
	int res = connect(ServerSock, (sockaddr*)&sai, sizeof(sockaddr_in));
	if (res!=0)
	{//error during connection
		closesocket(ServerSock);
		return FALSE;
	};
	//create listening socket
	SOCKET incs;
	SOCKET tempcs = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;                                          
	res = bind(tempcs, (sockaddr*)&addr, sizeof(sockaddr_in));
	int len = sizeof(addr);
	res = getsockname(tempcs, (sockaddr*)&addr, &len);
	int port = addr.sin_port;
	listen(tempcs, 5);
	DWORD length;
	void* msg = GetConnectionMessage(port, length);
	if (msg == NULL)
	{
		closesocket(ServerSock);
		closesocket(tempcs);
		return FALSE;
	};
	if (!SendNetworkMessage(ServerSock, msg, length))
	{
		delete msg;
		closesocket(ServerSock);
		closesocket(tempcs);
		return FALSE;
	};
	delete msg;
	len = sizeof(sockaddr_in);
	incs = accept(tempcs, (sockaddr*)&addr, &len);           
	if (incs == INVALID_SOCKET)
	{
		closesocket(ServerSock);
		closesocket(tempcs);
		return FALSE;
	};
	closesocket(tempcs);
	if (m_waitForReplyOnConnection)
	{
		//if connection is Ok, we should receive message from Server (should not we??)
		DWORD l;
		msg = ReceiveNetworkMessage(incs, l); 
		if (msg == NULL || !ConnectionMessageValid(msg, length))
		{
			if (msg!=NULL) delete msg;
			closesocket(ServerSock);
			closesocket(incs);
			return FALSE;
		};
		delete msg;
	};
	ResetConnection();
	InitConnection(incs, ServerSock);
	if (!CreateThreads()) return FALSE;
	return TRUE;
#ifndef _DEBUG
	}catch(...){ASSERT(FALSE);return FALSE;};
#endif
}

//Server side
DWORD CTcpIpConnection::GetConnectionPort(void* msg, DWORD length)
{
	return 0;
}

void* CTcpIpConnection::cioReceiveMessage(int* Error, int* length)
{
//	return ReceiveNetMessage(Error, length);
	int l;
	int TickCount = 0;
	*Error = 0;
	char* buf = new char[*length];
	char* tempbuf = buf;
	int recl = 0;
	do
	{
		l = recv(GetInSocket(), tempbuf, *length-recl, 0);
		if (l==SOCKET_ERROR || l==0) 
		{
			*Error = 1;
			delete buf;
			return NULL;
		};
		recl+=l;
		tempbuf+=l;
		if (recl<*length) 
		{
			TickCount+=1;
			Sleep(50);//retry to receive every 10 miliseconds
		};
	}while(recl<*length && TickCount<2000);
	*length = recl;
	return buf;
}

BOOL CTcpIpConnection::cioSendMessage(void* msg, int msg_size)
{
	return SendNetMessage(msg, msg_size);
}
