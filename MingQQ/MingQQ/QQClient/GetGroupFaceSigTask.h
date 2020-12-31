#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

class CGetGroupFaceSigTask : public CThreadPoolTask
{
public:
	CGetGroupFaceSigTask(void);
	~CGetGroupFaceSigTask(void);

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
