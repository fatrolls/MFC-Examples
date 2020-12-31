#include "StdAfx.h"
#include "GetGroupFaceSigTask.h"

CGetGroupFaceSigTask::CGetGroupFaceSigTask(void)
{
}

CGetGroupFaceSigTask::~CGetGroupFaceSigTask(void)
{
}

int CGetGroupFaceSigTask::Run()
{
	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		m_bStop = FALSE;
		return 0;
	}

	CGetGroupFaceSigResult * lpGetGroupFaceSigResult = new CGetGroupFaceSigResult;
	if (lpGetGroupFaceSigResult != NULL)
	{
		BOOL bRet = m_lpQQProtocol->GetGroupFaceSignal(m_HttpClient, WEBQQ_CLIENT_ID, 
			m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), lpGetGroupFaceSigResult);
		if (!bRet || lpGetGroupFaceSigResult->m_nRetCode != 0)
		{
			delete lpGetGroupFaceSigResult;
			lpGetGroupFaceSigResult = NULL;
		}
		::PostMessage(m_lpQQUser->m_hCallBackWnd, 
			QQ_MSG_UPDATE_GROUPFACESIG, 0, (LPARAM)lpGetGroupFaceSigResult);
	}

	m_bStop = FALSE;
	return 0;
}

int CGetGroupFaceSigTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CGetGroupFaceSigTask::TaskFinish()
{
	delete this;
}