#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "LoginTask.h"
#include "LogoutTask.h"
#include "SendMsgTask.h"
#include "RecvMsgTask.h"
#include "PollTask.h"
#include "InfoTask.h"
#include "GetGroupFaceSigTask.h"
#include "ChangeStatusTask.h"

class CQQClient
{
public:
	CQQClient(void);
	~CQQClient(void);

public:
	BOOL Init();										// 初始化客户端
	void UnInit();										// 反初始化客户端

	void SetUser(LPCTSTR lpQQNum, LPCTSTR lpQQPwd);		// 设置QQ号码和密码
	void SetLoginStatus(QQ_STATUS nStatus);				// 设置登录状态
	void SetCallBackWnd(HWND hCallBackWnd);				// 设置回调窗口句柄
	void SetVerifyCode(LPCTSTR lpVerifyCode);			// 设置验证码

	BOOL Login();										// 登录
	BOOL Logout();										// 注销

	void CancelLogin();									// 取消登录
	
	void ChangeStatus(QQ_STATUS nStatus);				// 改变在线状态
	void UpdateBuddyList();								// 更新好友列表
	void UpdateGroupList();								// 更新群列表
	void UpdateRecentList();							// 更新最近联系人列表
	void UpdateBuddyInfo(UINT nQQUin);					// 更新好友信息
	void UpdateGroupMemberInfo(UINT nGroupCode, UINT nQQUin);	// 更新群成员信息
	void UpdateGroupInfo(UINT nGroupCode);				// 更新群信息
	void UpdateBuddyNum(UINT nQQUin);					// 更新好友号码
	void UpdateGroupMemberNum(UINT nGroupCode, UINT nQQUin);	// 更新群成员号码
	void UpdateGroupMemberNum(UINT nGroupCode, std::vector<UINT> * arrQQUin);	// 更新群成员号码
	void UpdateGroupNum(UINT nGroupCode);				// 更新群号码
	void UpdateBuddySign(UINT nQQUin);					// 更新好友个性签名
	void UpdateGroupMemberSign(UINT nGroupCode, UINT nQQUin);	// 更新群成员个性签名
	void ModifyQQSign(LPCTSTR lpSign);					// 修改QQ个性签名
	void UpdateBuddyHeadPic(UINT nQQUin, UINT nQQNum);			// 更新好友头像
	void UpdateGroupMemberHeadPic(UINT nGroupCode, UINT nQQUin, UINT nQQNum);// 更新群成员头像
	void UpdateGroupHeadPic(UINT nGroupCode, UINT nGroupNum);	// 更新群头像
	void UpdateGroupFaceSignal();						// 更新群表情信令
	BOOL SendBuddyMsg(UINT nToUin, time_t nTime, LPCTSTR lpMsg);				// 发送好友消息
	BOOL SendGroupMsg(UINT nGroupId, time_t nTime, LPCTSTR lpMsg);				// 发送群消息
	BOOL SendSessMsg(UINT nGroupId, UINT nToUin, time_t nTime, LPCTSTR lpMsg);	// 发送临时会话消息

	BOOL IsOffline();									// 是否离线状态
	QQ_STATUS GetStatus();								// 获取在线状态
	BOOL GetVerifyCodePic(const BYTE *& lpData, DWORD& dwSize);	// 获取验证码图片

	CBuddyInfo * GetUserInfo();							// 获取用户信息
	CBuddyList * GetBuddyList();						// 获取好友列表
	CGroupList * GetGroupList();						// 获取群列表
	CRecentList * GetRecentList();						// 获取最近联系人列表
	CMessageList * GetMessageList();					// 获取消息列表
	CMessageLogger * GetMsgLogger();					// 获取消息记录管理器

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

private:
	void OnUpdateBuddyList(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateGroupList(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateRecentList(UINT message, WPARAM wParam, LPARAM lParam);
	void OnBuddyMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void OnGroupMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void OnSessMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void OnSysGroupMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void OnStatusChangeMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void OnKickMsg(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateBuddyNumber(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateGMemberNumber(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateGroupNumber(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateBuddySign(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateGMemberSign(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateBuddyInfo(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateGMemberInfo(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateGroupInfo(UINT message, WPARAM wParam, LPARAM lParam);
	void OnUpdateC2CMsgSig(UINT message, WPARAM wParam, LPARAM lParam);
	void OnChangeStatusResult(UINT message, WPARAM wParam, LPARAM lParam);

	void OnInternal_GetBuddyData(UINT message, WPARAM wParam, LPARAM lParam);
	void OnInternal_GetGroupData(UINT message, WPARAM wParam, LPARAM lParam);
	void OnInternal_GetGMemberData(UINT message, WPARAM wParam, LPARAM lParam);
	UINT OnInternal_GroupId2Code(UINT message, WPARAM wParam, LPARAM lParam);

	BOOL CreateProxyWnd();		// 创建代理窗口
	BOOL DestroyProxyWnd();		// 销毁代理窗口
	static LRESULT CALLBACK ProxyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	CQQUser m_QQUser;
	CQQProtocol m_QQProtocol;
	CThreadPool m_ThreadPool;
	CLoginTask m_LoginTask;
	CLogoutTask m_LogoutTask;
	CSendMsgTask m_SendMsgTask;
	CRecvMsgTask m_RecvMsgTask;
	CPollTask m_PollTask;
};
