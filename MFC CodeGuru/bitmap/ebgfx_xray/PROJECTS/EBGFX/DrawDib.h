// DrawDib.h: interface for the CDrawDib class.
//
//	Creator : El Barto (ef00@luc.ac.be)
//	Location : http://www.luc.ac.be/~ef00/ebgfx
//	Date : 09-04-98
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWDIB_H__B1E2F1A3_CCA7_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_DRAWDIB_H__B1E2F1A3_CCA7_11D1_91CA_0020AFF82585__INCLUDED_

#include  <vfw.h>
#include "Dib.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDrawDib  
{
public:
	HDRAWDIB m_hDrawDib;

	HDRAWDIB Open ();
	BOOL Close ();
	
	BOOL Begin ( HDC hdc, int dxDest, int dyDest,
		LPBITMAPINFOHEADER lpbi, int dxSrc, int dySrc, UINT wFlags );
	BOOL End ();

	BOOL Draw ( HDC hdc, int xDst, int yDst,
		int dxDst, int dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits,
		int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags );
	BOOL DrawDib ( CDib *Dib, HDC hdc, int xDst, int yDst,
		int dxDst, int dyDst, UINT wFlags );
	
	LPVOID GetBuffer ( LPBITMAPINFOHEADER lpbi,
		DWORD dwSize, DWORD dwFlags );
	
	BOOL ProfileDisplay ( LPBITMAPINFOHEADER lpbi );

	HPALETTE GetPalette ();
	BOOL SetPalette ( HPALETTE hpal );
	BOOL ChangePalette ( HDRAWDIB hdd, int iStart, int iLen,
		LPPALETTEENTRY lppe );
	UINT Realize ( HDC hdc, BOOL fBackground );

	BOOL Start ( LONG rate );
	BOOL Stop ();
	BOOL Time ( LPDRAWDIBTIME lpddtime );

	CDrawDib ();
	virtual ~CDrawDib ();
};

#endif // !defined(AFX_DRAWDIB_H__B1E2F1A3_CCA7_11D1_91CA_0020AFF82585__INCLUDED_)
