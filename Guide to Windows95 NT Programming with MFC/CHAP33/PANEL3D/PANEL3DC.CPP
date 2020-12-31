///////////////////////////////////////////////////////////////////
//  Module  : PANEL3DC.CPP
//
//  Purpose : Implementation of the CPanel3dCtrl OLE control class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-10-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "panel3d.h"
#include "panel3dc.h"
#include "panel3dp.h"
#include "colors.h"    // Lots of custom colors

IMPLEMENT_DYNCREATE(CPanel3dCtrl, COleControl)

///////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPanel3dCtrl, COleControl)
	DISP_PROPERTY_NOTIFY(CPanel3dCtrl, "TextAlignment", 
      m_textAlignment, OnTextAlignmentChanged, VT_I2)
	
   DISP_PROPERTY_NOTIFY(CPanel3dCtrl, "BevelWidth", 
      m_bevelWidth, OnBevelWidthChanged, VT_I2)
	
   DISP_PROPERTY_NOTIFY(CPanel3dCtrl, "BevelStyle", 
      m_bevelStyle, OnBevelStyleChanged, VT_I2)

	DISP_PROPERTY_NOTIFY(CPanel3dCtrl, "DrawText3d", 
      m_drawText3d, OnDrawText3dChanged, VT_BOOL)

	DISP_PROPERTY_NOTIFY(CPanel3dCtrl, "DrawBorder", 
      m_drawBorder, OnDrawBorderChanged, VT_BOOL)

	DISP_DEFVALUE(CPanel3dCtrl, "Caption")
	DISP_STOCKPROP_CAPTION()

	DISP_FUNCTION_ID(CPanel3dCtrl, "AboutBox", DISPID_ABOUTBOX, 
      AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

///////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CPanel3dCtrl, 1)
	PROPPAGEID(CPanel3dPropPage::guid)
END_PROPPAGEIDS(CPanel3dCtrl)

///////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPanel3dCtrl, "PANEL3D.Panel3dCtrl.1",
	0xaf51a703, 0xd9ac, 0x11cf, 0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 
     0, 0)

///////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPanel3dCtrl, _tlid, _wVerMajor, _wVerMinor)

///////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPanel3d =
{ 
   0x4d85cc82, 0xd9c6, 0x11cf, 
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0 
   } 
};

const IID BASED_CODE IID_DPanel3dEvents =
{ 
   0x4d85cc83, 0xd9c6, 0x11cf, 
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0 
   } 
};

///////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPanel3dOleMisc =
	OLEMISC_SIMPLEFRAME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPanel3dCtrl, IDS_PANEL3D, _dwPanel3dOleMisc)

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl::CPanel3dCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPanel3dCtrl

BOOL CPanel3dCtrl::CPanel3dCtrlFactory::UpdateRegistry(BOOL bReg)
{
	if (bReg)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PANEL3D,
			IDB_PANEL3D,
			afxRegApartmentThreading,
			_dwPanel3dOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl::CPanel3dCtrl() - Constructor

CPanel3dCtrl::CPanel3dCtrl()
{
	InitializeIIDs(&IID_DPanel3d, &IID_DPanel3dEvents);
	
   // Support visual (not OLE) containment of other controls
   EnableSimpleFrame();
}

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl::~CPanel3dCtrl() - Destructor

CPanel3dCtrl::~CPanel3dCtrl()
{
}

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl::OnDraw - Drawing function

void CPanel3dCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
   DrawControl(*pdc);
}

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DoPropExchange - Persistence support

void CPanel3dCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_* functions for each persistent custom property
   PX_Short(pPX, _T("BevelWidth"), m_bevelWidth, 2);
   PX_Short(pPX, _T("BevelStyle"), m_bevelStyle, bsInset);
   PX_Short(pPX, _T("TextAlignment"), m_textAlignment, taCenter);
   PX_Bool(pPX, _T("DrawText3d"), m_drawText3d, FALSE);
   PX_Bool(pPX, _T("DrawBorder"), m_drawBorder, FALSE);
}

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl::AboutBox - Display an "About" box to the user

void CPanel3dCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_PANEL3D);
	dlgAbout.DoModal();
}

///////////////////////////////////////////////////////////////////
// CPanel3dCtrl message handlers

void CPanel3dCtrl::OnBevelWidthChanged() 
{
   InvalidateControl();
	SetModifiedFlag();
}

void CPanel3dCtrl::OnBevelStyleChanged() 
{
   InvalidateControl();
	SetModifiedFlag();
}

void CPanel3dCtrl::OnDrawText3dChanged() 
{
   InvalidateControl();
	SetModifiedFlag();
}

void CPanel3dCtrl::OnDrawBorderChanged() 
{
   InvalidateControl();
	SetModifiedFlag();
}

void CPanel3dCtrl::OnTextAlignmentChanged() 
{
   InvalidateControl();
	SetModifiedFlag();
}

//////////////////////////////////////////////////////////////////
// Helper Methods
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// CPanel3dCtrl::DrawBevel()

void CPanel3dCtrl::DrawBevel(CDC* pDC, CRect& rc, CPen& pen1, 
                             CPen& pen2)
{  
   // See if we need a bevel at all
   if (m_bevelStyle == bsNone)
      return;

   //
   // Draw the bevel top and left
   //

   UINT uBevelWidth = m_bevelWidth;  

   // Bevel width is one more than m_uBevelWidth if drawing border   
   if (m_drawBorder)
      uBevelWidth = m_bevelWidth + 1;

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

void CPanel3dCtrl::DrawCaption(CDC* pDC, CRect& rc, HDC hDC)
{
   CSize   size; 
   INT     cx     = 0;
   INT     cy     = 0;
   INT     nExtra = 2;
   CString strCaption = InternalGetText();

   // Get the bounds of the caption text
   ::GetTextExtentPoint32( 
      hDC,                     // handle of device context 
      strCaption,              // address of text string 
      strCaption.GetLength(),  // number of characters in string 
      &size);                  // address of size structure  

   //
   // Adjust bevel width to accommodate a border if needed
   // (bevel width is one more than m_uBevelWidth if drawing 
   // a border)...
   //
   UINT uBevelWidth = m_bevelWidth;  
   
   if (m_drawBorder)
      uBevelWidth = m_bevelWidth + 1;
   
   // Determine the current text alignment
   switch (m_textAlignment)
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
   if (!m_drawText3d)
   {  
      // Set the panel caption
      pDC->TextOut(cx, cy, strCaption);
      return;
   }

   //
   // OK, draw caption as "3d" text
   //
   
   // The etched highlight
   pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
   pDC->TextOut(cx + 2, cy + 2, strCaption);

   // The regular text
   pDC->SetTextColor(crBlack);
   pDC->TextOut(cx, cy, strCaption);
}

void CPanel3dCtrl::DrawControl(CDC& dc)
{
   // Get the client area for the control
   CRect rc;
   GetClientRect(&rc);

   // Paint the panel rect
   dc.FillSolidRect(&rc, ::GetSysColor(COLOR_3DFACE));

   // Draw the text caption
   DrawCaption(&dc, rc, dc.GetSafeHdc());
   
   // Draw bevel
   switch (m_bevelStyle)
   {
      case bsRaised:
         DrawBevelRaised(&dc, rc);
         break;

      case bsInset:
         DrawBevelInset(&dc, rc);
   }

   // Draw a black border if needed
   if (m_drawBorder)
   {
      CBrush brBorder(crBlack);
      dc.FrameRect(&rc, &brBorder);
   }
}

///////////////////////////////////////////////////////////////////
