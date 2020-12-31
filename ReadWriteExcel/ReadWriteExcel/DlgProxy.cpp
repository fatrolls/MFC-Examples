
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadWriteExcel.h"
#include "DlgProxy.h"
#include "ReadWriteExcelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReadWriteExcelDlgAutoProxy

IMPLEMENT_DYNCREATE(CReadWriteExcelDlgAutoProxy, CCmdTarget)

CReadWriteExcelDlgAutoProxy::CReadWriteExcelDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CReadWriteExcelDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CReadWriteExcelDlg)))
		{
			m_pDialog = reinterpret_cast<CReadWriteExcelDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CReadWriteExcelDlgAutoProxy::~CReadWriteExcelDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CReadWriteExcelDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CReadWriteExcelDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CReadWriteExcelDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IReadWriteExcel 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {AF2A28C6-8ECD-4D30-9DAA-1A7C0EBA8D1C}
static const IID IID_IReadWriteExcel =
{ 0xAF2A28C6, 0x8ECD, 0x4D30, { 0x9D, 0xAA, 0x1A, 0x7C, 0xE, 0xBA, 0x8D, 0x1C } };

BEGIN_INTERFACE_MAP(CReadWriteExcelDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CReadWriteExcelDlgAutoProxy, IID_IReadWriteExcel, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {B2359DC3-377F-45D3-AF2A-77278B400702}
IMPLEMENT_OLECREATE2(CReadWriteExcelDlgAutoProxy, "ReadWriteExcel.Application", 0xb2359dc3, 0x377f, 0x45d3, 0xaf, 0x2a, 0x77, 0x27, 0x8b, 0x40, 0x7, 0x2)


// CReadWriteExcelDlgAutoProxy 消息处理程序
