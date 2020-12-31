#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

enum INFO_OP_TYPE			// 操作类型
{
	OP_TYPE_GETBUDDYINFO,	// 获取好友信息
	OP_TYPE_GETGMEMBERINFO,	// 获取群成员信息
	OP_TYPE_GETGROUPINFO,	// 获取群信息
	OP_TYPE_SETBUDDYINFO	// 设置好友信息
};

class CInfoTask : public CThreadPoolTask
{
public:
	CInfoTask(void);
	~CInfoTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	INFO_OP_TYPE m_nType;	// 操作类型
	UINT m_nGroupCode;		// 群代码
	UINT m_nQQUin;			// 好友Uin或者群成员Uin

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
