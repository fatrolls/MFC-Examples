#include "StdAfx.h"
#include "QQSignTask.h"

CQQSignTask::CQQSignTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_nType = QQSIGN_OP_TYPE_GET;
	m_bStop = FALSE;
}

CQQSignTask::~CQQSignTask(void)
{
	DelAllItems();
}

int CQQSignTask::Run()
{
	BOOL bRet;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		DelAllItems();
		m_bStop = FALSE;
		return 0;
	}

	if (QQSIGN_OP_TYPE_GET == m_nType)	// 获取QQ个性签名
	{
		for (int i = 0; i < (int)m_arrGetParam.size(); i++)
		{
			QQSIGN_GET_PARAM stGetParam;
			CGetSignResult * lpGetSignResult;

			stGetParam = m_arrGetParam[i];

			lpGetSignResult = new CGetSignResult;
			if (NULL == lpGetSignResult)
				goto Ret0;

			bRet = m_lpQQProtocol->GetQQSign(m_HttpClient, stGetParam.nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetSignResult);
			if (m_bStop)
			{
				delete lpGetSignResult;
				goto Ret0;
			}

			if (!bRet || lpGetSignResult->m_nRetCode != 0)
			{
				delete lpGetSignResult;
				lpGetSignResult = NULL;
			}

			if (!stGetParam.bIsGMember)
			{
				::PostMessage(m_lpQQUser->m_hProxyWnd, 
					QQ_MSG_UPDATE_BUDDY_SIGN, 0, (LPARAM)lpGetSignResult);
			}
			else
			{
				::PostMessage(m_lpQQUser->m_hProxyWnd, 
					QQ_MSG_UPDATE_GMEMBER_SIGN, stGetParam.nGroupCode, (LPARAM)lpGetSignResult);
			}
		}
	}
	else if (QQSIGN_OP_TYPE_SET == m_nType)	// 设置QQ个性签名
	{
		QQSIGN_SET_PARAM stSetParam;
		CSetSignResult setSignResult;

		for (int i = 0; i < (int)m_arrSetParam.size(); i++)
		{
			stSetParam = m_arrSetParam[i];
			bRet = m_lpQQProtocol->SetQQSign(m_HttpClient, stSetParam.m_strSign.c_str(),
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), &setSignResult);
			if (m_bStop)
				goto Ret0;

			if (!bRet || setSignResult.m_nRetCode != 0)
				continue;
		}
	}

Ret0:
	DelAllItems();
	m_bStop = FALSE;

	return 0;
}

int CQQSignTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CQQSignTask::TaskFinish()
{
	delete this;
}

BOOL CQQSignTask::AddGetParam(BOOL bIsGMember, UINT nGroupCode, UINT nQQUin)
{
	QQSIGN_GET_PARAM stGetParam;
	stGetParam.bIsGMember = bIsGMember;
	stGetParam.nGroupCode = nGroupCode;
	stGetParam.nQQUin = nQQUin;
	m_arrGetParam.push_back(stGetParam);
	return TRUE;
}

BOOL CQQSignTask::AddSetParam(LPCTSTR lpSign)
{
	if (NULL == lpSign)
		return FALSE;

	QQSIGN_SET_PARAM stSetParam;
	stSetParam.m_strSign = lpSign;
	m_arrSetParam.push_back(stSetParam);

	return TRUE;
}

void CQQSignTask::DelAllItems()
{
	m_arrGetParam.clear();
	m_arrSetParam.clear();
}
