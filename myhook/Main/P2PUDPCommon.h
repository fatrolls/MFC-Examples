#ifndef __P2P_UDP_COMMON_H__
#define __P2P_UDP_COMMON_H__

#include <map>
using namespace std;
#include <winsock2.h>

#define SERVER_PORT 4567
#define SERVER_IP "192.168.1.11"

typedef struct _HostInfo 
{
	char strUserName[MAX_PATH];
	ULONG dwIp;  //ipµØÖ·
	USHORT nPort;//¶Ë¿Ú
	unsigned long dwTickCount;
	bool operator==(const _HostInfo& that)
	{
		return ((strcmp(strUserName, that.strUserName) == 0) && dwIp == that.dwIp && nPort == that.nPort);
	}
} HostInfo, *PHostInfo;

class PeerList: public map<CString, HostInfo>
{
public:
	PeerList();
	~PeerList();
	bool AddAPeer(HostInfo& info);
	HostInfo* GetAPeer(sockaddr_in* addr);
	HostInfo* GetAPeer(CString strPeerName);
	void DeleteAllPeers();
	bool DeletePeer(CString strPeerName);
};

enum USER_ACTION
{
   USER_CONNECT = 1,
   USER_CONNECT_ACK,
   USER_GET_USER_LIST,
   USER_LIST_BEGIN,
   USER_LIST_IN_PROGRESS,
   USER_LIST_COMPLETE,
   USER_QUERY_ACTIVE,
   USER_QUERY_ACTIVE_ACK,
   USER_LOG_IN,
   USER_LOG_IN_2,
   USER_LOG_IN_ACK,
   USER_LOG_OUT,
   USER_LOG_OUT_ACK,
   USER_MSG,
   USER_MSG_ACK,
   USER_MAKE_HOLE
};

struct CP2PMessage
{
   USER_ACTION action;
   HostInfo hostinfo;
   int nDataLen;
   char data[1];
};

class CP2PUDPServer  
{
public:
	CP2PUDPServer();
	virtual ~CP2PUDPServer();
protected:
	virtual void QueryClientActive();
	virtual void OnUpdateUserList();
	static UINT ThreadProc(LPVOID param);
	virtual void OnUserLogout(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserLogin(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserQueryActiveAck(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserGetList(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserConnectAck(CP2PMessage* pMsg, sockaddr_in& addr);
	virtual void OnUserConnect(CP2PMessage* pMsg, sockaddr_in& addr);
	
	PeerList m_peerList;
	SOCKET m_socket;
	CEvent m_event;
	bool m_bThreadExit;
	CWinThread* m_pWorkThread;
	WSAOVERLAPPED m_overlap;
	CCriticalSection m_cs;
};


class CP2pUDPClient  
{
public:
	virtual void SendContent(HostInfo* pHost, CString strMsg);
	CP2pUDPClient(int nPort = 0);
	virtual ~CP2pUDPClient();
	
protected:
	virtual void SendMsg(HostInfo* pHost, CString strMsg);
	virtual void GetUserList();
	virtual void LogOut();
	virtual void LogIn();
	virtual void OnUserMsg(CP2PMessage* pMsg);
	virtual void OnUserMsgAck(CP2PMessage* pMsg);
	virtual void OnUserMakeHole(CP2PMessage* pMsg);
	virtual void OnUserConnectAck(CP2PMessage* pMsg);
	virtual void OnUserListUpdate();
	static UINT ThreadProc(LPVOID pParam);
	
	PeerList m_peerList;
	SOCKET m_socket;
	CEvent m_event;
	bool m_bThreadExit;
	CWinThread* m_pWorkThread;
	WSAOVERLAPPED m_overlap;
	HostInfo m_SelfInfo;
	bool m_bConnected;
	vector<HostInfo> m_aHoleClients;
	CEvent m_MakeHoleEvent;
	CCriticalSection m_cs;
	int m_nPort;
private:
	static UINT SendText(LPVOID pParam);

	struct MsgData
	{
		CP2pUDPClient* pClient;
		CString strMsg;
		HostInfo* pHost;
	};
};

#endif