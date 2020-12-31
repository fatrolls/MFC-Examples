#include "StdAfx.h"
#include "QQProtocolData.h"

const TCHAR * WEBQQ_APP_ID = _T("1003903");
const TCHAR * WEBQQ_CLIENT_ID = _T("97518388");

QQ_STATUS ConvertToQQStatus(LPCTSTR lpStatus)
{
	if (NULL == lpStatus || NULL == *lpStatus)
		return QQ_STATUS_OFFLINE;

	if (_tcsicmp(lpStatus, QQ_STATUS_STR_ONLINE) == 0)
		return QQ_STATUS_ONLINE;
	else if (_tcsicmp(lpStatus, QQ_STATUS_STR_CALLME) == 0)
		return QQ_STATUS_CALLME;
	else if (_tcsicmp(lpStatus, QQ_STATUS_STR_AWAY) == 0)
		return QQ_STATUS_AWAY;
	else if (_tcsicmp(lpStatus, QQ_STATUS_STR_BUSY) == 0)
		return QQ_STATUS_BUSY;
	else if (_tcsicmp(lpStatus, QQ_STATUS_STR_SILENT) == 0)
		return QQ_STATUS_SILENT;
	else if (_tcsicmp(lpStatus, QQ_STATUS_STR_HIDDEN) == 0)
		return QQ_STATUS_HIDDEN;
	else if (_tcsicmp(lpStatus, QQ_STATUS_STR_OFFLINE) == 0)
		return QQ_STATUS_OFFLINE;
	else
		return QQ_STATUS_OFFLINE;
}

LPCTSTR ConvertToQQStatusStr(QQ_STATUS nStatus)
{
	switch (nStatus)
	{
	case QQ_STATUS_ONLINE:
		return QQ_STATUS_STR_ONLINE;
	case QQ_STATUS_CALLME:
		return QQ_STATUS_STR_CALLME;
	case QQ_STATUS_AWAY:
		return QQ_STATUS_STR_AWAY;
	case QQ_STATUS_BUSY:
		return QQ_STATUS_STR_BUSY;
	case QQ_STATUS_SILENT:
		return QQ_STATUS_STR_SILENT;
	case QQ_STATUS_HIDDEN:
		return QQ_STATUS_STR_HIDDEN;
	case QQ_STATUS_OFFLINE:
		return QQ_STATUS_STR_OFFLINE;
	default:
		return QQ_STATUS_STR_OFFLINE;
	}
}

// 获取HTTP头指定字段名称的值
tstring GetRespHeader(std::vector<tstring>* arrRespHeader, 
					  LPCTSTR lpszName, int nIndex/* = 0*/)
{
	tstring strLine;
	int nNameLen, nIndex2 = 0;

	if (NULL == arrRespHeader || NULL == lpszName)
		return _T("");

	nNameLen = _tcslen(lpszName);
	if (nNameLen <= 0)
		return _T("");

	for (int i = 0; i < (int)arrRespHeader->size(); i++)
	{
		strLine = (*arrRespHeader)[i];
		if (!_tcsnicmp(strLine.c_str(), lpszName, nNameLen))
		{
			if (nIndex == nIndex2)
			{
				int nPos = nNameLen;
				int nLineLen = (int)strLine.size();

				for(; nPos < nLineLen && strLine[nPos] == _T(' '); ++nPos);	// 跳过前导空格
				if (strLine[nPos] == _T(':'))	// 跳过“:”符号
					nPos++;
				for(; nPos < nLineLen && strLine[nPos] == _T(' '); ++nPos);	// 跳过前导空格

				return strLine.substr(nPos);
			}

			nIndex2++;
		}
	}

	return _T("");
}

CVerifyCodeInfo::CVerifyCodeInfo(void)
{
	Reset();
}

CVerifyCodeInfo::~CVerifyCodeInfo(void)
{
}

void CVerifyCodeInfo::Reset()
{
	m_nNeedVerify = 0;
	m_strVerifyCode = _T("");
	m_strVCType = _T("");
}

BOOL CVerifyCodeInfo::Parse(CBuffer * lpBuf)
{
	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	// ptui_checkVC('0','!C4P', '\x00\x00\x00\x00\x32\x87\x00\x6c');

	WCHAR * lpRespDataW = Utf8ToUnicode((const CHAR *)lpBuf->GetData());
	if (NULL == lpRespDataW)
		return FALSE;

	//LPCTSTR lpFmt = _T("ptui_checkVC('%d','%[^']', '%[^']');");
	//_stscanf(lpRespDataW, lpFmt, &m_nNeedVerify, cTemp1, cTemp2);

	tstring str = lpRespDataW;
	delete []lpRespDataW;

	tstring strTemp1, strTemp2, strTemp3;
	
	tstring::size_type nPos1 = str.find(_T("ptui_checkVC('"));
	if (nPos1 != tstring::npos)
	{
		nPos1 += _tcslen(_T("ptui_checkVC('"));
		tstring::size_type nPos2 = str.find(_T("','"), nPos1);
		if (nPos2 != tstring::npos)
		{
			strTemp1 = str.substr(nPos1, nPos2 - nPos1);
			if (!strTemp1.empty())
				m_nNeedVerify = ::_tcstol(strTemp1.c_str(), NULL, 10);

			nPos1 = nPos2+_tcslen(_T("','"));
			nPos2 = str.find(_T("','"), nPos1);
			if (nPos2 != tstring::npos)
			{
				strTemp2 = str.substr(nPos1, nPos2 - nPos1);

				nPos1 = nPos2+_tcslen(_T("','"));
				nPos2 = str.find(_T("');"), nPos1);
				if (nPos2 != tstring::npos)
					strTemp3 = str.substr(nPos1, nPos2 - nPos1);
			}
		}
	}

	if (m_nNeedVerify == 0)		// 不需要验证码
	{
		m_strVCType = _T("");
		m_strVerifyCode = strTemp2;
	}
	else
	{
		m_strVCType = strTemp2;
		m_strVerifyCode = _T("");
	}

	m_nPtUinLen = sizeof(m_cPtUin) / sizeof(CHAR);
	return ParsePtUin(strTemp3.c_str(), m_cPtUin, m_nPtUinLen);
}

BOOL CVerifyCodeInfo::ParsePtUin(const TCHAR * lpInPtUin, CHAR * lpOutPtUin, int& nOutPtUinLen)
{
	nOutPtUinLen = 0;

	if (NULL == lpOutPtUin)
		return FALSE;

	memset(lpOutPtUin, 0, nOutPtUinLen);

	if (NULL == lpInPtUin || NULL == *lpInPtUin)
		return FALSE;

	TCHAR cTemp[3] = {0};

	int nInPtUinLen = _tcslen(lpInPtUin);
	for (int i = 0; i < nInPtUinLen; i++)
	{
		if (lpInPtUin[i] == _T('\\') && lpInPtUin[i+1] == _T('x'))
		{
			i += 2;
			if (i + 1 < nInPtUinLen && isalnum(lpInPtUin[i]) && isalnum(lpInPtUin[i+1]))
			{
				cTemp[0] = lpInPtUin[i];
				cTemp[1] = lpInPtUin[i+1];
				cTemp[2] = _T('\0');
				lpOutPtUin[m_nPtUinLen] = _tcstol(cTemp, NULL, 16);
				m_nPtUinLen++;
				i += 1;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}

	return TRUE;
}

CLoginResult_1::CLoginResult_1(void)
{
	Reset();
}

CLoginResult_1::~CLoginResult_1(void)
{

}

void CLoginResult_1::Reset()
{
	m_nRetCode = 0;
	m_strMsg = _T("");
	m_strPtWebQq = _T("");
	m_strSKey = _T("");
}

BOOL CLoginResult_1::Parse(CBuffer * lpBuf, std::vector<tstring>* arrRespHeader)
{
	if (NULL == lpBuf || lpBuf->GetData() == NULL 
		|| lpBuf->GetSize() <= 0 || NULL == arrRespHeader)
		return FALSE;

	Reset();

	WCHAR * lpRespDataW = Utf8ToUnicode((const CHAR *)lpBuf->GetData());
	if (NULL == lpRespDataW)
		return FALSE;

	LPCTSTR lpFmt = _T("ptuiCB('%d',%*[^,],%*[^,],%*[^,],'%[^']');");
	int nRetCode = -1;
	TCHAR cMsg[1024] = {0};

	_stscanf(lpRespDataW, lpFmt, &nRetCode, cMsg);
	delete []lpRespDataW;

	m_nRetCode = nRetCode;
	m_strMsg = cMsg;

//	HTTP/1.1 200 OK
//	Date: Tue, 26 Mar 2013 04:08:43 GMT
//  Server: Tencent Login Server/2.0.0
//  P3P: CP="CAO PSA OUR"
//  Set-Cookie: pt2gguin=o0847708268; EXPIRES=Fri, 02-Jan-2020 00:00:00 GMT; PATH=/; DOMAIN=qq.com;
//  Set-Cookie: uin=o0847708268; PATH=/; DOMAIN=qq.com;
//	Set-Cookie: skey=@9Nf6S5Mqa; PATH=/; DOMAIN=qq.com;
//	Set-Cookie: ETK=; PATH=/; DOMAIN=ptlogin2.qq.com;
//	Set-Cookie: ptuserinfo=e5beaee5b098; PATH=/; DOMAIN=ptlogin2.qq.com;
//	Set-Cookie: ptwebqq=b6940e2d89ca07990a9f3edc04c335763a67a97746a573b0afcce74ea46a46e6; PATH=/; DOMAIN=qq.com;
//  Pragma: no-cache
//	Cache-Control: no-cache; must-revalidate
//  Connection: Close
//	Content-Type: application/x-javascript; charset=utf-8

	tstring strCookie;
	tstring::size_type nPos;
	int nIndex = 0;

	while (1)
	{
		strCookie = GetRespHeader(arrRespHeader, _T("Set-Cookie"), nIndex);
		if (strCookie == _T(""))
			break;

		nPos = strCookie.find(_T("ptwebqq"));
		if (nPos != tstring::npos)
			m_strPtWebQq = GetBetweenString(strCookie.c_str()+nPos+7, _T("="), _T(";"));

		nPos = strCookie.find(_T("skey"));
		if (nPos != tstring::npos)
			m_strSKey = GetBetweenString(strCookie.c_str()+nPos+4, _T("="), _T(";"));

		nIndex++;
	}

	return TRUE;
}

CLoginResult_2::CLoginResult_2(void)
{
	Reset();
}

CLoginResult_2::~CLoginResult_2(void)
{

}

void CLoginResult_2::Reset()
{
	m_nRetCode = 0;
	m_nUIN = 0;
	m_nCIP = 0;
	m_nIndex = 0;
	m_nPort = 0;
	m_nStatus = QQ_STATUS_OFFLINE;
	m_strVfWebQq = _T("");
	m_strPSessionId = _T("");
	m_nUser_State = 0;
	m_f = 0;
	m_nServerTime = -1;
	m_dwTickCount = 0;
}

BOOL CLoginResult_2::Parse(CBuffer * lpBuf, std::vector<tstring>* arrRespHeader)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL 
		|| lpBuf->GetSize() <= 0 || NULL == arrRespHeader)
		return FALSE;

	Reset();

	tstring strDate = GetRespHeader(arrRespHeader, _T("Date"));
	if (!strDate.empty())
		m_nServerTime = httpdate_parse(strDate.c_str());
	if (-1 == m_nServerTime)
		m_nServerTime = ::time(NULL);
	m_dwTickCount = ::GetTickCount();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["uin"].isNull())
				m_nUIN = JsonValue["uin"].asUInt();

			if (!JsonValue["cip"].isNull())
				m_nCIP = JsonValue["cip"].asUInt();

			if (!JsonValue["index"].isNull())
				m_nIndex = JsonValue["index"].asInt();

			if (!JsonValue["port"].isNull())
				m_nPort = JsonValue["port"].asInt();

			if (!JsonValue["status"].isNull())
			{
				strValue = JsonValue["status"].asString();
				m_nStatus = ConvertToQQStatus(Utf8ToUnicode(strValue).c_str());
			}

			if (!JsonValue["vfwebqq"].isNull())
			{
				strValue = JsonValue["vfwebqq"].asString();
				m_strVfWebQq = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["psessionid"].isNull())
			{
				strValue = JsonValue["psessionid"].asString();
				m_strPSessionId = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["user_state"].isNull())
				m_nUser_State = JsonValue["user_state"].asInt();

			if(!JsonValue["f"].isNull())
				m_f = JsonValue["f"].asInt();
		}
	}

	return TRUE;
}

CLogoutResult::CLogoutResult(void)
{
	Reset();
}

CLogoutResult::~CLogoutResult(void)
{

}

void CLogoutResult::Reset()
{
	m_nRetCode = 0;
	m_strResult = _T("");
}

BOOL CLogoutResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if(!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if(!JsonValue["result"].isNull())
		{
			strValue = JsonValue["result"].asString();
			m_strResult = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

COnlineBuddyListResult::COnlineBuddyListResult(void)
{
	Reset();
}

COnlineBuddyListResult::~COnlineBuddyListResult(void)
{
	Reset();
}

void COnlineBuddyListResult::Reset()
{
	m_nRetCode = 0;

	for (int i = 0; i < (int)m_arrOnlineBuddyInfo.size(); i++)
	{
		if (m_arrOnlineBuddyInfo[i] != NULL)
			delete m_arrOnlineBuddyInfo[i];
	}
	m_arrOnlineBuddyInfo.clear();
}

BOOL COnlineBuddyListResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			for (int i = 0; i < (int)JsonValue.size(); i++)
			{
				COnlineBuddyInfo * lpOnlineBuddyInfo = new COnlineBuddyInfo;
				if (lpOnlineBuddyInfo != NULL)
				{
					lpOnlineBuddyInfo->Reset();

					if (!JsonValue[i]["uin"].isNull())
						lpOnlineBuddyInfo->m_nUin = JsonValue[i]["uin"].asUInt();

					if (!JsonValue[i]["status"].isNull())
					{
						strValue = JsonValue[i]["status"].asString();
						lpOnlineBuddyInfo->m_nStatus = ConvertToQQStatus(Utf8ToUnicode(strValue).c_str());
					}

					if (!JsonValue[i]["client_type"].isNull())
						lpOnlineBuddyInfo->m_nClientType = JsonValue[i]["client_type"].asUInt();

					m_arrOnlineBuddyInfo.push_back(lpOnlineBuddyInfo);
				}
			}
		}
	}

	return TRUE;
}

CBuddyListResult::CBuddyListResult(void)
{
	Reset();
}

CBuddyListResult::~CBuddyListResult(void)
{
	Reset();
}

void CBuddyListResult::Reset()
{
	m_nRetCode = 0;

	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpBuddyTeamInfo != NULL)
			delete lpBuddyTeamInfo;
	}
	m_arrBuddyTeamInfo.clear();
}

BOOL CBuddyListResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue, valueFriends, valueMarkNames;
	Json::Value valueCategories, valueVipInfo, valueInfo;
	std::string strText, strValue;
	CBuddyInfo * lpBuddyInfo;
	CBuddyTeamInfo * lpBuddyTeamInfo;
	UINT nQQUin;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		valueCategories = JsonValue["result"]["categories"];
		if (!valueCategories.isNull())
		{
			for (int i = 0; i < (int)valueCategories.size(); ++i)
			{
				lpBuddyTeamInfo = new CBuddyTeamInfo;
				if (lpBuddyTeamInfo != NULL)
				{
					lpBuddyTeamInfo->Reset();

					if(!valueCategories[i]["index"].isNull())
						lpBuddyTeamInfo->m_nIndex = valueCategories[i]["index"].asInt();

					if(!valueCategories[i]["sort"].isNull())
						lpBuddyTeamInfo->m_nSort = valueCategories[i]["sort"].asInt();

					if(!valueCategories[i]["name"].isNull())
					{
						strValue = valueCategories[i]["name"].asString();
						lpBuddyTeamInfo->m_strName = Utf8ToUnicode(strValue);
					}

					m_arrBuddyTeamInfo.push_back(lpBuddyTeamInfo);
				}
			}
		}

		lpBuddyTeamInfo = GetBuddyTeamByInnerIndex(0);
		if (NULL == lpBuddyTeamInfo)
		{
			lpBuddyTeamInfo = new CBuddyTeamInfo;
			if (lpBuddyTeamInfo != NULL)
			{
				lpBuddyTeamInfo->m_nIndex = 0;
				lpBuddyTeamInfo->m_nSort = 0;
				lpBuddyTeamInfo->m_strName = _T("我的好友");
				m_arrBuddyTeamInfo.push_back(lpBuddyTeamInfo);
			}
		}
		SortBuddyTeam();

		valueFriends = JsonValue["result"]["friends"];
		if (!valueFriends.isNull())
		{
			for (int i = 0; i < (int)valueFriends.size(); ++i)
			{
				lpBuddyInfo = new CBuddyInfo;
				if (lpBuddyInfo != NULL)
				{
					lpBuddyInfo->Reset();

					if (!valueFriends[i]["uin"].isNull())
						lpBuddyInfo->m_nQQUin = valueFriends[i]["uin"].asUInt();

					if(!valueFriends[i]["categories"].isNull())
						lpBuddyInfo->m_nTeamIndex = valueFriends[i]["categories"].asInt();

					lpBuddyTeamInfo = GetBuddyTeamByInnerIndex(lpBuddyInfo->m_nTeamIndex);
					if (lpBuddyTeamInfo != NULL)
						lpBuddyTeamInfo->m_arrBuddyInfo.push_back(lpBuddyInfo);
					else
						delete lpBuddyInfo;
				}
			}
		}

		valueMarkNames = JsonValue["result"]["marknames"];
		if (!valueMarkNames.isNull())
		{
			for (int i = 0; i < (int)valueMarkNames.size(); ++i)
			{
				if (!valueMarkNames[i]["uin"].isNull())
					nQQUin = valueMarkNames[i]["uin"].asUInt();
				else
					nQQUin = 0;

				lpBuddyInfo = GetBuddy(nQQUin);
				if (lpBuddyInfo != NULL)
				{
					if (!valueMarkNames[i]["markname"].isNull())
					{
						strValue = valueMarkNames[i]["markname"].asString();
						lpBuddyInfo->m_strMarkName = Utf8ToUnicode(strValue);
					}
				}
			}
		}

		valueVipInfo = JsonValue["result"]["vipinfo"];
		if (!valueVipInfo.isNull())
		{
			for (int i = 0; i < (int)valueVipInfo.size(); ++i)
			{
				if (!valueVipInfo[i]["u"].isNull())
					nQQUin = valueVipInfo[i]["u"].asUInt();
				else
					nQQUin = 0;

				lpBuddyInfo = GetBuddy(nQQUin);
				if (lpBuddyInfo != NULL)
				{
					if (!valueVipInfo[i]["is_vip"].isNull())
						lpBuddyInfo->m_bIsVip = valueVipInfo[i]["is_vip"].asBool();

					if(!valueVipInfo[i]["vip_level"].isNull())
						lpBuddyInfo->m_nVipLevel = valueVipInfo[i]["vip_level"].asInt();
				}
			}
		}

		valueInfo = JsonValue["result"]["info"];
		if (!valueInfo.isNull())
		{
			for (int i = 0; i < (int)valueInfo.size(); ++i)
			{
				if(!valueInfo[i]["uin"].isNull())
					nQQUin = valueInfo[i]["uin"].asUInt();
				else
					nQQUin = 0;

				lpBuddyInfo = GetBuddy(nQQUin);
				if (lpBuddyInfo != NULL)
				{
					if(!valueInfo[i]["face"].isNull())
						lpBuddyInfo->m_nFace = valueInfo[i]["face"].asInt();

					if(!valueInfo[i]["flag"].isNull())
						lpBuddyInfo->m_dwFlag = valueInfo[i]["flag"].asUInt();

					if(!valueInfo[i]["nick"].isNull())
					{
						strValue = valueInfo[i]["nick"].asString();
						lpBuddyInfo->m_strNickName = Utf8ToUnicode(strValue);
					}
				}
			}
		}
	}

	return TRUE;
}

int CBuddyListResult::GetBuddyTeamCount()
{
	return m_arrBuddyTeamInfo.size();
}

CBuddyTeamInfo * CBuddyListResult::GetBuddyTeam(int nTeamIndex)
{
	if (nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamInfo.size())
		return m_arrBuddyTeamInfo[nTeamIndex];
	else
		return NULL;
}

CBuddyTeamInfo * CBuddyListResult::GetBuddyTeamByInnerIndex(int nInnerTeamIndex)
{
	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpBuddyTeamInfo != NULL && nInnerTeamIndex == lpBuddyTeamInfo->m_nIndex)
			return lpBuddyTeamInfo;
	}
	return NULL;
}

int CBuddyListResult::GetBuddyCount(int nTeamIndex)
{
	CBuddyTeamInfo * lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
	if (lpBuddyTeamInfo != NULL)
		return lpBuddyTeamInfo->GetBuddyCount();
	else
		return 0;
}

int CBuddyListResult::GetOnlineBuddyCount(int nTeamIndex)
{
	CBuddyTeamInfo * lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
	if (lpBuddyTeamInfo != NULL)
		return lpBuddyTeamInfo->GetOnlineBuddyCount();
	else
		return 0;
}

CBuddyInfo * CBuddyListResult::GetBuddy(int nTeamIndex, int nIndex)
{
	CBuddyTeamInfo * lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
	if (lpBuddyTeamInfo != NULL)
		return lpBuddyTeamInfo->GetBuddy(nIndex);
	else
		return NULL;
}

CBuddyInfo * CBuddyListResult::GetBuddy(UINT nQQUin)
{
	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpBuddyTeamInfo != NULL)
		{
			for (int j = 0; j < (int)lpBuddyTeamInfo->m_arrBuddyInfo.size(); j++)
			{
				CBuddyInfo * lpBuddyInfo = lpBuddyTeamInfo->m_arrBuddyInfo[j];
				if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)
					return lpBuddyInfo;
			}
		}

	}
	return NULL;
}

BOOL CBuddyListResult::SetOnlineBuddyList(COnlineBuddyListResult * lpOnlineBuddyListResult)
{
	if (NULL == lpOnlineBuddyListResult)
		return FALSE;

	for (int i = 0; i < (int)lpOnlineBuddyListResult->m_arrOnlineBuddyInfo.size(); i++)
	{
		COnlineBuddyInfo * lpOnlineBuddyInfo = lpOnlineBuddyListResult->m_arrOnlineBuddyInfo[i];
		if (lpOnlineBuddyInfo != NULL)
		{
			CBuddyInfo * lpBuddyInfo = GetBuddy(lpOnlineBuddyInfo->m_nUin);
			if (lpBuddyInfo != NULL)
			{
				lpBuddyInfo->m_nClientType = lpOnlineBuddyInfo->m_nClientType;
				lpBuddyInfo->m_nStatus = lpOnlineBuddyInfo->m_nStatus;
			}
		}
	}
	return TRUE;
}

void CBuddyListResult::SortBuddyTeam()
{
	CBuddyTeamInfo * lpBuddyTeamInfo1, * lpBuddyTeamInfo2;
	BOOL bExchange;
	int nCount;

	nCount = (int)m_arrBuddyTeamInfo.size();
	for (int i = 0; i < nCount-1; i++)
	{
		bExchange = FALSE;
		for (int j = nCount-1; j > i; j--)
		{
			lpBuddyTeamInfo1 = m_arrBuddyTeamInfo[j-1];
			lpBuddyTeamInfo2 = m_arrBuddyTeamInfo[j];
			if (lpBuddyTeamInfo1 != NULL && lpBuddyTeamInfo2 != NULL)
			{
				if (lpBuddyTeamInfo2->m_nSort < lpBuddyTeamInfo1->m_nSort)
				{
					m_arrBuddyTeamInfo[j-1] = lpBuddyTeamInfo2;
					m_arrBuddyTeamInfo[j] = lpBuddyTeamInfo1;
					bExchange = TRUE;
				}
			}
		}
		if (!bExchange)
			break;
	}
}

void CBuddyListResult::SortBuddy()
{
	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpTeamInfo != NULL)
			lpTeamInfo->Sort();
	}
}

CGroupListResult::CGroupListResult(void)
{
	Reset();
}

CGroupListResult::~CGroupListResult(void)
{
	Reset();
}

void CGroupListResult::Reset()
{
	m_nRetCode = 0;

	for (int i = 0; i < (int)m_arrGroupInfo.size(); i++)
	{
		CGroupInfo * lpGroupInfo = m_arrGroupInfo[i];
		if (lpGroupInfo != NULL)
			delete lpGroupInfo;
	}
	m_arrGroupInfo.clear();
}

BOOL CGroupListResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"]["gnamelist"].isNull())
		{
			JsonValue = JsonValue["result"]["gnamelist"];

			for (int i = 0; i < (int)JsonValue.size(); i++)
			{
				CGroupInfo * lpGroupInfo = new CGroupInfo;
				if (lpGroupInfo != NULL)
				{
					lpGroupInfo->Reset();

					if (!JsonValue[i]["flag"].isNull())
						lpGroupInfo->m_nFlag = JsonValue[i]["flag"].asUInt();

					if (!JsonValue[i]["name"].isNull())
					{
						strValue = JsonValue[i]["name"].asString();
						lpGroupInfo->m_strName = Utf8ToUnicode(strValue);
					}

					if (!JsonValue[i]["gid"].isNull())
						lpGroupInfo->m_nGroupId = JsonValue[i]["gid"].asUInt();

					if (!JsonValue[i]["code"].isNull())
						lpGroupInfo->m_nGroupCode = JsonValue[i]["code"].asUInt();

					m_arrGroupInfo.push_back(lpGroupInfo);
				}
			}
		}
	}

	return TRUE;
}

// 获取群总数
int CGroupListResult::GetGroupCount()
{
	return (int)m_arrGroupInfo.size();
}

// 根据索引获取群信息
CGroupInfo * CGroupListResult::GetGroup(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrGroupInfo.size())
		return m_arrGroupInfo[nIndex];
	else
		return NULL;
}

CRecentListResult::CRecentListResult(void)
{
	Reset();
}

CRecentListResult::~CRecentListResult(void)
{
	Reset();
}

void CRecentListResult::Reset()
{
	m_nRetCode = 0;

	for (int i = 0; i < (int)m_arrRecentInfo.size(); i++)
	{
		if (m_arrRecentInfo[i] != NULL)
			delete m_arrRecentInfo[i];
	}
	m_arrRecentInfo.clear();
}

BOOL CRecentListResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			for (int i = 0; i < (int)JsonValue.size(); i++)
			{
				CRecentInfo * lpRecentInfo = new CRecentInfo;
				if (lpRecentInfo != NULL)
				{
					lpRecentInfo->Reset();

					if (!JsonValue[i]["uin"].isNull())
						lpRecentInfo->m_nQQUin = JsonValue[i]["uin"].asUInt();

					if (!JsonValue[i]["type"].isNull())
						lpRecentInfo->m_nType = JsonValue[i]["type"].asUInt();

					m_arrRecentInfo.push_back(lpRecentInfo);
				}
			}
		}
	}

	return TRUE;
}

CGetQQNumResult::CGetQQNumResult(void)
{
	Reset();
}

CGetQQNumResult::~CGetQQNumResult(void)
{

}

void CGetQQNumResult::Reset()
{
	m_nRetCode = 0;
	m_nQQUin = 0;
	m_nQQNum = 0;
}

BOOL CGetQQNumResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["account"].isNull())
				m_nQQNum = JsonValue["account"].asUInt();

			if (!JsonValue["uin"].isNull())
				m_nQQUin = JsonValue["uin"].asUInt();
		}
	}

	return TRUE;
}

CGetSignResult::CGetSignResult(void)
{
	Reset();
}

CGetSignResult::~CGetSignResult(void)
{

}

void CGetSignResult::Reset()
{
	m_nRetCode = 0;
	m_nQQUin = 0;
	m_strSign = _T("");
}

BOOL CGetSignResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"][(UINT)0].isNull())
		{
			JsonValue = JsonValue["result"][(UINT)0];

			if (!JsonValue["uin"].isNull())
				m_nQQUin = JsonValue["uin"].asUInt();

			if (!JsonValue["lnick"].isNull())
			{
				strValue = JsonValue["lnick"].asString();
				m_strSign = Utf8ToUnicode(strValue);
			}
		}
	}

	return TRUE;
}

CSetSignResult::CSetSignResult(void)
{
	Reset();
}

CSetSignResult::~CSetSignResult(void)
{

}

void CSetSignResult::Reset()
{
	m_nRetCode = 0;
	m_nResult = 0;
}

BOOL CSetSignResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			if (!JsonValue["result"]["result"].isNull())
				m_nResult = JsonValue["result"]["result"].asInt();
		}
	}

	return TRUE;
}

CBuddyInfoResult::CBuddyInfoResult(void)
{
	Reset();
}

CBuddyInfoResult::~CBuddyInfoResult(void)
{

}

void CBuddyInfoResult::Reset()
{
	m_nRetCode = 0;
	m_nQQUin = 0;
	m_strNickName = _T("");
	m_nFace = 0;
	m_strGender = _T("");
	m_nShengXiao = 0;
	m_nConstel = 0;
	m_nBlood = 0;
	m_strBirthday = _T("");
	m_strCountry = _T("");
	m_strProvince = _T("");
	m_strCity = _T("");
	m_strPhone = _T("");
	m_strMobile = _T("");
	m_strEmail = _T("");
	m_strOccupation = _T("");
	m_strCollege = _T("");
	m_strHomepage = _T("");
	m_strPersonal = _T("");
	m_bAllow = FALSE;
	m_nRegTime = 0;
	m_nStat = 0;
	m_nVipInfo = 0;
	m_nClientType = 0;
	m_strToken = _T("");
}

BOOL CBuddyInfoResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["face"].isNull())
				m_nFace = JsonValue["face"].asInt();

			if (!JsonValue["birthday"].isNull())
			{
				int nYear = 1970, nMonth = 1, nDay = 1;
				TCHAR cTemp[16] = {0};

				if (!JsonValue["birthday"]["year"].isNull())
					nYear = JsonValue["birthday"]["year"].asInt();
				if (!JsonValue["birthday"]["month"].isNull())
					nMonth = JsonValue["birthday"]["month"].asInt();
				if (!JsonValue["birthday"]["day"].isNull())
					nDay = JsonValue["birthday"]["day"].asInt();

				wsprintf(cTemp, _T("%d年%d月%d日"), nYear, nMonth, nDay);
				m_strBirthday = cTemp;
			}

			if (!JsonValue["occupation"].isNull())
			{
				strValue = JsonValue["occupation"].asString();
				m_strOccupation = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["phone"].isNull())
			{
				strValue = JsonValue["phone"].asString();
				m_strPhone = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["allow"].isNull())
				m_bAllow = JsonValue["allow"].asInt();

			if (!JsonValue["college"].isNull())
			{
				strValue = JsonValue["college"].asString();
				m_strCollege = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["reg_time"].isNull())
				m_nRegTime = JsonValue["reg_time"].asUInt();

			if (!JsonValue["uin"].isNull())
				m_nQQUin = JsonValue["uin"].asUInt();

			if (!JsonValue["constel"].isNull())
				m_nConstel = JsonValue["constel"].asInt();

			if (!JsonValue["blood"].isNull())
				m_nBlood = JsonValue["blood"].asInt();

			if (!JsonValue["homepage"].isNull())
			{
				strValue = JsonValue["homepage"].asString();
				m_strHomepage = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["stat"].isNull())
				m_nStat = JsonValue["stat"].asInt();

			if (!JsonValue["vip_info"].isNull())
				m_nVipInfo = JsonValue["vip_info"].asInt();

			if (!JsonValue["country"].isNull())
			{
				strValue = JsonValue["country"].asString();
				m_strCountry = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["city"].isNull())
			{
				strValue = JsonValue["city"].asString();
				m_strCity = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["personal"].isNull())
			{
				strValue = JsonValue["personal"].asString();
				m_strPersonal = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["nick"].isNull())
			{
				strValue = JsonValue["nick"].asString();
				m_strNickName = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["shengxiao"].isNull())
				m_nShengXiao = JsonValue["shengxiao"].asInt();

			if (!JsonValue["email"].isNull())
			{
				strValue = JsonValue["email"].asString();
				m_strEmail = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["province"].isNull())
			{
				strValue = JsonValue["province"].asString();
				m_strProvince = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["gender"].isNull())
			{
				strValue = JsonValue["gender"].asString();
				m_strGender = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["mobile"].isNull())
			{
				strValue = JsonValue["mobile"].asString();
				m_strMobile = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["client_type"].isNull())
				m_nClientType = JsonValue["client_type"].asInt();

			if (!JsonValue["token"].isNull())
			{
				strValue = JsonValue["token"].asString();
				m_strToken = Utf8ToUnicode(strValue);
			}
		}
	}

	return TRUE;
}

CGroupInfoResult::CGroupInfoResult(void)
{
	Reset();
}

CGroupInfoResult::~CGroupInfoResult(void)
{
	Reset();
}

void CGroupInfoResult::Reset()
{
	m_nRetCode = 0;
	m_nGroupCode = 0;
	m_nGroupId = 0;
	m_strName = _T("");
	m_strMemo = _T("");
	m_strFingerMemo = _T("");
	m_nOwnerUin = 0;
	m_nCreateTime = 0;
	m_nFace = 0;
	m_nLevel = 0;
	m_nClass = 0;
	m_nOption = 0;
	m_nFlag = 0;

	for (int i = 0; i < (int)m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrMember[i];
		if (lpBuddyInfo != NULL)
			delete lpBuddyInfo;
	}
	m_arrMember.clear();
}

BOOL CGroupInfoResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue, JsonValue2;
	std::string strText, strValue;
	CBuddyInfo * lpBuddyInfo;
	UINT nQQUin;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["ginfo"].isNull())
			{
				JsonValue2 = JsonValue["ginfo"];

				if (!JsonValue2["face"].isNull())
					m_nFace = JsonValue2["face"].asInt();

				if (!JsonValue2["memo"].isNull())
				{
					strValue = JsonValue2["memo"].asString();
					Replace(strValue, "\r", "\r\n");
					m_strMemo = Utf8ToUnicode(strValue);
				}

				if (!JsonValue2["class"].isNull())
					m_nClass = JsonValue2["class"].asInt();

				if (!JsonValue2["fingermemo"].isNull())
				{
					strValue = JsonValue2["fingermemo"].asString();
					Replace(strValue, "\r", "\r\n");
					m_strFingerMemo = Utf8ToUnicode(strValue);
				}

				if (!JsonValue2["code"].isNull())
					m_nGroupCode = JsonValue2["code"].asUInt();

				if (!JsonValue2["createtime"].isNull())
					m_nCreateTime = JsonValue2["createtime"].asUInt();

				if (!JsonValue2["flag"].isNull())
					m_nFlag = JsonValue2["flag"].asUInt();

				if (!JsonValue2["level"].isNull())
					m_nLevel = JsonValue2["level"].asUInt();

				if (!JsonValue2["name"].isNull())
				{
					strValue = JsonValue2["name"].asString();
					m_strName = Utf8ToUnicode(strValue);
				}

				if (!JsonValue2["gid"].isNull())
					m_nGroupId = JsonValue2["gid"].asUInt();

				if (!JsonValue2["owner"].isNull())
					m_nOwnerUin = JsonValue2["owner"].asUInt();

				if (!JsonValue2["option"].isNull())
					m_nOption = JsonValue2["option"].asUInt();

				if (!JsonValue2["members"].isNull())
				{
					JsonValue2 = JsonValue2["members"];
					for (int i = 0; i < (int)JsonValue2.size(); i++)
					{
						lpBuddyInfo = new CBuddyInfo;
						if (lpBuddyInfo != NULL)
						{
							lpBuddyInfo->Reset();

							if (!JsonValue2[i]["muin"].isNull())
								lpBuddyInfo->m_nQQUin = JsonValue2[i]["muin"].asUInt();

							if (!JsonValue2[i]["mflag"].isNull())
								lpBuddyInfo->m_nGroupFlag = JsonValue2[i]["mflag"].asUInt();

							m_arrMember.push_back(lpBuddyInfo);
						}
					}
				}
			}

			if (!JsonValue["stats"].isNull())
			{
				JsonValue2 = JsonValue["stats"];
				for (int i = 0; i < (int)JsonValue2.size(); i++)
				{
					if (!JsonValue2[i]["uin"].isNull())
						nQQUin = JsonValue2[i]["uin"].asUInt();
					else
						nQQUin = 0;

					lpBuddyInfo = GetMemberByUin(nQQUin);
					if (lpBuddyInfo != NULL)
					{
						if (!JsonValue2[i]["client_type"].isNull())
							lpBuddyInfo->m_nClientType = JsonValue2[i]["client_type"].asInt();

						if (!JsonValue2[i]["stat"].isNull())
							lpBuddyInfo->m_nStatus = (QQ_STATUS)JsonValue2[i]["stat"].asInt();
					}
				}
			}

			if (!JsonValue["minfo"].isNull())
			{
				JsonValue2 = JsonValue["minfo"];
				for (int i = 0; i < (int)JsonValue2.size(); i++)
				{
					if (!JsonValue2[i]["uin"].isNull())
						nQQUin = JsonValue2[i]["uin"].asUInt();
					else
						nQQUin = 0;

					lpBuddyInfo = GetMemberByUin(nQQUin);
					if (lpBuddyInfo != NULL)
					{
						if (!JsonValue2[i]["nick"].isNull())
						{
							strValue = JsonValue2[i]["nick"].asString();
							lpBuddyInfo->m_strNickName = Utf8ToUnicode(strValue);
						}

						if (!JsonValue2[i]["province"].isNull())
						{
							strValue = JsonValue2[i]["province"].asString();
							lpBuddyInfo->m_strProvince = Utf8ToUnicode(strValue);
						}

						if (!JsonValue2[i]["gender"].isNull())
						{
							strValue = JsonValue2[i]["gender"].asString();
							lpBuddyInfo->m_strGender = Utf8ToUnicode(strValue);
						}

						if (!JsonValue2[i]["country"].isNull())
						{
							strValue = JsonValue2[i]["country"].asString();
							lpBuddyInfo->m_strCountry = Utf8ToUnicode(strValue);
						}

						if (!JsonValue2[i]["city"].isNull())
						{
							strValue = JsonValue2[i]["city"].asString();
							lpBuddyInfo->m_strCity = Utf8ToUnicode(strValue);
						}
					}
				}
			}

			if (!JsonValue["cards"].isNull())
			{
				JsonValue2 = JsonValue["cards"];
				for (int i = 0; i < (int)JsonValue2.size(); i++)
				{
					if (!JsonValue2[i]["muin"].isNull())
						nQQUin = JsonValue2[i]["muin"].asUInt();
					else
						nQQUin = 0;

					lpBuddyInfo = GetMemberByUin(nQQUin);
					if (lpBuddyInfo != NULL)
					{
						if (!JsonValue2[i]["card"].isNull())
						{
							strValue = JsonValue2[i]["card"].asString();
							lpBuddyInfo->m_strGroupCard = Utf8ToUnicode(strValue);
						}
					}
				}
			}

			if (!JsonValue["vipinfo"].isNull())
			{
				JsonValue2 = JsonValue["vipinfo"];
				for (int i = 0; i < (int)JsonValue2.size(); i++)
				{
					if (!JsonValue2[i]["u"].isNull())
						nQQUin = JsonValue2[i]["u"].asUInt();
					else
						nQQUin = 0;

					lpBuddyInfo = GetMemberByUin(nQQUin);
					if (lpBuddyInfo != NULL)
					{
						if (!JsonValue2[i]["vip_level"].isNull())
							lpBuddyInfo->m_nVipLevel = JsonValue2[i]["vip_level"].asInt();

						if (!JsonValue2[i]["is_vip"].isNull())
							lpBuddyInfo->m_bIsVip = JsonValue2[i]["is_vip"].asInt();
					}
				}
			}
		}
	}

	return TRUE;
}

CBuddyInfo * CGroupInfoResult::GetMemberByUin(UINT nQQUin)
{
	for (int i = 0; i < (int)m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrMember[i];
		if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)
			return lpBuddyInfo;
	}
	return NULL;
}

CSendBuddyMsgResult::CSendBuddyMsgResult(void)
{
	Reset();
}

CSendBuddyMsgResult::~CSendBuddyMsgResult(void)
{

}

void CSendBuddyMsgResult::Reset()
{
	m_nRetCode = 0;
	m_strResult = _T("");
}

BOOL CSendBuddyMsgResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if(!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if(!JsonValue["result"].isNull())
		{
			strValue = JsonValue["result"].asString();
			m_strResult = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

CSendGroupMsgResult::CSendGroupMsgResult(void)
{
	Reset();
}

CSendGroupMsgResult::~CSendGroupMsgResult(void)
{

}

void CSendGroupMsgResult::Reset()
{
	m_nRetCode = 0;
	m_strResult = _T("");
}

BOOL CSendGroupMsgResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if(!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if(!JsonValue["result"].isNull())
		{
			strValue = JsonValue["result"].asString();
			m_strResult = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

CSendSessMsgResult::CSendSessMsgResult(void)
{
	Reset();
}

CSendSessMsgResult::~CSendSessMsgResult(void)
{

}

void CSendSessMsgResult::Reset()
{
	m_nRetCode = 0;
	m_strResult = _T("");
}

BOOL CSendSessMsgResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if(!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if(!JsonValue["result"].isNull())
		{
			strValue = JsonValue["result"].asString();
			m_strResult = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

CChangeStatusResult::CChangeStatusResult(void)
{
	Reset();
}

CChangeStatusResult::~CChangeStatusResult(void)
{

}

void CChangeStatusResult::Reset()
{
	m_nRetCode = 0;
	m_strResult = _T("");
}

BOOL CChangeStatusResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if(!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if(!JsonValue["result"].isNull())
		{
			strValue = JsonValue["result"].asString();
			m_strResult = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

CGetC2CMsgSigResult::CGetC2CMsgSigResult(void)
{
	m_nGroupId = 0;
	m_nQQUin = 0;
	Reset();
}

CGetC2CMsgSigResult::~CGetC2CMsgSigResult(void)
{

}

void CGetC2CMsgSigResult::Reset()
{
	m_nRetCode = 0;
	m_nType = 0;
	m_strValue = _T("");
	m_nFlags = 0;
}

BOOL CGetC2CMsgSigResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["type"].isNull())
				m_nType = JsonValue["type"].asInt();

			if (!JsonValue["value"].isNull())
			{
				strValue = JsonValue["value"].asString();
				m_strValue = Utf8ToUnicode(strValue);
			}

			m_nFlags = 0;	// 暂时不解析"flags":{"text":1,"pic":1,"file":1,"audio":1,"video":1}
		}
	}

	return TRUE;
}

CGetGroupFaceSigResult::CGetGroupFaceSigResult(void)
{
	Reset();
}

CGetGroupFaceSigResult::~CGetGroupFaceSigResult(void)
{
}

void CGetGroupFaceSigResult::Reset()
{
	m_nRetCode = 0;
	m_nReply = 0;
	m_strGFaceKey = _T("");
	m_strGFaceSig = _T("");
}

BOOL CGetGroupFaceSigResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["reply"].isNull())
				m_nReply = JsonValue["reply"].asInt();

			if (!JsonValue["gface_key"].isNull())
			{
				strValue = JsonValue["gface_key"].asString();
				m_strGFaceKey = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["gface_sig"].isNull())
			{
				strValue = JsonValue["gface_sig"].asString();
				m_strGFaceSig = Utf8ToUnicode(strValue);
			}
		}
	}

	return TRUE;
}

CUploadBuddyChatPicResult::CUploadBuddyChatPicResult(void)
{
	Reset();
}

CUploadBuddyChatPicResult::~CUploadBuddyChatPicResult(void)
{
}

void CUploadBuddyChatPicResult::Reset()
{
	m_nRetCode = 0;
	m_dwFileSize = 0;
	m_strFileName = _T("");
	m_strFilePath = _T("");
}

BOOL CUploadBuddyChatPicResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	const CHAR * lpStart = "parent.EQQ.Model.ChatMsg.callbackSendPic(";
	const CHAR * lpEnd = ");</script></head>";

	strText = (const CHAR *)lpBuf->GetData();
	std::string::size_type nPos = strText.find(lpStart);
	if (nPos == tstring::npos)
		return FALSE;
	nPos += strlen(lpStart);
	std::string::size_type nPos2 = strText.find(lpEnd, nPos);
	if (nPos2 == tstring::npos)
		return FALSE;
	strText = strText.substr(nPos, nPos2-nPos);

	Replace(strText, "'", "\"");
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["filesize"].isNull())
			m_dwFileSize = JsonValue["filesize"].asUInt();

		if (!JsonValue["filename"].isNull())
		{
			strValue = JsonValue["filename"].asString();
			m_strFileName = Utf8ToUnicode(strValue);
		}

		if (!JsonValue["filepath"].isNull())
		{
			strValue = JsonValue["filepath"].asString();
			m_strFilePath = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

CApplyBuddyChatPicResult::CApplyBuddyChatPicResult(void)
{
	Reset();
}

CApplyBuddyChatPicResult::~CApplyBuddyChatPicResult(void)
{
}

void CApplyBuddyChatPicResult::Reset()
{
	m_nRetCode = 0;
	m_strUrl = _T("");
	m_nSuccess = 0;
	m_strFilePath = _T("");
}

BOOL CApplyBuddyChatPicResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	strText = (const CHAR *)lpBuf->GetData();
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["retcode"].isNull())
			m_nRetCode = JsonValue["retcode"].asInt();

		if (!JsonValue["result"].isNull())
		{
			JsonValue = JsonValue["result"];

			if (!JsonValue["url"].isNull())
			{
				strValue = JsonValue["url"].asString();
				m_strUrl = Utf8ToUnicode(strValue);
			}

			if (!JsonValue["success"].isNull())
				m_nSuccess = JsonValue["success"].asInt();

			if (!JsonValue["file_path"].isNull())
			{
				strValue = JsonValue["file_path"].asString();
				m_strFilePath = Utf8ToUnicode(strValue);
			}
		}
	}

	return TRUE;
}

CUploadGroupChatPicResult::CUploadGroupChatPicResult(void)
{
	Reset();
}

CUploadGroupChatPicResult::~CUploadGroupChatPicResult(void)
{
}

void CUploadGroupChatPicResult::Reset()
{
	m_nRetCode = 0;
	m_strFilePath = _T("");
}

BOOL CUploadGroupChatPicResult::Parse(CBuffer * lpBuf)
{
	Json::Reader JsonReader;
	Json::Value JsonValue;
	std::string strText, strValue;

	if (NULL == lpBuf || lpBuf->GetData() == NULL || lpBuf->GetSize() <= 0)
		return FALSE;

	Reset();

	const CHAR * lpStart = "parent.EQQ.Model.ChatMsg.callbackSendPicGroup(";
	const CHAR * lpEnd = ");</script></head>";

	strText = (const CHAR *)lpBuf->GetData();
	std::string::size_type nPos = strText.find(lpStart);
	if (nPos == tstring::npos)
		return FALSE;
	nPos += strlen(lpStart);
	std::string::size_type nPos2 = strText.find(lpEnd, nPos);
	if (nPos2 == tstring::npos)
		return FALSE;
	strText = strText.substr(nPos, nPos2-nPos);

	Replace(strText, "'", "\"");
	if (JsonReader.parse(strText, JsonValue))
	{
		if (!JsonValue["ret"].isNull())
			m_nRetCode = JsonValue["ret"].asInt();

		if (!JsonValue["msg"].isNull())
		{
			strValue = JsonValue["msg"].asString();
			if (4 == m_nRetCode)
			{
				nPos = strValue.find(' ');
				if (nPos != tstring::npos)
					strValue = strValue.substr(0, nPos);
			}
			m_strFilePath = Utf8ToUnicode(strValue);
		}
	}

	return TRUE;
}

CBuddyInfo::CBuddyInfo(void)
{
	Reset();
}

CBuddyInfo::~CBuddyInfo(void)
{

}

void CBuddyInfo::Reset()
{
	m_nQQUin = 0;
	m_nQQNum = 0;
	m_nTeamIndex = 0;
	m_strNickName = _T("");
	m_strMarkName = _T("");
	m_bIsVip = FALSE;
	m_nVipLevel = 0;
	m_nFace = 0;
	m_dwFlag = 0;
	m_nStatus = QQ_STATUS_OFFLINE;
	m_nClientType = 0;
	m_strGroupCard = _T("");
	m_nGroupFlag = 0;
	m_strSign = _T("");
	m_strGender = _T("");
	m_nShengXiao = 0;
	m_nConstel = 0;
	m_nBlood = 0;
	m_strBirthday = _T("");
	m_strCountry = _T("");
	m_strProvince = _T("");
	m_strCity = _T("");
	m_strPhone = _T("");
	m_strMobile = _T("");
	m_strEmail = _T("");
	m_strOccupation = _T("");
	m_strCollege = _T("");
	m_strHomepage = _T("");
	m_strPersonal = _T("");
	m_bAllow = FALSE;
	m_nRegTime = 0;
	m_nStat = 0;
	m_nVipInfo = 0;
	m_strToken = _T("");
	m_strGroupSig = _T("");
	m_bHasQQNum = m_bHasQQSign = m_bHasBuddyInfo = FALSE;
}

void CBuddyInfo::SetQQNum(CGetQQNumResult * lpGetQQNumResult)
{
	if (lpGetQQNumResult != NULL)
	{
		m_nQQNum = lpGetQQNumResult->m_nQQNum;
		m_bHasQQNum = TRUE;
	}
}

void CBuddyInfo::SetQQSign(CGetSignResult * lpGetSignResult)
{
	if (lpGetSignResult != NULL)
	{
		m_strSign = lpGetSignResult->m_strSign;
		m_bHasQQSign = TRUE;
	}
}

void CBuddyInfo::SetBuddyInfo(CBuddyInfoResult * lpBuddyInfoResult)
{
	if (NULL == lpBuddyInfoResult)
		return;

	m_nQQUin = lpBuddyInfoResult->m_nQQUin;
	m_strNickName = lpBuddyInfoResult->m_strNickName;
	m_nFace = lpBuddyInfoResult->m_nFace;
	m_strGender = lpBuddyInfoResult->m_strGender;
	m_nShengXiao = lpBuddyInfoResult->m_nShengXiao;
	m_nConstel = lpBuddyInfoResult->m_nConstel;
	m_nBlood = lpBuddyInfoResult->m_nBlood;
	m_strBirthday = lpBuddyInfoResult->m_strBirthday;
	m_strCountry = lpBuddyInfoResult->m_strCountry;
	m_strProvince = lpBuddyInfoResult->m_strProvince;
	m_strCity = lpBuddyInfoResult->m_strCity;
	m_strPhone = lpBuddyInfoResult->m_strPhone;
	m_strMobile = lpBuddyInfoResult->m_strMobile;
	m_strEmail = lpBuddyInfoResult->m_strEmail;
	m_strOccupation = lpBuddyInfoResult->m_strOccupation;
	m_strCollege = lpBuddyInfoResult->m_strCollege;
	m_strHomepage = lpBuddyInfoResult->m_strHomepage;
	m_strPersonal = lpBuddyInfoResult->m_strPersonal;
	m_bAllow = lpBuddyInfoResult->m_bAllow;
	m_nRegTime = lpBuddyInfoResult->m_nRegTime;
	m_nStat = lpBuddyInfoResult->m_nStat;
	m_nVipInfo = lpBuddyInfoResult->m_nVipInfo;
	m_nClientType = lpBuddyInfoResult->m_nClientType;
	m_strToken = lpBuddyInfoResult->m_strToken;
	m_bHasBuddyInfo = TRUE;
}

BOOL CBuddyInfo::IsHasQQNum()
{
	return m_bHasQQNum;
}

BOOL CBuddyInfo::IsHasQQSign()
{
	return m_bHasQQSign;
}

BOOL CBuddyInfo::IsHasBuddyInfo()
{
	return m_bHasBuddyInfo;
}

tstring CBuddyInfo::GetDisplayGender()
{
	if (m_strGender == _T("male"))
		return _T("男");
	else if (m_strGender == _T("female"))
		return _T("女");
	else
		return _T("未知");	// "unknown"
}

tstring CBuddyInfo::GetDisplayShengXiao()
{
	static TCHAR cShengXiao[][2] = {_T(""), _T("鼠"), _T("牛"), _T("虎"), _T("兔"), _T("龙"), _T("蛇"), _T("马"), _T("羊"), _T("猴"), _T("鸡"), _T("狗"), _T("猪")};
	if (m_nShengXiao >= 0 && m_nShengXiao < 12)
		return cShengXiao[m_nShengXiao];
	else
		return _T("");
}

tstring CBuddyInfo::GetDisplayConstel()
{
	static TCHAR cConstel[][4] = {_T(""), _T("水瓶座"), _T("双鱼座"), _T("白羊座"), _T("金牛座"), _T("双子座"), _T("巨蟹座"), _T("狮子座"), _T("处女座"), _T("天秤座"), _T("天蝎座"), _T("射手座"), _T("摩羯座")};
	if (m_nConstel >= 0 && m_nConstel < 12)
		return cConstel[m_nConstel];
	else
		return _T("");
}

tstring CBuddyInfo::GetDisplayBlood()
{
	static TCHAR cBlood[][4] = {_T(""), _T("A型"), _T("B型"), _T("O型"), _T("AB型"), _T("其它")};
	if (m_nBlood >= 0 && m_nBlood < 5)
		return cBlood[m_nBlood];
	else
		return _T("");
}

CBuddyTeamInfo::CBuddyTeamInfo(void)
{
	Reset();
}

CBuddyTeamInfo::~CBuddyTeamInfo(void)
{
	Reset();
}

void CBuddyTeamInfo::Reset()
{
	m_nIndex = 0;
	m_nSort = 0;
	m_strName = _T("");
	for (int i = 0; i < (int)m_arrBuddyInfo.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrBuddyInfo[i];
		if (lpBuddyInfo != NULL)
			delete lpBuddyInfo;
	}
	m_arrBuddyInfo.clear();
}

int CBuddyTeamInfo::GetBuddyCount()
{
	return m_arrBuddyInfo.size();
}

int CBuddyTeamInfo::GetOnlineBuddyCount()
{
	int nCount = 0;
	for (int i = 0; i < (int)m_arrBuddyInfo.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrBuddyInfo[i];
		if (lpBuddyInfo != NULL && lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE)
			nCount++;
	}
	return nCount;
}

CBuddyInfo * CBuddyTeamInfo::GetBuddy(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrBuddyInfo.size())
		return m_arrBuddyInfo[nIndex];
	else
		return NULL;
}

void CBuddyTeamInfo::Sort()
{
	CBuddyInfo * lpBuddyInfo1, * lpBuddyInfo2;
	BOOL bExchange;
	int nCount;

	nCount = (int)m_arrBuddyInfo.size();
	for (int i = 0; i < nCount-1; i++)
	{
		bExchange = FALSE;
		for (int j = nCount-1; j > i; j--)
		{
			lpBuddyInfo1 = m_arrBuddyInfo[j-1];
			lpBuddyInfo2 = m_arrBuddyInfo[j];
			if (lpBuddyInfo1 != NULL && lpBuddyInfo2 != NULL)
			{
				if (lpBuddyInfo2->m_nStatus < lpBuddyInfo1->m_nStatus)
				{
					m_arrBuddyInfo[j-1] = lpBuddyInfo2;
					m_arrBuddyInfo[j] = lpBuddyInfo1;
					bExchange = TRUE;
				}
			}
		}
		if (!bExchange)
			break;
	}
}

COnlineBuddyInfo::COnlineBuddyInfo(void)
{
	Reset();
}

COnlineBuddyInfo::~COnlineBuddyInfo(void)
{

}

void COnlineBuddyInfo::Reset()
{
	m_nUin = 0;
	m_nStatus = QQ_STATUS_OFFLINE;
	m_nClientType = 0;
}

CBuddyList::CBuddyList(void)
{
	Reset();
}

CBuddyList::~CBuddyList(void)
{
	Reset();
}

void CBuddyList::Reset()
{
	m_nRetCode = 0;

	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpBuddyTeamInfo != NULL)
			delete lpBuddyTeamInfo;
	}
	m_arrBuddyTeamInfo.clear();
}

int CBuddyList::GetBuddyTeamCount()
{
	return m_arrBuddyTeamInfo.size();
}

CBuddyTeamInfo * CBuddyList::GetBuddyTeam(int nTeamIndex)
{
	if (nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamInfo.size())
		return m_arrBuddyTeamInfo[nTeamIndex];
	else
		return NULL;
}

CBuddyTeamInfo * CBuddyList::GetBuddyTeamByIndex(int nIndex)
{
	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpBuddyTeamInfo != NULL && nIndex == lpBuddyTeamInfo->m_nIndex)
			return lpBuddyTeamInfo;
	}
	return NULL;
}

int CBuddyList::GetBuddyCount(int nTeamIndex)
{
	CBuddyTeamInfo * lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
	if (lpBuddyTeamInfo != NULL)
		return lpBuddyTeamInfo->GetBuddyCount();
	else
		return 0;
}

int CBuddyList::GetOnlineBuddyCount(int nTeamIndex)
{
	CBuddyTeamInfo * lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
	if (lpBuddyTeamInfo != NULL)
		return lpBuddyTeamInfo->GetOnlineBuddyCount();
	else
		return 0;
}

CBuddyInfo * CBuddyList::GetBuddy(int nTeamIndex, int nIndex)
{
	CBuddyTeamInfo * lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
	if (lpBuddyTeamInfo != NULL)
		return lpBuddyTeamInfo->GetBuddy(nIndex);
	else
		return NULL;
}

CBuddyInfo * CBuddyList::GetBuddy(UINT nQQUin)
{
	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpBuddyTeamInfo != NULL)
		{
			for (int j = 0; j < (int)lpBuddyTeamInfo->m_arrBuddyInfo.size(); j++)
			{
				CBuddyInfo * lpBuddyInfo = lpBuddyTeamInfo->m_arrBuddyInfo[j];
				if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)
					return lpBuddyInfo;
			}
		}
	}
	return NULL;
}

BOOL CBuddyList::SetOnlineBuddyList(COnlineBuddyListResult * lpOnlineBuddyListResult)
{
	if (NULL == lpOnlineBuddyListResult)
		return FALSE;

	for (int i = 0; i < (int)lpOnlineBuddyListResult->m_arrOnlineBuddyInfo.size(); i++)
	{
		COnlineBuddyInfo * lpOnlineBuddyInfo = lpOnlineBuddyListResult->m_arrOnlineBuddyInfo[i];
		if (lpOnlineBuddyInfo != NULL)
		{
			CBuddyInfo * lpBuddyInfo = GetBuddy(lpOnlineBuddyInfo->m_nUin);
			if (lpBuddyInfo != NULL)
			{
				lpBuddyInfo->m_nClientType = lpOnlineBuddyInfo->m_nClientType;
				lpBuddyInfo->m_nStatus = lpOnlineBuddyInfo->m_nStatus;
			}
		}
	}
	return TRUE;
}

void CBuddyList::SortBuddyTeam()
{
	CBuddyTeamInfo * lpBuddyTeamInfo1, * lpBuddyTeamInfo2;
	BOOL bExchange;
	int nCount;

	nCount = (int)m_arrBuddyTeamInfo.size();
	for (int i = 0; i < nCount-1; i++)
	{
		bExchange = FALSE;
		for (int j = nCount-1; j > i; j--)
		{
			lpBuddyTeamInfo1 = m_arrBuddyTeamInfo[j-1];
			lpBuddyTeamInfo2 = m_arrBuddyTeamInfo[j];
			if (lpBuddyTeamInfo1 != NULL && lpBuddyTeamInfo2 != NULL)
			{
				if (lpBuddyTeamInfo2->m_nSort < lpBuddyTeamInfo1->m_nSort)
				{
					m_arrBuddyTeamInfo[j-1] = lpBuddyTeamInfo2;
					m_arrBuddyTeamInfo[j] = lpBuddyTeamInfo1;
					bExchange = TRUE;
				}
			}
		}
		if (!bExchange)
			break;
	}
}

void CBuddyList::SortBuddy()
{
	for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
	{
		CBuddyTeamInfo * lpTeamInfo = m_arrBuddyTeamInfo[i];
		if (lpTeamInfo != NULL)
			lpTeamInfo->Sort();
	}
}

BOOL CBuddyList::AddBuddyTeam(CBuddyTeamInfo * lpBuddyTeamInfo)
{
	if (NULL == lpBuddyTeamInfo)
		return FALSE;
	m_arrBuddyTeamInfo.push_back(lpBuddyTeamInfo);
	return TRUE;
}

CGroupInfo::CGroupInfo(void)
{
	Reset();
}

CGroupInfo::~CGroupInfo(void)
{
	Reset();
}

void CGroupInfo::Reset()
{
	m_nGroupCode = 0;
	m_nGroupId = 0;
	m_nGroupNumber = 0;
	m_strName = _T("");
	m_strMemo = _T("");
	m_strFingerMemo = _T("");
	m_nOwnerUin = 0;
	m_nCreateTime = 0;
	m_nFace = 0;
	m_nLevel = 0;
	m_nClass = 0;
	m_nOption = 0;
	m_nFlag = 0;
	m_bHasGroupNumber = m_bHasGroupInfo = FALSE;

	DelAllMember();
}

// 获取群成员总人数
int CGroupInfo::GetMemberCount()
{
	return (int)m_arrMember.size();
}

// 获取群成员在线人数
int CGroupInfo::GetOnlineMemberCount()
{
	int nCount = 0;
	for (int i = 0; i < (int)m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrMember[i];
		if (lpBuddyInfo != NULL && lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE)
			nCount++;
	}
	return nCount;
}

// 根据索引获取群成员信息
CBuddyInfo * CGroupInfo::GetMember(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_arrMember.size())
		return NULL;

	return m_arrMember[nIndex];
}

// 根据QQUin获取群成员信息
CBuddyInfo * CGroupInfo::GetMemberByUin(UINT nQQUin)
{
	for (int i = 0; i < (int)m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrMember[i];
		if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)
			return lpBuddyInfo;
	}
	return NULL;
}

// 根据QQNum获取群成员信息
CBuddyInfo * CGroupInfo::GetMemberByNum(UINT nQQNum)
{
	for (int i = 0; i < (int)m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrMember[i];
		if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQNum == nQQNum)
			return lpBuddyInfo;
	}
	return NULL;
}

// 对群成员列表按在线状态进行排序
void CGroupInfo::Sort()
{
	CBuddyInfo * lpBuddyInfo1, * lpBuddyInfo2;
	BOOL bExchange;
	int nCount;

	nCount = (int)m_arrMember.size();
	for (int i = 0; i < nCount-1; i++)
	{
		bExchange = FALSE;
		for (int j = nCount-1; j > i; j--)
		{
			lpBuddyInfo1 = m_arrMember[j-1];
			lpBuddyInfo2 = m_arrMember[j];
			if (lpBuddyInfo1 != NULL && lpBuddyInfo2 != NULL)
			{
				if (lpBuddyInfo2->m_nStatus < lpBuddyInfo1->m_nStatus)
				{
					m_arrMember[j-1] = lpBuddyInfo2;
					m_arrMember[j] = lpBuddyInfo1;
					bExchange = TRUE;
				}
			}
		}
		if (!bExchange)
			break;
	}
}

// 添加群成员
BOOL CGroupInfo::AddMember(CBuddyInfo * lpBuddyInfo)
{
	if (NULL == lpBuddyInfo)
		return FALSE;
	m_arrMember.push_back(lpBuddyInfo);
	return TRUE;
}

// 删除所有群成员
BOOL CGroupInfo::DelAllMember()
{
	for (int i = 0; i < (int)m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = m_arrMember[i];
		if (lpBuddyInfo != NULL)
			delete lpBuddyInfo;
	}
	m_arrMember.clear();
	return TRUE;
}

// 设置群号码
void CGroupInfo::SetGroupNumber(CGetQQNumResult * lpGetQQNumResult)
{
	if (lpGetQQNumResult != NULL)
	{
		m_nGroupNumber = lpGetQQNumResult->m_nQQNum;
		m_bHasGroupNumber = TRUE;
	}
}

// 设置群信息
BOOL CGroupInfo::SetGroupInfo(CGroupInfoResult * lpGroupInfoResult)
{
	if (NULL == lpGroupInfoResult)
		return FALSE;

	m_nGroupCode = lpGroupInfoResult->m_nGroupCode;
	m_nGroupId = lpGroupInfoResult->m_nGroupId;
	m_strName = lpGroupInfoResult->m_strName;
	m_strMemo = lpGroupInfoResult->m_strMemo;
	m_strFingerMemo = lpGroupInfoResult->m_strFingerMemo;
	m_nOwnerUin = lpGroupInfoResult->m_nOwnerUin;
	m_nCreateTime = lpGroupInfoResult->m_nCreateTime;
	m_nFace = lpGroupInfoResult->m_nFace;
	m_nLevel = lpGroupInfoResult->m_nLevel;
	m_nClass = lpGroupInfoResult->m_nClass;
	m_nOption = lpGroupInfoResult->m_nOption;
	m_nFlag = lpGroupInfoResult->m_nFlag;

	DelAllMember();
	for (int i = 0; i < (int)lpGroupInfoResult->m_arrMember.size(); i++)
	{
		CBuddyInfo * lpBuddyInfo = lpGroupInfoResult->m_arrMember[i];
		if (lpBuddyInfo != NULL)
			m_arrMember.push_back(lpBuddyInfo);
	}
	lpGroupInfoResult->m_arrMember.clear();
	Sort();
	m_bHasGroupInfo = TRUE;

	return TRUE;
}

BOOL CGroupInfo::IsHasGroupNumber()
{
	return m_bHasGroupNumber;
}

BOOL CGroupInfo::IsHasGroupInfo()
{
	return m_bHasGroupInfo;
}

CGroupList::CGroupList(void)
{
	Reset();
}

CGroupList::~CGroupList(void)
{
	Reset();
}

void CGroupList::Reset()
{
	for (int i = 0; i < (int)m_arrGroupInfo.size(); i++)
	{
		CGroupInfo * lpGroupInfo = m_arrGroupInfo[i];
		if (lpGroupInfo != NULL)
			delete lpGroupInfo;
	}
	m_arrGroupInfo.clear();
}

// 获取群总数
int CGroupList::GetGroupCount()
{
	return (int)m_arrGroupInfo.size();
}

// 获取群信息(根据索引)
CGroupInfo * CGroupList::GetGroup(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrGroupInfo.size())
		return m_arrGroupInfo[nIndex];
	else
		return NULL;
}

// 获取群信息(根据群代码)
CGroupInfo * CGroupList::GetGroupByCode(UINT nGroupCode)
{
	for (int i = 0; i < (int)m_arrGroupInfo.size(); i++)
	{
		CGroupInfo * lpGroupInfo = m_arrGroupInfo[i];
		if (lpGroupInfo != NULL && lpGroupInfo->m_nGroupCode == nGroupCode)
			return lpGroupInfo;
	}
	return NULL;
}

// 获取群信息(根据群Id)
CGroupInfo * CGroupList::GetGroupById(UINT nGroupId)
{
	for (int i = 0; i < (int)m_arrGroupInfo.size(); i++)
	{
		CGroupInfo * lpGroupInfo = m_arrGroupInfo[i];
		if (lpGroupInfo != NULL && lpGroupInfo->m_nGroupId == nGroupId)
			return lpGroupInfo;
	}
	return NULL;
}

// 根据群代码和群成员QQUin获取群成员信息
CBuddyInfo * CGroupList::GetGroupMemberByCode(UINT nGroupCode, UINT nQQUin)
{
	CGroupInfo * lpGroupInfo = GetGroupByCode(nGroupCode);
	if (lpGroupInfo != NULL)
		return lpGroupInfo->GetMemberByUin(nQQUin);
	else
		return NULL;
}

// 根据群Id和群成员QQUin获取群成员信息
CBuddyInfo * CGroupList::GetGroupMemberById(UINT nGroupId, UINT nQQUin)
{
	CGroupInfo * lpGroupInfo = GetGroupById(nGroupId);
	if (lpGroupInfo != NULL)
		return lpGroupInfo->GetMemberByUin(nQQUin);
	else
		return NULL;
}

// 添加群
BOOL CGroupList::AddGroup(CGroupInfo * lpGroupInfo)
{
	if (NULL == lpGroupInfo)
		return FALSE;
	m_arrGroupInfo.push_back(lpGroupInfo);
	return TRUE;
}

// 由群Id获取群代码
UINT CGroupList::GetGroupCodeById(UINT nGroupId)
{
	CGroupInfo * lpGroupInfo = GetGroupById(nGroupId);
	return ((lpGroupInfo != NULL) ? lpGroupInfo->m_nGroupCode : 0);
}

// 由群代码获取群Id
UINT CGroupList::GetGroupIdByCode(UINT nGroupCode)
{
	CGroupInfo * lpGroupInfo = GetGroupByCode(nGroupCode);
	return ((lpGroupInfo != NULL) ? lpGroupInfo->m_nGroupId : 0);
}

CRecentInfo::CRecentInfo(void)
{
	Reset();
}

CRecentInfo::~CRecentInfo(void)
{

}

void CRecentInfo::Reset()
{
	m_nQQUin = 0;
	m_nType = 0;
}

CRecentList::CRecentList(void)
{
	Reset();
}

CRecentList::~CRecentList(void)
{
	Reset();
}

void CRecentList::Reset()
{
	m_nRetCode = 0;

	for (int i = 0; i < (int)m_arrRecentInfo.size(); i++)
	{
		if (m_arrRecentInfo[i] != NULL)
			delete m_arrRecentInfo[i];
	}
	m_arrRecentInfo.clear();
}

BOOL CRecentList::AddRecent(CRecentInfo * lpRecentInfo)
{
	if (NULL == lpRecentInfo)
		return FALSE;
	m_arrRecentInfo.push_back(lpRecentInfo);
	return TRUE;
}

int CRecentList::GetRecentCount()
{
	return (int)m_arrRecentInfo.size();
}

CRecentInfo * CRecentList::GetRecent(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrRecentInfo.size())
		return m_arrRecentInfo[nIndex];
	else
		return NULL;
}

CBuddyMessage::CBuddyMessage(void)
{
	m_nMsgId = 0;
	m_nMsgId2 = 0;
	m_nFromUin = 0;
	m_nToUin = 0;
	m_nMsgType = 0;
	m_nReplyIp = 0;
	m_nTime = 0;
}

CBuddyMessage::~CBuddyMessage(void)
{
	Reset();
}

BOOL CBuddyMessage::IsType(LPCTSTR lpType)
{
	return (_tcsicmp(lpType, _T("message")) == 0);
}

void CBuddyMessage::Reset()
{
	m_nMsgId = 0;
	m_nMsgId2 = 0;
	m_nFromUin = 0;
	m_nToUin = 0;
	m_nMsgType = 0;
	m_nReplyIp = 0;
	m_nTime = 0;

	for (int i = 0; i < (int)m_arrContent.size(); i++)
	{
		CContent * lpContent = m_arrContent[i];
		if (lpContent != NULL)
			delete lpContent;
	}
	m_arrContent.clear();
}

BOOL CBuddyMessage::Parse(Json::Value& JsonValue)
{
	std::string strValue;
	int nCount, nCount2;

	Reset();

	if (!JsonValue["msg_id"].isNull())
		m_nMsgId = JsonValue["msg_id"].asUInt();

	if (!JsonValue["msg_id2"].isNull())
		m_nMsgId2 = JsonValue["msg_id2"].asUInt();

	if (!JsonValue["from_uin"].isNull())
		m_nFromUin = JsonValue["from_uin"].asUInt();

	if (!JsonValue["to_uin"].isNull())
		m_nToUin = JsonValue["to_uin"].asUInt();

	if (!JsonValue["msg_type"].isNull())
		m_nMsgType = JsonValue["msg_type"].asUInt();

	if (!JsonValue["reply_ip"].isNull())
		m_nReplyIp = JsonValue["reply_ip"].asUInt();

	if (!JsonValue["time"].isNull())
		m_nTime = JsonValue["time"].asUInt();

	nCount = (int)JsonValue["content"].size();
	for (int i = 0; i < nCount; ++i)
	{
		if (JsonValue["content"][i].isNull())
			continue;

		if (JsonValue["content"][i].isString())		// 纯文本
		{
			CContent * lpContent = new CContent;
			if (NULL == lpContent)
				continue;

			strValue = JsonValue["content"][i].asString();

			if (i == nCount - 1)					// 去除消息最后多余的一个空格
			{
				nCount2 = strValue.size();
				if (nCount2 > 0 && (strValue[nCount2 - 1] == ' '))
					strValue.erase(strValue.end()-1);
			}

			Replace(strValue, "\r", "\r\n");

			lpContent->m_nType = CONTENT_TYPE_TEXT;
			lpContent->m_strText = Utf8ToUnicode(strValue);
			m_arrContent.push_back(lpContent);
		}
		else if (JsonValue["content"][i].isArray())
		{
			if (JsonValue["content"][i][(UINT)0].isNull())
				continue;
			
			strValue = JsonValue["content"][i][(UINT)0].asString();	// 内容类型
			if (strValue == "font")		// 字体信息
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;

				lpContent->m_nType = CONTENT_TYPE_FONT_INFO;

				if (!JsonValue["content"][i][(UINT)1]["size"].isNull())				// 字体大小
					lpContent->m_FontInfo.m_nSize = JsonValue["content"][i][(UINT)1]["size"].asInt();

				if (!JsonValue["content"][i][(UINT)1]["color"].isNull())			// 字体颜色
				{
					strValue = JsonValue["content"][i][(UINT)1]["color"].asString();
					lpContent->m_FontInfo.m_clrText = HexStrToRGB(Utf8ToUnicode(strValue).c_str());
				}

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)0].isNull())	// 字体风格(加粗)
					lpContent->m_FontInfo.m_bBold = JsonValue["content"][i][(UINT)1]["style"][(UINT)0].asBool();

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)1].isNull())	// 字体风格(倾斜)
					lpContent->m_FontInfo.m_bItalic = JsonValue["content"][i][(UINT)1]["style"][(UINT)1].asBool();

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)2].isNull())	// 字体风格(下划线)
					lpContent->m_FontInfo.m_bUnderLine = JsonValue["content"][i][(UINT)1]["style"][(UINT)2].asBool();

				if (!JsonValue["content"][i][(UINT)1]["name"].isNull())				// 字体名称
				{
					strValue = JsonValue["content"][i][(UINT)1]["name"].asString();
					lpContent->m_FontInfo.m_strName = Utf8ToUnicode(strValue);
				}
				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "face")	// 系统表情
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;
				lpContent->m_nType = CONTENT_TYPE_FACE;
				if (!JsonValue["content"][i][(UINT)1].isNull())
					lpContent->m_nFaceId = JsonValue["content"][i][(UINT)1].asInt();
				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "cface")	// 自定义表情
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;
				lpContent->m_nType = CONTENT_TYPE_CUSTOM_FACE;
				if (!JsonValue["content"][i][(UINT)1].isNull())
				{
					strValue = JsonValue["content"][i][(UINT)1].asString();
					lpContent->m_CFaceInfo.m_strName = Utf8ToUnicode(strValue);
				}
				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "offpic")	// 离线图片
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;
				lpContent->m_nType = CONTENT_TYPE_OFF_PIC;
				if (!JsonValue["content"][i][(UINT)1]["file_path"].isNull())
				{
					strValue = JsonValue["content"][i][(UINT)1]["file_path"].asString();
					lpContent->m_CFaceInfo.m_strName = Utf8ToUnicode(strValue);
				}
				m_arrContent.push_back(lpContent);
			}
		}
	}

	return TRUE;
}

CGroupMessage::CGroupMessage(void)
{

}

CGroupMessage::~CGroupMessage(void)
{

}

BOOL CGroupMessage::IsType(LPCTSTR lpType)
{
	return (_tcsicmp(lpType, _T("group_message")) == 0);
}

void CGroupMessage::Reset()
{
	m_nMsgId = 0;
	m_nMsgId2 = 0;
	m_nFromUin = 0;
	m_nToUin = 0;
	m_nMsgType = 0;
	m_nReplyIp = 0;
	m_nGroupCode = 0;
	m_nSendUin = 0;
	m_nSeq = 0;
	m_nInfoSeq = 0;
	m_nTime = 0;

	for (int i = 0; i < (int)m_arrContent.size(); i++)
	{
		CContent * lpContent = m_arrContent[i];
		if (lpContent != NULL)
			delete lpContent;
	}
	m_arrContent.clear();
}

BOOL CGroupMessage::Parse(Json::Value& JsonValue)
{
	std::string strValue;
	int nCount, nCount2;

	Reset();

	if (!JsonValue["msg_id"].isNull())
		m_nMsgId = JsonValue["msg_id"].asUInt();

	if (!JsonValue["msg_id2"].isNull())
		m_nMsgId2 = JsonValue["msg_id2"].asUInt();

	if (!JsonValue["from_uin"].isNull())
		m_nFromUin = JsonValue["from_uin"].asUInt();

	if (!JsonValue["to_uin"].isNull())
		m_nToUin = JsonValue["to_uin"].asUInt();

	if (!JsonValue["msg_type"].isNull())
		m_nMsgType = JsonValue["msg_type"].asUInt();

	if (!JsonValue["reply_ip"].isNull())
		m_nReplyIp = JsonValue["reply_ip"].asUInt();

	if (!JsonValue["time"].isNull())
		m_nTime = JsonValue["time"].asUInt();

	if (!JsonValue["group_code"].isNull())
		m_nGroupCode = JsonValue["group_code"].asUInt();

	if (!JsonValue["send_uin"].isNull())
		m_nSendUin = JsonValue["send_uin"].asUInt();

	if (!JsonValue["seq"].isNull())
		m_nSeq = JsonValue["seq"].asUInt();

	if (!JsonValue["info_seq"].isNull())
		m_nInfoSeq = JsonValue["info_seq"].asUInt();

	nCount = (int)JsonValue["content"].size();
	for (int i = 0; i < nCount; ++i)
	{
		if (JsonValue["content"][i].isNull())
			continue;

		if (JsonValue["content"][i].isString())		// 纯文本
		{
			CContent * lpContent = new CContent;
			if (NULL == lpContent)
				continue;

			strValue = JsonValue["content"][i].asString();

			if (i == nCount - 1)					// 去除消息最后多余的一个空格
			{
				nCount2 = strValue.size();
				if (nCount2 > 0 && strValue[nCount2 - 1] == ' ')
					strValue.erase(strValue.end()-1);
			}

			Replace(strValue, "\r", "\r\n");

			lpContent->m_nType = CONTENT_TYPE_TEXT;
			lpContent->m_strText = Utf8ToUnicode(strValue);
			m_arrContent.push_back(lpContent);
		}
		else if (JsonValue["content"][i].isArray())
		{
			if (JsonValue["content"][i][(UINT)0].isNull())
				continue;
			
			strValue = JsonValue["content"][i][(UINT)0].asString();	// 内容类型
			if (strValue == "font")			// 字体信息
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;

				lpContent->m_nType = CONTENT_TYPE_FONT_INFO;

				if (!JsonValue["content"][i][(UINT)1]["size"].isNull())				// 字体大小
					lpContent->m_FontInfo.m_nSize = JsonValue["content"][i][(UINT)1]["size"].asInt();

				if (!JsonValue["content"][i][(UINT)1]["color"].isNull())			// 字体颜色
				{
					strValue = JsonValue["content"][i][(UINT)1]["color"].asString();
					lpContent->m_FontInfo.m_clrText = HexStrToRGB(Utf8ToUnicode(strValue).c_str());
				}

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)0].isNull())	// 字体风格(加粗)
					lpContent->m_FontInfo.m_bBold = JsonValue["content"][i][(UINT)1]["style"][(UINT)0].asBool();

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)1].isNull())	// 字体风格(倾斜)
					lpContent->m_FontInfo.m_bItalic = JsonValue["content"][i][(UINT)1]["style"][(UINT)1].asBool();

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)2].isNull())	// 字体风格(下划线)
					lpContent->m_FontInfo.m_bUnderLine = JsonValue["content"][i][(UINT)1]["style"][(UINT)2].asBool();

				if (!JsonValue["content"][i][(UINT)1]["name"].isNull())				// 字体名称
				{
					strValue = JsonValue["content"][i][(UINT)1]["name"].asString();
					lpContent->m_FontInfo.m_strName = Utf8ToUnicode(strValue);
				}

				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "face")	// 系统表情
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;
				lpContent->m_nType = CONTENT_TYPE_FACE;
				if (!JsonValue["content"][i][(UINT)1].isNull())
					lpContent->m_nFaceId = JsonValue["content"][i][(UINT)1].asInt();
				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "cface")	// 自定义表情
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;
				lpContent->m_nType = CONTENT_TYPE_CUSTOM_FACE;
				if (!JsonValue["content"][i][(UINT)1].isNull())
				{
					if (!JsonValue["content"][i][(UINT)1]["name"].isNull())
					{
						strValue = JsonValue["content"][i][(UINT)1]["name"].asString();
						lpContent->m_CFaceInfo.m_strName = Utf8ToUnicode(strValue);
					}

					if (!JsonValue["content"][i][(UINT)1]["file_id"].isNull())
						lpContent->m_CFaceInfo.m_nFileId = JsonValue["content"][i][(UINT)1]["file_id"].asUInt();

					if (!JsonValue["content"][i][(UINT)1]["key"].isNull())
					{
						strValue = JsonValue["content"][i][(UINT)1]["key"].asString();
						lpContent->m_CFaceInfo.m_strKey = Utf8ToUnicode(strValue);
					}

					if (!JsonValue["content"][i][(UINT)1]["server"].isNull())
					{
						strValue = JsonValue["content"][i][(UINT)1]["server"].asString();
						lpContent->m_CFaceInfo.m_strServer = Utf8ToUnicode(strValue);
					}
				}
				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "cface_idx")	// 未知
			{

			}
		}
	}

	return TRUE;
}

CSessMessage::CSessMessage(void)
{
	Reset();
}

CSessMessage::~CSessMessage(void)
{
	Reset();
}

BOOL CSessMessage::IsType(LPCTSTR lpType)
{
	return (_tcsicmp(lpType, _T("sess_message")) == 0);
}

void CSessMessage::Reset()
{
	m_nMsgId = 0;
	m_nMsgId2 = 0;
	m_nFromUin = 0;
	m_nToUin = 0;
	m_nMsgType = 0;
	m_nReplyIp = 0;
	m_nTime = 0;
	m_nGroupId = 0;
	m_nQQNum = 0;
	m_nServiceType = 0;
	m_nFlags = 0;

	for (int i = 0; i < (int)m_arrContent.size(); i++)
	{
		CContent * lpContent = m_arrContent[i];
		if (lpContent != NULL)
			delete lpContent;
	}
	m_arrContent.clear();
}

BOOL CSessMessage::Parse(Json::Value& JsonValue)
{
	std::string strValue;
	int nCount, nCount2;

	Reset();

	if (!JsonValue["msg_id"].isNull())
		m_nMsgId = JsonValue["msg_id"].asUInt();

	if (!JsonValue["msg_id2"].isNull())
		m_nMsgId2 = JsonValue["msg_id2"].asUInt();

	if (!JsonValue["from_uin"].isNull())
		m_nFromUin = JsonValue["from_uin"].asUInt();

	if (!JsonValue["to_uin"].isNull())
		m_nToUin = JsonValue["to_uin"].asUInt();

	if (!JsonValue["msg_type"].isNull())
		m_nMsgType = JsonValue["msg_type"].asUInt();

	if (!JsonValue["reply_ip"].isNull())
		m_nReplyIp = JsonValue["reply_ip"].asUInt();

	if (!JsonValue["time"].isNull())
		m_nTime = JsonValue["time"].asUInt();

	if (!JsonValue["id"].isNull())
		m_nGroupId = JsonValue["id"].asUInt();

	if (!JsonValue["ruin"].isNull())
		m_nQQNum = JsonValue["ruin"].asUInt();

	if (!JsonValue["service_type"].isNull())
		m_nServiceType = JsonValue["service_type"].asUInt();

	m_nFlags = 0;	// 待解析("flags":{"text":1,"pic":1,"file":1,"audio":1,"video":1})

	nCount = (int)JsonValue["content"].size();
	for (int i = 0; i < nCount; ++i)
	{
		if (JsonValue["content"][i].isNull())
			continue;

		if (JsonValue["content"][i].isString())		// 纯文本
		{
			CContent * lpContent = new CContent;
			if (NULL == lpContent)
				continue;

			strValue = JsonValue["content"][i].asString();

			if (i == nCount - 1)					// 去除消息最后多余的一个空格
			{
				nCount2 = strValue.size();
				if (nCount2 > 0 && (strValue[nCount2 - 1] == ' '))
					strValue.erase(strValue.end()-1);
			}

			Replace(strValue, "\r", "\r\n");

			lpContent->m_nType = CONTENT_TYPE_TEXT;
			lpContent->m_strText = Utf8ToUnicode(strValue);
			m_arrContent.push_back(lpContent);
		}
		else if (JsonValue["content"][i].isArray())
		{
			if (JsonValue["content"][i][(UINT)0].isNull())
				continue;
			
			strValue = JsonValue["content"][i][(UINT)0].asString();	// 内容类型
			if (strValue == "font")		// 字体信息
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;

				lpContent->m_nType = CONTENT_TYPE_FONT_INFO;

				if (!JsonValue["content"][i][(UINT)1]["size"].isNull())				// 字体大小
					lpContent->m_FontInfo.m_nSize = JsonValue["content"][i][(UINT)1]["size"].asInt();

				if (!JsonValue["content"][i][(UINT)1]["color"].isNull())			// 字体颜色
				{
					strValue = JsonValue["content"][i][(UINT)1]["color"].asString();
					lpContent->m_FontInfo.m_clrText = HexStrToRGB(Utf8ToUnicode(strValue).c_str());
				}

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)0].isNull())	// 字体风格(加粗)
					lpContent->m_FontInfo.m_bBold = JsonValue["content"][i][(UINT)1]["style"][(UINT)0].asBool();

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)1].isNull())	// 字体风格(倾斜)
					lpContent->m_FontInfo.m_bItalic = JsonValue["content"][i][(UINT)1]["style"][(UINT)1].asBool();

				if (!JsonValue["content"][i][(UINT)1]["style"][(UINT)2].isNull())	// 字体风格(下划线)
					lpContent->m_FontInfo.m_bUnderLine = JsonValue["content"][i][(UINT)1]["style"][(UINT)2].asBool();

				if (!JsonValue["content"][i][(UINT)1]["name"].isNull())				// 字体名称
				{
					strValue = JsonValue["content"][i][(UINT)1]["name"].asString();
					lpContent->m_FontInfo.m_strName = Utf8ToUnicode(strValue);
				}
				m_arrContent.push_back(lpContent);
			}
			else if (strValue == "face")	// 系统表情
			{
				CContent * lpContent = new CContent;
				if (NULL == lpContent)
					continue;
				lpContent->m_nType = CONTENT_TYPE_FACE;
				if (!JsonValue["content"][i][(UINT)1].isNull())
					lpContent->m_nFaceId = JsonValue["content"][i][(UINT)1].asInt();
				m_arrContent.push_back(lpContent);
			}
		}
	}

	return TRUE;
}

CStatusChangeMessage::CStatusChangeMessage(void)
{
	Reset();
}

CStatusChangeMessage::~CStatusChangeMessage(void)
{

}

BOOL CStatusChangeMessage::IsType(LPCTSTR lpType)
{
	return (_tcsicmp(lpType, _T("buddies_status_change")) == 0);
}

void CStatusChangeMessage::Reset()
{
	m_nQQUin = 0;
	m_nStatus = QQ_STATUS_OFFLINE;
	m_nClientType = 0;
}

BOOL CStatusChangeMessage::Parse(Json::Value& JsonValue)
{
	std::string strValue;

	Reset();

	if (!JsonValue["uin"].isNull())
		m_nQQUin = JsonValue["uin"].asUInt();

	if (!JsonValue["status"].isNull())
	{
		strValue = JsonValue["status"].asString();
		m_nStatus = ConvertToQQStatus(Utf8ToUnicode(strValue).c_str());
	}

	if (!JsonValue["client_type"].isNull())
		m_nClientType = JsonValue["client_type"].asUInt();

	return TRUE;
}

CKickMessage::CKickMessage(void)
{
	Reset();
}

CKickMessage::~CKickMessage(void)
{

}

BOOL CKickMessage::IsType(LPCTSTR lpType)
{
	return (_tcsicmp(lpType, _T("kick_message")) == 0);
}

void CKickMessage::Reset()
{
	m_nMsgId = 0;
	m_nMsgId2 = 0;
	m_nFromUin = 0;
	m_nToUin = 0;
	m_nMsgType = 0;
	m_nReplyIp = 0;
	m_bShowReason = FALSE;
	m_strReason = _T("");
}

BOOL CKickMessage::Parse(Json::Value& JsonValue)
{
	std::string strValue;

	Reset();

	if (!JsonValue["msg_id"].isNull())
		m_nMsgId = JsonValue["msg_id"].asUInt();

	if (!JsonValue["from_uin"].isNull())
		m_nFromUin = JsonValue["from_uin"].asUInt();

	if (!JsonValue["to_uin"].isNull())
		m_nToUin = JsonValue["to_uin"].asUInt();

	if (!JsonValue["msg_id2"].isNull())
		m_nMsgId2 = JsonValue["msg_id2"].asUInt();

	if (!JsonValue["msg_type"].isNull())
		m_nMsgType = JsonValue["msg_type"].asUInt();

	if (!JsonValue["reply_ip"].isNull())
		m_nReplyIp = JsonValue["reply_ip"].asUInt();

	if (!JsonValue["show_reason"].isNull())
		m_bShowReason = JsonValue["show_reason"].asBool();

	if (!JsonValue["reason"].isNull())
	{
		strValue = JsonValue["reason"].asString();
		m_strReason = Utf8ToUnicode(strValue);
	}

	return TRUE;
}

CSysGroupMessage::CSysGroupMessage(void)
{
	Reset();
}

CSysGroupMessage::~CSysGroupMessage(void)
{

}

BOOL CSysGroupMessage::IsType(LPCTSTR lpType)
{
	return (_tcsicmp(lpType, _T("sys_g_msg")) == 0);
}

void CSysGroupMessage::Reset()
{
	m_nMsgId = 0;
	m_nMsgId2 = 0;
	m_nFromUin = 0;
	m_nToUin = 0;
	m_nMsgType = 0;
	m_nReplyIp = 0;
	m_strSubType = _T("");
	m_nGroupCode = 0;
	m_nGroupNumber = 0;
	m_nAdminUin = 0;
	m_strMsg = _T("");
	m_nOpType = 0;
	m_nOldMember = 0;
	m_strOldMember = _T("");
	m_strAdminUin = _T("");
	m_strAdminNickName = _T("");
}

BOOL CSysGroupMessage::Parse(Json::Value& JsonValue)
{
	std::string strValue;

	Reset();

	if (!JsonValue["msg_id"].isNull())
		m_nMsgId = JsonValue["msg_id"].asUInt();

	if (!JsonValue["from_uin"].isNull())
		m_nFromUin = JsonValue["from_uin"].asUInt();

	if (!JsonValue["to_uin"].isNull())
		m_nToUin = JsonValue["to_uin"].asUInt();

	if (!JsonValue["msg_id2"].isNull())
		m_nMsgId2 = JsonValue["msg_id2"].asUInt();

	if (!JsonValue["msg_type"].isNull())
		m_nMsgType = JsonValue["msg_type"].asUInt();

	if (!JsonValue["reply_ip"].isNull())
		m_nReplyIp = JsonValue["reply_ip"].asUInt();

	if (!JsonValue["type"].isNull())
	{
		strValue = JsonValue["type"].asString();
		m_strSubType = Utf8ToUnicode(strValue);
	}

	if (m_strSubType == _T("group_request_join_agree")
		|| m_strSubType == _T("group_request_join_deny"))		// 加群同意通知或拒绝加群通知
	{
		if (!JsonValue["gcode"].isNull())
			m_nGroupCode = JsonValue["gcode"].asUInt();

		if (!JsonValue["t_gcode"].isNull())
			m_nGroupNumber = JsonValue["t_gcode"].asUInt();

		if (!JsonValue["admin_uin"].isNull())
			m_nAdminUin = JsonValue["admin_uin"].asUInt();

		if (!JsonValue["msg"].isNull())
		{
			strValue = JsonValue["msg"].asString();
			m_strMsg = Utf8ToUnicode(strValue);
		}
		return TRUE;
	}
	else if (m_strSubType == _T("group_leave"))	// 被移出群通知
	{
		if (!JsonValue["gcode"].isNull())
			m_nGroupCode = JsonValue["gcode"].asUInt();

		if (!JsonValue["t_gcode"].isNull())
			m_nGroupNumber = JsonValue["t_gcode"].asUInt();

		if (!JsonValue["op_type"].isNull())
			m_nOpType = JsonValue["op_type"].asUInt();

		if (!JsonValue["old_member"].isNull())
			m_nOldMember = JsonValue["old_member"].asUInt();

		if (!JsonValue["t_old_member"].isNull())
		{
			strValue = JsonValue["t_old_member"].asString();
			m_strOldMember = Utf8ToUnicode(strValue);
		}

		if (!JsonValue["admin_uin"].isNull())
			m_nAdminUin = JsonValue["admin_uin"].asUInt();

		if (!JsonValue["t_admin_uin"].isNull())
		{
			strValue = JsonValue["t_admin_uin"].asString();
			m_strAdminUin = Utf8ToUnicode(strValue);
		}

		if (!JsonValue["admin_nick"].isNull())
		{
			strValue = JsonValue["admin_nick"].asString();
			m_strAdminNickName = Utf8ToUnicode(strValue);
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CMessageSender::CMessageSender(QQ_MSG_TYPE nType, UINT nSenderId, UINT nGroupCode)
{
	m_nType = nType;
	m_nSenderId = nSenderId;
	m_nGroupCode = nGroupCode;
}

CMessageSender::~CMessageSender(void)
{
	DelAllMsg();
}

// 添加消息
BOOL CMessageSender::AddMsg(void * lpMsg)
{
	if (NULL == lpMsg)
		return FALSE;
	m_arrMsg.push_back(lpMsg);
	return TRUE;
}

// 删除消息(根据索引)
BOOL CMessageSender::DelMsg(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrMsg.size())
	{
		m_arrMsg.erase(m_arrMsg.begin()+nIndex);
		return TRUE;
	}
	else
		return FALSE;
}

// 删除消息(根据消息Id)
BOOL CMessageSender::DelMsgById(UINT nMsgId)
{
	for (int i = 0; i < (int)m_arrMsg.size(); i++)
	{
		switch (m_nType)
		{
		case QQ_MSG_TYPE_BUDDY:
			{
				CBuddyMessage * lpMsg = (CBuddyMessage *)m_arrMsg[i];
				if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
				{
					delete lpMsg;
					m_arrMsg.erase(m_arrMsg.begin()+i);
					return TRUE;
				}
			}
			break;
		case QQ_MSG_TYPE_GROUP:
			{
				CGroupMessage * lpMsg = (CGroupMessage *)m_arrMsg[i];
				if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
				{
					delete lpMsg;
					m_arrMsg.erase(m_arrMsg.begin()+i);
					return TRUE;
				}
			}
			break;
		case QQ_MSG_TYPE_SESS:
			{
				CSessMessage * lpMsg = (CSessMessage *)m_arrMsg[i];
				if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
				{
					delete lpMsg;
					m_arrMsg.erase(m_arrMsg.begin()+i);
					return TRUE;
				}
			}
			break;
		case QQ_MSG_TYPE_SYSGROUP:
			{
				CSysGroupMessage * lpMsg = (CSysGroupMessage *)m_arrMsg[i];
				if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
				{
					delete lpMsg;
					m_arrMsg.erase(m_arrMsg.begin()+i);
					return TRUE;
				}
			}
			break;
		}
	}
	return FALSE;
}

// 删除所有消息
BOOL CMessageSender::DelAllMsg()
{
	for (int i = 0; i < (int)m_arrMsg.size(); i++)
	{
		void * lpMsg = m_arrMsg[i];
		if (lpMsg != NULL)
		{
			switch (m_nType)
			{
			case QQ_MSG_TYPE_BUDDY:
				delete (CBuddyMessage *)lpMsg;
				break;
			case QQ_MSG_TYPE_GROUP:
				delete (CGroupMessage *)lpMsg;
				break;
			case QQ_MSG_TYPE_SESS:
				delete (CSessMessage *)lpMsg;
				break;
			case QQ_MSG_TYPE_SYSGROUP:
				delete (CSysGroupMessage *)lpMsg;
				break;
			}
		}
	}
	m_arrMsg.clear();
	return TRUE;
}

// 获取消息类型
QQ_MSG_TYPE CMessageSender::GetMsgType()
{
	return m_nType;
}

// 获取发送者Id
UINT CMessageSender::GetSenderId()
{
	return m_nSenderId;
}

// 获取消息总数
int CMessageSender::GetMsgCount()
{
	return (int)m_arrMsg.size();
}

// 获取群代码
UINT CMessageSender::GetGroupCode()
{
	return m_nGroupCode;
}

// 获取好友消息(根据索引)
CBuddyMessage * CMessageSender::GetBuddyMsg(int nIndex)
{
	if (m_nType != QQ_MSG_TYPE_BUDDY)
		return NULL;

	if (nIndex >= 0 && nIndex < (int)m_arrMsg.size())
		return (CBuddyMessage *)m_arrMsg[nIndex];
	else
		return NULL;
}

// 获取群消息(根据索引)
CGroupMessage * CMessageSender::GetGroupMsg(int nIndex)
{
	if (m_nType != QQ_MSG_TYPE_GROUP)
		return NULL;

	if (nIndex >= 0 && nIndex < (int)m_arrMsg.size())
		return (CGroupMessage *)m_arrMsg[nIndex];
	else
		return NULL;
}

// 获取临时会话消息(根据索引)
CSessMessage * CMessageSender::GetSessMsg(int nIndex)
{
	if (m_nType != QQ_MSG_TYPE_SESS)
		return NULL;

	if (nIndex >= 0 && nIndex < (int)m_arrMsg.size())
		return (CSessMessage *)m_arrMsg[nIndex];
	else
		return NULL;
}

// 获取群系统消息(根据索引)
CSysGroupMessage * CMessageSender::GetSysGroupMsg(int nIndex)
{
	if (m_nType != QQ_MSG_TYPE_SYSGROUP)
		return NULL;

	if (nIndex >= 0 && nIndex < (int)m_arrMsg.size())
		return (CSysGroupMessage *)m_arrMsg[nIndex];
	else
		return NULL;
}

// 获取好友消息(根据消息Id)
CBuddyMessage * CMessageSender::GetBuddyMsgById(UINT nMsgId)
{
	if (m_nType != QQ_MSG_TYPE_BUDDY)
		return NULL;

	for (int i = 0; i < (int)m_arrMsg.size(); i++)
	{
		CBuddyMessage * lpMsg = (CBuddyMessage *)m_arrMsg[i];
		if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
			return lpMsg;
	}

	return NULL;
}

// 获取群消息(根据消息Id)
CGroupMessage * CMessageSender::GetGroupMsgById(UINT nMsgId)
{
	if (m_nType != QQ_MSG_TYPE_GROUP)
		return NULL;

	for (int i = 0; i < (int)m_arrMsg.size(); i++)
	{
		CGroupMessage * lpMsg = (CGroupMessage *)m_arrMsg[i];
		if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
			return lpMsg;
	}

	return NULL;
}

// 获取临时会话消息(根据消息Id)
CSessMessage * CMessageSender::GetSessMsgById(UINT nMsgId)
{
	if (m_nType != QQ_MSG_TYPE_SESS)
		return NULL;

	for (int i = 0; i < (int)m_arrMsg.size(); i++)
	{
		CSessMessage * lpMsg = (CSessMessage *)m_arrMsg[i];
		if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
			return lpMsg;
	}

	return NULL;
}

// 获取群系统消息(根据消息Id)
CSysGroupMessage * CMessageSender::GetSysGroupMsgById(UINT nMsgId)
{
	if (m_nType != QQ_MSG_TYPE_SYSGROUP)
		return NULL;

	for (int i = 0; i < (int)m_arrMsg.size(); i++)
	{
		CSysGroupMessage * lpMsg = (CSysGroupMessage *)m_arrMsg[i];
		if (lpMsg != NULL && lpMsg->m_nMsgId == nMsgId)
			return lpMsg;
	}

	return NULL;
}

CMessageList::CMessageList(void)
{
	
}

CMessageList::~CMessageList(void)
{
	DelAllMsgSender();
}

// 添加消息
BOOL CMessageList::AddMsg(QQ_MSG_TYPE nType, UINT nSenderId,
						  UINT nGroupCode, void * lpMsg)
{
	if (NULL == lpMsg)
		return FALSE;

	CMessageSender * lpMsgSender = GetMsgSender(nType, nSenderId);
	if (NULL == lpMsgSender)
	{
		lpMsgSender = new CMessageSender(nType, nSenderId, nGroupCode);
		if (NULL == lpMsgSender)
			return FALSE;

		m_arrMsgSender.push_back(lpMsgSender);
	}
	AddMsgIdentity(nType, nSenderId);
	return lpMsgSender->AddMsg(lpMsg);
}

// 删除消息
BOOL CMessageList::DelMsg(QQ_MSG_TYPE nType, UINT nMsgId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == nType)
		{
			if (lpMsgSender->DelMsgById(nMsgId))
				return TRUE;
		}
	}
	return FALSE;
}

// 删除消息发送者(根据索引)
BOOL CMessageList::DelMsgSender(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrMsgSender.size())
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[nIndex];
		if (lpMsgSender != NULL)
		{
			DelMsgIdentity(lpMsgSender->GetMsgType(), lpMsgSender->GetSenderId());
			delete lpMsgSender;
		}
		m_arrMsgSender.erase(m_arrMsgSender.begin()+nIndex);
		return TRUE;
	}
	else
		return FALSE;
}

// 删除消息发送者(根据消息类型和发送者Id)
BOOL CMessageList::DelMsgSender(QQ_MSG_TYPE nType, UINT nSenderId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == nType
			&& lpMsgSender->GetSenderId() == nSenderId)
		{
			DelMsgIdentity(nType, nSenderId);
			delete lpMsgSender;
			m_arrMsgSender.erase(m_arrMsgSender.begin()+i);
			return TRUE;
		}
	}
	return FALSE;
}

// 删除所有消息发送者
BOOL CMessageList::DelAllMsgSender()
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL)
		{
			DelMsgIdentity(lpMsgSender->GetMsgType(), lpMsgSender->GetSenderId());
			delete lpMsgSender;
		}
	}
	m_arrMsgSender.clear();
	return TRUE;
}

// 获取消息发送者总数
int CMessageList::GetMsgSenderCount()
{
	return (int)m_arrMsgSender.size();
}

// 获取消息发送者(根据索引)
CMessageSender * CMessageList::GetMsgSender(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrMsgSender.size())
		return m_arrMsgSender[nIndex];
	else
		return NULL;
}

// 获取消息发送者(根据消息类型和发送者Id)
CMessageSender * CMessageList::GetMsgSender(QQ_MSG_TYPE nType, UINT nSenderId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == nType
			&& lpMsgSender->GetSenderId() == nSenderId)
		{
			return lpMsgSender;
		}
	}
	return NULL;
}

// 获取最后一个发送消息过来的发送者
CMessageSender * CMessageList::GetLastMsgSender()
{
	int nCount = m_arrMsgIdentity.size();
	if (nCount <= 0)
		return NULL;

	MSG_IDENTITY stMsgId;
	stMsgId = m_arrMsgIdentity[nCount - 1];
	return GetMsgSender(stMsgId.nType, stMsgId.nSenderId);
}

// 获取好友消息(根据消息Id)
CBuddyMessage * CMessageList::GetBuddyMsg(UINT nMsgId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == QQ_MSG_TYPE_BUDDY)
		{
			CBuddyMessage * lpMsg = lpMsgSender->GetBuddyMsgById(nMsgId);
			if (lpMsg != NULL)
				return lpMsg;
		}
	}
	return NULL;
}

// 获取群消息(根据消息Id)
CGroupMessage * CMessageList::GetGroupMsg(UINT nMsgId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == QQ_MSG_TYPE_GROUP)
		{
			CGroupMessage * lpMsg = lpMsgSender->GetGroupMsgById(nMsgId);
			if (lpMsg != NULL)
				return lpMsg;
		}
	}
	return NULL;
}

// 获取临时会话消息(根据消息Id)
CSessMessage * CMessageList::GetSessMsg(UINT nMsgId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == QQ_MSG_TYPE_SESS)
		{
			CSessMessage * lpMsg = lpMsgSender->GetSessMsgById(nMsgId);
			if (lpMsg != NULL)
				return lpMsg;
		}
	}
	return NULL;
}

// 获取群系统消息(根据消息Id)
CSysGroupMessage * CMessageList::GetSysGroupMsg(UINT nMsgId)
{
	for (int i = 0; i < (int)m_arrMsgSender.size(); i++)
	{
		CMessageSender * lpMsgSender = m_arrMsgSender[i];
		if (lpMsgSender != NULL && lpMsgSender->GetMsgType() == QQ_MSG_TYPE_SYSGROUP)
		{
			CSysGroupMessage * lpMsg = lpMsgSender->GetSysGroupMsgById(nMsgId);
			if (lpMsg != NULL)
				return lpMsg;
		}
	}
	return NULL;
}

// 获取好友消息(根据发送者Id和消息Id)
CBuddyMessage * CMessageList::GetBuddyMsg(UINT nQQUin, UINT nMsgId)
{
	CMessageSender * lpMsgSender = GetMsgSender(QQ_MSG_TYPE_BUDDY, nQQUin);
	if (lpMsgSender != NULL)
		return lpMsgSender->GetBuddyMsgById(nMsgId);
	else
		return NULL;
}

// 获取群消息(根据发送者Id和消息Id)
CGroupMessage * CMessageList::GetGroupMsg(UINT nGroupCode, UINT nMsgId)
{
	CMessageSender * lpMsgSender = GetMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);
	if (lpMsgSender != NULL)
		return lpMsgSender->GetGroupMsgById(nMsgId);
	else
		return NULL;
}

// 获取临时会话消息(根据发送者Id和消息Id)
CSessMessage * CMessageList::GetSessMsg(UINT nQQUin, UINT nMsgId)
{
	CMessageSender * lpMsgSender = GetMsgSender(QQ_MSG_TYPE_SESS, nQQUin);
	if (lpMsgSender != NULL)
		return lpMsgSender->GetSessMsgById(nMsgId);
	else
		return NULL;
}

// 获取群系统消息(根据发送者Id和消息Id)
CSysGroupMessage * CMessageList::GetSysGroupMsg(UINT nGroupCode, UINT nMsgId)
{
	CMessageSender * lpMsgSender = GetMsgSender(QQ_MSG_TYPE_SYSGROUP, nGroupCode);
	if (lpMsgSender != NULL)
		return lpMsgSender->GetSysGroupMsgById(nMsgId);
	else
		return NULL;
}

void CMessageList::AddMsgIdentity(QQ_MSG_TYPE nType, UINT nSenderId)
{
	DelMsgIdentity(nType, nSenderId);

	MSG_IDENTITY stMsgId;
	stMsgId.nType = nType;
	stMsgId.nSenderId = nSenderId;
	m_arrMsgIdentity.push_back(stMsgId);
}

void CMessageList::DelMsgIdentity(QQ_MSG_TYPE nType, UINT nSenderId)
{
	for (int i = 0; i < (int)m_arrMsgIdentity.size(); i++)
	{
		if (m_arrMsgIdentity[i].nType == nType 
			&& m_arrMsgIdentity[i].nSenderId == nSenderId)
		{
			m_arrMsgIdentity.erase(m_arrMsgIdentity.begin()+i);
			break;
		}
	}
}

// CMessageLogger::CMessageLogger(void)
// {
// 
// }
// 
// CMessageLogger::~CMessageLogger(void)
// {
// 
// }
// 
// BOOL CMessageLogger::CreateMsgLogFile(LPCTSTR lpszFileName)
// {
// 	sqlite3 *conn = NULL;
// 	char *err_msg = NULL;
// 
// 	int nRet = sqlite3_open16(lpszFileName, &conn);
// 	if (nRet != SQLITE_OK)
// 		return FALSE;
// 
// 	char * lpSql = "CREATE TABLE [tb_BuddyMsg] ([id] INTEGER PRIMARY KEY, [uin] INTEGER, [nickname] TEXT, [time] INTEGER, [sendflag] INTEGER, [content] TEXT)";
// 	nRet = sqlite3_exec(conn, lpSql, 0, 0, &err_msg);	// 创建好友消息表
// 	if (nRet != SQLITE_OK)
// 	{
// 		sqlite3_close(conn);
// 		return FALSE;
// 	}
// 
// 	lpSql = "CREATE TABLE [tb_GroupMsg] ([id] INTEGER PRIMARY KEY, [groupnum] INTEGER, [uin] INTEGER, [nickname] TEXT, [time] INTEGER, [content] TEXT)";
// 	nRet = sqlite3_exec(conn, lpSql, 0, 0, &err_msg);	// 创建群消息表
// 	if (nRet != SQLITE_OK)
// 	{
// 		sqlite3_close(conn);
// 		return FALSE;
// 	}
// 
// 	lpSql = "CREATE TABLE [tb_SessMsg] ([id] INTEGER PRIMARY KEY, [uin] INTEGER, [nickname] TEXT, [time] INTEGER, [sendflag] INTEGER, [content] TEXT)";
// 	nRet = sqlite3_exec(conn, lpSql, 0, 0, &err_msg);	// 创建临时会话(群成员)消息表
// 	if (nRet != SQLITE_OK)
// 	{
// 		sqlite3_close(conn);
// 		return FALSE;
// 	}
// 
// 	nRet = sqlite3_close(conn);
// 	return (nRet != SQLITE_OK) ? FALSE : TRUE;
// }