// Overlpped_Server2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <Windows.h>
#include <process.h>
#pragma comment(lib, "WS2_32.lib")

#define MAX_BUFFER	256
#define MAX_TIMEOUT 1000

typedef enum _OPERATION_INFO
{
	OP_NULL,
	OP_READ,
	OP_WRITE
}OPERATIONINFO;

typedef struct _OVERLAPPED_INFO_
{	
public:
	_OVERLAPPED_INFO_()
	{
		Clean();
	}
	~_OVERLAPPED_INFO_()
	{
		Clean();
	}
protected:
	void Clean()
	{
		ol.hEvent = NULL;
		sock = INVALID_SOCKET;
		memset(&addr, 0, sizeof(addr));
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(0);
		wsaBuf.buf = szBuf;
		wsaBuf.len = MAX_BUFFER;
		memset(szBuf, 0, sizeof(szBuf));
		dwTrans = 0;
		dwFlags = 0;
		nOpType = OP_NULL;
	}
public:
	WSAOVERLAPPED ol;
	SOCKET sock;
	SOCKADDR_IN addr;
	WSABUF wsaBuf;
	char szBuf[MAX_BUFFER];
	DWORD dwTrans;
	DWORD dwFlags;
	OPERATIONINFO nOpType;
}OVERLAPPEDINFO, *POVERLAPPEDINFO;

unsigned __stdcall ThreadProc(LPVOID lParam);
void CALLBACK CompleteRoutine(DWORD dwError, DWORD dwTrans, LPWSAOVERLAPPED Overlppad, DWORD dwFlags);
BOOL bExitThread = FALSE;
int g_nIndex = 0;
OVERLAPPEDINFO* g_ol[WSA_MAXIMUM_WAIT_EVENTS] = {0};

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	if(0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("WSAStartup failed with error: %d/n", GetLastError());
		return EXIT_FAILURE;
	}
	if(2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion))
	{
		printf("Socket version not supported./n");
		WSACleanup();
		return EXIT_FAILURE;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == sock)
	{
		printf("socket failed with error code: %d/n", WSAGetLastError());
		WSACleanup();
		return EXIT_FAILURE;
	}
	SOCKADDR_IN addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(5050);
	if(SOCKET_ERROR == bind(sock, (LPSOCKADDR)&addr, sizeof(addr)))
	{
		printf("bind failed with error code: %d/n", WSAGetLastError());
		closesocket(sock);
		sock = INVALID_SOCKET;
		WSACleanup();
		return EXIT_FAILURE;
	}
	if(SOCKET_ERROR == listen(sock, 5))
	{
		printf("listen failed with error code: %d/n", WSAGetLastError());
		closesocket(sock);
		sock = INVALID_SOCKET;
		WSACleanup();
		return EXIT_FAILURE;
	}
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, 0, NULL);
	SOCKADDR_IN remote = {0};
	int len = sizeof(remote);
	printf("Server start, wait for client to connect .../n");
	while(TRUE)
	{
		SOCKET sNew = accept(sock, (LPSOCKADDR)&remote, &len);
		if(INVALID_SOCKET == sNew)
		{
			printf("accept failed with error code: %d/n", WSAGetLastError());
			continue;
		}
		printf("Client <%s : %d> come in./n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
		g_ol[g_nIndex] = new OVERLAPPEDINFO;
		g_ol[g_nIndex]->sock = sNew;
		g_ol[g_nIndex]->nOpType = OP_READ;
		memcpy(&(g_ol[g_nIndex]->addr), &remote, sizeof(remote));
		if(SOCKET_ERROR == WSARecv(g_ol[g_nIndex]->sock, &(g_ol[g_nIndex]->wsaBuf), 1, &(g_ol[g_nIndex]->dwTrans),
			&(g_ol[g_nIndex]->dwFlags), &(g_ol[g_nIndex]->ol), CompleteRoutine))
		{
			if(WSA_IO_PENDING != WSAGetLastError())
			{
				printf("WSARecv failed with error code: %d/n", WSAGetLastError());
				closesocket(g_ol[g_nIndex]->sock);
				delete g_ol[g_nIndex];
				g_ol[g_nIndex] = NULL;
				continue;
			}
		}
		g_nIndex++;
	}

	bExitThread = TRUE;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	if(INVALID_SOCKET != sock)
	{
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
	WSACleanup();
	return 0;
}

unsigned __stdcall ThreadProc(LPVOID lParam)
{
	while(!bExitThread)
	{
		DWORD dwRet = SleepEx(INFINITE, TRUE);
		if(WAIT_IO_COMPLETION == dwRet)
		{

		}
		else
		{
			printf("SleepEx failed with error code: %d/n", GetLastError());
		}
	}
	return 0;
}

void CALLBACK CompleteRoutine(DWORD dwError, DWORD dwTrans, LPWSAOVERLAPPED Overlppad, DWORD dwFlags)
{
	int nIndex = 0;
	for(; nIndex<g_nIndex; nIndex++)
	{
		if(&g_ol[nIndex]->ol == Overlppad)
		{
			break;
		}
	}
	if(0 != dwError || 0 == dwTrans)
	{
		printf("Client: <%s : %d> leave./n", inet_ntoa(g_ol[nIndex]->addr.sin_addr), ntohs(g_ol[nIndex]->addr.sin_port));
		closesocket(g_ol[nIndex]->sock);
		delete g_ol[nIndex];
		// Error or closesocket by peer
		for(int i=nIndex; i<g_nIndex-1; i++)
		{
			g_ol[i] = g_ol[i+1];
		}
		g_nIndex--;
	}
	else
	{
		switch(g_ol[nIndex]->nOpType)
		{
		case OP_READ:
			{
				printf("recv <%s : %d> data: %s/n", inet_ntoa(g_ol[nIndex]->addr.sin_addr), ntohs(g_ol[nIndex]->addr.sin_port), g_ol[nIndex]->szBuf);
				g_ol[nIndex]->nOpType = OP_WRITE;
				memset(&(g_ol[nIndex]->ol), 0, sizeof(g_ol[nIndex]->ol));
				if(SOCKET_ERROR  == WSASend(g_ol[nIndex]->sock, &(g_ol[nIndex]->wsaBuf), 1, &(g_ol[nIndex]->dwTrans), g_ol[nIndex]->dwFlags, &(g_ol[nIndex]->ol), CompleteRoutine))
				{
					if(WSA_IO_PENDING != WSAGetLastError())
					{
						printf("WSASend failed with error code: %d/n", WSAGetLastError());
					}
				}
			}			
			break;

		case OP_WRITE:
			{
				g_ol[nIndex]->nOpType = OP_READ;
				dwFlags = 0;
				memset(&(g_ol[nIndex]->ol), 0, sizeof(g_ol[nIndex]->ol));
				memset(g_ol[nIndex]->szBuf, 0, sizeof(g_ol[nIndex]->szBuf));
				g_ol[nIndex]->wsaBuf.buf = g_ol[nIndex]->szBuf;
				dwTrans = g_ol[nIndex]->wsaBuf.len = MAX_BUFFER;
				if(SOCKET_ERROR == WSARecv(g_ol[nIndex]->sock, &(g_ol[nIndex]->wsaBuf), 1, &dwTrans, &dwFlags, &(g_ol[nIndex]->ol), CompleteRoutine))
				{
					if(WSA_IO_PENDING != WSAGetLastError())
					{
						printf("WSARecv failed with error code: %d./n", WSAGetLastError());
					}
				}
			}
			break;

		default:
			break;
		}
	}
}