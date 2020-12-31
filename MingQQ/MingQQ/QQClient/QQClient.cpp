#include "StdAfx.h"
#include "QQClient.h"

CQQClient::CQQClient(void)
{
}

CQQClient::~CQQClient(void)
{
}

// 初始化客户端
BOOL CQQClient::Init()
{
	BOOL bRet = CreateProxyWnd();	// 创建代理窗口
	if (!bRet)
		return FALSE;

	bRet = m_ThreadPool.Init(10);	// 初始化线程池
	if (!bRet)
		return FALSE;

	return TRUE;
}

// 反初始化客户端
void CQQClient::UnInit()
{
	m_ThreadPool.UnInit();			// 反初始化线程池
	DestroyProxyWnd();				// 销毁代理窗口
}

// 设置QQ号码和密码
void CQQClient::SetUser(LPCTSTR lpQQNum, LPCTSTR lpQQPwd)
{
	if (NULL == lpQQNum || NULL == lpQQPwd
		|| m_QQUser.m_nStatus != QQ_STATUS_OFFLINE)
		return;

	m_QQUser.m_strQQNum = lpQQNum;
	m_QQUser.m_strQQPwd = lpQQPwd;
	m_QQUser.m_nQQUin = _tcstoul(lpQQNum, NULL, 10);
	m_QQUser.m_UserInfo.m_nQQUin = m_QQUser.m_nQQUin;
	m_QQUser.m_UserInfo.m_nQQNum = m_QQUser.m_nQQUin;
	m_QQUser.m_UserInfo.m_bHasQQNum = TRUE;
}

// 设置登录状态
void CQQClient::SetLoginStatus(QQ_STATUS nStatus)
{
	m_QQUser.m_nLoginStatus = nStatus;
}

// 设置回调窗口句柄
void CQQClient::SetCallBackWnd(HWND hCallBackWnd)
{
	m_QQUser.m_hCallBackWnd = hCallBackWnd;
}

// 设置验证码
void CQQClient::SetVerifyCode(LPCTSTR lpVerifyCode)
{
	if (lpVerifyCode != NULL)
		m_QQUser.m_strVerifyCode = lpVerifyCode;
}

// 登录
BOOL CQQClient::Login()
{
	if (!IsOffline() || m_QQUser.m_strQQNum.empty() || m_QQUser.m_strQQPwd.empty())
		return FALSE;
	
	if (m_LoginTask.IsRunning())
		return FALSE;

	m_LoginTask.m_lpQQUser = &m_QQUser;
	m_LoginTask.m_lpQQProtocol = &m_QQProtocol;
	m_LoginTask.m_lpThreadPool = &m_ThreadPool;
	m_LoginTask.m_lpPollTask = &m_PollTask;
	m_LoginTask.m_lpRecvMsgTask = &m_RecvMsgTask;
	m_LoginTask.m_lpSendMsgTask = &m_SendMsgTask;

	return m_ThreadPool.AddTask(&m_LoginTask);
}

// 注销
BOOL CQQClient::Logout()
{
	if (IsOffline())
		return FALSE;

	m_LogoutTask.m_lpQQUser = &m_QQUser;
	m_LogoutTask.m_lpQQProtocol = &m_QQProtocol;
	return m_ThreadPool.AddTask(&m_LogoutTask);
}

// 取消登录
void CQQClient::CancelLogin()
{
	m_ThreadPool.RemoveAllTask();
}

// 改变在线状态
void CQQClient::ChangeStatus(QQ_STATUS nStatus)
{
	if (IsOffline())
		return;

	CChangeStatusTask * lpChangeStatusTask = new CChangeStatusTask;
	if (lpChangeStatusTask != NULL)
	{
		lpChangeStatusTask->m_lpQQUser = &m_QQUser;
		lpChangeStatusTask->m_lpQQProtocol = &m_QQProtocol;
		lpChangeStatusTask->m_nStatus = nStatus;
		m_ThreadPool.AddTask(lpChangeStatusTask);
	}
}

// 更新好友列表
void CQQClient::UpdateBuddyList()
{
	if (IsOffline())
		return;
}

// 更新群列表
void CQQClient::UpdateGroupList()
{
	if (IsOffline())
		return;
}

// 更新最近联系人列表
void CQQClient::UpdateRecentList()
{
	if (IsOffline())
		return;
}

// 更新好友信息
void CQQClient::UpdateBuddyInfo(UINT nQQUin)
{
	if (IsOffline())
		return;

	CInfoTask * lpInfoTask = new CInfoTask;
	if (lpInfoTask != NULL)
	{
		lpInfoTask->m_lpQQUser = &m_QQUser;
		lpInfoTask->m_lpQQProtocol = &m_QQProtocol;
		lpInfoTask->m_nType = OP_TYPE_GETBUDDYINFO;
		lpInfoTask->m_nGroupCode = 0;
		lpInfoTask->m_nQQUin = nQQUin;
		m_ThreadPool.AddTask(lpInfoTask);
	}
}

// 更新群成员信息
void CQQClient::UpdateGroupMemberInfo(UINT nGroupCode, UINT nQQUin)
{
	if (IsOffline())
		return;

	CInfoTask * lpInfoTask = new CInfoTask;
	if (lpInfoTask != NULL)
	{
		lpInfoTask->m_lpQQUser = &m_QQUser;
		lpInfoTask->m_lpQQProtocol = &m_QQProtocol;
		lpInfoTask->m_nType = OP_TYPE_GETGMEMBERINFO;
		lpInfoTask->m_nGroupCode = nGroupCode;
		lpInfoTask->m_nQQUin = nQQUin;
		m_ThreadPool.AddTask(lpInfoTask);
	}
}

// 更新群信息
void CQQClient::UpdateGroupInfo(UINT nGroupCode)
{
	if (IsOffline())
		return;

	CInfoTask * lpInfoTask = new CInfoTask;
	if (lpInfoTask != NULL)
	{
		lpInfoTask->m_lpQQUser = &m_QQUser;
		lpInfoTask->m_lpQQProtocol = &m_QQProtocol;
		lpInfoTask->m_nType = OP_TYPE_GETGROUPINFO;
		lpInfoTask->m_nGroupCode = nGroupCode;
		lpInfoTask->m_nQQUin = 0;
		m_ThreadPool.AddTask(lpInfoTask);
	}
}

// 更新好友号码
void CQQClient::UpdateBuddyNum(UINT nQQUin)
{
	if (IsOffline())
		return;

	CQQNumTask * lpQQNumTask = new CQQNumTask;
	if (lpQQNumTask != NULL)
	{
		lpQQNumTask->m_lpQQUser = &m_QQUser;
		lpQQNumTask->m_lpQQProtocol = &m_QQProtocol;
		lpQQNumTask->AddParam(OP_TYPE_GETBUDDYNUM, 0, nQQUin);
		m_ThreadPool.AddTask(lpQQNumTask);
	}
}

// 更新群成员号码
void CQQClient::UpdateGroupMemberNum(UINT nGroupCode, UINT nQQUin)
{
	if (IsOffline())
		return;

	CQQNumTask * lpQQNumTask = new CQQNumTask;
	if (lpQQNumTask != NULL)
	{
		lpQQNumTask->m_lpQQUser = &m_QQUser;
		lpQQNumTask->m_lpQQProtocol = &m_QQProtocol;
		lpQQNumTask->AddParam(OP_TYPE_GETGMEMBERNUM, nGroupCode, nQQUin);
		m_ThreadPool.AddTask(lpQQNumTask);
	}
}

// 更新群成员号码
void CQQClient::UpdateGroupMemberNum(UINT nGroupCode, std::vector<UINT> * arrQQUin)
{
	if (QQ_STATUS_OFFLINE == m_QQUser.m_nStatus
		|| NULL == arrQQUin || (int)arrQQUin->size() <= 0)
		return;

	CQQNumTask * lpQQNumTask = new CQQNumTask;
	if (lpQQNumTask != NULL)
	{
		lpQQNumTask->m_lpQQUser = &m_QQUser;
		lpQQNumTask->m_lpQQProtocol = &m_QQProtocol;
		for (int i = 0; i < (int)arrQQUin->size(); i++)
		{
			lpQQNumTask->AddParam(OP_TYPE_GETGMEMBERNUM, nGroupCode, arrQQUin->at(i));
		}
		m_ThreadPool.AddTask(lpQQNumTask);
	}
}

// 更新群号码
void CQQClient::UpdateGroupNum(UINT nGroupCode)
{
	if (IsOffline())
		return;

	CQQNumTask * lpQQNumTask = new CQQNumTask;
	if (lpQQNumTask != NULL)
	{
		lpQQNumTask->m_lpQQUser = &m_QQUser;
		lpQQNumTask->m_lpQQProtocol = &m_QQProtocol;
		lpQQNumTask->AddParam(OP_TYPE_GETGROUPNUM, nGroupCode, 0);
		m_ThreadPool.AddTask(lpQQNumTask);
	}
}

// 更新好友个性签名
void CQQClient::UpdateBuddySign(UINT nQQUin)
{
	if (IsOffline())
		return;

	CQQSignTask * lpQQSignTask = new CQQSignTask;
	if (NULL == lpQQSignTask)
		return;

	lpQQSignTask->m_lpQQUser = &m_QQUser;
	lpQQSignTask->m_lpQQProtocol = &m_QQProtocol;
	lpQQSignTask->m_nType = QQSIGN_OP_TYPE_GET;
	lpQQSignTask->AddGetParam(FALSE, 0, nQQUin);
	m_ThreadPool.AddTask(lpQQSignTask);
}

// 更新群成员个性签名
void CQQClient::UpdateGroupMemberSign(UINT nGroupCode, UINT nQQUin)
{
	if (IsOffline())
		return;

	CQQSignTask * lpQQSignTask = new CQQSignTask;
	if (NULL == lpQQSignTask)
		return;

	lpQQSignTask->m_lpQQUser = &m_QQUser;
	lpQQSignTask->m_lpQQProtocol = &m_QQProtocol;
	lpQQSignTask->m_nType = QQSIGN_OP_TYPE_GET;
	lpQQSignTask->AddGetParam(TRUE, nGroupCode, nQQUin);
	m_ThreadPool.AddTask(lpQQSignTask);
}

// 修改QQ个性签名
void CQQClient::ModifyQQSign(LPCTSTR lpSign)
{
	if (IsOffline())
		return;

	if (NULL == lpSign)
		return;

	CQQSignTask * lpQQSignTask = new CQQSignTask;
	if (NULL == lpQQSignTask)
		return;

	lpQQSignTask->m_lpQQUser = &m_QQUser;
	lpQQSignTask->m_lpQQProtocol = &m_QQProtocol;
	lpQQSignTask->m_nType = QQSIGN_OP_TYPE_SET;
	lpQQSignTask->AddSetParam(lpSign);
	m_ThreadPool.AddTask(lpQQSignTask);
}

// 更新好友头像
void CQQClient::UpdateBuddyHeadPic(UINT nQQUin, UINT nQQNum)
{
	if (IsOffline())
		return;

	CGetHeadPicTask * lpGetHeadPicTask = new CGetHeadPicTask;
	if (NULL == lpGetHeadPicTask)
		return;

	lpGetHeadPicTask->m_lpQQUser = &m_QQUser;
	lpGetHeadPicTask->m_lpQQProtocol = &m_QQProtocol;
	lpGetHeadPicTask->AddParam(GHPT_OP_TYPE_BUDDY_PIC, 0, 0, nQQUin, nQQNum);
	m_ThreadPool.AddTask(lpGetHeadPicTask);
}

// 更新群成员头像
void CQQClient::UpdateGroupMemberHeadPic(UINT nGroupCode, UINT nQQUin, UINT nQQNum)
{
	if (IsOffline())
		return;

	CGetHeadPicTask * lpGetHeadPicTask = new CGetHeadPicTask;
	if (NULL == lpGetHeadPicTask)
		return;

	lpGetHeadPicTask->m_lpQQUser = &m_QQUser;
	lpGetHeadPicTask->m_lpQQProtocol = &m_QQProtocol;
	lpGetHeadPicTask->AddParam(GHPT_OP_TYPE_SESS_PIC, nGroupCode, 0, nQQUin, nQQNum);
	m_ThreadPool.AddTask(lpGetHeadPicTask);
}

// 更新群头像
void CQQClient::UpdateGroupHeadPic(UINT nGroupCode, UINT nGroupNum)
{
	if (IsOffline())
		return;

	CGetHeadPicTask * lpGetHeadPicTask = new CGetHeadPicTask;
	if (NULL == lpGetHeadPicTask)
		return;

	lpGetHeadPicTask->m_lpQQUser = &m_QQUser;
	lpGetHeadPicTask->m_lpQQProtocol = &m_QQProtocol;
	lpGetHeadPicTask->AddParam(GHPT_OP_TYPE_GROUP_PIC, nGroupCode, nGroupNum, 0,  0);
	m_ThreadPool.AddTask(lpGetHeadPicTask);
}

// 更新群表情信令
void CQQClient::UpdateGroupFaceSignal()
{
	if (IsOffline())
		return;

	CGetGroupFaceSigTask * lpGetGroupFaceSigTask = new CGetGroupFaceSigTask;
	if (NULL == lpGetGroupFaceSigTask)
		return;

	lpGetGroupFaceSigTask->m_lpQQUser = &m_QQUser;
	lpGetGroupFaceSigTask->m_lpQQProtocol = &m_QQProtocol;
	m_ThreadPool.AddTask(lpGetGroupFaceSigTask);
}

// 发送好友消息
BOOL CQQClient::SendBuddyMsg(UINT nToUin, time_t nTime, LPCTSTR lpMsg)
{
	if (IsOffline())
		return FALSE;

	return m_SendMsgTask.AddBuddyMsg(nToUin, nTime, lpMsg);
}

// 发送群消息
BOOL CQQClient::SendGroupMsg(UINT nGroupId, time_t nTime, LPCTSTR lpMsg)
{
	if (IsOffline())
		return FALSE;

	return m_SendMsgTask.AddGroupMsg(nGroupId, nTime, lpMsg);
}

// 发送临时会话消息
BOOL CQQClient::SendSessMsg(UINT nGroupId, UINT nToUin, time_t nTime, LPCTSTR lpMsg)
{
	if (IsOffline())
		return FALSE;

	return m_SendMsgTask.AddSessMsg(nGroupId, nToUin, nTime, lpMsg);
}

// 是否离线状态
BOOL CQQClient::IsOffline()
{
	return (QQ_STATUS_OFFLINE == m_QQUser.m_nStatus) ? TRUE : FALSE;
}

// 获取在线状态
QQ_STATUS CQQClient::GetStatus()
{
	return m_QQUser.m_nStatus;
}

// 获取验证码图片
BOOL CQQClient::GetVerifyCodePic(const BYTE *& lpData, DWORD& dwSize)
{
	lpData = m_QQUser.m_VerifyCodePic.GetData();
	dwSize = m_QQUser.m_VerifyCodePic.GetSize();

	if (lpData != NULL && dwSize > 0)
	{
		return TRUE;
	}
	else
	{
		lpData = NULL;
		dwSize = 0;
		return FALSE;
	}
}

// 获取用户信息
CBuddyInfo * CQQClient::GetUserInfo()
{
	return &m_QQUser.m_UserInfo;
}

// 获取好友列表
CBuddyList * CQQClient::GetBuddyList()
{
	return &m_QQUser.m_BuddyList;
}

// 获取群列表
CGroupList * CQQClient::GetGroupList()
{
	return &m_QQUser.m_GroupList;
}

// 获取最近联系人列表
CRecentList * CQQClient::GetRecentList()
{
	return &m_QQUser.m_RecentList;
}

// 获取消息列表
CMessageList * CQQClient::GetMessageList()
{
	return &m_QQUser.m_MsgList;
}

// 获取消息记录管理器
CMessageLogger * CQQClient::GetMsgLogger()
{
	return &m_QQUser.m_MsgLogger;
}

// 获取用户文件夹存放路径
tstring CQQClient::GetUserFolder()
{
	return m_QQUser.GetUserFolder();
}

// 设置用户文件夹存放路径
void CQQClient::SetUserFolder(LPCTSTR lpPath)
{
	return m_QQUser.SetUserFolder(lpPath);
}

// 获取个人文件夹存放路径
tstring CQQClient::GetPersonalFolder(UINT nUserNum/* = 0*/)
{
	return m_QQUser.GetPersonalFolder(nUserNum);
}

// 获取聊天图片存放路径
tstring CQQClient::GetChatPicFolder(UINT nUserNum/* = 0*/)
{
	return m_QQUser.GetChatPicFolder(nUserNum);
}

// 获取用户头像图片全路径文件名
tstring CQQClient::GetUserHeadPicFullName(UINT nUserNum/* = 0*/)
{
	return m_QQUser.GetUserHeadPicFullName(nUserNum);
}

// 获取好友头像图片全路径文件名
tstring CQQClient::GetBuddyHeadPicFullName(UINT nQQNum)
{
	return m_QQUser.GetBuddyHeadPicFullName(nQQNum);
}

// 获取群头像图片全路径文件名
tstring CQQClient::GetGroupHeadPicFullName(UINT nGroupNum)
{
	return m_QQUser.GetGroupHeadPicFullName(nGroupNum);
}

// 获取群成员头像图片全路径文件名
tstring CQQClient::GetSessHeadPicFullName(UINT nQQNum)
{
	return m_QQUser.GetSessHeadPicFullName(nQQNum);
}

// 获取聊天图片全路径文件名
tstring CQQClient::GetChatPicFullName(LPCTSTR lpszFileName)
{
	return m_QQUser.GetChatPicFullName(lpszFileName);
}

// 获取消息记录全路径文件名
tstring CQQClient::GetMsgLogFullName(UINT nUserNum/* = 0*/)
{
	return m_QQUser.GetMsgLogFullName(nUserNum);
}

// 判断是否需要更新好友头像
BOOL CQQClient::IsNeedUpdateBuddyHeadPic(UINT nQQNum)
{
	return m_QQUser.IsNeedUpdateBuddyHeadPic(nQQNum);
}

// 判断是否需要更新群头像
BOOL CQQClient::IsNeedUpdateGroupHeadPic(UINT nGroupNum)
{
	return m_QQUser.IsNeedUpdateGroupHeadPic(nGroupNum);
}

// 判断是否需要更新群成员头像
BOOL CQQClient::IsNeedUpdateSessHeadPic(UINT nQQNum)
{
	return m_QQUser.IsNeedUpdateSessHeadPic(nQQNum);
}

// 获取服务器时间
time_t CQQClient::GetServerTime()
{
	return m_QQUser.GetServerTime();
}

void CQQClient::OnUpdateBuddyList(UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = FALSE;
	CBuddyListResult * lpBuddyListResult = (CBuddyListResult *)lParam;
	if (lpBuddyListResult != NULL)
	{
		for (int i = 0; i < (int)lpBuddyListResult->m_arrBuddyTeamInfo.size(); i++)
		{
			CBuddyTeamInfo * lpBuddyTeamInfo = lpBuddyListResult->m_arrBuddyTeamInfo[i];
			if (lpBuddyTeamInfo != NULL)
				m_QQUser.m_BuddyList.AddBuddyTeam(lpBuddyTeamInfo);
		}
		lpBuddyListResult->m_arrBuddyTeamInfo.clear();
		delete lpBuddyListResult;
		bSuccess = TRUE;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, NULL, bSuccess);
}

void CQQClient::OnUpdateGroupList(UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = FALSE;
	CGroupListResult * lpGroupListResult = (CGroupListResult *)lParam;
	if (lpGroupListResult != NULL)
	{
		for (int i = 0; i < (int)lpGroupListResult->m_arrGroupInfo.size(); i++)
		{
			CGroupInfo * lpGroupInfo = lpGroupListResult->m_arrGroupInfo[i];
			if (lpGroupInfo != NULL)
				m_QQUser.m_GroupList.AddGroup(lpGroupInfo);
		}
		lpGroupListResult->m_arrGroupInfo.clear();
		delete lpGroupListResult;
		bSuccess = TRUE;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, NULL, bSuccess);
}

void CQQClient::OnUpdateRecentList(UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = FALSE;
	CRecentListResult * lpRecentListResult = (CRecentListResult *)lParam;
	if (lpRecentListResult != NULL)
	{
		for (int i = 0; i < (int)lpRecentListResult->m_arrRecentInfo.size(); i++)
		{
			CRecentInfo * lpRecentInfo = lpRecentListResult->m_arrRecentInfo[i];
			if (lpRecentInfo != NULL)
				m_QQUser.m_RecentList.AddRecent(lpRecentInfo);
		}
		lpRecentListResult->m_arrRecentInfo.clear();
		delete lpRecentListResult;
		bSuccess = TRUE;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, NULL, bSuccess);
}

void CQQClient::OnBuddyMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	CBuddyMessage * lpBuddyMsg = (CBuddyMessage *)lParam;
	if (NULL == lpBuddyMsg)
		return;
	
	UINT nQQUin = lpBuddyMsg->m_nFromUin;
	UINT nMsgId = lpBuddyMsg->m_nMsgId;

	m_QQUser.m_MsgList.AddMsg(QQ_MSG_TYPE_BUDDY, 
		lpBuddyMsg->m_nFromUin, 0, (void *)lpBuddyMsg);

	::SendMessage(m_QQUser.m_hCallBackWnd, message, nQQUin, nMsgId);
}

void CQQClient::OnGroupMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	CGroupMessage * lpGroupMsg = (CGroupMessage *)lParam;
	if (NULL == lpGroupMsg)
		return;
	
	UINT nGroupCode = lpGroupMsg->m_nGroupCode;
	UINT nMsgId = lpGroupMsg->m_nMsgId;

	m_QQUser.m_MsgList.AddMsg(QQ_MSG_TYPE_GROUP, 
		lpGroupMsg->m_nGroupCode, lpGroupMsg->m_nGroupCode, (void *)lpGroupMsg);

	::SendMessage(m_QQUser.m_hCallBackWnd, message, nGroupCode, nMsgId);
}

void CQQClient::OnSessMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	CSessMessage * lpSessMsg = (CSessMessage *)lParam;
	if (NULL == lpSessMsg)
		return;
	
	UINT nQQUin = lpSessMsg->m_nFromUin;
	UINT nMsgId = lpSessMsg->m_nMsgId;
	UINT nGroupCode = 0;

	CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupById(lpSessMsg->m_nGroupId);
	if (lpGroupInfo != NULL)
	{
		nGroupCode = lpGroupInfo->m_nGroupCode;
		CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByUin(lpSessMsg->m_nFromUin);
		if (NULL == lpBuddyInfo)
		{
			lpBuddyInfo = new CBuddyInfo;
			if (lpBuddyInfo != NULL)
			{
				lpBuddyInfo->Reset();
				lpBuddyInfo->m_nQQUin = lpSessMsg->m_nFromUin;
				lpBuddyInfo->m_nQQNum = lpSessMsg->m_nQQNum;
				lpGroupInfo->m_arrMember.push_back(lpBuddyInfo);
			}
			UpdateGroupMemberInfo(nGroupCode, lpSessMsg->m_nFromUin);
		}
	}

	m_QQUser.m_MsgList.AddMsg(QQ_MSG_TYPE_SESS, 
		lpSessMsg->m_nFromUin, nGroupCode, (void *)lpSessMsg);

	::SendMessage(m_QQUser.m_hCallBackWnd, message, nQQUin, nMsgId);
}

void CQQClient::OnSysGroupMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	CSysGroupMessage * lpSysGroupMsg = (CSysGroupMessage *)lParam;
	if (NULL == lpSysGroupMsg)
		return;

	UINT nGroupCode = lpSysGroupMsg->m_nGroupCode;

	m_QQUser.m_MsgList.AddMsg(QQ_MSG_TYPE_SYSGROUP, lpSysGroupMsg->m_nGroupCode, 
		lpSysGroupMsg->m_nGroupCode, (void *)lpSysGroupMsg);

	::SendMessage(m_QQUser.m_hCallBackWnd, message, 0, nGroupCode);
}

void CQQClient::OnStatusChangeMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = 0;
	CStatusChangeMessage * lpStatusChangeMsg = (CStatusChangeMessage *)lParam;
	if (NULL == lpStatusChangeMsg)
		return;
	
	nQQUin = lpStatusChangeMsg->m_nQQUin;
	CBuddyInfo * lpBuddyInfo = m_QQUser.m_BuddyList.GetBuddy(nQQUin);
	if (lpBuddyInfo != NULL)
	{
		lpBuddyInfo->m_nStatus = lpStatusChangeMsg->m_nStatus;
		lpBuddyInfo->m_nClientType = lpStatusChangeMsg->m_nClientType;
		CBuddyTeamInfo * lpBuddyTeamInfo = m_QQUser.m_BuddyList.GetBuddyTeam(lpBuddyInfo->m_nTeamIndex);
		if (lpBuddyTeamInfo != NULL)
			lpBuddyTeamInfo->Sort();
	}
	delete lpStatusChangeMsg;
	::SendMessage(m_QQUser.m_hCallBackWnd, message, 0, nQQUin);
}

void CQQClient::OnKickMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	CKickMessage * lpKickMsg = (CKickMessage *)lParam;
	if (NULL == lpKickMsg)
		return;
	
	delete lpKickMsg;
	m_QQUser.m_nStatus = QQ_STATUS_OFFLINE;
	m_ThreadPool.RemoveAllTask();
	::SendMessage(m_QQUser.m_hCallBackWnd, QQ_MSG_KICK_MSG, 0, 0);
}

void CQQClient::OnUpdateBuddyNumber(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = 0;
	CGetQQNumResult * lpGetQQNumResult = (CGetQQNumResult *)lParam;
	if (lpGetQQNumResult != NULL)
	{
		nQQUin = lpGetQQNumResult->m_nQQUin;
		CBuddyInfo * lpBuddyInfo = m_QQUser.m_BuddyList.GetBuddy(nQQUin);
		if (lpBuddyInfo != NULL)
			lpBuddyInfo->SetQQNum(lpGetQQNumResult);
		delete lpGetQQNumResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, 0, nQQUin);
}

void CQQClient::OnUpdateGMemberNumber(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = 0;
	CGetQQNumResult * lpGetQQNumResult = (CGetQQNumResult *)lParam;
	if (nGroupCode != 0 && lpGetQQNumResult != NULL)
	{
		nQQUin = lpGetQQNumResult->m_nQQUin;
		CBuddyInfo * lpBuddyInfo = m_QQUser.m_GroupList.GetGroupMemberByCode(nGroupCode, nQQUin);
		if (lpBuddyInfo != NULL)
			lpBuddyInfo->SetQQNum(lpGetQQNumResult);
		delete lpGetQQNumResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, nGroupCode, nQQUin);
}

void CQQClient::OnUpdateGroupNumber(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	CGetQQNumResult * lpGetQQNumResult = (CGetQQNumResult *)lParam;
	if (nGroupCode != 0 && lpGetQQNumResult != NULL)
	{
		CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupByCode(nGroupCode);
		if (lpGroupInfo != NULL)
			lpGroupInfo->SetGroupNumber(lpGetQQNumResult);
		delete lpGetQQNumResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, 0, nGroupCode);
}

void CQQClient::OnUpdateBuddySign(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = 0;
	CGetSignResult * lpGetSignResult = (CGetSignResult *)lParam;
	if (lpGetSignResult != NULL)
	{
		nQQUin = lpGetSignResult->m_nQQUin;
		if (m_QQUser.m_UserInfo.m_nQQUin == nQQUin)		// 更新用户个性签名
		{
			m_QQUser.m_UserInfo.SetQQSign(lpGetSignResult);
		}
		else											// 更新好友个性签名
		{
			CBuddyInfo * lpBuddyInfo = m_QQUser.m_BuddyList.GetBuddy(nQQUin);
			if (lpBuddyInfo != NULL)
				lpBuddyInfo->SetQQSign(lpGetSignResult);
		}
		delete lpGetSignResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, NULL, nQQUin);
}

void CQQClient::OnUpdateGMemberSign(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = 0;
	CGetSignResult * lpGetSignResult = (CGetSignResult *)lParam;

	if (nGroupCode != 0 && lpGetSignResult != NULL)
	{
		nQQUin = lpGetSignResult->m_nQQUin;
		CBuddyInfo * lpBuddyInfo = m_QQUser.m_GroupList.GetGroupMemberByCode(nGroupCode, nQQUin);
		if (lpBuddyInfo != NULL)
			lpBuddyInfo->SetQQSign(lpGetSignResult);
		delete lpGetSignResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, nGroupCode, nQQUin);
}

void CQQClient::OnUpdateBuddyInfo(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = 0;
	CBuddyInfoResult * lpBuddyInfoResult = (CBuddyInfoResult *)lParam;
	if (lpBuddyInfoResult != NULL)
	{
		nQQUin = lpBuddyInfoResult->m_nQQUin;

		if (m_QQUser.m_UserInfo.m_nQQUin == nQQUin)	// 更新用户信息
		{
			m_QQUser.m_UserInfo.SetBuddyInfo(lpBuddyInfoResult);
		}
		else										// 更新好友信息
		{
			CBuddyInfo * lpBuddyInfo = m_QQUser.m_BuddyList.GetBuddy(nQQUin);
			if (lpBuddyInfo != NULL)
				lpBuddyInfo->SetBuddyInfo(lpBuddyInfoResult);
		}
		delete lpBuddyInfoResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, NULL, nQQUin);
}

void CQQClient::OnUpdateGMemberInfo(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = 0;
	CBuddyInfoResult * lpBuddyInfoResult = (CBuddyInfoResult *)lParam;

	if (nGroupCode != 0 && lpBuddyInfoResult != NULL)
	{
		nQQUin = lpBuddyInfoResult->m_nQQUin;
		CBuddyInfo * lpBuddyInfo = m_QQUser.m_GroupList.GetGroupMemberByCode(nGroupCode, nQQUin);
		if (lpBuddyInfo != NULL)
			lpBuddyInfo->SetBuddyInfo(lpBuddyInfoResult);
		delete lpBuddyInfoResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, nGroupCode, nQQUin);
}

void CQQClient::OnUpdateGroupInfo(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = 0;
	CGroupInfoResult * lpGroupInfoResult = (CGroupInfoResult *)lParam;
	if (lpGroupInfoResult != NULL)
	{
		nGroupCode = lpGroupInfoResult->m_nGroupCode;
		CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupByCode(nGroupCode);
		if (lpGroupInfo != NULL)
			lpGroupInfo->SetGroupInfo(lpGroupInfoResult);
		delete lpGroupInfoResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, 0, nGroupCode);
}

void CQQClient::OnUpdateC2CMsgSig(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupId = 0;
	UINT nQQUin = 0;
	CGetC2CMsgSigResult * lpGetC2CMsgSigResult = (CGetC2CMsgSigResult *)lParam;
	if (lpGetC2CMsgSigResult != NULL)
	{
		nGroupId = lpGetC2CMsgSigResult->m_nGroupId;
		nQQUin = lpGetC2CMsgSigResult->m_nQQUin;
		CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupById(nGroupId);
		if (lpGroupInfo != NULL)
		{
			CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByUin(nQQUin);
			if (lpBuddyInfo != NULL)
				lpBuddyInfo->m_strGroupSig = lpGetC2CMsgSigResult->m_strValue;
		}
		delete lpGetC2CMsgSigResult;
	}
	::SendMessage(m_QQUser.m_hCallBackWnd, message, nGroupId, nQQUin);
}

void CQQClient::OnChangeStatusResult(UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)wParam;
	QQ_STATUS nNewStatus = (QQ_STATUS)lParam;

	if (bSuccess)
		m_QQUser.m_nStatus = nNewStatus;

	::SendMessage(m_QQUser.m_hCallBackWnd, message, wParam, lParam);
}

void CQQClient::OnInternal_GetBuddyData(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = (UINT)wParam;
	RMT_BUDDY_DATA * lpBuddyData = (RMT_BUDDY_DATA *)lParam;
	if (NULL == lpBuddyData)
		return;

	CBuddyInfo * lpBuddyInfo = m_QQUser.m_BuddyList.GetBuddy(nQQUin);
	if (NULL == lpBuddyInfo)
		return;

	lpBuddyData->nQQNum = lpBuddyInfo->m_nQQNum;

	int nMaxCnt = sizeof(lpBuddyData->szNickName) / sizeof(TCHAR);
	if (!lpBuddyInfo->m_strMarkName.empty())
		_tcsncpy(lpBuddyData->szNickName, lpBuddyInfo->m_strMarkName.c_str(), nMaxCnt);
	else
		_tcsncpy(lpBuddyData->szNickName, lpBuddyInfo->m_strNickName.c_str(), nMaxCnt);
	lpBuddyData->szNickName[nMaxCnt-1] = _T('\0');
}

void CQQClient::OnInternal_GetGroupData(UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	RMT_GROUP_DATA * lpGroupData = (RMT_GROUP_DATA *)lParam;
	if (NULL == lpGroupData)
		return;

	CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupByCode(nGroupCode);
	if (NULL == lpGroupInfo)
		return;

	lpGroupData->bHasGroupInfo = lpGroupInfo->m_bHasGroupInfo;
	lpGroupData->nGroupNum = lpGroupInfo->m_nGroupNumber;
}

void CQQClient::OnInternal_GetGMemberData(UINT message, WPARAM wParam, LPARAM lParam)
{
	RMT_GMEMBER_REQ * lpGMemberReq = (RMT_GMEMBER_REQ *)wParam;
	RMT_BUDDY_DATA * lpGMemberData = (RMT_BUDDY_DATA *)lParam;
	if (NULL == lpGMemberReq || NULL == lpGMemberData)
		return;

	CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupByCode(lpGMemberReq->nGroupCode);
	if (NULL == lpGroupInfo)
		return;

	CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByUin(lpGMemberReq->nQQUin);
	if (NULL == lpBuddyInfo)
		return;

	lpGMemberData->nQQNum = lpBuddyInfo->m_nQQNum;

	int nMaxCnt = sizeof(lpGMemberData->szNickName) / sizeof(TCHAR);
	if (!lpBuddyInfo->m_strGroupCard.empty())
		_tcsncpy(lpGMemberData->szNickName, lpBuddyInfo->m_strGroupCard.c_str(), nMaxCnt);
	else
		_tcsncpy(lpGMemberData->szNickName, lpBuddyInfo->m_strNickName.c_str(), nMaxCnt);
	lpGMemberData->szNickName[nMaxCnt-1] = _T('\0');
}

UINT CQQClient::OnInternal_GroupId2Code(UINT message, WPARAM wParam, LPARAM lParam)
{
	CGroupInfo * lpGroupInfo = m_QQUser.m_GroupList.GetGroupById(lParam);
	return ((lpGroupInfo != NULL) ? lpGroupInfo->m_nGroupCode : 0);
}

// 创建代理窗口
BOOL CQQClient::CreateProxyWnd()
{
	WNDCLASSEX wcex;
	LPCTSTR szWindowClass = _T("MINGQQ_PROXY_WND");
	HWND hWnd;

	DestroyProxyWnd();	// 销毁代理窗口

	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ProxyWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	if (!::RegisterClassEx(&wcex))
		return FALSE;

	hWnd = ::CreateWindow(szWindowClass, NULL, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
		return FALSE;

	::SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
	m_QQUser.m_hProxyWnd = hWnd;

	return TRUE;
}

// 销毁代理窗口
BOOL CQQClient::DestroyProxyWnd()
{
	if (m_QQUser.m_hProxyWnd != NULL)
	{
		::DestroyWindow(m_QQUser.m_hProxyWnd);
		m_QQUser.m_hProxyWnd = NULL;
	}
	return TRUE;
}

LRESULT CALLBACK CQQClient::ProxyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CQQClient * lpQQClient = (CQQClient *)::GetWindowLong(hWnd, GWL_USERDATA);
	if (NULL == lpQQClient)
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	if (message < QQ_MSG_FIRST || message > QQ_MSG_LAST)
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case QQ_MSG_LOGIN_RESULT:			// 登录返回消息
	case QQ_MSG_LOGOUT_RESULT:			// 注销返回消息
	case QQ_MSG_UPDATE_USER_INFO:		// 更新用户信息
	case QQ_MSG_UPDATE_BUDDY_HEADPIC:	// 更新好友头像
	case QQ_MSG_UPDATE_GMEMBER_HEADPIC:	// 更新群成员头像
	case QQ_MSG_UPDATE_GROUP_HEADPIC:	// 更新群头像
		::SendMessage(lpQQClient->m_QQUser.m_hCallBackWnd, message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_BUDDY_LIST:		// 更新好友列表消息
		lpQQClient->OnUpdateBuddyList(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_GROUP_LIST:		// 更新群列表消息
		lpQQClient->OnUpdateGroupList(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_RECENT_LIST:		// 更新最近联系人列表消息
		lpQQClient->OnUpdateRecentList(message, wParam, lParam);
		break;
	case QQ_MSG_BUDDY_MSG:				// 好友消息
		lpQQClient->OnBuddyMsg(message, wParam, lParam);
		break;
	case QQ_MSG_GROUP_MSG:				// 群消息
		lpQQClient->OnGroupMsg(message, wParam, lParam);
		break;
	case QQ_MSG_SESS_MSG:				// 临时会话消息
		lpQQClient->OnSessMsg(message, wParam, lParam);
		break;
	case QQ_MSG_STATUS_CHANGE_MSG:		// 好友状态改变消息
		lpQQClient->OnStatusChangeMsg(message, wParam, lParam);
		break;
	case QQ_MSG_KICK_MSG:				// 被踢下线消息
		lpQQClient->OnKickMsg(message, wParam, lParam);
		break;
	case QQ_MSG_SYS_GROUP_MSG:			// 群系统消息
		lpQQClient->OnSysGroupMsg(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_BUDDY_NUMBER:	// 更新好友号码
		lpQQClient->OnUpdateBuddyNumber(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_GMEMBER_NUMBER:	// 更新群成员号码
		lpQQClient->OnUpdateGMemberNumber(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_GROUP_NUMBER:	// 更新群号码
		lpQQClient->OnUpdateGroupNumber(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_BUDDY_SIGN:		// 更新好友个性签名
		lpQQClient->OnUpdateBuddySign(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_GMEMBER_SIGN:	// 更新群成员个性签名
		lpQQClient->OnUpdateGMemberSign(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_BUDDY_INFO:		// 更新好友信息
		lpQQClient->OnUpdateBuddyInfo(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_GMEMBER_INFO:	// 更新群成员信息
		lpQQClient->OnUpdateGMemberInfo(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_GROUP_INFO:		// 更新群信息
		lpQQClient->OnUpdateGroupInfo(message, wParam, lParam);
		break;
	case QQ_MSG_UPDATE_C2CMSGSIG:		// 更新临时会话信令
		lpQQClient->OnUpdateC2CMsgSig(message, wParam, lParam);
		break;
	case QQ_MSG_CHANGE_STATUS_RESULT:	// 改变在线状态返回消息
		lpQQClient->OnChangeStatusResult(message, wParam, lParam);
		break;

	case QQ_MSG_INTERNAL_GETBUDDYDATA:
		lpQQClient->OnInternal_GetBuddyData(message, wParam, lParam);
		break;
	case QQ_MSG_INTERNAL_GETGROUPDATA:
		lpQQClient->OnInternal_GetGroupData(message, wParam, lParam);
		break;
	case QQ_MSG_INTERNAL_GETGMEMBERDATA:
		lpQQClient->OnInternal_GetGMemberData(message, wParam, lParam);
		break;
	case QQ_MSG_INTERNAL_GROUPID2CODE:
		return lpQQClient->OnInternal_GroupId2Code(message, wParam, lParam);
		break;

	default:
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
