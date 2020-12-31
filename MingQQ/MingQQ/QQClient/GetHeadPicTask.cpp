#include "StdAfx.h"
#include "GetHeadPicTask.h"

CGetHeadPicTask::CGetHeadPicTask(void)
{
	m_lpQQUser = NULL;
	m_lpQQProtocol = NULL;
	m_bStop = FALSE;
}

CGetHeadPicTask::~CGetHeadPicTask(void)
{
	DelAllParams();
}

int CGetHeadPicTask::Run()
{
	GHPT_PARAM stParam;
	CBuffer bufPic;
	BOOL bRet;

	if (NULL == m_lpQQUser || NULL == m_lpQQProtocol)
	{
		DelAllParams();
		m_bStop = FALSE;
		return 0;
	}

	for (int i = 0; i < (int)m_arrParam.size(); i++)
	{
		stParam = m_arrParam[i];

		BOOL bIsBuddy;
		UINT nQQUin;
		if (GHPT_OP_TYPE_GROUP_PIC == stParam.nType)	// 群头像
		{
			bIsBuddy = FALSE;
			nQQUin = stParam.nGroupCode;
		}
		else										// 好友或群成员头像
		{
			bIsBuddy = TRUE;
			nQQUin = stParam.nQQUin;
		}

		bRet = m_lpQQProtocol->GetHeadPic(m_HttpClient, bIsBuddy, nQQUin, 
			m_lpQQUser->m_LoginResult2.m_strVfWebQq.c_str(), &bufPic);
		if (bRet)
			SavePic(stParam, bufPic.GetData(), bufPic.GetSize());

		if (m_bStop)
			break;

		if (GHPT_OP_TYPE_BUDDY_PIC == stParam.nType)			// 好友
			::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_UPDATE_BUDDY_HEADPIC, 0, stParam.nQQUin);
		else if (GHPT_OP_TYPE_GROUP_PIC == stParam.nType)		// 群
			::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_UPDATE_GROUP_HEADPIC, stParam.nGroupCode, 0);
		else if (GHPT_OP_TYPE_SESS_PIC == stParam.nType)		// 群成员
			::PostMessage(m_lpQQUser->m_hProxyWnd, QQ_MSG_UPDATE_GMEMBER_HEADPIC, stParam.nGroupCode, stParam.nQQUin);
	}

	DelAllParams();
	m_bStop = FALSE;

	return 0;
}

int CGetHeadPicTask::Stop()
{
	m_bStop = TRUE;
	m_HttpClient.SetCancalEvent();
	return 0;
}

void CGetHeadPicTask::TaskFinish()
{
	delete this;
}

BOOL CGetHeadPicTask::AddParam(GHPT_OP_TYPE nType, UINT nGroupCode, 
							   UINT nGroupNum, UINT nQQUin, UINT nQQNum)
{
	GHPT_PARAM stParam;
	stParam.nType = nType;
	stParam.nGroupCode = nGroupCode;
	stParam.nGroupNum = nGroupNum;
	stParam.nQQUin = nQQUin;
	stParam.nQQNum = nQQNum;
	m_arrParam.push_back(stParam);
	return TRUE;
}

void CGetHeadPicTask::DelAllParams()
{
	m_arrParam.clear();
}

BOOL CGetHeadPicTask::SavePic(GHPT_PARAM& stParam, const BYTE * lpData, DWORD dwSize)
{
	if (NULL == lpData || dwSize <= 0)
		return FALSE;

	tstring strFullName;
	if (GHPT_OP_TYPE_BUDDY_PIC == stParam.nType)			// 好友
		strFullName = m_lpQQUser->GetBuddyHeadPicFullName(stParam.nQQNum);
	else if (GHPT_OP_TYPE_GROUP_PIC == stParam.nType)		// 群
		strFullName = m_lpQQUser->GetGroupHeadPicFullName(stParam.nGroupNum);
	else if (GHPT_OP_TYPE_SESS_PIC == stParam.nType)		// 群成员
		strFullName = m_lpQQUser->GetSessHeadPicFullName(stParam.nQQNum);

	tstring strPath = ZYM::CPath::GetDirectoryName(strFullName.c_str());
	if (!ZYM::CPath::IsDirectoryExist(strPath.c_str()))
		ZYM::CPath::CreateDirectory(strPath.c_str(), NULL);

	FILE * fp = _tfopen(strFullName.c_str(), _T("wb"));
	if (NULL == fp)
		return FALSE;
	fwrite(lpData, dwSize, 1, fp);
	fclose(fp);
	return TRUE;
}