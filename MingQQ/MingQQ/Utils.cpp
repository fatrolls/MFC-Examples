#include "StdAfx.h"
#include "Utils.h"

WCHAR * AnsiToUnicode(const CHAR * lpszStr)
{
	WCHAR * lpUnicode;
	int nLen;

	if (NULL == lpszStr)
		return NULL;

	nLen = ::MultiByteToWideChar(CP_ACP, 0, lpszStr, -1, NULL, 0);
	if (0 == nLen)
		return NULL;

	lpUnicode = new WCHAR[nLen + 1];
	if (NULL == lpUnicode)
		return NULL;

	memset(lpUnicode, 0, sizeof(WCHAR) * (nLen + 1));
	nLen = ::MultiByteToWideChar(CP_ACP, 0, lpszStr, -1, lpUnicode, nLen);
	if (0 == nLen)
	{
		delete []lpUnicode;
		return NULL;
	}

	return lpUnicode;
}

CHAR * UnicodeToAnsi(const WCHAR * lpszStr)
{
	CHAR * lpAnsi;
	int nLen;

	if (NULL == lpszStr)
		return NULL;

	nLen = ::WideCharToMultiByte(CP_ACP, 0, lpszStr, -1, NULL, 0, NULL, NULL);
	if (0 == nLen)
		return NULL;

	lpAnsi = new CHAR[nLen + 1];
	if (NULL == lpAnsi)
		return NULL;

	memset(lpAnsi, 0, nLen + 1);
	nLen = ::WideCharToMultiByte(CP_ACP, 0, lpszStr, -1, lpAnsi, nLen, NULL, NULL);
	if (0 == nLen)
	{
		delete []lpAnsi;
		return NULL;
	}

	return lpAnsi;
}

CHAR * AnsiToUtf8(const CHAR * lpszStr)
{
	WCHAR * lpUnicode;
	CHAR * lpUtf8;
	int nLen;

	if (NULL == lpszStr)
		return NULL;

	nLen = ::MultiByteToWideChar(CP_ACP, 0, lpszStr, -1, NULL, NULL);
	if (0 == nLen)
		return NULL;

	lpUnicode = new WCHAR[nLen + 1];
	if (NULL == lpUnicode)
		return NULL;

	memset(lpUnicode, 0, sizeof(WCHAR) * (nLen + 1));
	nLen = ::MultiByteToWideChar(CP_ACP, 0, lpszStr, -1, lpUnicode, nLen);
	if (0 == nLen)
	{
		delete []lpUnicode;
		return NULL;
	}

	nLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicode, -1, NULL, 0, NULL, NULL);
	if (0 == nLen)
	{
		delete []lpUnicode;
		return NULL;
	}

	lpUtf8 = new CHAR[nLen + 1];
	if (NULL == lpUtf8)
	{
		delete []lpUnicode;
		return NULL;
	}

	memset(lpUtf8, 0, nLen + 1);
	nLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicode, -1, lpUtf8, nLen, NULL, NULL);
	if (0 == nLen)
	{
		delete []lpUnicode;
		delete []lpUtf8;
		return NULL;
	}

	delete []lpUnicode;

	return lpUtf8;
}

CHAR * Utf8ToAnsi(const CHAR * lpszStr)
{
	WCHAR * lpUnicode;
	CHAR * lpAnsi;
	int nLen;

	if (NULL == lpszStr)
		return NULL;

	nLen = ::MultiByteToWideChar(CP_UTF8, 0, lpszStr, -1, NULL, NULL);
	if (0 == nLen)
		return NULL;

	lpUnicode = new WCHAR[nLen + 1];
	if (NULL == lpUnicode)
		return NULL;

	memset(lpUnicode, 0, sizeof(WCHAR) * (nLen + 1));
	nLen = ::MultiByteToWideChar(CP_UTF8, 0, lpszStr, -1, lpUnicode, nLen);
	if (0 == nLen)
	{
		delete []lpUnicode;
		return NULL;
	}

	nLen = ::WideCharToMultiByte(CP_ACP, 0, lpUnicode, -1, NULL, 0, NULL, NULL);
	if (0 == nLen)
	{
		delete []lpUnicode;
		return NULL;
	}

	lpAnsi = new CHAR[nLen + 1];
	if (NULL == lpAnsi)
	{
		delete []lpUnicode;
		return NULL;
	}

	memset(lpAnsi, 0, nLen + 1);
	nLen = ::WideCharToMultiByte(CP_ACP, 0, lpUnicode, -1, lpAnsi, nLen, NULL, NULL);
	if (0 == nLen)
	{
		delete []lpUnicode;
		delete []lpAnsi;
		return NULL;
	}

	delete []lpUnicode;

	return lpAnsi;
}

CHAR * UnicodeToUtf8(const WCHAR * lpszStr)
{
	CHAR * lpUtf8;
	int nLen;

	if (NULL == lpszStr)
		return NULL;

	nLen = ::WideCharToMultiByte(CP_UTF8, 0, lpszStr, -1, NULL, 0, NULL, NULL);
	if (0 == nLen)
		return NULL;

	lpUtf8 = new CHAR[nLen + 1];
	if (NULL == lpUtf8)
		return NULL;

	memset(lpUtf8, 0, nLen + 1);
	nLen = ::WideCharToMultiByte(CP_UTF8, 0, lpszStr, -1, lpUtf8, nLen, NULL, NULL);
	if (0 == nLen)
	{
		delete []lpUtf8;
		return NULL;
	}

	return lpUtf8;
}

WCHAR * Utf8ToUnicode(const CHAR * lpszStr)
{
	WCHAR * lpUnicode;
	int nLen;

	if (NULL == lpszStr)
		return NULL;

	nLen = ::MultiByteToWideChar(CP_UTF8, 0, lpszStr, -1, NULL, 0);
	if (0 == nLen)
		return NULL;

	lpUnicode = new WCHAR[nLen + 1];
	if (NULL == lpUnicode)
		return NULL;

	memset(lpUnicode, 0, sizeof(WCHAR) * (nLen + 1));
	nLen = ::MultiByteToWideChar(CP_UTF8, 0, lpszStr, -1, lpUnicode, nLen);
	if (0 == nLen)
	{
		delete []lpUnicode;
		return NULL;
	}

	return lpUnicode;
}

BOOL AnsiToUnicode(const CHAR * lpszAnsi, WCHAR * lpszUnicode, int nLen)
{
	int nRet = ::MultiByteToWideChar(CP_ACP, 0, lpszAnsi, -1, lpszUnicode, nLen);
	return (0 == nRet) ? FALSE : TRUE;
}

BOOL UnicodeToAnsi(const WCHAR * lpszUnicode, CHAR * lpszAnsi, int nLen)
{
	int nRet = ::WideCharToMultiByte(CP_ACP, 0, lpszUnicode, -1, lpszAnsi, nLen, NULL, NULL);
	return (0 == nRet) ? FALSE : TRUE;
}

BOOL AnsiToUtf8(const CHAR * lpszAnsi, CHAR * lpszUtf8, int nLen)
{
	WCHAR * lpszUnicode = AnsiToUnicode(lpszAnsi);
	if (NULL == lpszUnicode)
		return FALSE;

	int nRet = UnicodeToUtf8(lpszUnicode, lpszUtf8, nLen);

	delete []lpszUnicode;

	return (0 == nRet) ? FALSE : TRUE;
}

BOOL Utf8ToAnsi(const CHAR * lpszUtf8, CHAR * lpszAnsi, int nLen)
{
	WCHAR * lpszUnicode = Utf8ToUnicode(lpszUtf8);
	if (NULL == lpszUnicode)
		return FALSE;

	int nRet = UnicodeToAnsi(lpszUnicode, lpszAnsi, nLen);

	delete []lpszUnicode;

	return (0 == nRet) ? FALSE : TRUE;
}

BOOL UnicodeToUtf8(const WCHAR * lpszUnicode, CHAR * lpszUtf8, int nLen)
{
	int nRet = ::WideCharToMultiByte(CP_UTF8, 0, lpszUnicode, -1, lpszUtf8, nLen, NULL, NULL);
	return (0 == nRet) ? FALSE : TRUE;
}

BOOL Utf8ToUnicode(const CHAR * lpszUtf8, WCHAR * lpszUnicode, int nLen)
{
	int nRet = ::MultiByteToWideChar(CP_UTF8, 0, lpszUtf8, -1, lpszUnicode, nLen);
	return (0 == nRet) ? FALSE : TRUE;
}

std::wstring AnsiToUnicode(const std::string& strAnsi)
{
	std::wstring strUnicode;

	WCHAR * lpszUnicode = AnsiToUnicode(strAnsi.c_str());
	if (lpszUnicode != NULL)
	{
		strUnicode = lpszUnicode;
		delete []lpszUnicode;
	}

	return strUnicode;
}
std::string UnicodeToAnsi(const std::wstring& strUnicode)
{
	std::string strAnsi;

	CHAR * lpszAnsi = UnicodeToAnsi(strUnicode.c_str());
	if (lpszAnsi != NULL)
	{
		strAnsi = lpszAnsi;
		delete []lpszAnsi;
	}

	return strAnsi;
}

std::string AnsiToUtf8(const std::string& strAnsi)
{
	std::string strUtf8;

	CHAR * lpszUtf8 = AnsiToUtf8(strAnsi.c_str());
	if (lpszUtf8 != NULL)
	{
		strUtf8 = lpszUtf8;
		delete []lpszUtf8;
	}

	return strUtf8;
}

std::string Utf8ToAnsi(const std::string& strUtf8)
{
	std::string strAnsi;

	CHAR * lpszAnsi = Utf8ToAnsi(strUtf8.c_str());
	if (lpszAnsi != NULL)
	{
		strAnsi = lpszAnsi;
		delete []lpszAnsi;
	}

	return strAnsi;
}

std::string UnicodeToUtf8(const std::wstring& strUnicode)
{
	std::string strUtf8;

	CHAR * lpszUtf8 = UnicodeToUtf8(strUnicode.c_str());
	if (lpszUtf8 != NULL)
	{
		strUtf8 = lpszUtf8;
		delete []lpszUtf8;
	}

	return strUtf8;
}

std::wstring Utf8ToUnicode(const std::string& strUtf8)
{
	std::wstring strUnicode;

	WCHAR * lpszUnicode = Utf8ToUnicode(strUtf8.c_str());
	if (lpszUnicode != NULL)
	{
		strUnicode = lpszUnicode;
		delete []lpszUnicode;
	}

	return strUnicode;
}

BOOL ToHexStr(const CHAR * lpStr, int nSrcLen, CHAR * lpHex, int nDestLen)
{
	const CHAR cHexTable[] = "0123456789ABCDEF";

	if (lpStr == NULL || nSrcLen <= 0
		|| lpHex == NULL || nDestLen <= 0)
		return FALSE;

	if (nDestLen < nSrcLen * 2)
		return FALSE;

	int i = 0;
	for (int j = 0; j < nSrcLen; j++)
	{
		unsigned int a = (unsigned int)lpStr[j];
		lpHex[i++] = cHexTable[(a & 0xf0) >> 4];
		lpHex[i++] = cHexTable[(a & 0x0f)];
	}
	lpHex[i] = '\0';

	return TRUE;
}

BOOL StrToHex(const CHAR * lpStr, CHAR * lpHex, int nLen)
{
	const CHAR cHexTable[] = "0123456789ABCDEF";

	if (lpStr == NULL || lpHex == NULL || nLen <= 0)
		return FALSE;

	int nSrcLen = strlen(lpStr);
	if (nLen <= nSrcLen * 2)
		return FALSE;

	int i = 0;
	for (int j = 0; j < (int)strlen(lpStr); j++)
	{
		unsigned int a = (unsigned int)lpStr[j];
		lpHex[i++] = cHexTable[(a & 0xf0) >> 4];
		lpHex[i++] = cHexTable[(a & 0x0f)];
	}
	lpHex[i] = '\0';

	return TRUE;
}

// 16位整型数据网络字节序与正常字节序转换
u_short Swap16(u_short nValue)
{
	u_short nRetValue = (u_short)((nValue & 0xff00) >> 0x08);
	nRetValue |= (u_short)(nValue << 0x08);
	return nRetValue;

}

// 32位整型数据网络字节序与正常字节序转换
u_long Swap32(u_long nValue)
{
	u_long nRetValue = ((nValue & 0xff000000) >> 0x18);
	nRetValue |= ((nValue & 0x00ff0000) >> 0x08);
	nRetValue |= ((nValue & 0x0000ff00) << 0x08);
	nRetValue |= ((nValue & 0x000000ff) << 0x18);

	return nRetValue;
}

COLORREF HexStrToRGB(LPCTSTR lpszStr)
{
	unsigned long lValue = _tcstoul(lpszStr, NULL, 16);
	return RGB((lValue & 0xFF0000) >> 16,  (lValue & 0xFF00 ) >> 8, lValue & 0xFF);
}

void RGBToHexStr(COLORREF color, TCHAR * lpBuf, int nLen)
{
	if (NULL == lpBuf || nLen <= 0)
		return;
	wsprintf(lpBuf, _T("%02x%02x%02x"), GetRValue(color), GetGValue(color), GetBValue(color));
}

BOOL IsToday(time_t lTime)
{
	time_t lCurTime;
	struct tm * lpCurTimeInfo, * lpTimeInfo;

	lCurTime = time(NULL);
	lpCurTimeInfo = localtime(&lCurTime);

	lpTimeInfo = localtime(&lTime);

	if (lpCurTimeInfo != NULL && lpTimeInfo != NULL
		&& lpCurTimeInfo->tm_year == lpTimeInfo->tm_year
		&& lpCurTimeInfo->tm_mon == lpTimeInfo->tm_mon
		&& lpCurTimeInfo->tm_mday == lpTimeInfo->tm_mday)
		return TRUE;
	else
		return FALSE;
}

// _T("%Y-%m-%d %H:%M:%S")
void FormatTime(time_t lTime, LPCTSTR lpFmt, TCHAR * lpBuf, int nLen)
{
	if (NULL == lpFmt || NULL == lpBuf || nLen <= 0)
		return;

	memset(lpBuf, 0, nLen*sizeof(TCHAR));

	struct tm * lpTimeInfo = localtime(&lTime);
	if (lpTimeInfo != NULL)
		_tcsftime(lpBuf, nLen, lpFmt, lpTimeInfo);
}

BOOL IsToday(SYSTEMTIME * lpTime)
{
	if (NULL == lpTime)
		return FALSE;

	SYSTEMTIME stSysTime = {0};
	::GetLocalTime(&stSysTime);

	if (stSysTime.wYear == lpTime->wYear
		&& stSysTime.wMonth == lpTime->wMonth
		&& stSysTime.wDay == lpTime->wDay)
		return TRUE;
	else
		return FALSE;
}

// 获取文件最后修改时间
BOOL GetFileLastWriteTime(LPCTSTR lpszFileName, SYSTEMTIME * lpSysTime)
{
	BOOL bRet = FALSE;

	if (NULL == lpszFileName || NULL == *lpszFileName
		|| NULL == lpSysTime)
		return FALSE;

	HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, 
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL); 
	if (hFile != INVALID_HANDLE_VALUE)
	{
		FILETIME stLastWriteTime = {0};
		bRet = ::GetFileTime(hFile, NULL, NULL, &stLastWriteTime);
		if (bRet)
		{
			FILETIME stLocalFileTime = {0};
			bRet = ::FileTimeToLocalFileTime(&stLastWriteTime, &stLocalFileTime);
			if (bRet)
				bRet = ::FileTimeToSystemTime(&stLocalFileTime, lpSysTime);
		}
		::CloseHandle(hFile);
	}
	return bRet;
}

// 读取整个文件
BOOL File_ReadAll(const TCHAR * lpszFileName, CHAR **lpData, LONG *lSize)
{
	if (NULL == lpData || NULL == lSize)
		return FALSE;

	CHAR * lpFileData = NULL;
	LONG lFileSize = 0;

	FILE * fp = _tfopen(lpszFileName, _T("rb"));
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		lFileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		if (lFileSize > 0)
		{
			lpFileData = new CHAR[lFileSize+16];
			if (lpFileData != NULL)
			{
				memset(lpFileData, 0, lFileSize+16);
				fread(lpFileData, lFileSize, 1, fp);
			}
		}

		fclose(fp);
	}

	if (lpFileData != NULL && lFileSize > 0)
	{
		*lpData = lpFileData;
		*lSize = lFileSize;
		return TRUE;
	}
	else
	{
		*lpData = NULL;
		*lSize = 0;
		return FALSE;
	}
}

// 检测指定字符是否是字母(A-Z，a-z)或数字(0-9)
BOOL my_isalnum(unsigned char cChar)
{
	return ((cChar | 0x20) - 'a') < 26u  || (cChar - '0') < 10u;
}

// 检测指定字符是否是字母(A-Z，a-z)或数字(0-9)
BOOL my_isalnum(wchar_t cChar)
{
	return ((cChar | 0x20) - L'a') < 26u  || (cChar - L'0') < 10u;
}

// 枚举系统字体回调函数
int CALLBACK EnumSysFontProc(const LOGFONT *lpelf, const TEXTMETRIC *lpntm, DWORD dwFontType, LPARAM lParam)
{
	if (dwFontType & TRUETYPE_FONTTYPE)
	{
		std::vector<tstring> * arrSysFont = (std::vector<tstring> *)lParam;
		if (arrSysFont != NULL)
		{
			for (int i = 0; i < (int)arrSysFont->size(); i++)
			{
				if ((*arrSysFont)[i] == lpelf->lfFaceName)
					return TRUE;
			}
			arrSysFont->push_back(lpelf->lfFaceName);
		}
	}

	return TRUE;
}

// 枚举系统字体
BOOL EnumSysFont(std::vector<tstring> * arrSysFont)
{
	if (NULL == arrSysFont)
		return FALSE;

	HDC hDC = ::GetDC(NULL);
	::EnumFontFamiliesEx(hDC, NULL, EnumSysFontProc, (LPARAM)arrSysFont, 0);
	::ReleaseDC(NULL, hDC);

	return TRUE;
}

// 闪烁窗口标题栏
BOOL FlashWindowEx(HWND hWnd, int nCount)
{
	FLASHWINFO stFlashInfo = {0};
	stFlashInfo.cbSize = sizeof(FLASHWINFO);
	stFlashInfo.hwnd = hWnd;
	stFlashInfo.dwFlags = FLASHW_TRAY | FLASHW_TIMERNOFG;
	stFlashInfo.uCount = nCount;
	stFlashInfo.dwTimeout = 0;
	return ::FlashWindowEx(&stFlashInfo);
}

// 获取系统任务栏区域
BOOL GetTrayWndRect(RECT * lpRect)
{
	if (NULL == lpRect)
		return FALSE;

	HWND hWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	if (hWnd != NULL)
		return ::GetWindowRect(hWnd, lpRect);
	else
		return FALSE;
}

BOOL IsDigit(const WCHAR * lpStr)
{
	for (const WCHAR * p = lpStr; *p != _T('\0'); p++)
	{
		if (!isdigit(*p))
			return FALSE;
	}
	return TRUE;
}

void Replace(std::string& strText, const CHAR * lpOldStr, const CHAR * lpNewStr)
{
	if (NULL == lpOldStr || NULL == lpNewStr)
		return;

	int nOldStrLen = strlen(lpOldStr);
	int nNewStrLen = strlen(lpNewStr);

	std::string::size_type nPos = 0;
	while ((nPos = strText.find(lpOldStr, nPos)) != std::string::npos)
	{
		strText.replace(nPos, nOldStrLen, lpNewStr);
		nPos += nNewStrLen;
	}
}

void Replace(std::wstring& strText, const WCHAR * lpOldStr, const WCHAR * lpNewStr)
{
	if (NULL == lpOldStr || NULL == lpNewStr)
		return;

	int nOldStrLen = wcslen(lpOldStr);
	int nNewStrLen = wcslen(lpNewStr);

	std::wstring::size_type nPos = 0;
	while ((nPos = strText.find(lpOldStr, nPos)) != std::wstring::npos)
	{
		strText.replace(nPos, nOldStrLen, lpNewStr);
		nPos += nNewStrLen;
	}
}

inline WCHAR ToLower(WCHAR c)
{
	return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
}

void ToLower(WCHAR * lpText)
{
	for (WCHAR * p = lpText; *p != _T('\0'); p++)
		*p = ToLower(*p);
}

void ToLower(std::wstring& strText)
{
	for (std::wstring::iterator i = strText.begin(); i != strText.end(); ++i)
		*i = ToLower(*i);
}

inline WCHAR ToUpper(WCHAR c)
{
	return (c >= 'a' && c <= 'z') ? (c + ('A' - 'a')) : c;
}

void ToUpper(WCHAR * lpText)
{
	for (WCHAR * p = lpText; *p != _T('\0'); p++)
		*p = ToUpper(*p);
}

void ToUpper(std::wstring& strText)
{
	for (std::wstring::iterator i = strText.begin(); i != strText.end(); ++i)
		*i = ToUpper(*i);
}

// 编码Html特殊字符
void EncodeHtmlSpecialChars(std::wstring& strText)
{
	Replace(strText, _T("&"), _T("&amp;"));
	Replace(strText, _T("'"), _T("&#39;"));
	Replace(strText, _T("\""), _T("&quot;"));
	Replace(strText, _T("<"), _T("&lt;"));
	Replace(strText, _T(">"), _T("&gt;"));
	Replace(strText, _T(" "), _T("&nbsp;"));
}

// 解码Html特殊字符
void DecodeHtmlSpecialChars(std::wstring& strText)
{
	Replace(strText, _T("&#39;"), _T("'"));
	Replace(strText, _T("&quot;"), _T("\""));
	Replace(strText, _T("&lt;"), _T("<"));
	Replace(strText, _T("&gt;"), _T(">"));
	Replace(strText, _T("&nbsp;"), _T(" "));
	Replace(strText, _T("&amp;"), _T("&"));
}

tstring GetBetweenString(const TCHAR * pStr, TCHAR cStart, TCHAR cEnd)
{
	tstring strText;

	if (NULL == pStr)
		return _T("");

	const TCHAR * p1 = _tcschr(pStr, cStart);
	if (NULL == p1)
		return _T("");

	const TCHAR * p2 = _tcschr(p1+1, cEnd);
	if (NULL == p2)
		return _T("");

	int nLen = p2-(p1+1);
	if (nLen <= 0)
		return _T("");

	TCHAR * lpText = new TCHAR[nLen+1];
	if (NULL == lpText)
		return _T("");

	memset(lpText, 0, (nLen+1)*sizeof(TCHAR));
	_tcsncpy(lpText, p1+1, nLen);
	strText = lpText;
	delete []lpText;

	return strText;
}

int GetBetweenInt(const TCHAR * pStr, TCHAR cStart, TCHAR cEnd, int nDefValue/* = 0*/)
{
	tstring strText = GetBetweenString(pStr, cStart, cEnd);
	if (!strText.empty() && IsDigit(strText.c_str()))
		return _tcstol(strText.c_str(), NULL, 10);
	else
		return nDefValue;
}

tstring GetBetweenString(const WCHAR * pStr, const WCHAR * pStart, const WCHAR * pEnd)
{
	tstring strText;

	if (NULL == pStr || NULL == pStart || NULL == pEnd)
		return _T("");

	int nStartLen = _tcslen(pStart);

	const TCHAR * p1 = _tcsstr(pStr, pStart);
	if (NULL == p1)
		return _T("");

	const TCHAR * p2 = _tcsstr(p1+nStartLen, pEnd);
	if (NULL == p2)
		return _T("");

	int nLen = p2-(p1+nStartLen);
	if (nLen <= 0)
		return _T("");

	TCHAR * lpText = new TCHAR[nLen+1];
	if (NULL == lpText)
		return _T("");

	memset(lpText, 0, (nLen+1)*sizeof(TCHAR));
	_tcsncpy(lpText, p1+nStartLen, nLen);
	strText = lpText;
	delete []lpText;

	return strText;
}

int GetBetweenInt(const WCHAR * pStr, const WCHAR * pStart, 
				  const WCHAR * pEnd, int nDefValue/* = 0*/)
{
	tstring strText = GetBetweenString(pStr, pStart, pEnd);
	if (!strText.empty() && IsDigit(strText.c_str()))
		return _tcstol(strText.c_str(), NULL, 10);
	else
		return nDefValue;
}

BOOL DllRegisterServer(LPCTSTR lpszFileName, BOOL bUnregister)
{
	typedef HRESULT (WINAPI * FREG)();

	BOOL bRet = FALSE;

	HMODULE hDLL = ::LoadLibrary(lpszFileName);
	if (NULL == hDLL)
		return FALSE;

	CHAR * lpszFuncName;
	if (!bUnregister)
		lpszFuncName = "DllRegisterServer";
	else
		lpszFuncName = "DllUnregisterServer";

	FREG lpfunc = (FREG)::GetProcAddress(hDLL, lpszFuncName);
	if (lpfunc != NULL)
	{
		lpfunc();
		bRet = TRUE;
	}

	::FreeLibrary(hDLL);

	return bRet;
}

BOOL DllRegisterServer(LPCTSTR lpszFileName)
{
	return DllRegisterServer(lpszFileName, FALSE);
}

BOOL DllUnregisterServer(LPCTSTR lpszFileName)
{
	return DllRegisterServer(lpszFileName, TRUE);
}

tstring GetMimeTypeByExtension(const TCHAR * lpExtension)
{
	if (NULL == lpExtension)
		return _T("");

	if (_tcsicmp(lpExtension, _T("jpg")) == 0
		|| _tcsicmp(lpExtension, _T("jpeg")) == 0
		|| _tcsicmp(lpExtension, _T("jpe")) == 0)
		return _T("image/jpeg");
	if (_tcsicmp(lpExtension, _T("png")) == 0)
		return _T("image/png");
	else if (_tcsicmp(lpExtension, _T("gif")) == 0)
		return _T("image/gif");
	else if (_tcsicmp(lpExtension, _T("bmp")) == 0)
		return _T("image/bmp");
	else if (_tcsicmp(lpExtension, _T("tiff")) == 0
		|| _tcsicmp(lpExtension, _T("tif")) == 0)
		return _T("image/tiff");
	else if (_tcsicmp(lpExtension, _T("ico")) == 0)
		return _T("image/vnd.microsoft.icon");
	else if (_tcsicmp(lpExtension, _T("svg")) == 0
		|| _tcsicmp(lpExtension, _T("svgz")) == 0)
		return _T("image/svg+xml");
	else
		return _T("");	// application/octet-stream
}

GUID GetFileTypeGuidByExtension(const WCHAR * lpExtension)
{
	GUID guid = GUID_NULL;

	if (NULL == lpExtension)
		return guid;

	UINT numEncoders = 0, size = 0;
	Gdiplus::Status status = Gdiplus::GetImageEncodersSize(&numEncoders, &size);  
	if (status != Gdiplus::Ok)
		return guid;

	Gdiplus::ImageCodecInfo* lpEncoders = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (NULL == lpEncoders)
		return guid;

	status = Gdiplus::GetImageEncoders(numEncoders, size, lpEncoders);
	if (Gdiplus::Ok == status)
	{
		for (UINT i = 0; i < numEncoders; i++)
		{
			BOOL bFind = FALSE;
			const WCHAR * pStart = lpEncoders[i].FilenameExtension;
			const WCHAR * pEnd = wcschr(pStart, L';');
			do 
			{
				if (NULL == pEnd)
				{
					LPCWSTR lpExt = ::wcsrchr(pStart, L'.');
					if ((lpExt != NULL) && (wcsicmp(lpExt, lpExtension) == 0))
					{
						guid = lpEncoders[i].FormatID;
						bFind = TRUE;
					}
					break;
				}

				int nLen = pEnd-pStart;
				if (nLen < MAX_PATH)
				{
					WCHAR cBuf[MAX_PATH] = {0};
					wcsncpy(cBuf, pStart, nLen);
					LPCWSTR lpExt = ::wcsrchr(cBuf, L'.');
					if ((lpExt != NULL) && (wcsicmp(lpExt, lpExtension) == 0))
					{
						guid = lpEncoders[i].FormatID;
						bFind = TRUE;
						break;
					}
				}
				pStart = pEnd+1;
				if (L'\0' == *pStart)
					break;
				pEnd = wcschr(pStart, L';');
			} while (1);
			if (bFind)
				break;
		}
	}

	free(lpEncoders);

	return guid;
}

CLSID GetEncoderClsidByExtension(const WCHAR * lpExtension)
{
	CLSID clsid = CLSID_NULL;

	if (NULL == lpExtension)
		return clsid;

	UINT numEncoders = 0, size = 0;
	Gdiplus::Status status = Gdiplus::GetImageEncodersSize(&numEncoders, &size);  
	if (status != Gdiplus::Ok)
		return clsid;

	Gdiplus::ImageCodecInfo* lpEncoders = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (NULL == lpEncoders)
		return clsid;

	status = Gdiplus::GetImageEncoders(numEncoders, size, lpEncoders);
	if (Gdiplus::Ok == status)
	{
		for (UINT i = 0; i < numEncoders; i++)
		{
			BOOL bFind = FALSE;
			const WCHAR * pStart = lpEncoders[i].FilenameExtension;
			const WCHAR * pEnd = wcschr(pStart, L';');
			do 
			{
				if (NULL == pEnd)
				{
					LPCWSTR lpExt = ::wcsrchr(pStart, L'.');
					if ((lpExt != NULL) && (wcsicmp(lpExt, lpExtension) == 0))
					{
						clsid = lpEncoders[i].Clsid;
						bFind = TRUE;
					}
					break;
				}

				int nLen = pEnd-pStart;
				if (nLen < MAX_PATH)
				{
					WCHAR cBuf[MAX_PATH] = {0};
					wcsncpy(cBuf, pStart, nLen);
					LPCWSTR lpExt = ::wcsrchr(cBuf, L'.');
					if ((lpExt != NULL) && (wcsicmp(lpExt, lpExtension) == 0))
					{
						clsid = lpEncoders[i].Clsid;
						bFind = TRUE;
						break;
					}
				}
				pStart = pEnd+1;
				if (L'\0' == *pStart)
					break;
				pEnd = wcschr(pStart, L';');
			} while (1);
			if (bFind)
				break;
		}
	}

	free(lpEncoders);

	return clsid;
}

// ImageFormatBMP, ImageFormatJPEG, ImageFormatPNG, ImageFormatGIF, ImageFormatTIFF
CLSID GetEncoderClsidByFileType(REFGUID guidFileType)
{
	CLSID clsid = CLSID_NULL;

	UINT numEncoders = 0, size = 0;
	Gdiplus::Status status = Gdiplus::GetImageEncodersSize(&numEncoders, &size);  
	if (status != Gdiplus::Ok)
		return clsid;

	Gdiplus::ImageCodecInfo* lpEncoders = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (NULL == lpEncoders)
		return clsid;

	status = Gdiplus::GetImageEncoders(numEncoders, size, lpEncoders);
	if (Gdiplus::Ok == status)
	{
		for (UINT i = 0; i < numEncoders; i++)
		{
			if (lpEncoders[i].FormatID == guidFileType)
				clsid = lpEncoders[i].Clsid;
		}
	}

	free(lpEncoders);

	return clsid;
}

// image/bmp, image/jpeg, image/gif, image/tiff, image/png
CLSID GetEncoderClsidByMimeType(const WCHAR * lpMimeType)
{
	CLSID clsid = CLSID_NULL;

	if (NULL == lpMimeType)
		return clsid;

	UINT numEncoders = 0, size = 0;
	Gdiplus::Status status = Gdiplus::GetImageEncodersSize(&numEncoders, &size);  
	if (status != Gdiplus::Ok)
		return clsid;

	Gdiplus::ImageCodecInfo* lpEncoders = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (NULL == lpEncoders)
		return clsid;

	status = Gdiplus::GetImageEncoders(numEncoders, size, lpEncoders);
	if (Gdiplus::Ok == status)
	{
		for (UINT i = 0; i < numEncoders; i++)
		{
			if (wcsicmp(lpEncoders[i].MimeType, lpMimeType) == 0)
				clsid = lpEncoders[i].Clsid;
		}
	}

	free(lpEncoders);

	return clsid;
}

/* RFC1123: Sun, 06 Nov 1994 08:49:37 GMT */
#define RFC1123_FORMAT _T("%3s, %02d %3s %4d %02d:%02d:%02d GMT")
/* RFC850:  Sunday, 06-Nov-94 08:49:37 GMT */
#define RFC1036_FORMAT _T("%10s %2d-%3s-%2d %2d:%2d:%2d GMT")
/* asctime: Wed Jun 30 21:49:08 1993 */
#define ASCTIME_FORMAT _T("%3s %3s %2d %2d:%2d:%2d %4d")

static const TCHAR *const rfc1123_weekdays[7] = { 
    _T("Sun"), _T("Mon"), _T("Tue"), _T("Wed"), _T("Thu"), _T("Fri"), _T("Sat") 
};
static const TCHAR *const short_months[12] = { 
    _T("Jan"), _T("Feb"), _T("Mar"), _T("Apr"), _T("May"), _T("Jun"),
    _T("Jul"), _T("Aug"), _T("Sep"), _T("Oct"), _T("Nov"), _T("Dec")
};

time_t gmt_to_local_win32(void)
{
    TIME_ZONE_INFORMATION tzinfo;
    DWORD dwStandardDaylight;
    long bias;

    dwStandardDaylight = GetTimeZoneInformation(&tzinfo);
    bias = tzinfo.Bias;

    if (dwStandardDaylight == TIME_ZONE_ID_STANDARD)
        bias += tzinfo.StandardBias;
    
    if (dwStandardDaylight == TIME_ZONE_ID_DAYLIGHT)
        bias += tzinfo.DaylightBias;
    
    return (- bias * 60);
}

/* Takes an RFC1123-formatted date string and returns the time_t.
 * Returns (time_t)-1 if the parse fails. */
time_t rfc1123_parse(const TCHAR *date) 
{
    struct tm gmt = {0};
    TCHAR wkday[4], mon[4];
    int n;
/*  it goes: Sun, 06 Nov 1994 08:49:37 GMT */
    n = _stscanf(date, RFC1123_FORMAT,
        wkday, &gmt.tm_mday, mon, &gmt.tm_year, &gmt.tm_hour,
        &gmt.tm_min, &gmt.tm_sec);
    /* Is it portable to check n==7 here? */
    gmt.tm_year -= 1900;
    for (n=0; n<12; n++)
    if (_tcscmp(mon, short_months[n]) == 0)
        break;
    /* tm_mon comes out as 12 if the month is corrupt, which is desired,
     * since the mktime will then fail */
    gmt.tm_mon = n;
    gmt.tm_isdst = -1;
    return mktime(&gmt) + gmt_to_local_win32();
}

/* Takes a string containing a RFC1036-style date and returns the time_t */
time_t rfc1036_parse(const TCHAR *date) 
{
    struct tm gmt = {0};
    int n;
    TCHAR wkday[11], mon[4];
    /* RFC850/1036 style dates: Sunday, 06-Nov-94 08:49:37 GMT */
    n = _stscanf(date, RFC1036_FORMAT,
        wkday, &gmt.tm_mday, mon, &gmt.tm_year,
        &gmt.tm_hour, &gmt.tm_min, &gmt.tm_sec);
    if (n != 7) {
    return (time_t)-1;
    }

    /* portable to check n here? */
    for (n=0; n<12; n++)
    if (_tcscmp(mon, short_months[n]) == 0)
        break;
    /* tm_mon comes out as 12 if the month is corrupt, which is desired,
     * since the mktime will then fail */

    /* Defeat Y2K bug. */
    if (gmt.tm_year < 50)
    gmt.tm_year += 100;

    gmt.tm_mon = n;
    gmt.tm_isdst = -1;
    return mktime(&gmt) + gmt_to_local_win32();
}


/* (as)ctime dates are like:
 *    Wed Jun 30 21:49:08 1993
 */
time_t asctime_parse(const TCHAR *date) 
{
    struct tm gmt = {0};
    int n;
    TCHAR wkday[4], mon[4];
    n = _stscanf(date, ASCTIME_FORMAT,
        wkday, mon, &gmt.tm_mday, 
        &gmt.tm_hour, &gmt.tm_min, &gmt.tm_sec,
        &gmt.tm_year);
    /* portable to check n here? */
    for (n=0; n<12; n++)
    if (_tcscmp(mon, short_months[n]) == 0)
        break;
    /* tm_mon comes out as 12 if the month is corrupt, which is desired,
     * since the mktime will then fail */
    gmt.tm_mon = n;
    gmt.tm_isdst = -1;
    return mktime(&gmt) + gmt_to_local_win32();
}

/* HTTP-date parser */
time_t httpdate_parse(const TCHAR *date)
{
    time_t tmp;
    tmp = rfc1123_parse(date);
    if (tmp == -1) {
        tmp = rfc1036_parse(date);
    if (tmp == -1)
        tmp = asctime_parse(date);
    }
    return tmp;
}