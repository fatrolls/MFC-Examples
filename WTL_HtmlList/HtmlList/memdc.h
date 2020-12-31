#ifndef _CMemDC_
#define _CMemDC_
#include <atlapp.h>
#include <atlgdi.h>
using namespace WTL;

/////////////////////////////////////////////////////////////////////////////
// CMemDC

class CMemDC : public CDC
{
public:
   CDCHandle     m_dc;          // Owner DC
   CBitmap       m_bitmap;      // Offscreen bitmap
   CBitmapHandle m_hOldBitmap;  // Originally selected bitmap
   RECT          m_rc;          // Rectangle of drawing area

   CMemDC(HDC hDC, LPRECT pRect = NULL)
   {
      ATLASSERT(hDC!=NULL);
      m_dc = hDC;
      if( pRect != NULL ) m_rc = *pRect; else m_dc.GetClipBox(&m_rc);

      CreateCompatibleDC(m_dc);
      ::LPtoDP(m_dc, (LPPOINT) &m_rc, sizeof(RECT)/sizeof(POINT));
      m_bitmap.CreateCompatibleBitmap(m_dc, m_rc.right-m_rc.left, m_rc.bottom-m_rc.top);
      m_hOldBitmap = SelectBitmap(m_bitmap);
      ::DPtoLP(m_dc, (LPPOINT) &m_rc, sizeof(RECT)/sizeof(POINT));
      SetWindowOrg(m_rc.left, m_rc.top);
   }
   ~CMemDC()
   {
      // Copy the offscreen bitmap onto the screen.
      m_dc.BitBlt(m_rc.left, m_rc.top, m_rc.right-m_rc.left, m_rc.bottom-m_rc.top,
                  m_hDC, m_rc.left, m_rc.top, SRCCOPY);
      //Swap back the original bitmap.
      SelectBitmap(m_hOldBitmap);
   }
};

#endif // _CMemDC_
