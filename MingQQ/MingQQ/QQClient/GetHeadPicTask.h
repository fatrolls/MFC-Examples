#pragma once

#include "QQUser.h"
#include "QQProtocol.h"
#include "ThreadPool.h"

enum GHPT_OP_TYPE
{
	GHPT_OP_TYPE_BUDDY_PIC,
	GHPT_OP_TYPE_GROUP_PIC,
	GHPT_OP_TYPE_SESS_PIC
};

struct GHPT_PARAM
{
	GHPT_OP_TYPE nType;
	UINT nGroupCode;
	UINT nGroupNum;
	UINT nQQUin;
	UINT nQQNum;
};

class CGetHeadPicTask : public CThreadPoolTask
{
public:
	CGetHeadPicTask(void);
	~CGetHeadPicTask(void);

public:
	virtual int Run();
	virtual int Stop();
	virtual void TaskFinish();

	BOOL AddParam(GHPT_OP_TYPE nType, UINT nGroupCode, 
		UINT nGroupNum, UINT nQQUin, UINT nQQNum);
	void DelAllParams();

private:
	BOOL SavePic(GHPT_PARAM& stParam, const BYTE * lpData, DWORD dwSize);

public:
	CQQUser * m_lpQQUser;
	CQQProtocol * m_lpQQProtocol;
	std::vector<GHPT_PARAM> m_arrParam;

private:
	BOOL m_bStop;
	CHttpClient m_HttpClient;
};
