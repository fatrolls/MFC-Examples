
#ifndef SKIN_WINDOW_H_
#define SKIN_WINDOW_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinImage.h"

class SKIN_CONTROLS_EXPORT CSkinWindow  
{
public:
	CSkinWindow();
	~CSkinWindow();

public:
	// 设置SKIN图片
	bool SetSkinImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	bool SetSkinImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	bool SetSkinImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 设置标题文字颜色 crInactiveText: 未激活文字的颜色
	void SetCaptionTextColor(COLORREF crText, COLORREF crInactiveText);

public:
	// 初始配置
	void InitWindow(CWnd* pWnd);
	// 非客户区大小
	void OnNcCalcSize(CWnd* pWnd, BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	// 非客户区按键测试
	LRESULT OnNcHitTest(CWnd* pWnd, CPoint point, BOOL bResizable = FALSE);
	// 非客户区绘制
	void OnNcPaint(CWnd* pWnd);
	// 标题消息
	void OnSetText(CWnd* pWnd);
	// 位置消息
	void OnSize(CWnd* pWnd);
	// 非客户区鼠标移动
	void OnNcMouseMove(CWnd* pWnd, UINT nHitTest, CPoint point);
	// 非客户区鼠标离开
	void OnNcMouseLeave(CWnd* pWnd);
	// 左键按下
	BOOL OnNcLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point);
	// 左键松开
	BOOL OnNcLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);
	// 右键松开
	BOOL OnNcRButtonUp(CWnd* pWnd, UINT nFlags, CPoint point);
	// 激活消息
	BOOL OnActivateApp(CWnd* pWnd, BOOL bActive, DWORD dwThreadID);
	// 背景
	BOOL OnEraseBkgnd(CWnd* pWnd, CDC * pDC);

	// 内部函数
private:
	void ResolveAnchor(const CRect& rcClient, CRect& rcAnchor, int nAnchor);
	void Paint(CWnd* pWnd, CDC* pDC);

private:
	enum
	{
		SKINPART_TOP_LEFT, SKINPART_TOP, SKINPART_TOP_RIGHT,
		SKINPART_IA_TOP_LEFT, SKINPART_IA_TOP, SKINPART_IA_TOP_RIGHT,
		SKINPART_LEFT_TOP, SKINPART_LEFT, SKINPART_LEFT_BOTTOM,
		SKINPART_IA_LEFT_TOP, SKINPART_IA_LEFT, SKINPART_IA_LEFT_BOTTOM,
		SKINPART_RIGHT_TOP, SKINPART_RIGHT, SKINPART_RIGHT_BOTTOM,
		SKINPART_IA_RIGHT_TOP, SKINPART_IA_RIGHT, SKINPART_IA_RIGHT_BOTTOM,
		SKINPART_BOTTOM_LEFT, SKINPART_BOTTOM, SKINPART_BOTTOM_RIGHT,
		SKINPART_IA_BOTTOM_LEFT, SKINPART_IA_BOTTOM, SKINPART_IA_BOTTOM_RIGHT,

		SKINPART_MINIMIZE, SKINPART_MINIMIZE_HOT, SKINPART_MINIMIZE_DOWN,
		SKINPART_IA_MINIMIZE,
		SKINPART_MAXIMIZE, SKINPART_MAXIMIZE_HOT, SKINPART_MAXIMIZE_DOWN,
		SKINPART_IA_MAXIMIZE,
		SKINPART_CLOSE, SKINPART_CLOSE_HOT, SKINPART_CLOSE_DOWN,
		SKINPART_IA_CLOSE,
		SKINPART_RESTORE, SKINPART_RESTORE_HOT, SKINPART_RESTORE_DOWN,
		SKINPART_IA_RESTORE,

		SKINPART__COUNT
	};

	enum
	{
		SKINANCHOR_SYSICON,
		SKINANCHOR_MINIMIZE,
		SKINANCHOR_MAXIMIZE,
		SKINANCHOR_CLOSE,

		SKINANCHOR__COUNT
	};

	enum
	{
		SKINPARTMODE_TILE,
		SKINPARTMODE_STRETCH
	};

private:
	static CSkinImage m_ImageDefSkin;
	CSkinImage m_ImageSkin; // 图片

private:
	CRect m_rcPart[SKINPART__COUNT];
	CRect m_rcAnchor[SKINANCHOR__COUNT];

private:
	CRect m_rcResize;
	CRect m_rcCaption;
	CFont m_fnCaption;
	COLORREF m_crCaptionText;
	COLORREF m_crCaptionInactive;

private:
	int m_nHoverAnchor;
	int m_nDownAnchor;

private:
	BOOL m_bTracking;
	BOOL m_bIsMinimzseEnable;
	BOOL m_bIsMaximizeEnable;
};

#endif // SKIN_WINDOW_H_
