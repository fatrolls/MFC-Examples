/*
Module : MAILSLOT.CPP
Purpose: Defines the implementation for a wrapper class for Win32 Mailslots
Created: PJN / MSLOT/1 / 18-06-1997
History: None

  Copyright (c) 1997 by PJ Naughter.  
  All rights reserved.
  
*/


/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "mailslot.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



////////////////////////////////// Implementation /////////////////////////////

CServerMailslot::CServerMailslot()
{
	m_hMailslot = INVALID_HANDLE_VALUE;
}

CServerMailslot::~CServerMailslot()
{
	if (IsOpen())
		Close();
}

BOOL CServerMailslot::Close()
{
	ASSERT(IsOpen());
	BOOL bSuccess = CloseHandle(m_hMailslot);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::Close() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

BOOL CServerMailslot::IsOpen() const
{
	return (m_hMailslot != INVALID_HANDLE_VALUE);
}

BOOL CServerMailslot::Open(LPCTSTR lpName, 
                           DWORD nMaxMessageSize, 
                           DWORD lReadTimeout, 
                           LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	ASSERT(!IsOpen());
	
	//the class encapsulates creating the mailslot name, all that is required is
	//a simple name for the mailslot e.g. lpName = PJSLOT will create the mailslot
	//name \\.\mailslot\PJSLOT
	TCHAR pszMailslotName[_MAX_PATH];
	_tcscpy(pszMailslotName, _T("\\\\.\\mailslot\\"));
	_tcscat(pszMailslotName, lpName);
	
	m_hMailslot = CreateMailslot(pszMailslotName, nMaxMessageSize, lReadTimeout, lpSecurityAttributes);
	
	if (m_hMailslot == INVALID_HANDLE_VALUE)
		TRACE1("CServerMailslot::Open() failed, GetLastError returned %d\n", GetLastError());
	
	return (m_hMailslot != INVALID_HANDLE_VALUE);
}

BOOL CServerMailslot::MessageWaiting()
{
	ASSERT(IsOpen());
	DWORD dwCount = 0;
	BOOL bSuccess = GetMailslotInfo(m_hMailslot, NULL, NULL, &dwCount, NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::MessageWaiting() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess && (dwCount != 0);
}

DWORD CServerMailslot::MessageCount()
{
	ASSERT(IsOpen());
	DWORD dwCount = 0;
	BOOL bSuccess = GetMailslotInfo(m_hMailslot, NULL, NULL, &dwCount, NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::MessageCount() failed, GetLastError returned %d\n", GetLastError());
	
	if (bSuccess)
		return dwCount;
	else
		return 0;
}

DWORD CServerMailslot::SizeOfWaitingMessage()
{
	ASSERT(IsOpen());
	DWORD dwSize = 0;
	BOOL bSuccess = GetMailslotInfo(m_hMailslot, NULL, &dwSize, NULL, NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::SizeOfWaitingMessage() failed, GetLastError returned %d\n", GetLastError());
	
	if (bSuccess)
		return dwSize;
	else
		return 0;
}

DWORD CServerMailslot::MaximumMessageSize()
{
	ASSERT(IsOpen());
	DWORD dwMaxSize = 0;
	BOOL bSuccess = GetMailslotInfo(m_hMailslot, &dwMaxSize, NULL, NULL, NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::MaxmimumMessageSize() failed, GetLastError returned %d\n", GetLastError());
	
	if (bSuccess)
		return dwMaxSize;
	else
		return 0;
}

BOOL CServerMailslot::SetReadTimeout(DWORD lReadTimeout)
{
	ASSERT(IsOpen());
	BOOL bSuccess = SetMailslotInfo(m_hMailslot, lReadTimeout);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::SetReadTimeout() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

BOOL CServerMailslot::Read(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead)
{
	ASSERT(IsOpen());
	BOOL bSuccess = ReadFile(m_hMailslot, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, (LPOVERLAPPED) NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::Read() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

BOOL CServerMailslot::GetCreationTime(LPFILETIME lpCreationTime)
{
	ASSERT(IsOpen());
	BOOL bSuccess = GetFileTime(m_hMailslot, lpCreationTime, NULL, NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::GetCreationTime() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

BOOL CServerMailslot::GetLastAccessTime(LPFILETIME lpLastAccessTime)
{
	ASSERT(IsOpen());
	BOOL bSuccess = GetFileTime(m_hMailslot, NULL, lpLastAccessTime, NULL);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::GetLastAccessTime() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

BOOL CServerMailslot::GetLastWriteTime(LPFILETIME lpLastWriteTime)
{
	ASSERT(IsOpen());
	BOOL bSuccess = GetFileTime(m_hMailslot, NULL, NULL, lpLastWriteTime);
	
	if (!bSuccess)
		TRACE1("CServerMailslot::GetLastWriteTime() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

#ifdef _DEBUG
void CServerMailslot::AssertValid() const
{
	CObject::AssertValid();
	ASSERT(IsOpen());
}
#endif

#ifdef _DEBUG
void CServerMailslot::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	
	CString sText;
	sText.Format(_T("Open=%d, m_hMailslot=%x\n"), IsOpen(), m_hMailslot);
	dc << sText;
}
#endif




CClientMailslot::CClientMailslot()
{
	m_hMailslot = INVALID_HANDLE_VALUE;
}

CClientMailslot::~CClientMailslot()
{
	if (IsOpen());
    Close();
}

BOOL CClientMailslot::Close()
{
	ASSERT(IsOpen());
	BOOL bSuccess = CloseHandle(m_hMailslot);
	
	if (!bSuccess)
		TRACE1("CClientMailslot::Close() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

BOOL CClientMailslot::IsOpen() const
{
	return (m_hMailslot != INVALID_HANDLE_VALUE);
}

BOOL CClientMailslot::Open(LPCTSTR lpComputerOrDomainName,
                           LPCTSTR lpName,
                           LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	ASSERT(!IsOpen());
	
	//the function encapsulates creating the mailslot name by breaking down the
	//creation of the mailslot name into the ComputerOrDomain and the actual mailslot itself
	//e.g. lpComputerOrDomainName = PJ, lpName = PJSLOT will create the actual mailslot
	//name of "\\PJ\mailslot\PJSLOT"
	TCHAR pszMailslotName[_MAX_PATH];
	_tcscpy(pszMailslotName, _T("\\\\"));
	_tcscat(pszMailslotName, lpComputerOrDomainName);
	_tcscat(pszMailslotName, _T("\\mailslot\\"));
	_tcscat(pszMailslotName, lpName);
	
	m_hMailslot = CreateFile(pszMailslotName, 
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		lpSecurityAttributes,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL);
	
	if (m_hMailslot == INVALID_HANDLE_VALUE)
		TRACE1("CClientMailslot::Open() failed, GetLastError returned %d\n", GetLastError());
	
	return (m_hMailslot != INVALID_HANDLE_VALUE);
}

BOOL CClientMailslot::Write(LPCVOID lpBuffer,
							DWORD nNumberOfBytesToWrite,
							LPDWORD lpNumberOfBytesWritten)
{
	ASSERT(IsOpen());
	BOOL bSuccess = WriteFile(m_hMailslot, lpBuffer, nNumberOfBytesToWrite,
		lpNumberOfBytesWritten, (LPOVERLAPPED) NULL);
	
	if (!bSuccess)
		TRACE1("CClientMailslot::Write() failed, GetLastError returned %d\n", GetLastError());
	
	return bSuccess;
}

#ifdef _DEBUG
void CClientMailslot::AssertValid() const
{
	CObject::AssertValid();
	ASSERT(IsOpen());
}
#endif

#ifdef _DEBUG
void CClientMailslot::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	
	CString sText;
	sText.Format(_T("Open=%d, m_hMailslot=%x\n"), IsOpen(), m_hMailslot);
	dc << sText;
}
#endif
