#include "StdAfx.h"
#include "LogoutTask.h"

CLogoutTask::CLogoutTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_bStop = FALSE;
}

CLogoutTask::~CLogoutTask(void)
{
}

int CLogoutTask::Run()
{
	BOOL bRet;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		m_bStop = FALSE;
		return 0;
	}

	CLogoutResult LogoutResult;
	bRet = m_lpQQProtocol->Logout(m_HttpClient, WEBQQ_CLIENT_ID,
		m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), &LogoutResult);
	m_lpQQUser->m_nStatus = QQ_STATUS_OFFLINE;
	::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_LOGOUT_RESULT, 0, 0);	// 通知回调窗口注销结果

	m_bStop = FALSE;

	return 0;
}

int CLogoutTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CLogoutTask::TaskFinish()
{

}