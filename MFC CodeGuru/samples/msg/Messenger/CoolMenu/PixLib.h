// PixLib.h: interface for the PixLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIXLIB_H__BDB658D2_C3BF_11D1_9AA6_0060B017334D__INCLUDED_)
#define AFX_PIXLIB_H__BDB658D2_C3BF_11D1_9AA6_0060B017334D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace PxLib
{
	extern void FillRect(CDC& dc, const CRect& rc, COLORREF color);
	extern void FillRect(CDC& dc, const CRect& rc, CBrush *pBrush);
	extern void PaintRect(CDC& dc, int x, int y, int w, int h, COLORREF color);
	extern void DrawEmbossed(CDC& dc, CImageList& il, int i,
								CPoint p, BOOL bColor=FALSE);

	extern HBITMAP LoadSysColorBitmap(LPCTSTR lpResName, BOOL bMono=FALSE);
	inline HBITMAP LoadSysColorBitmap(UINT nResID, BOOL bMono=FALSE)
	{
		return LoadSysColorBitmap(MAKEINTRESOURCE(nResID), bMono);
	}
	HBITMAP CreateDitherBitmap();
	int GetLuminosity(COLORREF color);
} // end namespace


#endif // !defined(AFX_PIXLIB_H__BDB658D2_C3BF_11D1_9AA6_0060B017334D__INCLUDED_)
