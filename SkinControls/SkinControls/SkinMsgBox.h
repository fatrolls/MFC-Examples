
#ifndef SKIN_MSG_BOX_H_
#define SKIN_MSG_BOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinButton.h"
#include "SkinDialog.h"

// 消息窗口
class SKIN_CONTROLS_EXPORT CSkinMsgBox : public CSkinDialog
{
public:
	// 构造函数
	CSkinMsgBox(CWnd* pParentWnd = NULL);
	// 析构函数
	virtual ~CSkinMsgBox();

	// 重载函数
protected:
	// 初始化消息
	virtual BOOL OnInitDialog();
	// 命令消息
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// 功能函数
public:
	// 显示消息
	int ShowMsgBox(LPCTSTR pszString, UINT uType = MB_OK, UINT nElapse = 0);
	// 显示消息
	int ShowMsgBox(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType = MB_OK, UINT nElapse = 0);

	// 内部函数
private:
	// 创建按钮
	void CreateBoxButton();

	// 消息映射
protected:
	// 绘画消息
	VOID OnPaint();
	// 时间消息
	VOID OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	// 属性变量
private:
	UINT m_uType; // 消息类型
	CString m_strString; // 提示消息
	CString m_strCaption; // 信息标题

	// 辅助变量
private:
	UINT m_nElapse; // 剩余时间
	UINT m_nBtCount; // 按钮数目
	CRect m_rcString; // 字符位置
	CString m_strDefBtn; // 默认按钮
	UINT m_uDefBtnIndex; // 默认索引

	// 控件变量
private:
	CSkinButton m_btnButton[3]; // 按钮控件
};

// 全局函数
extern "C" SKIN_CONTROLS_EXPORT INT ShowMsgBox(LPCTSTR pszString, UINT uType = MB_OK, UINT nElapse = 0);
extern "C" SKIN_CONTROLS_EXPORT INT ShowMsgBoxEx(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType = MB_OK, UINT nElapse = 0);

#endif // SKIN_MSG_BOX_H_