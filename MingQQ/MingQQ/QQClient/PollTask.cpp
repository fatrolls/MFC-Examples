#include "StdAfx.h"
#include "PollTask.h"

CPollTask::CPollTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_lpRecvMsgTask = NULL;
	m_bStop = FALSE;
}

CPollTask::~CPollTask(void)
{
}

int CPollTask::Run()
{
	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol || NULL == m_lpRecvMsgTask)
	{
		m_bStop = FALSE;
		return 0;
	}

	while (1)
	{
		if (m_bStop)
			break;

		CBuffer * lpMsgData = new CBuffer;
		if (NULL == lpMsgData)
			continue;

		BOOL bRet = m_lpQQProtocol->Poll(m_HttpClient, WEBQQ_CLIENT_ID, 
			m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), lpMsgData);
		if (!bRet || lpMsgData->GetData() == NULL || lpMsgData->GetSize() <= 0)
		{
			delete lpMsgData;
			::OutputDebugStringA("poll message error!\r\n");
			continue;
		}

		m_lpRecvMsgTask->AddMsgData(lpMsgData);
	}

	m_bStop = FALSE;

	return 0;
}

int CPollTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CPollTask::TaskFinish()
{
}