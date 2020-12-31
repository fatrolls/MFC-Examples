//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		AppIdle.cpp
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================

#include "Stdafx.h"

#include "MailMessage.h"
#include "DaoRecordsetCreate.h"


static TCHAR MailMessage[] =
{
	_T("MailMessage")
};

static TCHAR MailMessageSQL[] =
{
	_T("Select * From MailMessage")
};


CMailMessage::CMailMessage()
{
}

CMailMessage::~CMailMessage()
{
}

int CMailMessage::LoadDAO(CDaoDatabase *pDB)
{
	bool nRet = true;
	SMailMessage mail;
	CDaoRecordsetCreate set(pDB);

	try
	{
		set.Open(dbOpenSnapshot,MailMessageSQL,dbReadOnly | dbForwardOnly);

		while(!set.IsEOF())
		{
			ZeroMemory(&mail,sizeof(mail));

			nRet &= set.GetField(_T("SentTime_wYear")			,mail.m_SentTime.wYear);
			nRet &= set.GetField(_T("SentTime_wMonth")			,mail.m_SentTime.wMonth);
			nRet &= set.GetField(_T("SentTime_wDayOfWeek")		,mail.m_SentTime.wDayOfWeek);
			nRet &= set.GetField(_T("SentTime_wDay")			,mail.m_SentTime.wDay);
			nRet &= set.GetField(_T("SentTime_wHour")			,mail.m_SentTime.wHour);
			nRet &= set.GetField(_T("SentTime_wMinute")			,mail.m_SentTime.wMinute);
			nRet &= set.GetField(_T("SentTime_wSecond")			,mail.m_SentTime.wSecond);
			nRet &= set.GetField(_T("SentTime_wMilliseconds")	,mail.m_SentTime.wMilliseconds);
			nRet &= set.GetField(_T("SenderName")	,(mail.m_sSenderName)		,sizeof(mail.m_sSenderName));
			nRet &= set.GetField(_T("SenderMachine"),(mail.m_sSenderMachine)	,sizeof(mail.m_sSenderMachine));
			nRet &= set.GetField(_T("Message")		,(mail.m_sMessage)			,sizeof(mail.m_sMessage));

			Add(mail);
			set.MoveNext();
		}

		set.Close();
	}
	catch(CDaoException *e)
	{
		TRACE_DAO_EXCEPTION(e);

		nRet = 1;
		set.Close();
		e->Delete();
	}

	return nRet;
}

int CMailMessage::LoadDAO(LPCSTR szFileName)
{
	int nRet = 1;
	try
	{
		CDaoDatabase db;
	
		db.Open(szFileName,FALSE,TRUE);

		nRet &= LoadDAO(&db);
		db.Close();
	}
	catch(CDaoException *exDao)
	{
		exDao->ReportError();
		exDao->Delete();
		nRet = 1;
	}
	catch(CMemoryException *exMem)
	{
		exMem->ReportError();
		exMem->Delete();
		nRet = 1;
	}

	return nRet;
}


int CMailMessage::CreateDAO(CDaoDatabase *pDB)
{
	int nRet = 1;
	SMailMessage Desc;
	CDaoRecordsetCreate set(pDB);

	CDaoRecordsetCreate::SFieldInfo fields[] =
	{
		{_T("SentTime_wYear")			, dbInteger, 0, 0},
		{_T("SentTime_wMonth")			, dbInteger, 0, 0},
		{_T("SentTime_wDayOfWeek")		, dbInteger, 0, 0},
		{_T("SentTime_wDay")			, dbInteger, 0, 0},
		{_T("SentTime_wHour")			, dbInteger, 0, 0},
		{_T("SentTime_wMinute")			, dbInteger, 0, 0},
		{_T("SentTime_wSecond")			, dbInteger, 0, 0},
		{_T("SentTime_wMilliseconds")	, dbInteger, 0, 0},
		{_T("SenderName")	, dbText, sizeof(Desc.m_sSenderName), 0},
		{_T("SenderMachine"), dbText, sizeof(Desc.m_sSenderMachine), 0},
		{_T("Message")		, dbText, sizeof(Desc.m_sMessage), 0},
	};
	Desc;

	set.AddField(fields,_countof(fields));
	nRet = set.CreateTable("MailMessage");
	
	return nRet;
}

int CMailMessage::DeleteDAO(CDaoDatabase *pDB)
{
	bool nRet = true;
	CDaoRecordsetCreate set(pDB);

	try
	{
		set.Open(dbOpenDynaset,MailMessageSQL);
		while(!set.IsEOF())
		{
			set.Delete();
			set.MoveNext();
		}
		set.Close();
	}
	catch(CDaoException *e)
	{
		TRACE_DAO_EXCEPTION(e);
		
		nRet = 1;
		set.Close();
		e->Delete();
	}
	return nRet;
}

int CMailMessage::SaveDAO(CDaoDatabase *pDB)
{
	int i;
	bool nRet = true;
	SMailMessage mail;
	CDaoRecordsetCreate set(pDB);
	
	try
	{
		set.Open(dbOpenDynaset,MailMessageSQL,dbAppendOnly);
		
		for(i = 0;i < GetSize();i ++)
		{
			mail = (*this)[i];
			set.AddNew();

			nRet &= set.SetField(_T("SentTime_wYear")			,mail.m_SentTime.wYear);
			nRet &= set.SetField(_T("SentTime_wMonth")			,mail.m_SentTime.wMonth);
			nRet &= set.SetField(_T("SentTime_wDayOfWeek")		,mail.m_SentTime.wDayOfWeek);
			nRet &= set.SetField(_T("SentTime_wDay")			,mail.m_SentTime.wDay);
			nRet &= set.SetField(_T("SentTime_wHour")			,mail.m_SentTime.wHour);
			nRet &= set.SetField(_T("SentTime_wMinute")			,mail.m_SentTime.wMinute);
			nRet &= set.SetField(_T("SentTime_wSecond")			,mail.m_SentTime.wSecond);
			nRet &= set.SetField(_T("SentTime_wMilliseconds")	,mail.m_SentTime.wMilliseconds);
			nRet &= set.SetField(_T("SenderName")	,mail.m_sSenderName);
			nRet &= set.SetField(_T("SenderMachine"),mail.m_sSenderMachine);
			nRet &= set.SetField(_T("Message")		,mail.m_sMessage);
			
			set.Update();
		}
		set.Close();
	}
	catch(CDaoException *e)
	{
		TRACE_DAO_EXCEPTION(e);
		
		nRet = 1;
		set.Close();
		e->Delete();
	}
	return nRet;
}

int CMailMessage::SaveDAO(LPCSTR szFileName)
{
	int nRet = 1;

	try
	{
		CDaoDatabase db;

		try
		{
			db.Open(szFileName);
			nRet &= DeleteDAO(&db);
		}
		catch(CDaoException *exDao)
		{
			exDao->Delete();

			db.Create(szFileName);
			nRet &= CreateDAO(&db);
		}

		nRet &= SaveDAO(&db);

		db.Close();
	}
	catch(CDaoException *exDao)
	{
		exDao->ReportError();
		exDao->Delete();
		nRet = 1;
	}
	catch(CMemoryException *exMem)
	{
		exMem->ReportError();
		exMem->Delete();
		nRet = 1;
	}

	return nRet;
}


SMailMessage& CMailMessage::operator [](int index)
{
	return m_Messages[index];
}

int CMailMessage::GetSize()
{
	return m_Messages.GetSize();
}

int CMailMessage::Add(SMailMessage& mailMessage)
{
	return m_Messages.Add(mailMessage);
}

