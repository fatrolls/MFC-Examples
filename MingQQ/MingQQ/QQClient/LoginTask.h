#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"
#include "SendMsgTask.h"
#include "RecvMsgTask.h"
#include "PollTask.h"
#include "QQNumTask.h"
#include "QQSignTask.h"
#include "GetHeadPicTask.h"

class CLoginTask : public CThreadPoolTask
{
public:
	CLoginTask(void);
	~CLoginTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

private:
	CBuddyInfoResult * GetUserInfo();			// 获取用户信息
	CGetSignResult * GetUserSign();				// 获取用户签名
	CBuddyListResult * GetBuddyList();			// 获取好友列表
	CGroupListResult * GetGroupList();			// 获取群列表
	CRecentListResult * GetRecentList();		// 获取最近联系人列表
	BOOL StartSendMsgTask();					// 启动发送消息任务
	BOOL StartRecvMsgTask();					// 启动接收消息任务
	BOOL StartPollTask();						// 启动轮询任务
	BOOL StartGetBuddyNumberTask(CBuddyListResult * lpBuddyListResult, 
		CGroupListResult * lpGroupListResult);	// 启动获取好友QQ号码任务
	BOOL StartGetBuddySignTask(CBuddyListResult * lpBuddyListResult);	// 启动获取好友QQ签名任务
	BOOL StartGetHeadPicTask(CBuddyListResult * lpBuddyListResult, 
		CGroupListResult * lpGroupListResult);	// 启动获取头像图片任务

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	CThreadPool * m_lpThreadPool;
	CSendMsgTask * m_lpSendMsgTask;
	CRecvMsgTask * m_lpRecvMsgTask;
	CPollTask * m_lpPollTask;
	
private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
