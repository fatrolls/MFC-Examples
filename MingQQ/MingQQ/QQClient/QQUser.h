#pragma once

#include "../Path.h"
#include "QQProtocolData.h"
#include "MessageLogger.h"

class CQQUser
{
public:
	CQQUser(void);
	~CQQUser(void);

public:
	tstring GetUserFolder();							// 获取用户文件夹存放路径
	void SetUserFolder(LPCTSTR lpPath);					// 设置用户文件夹存放路径
	
	tstring GetPersonalFolder(UINT nUserNum = 0);		// 获取个人文件夹存放路径
	tstring GetChatPicFolder(UINT nUserNum = 0);		// 获取聊天图片存放路径

	tstring GetUserHeadPicFullName(UINT nUserNum = 0);	// 获取用户头像图片全路径文件名
	tstring GetBuddyHeadPicFullName(UINT nQQNum);		// 获取好友头像图片全路径文件名
	tstring GetGroupHeadPicFullName(UINT nGroupNum);	// 获取群头像图片全路径文件名
	tstring GetSessHeadPicFullName(UINT nQQNum);		// 获取群成员头像图片全路径文件名
	tstring GetChatPicFullName(LPCTSTR lpszFileName);	// 获取聊天图片全路径文件名
	tstring GetMsgLogFullName(UINT nUserNum = 0);		// 获取消息记录全路径文件名

	BOOL IsNeedUpdateBuddyHeadPic(UINT nQQNum);			// 判断是否需要更新好友头像
	BOOL IsNeedUpdateGroupHeadPic(UINT nGroupNum);		// 判断是否需要更新群头像
	BOOL IsNeedUpdateSessHeadPic(UINT nQQNum);			// 判断是否需要更新群成员头像

	time_t GetServerTime();								// 获取服务器时间

public:
	tstring m_strQQNum;
	tstring m_strQQPwd;
	UINT m_nQQUin;
	QQ_STATUS m_nStatus;
	HWND m_hProxyWnd;
	HWND m_hCallBackWnd;
	QQ_STATUS m_nLoginStatus;
	CBuffer m_VerifyCodePic;
	tstring m_strVerifyCode;
	CVerifyCodeInfo m_VerifyCodeInfo;
	CLoginResult_1 m_LoginResult1;
	CLoginResult_2 m_LoginResult2;
	tstring m_strUserFolder;
	CBuddyInfo m_UserInfo;
	CBuddyList m_BuddyList;
	CGroupList m_GroupList;
	CRecentList m_RecentList;
	CMessageList m_MsgList;
	CMessageLogger m_MsgLogger;
};
