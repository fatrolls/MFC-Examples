/////////////////////////////////////////////////////////////////////
//  Module   : PANEL3D.CPP
//
//  Purpose  : Implementation of a custom panel control: CPanel3dCtrl
//
//  Comments : The panel 3d control is derived from class CButton 
//             and provides a panel that can be raised or lowered, 
//             resized, repostioned, and recolored, and the caption 
//             text changed and realigned.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-09-96
/////////////////////////////////////////////////////////////////////

#include "panel3d.h"

IMPLEMENT_DYNAMIC(CPanel3dCtrl, CButton)

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::CPanel3dCtrl() - constructor

CPanel3dCtrl::CPanel3dCtrl()
{ 
   m_bDrawBorder  = FALSE;
   m_bDrawText3d  = TRUE;
   m_taTextAlign  = taCenter;
   m_bsBevelStyle = bsInset;
   m_uBevelWidth  = 3;
   m_sCaption     = "Panel3dCtrl";
   m_Size.Left    = 0;
   m_Size.Top     = 0;
   m_Size.Width   = 0;
   m_Size.Height  = 0;
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::CreatePanel() - constructor

void CPanel3dCtrl::CreatePanel(CWnd* pParent, CString sCaption, 
   INT nID, BevelStyle bsBevelStyle, INT nLeft, INT nTop, 
   INT nWidth, INT nHeight)
{
   // Update object members with creation parameters specified
   m_sCaption     = sCaption;
   m_bsBevelStyle = bsBevelStyle;
   m_Size.Left    = nLeft;
   m_Size.Top     = nTop;
   m_Size.Width   = nWidth;
   m_Size.Height  = nHeight;

   // Create the panel control
   Create(sCaption, BS_PANEL3D,
      CRect(nLeft, nTop, nLeft + nWidth, nTop + nHeight), pParent, 
      nID);
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::~CPanel3dCtrl() - destructor

CPanel3dCtrl::~CPanel3dCtrl()
{  
}

//
// Attributes Methods
//

TextAlign CPanel3dCtrl::GetTextAlignment() 
   { return m_taTextAlign; }

CString& CPanel3dCtrl::GetCaption() 
   { return m_sCaption; }

INT CPanel3dCtrl::GetLeft() 
   { return m_Size.Left; }

INT CPanel3dCtrl::GetTop() 
   { return m_Size.Top; }

INT CPanel3dCtrl::GetWidth() 
   { return m_Size.Width; }

INT CPanel3dCtrl::GetHeight() 
   { return m_Size.Height; }

inline void CPanel3dCtrl::SetBevelStyle(BevelStyle bsBevelStyle)
   {  m_bsBevelStyle = bsBevelStyle; }

void CPanel3dCtrl::SetBorderFlag(BOOL bDrawBorder)
   { m_bDrawBorder = bDrawBorder; }

void CPanel3dCtrl::SetText3dFlag(BOOL bDrawText3d)
   { m_bDrawText3d = bDrawText3d; }

void CPanel3dCtrl::SetBevelWidth(UINT uBevelWidth)
   { m_uBevelWidth = uBevelWidth; }

void CPanel3dCtrl::SetCaption(CString sCaption)
   { m_sCaption = sCaption; }

void CPanel3dCtrl::SetLeft(INT nLeft)
{
   m_Size.Left = nLeft; 
   UpdateSize();
}

void CPanel3dCtrl::SetTop(INT nTop)
{ 
   m_Size.Top = nTop; 
   UpdateSize();
}

void CPanel3dCtrl::SetWidth(INT nWidth)
{ 
   m_Size.Width = nWidth; 
   UpdateSize();
}

void CPanel3dCtrl::SetHeight(INT nHeight)
{
   m_Size.Height = nHeight; 
   UpdateSize();
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::SetTextAlignment() 

void CPanel3dCtrl::SetTextAlignment(TextAlign taAlign)
{ 
   // Make sure the value is within valid range
   if ((taAlign < taLeftTop) || (taAlign > taRightBottom))
      return;

   // Set the new alignment 
   m_taTextAlign = taAlign;
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::UpdateSize() 

void CPanel3dCtrl::UpdateSize()
{ 
   // Update the window position
   this->SetWindowPos(0, GetLeft(), GetTop(), 
      GetWidth(), GetHeight(), 
      SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DrawItem() - Draw the Panel3d

void CPanel3dCtrl::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{  
   // Make sure the structure is ready for action
   ASSERT(lpDIS != NULL);

   // Get a pointer to a DC from the LPDRAWITEMSTRUCT
   CDC* pDC = CDC::FromHandle(lpDIS->hDC);
   
   // Get the client rect for the panel
   CRect  rc;
   this->GetClientRect(&rc);

   // Paint the panel rect
   pDC->FillSolidRect(&rc, ::GetSysColor(COLOR_3DFACE));

   // Draw the text caption
   DrawCaption(pDC, rc, lpDIS);
   
   // Draw bevel
   switch (m_bsBevelStyle)
   {
      case bsRaised:
         DrawBevelRaised(pDC, rc);
         break;

      case bsInset:
         DrawBevelInset(pDC, rc);
   }

   // Draw a black border if needed
   if (m_bDrawBorder)
   {
      CBrush brBorder(crBlack);
      pDC->FrameRect(&rc, &brBorder);
   }
}

// 
// Operations
//

void CPanel3dCtrl::Refresh()
   { this->Invalidate(); }

//
// Helper Methods
//

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DrawBevel()

void CPanel3dCtrl::DrawBevel(CDC* pDC, CRect& rc, CPen& pen1, 
                             CPen& pen2)
{  
   // See if we need a bevel at all
   if (m_bsBevelStyle == bsNone)
      return;

   //
   // Draw the bevel top and left
   //

   UINT uBevelWidth = m_uBevelWidth;  

   // Bevel width is one more than m_uBevelWidth if drawing a border   
   if (m_bDrawBorder)
      uBevelWidth = m_uBevelWidth + 1;

   // The top
   INT cxLeft  = rc.left;
   INT cy      = rc.top;
   INT cxRight = rc.right + 1;

   // Select a new pen into the DC for drawing, save the old pen
   CPen* ppenOld = pDC->SelectObject(&pen1);
   
   // Draw the bevel
   for (UINT i = 0; i < uBevelWidth; i++)
   {
      pDC->MoveTo(cxLeft++, cy);
      pDC->LineTo(cxRight--, cy++);
   }

   // The left
   INT cx       = rc.left;
   INT cyTop    = rc.top;
   INT cyBottom = rc.bottom + 1;

   for (i = 0; i < uBevelWidth; i++)
   {
      pDC->MoveTo(cx, cyTop++);
      pDC->LineTo(cx++, cyBottom--);
   }

   //
   // Draw the bevel bottom and right
   //

   // The bottom
   cxLeft  = rc.left;
   cy      = rc.bottom - 1;
   cxRight = rc.right;

   // Select a new pen into the DC for drawing
   pDC->SelectObject(pen2);

   // Draw the bevel
   for (i = 0; i < uBevelWidth; i++)
   {
      pDC->MoveTo(cxLeft++, cy);
      pDC->LineTo(cxRight--, cy--);
   }

   // The right
   cx       = rc.right - 1;
   cyTop    = rc.top;
   cyBottom = rc.bottom;

   for (i = 0; i < uBevelWidth; i++)
   {
      pDC->MoveTo(cx, cyTop++);
      pDC->LineTo(cx--, cyBottom--);
   }

   // Restore the original pen
   pDC->SelectObject(ppenOld);
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DrawBevelRaised()

void CPanel3dCtrl::DrawBevelRaised(CDC* pDC, CRect& rc)
{
   CPen penLight(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));
   CPen penShadow(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

   DrawBevel(pDC, rc, penLight, penShadow);
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DrawBevelInset()

void CPanel3dCtrl::DrawBevelInset(CDC* pDC, CRect& rc)
{
   CPen penLight(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));
   CPen penShadow(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

   DrawBevel(pDC, rc, penShadow, penLight);
}

////////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DrawCaption()

void CPanel3dCtrl::DrawCaption(CDC* pDC, CRect& rc, 
                               LPDRAWITEMSTRUCT& lpDIS)
{
   CSize  size; 
   INT    cx     = 0;
   INT    cy     = 0;
   INT    nExtra = 2;

   // Get the bounds of the caption text
   ::GetTextExtentPoint32( 
      lpDIS->hDC,              // handle of device context 
      m_sCaption,              // address of text string 
      m_sCaption.GetLength(),  // number of characters in string 
      &size);                  // address of size structure  

   //
   // Adjust bevel width to accommodate a border if needed
   // (bevel width is one more than m_uBevelWidth if drawing 
   // a border)...
   //
   UINT uBevelWidth = m_uBevelWidth;  
   
   if (m_bDrawBorder)
      uBevelWidth = m_uBevelWidth + 1;
   
   // Determine the current text alignment
   switch (m_taTextAlign)
   {
      case taLeftTop:
         cx = uBevelWidth + rc.left + nExtra;
         cy = uBevelWidth + rc.top + nExtra;
         break;

      case taLeftMid:
         cx = uBevelWidth + rc.left + nExtra;
         cy = (rc.top + rc.bottom) / 2 - size.cy / 2;
         break;

      case taLeftBottom: 
         cx = uBevelWidth + rc.left + nExtra;
         cy = rc.bottom - uBevelWidth - size.cy - nExtra;
         break;
      
      case taCenterTop:
         cx = (rc.left + rc.right) / 2 - size.cx / 2;
         cy = uBevelWidth + rc.top + nExtra;
         break;
      
      case taCenter:
         cx = (rc.left + rc.right) / 2 - size.cx / 2;
         cy = (rc.top + rc.bottom) / 2 - size.cy / 2;
         break;
      
      case taCenterBottom:
         cx = (rc.left + rc.right) / 2 - size.cx / 2;
         cy = rc.bottom - uBevelWidth - size.cy - nExtra;
         break;
      
      case taRightTop:
         cx = rc.right - uBevelWidth - size.cx - nExtra;
         cy = uBevelWidth + rc.top + nExtra;
         break;
      
      case taRightMid:
         cx = rc.right - uBevelWidth - size.cx - nExtra;
         cy = (rc.top + rc.bottom) / 2 - size.cy / 2;
         break;
      
      case taRightBottom:
         cx = rc.right - uBevelWidth - size.cx - nExtra;
         cy = rc.bottom - uBevelWidth - size.cy - nExtra;
         break;

      default:  // Default to taCenterMid
         cx = (rc.left + rc.right) / 2 - size.cx / 2;
         cy = (rc.top + rc.bottom) / 2 - size.cy / 2;
   }
   
   // Make text background transparent
   pDC->SetBkMode(TRANSPARENT);

   // If not using "3d" text
   if (!m_bDrawText3d)
   {  
      // Set the panel caption
      pDC->TextOut(cx, cy, m_sCaption);
      return;
   }

   //
   // OK, draw caption as "3d" text
   //
   
   // The etched highlight
   pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
   pDC->TextOut(cx + 2, cy + 2, m_sCaption);

   // The regular text
   pDC->SetTextColor(crBlack);
   pDC->TextOut(cx, cy, m_sCaption);
}

////////////////////////////////////////////////////////////////////
