/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File RawSocket.cpp
// class CWizRawSocket
//
// 23/07/1996 14:54                       Author: Poul, Hadas & Oren
///////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include <RawSocket.h>
#ifdef _UNICODE
#include <winnls.h>
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//*****************************************************************
void CWizSyncSocket::Init(SOCKET h)
{
	m_hSocket = h;
}
//*****************************************************************
void CWizSyncSocket::Close()
{
	ASSERT(m_hSocket != INVALID_SOCKET);
	::closesocket(m_hSocket);
	m_hSocket = INVALID_SOCKET;
}
//*****************************************************************
int CWizSyncSocket::SetIntOption(int level, int optname, int val)
{
	return ::setsockopt (m_hSocket, level, optname, (char *)&val, sizeof(val));
}
//*****************************************************************
BOOL CWizSyncSocket::InitializeSocket(int nPort)
{
	// Socket must be created with socket()
	ASSERT(m_hSocket != INVALID_SOCKET);
	// Make up address
	SOCKADDR_IN	SockAddr;
	memset(&SockAddr,0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = INADDR_ANY;
	SockAddr.sin_port   = ::htons(nPort);
	// Bind to the address and port
	int r = ::bind(m_hSocket, (SOCKADDR*)&SockAddr, sizeof(SockAddr));
	if (r == 0)
		{
		SetIntOption (SOL_SOCKET, SO_DONTLINGER,1);
		SetIntOption (SOL_SOCKET, SO_KEEPALIVE,1);
		// establishes a socket to listen for incoming connection
		// so Accept can be called
		r = ::listen (m_hSocket, 5);
		if (r == 0)
			return TRUE;
		}
	return FALSE;
}
//*****************************************************************
BOOL CWizSyncSocket::Create(int nPort)
{
	// creates a socket
	m_hSocket = ::socket(PF_INET, SOCK_STREAM, 0);
	if (m_hSocket == INVALID_SOCKET)
		return FALSE;
	// Bind to the port
	if (!InitializeSocket(nPort))
		{
		Close();
		return FALSE;
		}
	return TRUE;
}
//*****************************************************************
// Create an invalid socket
CWizSyncSocket::CWizSyncSocket(SOCKET h /* = INVALID_SOCKET */)
{
	Init(h);
}
//*****************************************************************
// Create a listening socket
CWizSyncSocket::CWizSyncSocket(int nPort)
{
	Init(INVALID_SOCKET);
	if(!Create(nPort))
		throw XCannotCreate();
}
//*****************************************************************
CWizSyncSocket::~CWizSyncSocket()
{
	if (m_hSocket != INVALID_SOCKET)
		Close();
}
//*****************************************************************
// Waits for pending connections on the port, 
// creates a new socket with the same properties as this 
// and returns a handle to the new socket
SOCKET CWizSyncSocket::Accept()
{
	SOCKET h = ::accept (m_hSocket, NULL, NULL);
	return h;
}
//*****************************************************************
// Cerates a socket and establishes a connection to a peer
// on lpszHostAddress:nHostPort 
BOOL CWizSyncSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort )
{
	ASSERT(lpszHostAddress != NULL);
	// Create ? socket
	if (m_hSocket == INVALID_SOCKET)
		{
		m_hSocket = ::socket(PF_INET, SOCK_STREAM, 0);
		if (m_hSocket == INVALID_SOCKET)
			return FALSE;
		}

	// Fill address machinery of sockets.
	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));
#ifdef _UNICODE
	char buff[500];
	WideCharToMultiByte(CP_ACP, 0, lpszHostAddress, -1, buff, 500, NULL, NULL);
	LPSTR lpszAscii = buff;
#else
	LPSTR lpszAscii = (LPSTR)lpszHostAddress;
#endif
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}
	}
	sockAddr.sin_port = htons((u_short)nHostPort);
	// connects to peer
	int r = ::connect(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	if (r != SOCKET_ERROR)
		{
		ASSERT(r == 0);
		return TRUE;
		}

	int e = ::WSAGetLastError();
	ASSERT(e != WSAEWOULDBLOCK);

	return FALSE;
}

//*****************************************************************
// read raw data
int	CWizReadWriteSocket::Read(void *pData, int nLen) 
{
	char* pcData = (char* )pData;
	int	n = nLen;
	// if data size is bigger then network buffer
	// handle it nice
	do
		{
		int r1 = ::recv (m_hSocket, pcData, n, 0);
		if (r1 == SOCKET_ERROR)
			{
			int e = WSAGetLastError();
			ASSERT(e != WSAEWOULDBLOCK);
			return 0;
			}
		else if (r1 == 0)
			return 0; 
		else if (r1 < 0)
			{
			ASSERT(0);
			return 0;
			}
		pcData += r1;
		n -= r1;
		} while (n > 0);

	ASSERT(n == 0);
	return nLen;
}
//*****************************************************************
// write raw data
int	CWizReadWriteSocket::Write(const void *pData, int nLen) 
{
	const char* pcData = (const char* )pData;
	int	n = nLen;
	// if data size is bigger then network buffer
	// handle it nice
	
	do
		{
		int r1 = ::send (m_hSocket, pcData, n, 0);
		if (r1 == SOCKET_ERROR)
			{
			int e = WSAGetLastError();
			ASSERT(e != WSAEWOULDBLOCK);
			return 0;
			}
		else if (r1 == 0)
			return 0;
		else if (r1 < 0)
			{
			ASSERT(0);
			return 0;
			}
		pcData += r1;
		n -= r1;
		} while (n > 0);

	ASSERT(n == 0);
	return nLen;
}
//*****************************************************************
// Reads UNICODE string from socket.
// Converts string from ANSI to UNICODE.
int CWizReadWriteSocket::ReadString  (WCHAR* lpszString, int nMaxLen)
{
	// read string length
	u_long nt_Len;
	if (Read(&nt_Len, sizeof(nt_Len)) < sizeof(nt_Len))
		return 0;
	int Len = ntohl(nt_Len);
	if (Len == 0 || Len >= nMaxLen)
		return 0;

	static const int BUFF_SIZE = 2000;
	if (Len >= BUFF_SIZE)
		return 0;
	char buff[BUFF_SIZE];
	// Read ANSI string to the buffer
	if (Read(buff, Len) < Len)
		return 0;
	buff[Len] = 0;

	// Convert ANSI string to the UNICODE
	VERIFY(::MultiByteToWideChar(CP_ACP, 0, buff, Len, lpszString, nMaxLen*sizeof(lpszString[0])));
	return Len;
}
//*****************************************************************
// Reads ANSI string from socket.
int CWizReadWriteSocket::ReadString  (char* lpszString, int nMaxLen)
{
	// read string length
	u_long nt_Len;
	if (Read(&nt_Len, sizeof(nt_Len)) < sizeof(nt_Len))
		return 0;
	int Len = ntohl(nt_Len);
	if (Len == 0 || Len >= nMaxLen)
		return 0;

	// Read ANSI string
	if (Read(lpszString, Len) < Len)
		return 0;
	lpszString[Len] = 0;
	return Len;
}
//*****************************************************************
inline int Length(const char* p)
{
	return strlen(p);
}
//*****************************************************************
inline int Length(const WCHAR* p)
{
	return wcslen(p);
}
//*****************************************************************
// Writes UNICODE string to socket,
// converts UNICODE string to ANSI.
BOOL CWizReadWriteSocket::WriteString (const WCHAR*  lpszString, int nLen /* = -1*/)
{
	if (nLen < 0)
		nLen = Length(lpszString);
	static const int BUFF_SIZE = 2000;
	if (nLen >= BUFF_SIZE*sizeof(lpszString) + sizeof(u_long))
		return FALSE;
	char buff[BUFF_SIZE];
	u_long nt_Len = htonl(nLen);
	int nSize = sizeof(nt_Len);
	memcpy(buff, &nt_Len, nSize);
	// To make one call less, the length of the string
	// copied to the buffer before the string itself
	// and the buffer sent once.
	char* ptr = buff + nSize;
	if (nLen > 0)
		{
		// Convert ANSI to UNICODE
		int s = WideCharToMultiByte(CP_ACP, 0, lpszString, nLen, ptr, BUFF_SIZE - sizeof(u_long), NULL, NULL);
		ASSERT(s > 0);
		nSize += s;
		}
	return Write(buff, nSize);
}
//*****************************************************************
// Writes ANSI string to socket.
BOOL CWizReadWriteSocket::WriteString (const char* lpszString, int nLen /* = -1*/)
{
	if (nLen < 0)
		nLen = strlen(lpszString);
	static const int BUFF_SIZE = 2000;
	if (nLen >= BUFF_SIZE*sizeof(lpszString) + sizeof(u_long))
		return FALSE;
	char buff[BUFF_SIZE];
	u_long nt_Len = htonl(nLen);
	int nSize = sizeof(nt_Len);
	memcpy(buff, &nt_Len, nSize);
	// To make one call less, the length of the string
	// copied to the buffer before the string itself
	// and the buffer sent once.
	char* ptr = buff + nSize;
	if (nLen > 0)
		{
		memcpy(ptr, lpszString, nLen);
		nSize += nLen;
		}
	return Write(buff, nSize);
}
//*****************************************************************
BOOL CWizSyncSocket::GetHostName(LPTSTR lpszAddress, size_t nAddrSize, UINT& rSocketPort)
{
	if (nAddrSize < 1)
		return FALSE;

	*lpszAddress = TCHAR(0);
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	int r;

	while ((r = ::getsockname(m_hSocket, (SOCKADDR*)&sockAddr, &nSockAddrLen)) == SOCKET_ERROR)
		{
		const int e = ::WSAGetLastError();
		if (e != WSAEINPROGRESS)
			return FALSE;
		}

	ASSERT(r == 0);
	rSocketPort = ::ntohs(sockAddr.sin_port);

	char    szName[64];
	struct  hostent *h;
	DWORD	dwMyAddress;

	int r1;
	while((r1 = ::gethostname(szName,sizeof(szName))) == SOCKET_ERROR)
		{
		const int e = ::WSAGetLastError();
		if (e != WSAEINPROGRESS)
			return FALSE;
		}

	ASSERT(r1 == 0);
	h = (struct hostent *) ::gethostbyname(szName);
	memcpy(&dwMyAddress,h->h_addr_list[0],sizeof(DWORD));
	if (dwMyAddress == INADDR_NONE)
		return FALSE;
	struct   in_addr     tAddr;
	memcpy(&tAddr,&dwMyAddress,sizeof(DWORD));
	char    *ptr = ::inet_ntoa(tAddr);

#ifdef _UNICODE
	return ::MultiByteToWideChar(CP_ACP, 0, ptr, -1, lpszAddress, nAddrSize*sizeof(lpszAddress[0]));
#else
	if (size_t(lstrlen(ptr)) >= nAddrSize)
		return FALSE;
	lstrcpy(lpszAddress, ptr);
#endif

	return TRUE;
}
//*****************************************************************
BOOL CWizSyncSocket::GetPeerName(LPTSTR lpszAddress, size_t nAddrSize, UINT& rPeerPort)
{
	if (nAddrSize < 1)
		return FALSE;
	*lpszAddress = TCHAR(0);
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);
	int r;
	while ((r = ::getpeername(m_hSocket, (SOCKADDR*)&sockAddr, &nSockAddrLen)) == SOCKET_ERROR)
		{
		const int e = ::WSAGetLastError();
		if (e != WSAEINPROGRESS)
			return FALSE;
		}

	ASSERT(r == 0);
	rPeerPort = ntohs(sockAddr.sin_port);
	char * pAddr = inet_ntoa(sockAddr.sin_addr);
	int len = strlen(pAddr);
#ifdef _UNICODE
	char buff[100];
	if (len >= 100 || len >= int(nAddrSize))
		return FALSE;
	memcpy(buff, pAddr,100);
	return ::MultiByteToWideChar(CP_ACP, 0, buff, len, lpszAddress, nAddrSize*sizeof(lpszAddress[0]));
#else
	if (size_t(len) >= nAddrSize)
		return FALSE;
	memcpy(lpszAddress, pAddr,len + 1);
#endif
	return TRUE;
}
//*****************************************************************

#ifdef _DEBUG
void Foo()
{

	CWizReadWriteSocket s;
	int i;
	short j;
	char k;
	double d;

	s << i << j << k << d;
	s >> i >> j >> k >> d;
}

#endif