///////////////////////////////////////////////////////////////////
//  Module  : JIGGLERC.CPP
//
//  Purpose : Implementation of the CJigglerCtrl OLE control class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-27-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Jiggler.h"
#include "JigglerC.h"
#include "JigglerP.h"
#include <random.h>

IMPLEMENT_DYNCREATE(CJigglerCtrl, COleControl)

// Default OLE font for the control
static const FONTDESC _fontdescDefault =
{
   sizeof(FONTDESC), OLESTR("Arial"), FONTSIZE(24),
   FW_NORMAL, ANSI_CHARSET, FALSE, FALSE, FALSE
};

///////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJigglerCtrl, COleControl)
   //{{AFX_MSG_MAP(CJigglerCtrl)
   ON_WM_CREATE()
   ON_WM_DESTROY()
   ON_WM_TIMER()
   //}}AFX_MSG_MAP
   ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
   ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CJigglerCtrl, COleControl)
   //{{AFX_DISPATCH_MAP(CJigglerCtrl)
   DISP_PROPERTY_NOTIFY(CJigglerCtrl, "Interval", m_nInterval, OnIntervalChanged, VT_I2)
   DISP_PROPERTY_EX(CJigglerCtrl, "DefaultFont", GetDefaultFont, SetDefaultFont, VT_FONT)
   DISP_DEFVALUE(CJigglerCtrl, "Caption")
   DISP_STOCKFUNC_REFRESH()
   DISP_STOCKPROP_READYSTATE()
   DISP_STOCKPROP_CAPTION()
   DISP_STOCKPROP_BACKCOLOR()
   DISP_STOCKPROP_FORECOLOR()
   //}}AFX_DISPATCH_MAP
   DISP_FUNCTION_ID(CJigglerCtrl, "AboutBox", DISPID_ABOUTBOX, 
      AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

///////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CJigglerCtrl, COleControl)
   //{{AFX_EVENT_MAP(CJigglerCtrl)
   // NOTE - ClassWizard will add and remove event map entries
   //  DO NOT EDIT what you see in these blocks of generated code!
   EVENT_STOCK_READYSTATECHANGE()
   //}}AFX_EVENT_MAP
END_EVENT_MAP()

///////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CJigglerCtrl, 3)
   PROPPAGEID(CJigglerPropPage::guid)
   PROPPAGEID(CLSID_CColorPropPage)
   PROPPAGEID(CLSID_CFontPropPage)
END_PROPPAGEIDS(CJigglerCtrl)

///////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJigglerCtrl, "JIGGLER.JigglerCtrl.1",
   0x5cd2fc83, 0xe7bd, 0x11cf, 0xa3, 0xbc, 0x44, 0x45, 0x53, 
   0x54, 0, 0)

///////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CJigglerCtrl, _tlid, _wVerMajor, _wVerMinor)

///////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DJiggler =
{ 
   0x5cd2fc81, 0xe7bd, 0x11cf, 
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0 
   } 
};

const IID BASED_CODE IID_DJigglerEvents =
{
   0x5cd2fc82, 0xe7bd, 0x11cf,
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0 
   } 
};

///////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwJigglerOleMisc =
   OLEMISC_ACTIVATEWHENVISIBLE |
   OLEMISC_SETCLIENTSITEFIRST |
   OLEMISC_INSIDEOUT |
   OLEMISC_CANTLINKINSIDE |
   OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CJigglerCtrl, IDS_JIGGLER, _dwJigglerOleMisc)

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::CJigglerCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CJigglerCtrl

BOOL CJigglerCtrl::CJigglerCtrlFactory::UpdateRegistry(
   BOOL bRegister)
{
   if (bRegister)
      return AfxOleRegisterControlClass(
         AfxGetInstanceHandle(),
         m_clsid,
         m_lpszProgID,
         IDS_JIGGLER,
         IDB_JIGGLER,
         afxRegInsertable | afxRegApartmentThreading,
         _dwJigglerOleMisc,
         _tlid,
         _wVerMajor,
         _wVerMinor);
   else
      return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::CJigglerCtrl - Constructor

CJigglerCtrl::CJigglerCtrl() : m_fontDefault(&m_xFontNotification)
{
   InitializeIIDs(&IID_DJiggler, &IID_DJigglerEvents);

   m_lReadyState = READYSTATE_LOADING;
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::DoPropExchange - Persistence support

void CJigglerCtrl::DoPropExchange(CPropExchange* pPX)
{
   ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
   
   // Set a default caption
   if (InternalGetText() == "")
      SetText(_T("ActiveX Jiggler!!"));
   
   COleControl::DoPropExchange(pPX);

   // Property exchange for default font
   PX_Font(pPX, _T("DefaultFont"), m_fontDefault, 
      &_fontdescDefault);

   // Call PX_* functions for each persistent custom property
   PX_Short(pPX, _T("Interval"), m_nInterval, 100);
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::AboutBox - Display an "About" box to the user

void CJigglerCtrl::AboutBox()
{
   CDialog dlgAbout(IDD_ABOUTBOX_JIGGLER);
   dlgAbout.DoModal();
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::JiggleText() - The meat of the control!

void CJigglerCtrl::JiggleText()
{
   // Get the client DC
   CClientDC dc(this);

   // Prepare a memory DC for holding a memory bitmap
   CDC dcMem;
   dcMem.CreateCompatibleDC(&dc);

   // Get the current caption text and text length
   const CString& strText = InternalGetText();
   int nMsgLen = strText.GetLength();

   // Select font and set transparent text mode, forecolor
   CFont* pFontOld = SelectFontObject(&dcMem, m_fontDefault);
   int nModeOld = dcMem.SetBkMode(TRANSPARENT);
   int crTextColorOldMem = dcMem.SetTextColor(
      TranslateColor(GetForeColor()));

   // Get the text char size for current font
   TEXTMETRIC tm;
   dcMem.GetTextMetrics(&tm);

   int nTextHeight = tm.tmHeight + tm.tmExternalLeading * 2;
   int nAveCharWidth = (int)(tm.tmAveCharWidth * 1.5);

   // Get the bounding rect for the entire string (current font)
   int nCtrlWidth = nAveCharWidth * nMsgLen + (nAveCharWidth / 2);
   int nCtrlHeight = nTextHeight + (nTextHeight / 4);

   // Autosize the control to the text (if needed)
   int nWidth, nHeight;
   GetControlSize(&nWidth, &nHeight);
   CRect rcOld(0, 0, nCtrlWidth, nCtrlHeight);
   CRect rcCurrent(0, 0, nWidth, nHeight);

   if (rcCurrent != rcOld)
      SetControlSize(nCtrlWidth, nCtrlHeight);
   
   // Prepare a memory bitmap
   CBitmap bmp;
   bmp.CreateCompatibleBitmap(&dc, nCtrlWidth, nCtrlHeight);

   // Select the bitmap
   CBitmap* pbmpOld = dcMem.SelectObject(&bmp);

   // Fill with current background color
   CRect rc(0, 0, nCtrlWidth, nCtrlHeight);
   CBrush brBack(TranslateColor(GetBackColor()));
   dcMem.FillRect(&rc, &brBack);

   // Create a random number generating object
   CRand rand;
   
   // Jiggle the chars
   for (int i = 0; i < nMsgLen; i++)
   {
      CRect rc;
      UINT cx = rand.MapRand(nAveCharWidth) / 2;
      UINT cy = rand.MapRand(nTextHeight) / 4;

      rc.left   = (nAveCharWidth * i) + cx;
      rc.right  = rc.left + nAveCharWidth + cx;
      rc.top    = cy;
      rc.bottom = rc.top + nTextHeight + cy;

      // Draw next character on the bitmap
      dcMem.DrawText((CString)strText[i], rc, DT_CENTER);
   }

   // Blast bitmapped text to the window
   dc.BitBlt(0, 0, nCtrlWidth, nCtrlHeight, &dcMem, 0, 0, SRCCOPY);

   // Clean up
   dcMem.SelectObject(pbmpOld);
   dcMem.SelectObject(pFontOld);
   dcMem.SetTextColor(crTextColorOldMem);
   dcMem.SetBkMode(TranslateColor(nModeOld));
   bmp.DeleteObject();
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::OnCreate()

int CJigglerCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (COleControl::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   SetTimer(IDC_TIMER1, m_nInterval, NULL);
   return 0;
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::OnCreate()

void CJigglerCtrl::OnDestroy() 
{
   COleControl::OnDestroy();
   KillTimer(IDC_TIMER1);
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::OnTimer() - Jiggles text in response to WM_TIMER

void CJigglerCtrl::OnTimer(UINT nIDEvent) 
{
   if (nIDEvent == IDC_TIMER1)
      JiggleText();
   
   COleControl::OnTimer(nIDEvent);
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::OnIntervalChanged()

void CJigglerCtrl::OnIntervalChanged() 
{
   // Kill existing timer
   KillTimer(IDC_TIMER1);

   // Start with new interval
   SetTimer(IDC_TIMER1, m_nInterval, NULL);
   SetModifiedFlag();
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::GetDefaultFont()

LPFONTDISP CJigglerCtrl::GetDefaultFont() 
{
   return m_fontDefault.GetFontDispatch();
}

///////////////////////////////////////////////////////////////////
// CJigglerCtrl::SetDefaultFont()

void CJigglerCtrl::SetDefaultFont(LPFONTDISP newValue) 
{
   m_fontDefault.InitializeFont(&_fontdescDefault, newValue);
   OnFontChanged();
   SetModifiedFlag();
}

///////////////////////////////////////////////////////////////////






