// GroupTalk.h: interface for the CGroupTalk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUPTALK_H__C66FE0C6_3683_4FB9_89D4_8C1E43D5FE51__INCLUDED_)
#define AFX_GROUPTALK_H__C66FE0C6_3683_4FB9_89D4_8C1E43D5FE51__INCLUDED_

#include <winsock2.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_GROUPTALK	WM_USER + 105    
//#define BUFFER_SIZE 4096
#define GROUP_PORT  4567

const enum
{
	MT_JION = 1,	// 一个用户加入
	MT_LEAVE,		// 一个用户离开
	MT_MESG,		// 一个用户发送消息

	// 内部使用，告诉新加入的用户自己的用户信息
	MT_MINE
};

typedef struct gt_hdr
{
	u_char gt_type;			// 消息类型
	DWORD dwAddr;			// 发送此消息的用户的IP地址
	char szUser[15];		// 发送此消息的用户的用户名

	int nDataLength;		// 后面数据的长度
	char *data() { return (char*)(this + 1); }
} GT_HDR;

class CGroupTalk  
{
public:
	void SendText(CString strText, DWORD dwAddr);
	CGroupTalk(CWnd* pNotifyWnd, DWORD dwMultiAddr, DWORD dwLocalAddr = 0, int nTTL = 128);
	virtual ~CGroupTalk();
	
protected:
	CWnd* m_pNotifyWnd;
	DWORD m_dwMultiAddr;
	DWORD m_dwLocalAddr;
	int m_nTTL;
	CWinThread* m_pThread;
	CEvent m_event;
	SOCKET m_sSend;
	SOCKET m_sRead;
	BOOL m_bQuit;
	char m_szUser[MAX_PATH];
private:
	void DispatchMsg(GT_HDR* pHeader, int nLen);
	BOOL JoinGroup();
	static UINT ThreadEntry(LPVOID pParam);
	BOOL LeaveGroup();
	int Send(char* pText, int nLen, DWORD dwRemoteAddr);
};

#endif
// !defined(AFX_GROUPTALK_H__C66FE0C6_3683_4FB9_89D4_8C1E43D5FE51__INCLUDED_)
