// P2pUDPUtility.h: interface for the CMyP2pUDPServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P2PUDPUTILITY_H__E843B8D3_A6B2_40EA_BE04_59841DD8B811__INCLUDED_)
#define AFX_P2PUDPUTILITY_H__E843B8D3_A6B2_40EA_BE04_59841DD8B811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "P2PUDPCommon.h"

class CP2PUdpServerDlg;

class CMyP2pUDPServer : public CP2PUDPServer  
{
public:
	CMyP2pUDPServer(CP2PUdpServerDlg* pNotifyWnd);
	virtual ~CMyP2pUDPServer();
protected:
	virtual void OnUserLogout(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserLogin(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserQueryActiveAck(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserGetList(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserConnectAck(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserConnect(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void CMyP2pUDPServer::OnUpdateUserList();

	CP2PUdpServerDlg* m_pNotifyWnd;
	CCriticalSection m_DlgCs;
};

class CP2PUdpClientDlg;

class CMyP2pUDPClient : public CP2pUDPClient  
{
public:
	CMyP2pUDPClient(CP2PUdpClientDlg* pNotifyWnd, USHORT nPort = 0);
	virtual ~CMyP2pUDPClient();
protected:
	virtual void OnUserMsg(CP2PMessage* pMsg);
	virtual void OnUserMsgAck(CP2PMessage* pMsg);
	virtual void OnUserMakeHole(CP2PMessage* pMsg);
	virtual void OnUserConnectAck(CP2PMessage* pMsg);
	virtual void OnUserListUpdate();

	CP2PUdpClientDlg*  m_pNotifyWnd;
	CCriticalSection m_DlgCs;
};

#endif // !defined(AFX_P2PUDPUTILITY_H__E843B8D3_A6B2_40EA_BE04_59841DD8B811__INCLUDED_)
