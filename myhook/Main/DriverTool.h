// DriverTool.h: interface for the CDriverTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVERTOOL_H__257EF964_5488_41B6_9618_A742B05DD18B__INCLUDED_)
#define AFX_DRIVERTOOL_H__257EF964_5488_41B6_9618_A742B05DD18B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDriverTool  
{
public:
	CDriverTool();
	virtual ~CDriverTool();

	// 此驱动是否可用
	virtual BOOL IsValid() { return (m_hSCM != NULL && m_hService != NULL); }
	// 开启服务。也就是说驱动的DriverEntry函数将被调用
	virtual BOOL StartDriver(LPCTSTR pszDriverPath = NULL);
	// 结束服务。即驱动程序的DriverUnload例程将被调用
	virtual BOOL StopDriver(LPCTSTR pszDriverPath = NULL);
	// 打开设备，即取得到此驱动的一个句柄
	virtual HANDLE  OpenControlDevice(LPCTSTR pszDriverPath = NULL);
	// 向设备发送控制代码
	virtual DWORD IoControl(HANDLE hDriver, DWORD nCode, PVOID pInBuffer, DWORD nInCount, PVOID pOutBuffer, DWORD nOutCount);
	//卸载驱动
	virtual BOOL UnInstallDriver(LPCTSTR pszDriverPath = NULL);
	//安装驱动
	virtual bool  InstallDriver(LPCTSTR pszDriverPath, LPCTSTR pszLinkName, bool bAttach = true);
	// 实现
protected:
	char m_szLinkName[MAX_PATH];//符号连接名称
	bool m_bStarted;//是否启动
	bool m_bCreateService;//是否启动服务
	HANDLE m_hSCM;//服务控制管理器句柄
	HANDLE m_hService;//服务句柄
	HANDLE m_hDriver;//驱动句柄， 文件
};


#endif // !defined(AFX_DRIVERTOOL_H__257EF964_5488_41B6_9618_A742B05DD18B__INCLUDED_)
