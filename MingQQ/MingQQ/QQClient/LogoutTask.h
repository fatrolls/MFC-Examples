#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

class CLogoutTask : public CThreadPoolTask
{
public:
	CLogoutTask(void);
	~CLogoutTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
