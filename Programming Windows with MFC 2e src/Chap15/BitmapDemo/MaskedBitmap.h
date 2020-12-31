// MaskedBitmap.h: interface for the CMaskedBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASKEDBITMAP_H__D71EF554_A6FE_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_MASKEDBITMAP_H__D71EF554_A6FE_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMaskedBitmap : public CBitmap  
{
public:
	void DrawTransparent (CDC* pDC, int x, int y, COLORREF clrTransparency);
	void Draw (CDC* pDC, int x, int y);
};

#endif // !defined(AFX_MASKEDBITMAP_H__D71EF554_A6FE_11D2_8E53_006008A82731__INCLUDED_)
