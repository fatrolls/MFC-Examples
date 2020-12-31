#pragma once

#include "ThreadPool.h"
#include "QQUser.h"
#include "QQProtocol.h"
#include "GetChatPicTask.h"

// 写入一条好友消息记录
void WriteBuddyMsgLog(CQQUser * lpQQUser, UINT nQQNum, 
					  LPCTSTR lpNickName, BOOL bSelf, CBuddyMessage * lpMsg);

// 写入一条群消息记录
void WriteGroupMsgLog(CQQUser * lpQQUser, UINT nGroupNum, UINT nQQNum, 
					  LPCTSTR lpNickName, CGroupMessage * lpMsg);

// 写入一条临时会话(群成员)消息记录
void WriteSessMsgLog(CQQUser * lpQQUser, UINT nQQNum, 
					 LPCTSTR lpNickName, BOOL bSelf, CSessMessage * lpMsg);

class CGMemberMapKey
{
public:
	CGMemberMapKey(void):m_nGroupCode(0), m_nQQUin(0){}
	~CGMemberMapKey(void){}

public:
	bool operator < (const CGMemberMapKey& rhs) const
	{
		if(m_nGroupCode < rhs.m_nGroupCode) return true;
		if(m_nGroupCode > rhs.m_nGroupCode) return false;
		return  m_nQQUin < rhs.m_nQQUin;
	}

public:
	UINT m_nGroupCode;
	UINT m_nQQUin;
};

class CRecvMsg
{
public:
	CRecvMsg(void);
	~CRecvMsg(void);

public:
	UINT GetMsgId();
	UINT GetMsgId2();
	UINT GetTime();

public:
	QQ_MSG_TYPE m_nType;
	void * m_lpMsg;
};

struct RMT_BUDDY_DATA
{
	UINT nQQNum;
	TCHAR szNickName[32];
};

struct RMT_GROUP_DATA
{
	BOOL bHasGroupInfo;
	UINT nGroupNum;
};

struct RMT_GMEMBER_REQ
{
	UINT nGroupCode;
	UINT nQQUin;
};

class CRecvMsgTask : public CThreadPoolTask
{
public:
	CRecvMsgTask(void);
	~CRecvMsgTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

	BOOL AddMsgData(CBuffer * lpMsgData);
	void DelAllMsgData();

private:
	BOOL HandleMsg(CBuffer * lpMsg);

	BOOL ParseMsg(CBuffer * lpMsgData, std::vector<CRecvMsg *>& arrMsg);
	BOOL ParseMsg(Json::Value& JsonValue, CRecvMsg& msg);

	BOOL IsMsgRepeat(std::vector<CRecvMsg *>& arrMsg, CRecvMsg * lpMsg);	
	void SortMsgByTime(std::vector<CRecvMsg *>& arrMsg);
	
	BOOL HandleBuddyMsg(CRecvMsg * lpRecvMsg);
	BOOL HandleGroupMsg(CRecvMsg * lpRecvMsg);
	BOOL HandleSessMsg(CRecvMsg * lpRecvMsg);
	BOOL HandleStatusChangeMsg(CRecvMsg * lpRecvMsg);
	BOOL HandleKickMsg(CRecvMsg * lpRecvMsg);
	BOOL HandleSysGroupMsg(CRecvMsg * lpRecvMsg);

	RMT_BUDDY_DATA * GetBuddyData(UINT nQQUin);
	RMT_GROUP_DATA * GetGroupData(UINT nGroupCode);
	RMT_BUDDY_DATA * GetGMemberData(UINT nGroupCode, UINT nQQUin);
	UINT GroupId2Code(UINT nGroupId);

	BOOL IsNeedDownloadPic(std::vector<CContent *>& arrContent);
	BOOL StartGetChatPicTask(GETCHATPIC_OP_TYPE nType, void * lpMsg);

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	CThreadPool * m_lpThreadPool;

private:
	HANDLE m_hEvent;
	CHttpClient m_HttpClient;
	CRITICAL_SECTION m_csItem;
	HANDLE m_hSemaphore;
	std::vector<CBuffer *> m_arrItem;
	std::map<UINT,RMT_BUDDY_DATA *> m_mapBuddyData;
	std::map<UINT,RMT_GROUP_DATA *> m_mapGroupData;
	std::map<UINT,UINT> m_mapGroupId2Code;
	std::map<CGMemberMapKey, RMT_BUDDY_DATA *> m_mapGMemberData;
	UINT m_nPreMsgId, m_nPreMsgId2;
};