// Service.cpp: implementation of the CService class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h"
#include "Service.h"
#include "StartServiceDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CService::CService()
{
   m_pUtility = new CStartServiceDlg;
   m_bServiceInstalled = FALSE;
   m_bServiceStarted = FALSE;
   m_hControlDevice = INVALID_HANDLE_VALUE;
}

CService::~CService()
{
   delete m_pUtility;
   if (m_hControlDevice != INVALID_HANDLE_VALUE)
	   CloseHandle(m_hControlDevice);
}

BOOL CService::Install(char* pPath, char* pName, BOOL bPrompt)
{
   m_bServiceInstalled = m_pUtility->Install(pPath, pName, bPrompt);
   return m_bServiceInstalled;
}

BOOL CService::UnInstall(char* pName, BOOL bPrompt)
{
	m_bServiceInstalled = !m_pUtility->UnInstall(pName, bPrompt);
	if (!m_bServiceInstalled)
		m_bServiceStarted = FALSE;
	return !m_bServiceInstalled;
}

BOOL CService::RunService(char* pName, int nArg, char** pArg, BOOL bPrompt) 
{
	m_bServiceStarted = m_pUtility->RunService(pName, nArg, pArg, bPrompt);
	if (m_bServiceStarted)
		m_bServiceInstalled = TRUE;
	return m_bServiceStarted;
}

BOOL CService::KillService(char* pName, BOOL bPrompt)
{
    m_bServiceStarted = !m_pUtility->KillService(pName, bPrompt);
	if (!m_bServiceStarted)
	{
		if (m_hControlDevice != INVALID_HANDLE_VALUE)
			CloseHandle(m_hControlDevice);
		m_hControlDevice = INVALID_HANDLE_VALUE;
		m_aAdapterName.clear();
	}
	return !m_bServiceStarted;
}

BOOL CService::OpenControlDevice(char* pControlDeviceLinkName)
{
	if (!m_bServiceInstalled || !m_bServiceStarted)
		return FALSE;
    char szName[MAX_PATH] = { 0 };
	sprintf(szName, "\\\\.\\%s", pControlDeviceLinkName);
	m_hControlDevice = CreateFile(_T(szName), GENERIC_READ | GENERIC_WRITE, 0,
		                          NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return m_hControlDevice != INVALID_HANDLE_VALUE;
}

void CService::CloseControlDevice()
{
    if(m_hControlDevice != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(m_hControlDevice);
		m_hControlDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CService::EnumAdapters(UINT nIoEnumAdapterCode)
{
	m_aAdapterName.clear();
	if (!m_bServiceInstalled || !m_bServiceStarted)
		return FALSE;
	if (m_hControlDevice == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD dwBufferLength = sizeof(m_buffer);
	BOOL bRet = ::DeviceIoControl(m_hControlDevice, nIoEnumAdapterCode, 
			NULL, 0, m_buffer, dwBufferLength, &dwBufferLength, NULL);
	if(!bRet)
		return FALSE;
	
	// 保存适配器数量
	int nAdapters = (ULONG)((ULONG*)m_buffer)[0];
	// 下面从m_buffer中获取适配器名称和符号连接名称
	// 指向设备名称
	WCHAR *pwsz = (WCHAR *)((ULONG *)m_buffer + 1);
	int i = 0;
	AdapterName name;
	name.wszAdapterName = pwsz;
	while(*(pwsz++) != NULL)
	{
		while(*(pwsz++) != NULL);		
		name.wszAdapterLinkName = pwsz + 12; // pwsz 指向"\DosDevices\Packet_{}", 加12是为了去掉"\DosDevices\"
		m_aAdapterName.insert(m_aAdapterName.end(), name);
		while(*(pwsz++) != NULL);
		if(++i >= MAX_ADAPTERS)
			break;		
		name.wszAdapterName = pwsz;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// CAdapter Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdapter::CAdapter()
{
   m_hAdapter = INVALID_HANDLE_VALUE;
   m_nQueryOidCode = 0;
   m_nSetOidCode = 0;
   m_nResetOidCode = 0;
   m_nGenFilterCode = 0;
}

CAdapter::~CAdapter()
{
    CloseAdapter();
}

void CAdapter::SetOidCode(UINT aIOOidCodes[4])
{
   m_nQueryOidCode = aIOOidCodes[0];
   m_nSetOidCode = aIOOidCodes[1];
   m_nResetOidCode = aIOOidCodes[2];
   m_nGenFilterCode = aIOOidCodes[3];
}

void CAdapter::CloseAdapter()
{
	if(m_hAdapter != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(m_hAdapter);
		m_hAdapter = INVALID_HANDLE_VALUE;
	}
}

BOOL CAdapter::OpenAdapter(LPCWSTR pwszSymbolicLink, BOOL bAsyn)
{
	char szFile[1024];
	wsprintf(szFile, _T("\\\\.\\%ws"), pwszSymbolicLink);
	// 打开到驱动程序所控制设备的句柄
	m_hAdapter = ::CreateFile(szFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
		bAsyn ? FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED : FILE_ATTRIBUTE_NORMAL, NULL);
	int n = ::GetLastError();
	return m_hAdapter != INVALID_HANDLE_VALUE;
}

BOOL CAdapter::ResetAdapter()
{
	if(m_hAdapter == INVALID_HANDLE_VALUE)
		return FALSE;
	if (m_nResetOidCode == 0)
		return FALSE;
	DWORD dw;
	return DeviceIoControl(m_hAdapter, m_nResetOidCode, NULL, 0, NULL, 0, &dw, NULL);
}

int CAdapter::RecieveData(PVOID pBuffer, int nLen, LPOVERLAPPED lpOverlapped)
{
	if(m_hAdapter == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD dwRead;
	if(::ReadFile(m_hAdapter, pBuffer, nLen, &dwRead, lpOverlapped))
		return dwRead;
	else
		return -1;
}

int CAdapter::SendData(PVOID pBuffer, int nLen, LPOVERLAPPED lpOverlapped)
{
	if(m_hAdapter == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD dwWrite;
	if(::WriteFile(m_hAdapter, pBuffer, nLen, &dwWrite, lpOverlapped))
		return dwWrite;
	else
		return -1;
}

BOOL CAdapter::ProtoRequest(PPROTOCOL_OID_DATA pOidData, BOOL bQuery)
{
	if(m_hAdapter == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD dw;
	UINT iOCode = 0;

	if (bQuery)
        iOCode = m_nQueryOidCode;
	else
		iOCode = m_nSetOidCode;

	if (iOCode == 0)
		return FALSE;

	return  DeviceIoControl(m_hAdapter, iOCode, pOidData, sizeof(PROTOCOL_OID_DATA) -1 + pOidData->Length,
		                    pOidData, sizeof(PROTOCOL_OID_DATA) -1 + pOidData->Length, &dw, NULL);
}

BOOL CAdapter::SetFilter(ULONG nFilters)
{
	if(m_hAdapter == INVALID_HANDLE_VALUE)
		return FALSE;
	if (m_nGenFilterCode == 0)
		return false;
	PPROTOCOL_OID_DATA pOidData = (PPROTOCOL_OID_DATA)::GlobalAlloc(GPTR, (sizeof(PROTOCOL_OID_DATA) + sizeof(ULONG) - 1));
	pOidData->Oid = m_nGenFilterCode; 
	pOidData->Length = sizeof(ULONG);
	*((PULONG)pOidData->Data) = nFilters;
	BOOL bRet = ProtoRequest(pOidData, FALSE);
	::GlobalFree(pOidData);
	return bRet;
}

//实例
/*
int main()
{
	// 启动服务
	if(!ProtoStartService())
	{
		printf(" ProtoStartService() failed %d \n", ::GetLastError());
		return -1;
	}
	// 打开控制设备对象
	HANDLE hControlDevice = ProtoOpenControlDevice();
	if(hControlDevice == INVALID_HANDLE_VALUE)
	{
		printf(" ProtoOpenControlDevice() failed() %d \n", ::GetLastError());
		ProtoStopService();
		return -1;
	}
	// 枚举绑定的下层适配器
	CPROTOAdapters adapters;
	if(!adapters.EnumAdapters(hControlDevice))
	{
		printf(" Enume adapter failed \n"); 
		ProtoStopService();
		return -1;
	}
	
	// 创建一个原始封包（至少应为16个字节长）
	BYTE bytes[] =  {0xff,0xff,0xff,0xff,0xff,0xff,  // 目的MAC地址
					 0x00,0x02,0x3e,0x4c,0x49,0xaa,  // 源MAC地址
					 0x08,0x00,					     // 协议
					 0x01,0x02,0x03,0x04,0x05,0x06}; // 通常数据
	// 打印出每个下层适配器的信息，发送数据
	for(int i=0; i<adapters.m_nAdapters; i++)
	{
		char sz[256];
		wsprintf(sz, "\n\n Adapter:	%ws \n Symbolic Link: %ws \n\n ", 
								adapters.m_pwszAdapterName[i], adapters.m_pwszSymbolicLink[i]);
		printf(sz);

		CAdapter adapter;
		adapter.OpenAdapter(adapters.m_pwszSymbolicLink[i]);
		// 在此适配器上发送原始数据
		int nSend = adapter.SendData(bytes, sizeof(bytes));
		if(nSend > 0)
			printf(" Packet sent: %d bytes \n", nSend);
		else
			printf(" Packet sent failed \n");
	}

	::CloseHandle(hControlDevice);
	ProtoStopService();
	return 0;
}
*/
