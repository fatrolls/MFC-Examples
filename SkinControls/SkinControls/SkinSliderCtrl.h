
#ifndef SKIN_SLIDERCTRL_H_
#define SKIN_SLIDERCTRL_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinImage.h"

#define WM_SKINSLIDER_MOVING (WM_USER + 9425)
#define WM_SKINSLIDER_MOVED  (WM_USER + 9426)

// 滑动条
class SKIN_CONTROLS_EXPORT CSkinSliderCtrl : public CStatic
{
public:
	CSkinSliderCtrl();
	virtual ~CSkinSliderCtrl();

	// 功能函数
public:
	// 设置背景图片
	void SetBackImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	void SetBackImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	void SetBackImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置背景图片2
	void SetBack2Image(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	void SetBack2Image(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	void SetBack2Image(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置滑动块图片
	void SetThumbImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	void SetThumbImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	void SetThumbImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置背景色
	void SetBackColor(COLORREF crBackColor) { m_crBackColor = crBackColor; }

	// 查询属性
	void GetRange(int &nMin, int &nMax) { nMin = m_nMin; nMax = m_nMax; }
	int GetRangeMax() { return m_nMax; }
	int GetRangeMin() { return m_nMin; }

	int GetPos() { return m_nPos; }

	// 设置属性
	void SetRange(int nMin, int nMax, BOOL bRedraw=FALSE);
	void SetRangeMin(int nMin, BOOL bRedraw = FALSE);
	void SetRangeMax(int nMax, BOOL bRedraw = FALSE);

	void SetPos(int nPos);

	void SetVertical(BOOL bVertical = TRUE) { m_bVertical = bVertical; };

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();

protected:
	void SetBitmap(HBITMAP hBitmap) {};

	int Pixel2Pos(int nPixel);
	int Pos2Pixel(int nPos);

	// 消息函数
protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnPaint();
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	UINT OnGetDlgCode();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnDestroy();
	void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinSliderCtrl)

protected:
	CSkinImage m_ImageBack; // 背景1
	CSkinImage m_ImageBack2; // 背景2
	CSkinImage m_ImageThumb; // 滑动块
	COLORREF m_crBackColor;  // 背景色

	int m_nMax, m_nMin, m_nPos, m_nPage;
	int m_nMouseOffset;

	BOOL m_bVertical;
	BOOL m_bLButtonDown;

private:
	static CSkinImage m_ImageDefSlider; // 滑动条
};

#endif // SKIN_SLIDERCTRL_H_