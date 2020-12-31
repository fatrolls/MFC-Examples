#ifndef __CIMAGE_INL__
#define __CIMAGE_INL__

#include "cimage.h"

inline BOOL CImage::Draw(HDC hdc, int xDst, int yDst, int cxDst, int cyDst, 
                                  int xSrc, int ySrc, int cxSrc, int cySrc)
{
   return DrawImplementation(hdc, xDst, yDst, cxDst, cyDst, xSrc, ySrc, cxSrc, cySrc);
}

inline BOOL CImage::Draw(HDC hdc, const POINT& pt) 
{ 
   return Draw(hdc, pt.x, pt.y); 
}

inline BOOL CImage::Draw(HDC hdc, const RECT& dst)
{ 
   return Draw(hdc, dst.left, dst.top, dst.right - dst.left, dst.bottom - dst.top); 
}

inline BOOL CImage::Draw(HDC hdc, const RECT& dst, const RECT& src)
{ 
   return DrawImplementation(hdc, dst.left, dst.top, dst.right - dst.left, dst.bottom - dst.top,
                    src.left, src.top, src.right - src.left, src.bottom - src.top); 
}

inline void   CImage::EnableTransparency(BOOL bEnable /*= TRUE*/)
{ 
   if (!bEnable) m_info.nBkgndIndex = -1; 
}

inline BOOL CImage::HasTransparency(void) const
{ 
   return (m_info.nBkgndIndex != -1); 
}

inline DWORD  CImage::GetWidth (void) const
{ 
   return m_header.biWidth ; 
}

inline DWORD  CImage::GetHeight(void) const 
{ 
   return m_header.biHeight; 
}

inline SIZE   CImage::GetSize  (void) const
{ 
   SIZE size; size.cx = m_header.biWidth, size.cy = m_header.biHeight; return size; 
}

inline DWORD  CImage::GetEffWidth() const
{
   return m_info.dwEffWidth;
}

inline DWORD  CImage::GetColorCount() const
{
   return m_header.biClrUsed;
}

inline BYTE	  CImage::GetColorType() const
{
   return m_info.bColorType;
}

inline WORD	  CImage::GetBPP() const
{
   return m_header.biBitCount;
}

inline enum cximage_type CImage::GetFileType()
{ 
   return m_info.dwFileType;
}

inline void   CImage::SetFileType(enum cximage_type type)
{ 
   m_info.dwFileType = type;
}

inline LPCSTR CImage::GetLastError()
{ 
   return m_info.szLastError;
}

#endif // __CIMAGE_INL__
