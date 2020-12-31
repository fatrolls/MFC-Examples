#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

enum QQSIGN_OP_TYPE		// 操作类型
{
	QQSIGN_OP_TYPE_GET,	// 获取
	QQSIGN_OP_TYPE_SET	// 设置
};

struct QQSIGN_GET_PARAM
{
	BOOL bIsGMember;	// 是群成员还是好友
	UINT nGroupCode;	// 群代码
	UINT nQQUin;		// 好友Uin或者群成员Uin
};

struct QQSIGN_SET_PARAM
{
	tstring m_strSign;	// 需要设置的个性签名
};

class CQQSignTask : public CThreadPoolTask
{
public:
	CQQSignTask(void);
	~CQQSignTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

	BOOL AddGetParam(BOOL bIsGMember, UINT nGroupCode, UINT nQQUin);
	BOOL AddSetParam(LPCTSTR lpSign);
	void DelAllItems();

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	QQSIGN_OP_TYPE m_nType;
	std::vector<QQSIGN_GET_PARAM> m_arrGetParam;
	std::vector<QQSIGN_SET_PARAM> m_arrSetParam;

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
