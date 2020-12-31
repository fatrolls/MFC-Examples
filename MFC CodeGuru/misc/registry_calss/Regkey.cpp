#include "stdafx.h"
#include "Regkey.h"

CRegKey::CRegKey()
{
	m_hKey = NULL;
}

CRegKey::~CRegKey()
{
	Close();
}

LONG CRegKey::Open (HKEY hKeyRoot, LPCTSTR pszPath)
{
	DWORD dw;
	m_sPath = pszPath;

	return RegCreateKeyEx (hKeyRoot, pszPath, 0L, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, 
		&m_hKey, &dw);
}

void CRegKey::Close()
{
	if (m_hKey)
	{
		RegCloseKey (m_hKey);
		m_hKey = NULL;
	}
}

LONG CRegKey::Write (LPCTSTR pszKey, DWORD dwVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);
	return RegSetValueEx (m_hKey, pszKey, 0L, REG_DWORD,
		(CONST BYTE*) &dwVal, sizeof(DWORD));
}

LONG CRegKey::Write (LPCTSTR pszKey, LPCTSTR pszData)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);
	ASSERT(pszData);
	ASSERT(AfxIsValidAddress(pszData, strlen(pszData), FALSE));

	return RegSetValueEx (m_hKey, pszKey, 0L, REG_SZ,
		(CONST BYTE*) pszData, strlen(pszData) + 1);
}

LONG CRegKey::Write (LPCTSTR pszKey, const BYTE* pData,
	DWORD dwLength)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);
	ASSERT(pData && dwLength > 0);
	ASSERT(AfxIsValidAddress(pData, dwLength, FALSE));

	return RegSetValueEx (m_hKey, pszKey, 0L, REG_BINARY,
		pData, dwLength);
}

LONG CRegKey::Read (LPCTSTR pszKey, DWORD& dwVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lRet = RegQueryValueEx (m_hKey, (LPSTR) pszKey, NULL, 
		&dwType, (BYTE *) &dwDest, &dwSize);

	if (lRet == ERROR_SUCCESS)
		dwVal = dwDest;

	return lRet;
}

LONG CRegKey::Read (LPCTSTR pszKey, CString& sVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	DWORD dwType;
	DWORD dwSize = 200;
	char  string[200];

	LONG lReturn = RegQueryValueEx (m_hKey, (LPSTR) pszKey, NULL,
		&dwType, (BYTE *) string, &dwSize);

	if (lReturn == ERROR_SUCCESS)
		sVal = string;

	return lReturn;
}

LONG CRegKey::Read (LPCTSTR pszKey, BYTE* pData, DWORD& dwLen)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	DWORD dwType;

	return RegQueryValueEx (m_hKey, (LPSTR) pszKey, NULL,
		&dwType, pData, &dwLen);
}

LONG CRegKey::GetEnumKeys(HKEY hKeyRoot, LPCTSTR pszPath, CStringArray &strArray)
{
  int  nIndex;
  long lRetCode;
	char szValue[MAX_PATH];

  if ((lRetCode = Open(hKeyRoot, pszPath)) != ERROR_SUCCESS)
    return lRetCode;

  strArray.RemoveAll();
  for (nIndex = 0, lRetCode = ERROR_SUCCESS; lRetCode == ERROR_SUCCESS; nIndex++)
  {
    lRetCode = RegEnumKey(m_hKey, nIndex, szValue, MAX_PATH);
    if (lRetCode == ERROR_SUCCESS)
      strArray.Add(szValue);
  }

  Close();

  return ERROR_SUCCESS;
}

LONG CRegKey::GetEnumValues(HKEY hKeyRoot, LPCTSTR pszPath, CStringArray &strArray)
{
  int   nIndex;
  long  lRetCode;
	char  szValue[MAX_PATH];
  DWORD dwValue;

  if ((lRetCode = Open(hKeyRoot, pszPath)) != ERROR_SUCCESS)
    return lRetCode;

  strArray.RemoveAll();
  for (nIndex = 0, lRetCode = ERROR_SUCCESS; lRetCode == ERROR_SUCCESS; nIndex++)
  {
		szValue[0] = '\0';
		dwValue    = MAX_PATH;
    lRetCode   = RegEnumValue(m_hKey, nIndex, szValue, &dwValue, NULL, NULL, NULL, NULL);
    if (lRetCode == ERROR_SUCCESS)
      strArray.Add(szValue);
  }

  Close();

  return ERROR_SUCCESS;
}