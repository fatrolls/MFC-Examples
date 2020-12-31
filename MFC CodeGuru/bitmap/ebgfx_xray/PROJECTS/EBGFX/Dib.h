// Dib.h: interface for the CDib class.
//
//	Creator : El Barto (ef00@luc.ac.be)
//	Location : http://www.luc.ac.be/~ef00/ebgfx
//	Date : 09-04-98
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__4AC8F494_CB24_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_DIB_H__4AC8F494_CB24_11D1_91CA_0020AFF82585__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDib  
{
public:
	COLORREF *m_Bits;
	BITMAPINFO m_Info;
	HBITMAP m_Bitmap;
	CSize m_Size;

	BOOL Create ( int Width, int Height );
	BOOL Destroy ();

	void CopyDC ( CDC *pDC, int x, int y );
	void PasteDC ( CDC *pDC, int x, int y, int w, int h );
	void SetBitmap ( CDC *pDC, CBitmap *pBitmap );
	
	void Fill ( int R, int G, int B );
	void FillGlass ( int R, int G, int B, int A );
	void FillStippledGlass ( int R, int G, int B );

	void Copy ( CDib *Dib );
	void Paste ( CDib *Dib );

	void Blend ( CDib *Dib, int A );
	void Darken ( CDib *Dib );
	void Difference ( CDib *Dib );
	void Lighten ( CDib *Dib );
	void Multiply ( CDib *Dib );
	void Screen ( CDib *Dib );

	void CopyRect ( CDib *Dib, int x, int y );
	void PasteRect ( CDib *Dib, int x, int y );

	void FillRect ( int x, int y, int w, int h, int R, int G, int B );
	void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
	void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );
	
	void BlendRect ( CDib *Dib, int x, int y, int A );
	void DarkenRect ( CDib *Dib, int x, int y );
	void DifferenceRect ( CDib *Dib, int x, int y );
	void LightenRect ( CDib *Dib, int x, int y );
	void MultiplyRect ( CDib *Dib, int x, int y );
	void ScreenRect ( CDib *Dib, int x, int y );

	void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
	void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );

	CDib ();
	virtual ~CDib ();
};

#endif // !defined(AFX_DIB_H__4AC8F494_CB24_11D1_91CA_0020AFF82585__INCLUDED_)
