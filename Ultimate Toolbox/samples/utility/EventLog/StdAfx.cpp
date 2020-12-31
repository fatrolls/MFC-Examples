// stdafx.cpp : source file that includes just the standard includes
//	EventLog.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

static TCHAR szUnknownError[] = _T("*** Unknown Error ***");
CString GetErrorMessage(HRESULT nErrorCode, ...)
{
	va_list args;
	LPTSTR pszMsgBuf = NULL;
	BOOL bUnknown = FALSE;
	CString sResult;

	// ... Get the variable number of parameters
	va_start(args, nErrorCode);

	// ... Get the actual message from this DLL
	if (::FormatMessage(
	  FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	  ::GetModuleHandle(AfxGetAppName()),
	  nErrorCode,
	  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
	  (LPTSTR)&pszMsgBuf,
	  0,
	  &args) == 0)
	{
		TRACE2("No message was found for error code %i == 0x%8.8X\n",
			nErrorCode, nErrorCode);
	  	pszMsgBuf = szUnknownError;
		bUnknown = TRUE;
	}

	// Fill out parameter
	sResult = pszMsgBuf;

	// ... Clean up
	if (!bUnknown)
		LocalFree(pszMsgBuf);
	va_end(args);

	return sResult;
}