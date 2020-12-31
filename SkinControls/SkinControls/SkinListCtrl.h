
#ifndef SKIN_LISTCTRL_H_
#define SKIN_LISTCTRL_H_
#pragma once

#include "SkinScrollBar.h"
#include "SkinControlsDefine.h"
#include "SkinImage.h"

// 排序位置
#define SORT_AFTER 1 // 后面位置
#define SORT_FRONT -1 // 前面位置

// 排序类型
enum enSortType
{
	SortType_NoSort,				//没有排序
	SortType_Ascend,				//升序排序
	SortType_Descale,				//降序排序
};

// 类声明
class CSkinListCtrl;
class CSkinHeaderCtrl;

//////////////////////////////////////////////////////////////////////////////////

// 列头控件
class SKIN_CONTROLS_EXPORT CSkinHeaderCtrl : public CHeaderCtrl
{
public:
	// 构造函数
	CSkinHeaderCtrl();
	// 析构函数
	virtual ~CSkinHeaderCtrl();

	// 重载函数
public:
	// 控件绑定
	virtual void PreSubclassWindow();
	// 控件消息
	virtual BOOL OnChildNotify(UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);

	// 功能函数
public:
	// 设置锁定
	void SetLockCount(UINT uLockCount);
	// 设置列高
	void SetItemHeight(UINT uItemHeight);
	// 设置资源
	void SetHeaderImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 设置资源
	void SetHeaderImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置资源
	void SetHeaderImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);

	// 消息函数
protected:
	// 重画消息
	void OnPaint();
	// 绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()

	// 锁定列表
protected:
	UINT m_uLockCount; // 锁定数目
	UINT m_uItemHeight; // 子项高度
	COLORREF m_crTitle; // 字体颜色
	CSkinImage m_ImageHead; // 头部资源
};

//////////////////////////////////////////////////////////////////////////////////

// 列表控件
class SKIN_CONTROLS_EXPORT CSkinListCtrl : public CListCtrl
{
public:
	// 构造函数
	CSkinListCtrl();
	// 析构函数
	virtual ~CSkinListCtrl();

	// 重载函数
public:
	// 控件绑定
	virtual VOID PreSubclassWindow();
	// 绘画函数
	virtual VOID DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// 如果要改变行高 必须在父窗口的OnMeasureItem中调用
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// 插入函数
public:
	// 插入数据
	virtual void InsertDataItem(void* pItemData);
	// 更新数据
	virtual void UpdateDataItem(void* pItemData);
	// 删除数据
	virtual void DeleteDataItem(void* pItemData);

	// 数据控制
protected:
	// 获取位置
	virtual int GetInsertIndex(void* pItemData);
	// 排列数据
	virtual int SortItemData(LPARAM lParam1, LPARAM lParam2, WORD wColumnIndex, bool bAscendSort);
	// 描述字符
	virtual void ConstructString(void* pItemData, WORD wColumnIndex, LPTSTR pszString, WORD wMaxCount);

	// 绘画控制
protected:
	// 获取颜色
	virtual void GetItemColor(LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF& crColorText, COLORREF& crColorBack);
	// 绘画数据
	virtual void DrawCustomItem(CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, CRect& rcSubItem, int nColumnIndex);

	// 消息函数
protected:
	// 绘画背景
	BOOL OnEraseBkgnd(CDC* pDC);
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);

	// 静态函数
protected:
	// 排列函数
	static int CALLBACK SortFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamList);

	// 消息映射
protected:
	// 点击列表
	void OnColumnclick(NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()

	// 变量定义
public:
	CSkinHeaderCtrl m_SkinHeaderCtrl; // 列头控件
	CSkinScrollBar m_SkinScrollBar; // 滚动条类

	// 数据变量
protected:
	bool m_bAscendSort; // 升序标志
	COLORREF m_crTitle; // 字体颜色
	COLORREF m_crListTX; // 列表文字
	COLORREF m_crListBK; // 列表底色
};

#endif // SKIN_LISTCTRL_H_