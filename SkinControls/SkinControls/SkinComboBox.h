
#ifndef SKIN_COMBOBOX_H_
#define SKIN_COMBOBOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinEdit.h"
#include "SkinImage.h"

// 列表控件
class SKIN_CONTROLS_EXPORT CSkinComboBoxList : public CListBox
{
public:
	// 构造函数
	CSkinComboBoxList();
	// 析构函数
	virtual ~CSkinComboBoxList();

	// 重载函数
protected:
	// 绘画子项
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// 消息映射
protected:
	// 界面绘画
	void OnNcPaint();

    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

// 编辑控件
class SKIN_CONTROLS_EXPORT CSkinComboBoxEdit : public CSkinEdit
{
protected:
	// 设置焦点
	afx_msg VOID OnSetFocus(CWnd* pOldWnd);
	// 失去焦点
	afx_msg VOID OnKillFocus(CWnd* pNewWnd);
	// 鼠标离开
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	// 鼠标移动
	afx_msg VOID OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

// 选择控件
class SKIN_CONTROLS_EXPORT CSkinComboBox : public CComboBox
{
	friend class CSkinComboBoxEdit;

public:
	// 构造函数
	CSkinComboBox();
	// 析构函数
	virtual ~CSkinComboBox();

	// 重载函数
protected:
	// 控件绑定
    virtual VOID PreSubclassWindow();
	// 测量子项
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// 功能函数
public:
	// 边框设置
	void SetDrawBorder(bool bDrawBorad);
	// 设置资源
	bool SetButtonImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 设置资源
	bool SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置资源
	bool SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);

	// 内部函数
protected:
	// 配置控件
	void Initialization();
	// 更新控件
	void RedrawFocusedFrame();
	// 调整控件
	void RectifyControl(int nWidth, int nHeight);
	// 设置高亮
	void SetHighlighted(BOOL bHot);

	// 消息映射
protected:
	// 重画消息
    void OnPaint();
	// 列表关闭
	void OnCbnCloseup();
	// 绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	// 创建消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 鼠标移动
	void OnMouseMove(UINT nFlags, CPoint Point);
	// 鼠标离开
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	// 设置焦点
	void OnSetFocus(CWnd* pOldWnd);
	// 失去焦点
	void OnKillFocus(CWnd* pNewWnd);

	DECLARE_MESSAGE_MAP()

	// 属性变量
protected:
	enum
	{
		_nImageNormal = 0,
		_nImageFocusOrHover,
		_nImagePushed,
		_nImageDisabled,

		_nImageCount = 4,
	};
	UINT m_uButtonWidth; // 按钮宽度
	COLORREF m_crEnableBack; // 背景颜色
	COLORREF m_crDisableBack; // 背景颜色
	COLORREF m_crEnableBorder; // 边框颜色
	COLORREF m_crDisableBorder; // 边框颜色
	CSkinImage m_ImageButton;

	// 状态变量
protected:
	BOOL m_bHighlighted; // 高亮
	BOOL m_bFocused; // 焦点
	bool m_bDrawBorder; // 绘画边框

	// 控件变量
protected:
	CSkinComboBoxEdit m_SkinComboBoxEdit; // 编辑控件
	CSkinComboBoxList m_SkinComboBoxList; // 列表控件

private:
	static CSkinImage m_ImageDefButton;
};

#endif // SKIN_COMBOBOX_H_