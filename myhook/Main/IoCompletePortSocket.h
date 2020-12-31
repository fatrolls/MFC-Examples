// IoCompletePortSocket.h: interface for the CIoCompletePortSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCOMPLETEPORTSOCKET_H__2AA624C4_CFBB_4A50_926E_4485920D698B__INCLUDED_)
#define AFX_IOCOMPLETEPORTSOCKET_H__2AA624C4_CFBB_4A50_926E_4485920D698B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <afxmt.h>
#include <winsock2.h>

using namespace std;

//#define BUFFER_SIZE 1024
#define SERVER_PORT 1027
#define SERVER_ADDRESS "127.0.0.1"

struct IpAddress
{
   SOCKET s;
   sockaddr_in addr;
};

typedef struct _IO_DATA			// per-I/O数据
{
	OVERLAPPED ol;			// 重叠结构
	char buf[BUFFER_SIZE];	// 数据缓冲区
	int nOperationType;		// 操作类型
#define OP_READ   1
#define OP_WRITE  2
#define OP_ACCEPT 3

} IoData, *PIoData;

enum CMD
{
   CMD_JOIN, 
   CMD_LEAVE, 
   CMD_SET_ALL_ONLINE_USERS, 
   CMD_ADD_USER,
   CMD_DELETE_USER, 
   CMD_USER_MSG
};

class CIoCompletePortSocket  
{
public:
	void SendMsg(CString strSendMsg, IpAddress* pAddr);
	CIoCompletePortSocket(CWnd* pNotifyWnd);
	virtual ~CIoCompletePortSocket();
private:
	void InitializeUserList(char* pBuff, int nLen);
	void AddUser(char* pBuf);
	void DeleteUser(char* pBuf, IpAddress& selfaddr);
	void ShowUserMsg(char* pBuf);
    static UINT ThreadProc(LPVOID pParam);
	char* CommandToString(CMD cmd, int &nSize);
	bool ParseCommand(CMD cmd, char* szText, void** pData = NULL);

	HANDLE m_hCompletePort;
	SOCKET m_sSocket;
	CEvent m_ReadEvent;
    CEvent m_WriteEvent;
	bool   m_bExit;
	CWinThread* m_pThread;
	CWnd* m_pNotifyWnd;
	map<SOCKET, IpAddress> m_aUsers;
	IoData readdata;
	IoData writedata;
	IpAddress address;
};

#endif // !defined(AFX_IOCOMPLETEPORTSOCKET_H__2AA624C4_CFBB_4A50_926E_4485920D698B__INCLUDED_)
