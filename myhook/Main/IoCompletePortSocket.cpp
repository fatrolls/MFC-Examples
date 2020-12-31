// IoCompletePortSocket.cpp: implementation of the CIoCompletePortSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h"
#include <winsock2.h>
#include "IoCompletePortSocket.h"
#include "IoCompletePortTalkDlg.h"
#include "ProtocolTypes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoCompletePortSocket::CIoCompletePortSocket(CWnd* pNotifyWnd)
{
	m_bExit = false;
	m_pNotifyWnd = pNotifyWnd;
	m_pThread = AfxBeginThread(AFX_THREADPROC(ThreadProc), this);
}

CIoCompletePortSocket::~CIoCompletePortSocket()
{
    m_bExit = true;
	m_ReadEvent.SetEvent();
	m_WriteEvent.SetEvent();
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
}

char* CIoCompletePortSocket::CommandToString(CMD cmd, int &nSize)
{
    char* pBuf;
   
	switch(cmd)
	{
	case CMD_JOIN:
		nSize = 13;
		pBuf = new char[nSize];
		memset(pBuf, 0, nSize);
		memcpy(pBuf, "command_join", 12);
		break;
	case CMD_LEAVE:
		nSize = 14;
		pBuf = new char[nSize];
		memset(pBuf, 0, nSize);
		memcpy(pBuf, "command_leave", 13);
		break;
	case CMD_SET_ALL_ONLINE_USERS:
		nSize = 28;
		pBuf = new char[nSize];
		memset(pBuf, 0, nSize);
		memcpy(pBuf, "command_set_all_online_user", 27);
		break;
	case CMD_ADD_USER:
		nSize = 17;
		pBuf = new char[nSize];
		memset(pBuf, 0, nSize);
		memcpy(pBuf, "command_add_user", 16);
		break;
	case CMD_DELETE_USER:
		nSize = 20;
		pBuf = new char[nSize];
		memset(pBuf, 0, nSize);
		memcpy(pBuf, "command_delete_user", 19);
		break;
	case CMD_USER_MSG:
        nSize = 21;
		pBuf = new char[nSize];
		memset(pBuf, 0, nSize);
		memcpy(pBuf, "command_user_message", 20);
		break;
	default:
		nSize =0;
		pBuf = NULL;
	}
	return pBuf;
}

bool CIoCompletePortSocket::ParseCommand(CMD cmd, char* szText, void** pData)
{
	int nSize;
	char *pCmd = CommandToString(cmd, nSize);
    if (memcmp(szText, pCmd, nSize) == 0)
	{
		delete [] pCmd;
		if (pData != NULL)
			*pData = &szText[nSize];
		return true;
	}
	else
	{
		delete [] pCmd;
		return false;
	}
}

UINT CIoCompletePortSocket::ThreadProc(LPVOID pParam)
{
    CIoCompletePortSocket* pThis = (CIoCompletePortSocket*)pParam;
    WSABUF buf;
	DWORD dwRecv;
	DWORD dwFlags = 0;
	WSABUF buf2;
	int nSize;
	DWORD dwSend;
	MySockaddr_In addr(SERVER_PORT, SERVER_ADDRESS);
	char* pCmd;

	pThis->m_hCompletePort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	pThis->m_sSocket = socket(AF_INET, SOCK_STREAM, 0);
	ASSERT(pThis->m_sSocket != INVALID_SOCKET);
		
	if (SOCKET_ERROR == connect(pThis->m_sSocket, (LPSOCKADDR)&addr, sizeof(addr)))	
	{
		CloseHandle(pThis->m_hCompletePort);
		closesocket(pThis->m_sSocket);
		return 0;
	}
	
	pThis->address.s = pThis->m_sSocket;
	int len = sizeof(sockaddr_in);
	getsockname(pThis->m_sSocket, (LPSOCKADDR)&pThis->address.addr, &len);
    CreateIoCompletionPort((HANDLE)pThis->m_sSocket, pThis->m_hCompletePort, (DWORD)&pThis->address, 0);
    
	//发出读操作
	pThis->readdata.nOperationType = OP_READ;
	pThis->readdata.ol.hEvent = pThis->m_ReadEvent.m_hObject;
	buf.buf = pThis->readdata.buf;
	buf.len = BUFFER_SIZE;
	ZeroMemory(buf.buf, BUFFER_SIZE);
	WSARecv(pThis->m_sSocket, &buf, 1, &dwRecv, &dwFlags, &pThis->readdata.ol, NULL);
    
	//发出写操作
	pThis->writedata.nOperationType = OP_WRITE;
	pThis->writedata.ol.hEvent = pThis->m_WriteEvent.m_hObject;
    buf2.buf = pThis->writedata.buf;
	buf2.len = BUFFER_SIZE;
	ZeroMemory(buf2.buf, BUFFER_SIZE);
	pCmd = pThis->CommandToString(CMD_JOIN, nSize);
	memcpy(buf2.buf, pCmd, nSize);
	delete [] pCmd;
	WSASend(pThis->m_sSocket, &buf2, 1, &dwSend, 0, &pThis->writedata.ol, NULL);
   
	while(!pThis->m_bExit)
	{
		IpAddress* pIpAddress;
		PIoData pIoData;
		DWORD dwTrans;
		BOOL bOK = ::GetQueuedCompletionStatus(pThis->m_hCompletePort, &dwTrans, (LPDWORD)&pIpAddress, (LPOVERLAPPED*)&pIoData, WSA_INFINITE);
		if (!bOK || (dwTrans == 0 && (pIoData->nOperationType == OP_READ || pIoData->nOperationType == OP_WRITE)))
		    break;

		switch(pIoData->nOperationType)
		{
		case OP_READ:
			{
				pIoData->buf[dwTrans] = 0;
                char* pBuf;
				//如果是连接后接收所有用户列表的命令
				if (pThis->ParseCommand(CMD_SET_ALL_ONLINE_USERS, pIoData->buf, (void**)&pBuf))
				{
                    pThis->InitializeUserList(pBuf, dwTrans - (pBuf - pIoData->buf));
				}
				//如果是一个新用户加入， 更新用户列表
				else if (pThis->ParseCommand(CMD_ADD_USER, pIoData->buf, (void**)&pBuf))
				{
                    pThis->AddUser(pBuf);
				}
				//如果是删除用户
                else if (pThis->ParseCommand(CMD_DELETE_USER, pIoData->buf, (void**)&pBuf))
				{
                    pThis->DeleteUser(pBuf, pThis->address);
				}
				//如果是用户消息
				else if (pThis->ParseCommand(CMD_USER_MSG, pIoData->buf, (void**)&pBuf))
				{
                    pThis->ShowUserMsg(pBuf);
				}
				//再次投递接收数据的请求
                WSABUF bufRead;
				bufRead.buf = pIoData->buf;
				bufRead.len = BUFFER_SIZE;
				DWORD dwRecv;
				DWORD dwFlags = 0;
				::WSARecv(pThis->m_sSocket, &bufRead, 1, &dwRecv, &dwFlags, &pIoData->ol, NULL);
			}
			break;
		case OP_WRITE:
			{
                int ikl = 1;
			}
			break;
		}	
	}

	CloseHandle(pThis->m_hCompletePort);
	closesocket(pThis->m_sSocket);
    return 0L;
}

void CIoCompletePortSocket::ShowUserMsg(char *pBuf)
{
    IpAddress* pRemoteAddr = (IpAddress*)pBuf;
	char* pMsg = pBuf + 2 * (sizeof(IpAddress) + 1);
	CString strMsg;
	strMsg.Format("『%s:%d说』:%s", inet_ntoa(pRemoteAddr->addr.sin_addr), ntohs(pRemoteAddr->addr.sin_port), pMsg);
    CIoCompletePortTalkDlg* pDlg = (CIoCompletePortTalkDlg*)m_pNotifyWnd;
	pDlg->m_lstRecord.AddString(strMsg);
}

void CIoCompletePortSocket::DeleteUser(char *pBuf, IpAddress& selfaddr)
{
    IpAddress* pAddr = (IpAddress*)pBuf;
	CString strAddr = inet_ntoa(pAddr->addr.sin_addr);
	int nPort = ntohs(pAddr->addr.sin_port);
	CString selfIP = inet_ntoa(selfaddr.addr.sin_addr);
	int selfport = ntohs(selfaddr.addr.sin_port);
	CIoCompletePortTalkDlg* pDlg = (CIoCompletePortTalkDlg*)m_pNotifyWnd;
	//如果是自己
	if (strAddr == selfIP && nPort == selfport)
    {
		m_bExit = true;
		m_ReadEvent.SetEvent();
		m_WriteEvent.SetEvent();
		pDlg->m_lstUsers.ResetContent();
		m_aUsers.clear();
	}
	else
	{
        CString strKey;
		strKey.Format("%s:%d", strAddr, nPort);
		int iSel = pDlg->m_lstUsers.FindStringExact(-1, strKey);
		if (iSel != LB_ERR)
		{
			pDlg->m_lstUsers.DeleteString(iSel);
            map<SOCKET, IpAddress>::iterator it = m_aUsers.find(pAddr->s);
			if (it != m_aUsers.end())
				m_aUsers.erase(it);
		}
	}
}

void CIoCompletePortSocket::AddUser(char *pBuf)
{
    IpAddress* pAddr = (IpAddress*)pBuf;
	CString strAddr = inet_ntoa(pAddr->addr.sin_addr);
	int nPort = ntohs(pAddr->addr.sin_port);
	CIoCompletePortTalkDlg* pDlg = (CIoCompletePortTalkDlg*)m_pNotifyWnd;
	CString strKey;
	strKey.Format("%s:%d", strAddr, nPort);
	pDlg->m_lstUsers.AddString(strKey);
	IpAddress addr;
	memcpy(&addr, pAddr, sizeof(IpAddress));
	m_aUsers.insert(make_pair(pAddr->s, addr));
	pDlg->m_lstUsers.SetItemData(pDlg->m_lstUsers.GetCount()-1, (DWORD)&m_aUsers.find(pAddr->s)->second);
}

void CIoCompletePortSocket::InitializeUserList(char *pBuf, int nLen)
{
    CIoCompletePortTalkDlg* pDlg = (CIoCompletePortTalkDlg*)m_pNotifyWnd;
	pDlg->m_lstUsers.ResetContent();
	m_aUsers.clear();
	int iCount = nLen / (sizeof(IpAddress) + 1);

	for(int i=0; i<iCount; i++)
	{
		IpAddress* pAddr = (IpAddress*)(pBuf + (sizeof(IpAddress) + 1) * i);
        CString strAddr = inet_ntoa(pAddr->addr.sin_addr);
		int nPort = ntohs(pAddr->addr.sin_port);
		CString strKey;
		strKey.Format("%s:%d", strAddr, nPort);
		pDlg->m_lstUsers.AddString(strKey);
		IpAddress addr;
		memcpy(&addr, pAddr, sizeof(IpAddress));
		m_aUsers.insert(make_pair(pAddr->s, addr));
		pDlg->m_lstUsers.SetItemData(pDlg->m_lstUsers.GetCount()-1, (DWORD)&m_aUsers.find(pAddr->s)->second);
	}
}

void CIoCompletePortSocket::SendMsg(CString strSendMsg, IpAddress* pAddr)
{
    //发出写操作
	//writedata.nOperationType = OP_WRITE;
	//writedata.ol.hEvent = pThis->m_WriteEvent.m_hObject;
	WSABUF buf;
    buf.buf = writedata.buf;
	buf.len = BUFFER_SIZE;
	ZeroMemory(buf.buf, BUFFER_SIZE);
	int nSize;
	char* pCmd = CommandToString(CMD_USER_MSG, nSize);
	memcpy(buf.buf, pCmd, nSize);
	delete [] pCmd;
	buf.len = nSize + 2 * (1 + sizeof(IpAddress)) + strSendMsg.GetLength();
	//拷贝源地址
	memcpy(buf.buf+nSize, (char*)&address, sizeof(IpAddress));
    //拷贝目的地址
	memcpy(buf.buf+nSize+sizeof(IpAddress)+1, (char*)pAddr, sizeof(IpAddress));
	//拷贝数据
	memcpy(buf.buf+nSize+2*(sizeof(IpAddress)+1), strSendMsg.GetBuffer(strSendMsg.GetLength()), strSendMsg.GetLength());
	DWORD dwSend;
	WSASend(m_sSocket, &buf, 1, &dwSend, 0, &writedata.ol, NULL);
}
