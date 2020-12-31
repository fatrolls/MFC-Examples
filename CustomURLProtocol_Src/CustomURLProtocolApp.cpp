#include <stdafx.h>
#include "CustomURLProtocolApp.h"
#include <Strsafe.h>


CustomURLProtocol::CustomURLProtocol()
{
	m_wszProtocolName =	L"CustomProtocol";
	m_wszCompanyName	=	L"CompanyName";
	m_wszAppPath		=	L"Notepad.exe";
}
	
CustomURLProtocol::CustomURLProtocol(std::wstring pwProtocolName, std::wstring pwCompanyName, std::wstring pwAppPath)
{
	m_wszProtocolName =	pwProtocolName;
	m_wszCompanyName	=	pwCompanyName;
	m_wszAppPath		=	pwAppPath;
}

void CustomURLProtocol::FormatErrorMsg()
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					m_dwErrorCode,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR) &lpMsgBuf,
					0, NULL );

	// Display the error message and exit the process
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
	(lstrlen((LPCTSTR)lpMsgBuf)+ 40) * sizeof(TCHAR)); 

	StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("CustomURLProtocol::Failed with error %d: %s"), 
        m_dwErrorCode, lpMsgBuf); 

	m_wszErrorMsg.append((LPCTSTR)lpDisplayBuf);
	OutputDebugStringW((LPCTSTR)lpDisplayBuf);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

int CustomURLProtocol::CreateCustomProtocol()
{
	WCHAR szValue[MAX_PATH] = {0};
	HKEY hKey				= NULL;
	HKEY hKeyDefaultIcon	= NULL;
	HKEY hKeyCommand		= NULL;
	bool IsRegAlreadyPresent=	false;

	do
	{
		if((m_dwErrorCode = RegOpenKeyExW(HKEY_CLASSES_ROOT, m_wszProtocolName.c_str(), 0L,  KEY_READ, &hKey)) != ERROR_SUCCESS)
		{
			if((m_dwErrorCode = RegCreateKeyExW( HKEY_CLASSES_ROOT,
						m_wszProtocolName.c_str(),
						0,
						NULL,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,
						NULL,
						&hKey,
						NULL)) == ERROR_SUCCESS)
			{
				swprintf_s(szValue,MAX_PATH,URL_PROTOCOL_STRING,m_wszProtocolName.c_str());
				if((m_dwErrorCode = RegSetValueExW( hKey,L"",0,REG_SZ,(BYTE *)&szValue,wcslen(szValue)*2+2)) != ERROR_SUCCESS)
					break;

				if((m_dwErrorCode = RegSetValueExW( hKey,URL_PROTOCOL,0,REG_SZ,(BYTE *)"",sizeof(REG_SZ))) != ERROR_SUCCESS)
					break;

				if( (m_dwErrorCode = RegCreateKeyW(hKey,URL_PROTOCOL_DEFAULTICON,&hKeyDefaultIcon)) == ERROR_SUCCESS )
				{
					swprintf_s(szValue,MAX_PATH,L"%s",m_wszAppPath.c_str());
					if((m_dwErrorCode = RegSetValueExW( hKeyDefaultIcon,L"",0,REG_SZ,(BYTE *)&szValue,wcslen(szValue)*2 + 2)) != ERROR_SUCCESS)
						break;

					if( (m_dwErrorCode = RegCreateKeyW(hKey,URL_PROTOCOL_COMMAND,&hKeyCommand)) == ERROR_SUCCESS )
					{
						swprintf_s(szValue,MAX_PATH,L"\"%s\" \"%%1\"",m_wszAppPath.c_str());
						m_dwErrorCode = RegSetValueExW( hKeyCommand,L"",0,REG_SZ,(BYTE *)&szValue,wcslen(szValue)*2+2);
					}
				}
			}
		}
		else
		{
			m_dwErrorCode	=	-1;
			IsRegAlreadyPresent = true;
			swprintf_s(szValue,MAX_PATH,L"%s Key is already present.",m_wszProtocolName.c_str());
			m_wszErrorMsg=szValue;
		}
	}
	while(FALSE);
	
	if(m_dwErrorCode != ERROR_SUCCESS)
		FormatErrorMsg();

	if(hKeyCommand)
	{
		::RegCloseKey(hKeyCommand);
		hKeyCommand = NULL;
	}
	if(hKeyDefaultIcon)
	{
		::RegCloseKey(hKeyDefaultIcon);
		hKeyDefaultIcon = NULL;
	}
	if(hKey)
	{
		::RegCloseKey(hKey);
		hKey = NULL;
	}

	return m_dwErrorCode;
}



int CustomURLProtocol::DeleteCustomProtocol()
{
	HKEY hKey = NULL;

	if((m_dwErrorCode = RegOpenKeyExW(HKEY_CLASSES_ROOT, m_wszProtocolName.c_str(), 0L,  KEY_ALL_ACCESS, &hKey)) == ERROR_SUCCESS)
	{
		if( m_dwErrorCode = ::RegDeleteKey(hKey,URL_PROTOCOL_DEFAULTICON) == ERROR_SUCCESS)	
			if( m_dwErrorCode = ::RegDeleteKey(hKey,URL_PROTOCOL_COMMAND) == ERROR_SUCCESS)	
				if( m_dwErrorCode = ::RegDeleteKey(hKey,URL_PROTOCOL_OPEN) == ERROR_SUCCESS)	
					if( m_dwErrorCode = ::RegDeleteKey(hKey,URL_PROTOCOL_SHELL) == ERROR_SUCCESS)
						if( m_dwErrorCode = ::RegCloseKey(hKey) == ERROR_SUCCESS)
							m_dwErrorCode = ::RegDeleteKey(HKEY_CLASSES_ROOT,m_wszProtocolName.c_str());						
	}
	if(m_dwErrorCode != ERROR_SUCCESS)
		FormatErrorMsg();
	return m_dwErrorCode;
}



