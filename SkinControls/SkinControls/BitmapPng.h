
#ifndef BITMAP_PNG_H_
#define BITMAP_PNG_H_
#pragma once

#include "SkinControlsDefine.h"

// 用来加载PNG
class SKIN_CONTROLS_EXPORT CBitmapPng : public CBitmap
{
	struct CCallback;
public:
	CBitmapPng();

public:

	// 从文件加载
	BOOL LoadFromFile(LPCTSTR lpszFileName);

	// 从资源加载
	BOOL LoadFromResource(HMODULE hModule, HRSRC hRes);

	// 从内存加载
	BOOL LoadFromMemory(BYTE* pBuffer, DWORD dwSize);

	BOOL LoadFromFile(CFile* pFile);

	// 是否有Alpha通道
	BOOL IsAlpha() const;

private:
	HBITMAP ConvertToBitmap(BYTE* pbImage, CSize szImage,  int cImgChannels) const;

protected:
	BOOL m_bAlpha;
};

AFX_INLINE BOOL CBitmapPng::IsAlpha() const {
	return m_bAlpha;
}

SKIN_CONTROLS_EXPORT int ZLibCompress(BYTE *dest, ULONG* destLen, const BYTE *source, ULONG sourceLen);
SKIN_CONTROLS_EXPORT ULONG ZLibCompressBound(ULONG sourceLen);
SKIN_CONTROLS_EXPORT int ZLibUncompress(BYTE *dest, ULONG* destLen, const BYTE* source, ULONG sourceLen);

#endif // BITMAP_PNG_H_
