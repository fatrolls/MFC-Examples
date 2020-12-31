// P2pUDPUtility.cpp: implementation of the CMyP2pUDPServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h"
#include "P2PUdpDlg.h"
#include "P2pUDPUtility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyP2pUDPServer::CMyP2pUDPServer(CP2PUdpServerDlg* pNotifyWnd)
{
    m_pNotifyWnd = pNotifyWnd;
}

CMyP2pUDPServer::~CMyP2pUDPServer()
{

}

void CMyP2pUDPServer::OnUserLogout(CP2PMessage* pMsg, sockaddr_in& addr)
{
	CString strKey;
	in_addr addr1;
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	CString strIP = inet_ntoa(addr1);
	strKey.Format("%s %s:%d", pMsg->hostinfo.strUserName, strIP, ntohs(pMsg->hostinfo.nPort));
	int index = m_pNotifyWnd->m_lstUser.FindStringExact(-1, strKey);
	if (index != LB_ERR)
	{
		m_DlgCs.Lock();
		m_pNotifyWnd->m_lstUser.DeleteString(index);
		m_pNotifyWnd->m_lstInfo.AddString(strKey + " Log out");
		m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
		m_DlgCs.Unlock();
	}
}

void CMyP2pUDPServer::OnUserLogin(CP2PMessage* pMsg, sockaddr_in& addr)
{
	CString strKey;
	in_addr addr1;
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	CString strIP = inet_ntoa(addr1);
	strKey.Format("%s %s:%d", pMsg->hostinfo.strUserName, strIP, ntohs(pMsg->hostinfo.nPort));
	m_DlgCs.Lock();
    m_pNotifyWnd->m_lstUser.AddString(strKey);
	m_pNotifyWnd->m_lstInfo.AddString(strKey + " Log in");
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

void CMyP2pUDPServer::OnUpdateUserList()
{	
	m_pNotifyWnd->m_lstUser.LockWindowUpdate();
	m_pNotifyWnd->m_lstUser.ResetContent();

	CString strKey;
	map<CString, HostInfo>::iterator it;
	for(it=m_peerList.begin(); it!=m_peerList.end(); it++)
	{
		in_addr addr1;
	    addr1.S_un.S_addr = it->second.dwIp;
	    CString strIP = inet_ntoa(addr1);
	    strKey.Format("%s %s:%d", it->second.strUserName, strIP, ntohs(it->second.nPort));
		m_DlgCs.Lock();
		m_pNotifyWnd->m_lstUser.AddString(strKey);
		m_DlgCs.Unlock();
	}
	m_pNotifyWnd->m_lstUser.UnlockWindowUpdate();
}

void CMyP2pUDPServer::OnUserQueryActiveAck(CP2PMessage* pMsg, sockaddr_in& addr)
{
	CString strKey;
	in_addr addr1;
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	CString strIP = inet_ntoa(addr1);
	strKey.Format("%s %s:%d", pMsg->hostinfo.strUserName, strIP, ntohs(pMsg->hostinfo.nPort));
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strKey + "应答");
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

void CMyP2pUDPServer::OnUserGetList(CP2PMessage* pMsg, sockaddr_in& addr)
{
	CString strKey;
	in_addr addr1;
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	CString strIP = inet_ntoa(addr1);
	strKey.Format("%s %s:%d", pMsg->hostinfo.strUserName, strIP, ntohs(pMsg->hostinfo.nPort));
	CString strLog = strKey + "请求获得用户列表";
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strLog);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

void CMyP2pUDPServer::OnUserConnectAck(CP2PMessage* pMsg, sockaddr_in& addr)
{
	CString strDest, strHost;
	in_addr addr1;
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	CString strIP = inet_ntoa(addr1);
	strDest.Format("%s %s:%d", pMsg->hostinfo.strUserName, strIP, ntohs(pMsg->hostinfo.nPort));
	HostInfo* pHost = m_peerList.GetAPeer(&addr);
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	strIP = inet_ntoa(addr1);
	strHost.Format("%s %s:%d", pHost->strUserName, strIP, ntohs(pHost->nPort));
	CString strLog = "[" + strHost + "]对[" + strDest + "]请求打洞的响应";
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strLog);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

void CMyP2pUDPServer::OnUserConnect(CP2PMessage* pMsg, sockaddr_in& addr)
{
    CString strDest, strHost;
	in_addr addr1;
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	CString strIP = inet_ntoa(addr1);
	strDest.Format("%s %s:%d", pMsg->hostinfo.strUserName, strIP, ntohs(pMsg->hostinfo.nPort));
	HostInfo* pHost = m_peerList.GetAPeer(&addr);
	addr1.S_un.S_addr = pMsg->hostinfo.dwIp;
	strIP = inet_ntoa(addr1);
	strHost.Format("%s %s:%d", pHost->strUserName, strIP, ntohs(pHost->nPort));
	CString strLog = "[" + strHost + "]请求[" + strDest + "]打洞";
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strLog);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

//////////////////////////////////////////////////////////////////////
// CMyP2pUDPClient Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyP2pUDPClient::CMyP2pUDPClient(CP2PUdpClientDlg* pNotifyWnd, USHORT nPort)
: CP2pUDPClient(nPort)
{
    m_pNotifyWnd = pNotifyWnd;
}

CMyP2pUDPClient::~CMyP2pUDPClient()
{

}

void CMyP2pUDPClient::OnUserConnectAck(CP2PMessage *pMsg)
{
    CString strKey;
	strKey.Format("[%s:%s:%d]向本机打洞成功", pMsg->hostinfo.strUserName, inet_ntoa(*((in_addr*)&pMsg->hostinfo.dwIp)),
		          htons(pMsg->hostinfo.nPort));
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strKey);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

void CMyP2pUDPClient::OnUserMakeHole(CP2PMessage *pMsg)
{
    CString strKey;
	strKey.Format("收到[%s:%s:%d]向本机打洞的数据", pMsg->hostinfo.strUserName, inet_ntoa(*((in_addr*)&pMsg->hostinfo.dwIp)),
		          htons(pMsg->hostinfo.nPort));
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strKey);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}

void CMyP2pUDPClient::OnUserMsgAck(CP2PMessage *pMsg)
{
    CString strKey;
	strKey.Format("[%s:%s:%d]已经向本机打洞", pMsg->hostinfo.strUserName, inet_ntoa(*((in_addr*)&pMsg->hostinfo.dwIp)),
		          htons(pMsg->hostinfo.nPort));
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstInfo.AddString(strKey);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstInfo);
	m_DlgCs.Unlock();
}


void CMyP2pUDPClient::OnUserMsg(CP2PMessage *pMsg)
{
    CString strKey;
	strKey.Format("[%s:%s:%d]说:%s", pMsg->hostinfo.strUserName, inet_ntoa(*((in_addr*)&pMsg->hostinfo.dwIp)),
		          htons(pMsg->hostinfo.nPort), pMsg->data);
	m_DlgCs.Lock();
	m_pNotifyWnd->m_lstContent.AddString(strKey);
	m_pNotifyWnd->SetListBoxPos(m_pNotifyWnd->m_lstContent);
	m_DlgCs.Unlock();
}

void CMyP2pUDPClient::OnUserListUpdate()
{
	CP2pUDPClient::OnUserListUpdate();
    m_DlgCs.Lock();
	//m_pNotifyWnd->m_lstUser.LockWindowUpdate();
	m_pNotifyWnd->m_lstUser.ResetContent();
	CString strKey;

	for(map<CString, HostInfo>::iterator it=m_peerList.begin(); it!=m_peerList.end(); it++)
	{
        strKey.Format("%s %s:%d", it->second.strUserName, inet_ntoa(*((in_addr*)&it->second.dwIp)), htons(it->second.nPort));
		m_pNotifyWnd->m_lstUser.AddString(strKey);
		m_pNotifyWnd->m_lstUser.SetItemData(m_pNotifyWnd->m_lstUser.GetCount()-1, (DWORD)&it->second);
	}
	//m_pNotifyWnd->m_lstUser.UnlockWindowUpdate();
	m_DlgCs.Unlock();
}