// HookDriver.h: interface for the CHookDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOKDRIVER_H__647A55DC_52B2_4852_8853_E232E328707B__INCLUDED_)
#define AFX_HOOKDRIVER_H__647A55DC_52B2_4852_8853_E232E328707B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHookDriver  
{
public:
	CHookDriver(LPCTSTR pszDriverPath, LPCTSTR pszLinkName);
	virtual ~CHookDriver();

	// 此驱动是否可用
	virtual BOOL IsValid() { return (m_hSCM != NULL && m_hService != NULL); }
	// 开启服务。也就是说驱动的DriverEntry函数将被调用
	virtual BOOL StartDriver();
	// 结束服务。即驱动程序的DriverUnload例程将被调用
	virtual BOOL StopDriver();
	// 打开设备，即取得到此驱动的一个句柄
	virtual BOOL OpenDevice();
	// 向设备发送控制代码
	virtual DWORD IoControl(DWORD nCode, PVOID pInBuffer, 
			DWORD nInCount, PVOID pOutBuffer, DWORD nOutCount);
	// 实现
protected:
	char m_szLinkName[MAX_PATH];//符号连接名称
	bool m_bStarted;//是否启动
	bool m_bCreateService;//是否启动服务
	HANDLE m_hSCM;//服务控制管理器句柄
	HANDLE m_hService;//服务句柄
	HANDLE m_hDriver;//驱动句柄， 文件
};

#endif // !defined(AFX_HOOKDRIVER_H__647A55DC_52B2_4852_8853_E232E328707B__INCLUDED_)
