/*
 * Copyright Bruce Liang (ldcsaa@gmail.com)
 *
 * Version	: 2.3.2
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Porject	: https://code.google.com/p/ldcsaa
 * Bolg		: http://www.cnblogs.com/ldcsaa
 * WeiBo	: http://weibo.com/u/1402935851
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
/******************************************************************************

Module:  AdoObjectPool.h
Notices: Copyright (c) 2006 Bruce Liang
Purpose: 封装多线程的 ADO 数据库连接.
Desc:
		 1. CAdoObject 封装一个数据库连接
		 2. CAdoObjectPool 封装数据库连接池

Usage:
		 1. 通常应用程序只使用 CAdoObjectPool 对象, 不必处理 CAdoObject 对象
		 2. 使用方法: 在数据库访问函数中定义一个 CAdoObjectPool 局部对象, 然后
			调用该对象的相应方法
			(见: TestDBAccessor测试程序对 DBAccessor 对象的使用)

Rule:	1.	见: "DBAccessor.h" 的头部注释

Example:	见: TestDBAccessor测试程序
											
******************************************************************************/

#pragma once

#import <msado15.dll> no_namespace rename ("EOF", "adoEOF") rename("BOF","adoBOF")


#include <icrsint.h>
#include <vector>

#include "GeneralHelper.h"
#include "InitCom.h"
#include "CriticalSection.h"
#include "Event.h"
#include "WaitFor.h"
#include "VarConv.h"

/******************* 通过字段名称获取字段值 *******************/
#define GET_FIELD_ITEM(rs, field)		rs->Fields->Item[_T(#field)]->Value
#define GET_FIELD_CY(rs, field)			vartocy		(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_STR(rs, field)		vartostr	(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_BOOL(rs, field)		vartobool	(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_DATE(rs, field)		vartodate	(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_BYTE(rs, field)		vartoi1		(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_SHORT(rs, field)		vartoi2		(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_LONG(rs, field)		vartoi4		(GET_FIELD_ITEM(rs, field))
#define GET_FIELD_DOUBLE(rs, field)		vartof		(GET_FIELD_ITEM(rs, field))
/******************* 通过字段索引获取字段值 *******************/
#define GET_INDEX_ITEM(rs, field)		rs->Fields->Item[(long)field]->Value
#define GET_INDEX_CY(rs, field)			vartocy		(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_STR(rs, field)		vartostr	(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_BOOL(rs, field)		vartobool	(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_DATE(rs, field)		vartodate	(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_BYTE(rs, field)		vartoi1		(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_SHORT(rs, field)		vartoi2		(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_LONG(rs, field)		vartoi4		(GET_INDEX_ITEM(rs, field))
#define GET_INDEX_DOUBLE(rs, field)		vartof		(GET_INDEX_ITEM(rs, field))


/****************************************************************************************************
											CAdoObject 
****************************************************************************************************/
class CAdoObject
{
	friend class CAdoObjectPool;
public:

	/**********************************
	描述: 打开数据库连接
	参数: 
			bPreClose		: 如果原来有打开的连接，是否先关闭		默认: 否
			Options			: 连接选项								默认: adConnectUnspecified
	返回值		: 操作结果
	异常		: _com_error
	**********************************/
	HRESULT OpenConnection(BOOL bPreClose = FALSE, long Options = adConnectUnspecified)
	{
		HRESULT hr		= S_FALSE;
		BOOL isOpened	= IsOpened();

		if(!bPreClose && isOpened)
			return hr;

		if(isOpened)
			hr = CloseConnection();

		if(SUCCEEDED(hr))
		{
			hr = (m_pConnection->Open(m_bstrDSN, _T(""), _T(""), Options));
			if(SUCCEEDED(hr))
				m_pCommand->ActiveConnection = m_pConnection;
		}
		return hr;
	}

	/**********************************
	描述: 打开记录集
	参数: 
			Source		: 要打开的源, 可以是 SQL 语句或数据表格等
			Options		: 源类型		默认: SQL 语句
			CursorType	: 游标类型		默认: 静态游标
			LockType	: 锁类型		默认: 乐观锁
			pRecordset	: 要打开的记录集对象, 如果等于 NULL 则打开
						  CAdoObject 对象内部包含的记录集对象 m_pRecordset, 
						  如果打开的是CAdoObject::m_pRecordset, 则不需要调有
						  CloseRecordset()方法进行关闭
										默认: NULL
	返回值: 打开的记录集	
	异常  : _com_error
	**********************************/
	_RecordsetPtr OpenRecordset(const CString& Source, long Options = adCmdText, CursorTypeEnum CursorType = adOpenStatic, LockTypeEnum LockType = adLockOptimistic, _RecordsetPtr pRecordset = NULL)
	{
		if(pRecordset == NULL)
			pRecordset = m_pRecordset;

		HRESULT hr = CloseRecordset(pRecordset);
		if(SUCCEEDED(hr))
			hr = pRecordset->Open((LPCTSTR)Source, (_Connection*)m_pConnection, CursorType, LockType, Options);
		
		ASSERT(SUCCEEDED(hr));

		return pRecordset;
	}

	/**********************************
	描述: 执行命令
	参数: 
			Source			: 要执行的源, 可以是 SQL 语句或存储过程等
			RecordsAffected	: 影响的行数
			Parameters		: 命令参数
			CmdType			: 命令类型		默认: SQL 语句
			CmdTimeout		: 超时值, 如果等于0则使用默认设置
											默认: 0
			pCommand		: 要执行的命令对象, 如果等于NULL则执行
							  CAdoObject 对象内部包含的命令对象 m_pCommand
											默认: NULL
	返回值: 结果记录集	
	异常  : _com_error
	**********************************/
	_RecordsetPtr ExecuteCommand(const CString& Command, long* RecordsAffected, CommandTypeEnum CmdType = adCmdText, VARIANT* Parameters = NULL, long CmdTimeout = 0, _CommandPtr pCommand = NULL)
	{
		if(pCommand == NULL)
			pCommand = m_pCommand;
		else
			pCommand->ActiveConnection = m_pConnection;

		*RecordsAffected = 0;
		pCommand->CommandText = (LPCTSTR)Command;
		if(CmdTimeout != 0)
			pCommand->CommandTimeout = CmdTimeout;
		_variant_t var(*RecordsAffected);
		_RecordsetPtr rs = pCommand->Execute(&var, Parameters, CmdType);
		if(var.vt != VT_NULL && var.vt != VT_EMPTY)
			*RecordsAffected = var.lVal;

		return rs;
	}

	/**********************************
	描述: 关闭记录集
	参数: 
			pRecordset	: 要关闭的记录集对象, 如果等于NULL则关闭
						  CAdoObject 对象内部包含的记录集对象 m_pRecordset
										默认: NULL
	返回值: 操作结果	
	**********************************/

	HRESULT CloseRecordset(_RecordsetPtr pRecordset = NULL)
	{
		if(pRecordset == NULL)
			pRecordset = m_pRecordset;

		return (pRecordset->GetState() & adStateOpen) ? pRecordset->Close() : S_FALSE;
	}

	/**********************************
	描述: 取消命令
	参数: 
			pCommand		: 要取消的命令对象, 如果等于NULL则取消
							  CAdoObject 对象内部包含的命令对象 m_pCommand
											默认: NULL
	返回值: 操作结果	
	**********************************/
	HRESULT CancelCommand(_CommandPtr pCommand = NULL)
	{
		if(pCommand == NULL)
			pCommand = (_CommandPtr*)(&m_pCommand);

		return (pCommand->GetState() & adStateExecuting) ? pCommand->Cancel() : S_FALSE;
	}

	// 取得对象内部的数据连接对象
	const _ConnectionPtr&	GetConnection() {return m_pConnection;}
	// 取得对象内部的记录集对象
	const _RecordsetPtr&	GetRecordset()	{return m_pRecordset;}
	// 取得对象内部的命令对象
	const _CommandPtr&		GetCommand()	{return m_pCommand;}

private:
	// 关闭数据库连接对象
	HRESULT CloseConnection()	{return IsOpened() ? m_pConnection->Close() : S_FALSE;}

	// 检查是否已经打开了数据库连接对象
	BOOL IsOpened()				{return m_pConnection->GetState() & adStateOpen;}

public:
	CAdoObject(LPCTSTR dsn)
	: m_pConnection	(_T("ADODB.Connection"))
	, m_pRecordset	(_T("ADODB.Recordset"))
	, m_pCommand	(_T("ADODB.Command"))
	, m_bstrDSN		(dsn)
	, m_lReference	(0)
	, m_evtAdo		(NULL, FALSE, TRUE)
	{
	}

	~CAdoObject()
	{
	}

private:
	CAdoObject(const CAdoObject&);
	CAdoObject operator = (const CAdoObject&);

private:
	_bstr_t			m_bstrDSN;		// 链接字符串

	_ConnectionPtr	m_pConnection;	// 连接对象
	_RecordsetPtr	m_pRecordset;	// 记录集对象
	_CommandPtr		m_pCommand;		// 命令对象

/******************* 以下内容由 CAdoObjectPool 使用和操作 *******************/
private:
	long GetReference()			{return m_lReference;}
	long IncReference()			{return ++m_lReference;}
	long DecReference()			{return --m_lReference;}

	HANDLE GetEventHandle()		{return m_evtAdo.GetHandle();}
	BOOL SetEvent()				{return m_evtAdo.Set();}

	long m_lReference;	// 引用计数

	CEvt m_evtAdo;		// 对象可用事件

};

typedef vector<CAdoObject*>			CAdoVector;
typedef hash_map<int, CAdoObject*>	CAdoMap;
typedef CAdoVector::iterator		IAdoIteratorV;
typedef CAdoVector::const_iterator	IAdoConstIteratorCV;
typedef CAdoMap::iterator			IAdoIteratorM;
typedef CAdoMap::const_iterator		IAdoConstIteratorCM;

/****************************************************************************************************
											CAdoObjectPool
****************************************************************************************************/
class CAdoObjectPool
{
public:
	/**********************************
	描述: 初始化连接池
	参数: 
			dsn			: 数据库连接串
			poolsize	: 连接池大小	默认: DEFAULT_CONNECTION_POOL_SIZE
	返回值: 操作结果, 如果失败会参数 _com_error 异常
	**********************************/
	static BOOL Init(LPCTSTR dsn, DWORD poolsize = DEFAULT_CONNECTION_POOL_SIZE)
	{

		if(sm_bHasInited)
			return FALSE;


		CLocalLock<CCriSec> local(sm_csAdo);

		ASSERT(poolsize >= 0);
		ASSERT(!sm_pevtAdo);

		if(poolsize == 0)
			poolsize = DEFAULT_CONNECTION_POOL_SIZE;

		sm_pevtAdo = new HANDLE[poolsize];

		for(DWORD i = 0; i < poolsize; ++i)
		{
			CAdoObject* ado	= new CAdoObject(dsn);
			sm_pevtAdo[i]	= ado->GetEventHandle();
			sm_vtAdo.push_back(ado);
		}

		return (sm_bHasInited = TRUE);
	}

	/**********************************
	描述: 释放连接池
	参数: 
	返回值: 操作结果	
	**********************************/
	static BOOL UnInit()
	{
		if(!sm_bHasInited)
			return FALSE;

		CLocalLock<CCriSec> local(sm_csAdo);

		WaitAllAdoObjectFree();
		ClearPtrArray(sm_vtAdo);

		if(sm_pevtAdo)
		{
			delete[] sm_pevtAdo;
			sm_pevtAdo = NULL;
		}

		return !(sm_bHasInited = FALSE);
	}

	/**********************************
	描述: 连接池是否已经被初始化
	参数: 
	返回值: 操作结果	
	**********************************/
	static BOOL HasInited() {return sm_bHasInited;}

public:
	/**********************************
	描述: 构造函数
			1. 如果它当前的 CAdoObject 对象未打开数据连接, 则会打开数据连接
			2. 把当前线程 ID 绑定到当前 CAdoObject 对象
			3. 增加当前 CAdoObject 对象的引用计数
	参数: 
			Options		: 打开数据连接的参数	默认: 同步方式
	返回值: 	
	**********************************/
	CAdoObjectPool(DWORD nWaitTime = INFINITE)
	: m_padoCurrent(NULL)
	{
		ASSERT(sm_vtAdo.size() > 0);

		CLocalLock<CCriSec> local(sm_csAdo);

		m_padoCurrent = GetFreeAdoObject(nWaitTime);

		if(m_padoCurrent)
			m_padoCurrent->IncReference();
	}

	/**********************************
	描述: 析构函数
			1. 递减当前 CAdoObject 对象的引用计数
			2. 如果当前 CAdoObject 对象的引用计数为 0 则: 
				A. 取消当前 CAdoObject 对象的线程 ID 绑定
				B. 关闭当前 CAdoObject 对象的记录集对象
				C. 关闭当前 CAdoObject 对象的数据库连接对象
	返回值: 	
	**********************************/

	~CAdoObjectPool()
	{
		if(m_padoCurrent && m_padoCurrent->DecReference() == 0)
		{
			sm_mpAdo.erase(::GetCurrentThreadId());
			m_padoCurrent->CloseRecordset();
			m_padoCurrent->CloseConnection();
			m_padoCurrent->SetEvent();
		}
	}

	/**********************************
	描述:	定义指向当前 CAdoObject 对象的智能指针
	返回值: 当前 CAdoObject 对象
	**********************************/
	CAdoObject* operator ->() {return m_padoCurrent;}

	// 对象是否可用
	BOOL IsValid() {return m_padoCurrent != NULL;}

	// 默认数据库连接池大小
	static const DWORD	DEFAULT_CONNECTION_POOL_SIZE = 10;

private:
	/**********************************
	描述:	获取空闲的 CAdoObject 对象
	返回值: 
	**********************************/
	static CAdoObject* GetFreeAdoObject(DWORD nWaitTime = INFINITE)
	{
		size_t poolsize = sm_vtAdo.size();

		ASSERT(poolsize > 0);

		long tid = ::GetCurrentThreadId();
		CAdoObject* pCurrent = NULL;

		// 首先在当前线程中查找被打开的 CAdoObjectPool 对象
		IAdoConstIteratorCM it = sm_mpAdo.find(tid);
		if(it != sm_mpAdo.end())
			pCurrent = it->second;

		while(!pCurrent)
		{
			DWORD retval = ::MsgWaitForMultipleObjectsEx(poolsize, sm_pevtAdo, nWaitTime, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
			
			retval -= WAIT_OBJECT_0;

			if(retval < poolsize)
			{
				pCurrent		= sm_vtAdo[retval];
				sm_mpAdo[tid]	= pCurrent;

				ASSERT(!pCurrent->IsOpened());
			}
			else if(retval == poolsize)
				::PeekMessageLoop();
			else if( retval == WAIT_TIMEOUT - WAIT_OBJECT_0)
				break;
		}

		return pCurrent;
	}

	/**********************************
	描述:	等待连接池内所有的 CAdoObject 对象边为空闲状态
	返回值: 
	**********************************/
	static void WaitAllAdoObjectFree()
	{
		size_t poolsize = sm_vtAdo.size();

		ASSERT(poolsize > 0);

		while(TRUE)
		{
			DWORD retval = ::MsgWaitForMultipleObjectsEx(poolsize, sm_pevtAdo, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE | MWMO_WAITALL);

			retval -= WAIT_OBJECT_0;

			if(retval < poolsize)
			{
				ASSERT(!sm_vtAdo[retval]->IsOpened());

				break;
			}
			else if(retval == poolsize)
				::PeekMessageLoop();
		}
	}

private:
	CAdoObjectPool(const CAdoObjectPool&);
	CAdoObjectPool operator = (const CAdoObjectPool&);

private:
	static BOOL			sm_bHasInited;
	static CInitCOM		sm_comAdo;

	static CCriSec		sm_csAdo;
	static CAdoVector	sm_vtAdo;
	static CAdoMap		sm_mpAdo;

	static HANDLE*		sm_pevtAdo;

	CAdoObject*			m_padoCurrent;
};

