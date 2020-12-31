
#ifndef SKIN_TREECTRL_H_
#define SKIN_TREECTRL_H_
#pragma once

#include "SkinScrollBar.h"
#include "SkinControlsDefine.h"
#include "SkinImage.h"

// 树形列表
class SKIN_CONTROLS_EXPORT CSkinTreeCtrl : public CTreeCtrl
{
public:
	CSkinTreeCtrl();
	virtual ~CSkinTreeCtrl();

	// 设置资源
public:
	// 设置箭头
	// 从资源加载图片设置箭头
	void SetArrowImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 从文件加载图片设置箭头
	void SetArrowImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 从内存加载图片设置箭头
	void SetArrowImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置背景色
	void SetBackColor(COLORREF crBack) { m_crBack = crBack; }
	// 设置横线颜色
	void SetLineColor(COLORREF crLine) { m_crLine = crLine; }
	// 设置选中颜色
	void SetSelectedColor(COLORREF crSelected) { m_crSelected = crSelected; }
	// 设置悬浮颜色
	void SetHoverColor(COLORREF crHover) { m_crHover = crHover; }

	// 功能函数
public:
	// 获取选择
	HTREEITEM GetCurrentSelectItem(bool bOnlyText);

	// 展开函数
public:
	// 展开判断
	bool ExpandVerdict(HTREEITEM hTreeItem);
	// 展开列表
	bool ExpandListItem(HTREEITEM hTreeItem);

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();
	//窗口函数
	virtual LRESULT DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam);

public:
	// 创建消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 重画消息
	void OnPaint();
	// 绘画背景
	BOOL OnEraseBkgnd(CDC* pDC);
	// 位置消息
	afx_msg void OnSize(UINT nType, INT cx, INT cy);
	// 鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);
	// 光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);
	// 右键列表
	void OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult);
	// 左击列表
	void OnNMLClick(NMHDR* pNMHDR, LRESULT* pResult);
	// 列表改变
	void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	// 列表展开
	void OnTvnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinTreeCtrl)

	// 绘画函数
private:
	// 绘画子项
	void DrawTreeItem(CDC* pDC, CRect& rcClient, CRect& rcClipBox);
	// 绘画背景
	void DrawTreeBack(CDC* pDC, CRect& rcClient, CRect& rcClipBox);

	// 绘画辅助
private:
	// 绘制图标
	void DrawListImage(CDC* pDC, CRect rcRect, HTREEITEM hTreeItem);
	// 绘制文本
	void DrawItemString(CDC* pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected);

	// 位置变量
protected:
	int m_nXScroll; // 滚动偏移
	int m_nYScroll; // 滚动偏移

	// 资源变量
protected:
	CSkinImage m_ImageArrow; // 箭头图标
	COLORREF m_crBack; // 背景色
	COLORREF m_crLine; // 横线颜色
	COLORREF m_crSelected; // 选中颜色
	COLORREF m_crHover; // 悬浮颜色

	// 辅助变量
protected:
	HTREEITEM m_hItemMouseHover; // 盘旋子项
	HTREEITEM m_hTreeClickExpand; // 单击树项

protected:
	CSkinScrollBar m_SkinScrollBar; // 滚动条类

};

#endif // SKIN_TREECTRL_H_