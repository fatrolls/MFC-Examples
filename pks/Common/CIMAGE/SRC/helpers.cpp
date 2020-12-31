// helpers.cpp
//

#include "stdafx.h"
#include "helpers.h"

#define LMRT_RECT_WIDTH(rc)  ((rc).right  - (rc).left)
#define LMRT_RECT_HEIGHT(rc) ((rc).bottom - (rc).top )

BOOL RectBestFit(SIZE extSrc, LPCRECT rcDest, LPRECT rcResult, BOOL bHCenter, BOOL bVCenter, BOOL bFill)
{
   SIZE extImage = extSrc;
   POINT pt;
   if ( bFill || ((extImage.cx > LMRT_RECT_WIDTH(*rcDest)) || (extImage.cy > LMRT_RECT_HEIGHT(*rcDest))) )
   {
      const float factor_x = (float)extImage.cx / (float)LMRT_RECT_WIDTH (*rcDest);
      const float factor_y = (float)extImage.cy / (float)LMRT_RECT_HEIGHT(*rcDest);
            float factor   = max(factor_x, factor_y);
      extImage.cx = (int)((float)extImage.cx / factor);
      extImage.cy = (int)((float)extImage.cy / factor);
   }
   
   pt.x = bHCenter ? (LMRT_RECT_WIDTH (*rcDest) - extImage.cx) / 2 : rcDest->left;
   pt.y = bVCenter ? (LMRT_RECT_HEIGHT(*rcDest) - extImage.cy) / 2 : rcDest->top;

   SetRect(rcResult, pt.x, pt.y, pt.x + extImage.cx, pt.y + extImage.cy);
   
   return TRUE;
}

CBrush* SelectObject(CDC* pDC, CBrush* brush)
{
   VERIFY(brush->UnrealizeObject());
	CPoint pt(0, 0);
	pDC->LPtoDP(&pt);
	pt = pDC->SetBrushOrg(pt.x % 8, pt.y % 8);
   return pDC->SelectObject(brush);
}

CString GetTempPath(void)
{
   CString str;
   GetTempPath(_MAX_PATH, str.GetBuffer(_MAX_PATH));
   str.ReleaseBuffer();
   return str;
}

BOOL IsFileSystemFile(LPCTSTR lpszPath)
{
   const DWORD dw = GetFileAttributes(lpszPath);
   return (ULONG_MAX != dw) && ((dw & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY);
}

BOOL MoveFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bOverwrite)
{
   if (bOverwrite && IsFileSystemFile(lpExistingFileName) && IsFileSystemFile(lpNewFileName))
   {
      _tunlink(lpNewFileName);
   }
#ifdef _MSDOS
   return (0 == rename(lpExistingFileName, lpNewFileName));
#else
   return MoveFile(lpExistingFileName, lpNewFileName);
#endif
}

