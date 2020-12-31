////////////////////////////////////////////////////////////////////
//  Header  : PANEL3D.H
//
//  Purpose : Interface for the CPanel3dCtrl custom control.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 05-09-96
////////////////////////////////////////////////////////////////////

#ifndef __PANELCTL_H__
#define __PANELCTL_H__

#ifndef __AFXWIN_H__
   #include <afxwin.h>  // MFC core components
#endif

#ifndef __COLORS_H__
   #include <colors.h>  // Lots of predefined colors
#endif

////////////////////////////////////////////////////////////////////
//  Structures and enumerated types

typedef struct tagPANELSIZE
{
   INT Left;
   INT Top;
   INT Width;
   INT Height;
} 
PANELSIZE;

enum BevelStyle 
{ 
   bsRaised, bsInset, bsNone 
};   

enum TextAlign 
{ 
   taLeftTop,    taLeftMid,   taLeftBottom, 
   taCenterTop,  taCenter,    taCenterBottom,
   taRightTop,   taRightMid,  taRightBottom
};

// Define a new button style for the Panel3d control
#define BS_PANEL3D  (BS_OWNERDRAW | WS_VISIBLE | \
                     WS_CHILD | WS_CLIPCHILDREN)

////////////////////////////////////////////////////////////////////
// Derive a new CPanel3dCtrl control class from CButton 

class CPanel3dCtrl : public CButton
{ 
   DECLARE_DYNAMIC(CPanel3dCtrl)

// Protected data members
protected:
   BOOL       m_bDrawBorder;
   BOOL       m_bDrawText3d;
   BevelStyle m_bsBevelStyle;
   UINT       m_uBevelWidth;
   CString    m_sCaption;
   TextAlign  m_taTextAlign;
   PANELSIZE  m_Size;

// 2-step construction
public:
   // Constructor
   CPanel3dCtrl();

   // Initialization
   void CreatePanel(CWnd* pParent, CString sCaption, INT nID, 
      BevelStyle bsBevelStyle, INT nLeft, INT nTop, INT nWidth, 
      INT nHeight);

// Attributes
public:
   void SetBorderFlag(BOOL bDrawBorder);
   void SetText3dFlag(BOOL bDrawText3d);

   TextAlign GetTextAlignment();
   void SetTextAlignment(TextAlign taAlignment);

   void SetBevelStyle(BevelStyle bsBevelStyle);
   void SetBevelWidth(UINT uBevelWidth);

   void SetCaption(CString sCaption);
   CString& GetCaption();

   INT GetLeft();
   void SetLeft(INT nLeft);

   INT GetTop();
   void SetTop(INT nTop);

   INT GetWidth();
   void SetWidth(INT nWidth);

   INT GetHeight();
   void SetHeight(INT nHeight);

// Operations
public:
   virtual void Refresh();

protected:
   virtual void UpdateSize();
   virtual void DrawBevel(CDC* pDC, CRect& rc, 
      CPen& pen1, CPen& pen2);
   virtual void DrawBevelInset(CDC* pDC, CRect& rc);
   virtual void DrawBevelRaised(CDC* pDC, CRect& rc);
   virtual void DrawCaption(CDC* pDC, CRect& rc, 
      LPDRAWITEMSTRUCT& lpDIS);

// Overridables (for owner draw only)
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

// Implementation
public:
   virtual ~CPanel3dCtrl();

};  // end CPanel3dCtrl

#endif // __PANELCTL_H__

////////////////////////////////////////////////////////////////////
