#include "StdAfx.h"
#include "SendMsgTask.h"

CMsgItem::CMsgItem(void)
{
	m_nType = QQ_MSG_TYPE_BUDDY;
	m_lpMsg = NULL;
	m_nGroupNum = m_nQQNum = 0;
}

CMsgItem::~CMsgItem(void)
{
	if (m_lpMsg != NULL)
	{
		switch (m_nType)
		{
		case QQ_MSG_TYPE_BUDDY:
			delete (CBuddyMessage *)m_lpMsg;
			break;
		case QQ_MSG_TYPE_GROUP:
			delete (CGroupMessage *)m_lpMsg;
			break;
		case QQ_MSG_TYPE_SESS:
			delete (CSessMessage *)m_lpMsg;
			break;
		}
	}
}

CSendMsgTask::CSendMsgTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_nMsgId = 1100001;
	memset(&m_csItem, 0, sizeof(CRITICAL_SECTION));
	::InitializeCriticalSection(&m_csItem);
	m_hSemaphore = ::CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
	m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

CSendMsgTask::~CSendMsgTask(void)
{
	for (int i = 0; i < (int)m_arrItem.size(); i++)
	{
		CMsgItem * lpMsgItem = m_arrItem[i];
		if (lpMsgItem != NULL)
			delete lpMsgItem;
	}
	m_arrItem.clear();

	::DeleteCriticalSection(&m_csItem);

	if (m_hSemaphore != NULL)
	{
		::CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}

	if (m_hEvent != NULL)
	{
		::CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}
}

int CSendMsgTask::Run()
{
	HANDLE hWaitEvent[2];
	DWORD dwIndex;
	CMsgItem * lpMsgItem;
	BOOL bRet;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
		return 0;

	hWaitEvent[0] = m_hEvent;
	hWaitEvent[1] = m_hSemaphore;

	while (1)
	{
		dwIndex = ::WaitForMultipleObjects(2, hWaitEvent, FALSE, INFINITE);

		if (dwIndex == WAIT_OBJECT_0)
			break;

		lpMsgItem = NULL;

		::EnterCriticalSection(&m_csItem);
		if (m_arrItem.size() > 0)
		{
			lpMsgItem = m_arrItem[0];
			m_arrItem.erase(m_arrItem.begin() + 0);
		}
		::LeaveCriticalSection(&m_csItem);

		if (lpMsgItem != NULL)
		{
			switch (lpMsgItem->m_nType)
			{
			case QQ_MSG_TYPE_BUDDY:		// 好友消息
				{
					bRet = SendBuddyMsg(lpMsgItem);
					if (!bRet)
						::OutputDebugString(_T("发送好友消息失败\n"));
				}
				break;
			case QQ_MSG_TYPE_GROUP:		// 群消息
				{
					bRet = SendGroupMsg(lpMsgItem);
					if (!bRet)
						::OutputDebugString(_T("发送群消息失败\n"));
				}
				break;
			case QQ_MSG_TYPE_SESS:		// 群成员消息
				{
					bRet = SendSessMsg(lpMsgItem);
					if (!bRet)
						::OutputDebugString(_T("发送群成员消息失败\n"));
				}
				break;
			}
			delete lpMsgItem;
		}
	}

	return 0;
}

int CSendMsgTask::Stop()
{
	m_HttpClient.SetCancalEvent();
	::SetEvent(m_hEvent);
	return 0;
}

void CSendMsgTask::TaskFinish()
{
	
}

BOOL CSendMsgTask::AddBuddyMsg(UINT nToUin, time_t nTime, LPCTSTR lpMsg)
{
	if (0 == nToUin || NULL == lpMsg || NULL == *lpMsg)
		return FALSE;

	CMsgItem * lpMsgItem = new CMsgItem;
	if (NULL == lpMsgItem)
		return FALSE;

	CBuddyMessage * lpBuddyMsg = new CBuddyMessage;
	if (NULL == lpBuddyMsg)
	{
		delete lpMsgItem;
		return FALSE;
	}

	m_nMsgId++;
	lpBuddyMsg->m_nMsgId = m_nMsgId;
	lpBuddyMsg->m_nTime = (UINT)nTime;
	lpBuddyMsg->m_nToUin = nToUin;

	CreateMsgContent(lpMsg, lpBuddyMsg->m_arrContent);

	lpMsgItem->m_nType = QQ_MSG_TYPE_BUDDY;
	lpMsgItem->m_lpMsg = (void *)lpBuddyMsg;
	if (m_lpQQUser != NULL)	// 使用到未加锁的主线程数据，不要在主线程之外的线程调用此函数
	{
		CBuddyInfo * lpBuddyInfo = m_lpQQUser->m_BuddyList.GetBuddy(nToUin);
		if (lpBuddyInfo != NULL)
			lpMsgItem->m_nQQNum = lpBuddyInfo->m_nQQNum;
		lpMsgItem->m_strNickName = m_lpQQUser->m_UserInfo.m_strNickName;
	}

	::EnterCriticalSection(&m_csItem);
	m_arrItem.push_back(lpMsgItem);
	::LeaveCriticalSection(&m_csItem);

	::ReleaseSemaphore(m_hSemaphore, 1, NULL);

	return TRUE;
}

BOOL CSendMsgTask::AddGroupMsg(UINT nGroupId, time_t nTime, LPCTSTR lpMsg)
{
	if (0 == nGroupId || NULL == lpMsg || NULL == *lpMsg)
		return FALSE;

	CMsgItem * lpMsgItem = new CMsgItem;
	if (NULL == lpMsgItem)
		return FALSE;

	CGroupMessage * lpGroupMsg = new CGroupMessage;
	if (NULL == lpGroupMsg)
	{
		delete lpMsgItem;
		return FALSE;
	}

	m_nMsgId++;
	lpGroupMsg->m_nMsgId = m_nMsgId;
	lpGroupMsg->m_nTime = (UINT)nTime;
	lpGroupMsg->m_nToUin = nGroupId;
	if (m_lpQQUser != NULL)
		lpGroupMsg->m_nGroupCode = m_lpQQUser->m_GroupList.GetGroupCodeById(nGroupId);

	CreateMsgContent(lpMsg, lpGroupMsg->m_arrContent);

	lpMsgItem->m_nType = QQ_MSG_TYPE_GROUP;
	lpMsgItem->m_lpMsg = (void *)lpGroupMsg;
	if (m_lpQQUser != NULL)	// 使用到未加锁的主线程数据，不要在主线程之外的线程调用此函数
	{
		CGroupInfo * lpGroupInfo = m_lpQQUser->m_GroupList.GetGroupById(nGroupId);
		if (lpGroupInfo != NULL)
		{
			lpMsgItem->m_nGroupNum = lpGroupInfo->m_nGroupNumber;
			lpMsgItem->m_nQQNum = m_lpQQUser->m_nQQUin;
			CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByUin(m_lpQQUser->m_nQQUin);
			if (lpBuddyInfo != NULL)
			{
				if (!lpBuddyInfo->m_strGroupCard.empty())
					lpMsgItem->m_strNickName = lpBuddyInfo->m_strGroupCard;
				else
					lpMsgItem->m_strNickName = lpBuddyInfo->m_strNickName;
			}
		}
	}
	
	::EnterCriticalSection(&m_csItem);
	m_arrItem.push_back(lpMsgItem);
	::LeaveCriticalSection(&m_csItem);

	::ReleaseSemaphore(m_hSemaphore, 1, NULL);

	return TRUE;
}

BOOL CSendMsgTask::AddSessMsg(UINT nGroupId, UINT nToUin, time_t nTime, LPCTSTR lpMsg)
{
	if (0 == nGroupId || 0 == nToUin || NULL == lpMsg || NULL == *lpMsg)
		return FALSE;

	CMsgItem * lpMsgItem = new CMsgItem;
	if (NULL == lpMsgItem)
		return FALSE;

	CSessMessage * lpSessMsg = new CSessMessage;
	if (NULL == lpSessMsg)
	{
		delete lpMsgItem;
		return FALSE;
	}

	m_nMsgId++;
	lpSessMsg->m_nMsgId = m_nMsgId;
	lpSessMsg->m_nTime = (UINT)nTime;
	lpSessMsg->m_nToUin = nToUin;
	lpSessMsg->m_nGroupId = nGroupId;
	
	CreateMsgContent(lpMsg, lpSessMsg->m_arrContent);

	lpMsgItem->m_nType = QQ_MSG_TYPE_SESS;
	lpMsgItem->m_lpMsg = (void *)lpSessMsg;
	if (m_lpQQUser != NULL)	// 使用到未加锁的主线程数据，不要在主线程之外的线程调用此函数
	{
		lpMsgItem->m_strNickName = m_lpQQUser->m_UserInfo.m_strNickName;

		CBuddyInfo * lpBuddyInfo = m_lpQQUser->m_GroupList.GetGroupMemberById(nGroupId, nToUin);
		if (lpBuddyInfo != NULL)
		{
			lpMsgItem->m_nQQNum = lpBuddyInfo->m_nQQNum;
			lpMsgItem->m_strGroupSig = lpBuddyInfo->m_strGroupSig;
		}
	}

	::EnterCriticalSection(&m_csItem);
	m_arrItem.push_back(lpMsgItem);
	::LeaveCriticalSection(&m_csItem);

	::ReleaseSemaphore(m_hSemaphore, 1, NULL);

	return TRUE;
}

BOOL CSendMsgTask::HandleFontInfo(LPCTSTR& p, tstring& strText, std::vector<CContent *>& arrContent)
{
	tstring strTemp = GetBetweenString(p+2, _T("[\""), _T("\"]")).c_str();
	if (!strTemp.empty())
	{
		LPCTSTR lpFontFmt = _T("%[^,],%d,%[^,],%d,%d,%d");
		TCHAR szName[32] = _T("宋体");
		TCHAR szColor[32] = _T("000000");
		int nSize = 9;
		BOOL bBold = FALSE, bItalic = FALSE, bUnderLine = FALSE;

		int nCount = _stscanf(strTemp.c_str(), lpFontFmt, szName, 
			&nSize, &szColor, &bBold, &bItalic, &bUnderLine);
		if (nCount != 6)
			return FALSE;

		if (!strText.empty())
		{
			CContent * lpContent = new CContent;
			if (lpContent != NULL)
			{
				lpContent->m_nType = CONTENT_TYPE_TEXT;
				lpContent->m_strText = strText;
				arrContent.push_back(lpContent);
			}
			strText = _T("");
		}

		CContent * lpContent = new CContent;
		if (lpContent != NULL)
		{
			lpContent->m_nType = CONTENT_TYPE_FONT_INFO;
			lpContent->m_FontInfo.m_nSize = nSize;
			lpContent->m_FontInfo.m_clrText = HexStrToRGB(szColor);
			lpContent->m_FontInfo.m_strName = szName;
			lpContent->m_FontInfo.m_bBold = bBold;
			lpContent->m_FontInfo.m_bItalic = bItalic;				
			lpContent->m_FontInfo.m_bUnderLine = bUnderLine;
			arrContent.push_back(lpContent);
		}

		p = _tcsstr(p+2, _T("\"]"));
		p++;
		return TRUE;
	}
	return FALSE;
}

BOOL CSendMsgTask::HandleSysFaceId(LPCTSTR& p, tstring& strText, std::vector<CContent *>& arrContent)
{
	int nFaceId = GetBetweenInt(p+2, _T("[\""), _T("\"]"), -1);
	if (nFaceId != -1)
	{
		if (!strText.empty())
		{
			CContent * lpContent = new CContent;
			if (lpContent != NULL)
			{
				lpContent->m_nType = CONTENT_TYPE_TEXT;
				lpContent->m_strText = strText;
				arrContent.push_back(lpContent);
			}
			strText = _T("");
		}

		CContent * lpContent = new CContent;
		if (lpContent != NULL)
		{
			lpContent->m_nType = CONTENT_TYPE_FACE;
			lpContent->m_nFaceId = nFaceId;
			arrContent.push_back(lpContent);
		}

		p = _tcsstr(p+2, _T("\"]"));
		p++;
		return TRUE;
	}
	return FALSE;
}

BOOL CSendMsgTask::HandleCustomPic(LPCTSTR& p, tstring& strText, std::vector<CContent *>& arrContent)
{
	tstring strFileName = GetBetweenString(p+2, _T("[\""), _T("\"]"));
	if (!strFileName.empty())
	{
		if (!strText.empty())
		{
			CContent * lpContent = new CContent;
			if (lpContent != NULL)
			{
				lpContent->m_nType = CONTENT_TYPE_TEXT;
				lpContent->m_strText = strText;
				arrContent.push_back(lpContent);
			}
			strText = _T("");
		}

		CContent * lpContent = new CContent;
		if (lpContent != NULL)
		{
			lpContent->m_nType = CONTENT_TYPE_CUSTOM_FACE;
			lpContent->m_CFaceInfo.m_strName = strFileName;
			arrContent.push_back(lpContent);
		}

		p = _tcsstr(p+2, _T("\"]"));
		p++;
		return TRUE;
	}
	return FALSE;
}

BOOL CSendMsgTask::CreateMsgContent(LPCTSTR lpMsg, std::vector<CContent *>& arrContent)
{
	tstring strText;
	CContent * lpContent;

	if (NULL == lpMsg)
		return FALSE;

	for (LPCTSTR p = lpMsg; *p != _T('\0'); p++)
	{
		if (*p == _T('/'))
		{
			if (*(p+1) == _T('/'))
			{
				strText += *p;
				p++;
				continue;
			}
			else if (*(p+1) == _T('o'))
			{
				if (HandleFontInfo(p, strText, arrContent))
					continue;
			}
			else if (*(p+1) == _T('f'))
			{
				if (HandleSysFaceId(p, strText, arrContent))
					continue;
			}
			else if (*(p+1) == _T('c'))
			{
				if (HandleCustomPic(p, strText, arrContent))
					continue;
			}
		}
		strText += *p;
	}

	if (!strText.empty())
	{
		lpContent = new CContent;
		if (lpContent != NULL)
		{
			lpContent->m_nType = CONTENT_TYPE_TEXT;
			lpContent->m_strText = strText;
			arrContent.push_back(lpContent);
		}
		strText = _T("");
	}

	return TRUE;
}

// 上传好友聊天图片
BOOL CSendMsgTask::UploadBuddyChatPic(LPCTSTR lpszFileName, CUploadBuddyChatPicResult& result)
{
	UINT& nQQUin = m_lpQQUser->m_nQQUin;
	tstring& strSKey = m_lpQQUser->m_LoginResult1.m_strSKey;
	tstring& strVfWebQq = m_lpQQUser->m_LoginResult2.m_strVfWebQq;
	tstring& strPSessionId = m_lpQQUser->m_LoginResult2.m_strPSessionId;

	BOOL bRet = m_lpQQProtocol->UploadBuddyChatPic(m_HttpClient, nQQUin, 
		strSKey.c_str(), lpszFileName, strVfWebQq.c_str(), &result);
	if (!bRet || (result.m_nRetCode != 0))
		return FALSE;

	CApplyBuddyChatPicResult result2;
	bRet = m_lpQQProtocol->ApplyBuddyChatPic(m_HttpClient, nQQUin, 
		result.m_strFilePath.c_str(), WEBQQ_CLIENT_ID, strPSessionId.c_str(), &result2);
	if (!bRet || (result2.m_nRetCode != 0))
		return FALSE;

	return TRUE;
}

// 上传群聊天图片
BOOL CSendMsgTask::UploadGroupChatPic(LPCTSTR lpszFileName, CUploadGroupChatPicResult& result)
{
	BOOL bRet = m_lpQQProtocol->UploadGroupChatPic(m_HttpClient, lpszFileName, 
		m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), &result);
	if (!bRet || (result.m_nRetCode != 0 && result.m_nRetCode != 4))
		return FALSE;

	return TRUE;
}

// 发送好友消息
BOOL CSendMsgTask::SendBuddyMsg(CMsgItem * lpMsgItem)
{
	if (NULL == lpMsgItem || NULL == lpMsgItem->m_lpMsg)
		return FALSE;

	CBuddyMessage * lpMsg = (CBuddyMessage *)lpMsgItem->m_lpMsg;
	std::vector<CContent *>& arrContent = lpMsg->m_arrContent;
	CUploadBuddyChatPicResult uploadPicResult;
	CSendBuddyMsgResult sendMsgResult;
	int nRetry = 3;		// 重试次数
	BOOL bRet;

	for (int i = 0; i < (int)arrContent.size(); i++)	// 上传自定义表情
	{
		CContent * lpContent = arrContent[i];
		if (lpContent != NULL && CONTENT_TYPE_CUSTOM_FACE == lpContent->m_nType)
		{
			for (int j = 0; j < nRetry; j++)
			{
				bRet = UploadBuddyChatPic(lpContent->m_CFaceInfo.m_strName.c_str(), uploadPicResult);
				if (bRet)
					break;
			}

			if (!bRet)
				return FALSE;

			lpContent->m_CFaceInfo.m_dwFileSize = uploadPicResult.m_dwFileSize;
			lpContent->m_CFaceInfo.m_strFileName = uploadPicResult.m_strFileName;
			lpContent->m_CFaceInfo.m_strFilePath = uploadPicResult.m_strFilePath;
		}
	}

	bRet = m_lpQQProtocol->SendBuddyMsg(m_HttpClient, lpMsg, WEBQQ_CLIENT_ID, 
		m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), &sendMsgResult);
	if (!bRet || (sendMsgResult.m_nRetCode != 0))
		return FALSE;

	WriteBuddyMsgLog(m_lpQQUser, lpMsgItem->m_nQQNum, lpMsgItem->m_strNickName.c_str(), TRUE, lpMsg);

	return TRUE;
}

// 发送群消息
BOOL CSendMsgTask::SendGroupMsg(CMsgItem * lpMsgItem)
{
	if (NULL == lpMsgItem || NULL == lpMsgItem->m_lpMsg)
		return FALSE;

	CGroupMessage * lpMsg = (CGroupMessage *)lpMsgItem->m_lpMsg;
	std::vector<CContent *>& arrContent = lpMsg->m_arrContent;
	CUploadGroupChatPicResult uploadPicResult;
	CGetGroupFaceSigResult sigResult;
	CSendGroupMsgResult sendMsgResult;
	BOOL bHasCustomFace = FALSE;
	int nRetry = 3;		// 重试次数
	BOOL bRet;

	for (int i = 0; i < (int)arrContent.size(); i++)	// 上传自定义表情
	{
		CContent * lpContent = arrContent[i];
		if (lpContent != NULL && CONTENT_TYPE_CUSTOM_FACE == lpContent->m_nType)
		{
			bHasCustomFace = TRUE;

			for (int j = 0; j < nRetry; j++)
			{
				bRet = UploadGroupChatPic(lpContent->m_CFaceInfo.m_strName.c_str(), uploadPicResult);
				if (bRet)
					break;
			}

			if (!bRet)
				return FALSE;

			lpContent->m_CFaceInfo.m_strFilePath = uploadPicResult.m_strFilePath;
		}
	}

	if (bHasCustomFace && (m_strGFaceKey.empty() || m_strGFaceSig.empty()))
	{
		bRet = m_lpQQProtocol->GetGroupFaceSignal(m_HttpClient, WEBQQ_CLIENT_ID, 
			m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), &sigResult);
		if (!bRet || (sigResult.m_nRetCode != 0))
			return FALSE;

		m_strGFaceKey = sigResult.m_strGFaceKey;
		m_strGFaceSig = sigResult.m_strGFaceSig;
	}

	bRet = m_lpQQProtocol->SendGroupMsg(m_HttpClient, lpMsg, 
		WEBQQ_CLIENT_ID, m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), 
		m_strGFaceKey.c_str(), m_strGFaceSig.c_str(), &sendMsgResult);
	if (!bRet || (sendMsgResult.m_nRetCode != 0))
		return FALSE;

	WriteGroupMsgLog(m_lpQQUser, lpMsgItem->m_nGroupNum, 
		lpMsgItem->m_nQQNum, lpMsgItem->m_strNickName.c_str(), lpMsg);

	return TRUE;
}

// 发送群成员消息
BOOL CSendMsgTask::SendSessMsg(CMsgItem * lpMsgItem)
{
	if (NULL == lpMsgItem || NULL == lpMsgItem->m_lpMsg)
		return FALSE;

	CSessMessage * lpMsg = (CSessMessage *)lpMsgItem->m_lpMsg;
	CSendSessMsgResult sendMsgResult;
	BOOL bRet;

	if (lpMsgItem->m_strGroupSig.empty())
	{
		CGetC2CMsgSigResult * lpGetC2CMsgSigResult = new CGetC2CMsgSigResult;
		if (NULL == lpGetC2CMsgSigResult)
			return FALSE;
		
		bRet = m_lpQQProtocol->GetC2CMsgSignal(m_HttpClient, 
			lpMsg->m_nGroupId, lpMsg->m_nToUin, WEBQQ_CLIENT_ID, 
			m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), lpGetC2CMsgSigResult);
		if (!bRet || lpGetC2CMsgSigResult->m_nRetCode != 0)
		{
			delete lpGetC2CMsgSigResult;
			lpGetC2CMsgSigResult = NULL;
			return FALSE;
		}
		lpMsgItem->m_strGroupSig = lpGetC2CMsgSigResult->m_strValue;
		lpGetC2CMsgSigResult->m_nGroupId = lpMsg->m_nGroupId;
		lpGetC2CMsgSigResult->m_nQQUin = lpMsg->m_nToUin;
		::PostMessage(m_lpQQUser->m_hProxyWnd, 
			QQ_MSG_UPDATE_C2CMSGSIG, 0, (LPARAM)lpGetC2CMsgSigResult);
	}

	bRet = m_lpQQProtocol->SendSessMsg(m_HttpClient, lpMsg, lpMsgItem->m_strGroupSig.c_str(), 
		WEBQQ_CLIENT_ID, m_lpQQUser->m_LoginResult2.m_strPSessionId.c_str(), &sendMsgResult);
	if (!bRet || (sendMsgResult.m_nRetCode != 0))
		return FALSE;

	WriteSessMsgLog(m_lpQQUser, lpMsgItem->m_nQQNum, lpMsgItem->m_strNickName.c_str(), TRUE, lpMsg);

	return TRUE;
}