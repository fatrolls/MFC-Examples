#include "StdAfx.h"
#include "GetChatPicTask.h"

CGetChatPicTask::CGetChatPicTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_nType = OP_TYPE_BUDDY_PIC;
	m_lpMsg = NULL;
	m_bStop = FALSE;
}

CGetChatPicTask::~CGetChatPicTask(void)
{

}

int CGetChatPicTask::Run()
{
	CBuffer bufPic;
	BOOL bRet;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol || NULL == m_lpMsg)
	{
		m_bStop = FALSE;
		return 0;
	}

	if (OP_TYPE_BUDDY_PIC == m_nType)	// 好友图片
	{
		CBuddyMessage * lpMsg = (CBuddyMessage *)m_lpMsg;

		int nCount = (int)lpMsg->m_arrContent.size();
		for (int i = 0; i < nCount; i++)
		{
			CContent * lpContent = lpMsg->m_arrContent[i];
			if (NULL == lpContent)
				continue;
			
			if (CONTENT_TYPE_CUSTOM_FACE == lpContent->m_nType)		// 自定义表情
			{
				bRet = m_lpQQProtocol->GetBuddyChatPic(m_HttpClient, lpMsg->m_nMsgId,
					lpContent->m_CFaceInfo.m_strName.c_str(), lpMsg->m_nFromUin, 
					WEBQQ_CLIENT_ID, m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), &bufPic);
				if (bRet)
					SavePic(lpContent->m_CFaceInfo.m_strName.c_str(), bufPic.GetData(), bufPic.GetSize());
			}
			else if (CONTENT_TYPE_OFF_PIC == lpContent->m_nType)	// 离线图片
			{
				bRet = m_lpQQProtocol->GetBuddyOffChatPic(m_HttpClient, 
					lpContent->m_CFaceInfo.m_strName.c_str(), lpMsg->m_nFromUin, 
					WEBQQ_CLIENT_ID, m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), &bufPic);
				if (bRet)
					SavePic(lpContent->m_CFaceInfo.m_strName.c_str(), bufPic.GetData(), bufPic.GetSize());
			}
		}

		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_BUDDY_MSG, NULL, (LPARAM)lpMsg);
	}
	else if (OP_TYPE_GROUP_PIC == m_nType)	// 群图片
	{
		CGroupMessage * lpMsg = (CGroupMessage *)m_lpMsg;

		int nCount = (int)lpMsg->m_arrContent.size();
		for (int i = 0; i < nCount; i++)
		{
			CContent * lpContent = lpMsg->m_arrContent[i];
			if (lpContent != NULL && CONTENT_TYPE_CUSTOM_FACE == lpContent->m_nType)
			{
				LPCTSTR lpFmt = _T("%[^:]:%d");
				TCHAR cServer[1024] = {0};
				int nPort = 0;

				_stscanf(lpContent->m_CFaceInfo.m_strServer.c_str(), lpFmt, cServer, &nPort);

				bRet = m_lpQQProtocol->GetGroupChatPic(m_HttpClient, lpMsg->m_nGroupCode,
					lpMsg->m_nSendUin, cServer, nPort, lpContent->m_CFaceInfo.m_nFileId, 
					lpContent->m_CFaceInfo.m_strName.c_str(), m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), &bufPic);
				if (bRet)
					SavePic(lpContent->m_CFaceInfo.m_strName.c_str(), bufPic.GetData(), bufPic.GetSize());
			}
		}

		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_GROUP_MSG, NULL, (LPARAM)lpMsg);
	}
	else if (OP_TYPE_SESS_PIC == m_nType)
	{
		// WebQQ协议目前不支持临时会话发送/接收自定义表情
	}

	m_bStop = FALSE;

	return 0;
}

int CGetChatPicTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CGetChatPicTask::TaskFinish()
{
	delete this;
}

// 保存图片
BOOL CGetChatPicTask::SavePic(LPCTSTR lpszFileName, const BYTE * lpData, DWORD dwSize)
{
	if (NULL == lpszFileName || NULL == *lpszFileName
		|| NULL == lpData || dwSize <= 0)
		return FALSE;

	::OutputDebugString(_T("下载图片："));
	::OutputDebugString(lpszFileName);
	::OutputDebugString(_T("\r\n"));

	tstring strFullName = m_lpQQUser->GetChatPicFullName(lpszFileName);

	tstring strPath = ZYM::CPath::GetDirectoryName(strFullName.c_str());
	if (!ZYM::CPath::IsDirectoryExist(strPath.c_str()))
		ZYM::CPath::CreateDirectory(strPath.c_str(), NULL);

	FILE * fp = _tfopen(strFullName.c_str(), _T("wb"));
	if (fp != NULL)
	{
		fwrite(lpData, dwSize, 1, fp);
		fclose(fp);
		return TRUE;
	}
	else
		return FALSE;
}
