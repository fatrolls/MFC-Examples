#pragma once

#include "ThreadPool.h"
#include "QQUser.h"
#include "QQProtocol.h"
#include "RecvMsgTask.h"

class CPollTask : public CThreadPoolTask
{
public:
	CPollTask(void);
	~CPollTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();
	
public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	CRecvMsgTask * m_lpRecvMsgTask;

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
