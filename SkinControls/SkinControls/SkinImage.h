
#ifndef SKIN_IMAGE_H_
#define SKIN_IMAGE_H_
#pragma once

#include "SkinControlsDefine.h"

// 位图格式
enum BitmapFormat
{
	BF_UNKNOWN = 0, // 未知格式
	BF_BMP,
	BF_PNG,
	BF_OTHER // 其他 比如JPG
};

// 图像处理类
class SKIN_CONTROLS_EXPORT CSkinImage : public CCmdTarget
{
public:
	CSkinImage();
	virtual ~CSkinImage();

public:
	// 创建位图
	BOOL Create(int nWidth, int nHeight, HDC hDc = NULL);
	// 从文件加载位图
	BOOL LoadFromFile(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 从资源加载位图
	BOOL LoadFromResource(HMODULE hModule, LPCTSTR lpszResource, BitmapFormat bf = BF_UNKNOWN);
	// 从内存加载位图
	BOOL LoadFromMemory(BYTE* pBuffer, DWORD dwSize, BitmapFormat bf = BF_UNKNOWN);
	// 销毁位图
	void DestroyImage();

	// clrTransparent 如果位图有ALPHA通道则无效
	// 绘画位图
	void DrawImage(CDC* pDC, int nXPos, int nYPos, COLORREF clrTransparent);
	// 绘画位图
	void DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight, COLORREF clrTransparent);
	// 绘画位图
	void DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight, int nXScr, int nYSrc, int nSrcWidth, int nSrcHeight, COLORREF clrTransparent);
	// 绘画位图 
	void DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc, COLORREF clrTransparent);

	// 绘画位图
	void DrawImage(CDC* pDC, int nXPos, int nYPos);
	// 绘画位图
	void DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight);
	// 绘画位图
	void DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight, int nXScr, int nYSrc, int nSrcWidth, int nSrcHeight);
	// 绘画位图
	void DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc);

	// 是否有效
	BOOL IsValid() const;
	// 是否有Alpha通道
	BOOL IsAlphaImage() const;
	// 获取宽度
	int GetHeight() const;
	// 获取高度
	int GetWidth() const;
	// 获取宽高
	CSize GetExtent() const;
	// 获取句柄
	HBITMAP GetBitmap() const;
	// 获取位置像素
	BOOL GetBitmapPixel(CPoint pt, COLORREF& clrPixel);
	// 创建区域
	bool CreateBitmapRegion(CRgn& BitmapRgn, COLORREF crTransColor);
	// 创建区域
	bool CreateBitmapRegion(CRgn& BitmapRgn, int nXSrcPos, int nYSrcPos, int nSrcWidth, int nSrcHeight, COLORREF crTransColor);
	operator HBITMAP() const { return m_hBitmap; }

public:
	// 是否PNG
	static BOOL IsPngBitmapFile(LPCTSTR pszFileName);
	static BOOL IsPngBitmapResource(HMODULE hModule, LPCTSTR lpBitmapName);
	static BOOL IsPngBitmapMemory(BYTE* pBuffer, DWORD dwSize);
	// 是否包含Alpha
	static BOOL IsAlphaBitmapFile(LPCTSTR pszFileName);
	static BOOL IsAlphaBitmapResource(HMODULE hModule, LPCTSTR lpBitmapName);
	static BOOL IsAlphaBitmapMemory(BYTE* pBuffer, DWORD dwSize);
	// 获取Alpha位图及它的Alpha信息
	static BOOL GetBitmapBits(CDC& dcSrc, HBITMAP hBitmap, PBITMAPINFO& pBitmapInfo, LPVOID& pBits, UINT& nSize);
	// 创建有效的Alpha位图
	static HBITMAP PreMultiplyAlphaBitmap(HBITMAP hBitmap, BOOL* pbAlpha, LPBYTE* lpBits);
	// 加载Alpha位图
	static HBITMAP LoadAlphaBitmap(UINT nIDResource);
	static HBITMAP LoadAlphaBitmap(HMODULE hModule, LPCTSTR lpszResource);
	// 从资源加载位图
	static HBITMAP LoadBitmapFromResource(HMODULE hModule, LPCTSTR lpszResource, BOOL* lbAlphaBitmap, BitmapFormat bf = BF_UNKNOWN);
	// 从文件加载位图
	static HBITMAP LoadBitmapFromFile(LPCTSTR lpszFileName, BOOL* lbAlphaBitmap, BitmapFormat bf = BF_UNKNOWN);
	// 从内存加载位图
	static HBITMAP ConvertToBitmap(BYTE* pBuffer, DWORD dwSize);
	static HBITMAP LoadBitmapFromMemory(BYTE* pBuffer, DWORD dwSize, BOOL* lbAlphaBitmap, BitmapFormat bf = BF_UNKNOWN);

	// 透明转换
	static BOOL TransparentBlt(HDC hdcDest, const CRect& rcDest,HDC hdcSrc, const CRect& rcSrc, UINT crTransparent);

	// 显示具有指定透明度的图像
	static BOOL AlphaBlend(HDC hdcDest, const CRect& rcDest,HDC hdcSrc, const CRect& rcSrc);
	static BOOL AlphaBlend2(HDC hdcDest, const CRect& rcDest,HDC hdcSrc, const CRect& rcSrc, BYTE Transparency);

	static HBITMAP Create32BPPDIBSection(HDC hDC, int iWidth, int iHeight, LPBYTE* lpBits = NULL);

	// 没有MSIMG32.DLL的系统使用
	static BOOL McTransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
		int nWidthDest, int nHeightDest, HDC hdcSrc,
		int nXOriginSrc, int nYOriginSrc, int nWidthSrc,
		int nHeightSrc, UINT crTransparent);

private:
	LPBYTE PreMultiply();
	static BOOL BitmapsCompatible(LPBITMAP lpbm1, LPBITMAP lpbm2);
	static BOOL BlendImages(HBITMAP hbmSrc1, BOOL bRTL1, HBITMAP hbmSrc2, BOOL bRTL2, HBITMAP hbmDst);
	static BOOL DoAlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest,
		int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
		int nYOriginSrc, int nWidthSrc, int nHeightSrc);
	
private:
	LPBYTE m_pBits;
	HBITMAP m_hBitmap;
	BOOL m_bAlpha;
	CSize m_szExtent;
};

#endif // SKIN_IMAGE_H_