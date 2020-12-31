#include "StdAfx.h"
#include "QQNumTask.h"

CQQNumTask::CQQNumTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_bStop = FALSE;
}

CQQNumTask::~CQQNumTask(void)
{
	DelAllItems();
}

int CQQNumTask::Run()
{
	QQNUM_PARAM stQQNumParam;
	CGetQQNumResult * lpGetQQNumResult;
	BOOL bRet;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		DelAllItems();
		m_bStop = FALSE;
		return 0;
	}

	for (int i = 0; i < (int)m_arrParam.size(); i++)
	{
		stQQNumParam = m_arrParam[i];

		lpGetQQNumResult = new CGetQQNumResult;
		if (NULL == lpGetQQNumResult)
			goto Ret0;

		if (OP_TYPE_GETBUDDYNUM == stQQNumParam.nType)	// 获取好友号码
		{
			bRet = m_lpQQProtocol->GetQQNum(m_HttpClient, TRUE, stQQNumParam.nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetQQNumResult);
			if (m_bStop)
			{
				delete lpGetQQNumResult;
				goto Ret0;
			}

			if (!bRet || lpGetQQNumResult->m_nRetCode != 0)
			{
				delete lpGetQQNumResult;
				lpGetQQNumResult = NULL;
			}

			::PostMessage(m_lpQQUser->m_hProxyWnd, 
				QQ_MSG_UPDATE_BUDDY_NUMBER, 0, (LPARAM)lpGetQQNumResult);
		}
		else if (OP_TYPE_GETGMEMBERNUM == stQQNumParam.nType)	// 获取群成员号码
		{
			bRet = m_lpQQProtocol->GetQQNum(m_HttpClient, TRUE, stQQNumParam.nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetQQNumResult);
			if (m_bStop)
			{
				delete lpGetQQNumResult;
				goto Ret0;
			}

			if (!bRet || lpGetQQNumResult->m_nRetCode != 0)
			{
				delete lpGetQQNumResult;
				lpGetQQNumResult = NULL;
			}

			::PostMessage(m_lpQQUser->m_hProxyWnd, 
				QQ_MSG_UPDATE_GMEMBER_NUMBER, stQQNumParam.nGroupCode, (LPARAM)lpGetQQNumResult);
		}
		else if (OP_TYPE_GETGROUPNUM == stQQNumParam.nType)	// 获取群号码
		{
			bRet = m_lpQQProtocol->GetQQNum(m_HttpClient, FALSE, stQQNumParam.nGroupCode, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetQQNumResult);
			if (m_bStop)
			{
				delete lpGetQQNumResult;
				goto Ret0;
			}

			if (!bRet || lpGetQQNumResult->m_nRetCode != 0)
			{
				delete lpGetQQNumResult;
				lpGetQQNumResult = NULL;
			}

			::PostMessage(m_lpQQUser->m_hProxyWnd, 
				QQ_MSG_UPDATE_GROUP_NUMBER, stQQNumParam.nGroupCode, (LPARAM)lpGetQQNumResult);
		}
	}

Ret0:
	DelAllItems();
	m_bStop = FALSE;

	return 0;
}

int CQQNumTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CQQNumTask::TaskFinish()
{
	delete this;
}

BOOL CQQNumTask::AddParam(QQNUM_OP_TYPE nType, UINT nGroupCode, UINT nQQUin)
{
	QQNUM_PARAM stQQNumParam;
	stQQNumParam.nType = nType;
	stQQNumParam.nGroupCode = nGroupCode;
	stQQNumParam.nQQUin = nQQUin;
	m_arrParam.push_back(stQQNumParam);
	return TRUE;
}

void CQQNumTask::DelAllItems()
{
	m_arrParam.clear();
}
