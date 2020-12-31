// Service.h: interface for the CService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICE_H__F2BB6498_F0D8_47FB_B18C_5F7EF7435D24__INCLUDED_)
#define AFX_SERVICE_H__F2BB6498_F0D8_47FB_B18C_5F7EF7435D24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStartServiceDlg;

#define MAX_ADAPTERS 100

class CService  
{
public:
	CService();
	virtual ~CService();

	void CloseControlDevice();
	BOOL EnumAdapters(UINT nIoEnumAdapterCode);
	BOOL OpenControlDevice(char* pControlDeviceLinkName);
    BOOL Install(char* pPath, char* pName, BOOL bPrompt = TRUE);
	BOOL UnInstall(char* pName, BOOL bPrompt = TRUE);
	BOOL RunService(char* pName, int nArg, char** pArg, BOOL bPrompt = TRUE) ;
	BOOL KillService(char* pName, BOOL bPrompt = TRUE);

    struct AdapterName
	{
		LPWSTR wszAdapterName;
		LPWSTR wszAdapterLinkName;
	};
	vector<AdapterName> m_aAdapterName;
protected:
	CStartServiceDlg* m_pUtility;
	BOOL m_bServiceStarted;
	BOOL m_bServiceInstalled;
	HANDLE m_hControlDevice;
	char m_buffer[MAX_ADAPTERS*256];
};

typedef struct _PROTOCOL_OID_DATA	// 设置和获取适配器OID信息所需的结构
{
    ULONG           Oid;
    ULONG           Length;
    UCHAR           Data[1];
} PROTOCOL_OID_DATA, *PPROTOCOL_OID_DATA;

class CAdapter  
{
public:
	CAdapter();
	virtual ~CAdapter();

	BOOL SetFilter(ULONG nFilters);
	BOOL ProtoRequest(PPROTOCOL_OID_DATA pOidData, BOOL bQuery);
	void SetOidCode(UINT aIOOidCodes[4]);
	int  SendData(PVOID pBuffer, int nLen, LPOVERLAPPED lpOverlapped);
	int  RecieveData(PVOID pBuffer, int nLen, LPOVERLAPPED lpOverlapped);
	BOOL ResetAdapter();
	BOOL OpenAdapter(LPCWSTR pwszSymbolicLink, BOOL bAsyn);
	void CloseAdapter();
protected:
	HANDLE m_hAdapter;
	ULONG m_nQueryOidCode;
	ULONG m_nSetOidCode;
	ULONG m_nResetOidCode;
	ULONG m_nGenFilterCode;
};

#endif // !defined(AFX_SERVICE_H__F2BB6498_F0D8_47FB_B18C_5F7EF7435D24__INCLUDED_)
