#include "StdAfx.h"
#include "ChangeStatusTask.h"

CChangeStatusTask::CChangeStatusTask(void)
{
}

CChangeStatusTask::~CChangeStatusTask(void)
{
}

int CChangeStatusTask::Run()
{
	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		m_bStop = FALSE;
		return 0;
	}

	CChangeStatusResult ChangeStatusResult;
	BOOL bRet = m_lpQQProtocol->ChangeStatus(m_HttpClient, m_nStatus, 
		WEBQQ_CLIENT_ID, m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(),
		&ChangeStatusResult);
	if (!bRet || ChangeStatusResult.m_nRetCode != 0)
		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_CHANGE_STATUS_RESULT, FALSE, 0);
	else
		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_CHANGE_STATUS_RESULT, TRUE, m_nStatus);

	m_bStop = FALSE;
	return 0;
}

int CChangeStatusTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CChangeStatusTask::TaskFinish()
{
	delete this;
}