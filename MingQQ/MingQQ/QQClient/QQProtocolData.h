#pragma once

#include <string>
#include <vector>
#include "../jsoncpp-0.5.0/json.h"		// 使用JsonCpp需要包含的头文件
#include "../Utils.h"
#include "../Path.h"
#include "Buffer.h"

#if defined(UNICODE) || defined(_UNICODE)
	typedef std::wstring tstring;
#else
	typedef std::string tstring;
#endif

extern const TCHAR * WEBQQ_APP_ID;
extern const TCHAR * WEBQQ_CLIENT_ID;

#define		QQ_MSG_LOGIN_RESULT				WM_USER + 100		// 登录返回消息
#define		QQ_MSG_LOGOUT_RESULT			WM_USER + 101		// 注销返回消息
#define		QQ_MSG_UPDATE_USER_INFO			WM_USER + 102		// 更新用户信息
#define		QQ_MSG_UPDATE_BUDDY_LIST		WM_USER + 103		// 更新好友列表消息
#define		QQ_MSG_UPDATE_GROUP_LIST		WM_USER + 104		// 更新群列表消息
#define		QQ_MSG_UPDATE_RECENT_LIST		WM_USER + 105		// 更新最近联系人列表消息
#define		QQ_MSG_BUDDY_MSG				WM_USER + 106		// 好友消息
#define		QQ_MSG_GROUP_MSG				WM_USER + 107		// 群消息
#define		QQ_MSG_SESS_MSG					WM_USER + 108		// 临时会话消息
#define		QQ_MSG_STATUS_CHANGE_MSG		WM_USER + 109		// 好友状态改变消息
#define		QQ_MSG_KICK_MSG					WM_USER + 110		// 被踢下线消息
#define		QQ_MSG_SYS_GROUP_MSG			WM_USER + 111		// 群系统消息
#define		QQ_MSG_UPDATE_BUDDY_NUMBER		WM_USER + 112		// 更新好友号码
#define		QQ_MSG_UPDATE_GMEMBER_NUMBER	WM_USER + 113		// 更新群成员号码
#define		QQ_MSG_UPDATE_GROUP_NUMBER		WM_USER + 114		// 更新群号码
#define		QQ_MSG_UPDATE_BUDDY_SIGN		WM_USER + 115		// 更新好友个性签名
#define		QQ_MSG_UPDATE_GMEMBER_SIGN		WM_USER + 116		// 更新群成员个性签名
#define		QQ_MSG_UPDATE_BUDDY_INFO		WM_USER + 117		// 更新好友信息
#define		QQ_MSG_UPDATE_GMEMBER_INFO		WM_USER + 118		// 更新群成员信息
#define		QQ_MSG_UPDATE_GROUP_INFO		WM_USER + 119		// 更新群信息
#define		QQ_MSG_UPDATE_C2CMSGSIG			WM_USER + 120		// 更新临时会话信令
#define		QQ_MSG_UPDATE_GROUPFACESIG		WM_USER + 121		// 更新群表情信令
#define		QQ_MSG_UPDATE_BUDDY_HEADPIC		WM_USER + 122		// 更新好友头像
#define		QQ_MSG_UPDATE_GMEMBER_HEADPIC	WM_USER + 123		// 更新群成员头像
#define		QQ_MSG_UPDATE_GROUP_HEADPIC		WM_USER + 124		// 更新群头像
#define		QQ_MSG_CHANGE_STATUS_RESULT		WM_USER + 125		// 改变在线状态返回消息

#define		QQ_MSG_INTERNAL_GETBUDDYDATA	WM_USER + 400
#define		QQ_MSG_INTERNAL_GETGROUPDATA	WM_USER + 401
#define		QQ_MSG_INTERNAL_GETGMEMBERDATA	WM_USER + 402
#define		QQ_MSG_INTERNAL_GROUPID2CODE	WM_USER + 403

#define		QQ_MSG_FIRST					WM_USER + 100
#define		QQ_MSG_LAST						WM_USER + 500

// QQ在线状态字符串
#define		QQ_STATUS_STR_ONLINE			_T("online")		// 我在线上
#define		QQ_STATUS_STR_CALLME			_T("callme")		// Q我吧
#define		QQ_STATUS_STR_AWAY				_T("away")			// 离开
#define		QQ_STATUS_STR_BUSY				_T("busy")			// 忙碌
#define		QQ_STATUS_STR_SILENT			_T("silent")		// 请匆打扰
#define		QQ_STATUS_STR_HIDDEN			_T("hidden")		// 隐身
#define		QQ_STATUS_STR_OFFLINE			_T("offline")		// 离线

// QQ消息类型字符串
#define		QQ_MSG_TYPE_STR_BUDDY			_T("message")		// 好友消息类型
#define		QQ_MSG_TYPE_STR_GROUP			_T("group_message")	// 群消息类型
#define		QQ_MSG_TYPE_STR_SESS			_T("sess_message")	// 临时会话消息类型
#define		QQ_MSG_TYPE_STR_STATUSCHANGE	_T("buddies_status_change")	// 好友状态改变消息类型
#define		QQ_MSG_TYPE_STR_KICK			_T("kick_message")	// 被踢下线消息类型
#define		QQ_MSG_TYPE_STR_SYSGROUP		_T("sys_g_msg")		// 群系统消息类型

enum QQ_LOGIN_RESULT_CODE	// 登录返回代码
{
	QLRC_SUCCESS,			// 登录成功
	QLRC_FAILED,			// 登录失败
	QLRC_PASSWORD_ERROR,	// 密码错误
	QLRC_NEED_VERIFY_CODE,	// 需要输入验证码
	QLRC_VERIFY_CODE_ERROR,	// 验证码错误
	QLRC_USER_CANCEL_LOGIN	// 用户取消登录
};

enum QQ_STATUS				// QQ在线状态
{
	QQ_STATUS_ONLINE = 10,	// 我在线上
	QQ_STATUS_CALLME = 60,	// Q我吧
	QQ_STATUS_AWAY = 30,	// 离开
	QQ_STATUS_BUSY = 50,	// 忙碌
	QQ_STATUS_SILENT = 70,	// 请匆打扰
	QQ_STATUS_HIDDEN = 80,	// 隐身
	QQ_STATUS_OFFLINE = 90	// 离线
};

enum QQ_CLIENT_TYPE			// QQ客户端类型
{
	QQ_CLIENT_TYPE_PC = 1,
	QQ_CLIENT_TYPE_MOBILE = 21,
	QQ_CLIENT_TYPE_IPHONE = 24,
	QQ_CLIENT_TYPE_WEBQQ = 41,
	QQ_CLIENT_TYPE_PAD = 42
};

enum CONTENT_TYPE
{
	CONTENT_TYPE_UNKNOWN,
	CONTENT_TYPE_FONT_INFO,
	CONTENT_TYPE_TEXT,
	CONTENT_TYPE_FACE,
	CONTENT_TYPE_CUSTOM_FACE,
	CONTENT_TYPE_OFF_PIC
};

enum QQ_MSG_TYPE
{
	QQ_MSG_TYPE_UNKNOWN,
	QQ_MSG_TYPE_BUDDY,
	QQ_MSG_TYPE_GROUP,
	QQ_MSG_TYPE_SESS,
	QQ_MSG_TYPE_STATUSCHANGE,
	QQ_MSG_TYPE_KICK,
	QQ_MSG_TYPE_SYSGROUP
};

QQ_STATUS ConvertToQQStatus(LPCTSTR lpStatus);
LPCTSTR ConvertToQQStatusStr(QQ_STATUS nStatus);

tstring GetRespHeader(std::vector<tstring>* arrRespHeader,	// 获取HTTP头指定字段名称的值
					  LPCTSTR lpszName, int nIndex = 0);

class CBuddyTeamInfo;
class CBuddyInfo;
class COnlineBuddyInfo;
class CGroupInfo;
class CRecentInfo;

class CVerifyCodeInfo
{
public:
	CVerifyCodeInfo(void);
	~CVerifyCodeInfo(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

private:
	BOOL ParsePtUin(const TCHAR * lpInPtUin, CHAR * lpOutPtUin, int& nOutPtUinLen);

public:
	int m_nNeedVerify;
	tstring m_strVerifyCode;
	tstring m_strVCType;
	CHAR m_cPtUin[1024];
	int m_nPtUinLen;
};

class CLoginResult_1
{
public:
	CLoginResult_1(void);
	~CLoginResult_1(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf, std::vector<tstring>* arrRespHeader);

public:
	int m_nRetCode;
	tstring m_strMsg;
	tstring m_strPtWebQq;
	tstring m_strSKey;
};

class CLoginResult_2
{
public:
	CLoginResult_2(void);
	~CLoginResult_2(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf, std::vector<tstring>* arrRespHeader);

public:
	int m_nRetCode;
	UINT m_nUIN;
	UINT m_nCIP;
	int m_nIndex;
	int m_nPort;
	QQ_STATUS m_nStatus;
	tstring m_strVfWebQq;
	tstring m_strPSessionId;
	int m_nUser_State;
	int m_f;
	time_t m_nServerTime;
	DWORD m_dwTickCount;
};

class CLogoutResult
{
public:
	CLogoutResult(void);
	~CLogoutResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strResult;
};

class COnlineBuddyListResult
{
public:
	COnlineBuddyListResult(void);
	~COnlineBuddyListResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	std::vector<COnlineBuddyInfo *> m_arrOnlineBuddyInfo;
};

class CBuddyListResult
{
public:
	CBuddyListResult(void);
	~CBuddyListResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);
	int GetBuddyTeamCount();
	CBuddyTeamInfo * GetBuddyTeam(int nTeamIndex);
	CBuddyTeamInfo * GetBuddyTeamByInnerIndex(int nInnerTeamIndex);
	int GetBuddyCount(int nTeamIndex);
	int GetOnlineBuddyCount(int nTeamIndex);
	CBuddyInfo * GetBuddy(int nTeamIndex, int nIndex);
	CBuddyInfo * GetBuddy(UINT nQQUin);
	BOOL SetOnlineBuddyList(COnlineBuddyListResult * lpOnlineBuddyListResult);
	void SortBuddyTeam();
	void SortBuddy();

public:
	int m_nRetCode;
	std::vector<CBuddyTeamInfo *> m_arrBuddyTeamInfo;
};

class CGroupListResult
{
public:
	CGroupListResult(void);
	~CGroupListResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);
	int GetGroupCount();				// 获取群总数
	CGroupInfo * GetGroup(int nIndex);	// 根据索引获取群信息

public:
	int m_nRetCode;
	std::vector<CGroupInfo *> m_arrGroupInfo;
};

class CRecentListResult
{
public:
	CRecentListResult(void);
	~CRecentListResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	std::vector<CRecentInfo *> m_arrRecentInfo;
};

class CGetQQNumResult
{
public:
	CGetQQNumResult(void);
	~CGetQQNumResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	UINT m_nQQUin;			// 内部QQ号码
	UINT m_nQQNum;			// QQ号码
};

class CGetSignResult
{
public:
	CGetSignResult(void);
	~CGetSignResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	UINT m_nQQUin;			// 内部QQ号码
	tstring m_strSign;		// 个性签名
};

class CSetSignResult
{
public:
	CSetSignResult(void);
	~CSetSignResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	int m_nResult;
};

class CBuddyInfoResult
{
public:
	CBuddyInfoResult(void);
	~CBuddyInfoResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	UINT m_nQQUin;			// 内部QQ号码
	tstring m_strNickName;	// 昵称
	int m_nFace;			// 头像
	tstring m_strGender;	// 性别
	int m_nShengXiao;		// 生肖
	int m_nConstel;			// 星座
	int m_nBlood;			// 血型
	tstring m_strBirthday;	// 生日
	tstring m_strCountry;	// 国家
	tstring m_strProvince;	// 省份
	tstring m_strCity;		// 城市
	tstring m_strPhone;		// 电话
	tstring m_strMobile;	// 手机
	tstring m_strEmail;		// 邮箱
	tstring m_strOccupation;// 职业
	tstring m_strCollege;	// 毕业院校
	tstring m_strHomepage;	// 个人主页
	tstring m_strPersonal;	// 个人说明
	BOOL m_bAllow;
	UINT m_nRegTime;
	int m_nStat;
	int m_nVipInfo;
	int m_nClientType;		// 客户端类型：1-QQ客户端 41-WebQQ
	tstring m_strToken;
};

class CGroupInfoResult
{
public:
	CGroupInfoResult(void);
	~CGroupInfoResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);
	CBuddyInfo * GetMemberByUin(UINT nQQUin);

public:
	int m_nRetCode;
	UINT m_nGroupCode;		// 群代码
	UINT m_nGroupId;		// 群ID
	tstring m_strName;		// 群名称
	tstring m_strMemo;		// 群公告
	tstring m_strFingerMemo;// 群简介
	UINT m_nOwnerUin;		// 群拥有者Uin
	UINT m_nCreateTime;		// 群创建时间
	int m_nFace;			// 群头像
	int m_nLevel;			// 群等级
	int m_nClass;			// 群分类索引
	UINT m_nOption;
	UINT m_nFlag;
	std::vector<CBuddyInfo *> m_arrMember;	// 群成员
};

class CSendBuddyMsgResult
{
public:
	CSendBuddyMsgResult(void);
	~CSendBuddyMsgResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strResult;
};

class CSendGroupMsgResult
{
public:
	CSendGroupMsgResult(void);
	~CSendGroupMsgResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strResult;
};

class CSendSessMsgResult
{
public:
	CSendSessMsgResult(void);
	~CSendSessMsgResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strResult;
};

class CChangeStatusResult
{
public:
	CChangeStatusResult(void);
	~CChangeStatusResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strResult;
};

class CGetC2CMsgSigResult
{
public:
	CGetC2CMsgSigResult(void);
	~CGetC2CMsgSigResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	int m_nType;
	tstring m_strValue;
	UINT m_nFlags;
	UINT m_nGroupId;
	UINT m_nQQUin;
};

class CGetGroupFaceSigResult
{
public:
	CGetGroupFaceSigResult(void);
	~CGetGroupFaceSigResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	int m_nReply;
	tstring m_strGFaceKey;
	tstring m_strGFaceSig;
};

class CUploadBuddyChatPicResult
{
public:
	CUploadBuddyChatPicResult(void);
	~CUploadBuddyChatPicResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	DWORD m_dwFileSize;
	tstring m_strFileName;
	tstring m_strFilePath;
};

class CApplyBuddyChatPicResult
{
public:
	CApplyBuddyChatPicResult(void);
	~CApplyBuddyChatPicResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strUrl;
	int m_nSuccess;
	tstring m_strFilePath;
};

class CUploadGroupChatPicResult
{
public:
	CUploadGroupChatPicResult(void);
	~CUploadGroupChatPicResult(void);

public:
	void Reset();
	BOOL Parse(CBuffer * lpBuf);

public:
	int m_nRetCode;
	tstring m_strFilePath;
};

class CBuddyInfo			// 好友信息
{
public:
	CBuddyInfo(void);
	~CBuddyInfo(void);

public:
	void Reset();
	void SetQQNum(CGetQQNumResult * lpGetQQNumResult);
	void SetQQSign(CGetSignResult * lpGetSignResult);
	void SetBuddyInfo(CBuddyInfoResult * lpBuddyInfoResult);
	BOOL IsHasQQNum();
	BOOL IsHasQQSign();
	BOOL IsHasBuddyInfo();
	tstring GetDisplayGender();
	tstring GetDisplayShengXiao();
	tstring GetDisplayConstel();
	tstring GetDisplayBlood();

public:
	UINT m_nQQUin;			// 内部QQ号码
	UINT m_nQQNum;			// QQ号码
	int m_nTeamIndex;		// 分组索引
	tstring m_strNickName;	// 昵称
	tstring m_strMarkName;	// 备注
	BOOL m_bIsVip;			// 是否VIP标志
	int m_nVipLevel;		// VIP等级
	int m_nFace;			// 头像
	DWORD m_dwFlag;			// 
	QQ_STATUS m_nStatus;	// 在线状态
	int m_nClientType;		// 客户端类型：1-QQ客户端 41-WebQQ
	tstring m_strGroupCard;	// 群名片
	UINT m_nGroupFlag;
	tstring m_strSign;		// QQ个性签名
	tstring m_strGender;	// 性别
	int m_nShengXiao;		// 生肖
	int m_nConstel;			// 星座
	int m_nBlood;			// 血型
	tstring m_strBirthday;	// 生日
	tstring m_strCountry;	// 国家
	tstring m_strProvince;	// 省份
	tstring m_strCity;		// 城市
	tstring m_strPhone;		// 电话
	tstring m_strMobile;	// 手机
	tstring m_strEmail;		// 邮箱
	tstring m_strOccupation;// 职业
	tstring m_strCollege;	// 毕业院校
	tstring m_strHomepage;	// 个人主页
	tstring m_strPersonal;	// 个人说明
	BOOL m_bAllow;
	UINT m_nRegTime;
	int m_nStat;
	int m_nVipInfo;
	tstring m_strToken;
	tstring m_strGroupSig;	// 群内会话信令
	BOOL m_bHasQQNum;
	BOOL m_bHasQQSign;
	BOOL m_bHasBuddyInfo;
};

class CBuddyTeamInfo		// 好友分组信息
{
public:
	CBuddyTeamInfo(void);
	~CBuddyTeamInfo(void);

public:
	void Reset();
	int GetBuddyCount();
	int GetOnlineBuddyCount();
	CBuddyInfo * GetBuddy(int nIndex);
	void Sort();

public:
	int m_nIndex;			// 索引
	int m_nSort;			// 排列顺序
	tstring m_strName;		// 分组名称
	std::vector<CBuddyInfo *> m_arrBuddyInfo;
};

class COnlineBuddyInfo		// 在线好友信息
{
public:
	COnlineBuddyInfo(void);
	~COnlineBuddyInfo(void);

public:
	void Reset();

public:
	UINT m_nUin;
	QQ_STATUS m_nStatus;	// 在线状态
	int m_nClientType;		// 客户端类型
};

class CBuddyList	// 好友列表
{
public:
	CBuddyList(void);
	~CBuddyList(void);

public:
	void Reset();
	int GetBuddyTeamCount();
	CBuddyTeamInfo * GetBuddyTeam(int nTeamIndex);
	CBuddyTeamInfo * GetBuddyTeamByIndex(int nIndex);
	int GetBuddyCount(int nTeamIndex);
	int GetOnlineBuddyCount(int nTeamIndex);
	CBuddyInfo * GetBuddy(int nTeamIndex, int nIndex);
	CBuddyInfo * GetBuddy(UINT nQQUin);
	BOOL SetOnlineBuddyList(COnlineBuddyListResult * lpOnlineBuddyListResult);
	void SortBuddyTeam();
	void SortBuddy();
	BOOL AddBuddyTeam(CBuddyTeamInfo * lpBuddyTeamInfo);

public:
	int m_nRetCode;
	std::vector<CBuddyTeamInfo *> m_arrBuddyTeamInfo;
};

class CGroupInfo			// 群信息
{
public:
	CGroupInfo(void);
	~CGroupInfo(void);

public:
	void Reset();
	int GetMemberCount();						// 获取群成员总人数
	int GetOnlineMemberCount();					// 获取群成员在线人数
	CBuddyInfo * GetMember(int nIndex);			// 根据索引获取群成员信息
	CBuddyInfo * GetMemberByUin(UINT nQQUin);	// 根据QQUin获取群成员信息
	CBuddyInfo * GetMemberByNum(UINT nQQNum);	// 根据QQNum获取群成员信息
	void Sort();								// 对群成员列表按在线状态进行排序
	BOOL AddMember(CBuddyInfo * lpBuddyInfo);	// 添加群成员
	BOOL DelAllMember();						// 删除所有群成员
	void SetGroupNumber(CGetQQNumResult * lpGetQQNumResult);	// 设置群号码
	BOOL SetGroupInfo(CGroupInfoResult * lpGroupInfoResult);	// 设置群信息
	BOOL IsHasGroupNumber();
	BOOL IsHasGroupInfo();

public:
	UINT m_nGroupCode;		// 群代码
	UINT m_nGroupId;		// 群ID
	UINT m_nGroupNumber;	// 群号码
	tstring m_strName;		// 群名称
	tstring m_strMemo;		// 群公告
	tstring m_strFingerMemo;// 群简介
	UINT m_nOwnerUin;		// 群拥有者Uin
	UINT m_nCreateTime;		// 群创建时间
	int m_nFace;			// 群头像
	int m_nLevel;			// 群等级
	int m_nClass;			// 群分类索引
	UINT m_nOption;
	UINT m_nFlag;
	BOOL m_bHasGroupNumber;
	BOOL m_bHasGroupInfo;
	std::vector<CBuddyInfo *> m_arrMember;	// 群成员
};

class CGroupList	// 群列表
{
public:
	CGroupList(void);
	~CGroupList(void);

public:
	void Reset();
	int GetGroupCount();							// 获取群总数
	CGroupInfo * GetGroup(int nIndex);				// 获取群信息(根据索引)
	CGroupInfo * GetGroupByCode(UINT nGroupCode);	// 获取群信息(根据群代码)
	CGroupInfo * GetGroupById(UINT nGroupId);		// 获取群信息(根据群Id)
	CBuddyInfo * GetGroupMemberByCode(UINT nGroupCode, UINT nQQUin);// 根据群代码和群成员QQUin获取群成员信息
	CBuddyInfo * GetGroupMemberById(UINT nGroupId, UINT nQQUin);	// 根据群Id和群成员QQUin获取群成员信息
	BOOL AddGroup(CGroupInfo * lpGroupInfo);		// 添加群
	UINT GetGroupCodeById(UINT nGroupId);			// 由群Id获取群代码
	UINT GetGroupIdByCode(UINT nGroupCode);			// 由群代码获取群Id

public:
	std::vector<CGroupInfo *> m_arrGroupInfo;
};

class CRecentInfo	// 最近联系人信息
{
public:
	CRecentInfo(void);
	~CRecentInfo(void);

public:
	void Reset();

public:
	UINT m_nQQUin;
	int m_nType;
};

class CRecentList			// 最近联系人列表
{
public:
	CRecentList(void);
	~CRecentList(void);

public:
	void Reset();
	BOOL AddRecent(CRecentInfo * lpRecentInfo);
	int GetRecentCount();
	CRecentInfo * GetRecent(int nIndex);

public:
	int m_nRetCode;
	std::vector<CRecentInfo *> m_arrRecentInfo;
};

class CFontInfo				// 字体信息
{
public:
	CFontInfo(void) : m_nSize(9),m_clrText(RGB(0,0,0)),m_strName(_T("宋体")),
		m_bBold(FALSE),m_bItalic(FALSE),m_bUnderLine(FALSE){}
	~CFontInfo(void){}

public:
	int m_nSize;			// 字体大小
	COLORREF m_clrText;		// 字体颜色
	tstring m_strName;		// 字体名称
	BOOL m_bBold;			// 是否加粗
	BOOL m_bItalic;			// 是否倾斜
	BOOL m_bUnderLine;		// 是否带下划线
};

class CCustomFaceInfo		// 自定义表情信息
{
public:
	CCustomFaceInfo(void) : m_nFileId(0),m_dwFileSize(0){}
	~CCustomFaceInfo(void){}

public:
	tstring m_strName;			// 接收自定义表情使用参数
	UINT m_nFileId;
	tstring m_strKey;
	tstring m_strServer;

	DWORD m_dwFileSize;			// 发送自定义表情使用参数
	tstring m_strFileName;
	tstring m_strFilePath;
};

class CContent				// 消息内容
{
public:
	CContent(void) : m_nType(CONTENT_TYPE_UNKNOWN),m_nFaceId(0){}
	~CContent(void){}

public:
	CONTENT_TYPE m_nType;			// 内容类型
	CFontInfo m_FontInfo;			// 字体信息
	tstring m_strText;				// 文本信息
	int m_nFaceId;					// 系统表情Id
	CCustomFaceInfo m_CFaceInfo;	// 自定义表情信息
};

class CBuddyMessage		// 好友消息
{
public:
	CBuddyMessage(void);
	~CBuddyMessage(void);

public:
	static BOOL IsType(LPCTSTR lpType);
	void Reset();
	BOOL Parse(Json::Value& JsonValue);

public:
	UINT m_nMsgId;
	UINT m_nMsgId2;
	UINT m_nFromUin;
	UINT m_nToUin;
	UINT m_nMsgType;
	UINT m_nReplyIp;
	UINT m_nTime;
	std::vector<CContent *> m_arrContent;
};

class CGroupMessage		// 群消息
{
public:
	CGroupMessage(void);
	~CGroupMessage(void);

public:
	static BOOL IsType(LPCTSTR lpType);
	void Reset();
	BOOL Parse(Json::Value& JsonValue);

public:
	UINT m_nMsgId;
	UINT m_nMsgId2;
	UINT m_nFromUin;
	UINT m_nToUin;
	UINT m_nMsgType;
	UINT m_nReplyIp;
	UINT m_nGroupCode;
	UINT m_nSendUin;
	UINT m_nSeq;
	UINT m_nInfoSeq;
	UINT m_nTime;
	std::vector<CContent *> m_arrContent;
};

class CSessMessage		// 临时消息
{
public:
	CSessMessage(void);
	~CSessMessage(void);

public:
	static BOOL IsType(LPCTSTR lpType);
	void Reset();
	BOOL Parse(Json::Value& JsonValue);

public:
	UINT m_nMsgId;
	UINT m_nMsgId2;
	UINT m_nFromUin;
	UINT m_nToUin;
	UINT m_nMsgType;
	UINT m_nReplyIp;
	UINT m_nTime;
	UINT m_nGroupId;
	UINT m_nQQNum;
	UINT m_nServiceType;
	UINT m_nFlags;
	std::vector<CContent *> m_arrContent;
};

class CStatusChangeMessage	// 状态改变通知消息
{
public:
	CStatusChangeMessage(void);
	~CStatusChangeMessage(void);

public:
	static BOOL IsType(LPCTSTR lpType);
	void Reset();
	BOOL Parse(Json::Value& JsonValue);

public:
	UINT m_nQQUin;
	QQ_STATUS m_nStatus;	// 在线状态
	int m_nClientType;		// 客户端类型
};

class CKickMessage	// 被踢下线通知消息(例如号码在另一地点登录)
{
public:
	CKickMessage(void);
	~CKickMessage(void);

public:
	static BOOL IsType(LPCTSTR lpType);
	void Reset();
	BOOL Parse(Json::Value& JsonValue);

public:
	UINT m_nMsgId;
	UINT m_nMsgId2;
	UINT m_nFromUin;
	UINT m_nToUin;
	UINT m_nMsgType;
	UINT m_nReplyIp;
	BOOL m_bShowReason;			// 是否显示被踢下线原因
	tstring m_strReason;		// 被踢下线原因
};

class CSysGroupMessage	// 群系统消息
{
public:
	CSysGroupMessage(void);
	~CSysGroupMessage(void);

public:
	static BOOL IsType(LPCTSTR lpType);
	void Reset();
	BOOL Parse(Json::Value& JsonValue);

public:
	UINT m_nMsgId;
	UINT m_nMsgId2;
	UINT m_nFromUin;
	UINT m_nToUin;
	UINT m_nMsgType;
	UINT m_nReplyIp;
	tstring m_strSubType;
	UINT m_nGroupCode;
	UINT m_nGroupNumber;
	UINT m_nAdminUin;
	tstring m_strMsg;
	UINT m_nOpType;
	UINT m_nOldMember;
	tstring m_strOldMember;
	tstring m_strAdminUin;
	tstring m_strAdminNickName;
};

class CMessageSender	// 消息发送者
{
public:
	CMessageSender(QQ_MSG_TYPE nType, UINT nSenderId, UINT nGroupCode);
	~CMessageSender(void);

public:
	BOOL AddMsg(void * lpMsg);						// 添加消息
	BOOL DelMsg(int nIndex);						// 删除消息(根据索引)
	BOOL DelMsgById(UINT nMsgId);					// 删除消息(根据消息Id)
	BOOL DelAllMsg();								// 删除所有消息

	QQ_MSG_TYPE GetMsgType();						// 获取消息类型
	UINT GetSenderId();								// 获取发送者Id
	int GetMsgCount();								// 获取消息总数
	UINT GetGroupCode();							// 获取群代码

	CBuddyMessage * GetBuddyMsg(int nIndex);		// 获取好友消息(根据索引)
	CGroupMessage * GetGroupMsg(int nIndex);		// 获取群消息(根据索引)
	CSessMessage * GetSessMsg(int nIndex);			// 获取临时会话消息(根据索引)
	CSysGroupMessage * GetSysGroupMsg(int nIndex);	// 获取群系统消息(根据索引)

	CBuddyMessage * GetBuddyMsgById(UINT nMsgId);	// 获取好友消息(根据消息Id)
	CGroupMessage * GetGroupMsgById(UINT nMsgId);	// 获取群消息(根据消息Id)
	CSessMessage * GetSessMsgById(UINT nMsgId);		// 获取临时会话消息(根据消息Id)
	CSysGroupMessage * GetSysGroupMsgById(UINT nMsgId);// 获取群系统消息(根据消息Id)

private:
	QQ_MSG_TYPE m_nType;
	UINT m_nSenderId;
	UINT m_nGroupCode;
	std::vector<void *> m_arrMsg;
};

class CMessageList	// 消息列表
{
public:
	CMessageList(void);
	~CMessageList(void);

public:
	BOOL AddMsg(QQ_MSG_TYPE nType, UINT nSenderId,			// 添加消息
		UINT nGroupCode, void * lpMsg);
	BOOL DelMsg(QQ_MSG_TYPE nType, UINT nMsgId);			// 删除消息

	BOOL DelMsgSender(int nIndex);							// 删除消息发送者(根据索引)
	BOOL DelMsgSender(QQ_MSG_TYPE nType, UINT nSenderId);	// 删除消息发送者(根据消息类型和发送者Id)
	BOOL DelAllMsgSender();									// 删除所有消息发送者

	int GetMsgSenderCount();								// 获取消息发送者总数
	CMessageSender * GetMsgSender(int nIndex);				// 获取消息发送者(根据索引)
	CMessageSender * GetMsgSender(QQ_MSG_TYPE nType, UINT nSenderId);// 获取消息发送者(根据消息类型和发送者Id)
	CMessageSender * GetLastMsgSender();					// 获取最后一个发送消息过来的发送者

	CBuddyMessage * GetBuddyMsg(UINT nMsgId);				// 获取好友消息(根据消息Id)
	CGroupMessage * GetGroupMsg(UINT nMsgId);				// 获取群消息(根据消息Id)
	CSessMessage * GetSessMsg(UINT nMsgId);					// 获取临时会话消息(根据消息Id)
	CSysGroupMessage * GetSysGroupMsg(UINT nMsgId);			// 获取群系统消息(根据消息Id)

	CBuddyMessage * GetBuddyMsg(UINT nQQUin, UINT nMsgId);	// 获取好友消息(根据发送者Id和消息Id)
	CGroupMessage * GetGroupMsg(UINT nGroupCode, UINT nMsgId);	// 获取群消息(根据发送者Id和消息Id)
	CSessMessage * GetSessMsg(UINT nQQUin, UINT nMsgId);	// 获取临时会话消息(根据发送者Id和消息Id)
	CSysGroupMessage * GetSysGroupMsg(UINT nGroupCode, UINT nMsgId);// 获取群系统消息(根据发送者Id和消息Id)

	struct MSG_IDENTITY
	{
		QQ_MSG_TYPE nType;
		UINT nSenderId;
	};

private:
	void AddMsgIdentity(QQ_MSG_TYPE nType, UINT nSenderId);
	void DelMsgIdentity(QQ_MSG_TYPE nType, UINT nSenderId);

private:
	std::vector<CMessageSender *> m_arrMsgSender;
	std::vector<MSG_IDENTITY> m_arrMsgIdentity;
};
