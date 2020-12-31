// LSPHelper.h: interface for the CLSPHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSPHELPER_H__CB526D9E_A103_440B_9BC7_2A92DD3ABCDD__INCLUDED_)
#define AFX_LSPHELPER_H__CB526D9E_A103_440B_9BC7_2A92DD3ABCDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Ws2spi.h>

class CLSPHelper  
{
public:
	bool RemoveProvider(DWORD dwCatalogID);
	bool RemoveProvider(WCHAR* szLSPDllPath);
	bool InstallProvider(WCHAR* szLSPName, WCHAR* szLSPDLLPath);
	CLSPHelper();
	virtual ~CLSPHelper();

	bool GetProvider(LPINT piProtocols);

	LPWSAPROTOCOL_INFOW m_pProtocolInfo;
	int m_iProtocolNum;
};

#endif // !defined(AFX_LSPHELPER_H__CB526D9E_A103_440B_9BC7_2A92DD3ABCDD__INCLUDED_)
