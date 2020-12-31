// DrawDib.cpp: implementation of the CDrawDib class.
//
//	Creator : El Barto (ef00@luc.ac.be)
//	Location : http://www.luc.ac.be/~ef00/ebgfx
//	Date : 09-04-98
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawDib::CDrawDib ()
{
	m_hDrawDib=NULL;
}

CDrawDib::~CDrawDib ()
{
	if ( m_hDrawDib )
		DrawDibClose ( m_hDrawDib );
}

HDRAWDIB CDrawDib::Open ()
{
	return m_hDrawDib=DrawDibOpen(); 
}

BOOL CDrawDib::Close ()
{
	return DrawDibClose ( m_hDrawDib );
}
	
BOOL CDrawDib::Begin ( HDC hdc, int dxDest, int dyDest,
	LPBITMAPINFOHEADER lpbi, int dxSrc, int dySrc, UINT wFlags )
{
	return DrawDibBegin ( m_hDrawDib, hdc, dxDest, dyDest, lpbi, 
		dxSrc, dySrc, wFlags );
}

BOOL CDrawDib::End ()
{
	return DrawDibEnd ( m_hDrawDib );
}

BOOL CDrawDib::Draw ( HDC hdc, int xDst, int yDst,
	int dxDst, int dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits,
	int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags )
{
	return DrawDibDraw ( m_hDrawDib, hdc, xDst, yDst, dxDst, dyDst, 
		lpbi, lpBits, xSrc, ySrc, dxSrc, dySrc, wFlags );
}

BOOL CDrawDib::DrawDib ( CDib *Dib, HDC hdc, int xDst, int yDst,
	int dxDst, int dyDst, UINT wFlags )
{
	return DrawDibDraw ( m_hDrawDib, hdc, xDst, yDst, dxDst, dyDst, 
		&(Dib->m_Info.bmiHeader), Dib->m_Bits, 0, 0, Dib->m_Size.cx,
		Dib->m_Size.cy, wFlags );
}
	
LPVOID CDrawDib::GetBuffer ( LPBITMAPINFOHEADER lpbi,
	DWORD dwSize, DWORD dwFlags )
{
	return DrawDibGetBuffer ( m_hDrawDib, lpbi, dwSize, dwFlags );
}
	
BOOL CDrawDib::ProfileDisplay ( LPBITMAPINFOHEADER lpbi )
{
	return DrawDibProfileDisplay ( lpbi );
}

HPALETTE CDrawDib::GetPalette ()
{
	return DrawDibGetPalette ( m_hDrawDib );
}

BOOL CDrawDib::SetPalette ( HPALETTE hpal )
{
	return DrawDibSetPalette ( m_hDrawDib, hpal );
}

BOOL CDrawDib::ChangePalette ( HDRAWDIB hdd, int iStart, int iLen,
	LPPALETTEENTRY lppe )
{
	return DrawDibChangePalette ( m_hDrawDib, iStart, iLen, lppe );
}

UINT CDrawDib::Realize ( HDC hdc, BOOL fBackground )
{
	return DrawDibRealize ( m_hDrawDib,  hdc,  fBackground );
}
	
BOOL CDrawDib::Start ( LONG rate )
{
	return DrawDibStart ( m_hDrawDib, rate );
}

BOOL CDrawDib::Stop ()
{
	return DrawDibStop ( m_hDrawDib );
}

BOOL CDrawDib::Time ( LPDRAWDIBTIME lpddtime )
{
	return DrawDibTime ( m_hDrawDib, lpddtime );
}