// HookDriver.cpp: implementation of the CHookDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h"
#include "HookDriver.h"
#include <winsvc.h>
#include "Helper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHookDriver::CHookDriver(LPCTSTR pszDriverPath, LPCTSTR pszLinkName)
{
	memset(m_szLinkName, 0, MAX_PATH);
	strncpy(m_szLinkName, pszLinkName, wcslen((PWCHAR)pszLinkName)*2);
	m_bStarted = FALSE;
	m_bCreateService = FALSE;
	m_hSCM = NULL;
	m_hService = NULL;
	m_hDriver = INVALID_HANDLE_VALUE;
    // 打开SCM管理器
	m_hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (m_hSCM == NULL)
	{
		AfxMessageBox("打开服务控制管理器失败", MB_OK, MB_ICONERROR);
		return;
	}
	// 创建或打开服务
	m_hService = CreateService((SC_HANDLE)m_hSCM, m_szLinkName, m_szLinkName, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,
		                       SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, pszDriverPath, NULL, 
							   0, NULL, NULL, NULL);
	if (m_hService == NULL)
	{
		int nError = GetLastError();
		if (nError == ERROR_SERVICE_EXISTS || nError == ERROR_SERVICE_MARKED_FOR_DELETE)
			m_hService = OpenService((SC_HANDLE)m_hSCM, m_szLinkName, SERVICE_ALL_ACCESS);
	}
	else
		m_bCreateService = TRUE;
}

CHookDriver::~CHookDriver()
{
	if (m_hDriver != INVALID_HANDLE_VALUE)
		CloseHandle(m_hDriver);
	StopDriver();
	if (m_bCreateService)
		DeleteService((SC_HANDLE)m_hService);
	if (m_hService)
		CloseServiceHandle((SC_HANDLE)m_hService);
	if (m_hSCM)
		CloseServiceHandle((SC_HANDLE)m_hSCM);
}

// 向设备发送控制代码
DWORD CHookDriver::IoControl(DWORD nCode, PVOID pInBuffer, DWORD nInCount, PVOID pOutBuffer, DWORD nOutCount)
{
	if (m_hDriver == INVALID_HANDLE_VALUE)
		return -1;
	DWORD nBytesRet;
	BOOL bRet = DeviceIoControl(m_hDriver, nCode, pInBuffer, nInCount, pOutBuffer, nOutCount, &nBytesRet, NULL);
	if (bRet)
		return nBytesRet;
	else
		return -1;
}

BOOL CHookDriver::OpenDevice()
{
	if (m_hDriver != INVALID_HANDLE_VALUE)
		return TRUE;
	
	char sz[MAX_PATH] = { 0 };
    wsprintf(sz, "\\\\.\\%s", m_szLinkName);
	m_hDriver = CreateFile(sz, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return m_hDriver != INVALID_HANDLE_VALUE;
}

BOOL CHookDriver::StopDriver()
{
	if (!m_bStarted)
		return TRUE;
	if (m_hService == NULL)
		return FALSE;
	SERVICE_STATUS ss;
	if (!ControlService((SC_HANDLE)m_hService, SERVICE_CONTROL_STOP, &ss))
    {
		if (GetLastError() == ERROR_SERVICE_NOT_ACTIVE)
			m_bStarted = FALSE;
	}
	else
	{
	    int nTry = 0;
		while(ss.dwCurrentState == SERVICE_STOP_PENDING && nTry ++ < 80)
		{
			Sleep(50);
			QueryServiceStatus((SC_HANDLE)m_hService, &ss);
		}
		if (ss.dwCurrentState == SERVICE_STOPPED)
			m_bStarted = FALSE;
	}
	return !m_bStarted;
}

BOOL CHookDriver::StartDriver()
{
	if (m_bStarted)
		return TRUE;
	if (m_hService == NULL)
		return FALSE;

	if (!StartService((SC_HANDLE)m_hService, 0, NULL))
	{
		DWORD dwError = GetLastError();
		CString strError;
		GetErrorMessage(dwError, strError);
		AfxMessageBox(strError);
		if (dwError == ERROR_SERVICE_ALREADY_RUNNING)
			m_bStarted = TRUE;
		else
			DeleteService((SC_HANDLE)m_hService);
	}
	else
	{
		int nTry = 0;
		SERVICE_STATUS ss;
		QueryServiceStatus((SC_HANDLE)m_hService, &ss);
		while(ss.dwCurrentState == SERVICE_START_PENDING && nTry ++ < 80)
		{
			Sleep(50);
            QueryServiceStatus((SC_HANDLE)m_hService, &ss);
		}
		if (ss.dwCurrentState == SERVICE_RUNNING)
			m_bStarted = TRUE;
	}
	return m_bStarted;
}