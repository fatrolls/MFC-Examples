#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

class CChangeStatusTask : public CThreadPoolTask
{
public:
	CChangeStatusTask(void);
	~CChangeStatusTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	QQ_STATUS m_nStatus;

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
