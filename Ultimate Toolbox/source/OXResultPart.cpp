// ==========================================================================
//				Class Implementation : COXResultPart
// ==========================================================================

// Source file : OXResultPart.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXResultPart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(COXResultPart, CObject, 1 | VERSIONABLE_SCHEMA)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
static TCHAR szUnknownError[] = _T("*** Unknown Error ***");

// --- Use the user default language for message retrieval
DWORD COXResultPart::m_dwLangID = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT); 

// Data members -------------------------------------------------------------
// protected:
	// COleDateTime m_creationTime;
	// --- The timestamp that was made when this return items was created

	// HRESULT m_resultCode;
	// --- The actual result code (actually a LONG)

	// CString m_sResultMessage;
	// --- A message specifying the result

	// DWORD m_dwExtra;
	// --- An extra data member to store user data


// private:
	
// Member functions ---------------------------------------------------------
// public:

COXResultPart::COXResultPart()
	{
	Initialize();
	ASSERT_VALID(this);
	}

COXResultPart::COXResultPart(HRESULT resultCode, ...)
	{
	va_list args;

	va_start(args, resultCode);
	InitializeEx(resultCode, &args);
	va_end(args);

	ASSERT_VALID(this);
	}

COXResultPart::COXResultPart(LPCTSTR pszModuleName, HRESULT resultCode, ...)
	{
	ASSERT(pszModuleName == NULL || AfxIsValidString(pszModuleName));
	va_list args;

	va_start(args, resultCode);
	InitializeEx(pszModuleName, resultCode, &args);
	va_end(args);

	ASSERT_VALID(this);
	}

BOOL COXResultPart::Initialize()
	{
	// ... Object does not have to be valid before this call
	m_creationTime = COleDateTime::GetCurrentTime();
	m_resultCode = 0;
	m_sResultMessage.Empty();
	m_dwExtra = 0;

	ASSERT_VALID(this);
	return TRUE;
	}

BOOL COXResultPart::Initialize(HRESULT resultCode, ...)
	{
	// ... Object does not have to be valid before this call
	va_list args;

	va_start(args, resultCode);
	BOOL bSuccess = InitializeEx(resultCode, &args);
	va_end(args);

	ASSERT_VALID(this);
	return bSuccess;
	}

BOOL COXResultPart::Initialize(LPCTSTR pszModuleName, HRESULT resultCode, ...)
	{
	ASSERT(pszModuleName == NULL || AfxIsValidString(pszModuleName));
	// ... Object does not have to be valid before this call
	va_list args;

	va_start(args, resultCode);
	BOOL bSuccess = InitializeEx(pszModuleName, resultCode, &args);
	va_end(args);

	ASSERT_VALID(this);
	return bSuccess;
	}

BOOL COXResultPart::InitializeSpecial(LPCTSTR pszModuleName, DWORD dwResultCode, ...)
	{
	ASSERT(pszModuleName == NULL || AfxIsValidString(pszModuleName));
	// ... Object does not have to be valid before this call
	va_list args;

	va_start(args, dwResultCode);
	BOOL bSuccess = InitializeExSpecial(pszModuleName, dwResultCode, &args);
	va_end(args);

	ASSERT_VALID(this);
	return bSuccess;
	}

COXResultPart::COXResultPart(const COXResultPart& resultItem)
	:
	m_creationTime(		resultItem.m_creationTime),
	m_resultCode(		resultItem.m_resultCode),
	m_sResultMessage(	resultItem.m_sResultMessage),	
	m_dwExtra(			resultItem.m_dwExtra)
	{
	ASSERT_VALID(&resultItem);
	ASSERT_VALID(this);
	}

HRESULT COXResultPart::GetResultCode() const
	{
	ASSERT_VALID(this);
	return m_resultCode;
	}

void COXResultPart::SetResultCode(HRESULT resultCode)
	{
	ASSERT_VALID(this);
	m_resultCode = resultCode;
	ASSERT_VALID(this);
	}

CString COXResultPart::GetResultMessage() const
	{
	ASSERT_VALID(this);
	return m_sResultMessage;
	}

void COXResultPart::SetResultMessage(CString sResultMessage)
	{
	ASSERT_VALID(this);
	m_sResultMessage = sResultMessage;
	ASSERT_VALID(this);
	}

void COXResultPart::AppendMessage(CString sMessage)
	{
	ASSERT_VALID(this);
	m_sResultMessage += sMessage;
	ASSERT_VALID(this);
	}

CString COXResultPart::BuildExtendedMessage() const
	{
	CString sExtendedMessage;
	CString sMsg;

	sMsg.Format(_T("Creation time : %s\n"), m_creationTime.Format());
	sExtendedMessage += sMsg;

	sMsg.Format(_T("Code : 0x%8.8X (%1.1X.%1.1X.%1.1X.%1.1X.%1.1X.%3.3X.%4.4X)\n"), 
		m_resultCode,
		HRESULT_SEVERITY(m_resultCode), // S - Severity - indicates success/fail
		(((m_resultCode) >> 30) & 0x1), // R - reserved - NT's second severity bit
		(((m_resultCode) >> 29) & 0x1), // C - reserved - NT's C field
		(((m_resultCode) >> 28) & 0x1), // N - reserved - indicate a mapped NT status value
		(((m_resultCode) >> 27) & 0x1), // r - reserved - message ids for display strings.
		HRESULT_FACILITY(m_resultCode), // Facility - is the facility code
		HRESULT_CODE(m_resultCode)); 	// Code - is the facility's status code
	sExtendedMessage += sMsg;

	sMsg.Format(_T("Message : %s\n"), m_sResultMessage);
	sExtendedMessage += sMsg;

	// Show extra data only when not 0
	if (m_dwExtra != 0)
		{
		sMsg.Format(_T("Extra data : %u = 0x%8.8X\n"), m_dwExtra, m_dwExtra);
		sExtendedMessage += sMsg;
		}

	return sExtendedMessage;
	}

COleDateTime COXResultPart::GetTimeStamp() const
	{
	return m_creationTime;
	}

void COXResultPart::SetTimeStamp(COleDateTime creationTime) 
	{
	ASSERT(creationTime.GetStatus() == COleDateTime::valid);
	ASSERT_VALID(this);
	m_creationTime = creationTime;
	ASSERT_VALID(this);
	}

DWORD COXResultPart::GetExtraData() const
	{
	ASSERT_VALID(this);
	return m_dwExtra;
	}

void COXResultPart::SetExtraData(DWORD dwExtra)
	{
	ASSERT_VALID(this);
	m_dwExtra = dwExtra;
	ASSERT_VALID(this);
	}

COXResultPart& COXResultPart::operator=(const COXResultPart& resultItem)
	{
	if(this==&resultItem)
		return *this;
		
	ASSERT_VALID(&resultItem);
	m_creationTime = 	resultItem.m_creationTime;
	m_resultCode = 		resultItem.m_resultCode;
	m_sResultMessage = 	resultItem.m_sResultMessage;
	m_dwExtra =			resultItem.m_dwExtra;
	ASSERT_VALID(this);
	return *this;
	}

BOOL COXResultPart::Succeeded() const
	{
	ASSERT_VALID(this);
	return SUCCEEDED(m_resultCode);
	}

BOOL COXResultPart::Failed() const
	{
	ASSERT_VALID(this);
	return FAILED(m_resultCode);
	}

WORD COXResultPart::GetCode() const
	{
	ASSERT_VALID(this);
	return (WORD)HRESULT_CODE(m_resultCode);
	}

WORD COXResultPart::GetFacility() const
	{
	ASSERT_VALID(this);
	return (WORD)HRESULT_FACILITY(m_resultCode);
	}

WORD COXResultPart::GetSeverity() const
	{
	ASSERT_VALID(this);
	return (WORD)HRESULT_SEVERITY(m_resultCode);
	}

WORD COXResultPart::GetSeverityEx() const
	{
	ASSERT_VALID(this);
	return (WORD)((m_resultCode >> 30) & 0x3);
	}

void COXResultPart::Serialize(CArchive& ar)
	{
	ASSERT_VALID(this);

	// Call base class implementation first
	CObject::Serialize(ar);

	// Then serailze members
	if (ar.IsLoading())
		{
		ar >> m_creationTime;
		ar >> m_resultCode;
		ar >> m_sResultMessage;
		ar >> m_dwExtra;
		}
	else
		{
		ar << m_creationTime;
		ar << m_resultCode;
		ar << m_sResultMessage;
		ar << m_dwExtra;
		}

	ASSERT_VALID(this);
	}

#ifdef _DEBUG
void COXResultPart::AssertValid() const
	{
	CObject::AssertValid();
	ASSERT(m_creationTime.GetStatus() != COleDateTime::invalid);
	}

void COXResultPart::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	dc << "\nm_creationTime : " << m_creationTime;
	dc << "\nm_resultCode : " << m_resultCode;
	dc << "\nm_sResultMessage : " << m_sResultMessage;
	dc << "\nm_dwExtra : " << m_dwExtra;
	dc << "\n";
	}
#endif //_DEBUG

COXResultPart::~COXResultPart()
	{
	}

// protected:
BOOL COXResultPart::InitializeEx(HRESULT resultCode, va_list* pArgs)
	// --- In  : resultCode : Result code to use
	//           pArgs : Optional parameters used to build the message
	// --- Out : 
	// --- Returns : Whether the message could be retrieved successfully
	// --- Effect : Initializes a result part object with the specified
	//              resultcode
	//				The appropriate message is retrieved from resource
	//			    and for this the optional parameters may be used
	{
	// ... Object does not have to be valid before this call
	m_creationTime = COleDateTime::GetCurrentTime();
	if (HRESULT_FACILITY(resultCode) == 0)
		// ... No facility specified, we assume WIN32 code
		m_resultCode = HRESULT_FROM_WIN32(resultCode);
	else
		m_resultCode = resultCode;
	m_sResultMessage.Empty();
	m_dwExtra = 0;
	BOOL bSuccess = RetrieveResultMessage(_T(""), m_resultCode, pArgs, m_sResultMessage);

	ASSERT_VALID(this);
	return bSuccess;
	}

BOOL COXResultPart::InitializeEx(LPCTSTR pszModuleName, HRESULT resultCode, va_list* pArgs)
	// --- In  : pszModuleName : Name of the module containing the message resource
	//			 resultCode : Result code to use
	//           pArgs : Optional parameters used to build the message
	// --- Out : 
	// --- Returns : Whether the message could be retrieved successfully
	// --- Effect : Initializes a result part object with the specified
	//              resultcode
	//				The appropriate message is retrieved from resource
	//			    and for this the optional parameters may be used
	{
	ASSERT(pszModuleName == NULL || AfxIsValidString(pszModuleName));
	// ... Object does not have to be valid before this call
	m_creationTime = COleDateTime::GetCurrentTime();
	if (HRESULT_FACILITY(resultCode) == 0)
		// ... No facility specified, we assume WIN32 code
		m_resultCode = HRESULT_FROM_WIN32(resultCode);
	else
		m_resultCode = resultCode;
	m_sResultMessage.Empty();
	m_dwExtra = 0;
	BOOL bSuccess = RetrieveResultMessage(CString(pszModuleName), m_resultCode, pArgs, m_sResultMessage);

	ASSERT_VALID(this);
	return bSuccess;
	}

BOOL COXResultPart::InitializeExSpecial(LPCTSTR pszModuleName, DWORD dwResultCode, va_list* pArgs)
	// --- In  : pszModuleName : Name of the module containing the message resource
	//			 resultCode : Result code to use
	//           pArgs : Optional parameters used to build the message
	// --- Out : 
	// --- Returns : Whether the message could be retrieved successfully
	// --- Effect : Initializes a result part object with the specified
	//              resultcode
	//				The appropriate message is retrieved from resource
	//			    and for this the optional parameters may be used
	{
	ASSERT(pszModuleName == NULL || AfxIsValidString(pszModuleName));
	// ... Object does not have to be valid before this call
	m_creationTime = COleDateTime::GetCurrentTime();
	m_resultCode = dwResultCode;
	m_sResultMessage.Empty();
	m_dwExtra = 0;
	BOOL bSuccess = RetrieveSpecialMessage(CString(pszModuleName), dwResultCode, pArgs, m_sResultMessage);

	ASSERT_VALID(this);
	return bSuccess;
	}

BOOL COXResultPart::RetrieveSpecialMessage(CString sModuleName, DWORD dwResultCode, 
	va_list* pArgs, CString& sResultMessage)
	// --- In  : pszModuleName : Name of the module containing the message resource
	//			 resultCode : Result code to use
	//           pARgs : Optional parameters used to build the message
	// --- Out : sResultMessage : The resulting message
	// --- Returns : Whether the message could be retrieved successfully
	// --- Effect : Initializes a result part with the specified result
	{
	LPTSTR pszMsgBuf = NULL;
	BOOL bUnknown = FALSE;
	DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE;
	HMODULE hModule = NULL;

	// ... Get the module handle if a module name is specified
	if (!sModuleName.IsEmpty())
		{
		hModule = ::GetModuleHandle(sModuleName);
		dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS;
		if (hModule == NULL)
			TRACE(_T("COXResultPart::RetrieveResultMessage : Module '%s' not found\n"), (LPCTSTR)sModuleName);
		}

	// ... Get the actual message 
	if (::FormatMessage(dwFlags, hModule, dwResultCode, m_dwLangID,
	      (LPTSTR)&pszMsgBuf, 0, pArgs) == 0)
		{
		TRACE2("COXResultPart::RetrieveResultMessage : No message was found for result code %i == 0x%8.8X\n",
			dwResultCode, dwResultCode);
	  	pszMsgBuf = szUnknownError;
		bUnknown = TRUE;
		}
	sResultMessage = pszMsgBuf;

	// ... Clean up
	if (!bUnknown)
		LocalFree(pszMsgBuf);

	return !bUnknown;
	}

BOOL COXResultPart::RetrieveResultMessage(CString sModuleName, HRESULT resultCode, 
	va_list* pArgs, CString& sResultMessage)
	// --- In  : pszModuleName : Name of the module containing the message resource
	//			 resultCode : Result code to use
	//           pARgs : Optional parameters used to build the message
	// --- Out : sResultMessage : The resulting message
	// --- Returns : Whether the message could be retrieved successfully
	// --- Effect : Initializes a result part with the specified result
	{
	LPTSTR pszMsgBuf = NULL;
	BOOL bUnknown = FALSE;
	DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE;
	HMODULE hModule = NULL;

	// ... Remove the facility part if FACILITY_WIN32
	if (HRESULT_FACILITY(resultCode) == FACILITY_WIN32)
		{
		resultCode = HRESULT_CODE(resultCode);
		dwFlags &= ~FORMAT_MESSAGE_FROM_HMODULE;
		}

	// ... Get the module handle if a module name is specified
	if (!sModuleName.IsEmpty())
		{
		hModule = ::GetModuleHandle(sModuleName);
		dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE;
		if (hModule == NULL)
			TRACE(_T("COXResultPart::RetrieveResultMessage : Module '%s' not found\n"), (LPCTSTR)sModuleName);
		}

	// ... Get the actual message 
	if (::FormatMessage(dwFlags, hModule, resultCode, m_dwLangID,
	      (LPTSTR)&pszMsgBuf, 0, pArgs) == 0)
		{
		TRACE2("COXResultPart::RetrieveResultMessage : No message was found for result code %i == 0x%8.8X\n",
			resultCode, resultCode);
	  	pszMsgBuf = szUnknownError;
		bUnknown = TRUE;
		}
	sResultMessage = pszMsgBuf;

	// ... Clean up
	if (!bUnknown)
		LocalFree(pszMsgBuf);

	return !bUnknown;
	}

// private:

// ==========================================================================
