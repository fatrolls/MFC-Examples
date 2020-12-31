#include "StdAfx.h"
#include "QQUser.h"

CQQUser::CQQUser(void)
{
	m_hProxyWnd = NULL;
	m_hCallBackWnd = NULL;
	m_strQQNum = _T("");
	m_strQQPwd = _T("");
	m_nQQUin = 0;
	m_nLoginStatus = QQ_STATUS_ONLINE;
	m_nStatus = QQ_STATUS_OFFLINE;
	m_strVerifyCode = _T("");
	m_strUserFolder = ZYM::CPath::GetAppPath() + _T("Users\\");
}

CQQUser::~CQQUser(void)
{
}

// 获取用户文件夹存放路径
tstring CQQUser::GetUserFolder()
{
	return m_strUserFolder;
}

// 设置用户文件夹存放路径
void CQQUser::SetUserFolder(LPCTSTR lpPath)
{
	if (lpPath != NULL)
		m_strUserFolder = lpPath;
}

// 获取个人文件夹存放路径
tstring CQQUser::GetPersonalFolder(UINT nUserNum/* = 0*/)
{
	if (0 == nUserNum)
		nUserNum = m_nQQUin;

	TCHAR szPath[MAX_PATH] = {0};
	wsprintf(szPath, _T("%s%u\\"), m_strUserFolder.c_str(), nUserNum);
	return szPath;
}

// 获取聊天图片存放路径
tstring CQQUser::GetChatPicFolder(UINT nUserNum/* = 0*/)
{
	return GetPersonalFolder(nUserNum)+_T("ChatImage\\");
}

// 获取用户头像图片全路径文件名
tstring CQQUser::GetUserHeadPicFullName(UINT nUserNum/* = 0*/)
{
	TCHAR szPath[MAX_PATH] = {0};
	LPCTSTR lpFmt = _T("%s%u\\HeadImage\\Buddy\\%u.png");

	if (0 == nUserNum)
		nUserNum = m_nQQUin;

	wsprintf(szPath, lpFmt, m_strUserFolder.c_str(), nUserNum, nUserNum);
	return szPath;
}

// 获取好友头像图片全路径文件名
tstring CQQUser::GetBuddyHeadPicFullName(UINT nQQNum)
{
	TCHAR szPath[MAX_PATH] = {0};
	LPCTSTR lpFmt = _T("%s%u\\HeadImage\\Buddy\\%u.png");
	wsprintf(szPath, lpFmt, m_strUserFolder.c_str(), m_nQQUin, nQQNum);
	return szPath;
}

// 获取群头像图片全路径文件名
tstring CQQUser::GetGroupHeadPicFullName(UINT nGroupNum)
{
	TCHAR szPath[MAX_PATH] = {0};
	LPCTSTR lpFmt = _T("%s%u\\HeadImage\\Group\\%u.png");
	wsprintf(szPath, lpFmt, m_strUserFolder.c_str(), m_nQQUin, nGroupNum);
	return szPath;
}

// 获取群成员头像图片全路径文件名
tstring CQQUser::GetSessHeadPicFullName(UINT nQQNum)
{
	TCHAR szPath[MAX_PATH] = {0};
	LPCTSTR lpFmt = _T("%s%u\\HeadImage\\Sess\\%u.png");
	wsprintf(szPath, lpFmt, m_strUserFolder.c_str(), m_nQQUin, nQQNum);
	return szPath;
}

// 获取聊天图片全路径文件名
tstring CQQUser::GetChatPicFullName(LPCTSTR lpszFileName)
{
	if (NULL == lpszFileName || NULL == *lpszFileName)
		return _T("");
	return GetChatPicFolder(m_nQQUin)+lpszFileName;
}

// 获取消息记录全路径文件名
tstring CQQUser::GetMsgLogFullName(UINT nUserNum/* = 0*/)
{
	return GetPersonalFolder(nUserNum)+_T("Msg.db");
}

// 判断是否需要更新好友头像
BOOL CQQUser::IsNeedUpdateBuddyHeadPic(UINT nQQNum)
{
	tstring strFullName = GetBuddyHeadPicFullName(nQQNum);

	if (!ZYM::CPath::IsFileExist(strFullName.c_str()))
		return TRUE;

	SYSTEMTIME stLastWriteTime = {0};
	GetFileLastWriteTime(strFullName.c_str(), &stLastWriteTime);

	return ((!IsToday(&stLastWriteTime)) ? TRUE : FALSE);
}

// 判断是否需要更新群头像
BOOL CQQUser::IsNeedUpdateGroupHeadPic(UINT nGroupNum)
{
	tstring strFullName = GetGroupHeadPicFullName(nGroupNum);

	if (!ZYM::CPath::IsFileExist(strFullName.c_str()))
		return TRUE;

	SYSTEMTIME stLastWriteTime = {0};
	GetFileLastWriteTime(strFullName.c_str(), &stLastWriteTime);

	return ((!IsToday(&stLastWriteTime)) ? TRUE : FALSE);
}

// 判断是否需要更新群成员头像
BOOL CQQUser::IsNeedUpdateSessHeadPic(UINT nQQNum)
{
	tstring strFullName = GetSessHeadPicFullName(nQQNum);

	if (!ZYM::CPath::IsFileExist(strFullName.c_str()))
		return TRUE;

	SYSTEMTIME stLastWriteTime = {0};
	GetFileLastWriteTime(strFullName.c_str(), &stLastWriteTime);

	return ((!IsToday(&stLastWriteTime)) ? TRUE : FALSE);
}

// 获取服务器时间
time_t CQQUser::GetServerTime()
{
	time_t nInterval = (::GetTickCount()-m_LoginResult2.m_dwTickCount)/1000;
	return m_LoginResult2.m_nServerTime+nInterval;
}