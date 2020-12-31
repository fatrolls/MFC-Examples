// GroupTalk.cpp: implementation of the CGroupTalk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h"
#include "GroupTalk.h"
//#include <Ws2tcpip.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGroupTalk::CGroupTalk(CWnd* pNotifyWnd, DWORD dwMultiAddr, DWORD dwLocalAddr, int nTTL8)
{
    m_pNotifyWnd = pNotifyWnd;
	m_dwMultiAddr = dwMultiAddr;
	m_dwLocalAddr = dwLocalAddr;
	m_nTTL = nTTL8;
	m_bQuit = false;
	ZeroMemory(m_szUser, MAX_PATH);
	gethostname(m_szUser, MAX_PATH);
	m_sRead = m_sSend = NULL;
	m_pThread = AfxBeginThread((AFX_THREADPROC)ThreadEntry, this);
}

CGroupTalk::~CGroupTalk()
{
    m_bQuit = true;
	m_event.SetEvent();
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
}


BOOL CGroupTalk::JoinGroup()
{
   // 加入会议组
    ip_mreq mcast;
	mcast.imr_interface.S_un.S_addr = INADDR_ANY;
	mcast.imr_multiaddr.S_un.S_addr = m_dwMultiAddr;
	if (SOCKET_ERROR == setsockopt(m_sRead, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)))
		return false;
	char buf[sizeof(GT_HDR)] = { 0 };
	GT_HDR* pHeader = (GT_HDR*)buf;
	pHeader->gt_type = MT_JION;
	strncpy(pHeader->szUser, m_szUser, 15);
	Send(buf, sizeof(GT_HDR), m_dwMultiAddr);
	return true;
}

int CGroupTalk::Send(char *pText, int nLen, DWORD dwRemoteAddr)
{
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr = dwRemoteAddr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(GROUP_PORT);
    return sendto(m_sSend, pText, nLen, 0, (LPSOCKADDR)&addr, sizeof(addr));
}

BOOL CGroupTalk::LeaveGroup()
{
	// 离开会议组
	ip_mreq	mcast;
	mcast.imr_interface.S_un.S_addr = INADDR_ANY;
	mcast.imr_multiaddr.S_un.S_addr = m_dwMultiAddr;
	int nRet = ::setsockopt(m_sRead, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mcast, sizeof(mcast));

	if(nRet != SOCKET_ERROR)
	{
		// 向组中所有成员发送MT_LEAVE消息，告诉它们自己离开了
		char buf[sizeof(GT_HDR)] = { 0 };
		GT_HDR *pHeader = (GT_HDR *)buf;
		pHeader->gt_type = MT_LEAVE;
		strncpy(pHeader->szUser, m_szUser, 15);
		Send(buf, sizeof(GT_HDR), m_dwMultiAddr);
		return TRUE;
	}
	return FALSE;
}

UINT CGroupTalk::ThreadEntry(LPVOID pParam)
{
	CGroupTalk* pTalk = (CGroupTalk*)pParam;
	pTalk->m_sSend = socket(AF_INET, SOCK_DGRAM, 0);
	pTalk->m_sRead = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    BOOL bReuseAddr = TRUE;
	setsockopt(pTalk->m_sRead, SOL_SOCKET, SO_REUSEADDR, (char*)&bReuseAddr, sizeof(BOOL));
    setsockopt(pTalk->m_sSend, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&pTalk->m_nTTL, sizeof(pTalk->m_nTTL));
	setsockopt(pTalk->m_sSend, IPPROTO_IP, IP_MULTICAST_IF, (char*)pTalk->m_dwLocalAddr, sizeof(pTalk->m_dwLocalAddr));
    sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(GROUP_PORT);
	si.sin_addr.S_un.S_addr = pTalk->m_dwLocalAddr;

	if (SOCKET_ERROR == bind(pTalk->m_sRead, (LPSOCKADDR)&si, sizeof(si)))
	{
		closesocket(pTalk->m_sRead);
		closesocket(pTalk->m_sSend);
		pTalk->m_pNotifyWnd->SendMessage(WM_GROUPTALK, -1, (long)"bind failed\n");
		return -1;
	}
	// 加入多播组
	if(!pTalk->JoinGroup())
	{
		::closesocket(pTalk->m_sSend);
		::closesocket(pTalk->m_sRead);
		pTalk->m_pNotifyWnd->SendMessage(WM_GROUPTALK, -1, (long)"JoinGroup failed! \n");
		return -1;
	}

	WSAOVERLAPPED ol = { 0 };
	ol.hEvent = pTalk->m_event.m_hObject;
	WSABUF buf;
	buf.buf = new char[BUFFER_SIZE];
	buf.len = BUFFER_SIZE;

	while(true)
	{
        DWORD dwRecv;
		DWORD dwFlags = 0;
		sockaddr_in saFrom;
		int nFromLen = sizeof(saFrom);
		int nRet = WSARecvFrom(pTalk->m_sRead, &buf, 1, &dwRecv, &dwFlags, (LPSOCKADDR)&saFrom, &nFromLen, &ol, NULL);
		if (nRet == SOCKET_ERROR)
		{
			if (WSA_IO_PENDING != WSAGetLastError())
			{
				pTalk->LeaveGroup();
                ::closesocket(pTalk->m_sSend);
				::closesocket(pTalk->m_sRead);
				pTalk->m_pNotifyWnd->SendMessage(WM_GROUPTALK, -1, (long)"PostRecv failed! \n");
				delete [] buf.buf;
				return -1;
			}
		}

		WSAWaitForMultipleEvents(1, &pTalk->m_event.m_hObject, TRUE, WSA_INFINITE, FALSE);
		if (pTalk->m_bQuit)
		{
			pTalk->LeaveGroup();
			::closesocket(pTalk->m_sSend);
			::closesocket(pTalk->m_sRead);
			delete [] buf.buf;
			return -1;
		}
		BOOL b = WSAGetOverlappedResult(pTalk->m_sRead, &ol, &dwRecv, FALSE, &dwFlags);
		if (b && dwRecv >= sizeof(GT_HDR))
		{
			GT_HDR* pHeader = (GT_HDR*)buf.buf;
			pHeader->dwAddr = saFrom.sin_addr.S_un.S_addr;
			pTalk->DispatchMsg(pHeader, dwRecv);
		}
	}
    delete [] buf.buf;
	return 0;
}

void CGroupTalk::DispatchMsg(GT_HDR *pHeader, int nLen)
{
    if(pHeader->gt_type == MT_JION)	// 新用户加入
	{	
		// 向新加入用户发送自己的用户信息
		char buff[sizeof(GT_HDR)] = { 0 };
		GT_HDR *pSend = (GT_HDR*)buff;
		strncpy(pSend->szUser, m_szUser, 15);	
		pSend->gt_type = MT_MINE;
		pSend->nDataLength = 0;
		Send(buff, sizeof(GT_HDR), pHeader->dwAddr);
	}
	else if(pHeader->gt_type == MT_MINE)
	{	
		// 是否来自自己，如果是，则不处理
		if(strcmp(pHeader->szUser, m_szUser) == 0)
			return;
		// 为简单起见，把在线用户当成新加入用户处理
		pHeader->gt_type = MT_JION;
	}

	// 通知主窗口处理
	m_pNotifyWnd->SendMessage(WM_GROUPTALK, 0, (LPARAM)pHeader);
}

void CGroupTalk::SendText(CString strText, DWORD dwAddr)
{
	int nSize = sizeof(GT_HDR) + 1 + strText.GetLength();
    char* buf = new char[nSize];
	ZeroMemory(buf, nSize);
	GT_HDR* pHeader = (GT_HDR*)buf;
	pHeader->gt_type = MT_MESG;
	strcpy(pHeader->szUser, m_szUser);
	strncpy(pHeader->data(), strText.GetBuffer(strText.GetLength()), strText.GetLength());
	strText.ReleaseBuffer();
	pHeader->nDataLength = strText.GetLength();
	Send(buf, nSize, dwAddr);
	delete [] buf;
}
