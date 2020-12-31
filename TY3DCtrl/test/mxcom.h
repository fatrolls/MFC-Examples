#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CMxScene 包装类
#ifdef _DEBUG
#import "..\bin\Debug\ProjectTreeCOMd.dll" no_namespace //raw_interfaces_only
#import "..\bin\Debug\SceneCOMd.dll" no_namespace //raw_interfaces_only
#else 
#import "..\bin\Debug\ProjectTreeCOM.dll" no_namespace //raw_interfaces_only
#import "..\bin\Debug\SceneCOM.dll" no_namespace //raw_interfaces_only
#endif
class CMxScene : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMxScene)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
            = { 0xEBE12DA6,0x4A44,0x41E8, {0x9C,0x5D,0x72,0xAE,0x21,0xCE,0xD1,0x98} };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

};


class CMxTree : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMxTree)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
            = { 0xC9C78852,0xA65F,0x476B, {0xB0,0x0B,0x10,0x51,0xC6,0x9D,0xF6,0x6E} };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

};
