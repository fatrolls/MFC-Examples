#include "winreg.h"

class CRegKey
{
// Construction
public:
	CRegKey();
	virtual ~CRegKey();

// Operations
public:
  LONG Open (HKEY hKeyRoot, LPCTSTR pszPath);
  LONG Open (HKEY hKeyRoot,  UINT nID);

  void Close();

	LONG Write (LPCTSTR pszKey, DWORD dwVal);
	LONG Write (LPCTSTR pszKey, LPCTSTR pszVal);
	LONG Write (LPCTSTR pszKey, const BYTE* pData, DWORD dwLength);

	LONG Read (LPCTSTR pszKey, DWORD& dwVal);
	LONG Read (LPCTSTR pszKey, CString& sVal);
	LONG Read (LPCTSTR pszKey, BYTE* pData, DWORD& dwLength);

  LONG GetEnumKeys(HKEY hKeyRoot, LPCTSTR pszPath, CStringArray &strArray);
  LONG GetEnumKeys(HKEY hKeyRoot, UINT nResourceID, CStringArray &strArray);

  LONG GetEnumValues(HKEY hKeyRoot, LPCTSTR pszPath, CStringArray &strArray);
  LONG GetEnumValues(HKEY hKeyRoot, UINT nResourceID, CStringArray &strArray);

protected:
	HKEY 	m_hKey;
	CString m_sPath;
};
