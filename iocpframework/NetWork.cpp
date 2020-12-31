// NetWork.cpp : Defines the entry point for the console application.
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
		nOpType = OP_NULL;
	}
public:
	WSAOVERLAPPED ol;
	SOCKET sock;
	SOCKADDR_IN addr;
	WSABUF wsaBuf;
	char szBuf[MAX_BUFFER];
	OPERATIONINFO nOpType;
}OVERLAPPEDINFO, *POVERLAPPEDINFO;

WSAEVENT g_event[WSA_MAXIMUM_WAIT_EVENTS] = {0};
OVERLAPPEDINFO* g_ol[WSA_MAXIMUM_WAIT_EVENTS] = {0};
int g_nIndex = 0;
BOOL g_bExitThread = FALSE;

unsigned __stdcall ThreadProc(LPVOID lParam);

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	if(0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("WSAStartup failed with error code: %d/n", GetLastError());
		return EXIT_FAILURE;
	}
	if(2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion))
	{
		printf("Socket version not supported./n");
		WSACleanup();
		return EXIT_FAILURE;
	}
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == sListen)
	{
		printf("socket failed with error code: %d/n", WSAGetLastError());
		WSACleanup();
		return EXIT_FAILURE;
	}
	SOCKADDR_IN addr = {0};
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5050);
	if(SOCKET_ERROR == bind(sListen, (LPSOCKADDR)&addr, sizeof(addr)))
	{
		printf("bind failed with error code: %d/n", WSAGetLastError());
		closesocket(sListen);
		sListen = INVALID_SOCKET;
		WSACleanup();
		return EXIT_FAILURE;
	}
	if(SOCKET_ERROR == listen(sListen, 5))
	{
		printf("listen failed with error code: %d/n", WSAGetLastError());
		closesocket(sListen);
		sListen = INVALID_SOCKET;
		WSACleanup();
		return EXIT_FAILURE;
	}
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, 0, NULL);
	if(NULL == hThread)
	{
		printf("_beginthreadex failed with error code: %d/n", GetLastError());
		closesocket(sListen);
		sListen = INVALID_SOCKET;
		WSACleanup();
		return EXIT_FAILURE;
	}
	
	printf("Server start listen and wait for client to connect .../n");

	SOCKADDR_IN remote = {0};
	int len = sizeof(remote);

	while(TRUE)
	{
		if(g_nIndex >= WSA_MAXIMUM_WAIT_EVENTS)
		{
			printf("Too many connect, wait for disconnect .../n");
			continue;
		}
		SOCKET sNew = accept(sListen, (LPSOCKADDR)&remote, &len);
		if(INVALID_SOCKET == sNew)
		{
			printf("accept failed with error code: %d/n", WSAGetLastError());
			continue;
		}
		printf("<IP: %s, Port: %d> client come in./n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
		DWORD dwTrans = 0;
		DWORD dwFlags = 0;
		g_ol[g_nIndex] = new OVERLAPPEDINFO;
		g_ol[g_nIndex]->sock = sNew;
		memcpy(&g_ol[g_nIndex]->addr, &remote, sizeof(remote));
		g_event[g_nIndex] = g_ol[g_nIndex]->ol.hEvent = WSACreateEvent();
		g_ol[g_nIndex]->nOpType = OP_READ;
		if(SOCKET_ERROR == WSARecv(g_ol[g_nIndex]->sock, &(g_ol[g_nIndex]->wsaBuf), 1, &dwTrans, &dwFlags, (LPWSAOVERLAPPED)&(g_ol[g_nIndex]->ol), NULL))
		{
			if(ERROR_IO_PENDING != WSAGetLastError())
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
	// End of thread and exit process
	g_bExitThread = TRUE; // Exit thread.
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	WSACleanup();
	return 0;
}

unsigned __stdcall ThreadProc(LPVOID lParam)
{
	while(!g_bExitThread)
	{
		DWORD dwTrans = 0;
		DWORD dwFlags = 0;
		DWORD dwIndex = WSAWaitForMultipleEvents(g_nIndex, g_event, FALSE, MAX_TIMEOUT, FALSE);
		if(WSA_WAIT_FAILED == dwIndex || WSA_WAIT_TIMEOUT == dwIndex)
		{
			continue;
		}
		
		dwIndex -= WSA_WAIT_EVENT_0;
		for(int i = dwIndex; i < g_nIndex; i++)
		{
			dwIndex = WSAWaitForMultipleEvents(1, &g_event[dwIndex], TRUE, INFINITE, FALSE);
			if(WSA_WAIT_FAILED == dwIndex)
			{
				continue;
			}
			dwIndex -= WSA_WAIT_EVENT_0;
			WSAResetEvent(g_event[dwIndex]);
			BOOL bRet = WSAGetOverlappedResult(g_ol[dwIndex]->sock, &(g_ol[dwIndex]->ol), &dwTrans, FALSE, &dwFlags);
			if(bRet)
			{
				if(dwTrans > 0)
				{
					switch(g_ol[dwIndex]->nOpType)
					{
					case OP_READ:
						{
							printf("recv client <%s:%d> data: %s/n", inet_ntoa(g_ol[dwIndex]->addr.sin_addr), ntohs(g_ol[dwIndex]->addr.sin_port), g_ol[dwIndex]->szBuf);
							g_ol[dwIndex]->nOpType = OP_WRITE;
							memset(&(g_ol[dwIndex]->ol), 0, sizeof(g_ol[dwIndex]->ol));
							if(SOCKET_ERROR == WSASend(g_ol[dwIndex]->sock, &(g_ol[dwIndex]->wsaBuf), 1, &dwTrans, dwFlags, &(g_ol[dwIndex]->ol), NULL))
							{
								if(ERROR_IO_PENDING != WSAGetLastError())
								{
									printf("WSASend failed with error code: %d/n", WSAGetLastError());
									continue;
								}
							}
						}
						break;

					case OP_WRITE:
						{
							g_ol[dwIndex]->nOpType = OP_READ;
							memset(&(g_ol[dwIndex]->ol), 0, sizeof(g_ol[dwIndex]->ol));
							memset(g_ol[dwIndex]->szBuf, 0, sizeof(g_ol[dwIndex]->szBuf));
							dwFlags = 0;
							g_ol[dwIndex]->wsaBuf.buf = g_ol[dwIndex]->szBuf;
							dwTrans = g_ol[dwIndex]->wsaBuf.len = MAX_BUFFER;
							if(SOCKET_ERROR == WSARecv(g_ol[dwIndex]->sock, &(g_ol[dwIndex]->wsaBuf), 1, &dwTrans, &dwFlags, &(g_ol[dwIndex]->ol), NULL))
							{
								if(ERROR_IO_PENDING != WSAGetLastError())
								{
									printf("WSARecv failed with error code: %d/n", WSAGetLastError());
									continue;
								}
							}
						}
						break;

					default:
						break;
					}				
				}
				else
				{
					printf("client <%s : %d> leave./n", inet_ntoa(g_ol[dwIndex]->addr.sin_addr), ntohs(g_ol[dwIndex]->addr.sin_port));
					closesocket(g_ol[dwIndex]->sock);
					WSACloseEvent(g_event[dwIndex]);
					delete g_ol[dwIndex];
					// Rebuild array
					for(int i= dwIndex; i<g_nIndex-1; i++)
					{
						g_event[i] = g_event[i+1];
						g_ol[i] = g_ol[i+1];
					}
					g_nIndex--;
				}
			}
			else
			{
				printf("WSAGetOverlappedResult failed with error: %d/n", WSAGetLastError());
			}
		}
	}
	printf("Server to exit ... /n");

	return 0;
}

