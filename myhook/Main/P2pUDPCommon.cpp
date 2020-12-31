#include "stdafx.h"
#include "P2PUDPCommon.h"
#include <algorithm>
#include "Helper.h"
#include "ProtocolTypes.h"

PeerList::PeerList()
{
}

PeerList::~PeerList()
{

}

bool PeerList::AddAPeer(HostInfo& info)
{
   if (find(info.strUserName) != end())
	   return false;
   insert(make_pair(CString(info.strUserName), info));
   return true;
}

bool PeerList::DeletePeer(CString strPeerName)
{
   if (find(strPeerName) == end())
	   return false;
   map<CString, HostInfo>::iterator it = find(strPeerName);
   erase(it);
   return true;
}

void PeerList::DeleteAllPeers()
{
   clear();
}

HostInfo* PeerList::GetAPeer(CString strPeerName)
{
	map<CString, HostInfo>::iterator it = find(strPeerName);
	if (it == end())
		return NULL;
	return &it->second;
}

HostInfo* PeerList::GetAPeer(sockaddr_in *addr)
{
    for(map<CString, HostInfo>::iterator it=begin(); it!=end(); it++)
	{
		if (it->second.dwIp == addr->sin_addr.S_un.S_addr 
		&&  it->second.nPort == addr->sin_port)
		    return &it->second;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
// CP2PUDPServer Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP2PUDPServer::CP2PUDPServer()
{
    m_socket = INVALID_SOCKET;
	m_bThreadExit = false;
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	MySockaddr_In addr(SERVER_PORT);
	bind(m_socket, (LPSOCKADDR)&addr, sizeof(addr));
	m_overlap.hEvent = m_event.m_hObject;
	m_pWorkThread = AfxBeginThread(AFX_THREADPROC(ThreadProc), this);
}

CP2PUDPServer::~CP2PUDPServer()
{
    m_bThreadExit = true;
	m_event.SetEvent();
	HANDLE aHandles[1] = { m_pWorkThread->m_hThread };
	WaitForMultipleObjects(1, aHandles, TRUE, INFINITE);
}

UINT CP2PUDPServer::ThreadProc(LPVOID param)
{
	CP2PUDPServer* pServer = (CP2PUDPServer*)param;
    char buf[4096];
	CP2PMessage* pMsg = (CP2PMessage*)buf;
    sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	DWORD nRet;
    WSABUF saBuf;

	saBuf.buf = buf;
	saBuf.len = 4096;

	while(!pServer->m_bThreadExit)
	{
		DWORD dwFlags = 0;
		pServer->QueryClientActive();
		if (SOCKET_ERROR == WSARecvFrom(pServer->m_socket, &saBuf, 1, &nRet, &dwFlags, (LPSOCKADDR)&remoteAddr, &nAddrLen, &pServer->m_overlap, NULL))
        {
			DWORD dwError = WSAGetLastError();
			CString strError;
			GetErrorMessage(dwError, strError);
			if (dwError != WSA_IO_PENDING)
			{
				if (pServer->m_bThreadExit)
			        break;
				//pServer->QueryClientActive();
				continue;
			}
			else
			{
				if (WaitForSingleObject(pServer->m_overlap.hEvent, 1000) == WAIT_TIMEOUT)
					continue;
				if (pServer->m_bThreadExit)
			        break;
				if (!GetOverlappedResult((HANDLE)pServer->m_socket, &pServer->m_overlap, &nRet, FALSE) || nRet <= 0)
				{
					//pServer->QueryClientActive();
					continue;
				}
			}
		}
		if (pServer->m_bThreadExit)
			break;
		if (nRet < sizeof(CP2PMessage))
		{
			//pServer->QueryClientActive();
			continue;
		}
		//命令
		switch(pMsg->action)
		{
        case USER_CONNECT:
			{
				CString strLog;
				strLog.Format("收到%s发出的请求%s打洞的消息\n", inet_ntoa(remoteAddr.sin_addr), inet_ntoa(*((in_addr*)&pMsg->hostinfo.dwIp)));
			    OutputDebugString(strLog);

				pServer->OnUserConnect(pMsg, remoteAddr);

				DWORD dwIP = pMsg->hostinfo.dwIp;
				USHORT nPort = pMsg->hostinfo.nPort;
				pMsg->hostinfo.dwIp = remoteAddr.sin_addr.S_un.S_addr;
				pMsg->hostinfo.nPort = remoteAddr.sin_port;
				strcpy(pMsg->hostinfo.strUserName, pServer->m_peerList.GetAPeer(&remoteAddr)->strUserName);
				remoteAddr.sin_port = nPort;
				remoteAddr.sin_addr.S_un.S_addr = dwIP;
				sendto(pServer->m_socket, (char*)pMsg, sizeof(CP2PMessage), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));
			}
			break;
		case USER_CONNECT_ACK:
			{
                CString strLog;
				strLog.Format("收到%s发出的%s请求打洞的响应消息\n", inet_ntoa(remoteAddr.sin_addr), inet_ntoa(*((in_addr*)&pMsg->hostinfo.dwIp)));
			    OutputDebugString(strLog);

				pServer->OnUserConnectAck(pMsg, remoteAddr);
				
				DWORD dwIP = pMsg->hostinfo.dwIp;
				USHORT nPort = pMsg->hostinfo.nPort;
				pMsg->hostinfo.dwIp = remoteAddr.sin_addr.S_un.S_addr;
				pMsg->hostinfo.nPort = remoteAddr.sin_port;
				strcpy(pMsg->hostinfo.strUserName, pServer->m_peerList.GetAPeer(&remoteAddr)->strUserName);
				remoteAddr.sin_port = nPort;
				remoteAddr.sin_addr.S_un.S_addr = dwIP;
				sendto(pServer->m_socket, (char*)pMsg, sizeof(CP2PMessage), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));
			}
			break;
		case USER_GET_USER_LIST:
			{
				CString strLog;
				strLog.Format("收到%s发出的请求用户列表消息\n", inet_ntoa(remoteAddr.sin_addr));
			    OutputDebugString(strLog);

				pServer->OnUserGetList(pMsg, remoteAddr);

				pMsg->action = USER_LIST_BEGIN;
                sendto(pServer->m_socket, (char*)pMsg, sizeof(CP2PMessage), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));

				map<CString, HostInfo>::iterator it;
				pMsg->action = USER_LIST_IN_PROGRESS;
				pServer->m_cs.Lock();
				for(it=pServer->m_peerList.begin(); it!=pServer->m_peerList.end(); it++)
				{
                     HostInfo& info = it->second;
					 memcpy(&pMsg->hostinfo, &info, sizeof(info));
					 sendto(pServer->m_socket, (char*)pMsg, sizeof(CP2PMessage), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));
				}
				pServer->m_cs.Unlock();
                pMsg->action = USER_LIST_COMPLETE;
                sendto(pServer->m_socket, (char*)pMsg, sizeof(CP2PMessage), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));
			}
			break;
		case USER_QUERY_ACTIVE_ACK:
			{
				pServer->OnUserQueryActiveAck(pMsg, remoteAddr);

                HostInfo* pInfo = pServer->m_peerList.GetAPeer(&remoteAddr);
				if (pInfo != NULL)
					pInfo->dwTickCount = GetTickCount();
			}
			break;
		case USER_LOG_IN:
			break;
		case USER_LOG_IN_2:	
			{
				CString strLog;
				strLog.Format("收到%s发出的请求Login消息\n", inet_ntoa(remoteAddr.sin_addr));
			    OutputDebugString(strLog);
				
				pServer->OnUserLogin(pMsg, remoteAddr);

				pMsg->hostinfo.dwTickCount = GetTickCount();
				pServer->m_cs.Lock();
				pServer->m_peerList.insert(make_pair(CString(pMsg->hostinfo.strUserName), pMsg->hostinfo));
				pServer->m_cs.Unlock();
				CP2PMessage msg;
				msg.action = USER_LOG_IN_ACK;
				msg.nDataLen = 0;
				sendto(pServer->m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));
			}
			break;
		case USER_LOG_OUT:
			{
				CString strLog;
				strLog.Format("收到%s发出的请求Logout消息\n", inet_ntoa(remoteAddr.sin_addr));
			    OutputDebugString(strLog);

				pServer->OnUserLogout(pMsg, remoteAddr);
                pServer->m_cs.Lock();
				map<CString, HostInfo>::iterator it = pServer->m_peerList.find(pMsg->hostinfo.strUserName);
				if (it != pServer->m_peerList.end())
					pServer->m_peerList.erase(it);
				pServer->m_cs.Unlock();
				CP2PMessage msg;
				msg.action = USER_LOG_OUT_ACK;
				msg.nDataLen = 0;
				sendto(pServer->m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&remoteAddr, sizeof(remoteAddr));
			}
			break;
		}
		//pServer->QueryClientActive();
	}
    return 0;
}

void CP2PUDPServer::OnUserConnect(CP2PMessage *pMsg, sockaddr_in& addr)
{
}

void CP2PUDPServer::OnUserConnectAck(CP2PMessage *pMsg, sockaddr_in& addr)
{
}

void CP2PUDPServer::OnUserGetList(CP2PMessage *pMsg, sockaddr_in& addr)
{
}

void CP2PUDPServer::OnUserQueryActiveAck(CP2PMessage *pMsg, sockaddr_in& addr)
{
}

void CP2PUDPServer::OnUserLogin(CP2PMessage *pMsg, sockaddr_in& addr)
{
}

void CP2PUDPServer::OnUserLogout(CP2PMessage *pMsg, sockaddr_in& addr)
{
}

void CP2PUDPServer::OnUpdateUserList()
{
}

//////////////////////////////////////////////////////////////////////
// CP2pUDPClient Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP2pUDPClient::CP2pUDPClient(int nPort)
{
    m_socket = INVALID_SOCKET;
	m_bThreadExit = false;
	m_bConnected = false;
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);

	m_nPort = nPort;

	if (nPort != 0)
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(nPort);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		bind(m_socket, (LPSOCKADDR)&addr, sizeof(addr));
	}
	m_overlap.hEvent = m_event.m_hObject;

    char szHost[MAX_PATH] = { 0 };
	gethostname(szHost, MAX_PATH);
	strcpy(m_SelfInfo.strUserName, szHost);
	hostent* pHost = gethostbyname(szHost);
	if (pHost == NULL)
		return;
	
	for(int i=0; ; i++)
	{
		char* p = pHost->h_addr_list[i];
		if (p == NULL)
			return;
		memcpy(&m_SelfInfo.dwIp, p, pHost->h_length);
		//in_addr addr1;
		//memcpy(&addr1.S_un.S_addr, p, pHost->h_length);
	    CString strIP = inet_ntoa(*(in_addr*)&m_SelfInfo.dwIp);
	    if (strIP != "0.0.0.0")
			break;
	}
	m_SelfInfo.nPort = 0;
	m_pWorkThread = AfxBeginThread(AFX_THREADPROC(ThreadProc), this);
}

CP2pUDPClient::~CP2pUDPClient()
{
    m_bThreadExit = true;
	m_event.SetEvent();
	HANDLE aHandles[1] = { m_pWorkThread->m_hThread };
	WaitForMultipleObjects(1, aHandles, TRUE, INFINITE);
	//closesocket(m_socket);
}

void CP2pUDPClient::OnUserListUpdate()
{
    for(int i=m_aHoleClients.size()-1; i>=0; i--)
	{
		HostInfo& info = m_aHoleClients[i];
		bool bFind = false;
		for(map<CString, HostInfo>::iterator it=m_peerList.begin(); it!=m_peerList.end(); it++)
		{
			if (it->second == info)
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)
			m_aHoleClients.erase(m_aHoleClients.begin()+i);
	}
}

void CP2pUDPClient::OnUserConnectAck(CP2PMessage *pMsg)
{

}

void CP2pUDPClient::OnUserMakeHole(CP2PMessage *pMsg)
{

}

void CP2pUDPClient::OnUserMsgAck(CP2PMessage *pMsg)
{

}


void CP2pUDPClient::OnUserMsg(CP2PMessage *pMsg)
{

}

UINT CP2pUDPClient::ThreadProc(LPVOID pParam)
{
	CP2pUDPClient* pClient = (CP2pUDPClient*)pParam;
    char buf[4096];
	CP2PMessage* pMsg = (CP2PMessage*)buf;
    sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	DWORD nRet;
    WSABUF saBuf;

	saBuf.buf = buf;
	saBuf.len = 4096;

	pClient->LogIn();
	
	while(true)
	{
		if (pClient->m_bThreadExit)
			  break;

		DWORD dwFlags = 0;
		pClient->GetUserList();
		
		if (SOCKET_ERROR == WSARecvFrom(pClient->m_socket, &saBuf, 1, &nRet, &dwFlags, (LPSOCKADDR)&remoteAddr, &nAddrLen, &pClient->m_overlap, NULL))
        {
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				if (pClient->m_bThreadExit)
			       break;
				//pClient->GetUserList();
				continue;
			}
			else
			{
				if (WaitForSingleObject(pClient->m_overlap.hEvent, 1000) == WAIT_TIMEOUT)
					continue;
				if (pClient->m_bThreadExit)
			       break;
				if (!GetOverlappedResult((HANDLE)pClient->m_socket, &pClient->m_overlap, &nRet, FALSE) || nRet <= 0)
				{
					//pClient->GetUserList();
					continue;
				}
			}
		}
		if (pClient->m_bThreadExit)
			break;
		if (nRet < sizeof(CP2PMessage))
		{
			//pClient->GetUserList();
			continue;
		}
		//命令
		switch(pMsg->action)
		{
        case USER_CONNECT:
			{
				sockaddr_in addr;
				addr.sin_family = AF_INET;
                addr.sin_port = pMsg->hostinfo.nPort;
				addr.sin_addr.S_un.S_addr = pMsg->hostinfo.dwIp;
				CString strIP = inet_ntoa(addr.sin_addr);
				int nPort = ntohs(addr.sin_port);
				CP2PMessage msg;
				//发出打洞消息
				msg.action = USER_MAKE_HOLE;
				memcpy(&msg.hostinfo, &pClient->m_SelfInfo, sizeof(HostInfo));
				msg.nDataLen = 0;
				sendto(pClient->m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
				//发出打洞响应给服务器
				pMsg->action = USER_CONNECT_ACK;
				addr.sin_port = htons(SERVER_PORT);
				addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
                sendto(pClient->m_socket, (char*)pMsg, sizeof(CP2PMessage), 0, (LPSOCKADDR)&addr, sizeof(addr));
				//加入已经打洞的客户列表
				pClient->m_aHoleClients.push_back(pMsg->hostinfo);
			}
			break;
		case USER_MAKE_HOLE:
			pClient->OnUserMakeHole(pMsg);
			break;
		case USER_CONNECT_ACK:
			pClient->m_aHoleClients.push_back(pMsg->hostinfo);
            pClient->OnUserConnectAck(pMsg);
			pClient->m_MakeHoleEvent.SetEvent();
			break;
		case USER_LIST_BEGIN:
			pClient->m_peerList.clear();
			break;
		case USER_LIST_IN_PROGRESS:
			pClient->m_peerList.AddAPeer(pMsg->hostinfo);
			break;
		case USER_LIST_COMPLETE:
			pClient->OnUserListUpdate();
			break;	
		case USER_QUERY_ACTIVE:
			{
				CP2PMessage msg;
				msg.nDataLen = 0;
				msg.action = USER_QUERY_ACTIVE_ACK;
				memcpy(&msg.hostinfo, &pClient->m_SelfInfo, sizeof(HostInfo));
				sockaddr_in addr;
				addr.sin_family = AF_INET;
				addr.sin_port = htons(SERVER_PORT);
				addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
				sendto(pClient->m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
			}
			break;
		case USER_LOG_IN_ACK:
			{
				pClient->m_bConnected = true;
				CP2PMessage msg;
				msg.action = USER_GET_USER_LIST;
				msg.nDataLen = 0;
				memcpy(&msg.hostinfo, &pClient->m_SelfInfo, sizeof(pClient->m_SelfInfo));
				sockaddr_in addr;
				addr.sin_family = AF_INET;
				addr.sin_port = htons(SERVER_PORT);
				addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
				sendto(pClient->m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
			}
			break;
		case USER_LOG_OUT_ACK:
			pClient->m_bThreadExit = true;
			pClient->m_bConnected = false;
			break;
		case USER_MSG_ACK:
			pClient->OnUserMsgAck(pMsg);
			break;
		case USER_MSG:
			pClient->OnUserMsg(pMsg);
			break;
		}
		//pClient->GetUserList();
	}

	pClient->LogOut();

    return 0;
}

void CP2pUDPClient::SendMsg(HostInfo *pHost, CString strMsg)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = pHost->nPort;
	addr.sin_addr.S_un.S_addr = pHost->dwIp;
	
	if (find(m_aHoleClients.begin(), m_aHoleClients.end(), *pHost) == m_aHoleClients.end())
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(SERVER_PORT);
		addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
		CP2PMessage msg;
		msg.action = USER_CONNECT;
		memcpy(&msg.hostinfo, pHost, sizeof(HostInfo));
		sendto(m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
		WaitForSingleObject(m_MakeHoleEvent.m_hObject, INFINITE);
	}
	
	if (find(m_aHoleClients.begin(), m_aHoleClients.end(), *pHost) == m_aHoleClients.end())
        return;
	int nSize = sizeof(CP2PMessage) + strMsg.GetLength() -1;
	CP2PMessage* pMsg = (CP2PMessage*)new char[nSize];
	pMsg->action = USER_MSG;
	memcpy(&pMsg->hostinfo, &m_SelfInfo, sizeof(HostInfo));
	pMsg->nDataLen = strMsg.GetLength();
	memcpy(pMsg->data, strMsg.GetBuffer(strMsg.GetLength()), strMsg.GetLength());
	pMsg->data[strMsg.GetLength()] = 0;
	sendto(m_socket, (char*)pMsg, nSize, 0, (LPSOCKADDR)&addr, sizeof(addr));
	Sleep(200);
	delete [] pMsg;
}

void CP2pUDPClient::LogIn()
{
    sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	CP2PMessage msg;
	msg.action = USER_LOG_IN;
	memcpy(&msg.hostinfo, &m_SelfInfo, sizeof(HostInfo));
	sendto(m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
	//sockaddr_in addr;
	int nLen = sizeof(addr);
	getsockname(m_socket, (LPSOCKADDR)&addr, &nLen);
	USHORT port = ntohs(addr.sin_port);
	m_SelfInfo.nPort = addr.sin_port;
    CP2PMessage msg2;
	msg2.action = USER_LOG_IN_2;
	memcpy(&msg2.hostinfo, &m_SelfInfo, sizeof(HostInfo));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);

	if (m_nPort == 0)
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = m_SelfInfo.nPort;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		bind(m_socket, (LPSOCKADDR)&addr, sizeof(addr));
	}

	sendto(m_socket, (char*)&msg2, sizeof(msg2), 0, (LPSOCKADDR)&addr, sizeof(addr));
}

void CP2pUDPClient::LogOut()
{
    sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	CP2PMessage msg;
	msg.action = USER_LOG_OUT;
	memcpy(&msg.hostinfo, &m_SelfInfo, sizeof(HostInfo));
	sendto(m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
}

void CP2PUDPServer::QueryClientActive()
{
	map<CString, HostInfo>::iterator it;
	ULONG dwTickCount;
	CP2PMessage msg;
	sockaddr_in addr;

	dwTickCount = GetTickCount();

	m_cs.Lock();
    vector<map<CString, HostInfo>::iterator > aDels;
	for(it=m_peerList.begin(); it!=m_peerList.end(); it++)
	{
        HostInfo& info = it->second;
		if (dwTickCount - info.dwTickCount >= 240 * 1000)
		    aDels.push_back(it);
	}
		
	bool bChange = false;
    for(int i=aDels.size()-1; i>=0; i--)
	{
		bChange = true;
		m_peerList.erase(aDels[i]);
	}
	m_cs.Unlock();
    if (bChange)
		OnUpdateUserList();

    msg.nDataLen = 0;
	msg.action = USER_QUERY_ACTIVE;

	if (m_bThreadExit)
		return;
	dwTickCount = GetTickCount();
    
	m_cs.Lock();
	for(it=m_peerList.begin(); it!=m_peerList.end(); it++)
	{
        HostInfo& info = it->second;
		if (dwTickCount - info.dwTickCount >= 60 * 1000)
		{
	    	addr.sin_family = AF_INET;
			addr.sin_port = info.nPort;
			addr.sin_addr.S_un.S_addr = info.dwIp;
			sendto(m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
		}
	}
	m_cs.Unlock();
}

void CP2pUDPClient::GetUserList()
{
	static unsigned long dwLastTick = GetTickCount();
	ULONG dwTick = GetTickCount();
    CP2PMessage msg;
	msg.action = USER_GET_USER_LIST;
	msg.nDataLen = 0;
	memcpy(&msg.hostinfo, &m_SelfInfo, sizeof(m_SelfInfo));
    sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);

	if (m_bThreadExit)
		return;
	if (dwTick - dwLastTick > 10 * 1000)
	{
		if (!m_bConnected)
		    return;
		sendto(m_socket, (char*)&msg, sizeof(msg), 0, (LPSOCKADDR)&addr, sizeof(addr));
		dwLastTick = dwTick;
	}
}

UINT CP2pUDPClient::SendText(LPVOID pParam)
{
    MsgData* pMsg = (MsgData*)pParam;
    pMsg->pClient->SendMsg(pMsg->pHost, pMsg->strMsg);
	delete pMsg;
	return 0;
}

void CP2pUDPClient::SendContent(HostInfo *pHost, CString strMsg)
{
    MsgData* pMsg = new MsgData;
	pMsg->pClient = this;
	pMsg->pHost = pHost;
	pMsg->strMsg = strMsg;
	AfxBeginThread(AFX_THREADPROC(SendText), pMsg);
}
