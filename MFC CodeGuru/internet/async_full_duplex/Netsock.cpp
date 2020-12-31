#include "stdafx.h"
#include "tcpipcon.h"

BOOL CTcpIpConnection::SendNetMessage(void* msg, int msg_size)
{
#ifndef _DEBUG
	try{
#endif
	int l;
	int TickCount = 0;
	char* tempbuf = (char*)msg;
	int sentl = 0;
	do
	{
		l = send(GetOutSocket(), tempbuf, msg_size-sentl, 0);
		if (l == SOCKET_ERROR) return FALSE;
		sentl+=l;
		tempbuf+=l;
		if (sentl<msg_size)
		{
			Sleep(50);
			TickCount+=1;
		};
	}while (sentl < msg_size  && TickCount<2000);
	if (sentl!=msg_size) return FALSE;
	return TRUE;
#ifndef _DEBUG
	}catch(...){ASSERT(FALSE);return FALSE;};
#endif
}

//static CInOutConnection receive/send functions
BOOL CTcpIpConnection::SendNetworkMessage(SOCKET sock, void* msg, int length, DWORD msg_frame)
{
#ifndef _DEBUG
	try{
#endif
	DWORD Header_Length = 8;
	int sentl = 0;
	int TickCount = 0;
	//add header to the message
	char* b = new char[length+Header_Length];
	memcpy((char*)b+Header_Length, msg, length);
	((DWORD*)b)[0] = msg_frame;
	((DWORD*)b)[1] = length;
	char* tempbuf = b;
	length+=Header_Length;
	do
	{
		int l = send(sock, tempbuf, length-sentl, 0);
		if (l == SOCKET_ERROR) return FALSE;
		sentl+=l;
		tempbuf+=l;
		if (sentl<length)
		{
			Sleep(50);
			TickCount==1;
			if (TickCount>2000)
			{
				delete b;
				return FALSE;
			};
		};
	}while(sentl<length);
	delete b;
	return TRUE;
#ifndef _DEBUG
	}catch(...){ASSERT(FALSE);return FALSE;};
#endif
}

BOOL CTcpIpConnection::ReceiveMsg(SOCKET sock, char* buf, int size)
{
#ifndef _DEBUG
	try{
#endif
	char* tempbuf = buf;
	int recl = 0;
	int TickCount = 0;
	do
	{
		int l = recv(sock, tempbuf, size-recl, 0);
		if (l == SOCKET_ERROR) return FALSE;
		recl+=l;
		tempbuf = tempbuf+l;
		if (recl<size)
		{
			Sleep(50);
			TickCount+=1;
			if (TickCount>2000)
			{
				return FALSE;
			};
		};
	}while(recl<size);
	return TRUE;
#ifndef _DEBUG
	}catch(...){ASSERT(FALSE);return FALSE;};
#endif
}

void* CTcpIpConnection::ReceiveNetworkMessage(SOCKET sock, DWORD& length, DWORD msg_frame)
{
	const DWORD Header_Length = 8;
	char headerbuf[Header_Length];
	BOOL res = CTcpIpConnection::ReceiveMsg(sock, headerbuf, Header_Length);
	if (!res) return NULL;
	if (((DWORD*)headerbuf)[0]==msg_frame)
	{
		int size = ((DWORD*)headerbuf)[1];
		if (size == 0) return NULL;
		length = size;
		char* buf = new char[size];
		res = CTcpIpConnection::ReceiveMsg(sock, buf, size);
		if (!res)
		{
			delete buf;
			return NULL;
		};
		return buf;
	};
	return NULL;
}
