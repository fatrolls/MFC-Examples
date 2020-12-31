// DaoBmp.cpp : implementation file
//

// this class is only to read bitmap, not to write it !

#include "stdafx.h"
#include "DaoBmp.h"
#include <string.h>
#include <memory.h>

#include "DIBApi.h"

CDaoBitmap::CDaoBitmap()
{
  m_pData = NULL;
}

CDaoBitmap::~CDaoBitmap()
{
  Init();
}

BOOL CDaoBitmap::Init()
{
  if (m_pData != NULL)
    GlobalUnlock(m_hData);
  m_pData = NULL;
  return FALSE;
}

BOOL CDaoBitmap::Lock()
{
  ASSERT(m_hData != NULL);
  ASSERT(m_dwDataLength > 0);
  ASSERT(m_pData == NULL);

  // lock gloabal memory
  m_pData = (LPBYTE)GlobalLock(m_hData);
  if (m_pData == NULL) return FALSE;

  // get upper limit
  LPBYTE s = &m_pData[m_dwDataLength];

  // get object header
  LPBYTE p = m_pData;
  m_pObject = (OBJECTHEADER*)p;
  m_pName  = p + m_pObject->NameOffset;
  m_pClass = p + m_pObject->ClassOffset;
  p += m_pObject->HeaderSize;

  // get ole header
  m_pOleHeader = (OLEHEADER*)p;
  p += sizeof(OLEHEADER);
  m_pOleInfo = p;
  p += m_pOleHeader->Len;

  // at this point, we can check if it is a bitmap
  if (strcmp((char*)m_pOleInfo, "PBrush") != 0) return Init();

  // search "BM" signature and DIB object info
  while (memcmp(p, "BM", 2) != 0 && p < s) p++;
  if (p == s) return Init();
  m_pDib = (DIBOBJECTINFO*)p;
  p += sizeof(DIBOBJECTINFO);

  // get bitmap info
  m_pBmInfo = (BITMAPINFO*)p;

  // calculate the check checksum
  BYTE cs = 0;
  DWORD Size = m_dwDataLength - m_pObject->HeaderSize - sizeof(DWORD);
  p = (LPBYTE)m_pOleHeader;
  while (Size--) cs ^= *p++;
  DWORD CheckSum = CHECKSUM_SIGNATURE | cs;
  m_CheckSum = *(DWORD*)p;
  if (CheckSum != m_CheckSum) return Init();
  return TRUE;
}

void CDaoBitmap::Unlock()
{
  Init();
}

CBitmap* CDaoBitmap::GetBitmap(CDC* pDC)
{
  LPBYTE pBitmapData = (LPBYTE)::FindDIBBits((char*)m_pBmInfo);
  m_hBitmap = ::CreateDIBitmap(*pDC, &m_pBmInfo->bmiHeader, CBM_INIT, pBitmapData, m_pBmInfo, DIB_RGB_COLORS);
  return CBitmap::FromHandle(m_hBitmap);
}

DWORD CDaoBitmap::Width()
{
  ASSERT(m_pBmInfo != NULL);
  return ::DIBWidth((char*)m_pBmInfo);
}

DWORD CDaoBitmap::Height()
{
  ASSERT(m_pBmInfo != NULL);
  return ::DIBHeight((char*)m_pBmInfo);
}

HANDLE CDaoBitmap::CopyToClipboard(HWND hWnd)
{
  ASSERT(m_pData != NULL);
  static HANDLE hData = NULL;
  if (::OpenClipboard(hWnd))
  {
    DWORD Size = m_pDib->Size - sizeof(DIBOBJECTINFO);
    hData = GlobalAlloc(GMEM_MOVEABLE, Size);
    if (hData != NULL)
    {
      LPBYTE pData = (LPBYTE)GlobalLock(hData);
      memcpy(pData, m_pBmInfo, Size);
      GlobalUnlock(hData);
      ::SetClipboardData(CF_DIB, hData);
    }
    ::CloseClipboard();
  }
  return hData;
}
