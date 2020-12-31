#pragma once

#include "ThreadPool.h"
#include "QQUser.h"
#include "QQProtocol.h"

// 写入一条好友消息记录
void WriteBuddyMsgLog(CQQUser * lpQQUser, UINT nQQNum, LPCTSTR lpNickName, 
					  BOOL bSelf, CBuddyMessage * lpMsg);

// 写入一条群消息记录
void WriteGroupMsgLog(CQQUser * lpQQUser, UINT nGroupNum, UINT nQQNum, 
					  LPCTSTR lpNickName, CGroupMessage * lpMsg);

// 写入一条临时会话(群成员)消息记录
void WriteSessMsgLog(CQQUser * lpQQUser, UINT nQQNum, LPCTSTR lpNickName, 
					 BOOL bSelf, CSessMessage * lpMsg);

class CMsgItem
{
public:
	CMsgItem(void);
	~CMsgItem(void);

public:
	QQ_MSG_TYPE m_nType;
	void * m_lpMsg;
	UINT m_nGroupNum;
	UINT m_nQQNum;
	tstring m_strNickName;
	tstring m_strGroupSig;
};

class CSendMsgTask : public CThreadPoolTask
{
public:
	CSendMsgTask(void);
	~CSendMsgTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();
	
	BOOL AddBuddyMsg(UINT nToUin, time_t nTime, LPCTSTR lpMsg);
	BOOL AddGroupMsg(UINT nGroupId, time_t nTime, LPCTSTR lpMsg);
	BOOL AddSessMsg(UINT nGroupId, UINT nToUin, time_t nTime, LPCTSTR lpMsg);

private:
	BOOL HandleFontInfo(LPCTSTR& p, tstring& strText, std::vector<CContent *>& arrContent);
	BOOL HandleSysFaceId(LPCTSTR& p, tstring& strText, std::vector<CContent *>& arrContent);
	BOOL HandleCustomPic(LPCTSTR& p, tstring& strText, std::vector<CContent *>& arrContent);
	BOOL CreateMsgContent(LPCTSTR lpMsg, std::vector<CContent *>& arrContent);
	BOOL UploadBuddyChatPic(LPCTSTR lpszFileName, CUploadBuddyChatPicResult& result);	// 上传好友聊天图片
	BOOL UploadGroupChatPic(LPCTSTR lpszFileName, CUploadGroupChatPicResult& result);	// 上传群聊天图片
	BOOL SendBuddyMsg(CMsgItem * lpMsgItem);	// 发送好友消息
	BOOL SendGroupMsg(CMsgItem * lpMsgItem);	// 发送群消息
	BOOL SendSessMsg(CMsgItem * lpMsgItem);		// 发送群成员消息

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;

private:
	CHttpClient m_HttpClient;
	UINT m_nMsgId;
	CRITICAL_SECTION m_csItem;
	HANDLE m_hSemaphore;
	HANDLE m_hEvent;
	std::vector<CMsgItem *> m_arrItem;
	tstring m_strGFaceKey, m_strGFaceSig;
};
