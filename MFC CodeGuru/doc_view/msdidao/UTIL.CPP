/////////////////////////////////////////////////////////////////////////////
// Printer font

#include "stdafx.h"
//#include "PrnFont.h"

CPrinterFont::~CPrinterFont()
{
  if (m_hObject != NULL) DeleteObject();
}

void CPrinterFont::Create(CDC* pDC)
{
  if (m_hObject == NULL)
  {
    LOGFONT m_lf;
    // create printer font from device context
    CFont* pFont = pDC->GetCurrentFont();
    pFont->GetObject(sizeof(LOGFONT), &m_lf);
    // map to printer font metrics
    HDC hDCFrom = ::GetDC(NULL);
    m_lf.lfHeight = ::MulDiv(m_lf.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY),
      ::GetDeviceCaps(hDCFrom, LOGPIXELSY));
    m_lf.lfWidth = ::MulDiv(m_lf.lfWidth, pDC->GetDeviceCaps(LOGPIXELSX),
      ::GetDeviceCaps(hDCFrom, LOGPIXELSX));
    ::ReleaseDC(NULL, hDCFrom);
    // create it, if it fails we just the the printer's default.
    VERIFY(this->CreateFontIndirect(&m_lf));
    CFont* pOldFont = pDC->SelectObject(this);
    pDC->GetTextMetrics(&m_tm);
    pDC->SelectObject(pOldFont);
  }
}

void CPrinterFont::Create(CDC* pDC, int nChar, int Width)
{
  if (m_hObject == NULL)
  {
    LOGFONT m_lf;
    // create printer font from device context
    CFont* pFont = pDC->GetCurrentFont();
    pFont->GetObject(sizeof(LOGFONT), &m_lf);
    // calculate the new Width
    m_lf.lfWidth = Width / nChar;
    m_lf.lfHeight = 0;
    // create it, if it fails we just the the printer's default.
    VERIFY(this->CreateFontIndirect(&m_lf));
    CFont* pOldFont = pDC->SelectObject(this);
    pDC->GetTextMetrics(&m_tm);
    pDC->SelectObject(pOldFont);
  }
}

/////////////////////////////////////////////////////////////////////////////
// string functions

void ClearSpaces(char* pszBuffer)
{
  char* p = pszBuffer;
  while(*p) p++; p--;
  while(p >= pszBuffer && *p == ' ') *p-- = '\0';
}

void StrPad(char* pszBuffer, int Len)
{
  char *p = pszBuffer;
  int len = 0;
  while (*p) { p++; len++; }
  while (len < Len) { *p++ = ' '; len++; }
  *p = '\0';
}

void StrCenter(char* pszBuffer, int Len)
{
  char *p = pszBuffer;
  int len = 0;

  StrPad(pszBuffer, Len);
  StrRight(pszBuffer, Len);			// right
  while(*p && *p == ' ') { p++; len++; }	// find first
  if (*p) StrLeft(&pszBuffer[len/2], Len);	// center
}

void StrLeft(char* pszBuffer, int Len)
{
  char *s, *d;

  StrPad(pszBuffer, Len);
  s = d = pszBuffer;
  while(*s && *s == ' ') s++;			// find first
  while(*s) *d++ = *s++;			// copy to start
  if (d != pszBuffer) while(*d) *d++ = ' ';	// fill with spaces
}

void StrRight(char* pszBuffer, int Len)
{
  char *s, *d, *p;

  StrPad(pszBuffer, Len);
  s = d = p = &pszBuffer[Len-1];
  while(s >= pszBuffer && *s == ' ') s--;	// find last
  while(s >= pszBuffer) *d-- = *s--;		// copy to end
  if (d != p) while(d >= pszBuffer) *d-- = ' ';	// fill with spaces
}

void ClearSpaces(CString& strBuffer)
{
  int len = strBuffer.GetLength();
  ::ClearSpaces(strBuffer.GetBuffer(len));
  strBuffer.ReleaseBuffer(-1);
}

void ClearAllSpaces(CString& strBuffer)
{
  int len = strBuffer.GetLength();
  char* p = strBuffer.GetBuffer(len);
  StrLeft(p, len);
  ::ClearSpaces(p);
  strBuffer.ReleaseBuffer(-1);
}

void StrLeft(CString& strBuffer)
{
  int len = strBuffer.GetLength();
  char* p = strBuffer.GetBuffer(len);
  StrLeft(p, len);
  strBuffer.ReleaseBuffer(-1);
}

void StrCenter(CString& strBuffer)
{
  int len = strBuffer.GetLength();
  char* p = strBuffer.GetBuffer(len);
  StrCenter(p, len);
  strBuffer.ReleaseBuffer(-1);
}

void StrRight(CString& strBuffer)
{
  int len = strBuffer.GetLength();
  char* p = strBuffer.GetBuffer(len);
  StrRight(p, len);
  strBuffer.ReleaseBuffer(-1);
}
