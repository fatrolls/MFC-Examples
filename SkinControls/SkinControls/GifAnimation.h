
#ifndef SKIN_GIFANIMATION_H_
#define SKIN_GIFANIMATION_H_
#pragma once

#include "SkinControlsDefine.h"
#include "GifImage.h"
#include "SkinImage.h"

// GIF动画类
/*
// 用法
// CGifAnimation m_GifAnimation;
// m_GifAnimation.SetAnimationInfo(...);
// m_GifAnimation.LoadFromFile(...);
// m_GifAnimation.Play();
// 在OnPaint()里 m_GifAnimation.Draw(...);
*/

class CCompatibleDC;

class SKIN_CONTROLS_EXPORT CGifAnimation
{
public:
	// 构造函数
	CGifAnimation();
	// 析构函数
	~CGifAnimation();

	// 功能函数
public:
	// 设置初始信息
	void SetAnimationInfo(HWND hWnd, CPoint& ptDraw, COLORREF clrBackground);
	// 播放
	void Play();
	// 绘画动画
	void Draw(CDC* pDC);
	// 停止
	void Stop();
	// 加载动画
	bool LoadFromFile(LPCTSTR pszFileName);
	// 加载动画
	bool LoadFromMemroy(BYTE* pcbData, LONG lDataSize);
	// 加载动画
	bool LoadFromResource(LPCTSTR pszResourceName, LPCTSTR pszResourceType);
	// 停止动画同时删除资源
	void UnLoad();
	// 正在播放
	BOOL IsPlaying() const;

private:
	BOOL PrepareDC();
	void ThreadAnimation();
	static UINT WINAPI _ThreadAnimation(LPVOID pParam);

private:
	CPoint m_ptDraw;
	BOOL m_bIsPlaying;
	volatile BOOL m_bExitThread;
	HWND m_hWnd;
	CGIFImage m_GifImage;
	
	HDC m_hMemDC;
	HDC m_hDispMemDC;
	HBITMAP m_hDispMemBM;
	HBITMAP m_hDispOldBM;
	BOOL m_bIsInitialized;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	COLORREF m_clrBackground;

	HANDLE m_hThread;
	HANDLE m_hExitEvent;
};

#endif // SKIN_GIFANIMATION_H_
