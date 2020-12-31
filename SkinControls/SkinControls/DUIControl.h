
#ifndef DUI_CONTROL_H_
#define DUI_CONTROL_H_
#pragma once

#include "SkinControlsDefine.h"

class CDUIManager;

// 控件基类
class SKIN_CONTROLS_EXPORT CDUIControl
{
public:
	CDUIControl();
	virtual ~CDUIControl();

public:
	// 控件ID 必须唯一
	virtual UINT GetID() const;
	virtual void SetID(UINT uID);
	virtual void SetName(LPCTSTR lpszName);
	virtual const CString& GetName() const;
	// 类名 根据这个来分类控件 比如"Button" "CheckBox"等
	virtual LPCTSTR GetClass() const;

	virtual void SetManager(CDUIManager* pDUIManager);

	// 文本相关
	virtual CString GetText() const;
	virtual void SetText(LPCTSTR pszText, bool bReDraw = false);
	virtual void SetFont(CFont* Font);
	// DrawText的最后一个参数的格式
	virtual void SetTextFormat(UINT uFormat, bool bReDraw = false);
	virtual void SetTextColor(COLORREF crText, bool bReDraw = false);

	// 位置相关
	virtual CRect GetPos() const;
	// 如果设置从右到左 则原点是从右边开始(反向的) 从下到上同理
	virtual void SetPos(const CRect& rc, bool bReDraw = false);
	virtual void SetPos(int x, int y, int cx, int cy, bool bReDraw = false);
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual int GetX() const;
	virtual int GetY() const;

	// DrawText的最后参数 DT_LEFT DT_TOP
	virtual void SetLayoutAlign(UINT uLayoutFormat);

	// 鼠标提示
	virtual CString GetToolTip() const;
	virtual void SetToolTip(LPCTSTR pszText);

	virtual COLORREF GetBkColor() const;
	virtual void SetBkColor(COLORREF crBk, bool bReDraw = false);

	// 一些重要的属性
	virtual bool IsVisible() const;
	virtual void SetVisible(bool bVisible = true, bool bReDraw = false);
	virtual bool IsEnabled() const;
	virtual void SetEnabled(bool bEnable = true, bool bReDraw = false);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);

	// 绘画
	virtual void DoPaint(CDC* pDC);
	virtual void PaintBkColor(CDC* pDC);
	virtual void PaintBkImage(CDC* pDC);
	virtual void PaintStatusImage(CDC* pDC);
	virtual void PaintText(CDC* pDC);

	// 操作相关
	virtual bool OnMouseMove(const CPoint& point);
	virtual bool OnMouseLeave();	// 这个主要的目的（button为例）：当控件在窗口边缘的时候 鼠标离开窗口 而控件可能是选中或者按下状态的时候需要刷新
	virtual bool OnLButtonDown(const CPoint& point);
	virtual bool OnLButtonUp(const CPoint& point);
	virtual bool OnRButtonDown(const CPoint& point);
	virtual bool OnRButtonUp(const CPoint& point);
	virtual bool OnMouseCursor(const CPoint& point);

	virtual void OnClick();
	virtual void UpdateControl();
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

	// 创建控件
	virtual bool CreateControl(UINT uID, LPCTSTR lpszName, CDUIManager* pDUIManager, const CRect& rc, LPCTSTR pszText = NULL, bool bVisble = true);

protected:
	UINT m_uID;
	CString m_strName;
	CRect m_rcItem;
	bool m_bVisible;
	bool m_bEnabled;
	CString m_strText;
	CString m_strToolTip;
	CFont* m_pFont;
	UINT m_uTextFormat;
	UINT m_uLayoutFormat;
	COLORREF m_clrBk;
	COLORREF m_clrTextColor;
	CDUIManager* m_pDUIManager;
};

#endif // DUI_CONTROL_H_