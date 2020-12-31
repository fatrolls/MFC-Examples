
#ifndef DUI_WND_H_
#define DUI_WND_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIControl.h"
#include "DUIManager.h"

class SKIN_CONTROLS_EXPORT CDUIWnd : public CWnd
{
public:
	CDUIWnd();
	virtual ~CDUIWnd();

public:
	// 加载配置
	bool LoadSkinXml(LPCTSTR lpszXml, LPCTSTR lpszWindow);
	// 更新皮肤
	bool UpdateSkinInfo(LPCTSTR lpszXml, LPCTSTR lpszWindow);
	// 绘画DUI控件(必须在合适的地方调用此函数,比如OnPaint)
	void DrawDuiControls(CDC* pDC);
	// DUI控件消息处理
	virtual void DuiMessageHandler(UINT uID, CDUIControl* pControl) = 0;
	CDUIManager* GetDuiManager() const { return m_pDuiManager; }

protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnSize(UINT nType, int cx, int cy);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	LRESULT OnDuiMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

protected:
	CDUIManager* m_pDuiManager;
	bool m_bMouseHover;
};

#endif // DUI_WND_H_
