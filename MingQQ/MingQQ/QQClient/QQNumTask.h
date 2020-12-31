#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

enum QQNUM_OP_TYPE			// 操作类型
{
	OP_TYPE_GETBUDDYNUM,	// 获取好友号码
	OP_TYPE_GETGMEMBERNUM,	// 获取群成员号码
	OP_TYPE_GETGROUPNUM,	// 获取群号码
};

struct QQNUM_PARAM
{
	QQNUM_OP_TYPE nType;	// 操作类型
	UINT nGroupCode;		// 群代码
	UINT nQQUin;			// 好友Uin或者群成员Uin
};

class CQQNumTask : public CThreadPoolTask
{
public:
	CQQNumTask(void);
	~CQQNumTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

	BOOL AddParam(QQNUM_OP_TYPE nType, UINT nGroupCode, UINT nQQUin);
	void DelAllItems();

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	std::vector<QQNUM_PARAM> m_arrParam;

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
