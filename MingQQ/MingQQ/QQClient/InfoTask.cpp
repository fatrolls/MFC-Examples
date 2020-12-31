#include "StdAfx.h"
#include "InfoTask.h"

CInfoTask::CInfoTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_nType = OP_TYPE_GETBUDDYINFO;
	m_nGroupCode = 0;
	m_nQQUin = 0;
	m_bStop = FALSE;
}

CInfoTask::~CInfoTask(void)
{
}

int CInfoTask::Run()
{
	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		m_bStop = FALSE;
		return 0;
	}
	
	if (OP_TYPE_GETBUDDYINFO == m_nType)	// 获取好友资料
	{
		CBuddyInfoResult * lpBuddyInfoResult = new CBuddyInfoResult;
		if (lpBuddyInfoResult != NULL)
		{
			BOOL bRet = m_lpQQProtocol->GetBuddyInfo(m_HttpClient, m_nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpBuddyInfoResult);
			if (!bRet || lpBuddyInfoResult->m_nRetCode != 0)
			{
				delete lpBuddyInfoResult;
				lpBuddyInfoResult = NULL;
			}
		}
		::PostMessage(m_lpQQUser->m_hProxyWnd, 
			QQ_MSG_UPDATE_BUDDY_INFO, 0, (LPARAM)lpBuddyInfoResult);
	}
	else if (OP_TYPE_GETGMEMBERINFO == m_nType)		// 获取群成员资料
	{
		CBuddyInfoResult * lpBuddyInfoResult = new CBuddyInfoResult;
		if (lpBuddyInfoResult != NULL)
		{
			BOOL bRet = m_lpQQProtocol->GetStrangerInfo(m_HttpClient, m_nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpBuddyInfoResult);
			if (!bRet || lpBuddyInfoResult->m_nRetCode != 0)
			{
				delete lpBuddyInfoResult;
				lpBuddyInfoResult = NULL;
			}
		}
		::PostMessage(m_lpQQUser->m_hProxyWnd, 
			QQ_MSG_UPDATE_GMEMBER_INFO, m_nGroupCode, (LPARAM)lpBuddyInfoResult);
	}
	else if (OP_TYPE_GETGROUPINFO == m_nType)		// 获取群资料
	{
		CGroupInfoResult * lpGroupInfoResult = new CGroupInfoResult;
		if (lpGroupInfoResult != NULL)
		{
			BOOL bRet = m_lpQQProtocol->GetGroupInfo(m_HttpClient, m_nGroupCode, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGroupInfoResult);
			if (!bRet || lpGroupInfoResult->m_nRetCode != 0)
			{
				delete lpGroupInfoResult;
				lpGroupInfoResult = NULL;
			}
		}
		::PostMessage(m_lpQQUser->m_hProxyWnd, 
			QQ_MSG_UPDATE_GROUP_INFO, 0, (LPARAM)lpGroupInfoResult);
	}

	m_bStop = FALSE;
	return 0;
}

int CInfoTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CInfoTask::TaskFinish()
{
	delete this;
}