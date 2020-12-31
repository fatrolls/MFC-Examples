#include "StdAfx.h"
#include "RecvMsgTask.h"

// "/f["系统表情id"] /c["自定义表情文件名"] /o[字体名称，大小，颜色，加粗，倾斜，下划线]"
tstring FormatContent(std::vector<CContent *>& arrContent)
{
	LPCTSTR lpFontFmt = _T("/o[\"%s,%d,%s,%d,%d,%d\"]");
	LPCTSTR lpFaceFmt = _T("/f[\"%d\"]");
	LPCTSTR lpCFaceFmt = _T("/c[\"%s\"]");
	TCHAR cBuf[1024];
	TCHAR cColor[32];
	tstring strMsg, strText;

	for (int i = 0; i < (int)arrContent.size(); i++)
	{
		CContent * lpContent = arrContent[i];
		if (NULL == lpContent)
			continue;

		switch (lpContent->m_nType)
		{
		case CONTENT_TYPE_FONT_INFO:
			{
				memset(cBuf, 0, sizeof(cBuf));
				memset(cColor, 0, sizeof(cColor));

				RGBToHexStr(lpContent->m_FontInfo.m_clrText, cColor, sizeof(cColor)/sizeof(TCHAR));

				wsprintf(cBuf, lpFontFmt, lpContent->m_FontInfo.m_strName.c_str(),
					lpContent->m_FontInfo.m_nSize, cColor,
					lpContent->m_FontInfo.m_bBold, lpContent->m_FontInfo.m_bItalic,
					lpContent->m_FontInfo.m_bUnderLine);
				strMsg += cBuf;
			}
			break;

		case CONTENT_TYPE_TEXT:
			{
				strText = lpContent->m_strText;
				Replace(strText, _T("/"), _T("//"));
				strMsg += strText;
			}
			break;

		case CONTENT_TYPE_FACE:
			{
				memset(cBuf, 0, sizeof(cBuf));
				wsprintf(cBuf, lpFaceFmt, lpContent->m_nFaceId);
				strMsg += cBuf;
			}
			break;

		case CONTENT_TYPE_CUSTOM_FACE:
		case CONTENT_TYPE_OFF_PIC:
			{
				if (!lpContent->m_CFaceInfo.m_strName.empty())
				{
					memset(cBuf, 0, sizeof(cBuf));
					wsprintf(cBuf, lpCFaceFmt, lpContent->m_CFaceInfo.m_strName.c_str());
					strMsg += cBuf;
				}
			}
			break;
		}
	}

	return strMsg;
}

BOOL CreateMsgLogFile(CMessageLogger& msgLogger, const tstring& strFileName)
{
	tstring strPath = ZYM::CPath::GetDirectoryName(strFileName.c_str());
	if (!ZYM::CPath::IsDirectoryExist(strPath.c_str()))
		ZYM::CPath::CreateDirectory(strPath.c_str(), NULL);

	msgLogger.SetMsgLogFileName(strFileName.c_str());
	return msgLogger.CreateMsgLogFile();
}

// 写入一条好友消息记录
void WriteBuddyMsgLog(CQQUser * lpQQUser, UINT nQQNum, 
					  LPCTSTR lpNickName, BOOL bSelf, CBuddyMessage * lpMsg)
{
	if (NULL == lpQQUser || 0 == nQQNum || NULL == lpMsg)
		return;

	TCHAR szNickName[32] = {0};
	if (NULL == lpNickName || NULL == *lpNickName)
	{
		wsprintf(szNickName, _T("%u"), nQQNum);
		lpNickName = szNickName;
	}

	tstring strContent = FormatContent(lpMsg->m_arrContent);

	if (!lpQQUser->m_MsgLogger.IsMsgLogFileValid())
		CreateMsgLogFile(lpQQUser->m_MsgLogger, lpQQUser->GetMsgLogFullName());

	lpQQUser->m_MsgLogger.Lock();
	lpQQUser->m_MsgLogger.WriteBuddyMsgLog(nQQNum, lpNickName, 
		lpMsg->m_nTime, bSelf, strContent.c_str());
	lpQQUser->m_MsgLogger.UnLock();
}

// 写入一条群消息记录
void WriteGroupMsgLog(CQQUser * lpQQUser, UINT nGroupNum, UINT nQQNum, 
					  LPCTSTR lpNickName, CGroupMessage * lpMsg)
{
	if (NULL == lpQQUser || 0 == nGroupNum || NULL == lpMsg)
		return;

	TCHAR szNickName[32] = {0};
	if (NULL == lpNickName || NULL == *lpNickName)
	{
		wsprintf(szNickName, _T("%u"), nQQNum);
		lpNickName = szNickName;
	}

	tstring strContent = FormatContent(lpMsg->m_arrContent);

	if (!lpQQUser->m_MsgLogger.IsMsgLogFileValid())
		CreateMsgLogFile(lpQQUser->m_MsgLogger, lpQQUser->GetMsgLogFullName());

	lpQQUser->m_MsgLogger.Lock();
	lpQQUser->m_MsgLogger.WriteGroupMsgLog(nGroupNum, nQQNum, 
		lpNickName, lpMsg->m_nTime, strContent.c_str());
	lpQQUser->m_MsgLogger.UnLock();
}

// 写入一条临时会话(群成员)消息记录
void WriteSessMsgLog(CQQUser * lpQQUser, UINT nQQNum, 
					 LPCTSTR lpNickName, BOOL bSelf, CSessMessage * lpMsg)
{
	if (NULL == lpQQUser || 0 == nQQNum || NULL == lpMsg)
		return;

	TCHAR szNickName[32] = {0};
	if (NULL == lpNickName || NULL == *lpNickName)
	{
		wsprintf(szNickName, _T("%u"), nQQNum);
		lpNickName = szNickName;
	}

	tstring strContent = FormatContent(lpMsg->m_arrContent);

	if (!lpQQUser->m_MsgLogger.IsMsgLogFileValid())
		CreateMsgLogFile(lpQQUser->m_MsgLogger, lpQQUser->GetMsgLogFullName());

	lpQQUser->m_MsgLogger.Lock();
	lpQQUser->m_MsgLogger.WriteSessMsgLog(nQQNum, lpNickName, 
		lpMsg->m_nTime, bSelf, strContent.c_str());
	lpQQUser->m_MsgLogger.UnLock();
}

CRecvMsg::CRecvMsg(void)
{

}

CRecvMsg::~CRecvMsg(void)
{

}

UINT CRecvMsg::GetMsgId()
{
	if (NULL == m_lpMsg)
		return 0;

	switch (m_nType)
	{
	case QQ_MSG_TYPE_BUDDY:
		return ((CBuddyMessage *)m_lpMsg)->m_nMsgId;
	case QQ_MSG_TYPE_GROUP:
		return ((CGroupMessage *)m_lpMsg)->m_nMsgId;
	case QQ_MSG_TYPE_SESS:
		return ((CSessMessage *)m_lpMsg)->m_nMsgId;
	default:
		return 0;
	}
}

UINT CRecvMsg::GetMsgId2()
{
	if (NULL == m_lpMsg)
		return 0;

	switch (m_nType)
	{
	case QQ_MSG_TYPE_BUDDY:
		return ((CBuddyMessage *)m_lpMsg)->m_nMsgId2;
	case QQ_MSG_TYPE_GROUP:
		return ((CGroupMessage *)m_lpMsg)->m_nMsgId2;
	case QQ_MSG_TYPE_SESS:
		return ((CSessMessage *)m_lpMsg)->m_nMsgId2;
	default:
		return 0;
	}
}

UINT CRecvMsg::GetTime()
{
	if (NULL == m_lpMsg)
		return 0;

	switch (m_nType)
	{
	case QQ_MSG_TYPE_BUDDY:
		return ((CBuddyMessage *)m_lpMsg)->m_nTime;
	case QQ_MSG_TYPE_GROUP:
		return ((CGroupMessage *)m_lpMsg)->m_nTime;
	case QQ_MSG_TYPE_SESS:
		return ((CSessMessage *)m_lpMsg)->m_nTime;
	default:
		return 0;
	}
}

CRecvMsgTask::CRecvMsgTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	memset(&m_csItem, 0, sizeof(CRITICAL_SECTION));
	::InitializeCriticalSection(&m_csItem);
	m_hSemaphore = ::CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
	m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_nPreMsgId = m_nPreMsgId2 = 0;
}

CRecvMsgTask::~CRecvMsgTask(void)
{
	DelAllMsgData();

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

int CRecvMsgTask::Run()
{
	HANDLE hWaitEvent[2];
	DWORD dwIndex;
	CBuffer * lpMsg;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
		return 0;

	hWaitEvent[0] = m_hEvent;
	hWaitEvent[1] = m_hSemaphore;

	while (1)
	{
		dwIndex = ::WaitForMultipleObjects(2, hWaitEvent, FALSE, INFINITE);

		if (dwIndex == WAIT_OBJECT_0)
			break;

		lpMsg = NULL;

		::EnterCriticalSection(&m_csItem);
		if (m_arrItem.size() > 0)
		{
			lpMsg = m_arrItem[0];
			m_arrItem.erase(m_arrItem.begin() + 0);
		}
		::LeaveCriticalSection(&m_csItem);

		if (NULL == lpMsg)
			continue;

		HandleMsg(lpMsg);

		delete lpMsg;
	}

	return 0;
}

int CRecvMsgTask::Stop()
{
	m_HttpClient.SetCancalEvent();
	::SetEvent(m_hEvent);
	return 0;
}

void CRecvMsgTask::TaskFinish()
{
}

BOOL CRecvMsgTask::AddMsgData(CBuffer * lpMsgData)
{
	if (NULL == lpMsgData)
		return FALSE;

	::EnterCriticalSection(&m_csItem);
	m_arrItem.push_back(lpMsgData);
	::LeaveCriticalSection(&m_csItem);

	::ReleaseSemaphore(m_hSemaphore, 1, NULL);

	return TRUE;
}

void CRecvMsgTask::DelAllMsgData()
{
	::EnterCriticalSection(&m_csItem);
	for (int i = 0; i < (int)m_arrItem.size(); i++)
	{
		CBuffer * lpMsgData = m_arrItem[i];
		if (lpMsgData != NULL)
			delete lpMsgData;
	}
	m_arrItem.clear();
	::LeaveCriticalSection(&m_csItem);
}

BOOL CRecvMsgTask::HandleMsg(CBuffer * lpMsgData)
{
	std::vector<CRecvMsg *> arrMsg;
	BOOL bRet;
	
	if (NULL == lpMsgData)
		return FALSE;

	bRet = ParseMsg(lpMsgData, arrMsg);
	if (!bRet || arrMsg.size() <= 0)
		return FALSE;

	if (arrMsg.size() > 1)
		SortMsgByTime(arrMsg);

	for (int i = 0; i < (int)arrMsg.size(); i++)
	{
		CRecvMsg * lpMsg = arrMsg[i];
		if (NULL == lpMsg)
			continue;
		
		switch (lpMsg->m_nType)
		{
		case QQ_MSG_TYPE_BUDDY:
			HandleBuddyMsg(lpMsg);
			break;
		case QQ_MSG_TYPE_GROUP:
			HandleGroupMsg(lpMsg);
			break;
		case QQ_MSG_TYPE_SESS:
			HandleSessMsg(lpMsg);
			break;
		case QQ_MSG_TYPE_STATUSCHANGE:
			HandleStatusChangeMsg(lpMsg);
			break;
		case QQ_MSG_TYPE_KICK:
			HandleKickMsg(lpMsg);
			break;
		case QQ_MSG_TYPE_SYSGROUP:
			HandleSysGroupMsg(lpMsg);
			break;
		}
	}

	return TRUE;
}

BOOL CRecvMsgTask::ParseMsg(CBuffer * lpMsgData, std::vector<CRecvMsg *>& arrMsg)
{
	if (NULL == lpMsgData)
		return FALSE;

	CHAR * lpData = (CHAR * )lpMsgData->GetData();
	DWORD dwSize = lpMsgData->GetSize();
	if (NULL == lpData || dwSize <= 0)
		return FALSE;

	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText;
	int nRetCode = -1;

	strText = lpData;
	if (!JsonReader.parse(strText, JsonValue))
		return FALSE;

	if (!JsonValue["retcode"].isNull())
		nRetCode = JsonValue["retcode"].asInt();

	switch (nRetCode)
	{
	case 0:
		{
			for (int i = 0; i < (int)JsonValue["result"].size(); i++)
			{
				CRecvMsg * lpMsg = new CRecvMsg;
				if (lpMsg != NULL)
				{
					BOOL bRet = ParseMsg(JsonValue["result"][i], *lpMsg);
					if (!bRet || IsMsgRepeat(arrMsg, lpMsg))
					{
						delete lpMsg;
						::OutputDebugStringA("Unknown message：");
						::OutputDebugStringA(strText.c_str());
						::OutputDebugStringA("\r\n");
					}
					else
					{
						arrMsg.push_back(lpMsg);
					}
				}
			}
		}
		break;

	case 116:
		break;

	default:
		{
			::OutputDebugStringA("Unknown poll message：");
			::OutputDebugStringA(strText.c_str());
			::OutputDebugStringA("\r\n");
		}
		return FALSE;
	}

	return TRUE;
}

BOOL CRecvMsgTask::ParseMsg(Json::Value& JsonValue, CRecvMsg& msg)
{
	std::string strValue;
	tstring strPollType;

	if (JsonValue.isNull())
		return FALSE;

	if (!JsonValue["poll_type"].isNull())
	{
		strValue = JsonValue["poll_type"].asString();
		strPollType = Utf8ToUnicode(strValue);
	}

	if (CBuddyMessage::IsType(strPollType.c_str()))	// 好友消息
	{
		CBuddyMessage * lpBuddyMsg = new CBuddyMessage;
		if (NULL == lpBuddyMsg)
			return FALSE;

		BOOL bRet = lpBuddyMsg->Parse(JsonValue["value"]);
		if (!bRet)
		{
			delete lpBuddyMsg;
			return FALSE;
		}

		msg.m_nType = QQ_MSG_TYPE_BUDDY;
		msg.m_lpMsg = lpBuddyMsg;
	}
	else if (CGroupMessage::IsType(strPollType.c_str()))	// 群消息
	{
		CGroupMessage * lpGroupMsg = new CGroupMessage;
		if (NULL == lpGroupMsg)
			return FALSE;

		BOOL bRet = lpGroupMsg->Parse(JsonValue["value"]);
		if (!bRet)
		{
			delete lpGroupMsg;
			return FALSE;
		}

		msg.m_nType = QQ_MSG_TYPE_GROUP;
		msg.m_lpMsg = lpGroupMsg;
	}
	else if (CSessMessage::IsType(strPollType.c_str()))	// 临时会话消息
	{
		CSessMessage * lpSessMsg = new CSessMessage;
		if (NULL == lpSessMsg)
			return FALSE;

		BOOL bRet = lpSessMsg->Parse(JsonValue["value"]);
		if (!bRet)
		{
			delete lpSessMsg;
			return FALSE;
		}

		msg.m_nType = QQ_MSG_TYPE_SESS;
		msg.m_lpMsg = lpSessMsg;
	}
	else if (CStatusChangeMessage::IsType(strPollType.c_str()))	// 状态改变通知消息
	{
		CStatusChangeMessage * lpStatusChangeMsg = new CStatusChangeMessage;
		if (NULL == lpStatusChangeMsg)
			return FALSE;

		BOOL bRet = lpStatusChangeMsg->Parse(JsonValue["value"]);
		if (!bRet)
		{
			delete lpStatusChangeMsg;
			return FALSE;
		}

		msg.m_nType = QQ_MSG_TYPE_STATUSCHANGE;
		msg.m_lpMsg = lpStatusChangeMsg;
	}
	else if (CKickMessage::IsType(strPollType.c_str()))	// 被踢下线通知消息
	{
		CKickMessage * lpKickMsg = new CKickMessage;
		if (NULL == lpKickMsg)
			return FALSE;

		BOOL bRet = lpKickMsg->Parse(JsonValue["value"]);
		if (!bRet)
		{
			delete lpKickMsg;
			return FALSE;
		}

		msg.m_nType = QQ_MSG_TYPE_KICK;
		msg.m_lpMsg = lpKickMsg;
	}
	else if (CSysGroupMessage::IsType(strPollType.c_str()))	// 群系统消息
	{
		CSysGroupMessage * lpSysGroupMsg = new CSysGroupMessage;
		if (NULL == lpSysGroupMsg)
			return FALSE;
		
		BOOL bRet = lpSysGroupMsg->Parse(JsonValue["value"]);
		if (!bRet)
		{
			delete lpSysGroupMsg;
			return FALSE;
		}

		msg.m_nType = QQ_MSG_TYPE_SYSGROUP;
		msg.m_lpMsg = lpSysGroupMsg;
	}
	else
	{
		// Unknown message type
		return FALSE;
	}

	return TRUE;
}

BOOL CRecvMsgTask::IsMsgRepeat(std::vector<CRecvMsg *>& arrMsg, CRecvMsg * lpMsg)
{
	if (NULL == lpMsg)
		return TRUE;

	if (lpMsg->m_nType != QQ_MSG_TYPE_BUDDY 
		&& lpMsg->m_nType != QQ_MSG_TYPE_GROUP 
		&& lpMsg->m_nType != QQ_MSG_TYPE_SESS)
		return FALSE;

	UINT nMsgId = lpMsg->GetMsgId();
	UINT nMsgId2 = lpMsg->GetMsgId2();

	for (int i = 0; i < (int)arrMsg.size(); i++)
	{
		CRecvMsg * lpMsg2 = arrMsg[i];
		if (lpMsg2 != NULL && lpMsg2->GetMsgId() == nMsgId && lpMsg2->GetMsgId2() == nMsgId2)
			return TRUE;
	}

	if (m_nPreMsgId == nMsgId && m_nPreMsgId2 == nMsgId2)
		return TRUE;
	
	m_nPreMsgId =nMsgId;
	m_nPreMsgId2 = nMsgId2;

	return FALSE;
}

void CRecvMsgTask::SortMsgByTime(std::vector<CRecvMsg *>& arrMsg)
{
	CRecvMsg * lpMsg1, * lpMsg2;
	BOOL bExchange;
	int nCount;

	nCount = (int)arrMsg.size();
	for (int i = 0; i < nCount-1; i++)
	{
		bExchange = FALSE;
		for (int j = nCount-1; j > i; j--)
		{
			lpMsg1 = arrMsg[j-1];
			lpMsg2 = arrMsg[j];
			if (lpMsg1 != NULL && lpMsg2 != NULL)
			{
				if (lpMsg2->GetTime() < lpMsg1->GetTime())
				{
					arrMsg[j-1] = lpMsg2;
					arrMsg[j] = lpMsg1;
					bExchange = TRUE;
				}
			}
		}
		if (!bExchange)
			break;
	}
}

BOOL CRecvMsgTask::HandleBuddyMsg(CRecvMsg * lpRecvMsg)
{
	if (NULL == lpRecvMsg || NULL == lpRecvMsg->m_lpMsg)
		return FALSE;

	CBuddyMessage * lpMsg = (CBuddyMessage *)lpRecvMsg->m_lpMsg;

	UINT nQQNum = 0;
	tstring strNickName;

	RMT_BUDDY_DATA * lpBuddyData = GetBuddyData(lpMsg->m_nFromUin);
	if (lpBuddyData != NULL)
	{
		nQQNum = lpBuddyData->nQQNum;
		strNickName = lpBuddyData->szNickName;
	}

	WriteBuddyMsgLog(m_lpQQUser, nQQNum, strNickName.c_str(), FALSE, lpMsg);	// 写入消息记录

	if (IsNeedDownloadPic(lpMsg->m_arrContent))	// 需要下载图片
		StartGetChatPicTask(OP_TYPE_BUDDY_PIC, lpMsg);
	else
		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_BUDDY_MSG, 0, (LPARAM)lpMsg);

	return TRUE;
}

BOOL CRecvMsgTask::HandleGroupMsg(CRecvMsg * lpRecvMsg)
{
	if (NULL == lpRecvMsg || NULL == lpRecvMsg->m_lpMsg)
		return FALSE;

	CGroupMessage * lpMsg = (CGroupMessage *)lpRecvMsg->m_lpMsg;

	UINT nGroupNum = 0;
	UINT nQQNum = 0;
	tstring strNickName;

	RMT_GROUP_DATA * lpGroupData = GetGroupData(lpMsg->m_nGroupCode);
	if (lpGroupData != NULL)
		nGroupNum = lpGroupData->nGroupNum;

	RMT_BUDDY_DATA * lpBuddyData = GetGMemberData(lpMsg->m_nGroupCode, lpMsg->m_nSendUin);
	if (lpBuddyData != NULL)
	{
		nQQNum = lpBuddyData->nQQNum;
		strNickName = lpBuddyData->szNickName;
	}

	WriteGroupMsgLog(m_lpQQUser, nGroupNum, nQQNum, strNickName.c_str(), lpMsg);	// 写入消息记录

	if (IsNeedDownloadPic(lpMsg->m_arrContent))	// 需要下载图片
		StartGetChatPicTask(OP_TYPE_GROUP_PIC, lpMsg);
	else
		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_GROUP_MSG, 0, (LPARAM)lpMsg);

	return TRUE;
}

BOOL CRecvMsgTask::HandleSessMsg(CRecvMsg * lpRecvMsg)
{
	if (NULL == lpRecvMsg || NULL == lpRecvMsg->m_lpMsg)
		return FALSE;

	CSessMessage * lpMsg = (CSessMessage *)lpRecvMsg->m_lpMsg;

	UINT nQQNum = 0;
	tstring strNickName;

	UINT nGroupCode = GroupId2Code(lpMsg->m_nGroupId);				// 群标识转换到群代码
	if (nGroupCode != 0)
	{
		RMT_GROUP_DATA * lpGroupData = GetGroupData(nGroupCode);	// 确保群信息已获取

		RMT_BUDDY_DATA * lpBuddyData = GetGMemberData(nGroupCode, lpMsg->m_nFromUin);
		if (lpBuddyData != NULL)
		{
			nQQNum = lpBuddyData->nQQNum;
			strNickName = lpBuddyData->szNickName;
		}
	}

	WriteSessMsgLog(m_lpQQUser, nQQNum, strNickName.c_str(), FALSE, lpMsg);		// 写入消息记录

	if (IsNeedDownloadPic(lpMsg->m_arrContent))	// 需要下载图片
		StartGetChatPicTask(OP_TYPE_SESS_PIC, lpMsg);
	else	
		::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_SESS_MSG, 0, (LPARAM)lpMsg);

	return TRUE;
}

BOOL CRecvMsgTask::HandleStatusChangeMsg(CRecvMsg * lpRecvMsg)
{
	if (NULL == lpRecvMsg || NULL == lpRecvMsg->m_lpMsg)
		return FALSE;
	::PostMessage(m_lpQQUser->m_hProxyWnd, 
		QQ_MSG_STATUS_CHANGE_MSG, 0, (LPARAM)lpRecvMsg->m_lpMsg);
	return TRUE;
}

BOOL CRecvMsgTask::HandleKickMsg(CRecvMsg * lpRecvMsg)
{
	if (NULL == lpRecvMsg || NULL == lpRecvMsg->m_lpMsg)
		return FALSE;
	::PostMessage(m_lpQQUser->m_hProxyWnd, 
		QQ_MSG_KICK_MSG, 0, (LPARAM)lpRecvMsg->m_lpMsg);
	return TRUE;
}

BOOL CRecvMsgTask::HandleSysGroupMsg(CRecvMsg * lpRecvMsg)
{
	if (NULL == lpRecvMsg || NULL == lpRecvMsg->m_lpMsg)
		return FALSE;
	::PostMessage(m_lpQQUser->m_hProxyWnd, 
		QQ_MSG_SYS_GROUP_MSG, 0, (LPARAM)lpRecvMsg->m_lpMsg);
	return TRUE;
}

RMT_BUDDY_DATA * CRecvMsgTask::GetBuddyData(UINT nQQUin)
{
	std::map<UINT,RMT_BUDDY_DATA *>::iterator iter;
	std::pair<std::map<UINT, RMT_BUDDY_DATA *>::iterator, bool> pairInsert;
	RMT_BUDDY_DATA * lpBuddyData = NULL;
	BOOL bRet;

	iter = m_mapBuddyData.find(nQQUin);
	if (iter != m_mapBuddyData.end())
	{
		lpBuddyData = iter->second;
		if (lpBuddyData != NULL)
		{
			if (lpBuddyData->nQQNum != 0 && 
				lpBuddyData->szNickName[0] != _T('\0'))
				return lpBuddyData;
		}
		else
			m_mapBuddyData.erase(iter);
	}

	if (NULL == lpBuddyData)
	{
		lpBuddyData = new RMT_BUDDY_DATA;
		if (NULL == lpBuddyData)
			return NULL;
		memset(lpBuddyData, 0, sizeof(RMT_BUDDY_DATA));

		pairInsert = m_mapBuddyData.insert(std::pair<UINT, RMT_BUDDY_DATA *>(nQQUin, lpBuddyData));
		if (!pairInsert.second)
		{
			delete lpBuddyData;
			return NULL;
		}
	}

	::SendMessageTimeout(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GETBUDDYDATA, 
		nQQUin, (LPARAM)lpBuddyData, SMTO_BLOCK, 8000, 0);

	//::SendMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GETBUDDYDATA, nQQUin, (LPARAM)lpBuddyData);
	if (lpBuddyData->nQQNum != 0 && lpBuddyData->szNickName[0] != _T('\0'))
	{
		return lpBuddyData;
	}

	if (0 == lpBuddyData->nQQNum)
	{
		CGetQQNumResult * lpGetQQNumResult = new CGetQQNumResult;
		if (NULL == lpGetQQNumResult)
			return NULL;

		int nRetry = 3;
		for (int i = 0; i < nRetry; i++)
		{
			bRet = m_lpQQProtocol->GetQQNum(m_HttpClient, TRUE, nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetQQNumResult);
			if (bRet && 0 == lpGetQQNumResult->m_nRetCode)
				break;
		}

		if (bRet && 0 == lpGetQQNumResult->m_nRetCode)
		{
			lpBuddyData->nQQNum = lpGetQQNumResult->m_nQQNum;
			::PostMessage(m_lpQQUser->m_hProxyWnd, 
				QQ_MSG_UPDATE_BUDDY_NUMBER, 0, (LPARAM)lpGetQQNumResult);
		}
		else
		{
			delete lpGetQQNumResult;
			return NULL;
		}
	}

	if (_T('\0') == lpBuddyData->szNickName[0])
	{
		// 假定昵称一定能够从好友列表获取到，这里不处理
	}

	return lpBuddyData;
}

RMT_GROUP_DATA * CRecvMsgTask::GetGroupData(UINT nGroupCode)
{
	std::map<UINT,RMT_GROUP_DATA *>::iterator iter;
	std::pair<std::map<UINT, RMT_GROUP_DATA *>::iterator, bool> pairInsert;
	RMT_GROUP_DATA * lpGroupData = NULL;
	BOOL bRet;

	iter = m_mapGroupData.find(nGroupCode);
	if (iter != m_mapGroupData.end())
	{
		lpGroupData = iter->second;
		if (lpGroupData != NULL)
		{
			if (lpGroupData->bHasGroupInfo && 
				lpGroupData->nGroupNum != 0)
				return lpGroupData;
		}
		else
			m_mapGroupData.erase(iter);
	}

	if (NULL == lpGroupData)
	{
		lpGroupData = new RMT_GROUP_DATA;
		if (NULL == lpGroupData)
			return NULL;
		memset(lpGroupData, 0, sizeof(RMT_GROUP_DATA));

		pairInsert = m_mapGroupData.insert(std::pair<UINT, RMT_GROUP_DATA *>(nGroupCode, lpGroupData));
		if (!pairInsert.second)
		{
			delete lpGroupData;
			return NULL;
		}
	}

	::SendMessageTimeout(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GETGROUPDATA, 
		nGroupCode, (LPARAM)lpGroupData, SMTO_BLOCK, 8000, 0);

	//::SendMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GETGROUPDATA, nGroupCode, (LPARAM)lpGroupData);
	if (lpGroupData->bHasGroupInfo && lpGroupData->nGroupNum != 0)
	{
		return lpGroupData;
	}

	if (!lpGroupData->bHasGroupInfo)
	{
		CGroupInfoResult * lpGroupInfoResult = new CGroupInfoResult;
		if (NULL == lpGroupInfoResult)
			return NULL;

		int nRetry = 3;
		for (int i = 0; i < nRetry; i++)
		{
			bRet = m_lpQQProtocol->GetGroupInfo(m_HttpClient, nGroupCode, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGroupInfoResult);
			if (bRet && 0 == lpGroupInfoResult->m_nRetCode)
				break;
		}

		if (bRet && 0 == lpGroupInfoResult->m_nRetCode)
		{
			lpGroupData->bHasGroupInfo = TRUE;

			::SendMessageTimeout(m_lpQQUser->m_hProxyWnd, QQ_MSG_UPDATE_GROUP_INFO, 
				0, (LPARAM)lpGroupInfoResult, SMTO_BLOCK, 8000, 0);

			//::SendMessage(m_lpQQUser->m_hProxyWnd, 
			//	QQ_MSG_UPDATE_GROUP_INFO, 0, (LPARAM)lpGroupInfoResult);
		}
		else
		{
			delete lpGroupInfoResult;
			return NULL;
		}
	}

	if (0 == lpGroupData->nGroupNum)
	{
		CGetQQNumResult * lpGetQQNumResult = new CGetQQNumResult;
		if (NULL == lpGetQQNumResult)
			return NULL;

		int nRetry = 3;
		for (int i = 0; i < nRetry; i++)
		{
			bRet = m_lpQQProtocol->GetQQNum(m_HttpClient, FALSE, nGroupCode, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetQQNumResult);
			if (bRet && 0 == lpGetQQNumResult->m_nRetCode)
				break;
		}

		if (bRet && 0 == lpGetQQNumResult->m_nRetCode)
		{
			lpGroupData->nGroupNum = lpGetQQNumResult->m_nQQNum;
			::PostMessage(m_lpQQUser->m_hProxyWnd, 
				QQ_MSG_UPDATE_GROUP_NUMBER, nGroupCode, (LPARAM)lpGetQQNumResult);
		}
		else
		{
			delete lpGetQQNumResult;
			return NULL;
		}
	}

	return lpGroupData;
}

RMT_BUDDY_DATA * CRecvMsgTask::GetGMemberData(UINT nGroupCode, UINT nQQUin)
{
	std::map<CGMemberMapKey,RMT_BUDDY_DATA *>::iterator iter;
	std::pair<std::map<CGMemberMapKey, RMT_BUDDY_DATA *>::iterator, bool> pairInsert;
	RMT_BUDDY_DATA * lpGMemberData = NULL;
	BOOL bRet;
	
	CGMemberMapKey key;
	key.m_nGroupCode = nGroupCode;
	key.m_nQQUin = nQQUin;

	iter = m_mapGMemberData.find(key);
	if (iter != m_mapGMemberData.end())
	{
		lpGMemberData = iter->second;
		if (lpGMemberData != NULL)
		{
			if (lpGMemberData->nQQNum != 0 && 
				lpGMemberData->szNickName[0] != _T('\0'))
				return lpGMemberData;
		}
		else
			m_mapGMemberData.erase(iter);
	}

	if (NULL == lpGMemberData)
	{
		lpGMemberData = new RMT_BUDDY_DATA;
		if (NULL == lpGMemberData)
			return NULL;
		memset(lpGMemberData, 0, sizeof(RMT_BUDDY_DATA));

		pairInsert = m_mapGMemberData.insert(std::pair<CGMemberMapKey, RMT_BUDDY_DATA *>(key, lpGMemberData));
		if (!pairInsert.second)
		{
			delete lpGMemberData;
			return NULL;
		}
	}

	RMT_GMEMBER_REQ stGMemberReq = {nGroupCode, nQQUin};

	::SendMessageTimeout(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GETGMEMBERDATA, 
		(WPARAM)&stGMemberReq, (LPARAM)lpGMemberData, SMTO_BLOCK, 8000, 0);

	//::SendMessage(m_lpQQUser->m_hProxyWnd, 
	//	QQ_MSG_INTERNAL_GETGMEMBERDATA, (WPARAM)&stGMemberReq, (LPARAM)lpGMemberData);
	if (lpGMemberData->nQQNum != 0 && lpGMemberData->szNickName[0] != _T('\0'))
	{
		return lpGMemberData;
	}

	if (0 == lpGMemberData->nQQNum)
	{
		CGetQQNumResult * lpGetQQNumResult = new CGetQQNumResult;
		if (NULL == lpGetQQNumResult)
			return NULL;

		int nRetry = 3;
		for (int i = 0; i < nRetry; i++)
		{
			bRet = m_lpQQProtocol->GetQQNum(m_HttpClient, TRUE, nQQUin, 
				m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), lpGetQQNumResult);
			if (bRet && 0 == lpGetQQNumResult->m_nRetCode)
				break;
		}

		if (bRet && 0 == lpGetQQNumResult->m_nRetCode)
		{
			lpGMemberData->nQQNum = lpGetQQNumResult->m_nQQNum;
			::PostMessage(m_lpQQUser->m_hProxyWnd, 
				QQ_MSG_UPDATE_GMEMBER_NUMBER, nGroupCode, (LPARAM)lpGetQQNumResult);
		}
		else
		{
			delete lpGetQQNumResult;
			return NULL;
		}
	}

	if (_T('\0') == lpGMemberData->szNickName[0])
	{
		// 假定昵称一定能够从好友列表获取到，这里不处理
	}

	return lpGMemberData;
}

UINT CRecvMsgTask::GroupId2Code(UINT nGroupId)
{
	std::map<UINT,UINT>::iterator iter;
	std::pair<std::map<UINT,UINT>::iterator, bool> pairInsert;
	UINT nGroupCode = 0;

	iter = m_mapGroupId2Code.find(nGroupId);
	if (iter != m_mapGroupId2Code.end())
	{
		nGroupCode = iter->second;
		if (nGroupCode != 0)
			return nGroupCode;
		else
			m_mapGroupId2Code.erase(iter);
	}

	::SendMessageTimeout(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GROUPID2CODE, 
		0, nGroupId, SMTO_BLOCK, 8000, (PDWORD_PTR)&nGroupCode);

	//nGroupCode = ::SendMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_INTERNAL_GROUPID2CODE, 0, nGroupId);
	if (nGroupCode != 0)
	{
		pairInsert = m_mapGroupId2Code.insert(std::pair<UINT,UINT>(nGroupId, nGroupCode));
		if (pairInsert.second)
			return nGroupCode;
	}
	
	return 0;
}

BOOL CRecvMsgTask::IsNeedDownloadPic(std::vector<CContent *>& arrContent)
{
	for (int i = 0; i < (int)arrContent.size(); i++)
	{
		CContent * lpContent = arrContent[i];
		if (NULL == lpContent)
			continue;

		if (CONTENT_TYPE_CUSTOM_FACE == lpContent->m_nType 
			|| CONTENT_TYPE_OFF_PIC == lpContent->m_nType)
		{
			tstring strFullName = m_lpQQUser->GetChatPicFullName(lpContent->m_CFaceInfo.m_strName.c_str());
			if (!ZYM::CPath::IsFileExist(strFullName.c_str()))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CRecvMsgTask::StartGetChatPicTask(GETCHATPIC_OP_TYPE nType, void * lpMsg)
{
	CGetChatPicTask * lpGetChatPicTask = new CGetChatPicTask;
	if (NULL == lpGetChatPicTask)
		return FALSE;

	lpGetChatPicTask->m_lpQQUser = m_lpQQUser;
	lpGetChatPicTask->m_lpQQProtocol = m_lpQQProtocol;
	lpGetChatPicTask->m_nType = nType;
	lpGetChatPicTask->m_lpMsg = lpMsg;
	return m_lpThreadPool->AddTask(lpGetChatPicTask);
}