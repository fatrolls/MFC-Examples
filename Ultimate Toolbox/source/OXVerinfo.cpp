// ==========================================================================
// 							Class Implementation : COXVersionInfo
// ==========================================================================

// Source file : verinfo.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "OXVerinfo.h"	// class specification
#ifdef WIN32
#include <winver.h>
#else
#include <ver.h>
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXVersionInfo, CObject)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
const DWORD COXVersionInfo::m_dwFixedFileInfoSignature = 0xFEEF04BDL;
const DWORD COXVersionInfo::m_dwAmericanEnglishTranslation = 0x040904E4L;
LPCTSTR	COXVersionInfo::m_pszTranslation = _T("\\VarFileInfo\\Translation");
LPCTSTR	COXVersionInfo::m_pszFileInfo = _T("StringFileInfo");

// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXVersionInfo::COXVersionInfo()
	{
	Empty();
	}
	
BOOL COXVersionInfo::ReadInfo(LPCTSTR pszPathName)
	{
	LPBYTE pData = NULL;
	DWORD  hVersion = 0;
	DWORD  dwVersionSize = 0;
	UINT   nVersionItemSize = 0;
	void*  pVersionItemData = NULL;
	VS_FIXEDFILEINFO*	pFixedFileInfo = NULL;
	
	// Assume failure   
	Empty();

	// Note :
	//  Several functions changed parameter type from WIN16 to WIN32
	//  e.g. WIN16 : BOOL VerQueryValue(const void FAR*, LPCSTR, VOID FAR* FAR*, UINT FAR*)
	//       WIN32 : BOOL VerQueryValue(const LPVOID, LPTSTR, LPVOID*, PUINT)
	// Notice that the second parameter changed from pointer to LPCTSTR  to
	//  just pointer to char
	// The /Gf option under large model locates string literals in the code segment
	// Passing such a string as parameter in WIN16 causes a General Protection Fault
	//  which points out that the string is not really const !
	// Therefore a copy to a temporary buffer will be used in both WIN16 and WIN32
 	
	TCHAR szCopyBuffer[512 + 1];

	_tcscpy(szCopyBuffer, pszPathName);
	dwVersionSize = ::GetFileVersionInfoSize(szCopyBuffer, &hVersion);
	if (dwVersionSize == 0)
		{
		TRACE(_T("COXVersionInfo::ReadInfo : Could  not get version info\n"));
		return FALSE;
		}

	pData = new BYTE[dwVersionSize + 1];
	_tcscpy(szCopyBuffer, pszPathName);
	VERIFY(::GetFileVersionInfo(szCopyBuffer, hVersion, dwVersionSize, pData));

	// Get the fixed info first	
	::VerQueryValue(pData, _T("\\"), &pVersionItemData, &nVersionItemSize);
	if (nVersionItemSize != 0) 
		{
		// ... Must have right size
		ASSERT(nVersionItemSize == sizeof(VS_FIXEDFILEINFO));
		pFixedFileInfo = (VS_FIXEDFILEINFO*)pVersionItemData;
		// ... Must have correct header;
	    ASSERT(pFixedFileInfo->dwSignature == m_dwFixedFileInfoSignature); 
	    
	    m_dwSignature = 		pFixedFileInfo->dwSignature;
	    m_dwStrucVersion = 		pFixedFileInfo->dwStrucVersion;
	    m_dwFileVersionMS = 	pFixedFileInfo->dwFileVersionMS;
	    m_dwFileVersionLS = 	pFixedFileInfo->dwFileVersionLS;
	    m_dwProductVersionMS = 	pFixedFileInfo->dwProductVersionMS;
	    m_dwProductVersionLS = 	pFixedFileInfo->dwProductVersionLS;
	    m_dwFileFlagsMask = 	pFixedFileInfo->dwFileFlagsMask;
	    m_dwFileFlags = 		pFixedFileInfo->dwFileFlags;
	    m_dwFileOS = 			pFixedFileInfo->dwFileOS;
	    m_dwFileType = 			pFixedFileInfo->dwFileType;
	    m_dwFileSubtype = 		pFixedFileInfo->dwFileSubtype;
	    m_dwFileDateMS = 		pFixedFileInfo->dwFileDateMS;
	    m_dwFileDateLS = 		pFixedFileInfo->dwFileDateLS;
		}
	else
		TRACE(_T("COXVersionInfo::ReadInfo : Could  not get fixed version info\n"));

	// Get the language - character info
	TCHAR szLangChar[512];
	_tcscpy(szCopyBuffer, m_pszTranslation); 
	::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize);
	if(nVersionItemSize != 0)
		{
		::VerLanguageName (*(UINT*)pVersionItemData, szLangChar, 512 - 1);
		
		// ... Swap high and low word (char set and lang id)
	    m_dwLanguageCountryID = MAKELONG(HIWORD(*(DWORD*)pVersionItemData), LOWORD(*(DWORD*)pVersionItemData));
	    m_sLanguageCountry = szLangChar;
	    }
	else
		TRACE(_T("COXVersionInfo::ReadInfo : Could  not get language info, using default\n"));

	// Get the variable info
	TCHAR szCountryHex[8 + 1];
    wsprintf(szCountryHex, _T("%08.8lX"), m_dwLanguageCountryID != 0 ? m_dwLanguageCountryID : m_dwAmericanEnglishTranslation);
	CString sFront = CString(_T("\\")) + m_pszFileInfo + _T("\\") + szCountryHex + _T("\\");
	CString sSubBlock;


    sSubBlock = sFront + _T("Comments");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sComments = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("CompanyName");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sCompanyName = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("FileDescription");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sFileDescription = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("FileVersion");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sFileVersion = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("InternalName");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sInternalName = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("LegalCopyright");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sLegalCopyright = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("LegalTrademarks");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sLegalTrademarks = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("OriginalFilename");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sOriginalFilename = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("PrivateBuild");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sPrivateBuild = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("ProductName");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sProductName = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("ProductVersion");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sProductVersion = (LPCTSTR)(LPTSTR)pVersionItemData;

    sSubBlock = sFront + _T("SpecialBuild");
	_tcscpy(szCopyBuffer, sSubBlock);
    if (::VerQueryValue(pData, szCopyBuffer, &pVersionItemData, &nVersionItemSize))
    	m_sSpecialBuild = (LPCTSTR)(LPTSTR)pVersionItemData;

	m_bValid = TRUE;
	delete[] pData;
	
	// Dump(afxDump);
	
	return TRUE;
	}
	
BOOL COXVersionInfo::ContainsValidInfo()
	{
	return m_bValid;
	}
	
CString COXVersionInfo::GetOSName()
	{
	if (!ContainsValidInfo())
		{
		TRACE(_T("COXVersionInfo::GetOSName() : Object does not contain valid info, returning empty string\n"));
		return _T("");
		}

	CString sResult;
    DWORD dwFileOS = m_dwFileOS;

	// Try all the possible flags and remove them it when a match is found
	// The order in which the possible flags are checked is important, because 
	// they binairy overlap (see winver.h or ver.h)

	// GUI Environment
	if ((dwFileOS & VOS__PM32) == VOS__PM32)
		{
		sResult += _T("- 32-bit PM");
		dwFileOS &= ~VOS__PM32;
		}
	if ((dwFileOS & VOS__WINDOWS16) == VOS__WINDOWS16)
		{
		sResult += _T("- 16-bit Windows");
		dwFileOS &= ~VOS__WINDOWS16;
		}
	if ((dwFileOS & VOS__PM16) == VOS__PM16)
		{
		sResult += _T("- 16-bit PM");
		dwFileOS &= ~VOS__PM16;
		}
	if ((dwFileOS & VOS__WINDOWS32) == VOS__WINDOWS32)
		{
		sResult += _T("- Win32");
		dwFileOS &= ~VOS__WINDOWS32;
		}

	// Basic OS
	if ((dwFileOS & VOS_OS232) == VOS_OS232)
		{
		sResult += _T("- 32-bit OS/2");
		dwFileOS &= ~VOS_OS232;
		}
	if ((dwFileOS & VOS_DOS) == VOS_DOS)
		{
		sResult += _T("- MS-DOS");
		dwFileOS &= ~VOS_DOS;
		}
	if ((dwFileOS & VOS_OS216) == VOS_OS216)
		{
		sResult += _T("- 16-bit OS/2");
		dwFileOS &= ~VOS_OS216;
		}
	if ((dwFileOS & VOS_NT) == VOS_NT)
		{
		sResult += _T("- Windows NT");
		dwFileOS &= ~VOS_NT;
		}
	// If the OS still contains flags, it are flag we did not anticipate
	if (dwFileOS != 0)
		{
		sResult += _T("- Unknown");
		}
	if (!sResult.IsEmpty())
		// ... If the result is not empty, remove the leading hyphen
		sResult = sResult.Mid(2);
	else
		// ... If the result is empty, no OS was specified
		sResult = _T("None");

	return sResult;
	}

void COXVersionInfo::Empty()
	{
    m_dwSignature = 0;
    m_dwStrucVersion = 0;
    m_dwFileVersionMS = 0;
    m_dwFileVersionLS = 0;
    m_dwProductVersionMS = 0;
    m_dwProductVersionLS = 0;
    m_dwFileFlagsMask = 0;
    m_dwFileFlags = 0;
    m_dwFileOS = 0;
    m_dwFileType = 0;
    m_dwFileSubtype = 0;
    m_dwFileDateMS = 0;
    m_dwFileDateLS = 0;

    m_dwLanguageCountryID = 0;
    m_sLanguageCountry = _T("");

	m_sComments = _T("");
	m_sCompanyName = _T("");
	m_sFileDescription = _T("");
	m_sFileVersion = _T("");
	m_sInternalName = _T("");
	m_sLegalCopyright = _T("");
	m_sLegalTrademarks = _T("");
	m_sOriginalFilename = _T("");
	m_sPrivateBuild = _T("");
	m_sProductName = _T("");
	m_sProductVersion = _T("");
	m_sSpecialBuild = _T("");

	m_bValid = FALSE;
	}

COXVersionInfo::~COXVersionInfo()
	{
	}
	
// Diagnostics ---------------------------------------------------------------
#ifdef _DEBUG
void COXVersionInfo::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXVersionInfo::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	
	dc << _T("\nm_dwSignature : ") << m_dwSignature;;
    dc << _T("\nm_dwStrucVersion : ") << m_dwStrucVersion;
    dc << _T("\nm_dwFileVersionMS : ") << m_dwFileVersionMS;
    dc << _T("\nm_dwFileVersionLS : ") << m_dwFileVersionLS;
    dc << _T("\nm_dwProductVersionMS : ") << m_dwProductVersionMS;
    dc << _T("\nm_dwProductVersionLS : ") << m_dwProductVersionLS;
    dc << _T("\nm_dwFileFlagsMask : ") << m_dwFileFlagsMask;
    dc << _T("\nm_dwFileFlags : ") << m_dwFileFlags;
    dc << _T("\nm_dwFileOS : ") << m_dwFileOS;
    dc << _T("\nm_dwFileType : ") << m_dwFileType;
    dc << _T("\nm_dwFileSubtype : ") << m_dwFileSubtype;
    dc << _T("\nm_dwFileDateMS : ") << m_dwFileDateMS;
    dc << _T("\nm_dwFileDateLS : ") << m_dwFileDateLS;

    dc << _T("\nm_dwLanguageCountryID : ") << m_dwLanguageCountryID;
    dc << _T("\nm_sLanguageCountry : ") << m_sLanguageCountry;

	dc << _T("\nm_sComments : ") << m_sComments;
	dc << _T("\nm_sCompanyName : ") << m_sCompanyName;
	dc << _T("\nm_sFileDescription : ") << m_sFileDescription;
	dc << _T("\nm_sFileVersion : ") << m_sFileVersion;
	dc << _T("\nm_sInternalName : ") << m_sInternalName;
	dc << _T("\nm_sLegalCopyright : ") << m_sLegalCopyright;
	dc << _T("\nm_sLegalTrademarks : ") << m_sLegalTrademarks;
	dc << _T("\nm_sOriginalFilename : ") << m_sOriginalFilename;
	dc << _T("\nm_sPrivateBuild : ") << m_sPrivateBuild;
	dc << _T("\nm_sProductName : ") << m_sProductName;
	dc << _T("\nm_sProductVersion : ") << m_sProductVersion;
	dc << _T("\nm_sSpecialBuild; : ") << m_sSpecialBuild;;
	
	dc << _T("\nm_bValid : ") << m_bValid;
	}
#endif //_DEBUG

// protected:

// private:

// Message handlers ---------------------------------------------------------

// ==========================================================================
