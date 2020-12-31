/////////////////////////////////////////////////////////////////////////////
// TcxMsgBox.h
//
// Implements the extended Message Box class.
//
// xx-Nov-98 Thales P. Carvalho
// Created.
//

#include "stdafx.h"
#include "TcxMsgBox.h"
#include <RichEdit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Local constants

//
// Dialog template - to use with InitModalIndirect.
//
// Note: the following code was used to dump this binary data
//
//    void DumpDlgRes( UINT uIDD )
//    {
//       HMODULE hMod = AfxGetResourceHandle();
//
//       HRSRC hRsrc = ::FindResource( hMod,
//          MAKEINTRESOURCE(uIDD), RT_DIALOG );
//   
//       HGLOBAL hData = ::LoadResource( hMod, hRsrc );
//       LPBYTE pData = (LPBYTE)::LockResource( hData );
//       DWORD dwcData = ::SizeofResource( hMod, hRsrc );
//
//       for( DWORD i = 0; i < dwcData; ++i )
//       {
//          if( i % 16 == 0 )
//             TRACE( "\n" );
//
//          TRACE( "0x%02x, ", pData[i] );
//       }
//    }
//

static const BYTE _dlgData[] =
{
   0x01, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
   0xc0, 0x00, 0xc8, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb9, 0x00,
   0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x08, 0x00,
   0x00, 0x00, 0x00, 0x01, 0x4d, 0x00, 0x53, 0x00, 0x20, 0x00, 0x53, 0x00, 
   0x61, 0x00, 0x6e, 0x00, 0x73, 0x00, 0x20, 0x00, 0x53, 0x00, 0x65, 0x00,
   0x72, 0x00, 0x69, 0x00, 0x66, 0x00, 0x00, 0x00,
};


/////////////////////////////////////////////////////////////////////////////
// Local utility functions

//
// RTF edit control StreamIn's callback function
//    - see CRichEditCtrl::StreamIn
//
static DWORD CALLBACK _LoadRtfCallback(
   DWORD dwCookie,      // (in) pointer to the string
   LPBYTE pbBuff,       // (in) pointer to the destination buffer
   LONG cb,             // (in) size in bytes of the destination buffer
   LONG FAR *pcb        // (out) number of bytes transfered
   )
{
   LPCTSTR pszMsg = (LPCTSTR)dwCookie;

   // number of bytes to copy
   *pcb = _tcslen( pszMsg ) * sizeof(TCHAR);

   // limiting it up to the buffer's size
   if( *pcb > cb )
      *pcb = cb;

   // copying the string to the buffer
   memcpy( pbBuff, pszMsg, *pcb );

   // advancing to the end of the string
   pszMsg += *pcb / sizeof(TCHAR);

   // if it's the end of the string, returns NULL;
   // otherwise, returns a pointer to the next char to transfer as the cookie
   return ( *pszMsg != '\0' ) ? (DWORD)pszMsg : NULL;
}

static BOOL _LoadStringEx( LPCTSTR pszResId, LPCTSTR pszRsType, CString& strOut )
{
   HINSTANCE hInst = ::AfxFindResourceHandle( pszResId, pszRsType );
   
   if( hInst == NULL )
      return FALSE;

   HRSRC hRsrc = ::FindResource( hInst, pszResId, pszRsType );

   if( hRsrc == NULL )
      return FALSE;

   HGLOBAL hGlobal = ::LoadResource( hInst, hRsrc );

	if (hGlobal == NULL)
		return FALSE;

   const BYTE* pData = (const BYTE*)::LockResource( hGlobal );
   DWORD dwSize = ::SizeofResource( hInst, hRsrc );
   
   if( pData == NULL )
      return FALSE;

   CString str( (LPCTSTR)pData, dwSize );
   strOut = str;

   ::UnlockResource( hGlobal );
   ::FreeResource( hGlobal );

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox

// Constructor
CTcxMsgBox::CTcxMsgBox(
   CWnd* pParentWnd     // parent window (NULL for main window)
   ) :
   m_uDefCmdId( (UINT)IDC_STATIC ),
   m_uEscCmdId( (UINT)IDC_STATIC ),
   m_bRtf( FALSE ),
   m_hIcon( NULL ),
   m_strTitle( AfxGetApp()->m_pszAppName )
{
   m_pParentWnd = pParentWnd;

   // default metric values
   const int _aDefMetrics[NUM_OF_METRICS] =
   {
      10,   // CX_LEFT_BORDER,
      10,   // CX_RIGHT_BORDER,      
      10,   // CY_TOP_BORDER,
      7,    // CY_BOTTOM_BORDER,

      10,   // CX_ICON_MSG_SPACE,
      7,    // CY_BTNS_MSG_SPACE,

      7,    // CX_BTN_BORDER,
      4,    // CY_BTN_BORDER,

      7,    // CX_BTNS_SPACE,
      40,   // CX_MIN_BTN,
   };

   for( int i = 0; i < NUM_OF_METRICS; ++i )
      m_aMetrics[i] = _aDefMetrics[i];
}


// Destructor
CTcxMsgBox::~CTcxMsgBox()
{
}


// Replaces CDialog::DoModal
int CTcxMsgBox::DoModal()
{
   InitModalIndirect( (LPCDLGTEMPLATE)_dlgData, m_pParentWnd );
   return CDialog::DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox - Button operations

// Add a button
void CTcxMsgBox::AddButton(
   UINT uIDC,           // button command ID
   BOOL bIsDefault,     // set the button as default
   BOOL bIsEscape,      // return this command if user press escape
   LPCTSTR pszText      // button text
   )
{
   ASSERT( uIDC != (UINT)IDC_STATIC );

   BTNDATA btndata;
   btndata.uIDC = uIDC;
   btndata.strBtn = pszText;

   int iBtn = m_aBtns.Add( btndata );

   if( bIsEscape )
      m_uEscCmdId = uIDC;

   if( bIsDefault )
      m_uDefCmdId = uIDC;
}

// Add a button
void CTcxMsgBox::AddButton(
   UINT uIDC,           // button command ID
   BOOL bIsDefault,     // set the button as default
   BOOL bIsEscape,      // return this command if user press escape
   UINT uIdText         // string ID of button's text
   )
{
   CString str;

   if( uIdText == (UINT)-1 )
      uIdText = uIDC;

   VERIFY( str.LoadString( uIdText ) );

   AddButton( uIDC, bIsDefault, bIsEscape, str );
}

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox - Plain text operations

BOOL CTcxMsgBox::SetMsg( UINT uMsgId )
{
   return m_strMsg.LoadString( uMsgId );
}

BOOL CTcxMsgBox::SetMsg( LPCTSTR pszMsg )
{
   m_strMsg = pszMsg;
   return TRUE;
}

BOOL CTcxMsgBox::SetMsgEx( LPCTSTR pszMsgResId, LPCTSTR pszMsgResType )
{
   return _LoadStringEx( pszMsgResId, pszMsgResType, m_strMsg );
}

BOOL CTcxMsgBox::FormatMsg( LPCTSTR pszFmt, ... )
{
   va_list marker;
   
   va_start( marker, pszFmt );
   
      BOOL bOK = FormatMsgV( pszFmt, marker );
   
   va_end( marker );

   return bOK;
}

BOOL CTcxMsgBox::FormatMsg( UINT uFmtStrId, ... )
{
   CString strFmt;
   if( !strFmt.LoadString( uFmtStrId ) )
      return FALSE;

   va_list marker;

   va_start( marker, uFmtStrId );

      BOOL bOK = FormatMsgV( strFmt, marker );

   va_end( marker );

   return bOK;
}

BOOL CTcxMsgBox::FormatMsgEx( LPCTSTR pszMsgResId, LPCTSTR pszMsgResType, ... )
{
   CString strFmt;
   if( !_LoadStringEx( pszMsgResId, pszMsgResType, strFmt ) )
      return FALSE;

   va_list marker;

   va_start( marker, pszMsgResType );

      BOOL bOK = FormatMsgV( strFmt, marker );

   va_end( marker );

   return bOK;
}

BOOL CTcxMsgBox::FormatMsgV( LPCTSTR pszFmt, va_list marker )
{
   XString str;
   str.FormatV( pszFmt, marker );
   m_strMsg = str;
   return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox - Icon operations

void CTcxMsgBox::SetIcon( HICON hIcon )
{
   m_hIcon = hIcon;

   if( m_hIcon != NULL )
   {
      // loading the icon and extracting it's dimensions
      ICONINFO ii;
      GetIconInfo( m_hIcon, &ii );

      BITMAP bm;
      GetObject( ii.hbmColor, sizeof(bm), &bm );
      
      m_dimIcon.cx = bm.bmWidth;
      m_dimIcon.cy = bm.bmHeight;
   }
   else
   {
      m_dimIcon.cx = 0;
      m_dimIcon.cy = 0;
   }
}

void CTcxMsgBox::SetIcon( UINT uIcon )
{
   SetIcon( AfxGetApp()->LoadIcon( uIcon ) );
}

void CTcxMsgBox::SetStandardIcon( LPCTSTR pszIconName )
{
   SetIcon( AfxGetApp()->LoadStandardIcon( pszIconName ) );
}

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox - Overrides

BOOL CTcxMsgBox::OnInitDialog()
{
   if( !CDialog::OnInitDialog() )
      return FALSE;

   SetWindowText( m_strTitle );

   // Getting the base dialog unit used in pixel <-> d.u. conversion
   
   CRect rc( 0, 0, CX_DLGUNIT_BASE, CY_DLGUNIT_BASE );
   MapDialogRect( rc );

   m_dimDlgUnit = rc.Size();

   // Creating the nested controls

   CreateRtfCtrl();
   CreateIcon();
   CreateBtns();

   // Updating the layout - preparing to show

   UpdateLayout();

   // Disabling the ESC key

   if( m_uEscCmdId == (UINT)IDC_STATIC )
      ModifyStyle( WS_SYSMENU, NULL );

   // Focusing and setting the defaul button
   if( m_uDefCmdId != (UINT)IDC_STATIC )
   {
      GetDlgItem( m_uDefCmdId )->SetFocus();
      SetDefID( m_uDefCmdId );

      return FALSE;
   }

   return TRUE;
}


BOOL CTcxMsgBox::OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
   if( message == WM_NOTIFY )
   {
      REQRESIZE* prr = (REQRESIZE*)lParam;
      if( prr->nmhdr.code == EN_REQUESTRESIZE )
      {
         // (1)
         // The rich edit control requested a resize.
         // Store the requested resize.
         m_dimMsg.cx = prr->rc.right - prr->rc.left;
         m_dimMsg.cy = prr->rc.bottom - prr->rc.top;

         *pResult = NULL;
         return TRUE;
      }
   }
   else if( message == WM_CLOSE )      
   {
      if( m_uEscCmdId != (UINT)IDC_STATIC )
         EndDialog( m_uEscCmdId );

      return TRUE;
   }

   return CDialog::OnWndMsg( message, wParam, lParam, pResult );
}


BOOL CTcxMsgBox::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
   if( pHandlerInfo == NULL && nID != (WORD)IDC_STATIC )
   {
      EndDialog( nID );     
      return TRUE;
   }

   return CDialog::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
}

BOOL CTcxMsgBox::PreTranslateMessage( MSG* pMsg )
{
   if( pMsg->message == WM_KEYDOWN )
   {
      if( pMsg->wParam == VK_RETURN )
      {
         CWnd* pWnd = GetFocus();
         
         if( pWnd != NULL )
         {
            UINT uIDC = (UINT)pWnd->GetDlgCtrlID();

            for( int i = 0; i < m_aBtns.GetSize(); ++i )
               if( m_aBtns[i].uIDC == uIDC )
               {
                  m_uDefCmdId = uIDC;
                  break;
               }
         }

         EndDialog( m_uDefCmdId );

         return TRUE;
      }
      else if( pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_CANCEL )
      {
         if( m_uEscCmdId != (UINT)IDC_STATIC )
            EndDialog( m_uEscCmdId );

         return TRUE;
      }
   }

   return CDialog::PreTranslateMessage( pMsg );
}

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox - Overrides

void CTcxMsgBox::CreateRtfCtrl()
{
   // Creating the Rich Edit control

   CRect rcDummy; // dimesion doesn't matter here

   m_edCtrl.Create( WS_CHILD|WS_VISIBLE|ES_LEFT|ES_MULTILINE|ES_READONLY,
      rcDummy, this, (UINT)IDC_STATIC );
   m_edCtrl.SetBackgroundColor( FALSE, ::GetSysColor( COLOR_3DFACE ) );
   m_edCtrl.SetFont( GetFont() );

   if( m_bRtf )
   {
      // Loading a RTF message
      EDITSTREAM es;
      es.dwCookie = (DWORD)(LPCTSTR)m_strMsg;
      es.dwError = 0;
      es.pfnCallback = _LoadRtfCallback;

      m_edCtrl.StreamIn( SF_RTF, es );
   }
   else
   {
      // Loading a plain text message
      m_edCtrl.SetWindowText( m_strMsg );
   }

   /////////////////////////////////////////////////////////
   // Calculating the best Rich Edit control dimension
   //
   // Note:
   //    There's no Rich Edit operation to get the minimum
   //    width it needs to show its contents without line
   //    breaks. However, given a width, we can check
   //    how much height it needs to show its text (see
   //    bottomless rich edit controls).
   //    We'll this mechanism to perform a binary search
   //    and find that best width value.

   m_edCtrl.SetEventMask( ENM_REQUESTRESIZE );

   m_dimMsg.cx = 0;
   m_dimMsg.cy = 0;

   // Performing a binary search for the best dimension

   int cxFirst = 0;
   int cxLast = ::GetSystemMetrics( SM_CXFULLSCREEN );
   int cyMax = 0;

   do
   {
      // taking a guess
      int cx = ( cxFirst + cxLast ) / 2;

      // testing it
      CRect rc( 0, 0, cx, 1 );
      m_edCtrl.MoveWindow( rc );
      m_edCtrl.RequestResize();

      // if it's the first guess, take it anyway
      if( cyMax == 0 )
         cyMax = m_dimMsg.cy;
      
      // refining the guess
      if( m_dimMsg.cy > cyMax )
      {
         cxFirst = cx + 1;
      }
      else
      {
         cxLast = cx - 1;
      }
   }
   while( cxFirst < cxLast );
}


void CTcxMsgBox::CreateBtns()
{
   // The minimum button's dimension
   m_dimBtn = CSize( FromDlgX( m_aMetrics[CX_MIN_BTN] ), 0 );

   // DC and Font for use in some dimension calculations
   CClientDC dc( this );
   
   CFont* pWndFont = GetFont();
   dc.SelectObject( pWndFont );


   CRect rcDummy; // dimesion doesn't matter here

   int cBtns = m_aBtns.GetSize();

   for( int i = 0; i < cBtns; ++i )
   {
      BTNDATA& btndata = m_aBtns[i];

      // Finding the minimum dimension needed to
      // properly show any button

      CSize dimBtn = dc.GetTextExtent( btndata.strBtn );

      m_dimBtn.cx = max( m_dimBtn.cx, dimBtn.cx );
      m_dimBtn.cy = max( m_dimBtn.cy, dimBtn.cy );

      // Creating the button with MFC's CButton help.

      CButton btnCtrl;

      btnCtrl.Create( btndata.strBtn,
         WS_CHILD|WS_VISIBLE|WS_TABSTOP,
         rcDummy, this, btndata.uIDC );
      
      btnCtrl.SetFont( pWndFont );

      btnCtrl.UnsubclassWindow();
   }

   // Add the button margins
   m_dimBtn.cx += 2 * FromDlgX( m_aMetrics[CX_BTN_BORDER] );
   m_dimBtn.cy += 2 * FromDlgY( m_aMetrics[CY_BTN_BORDER] );
}


void CTcxMsgBox::CreateIcon()
{
   if( m_hIcon != NULL )
   {
      CRect rcDummy; // dimesion doesn't matter here

      // Creating the icon control
      m_stIconCtrl.Create( NULL, WS_CHILD|WS_VISIBLE|WS_DISABLED|SS_ICON, rcDummy, this );
      m_stIconCtrl.SetIcon( m_hIcon );
   }
}


// Converts d.u. in pixel (x axe)
int CTcxMsgBox::FromDlgX( int x )
   { return x * m_dimDlgUnit.cx / CX_DLGUNIT_BASE; }

// Converts d.u. in pixel (y axe)
int CTcxMsgBox::FromDlgY( int y )
   { return y * m_dimDlgUnit.cy / CY_DLGUNIT_BASE; }


// Updates the layout
void CTcxMsgBox::UpdateLayout()
{
   // Caching the borders
   int cxLeft = FromDlgX( m_aMetrics[CX_LEFT_BORDER] );
   int cxRight = FromDlgX( m_aMetrics[CX_RIGHT_BORDER] );   
   int cyTop = FromDlgY( m_aMetrics[CY_TOP_BORDER] );
   int cyBottom = FromDlgY( m_aMetrics[CY_BOTTOM_BORDER] );

   // Caching the space between buttons
   int cxBtnsSpace = FromDlgX( m_aMetrics[CX_BTNS_SPACE] );

   // The minimum dimensios of the client area
   // (starting with the message)
   CSize dimClient = m_dimMsg;
   int xMsg = 0;

   if( m_hIcon != NULL )
   {
      // Adding the icon
      xMsg = m_dimIcon.cx + FromDlgX( m_aMetrics[CX_ICON_MSG_SPACE] );

      dimClient.cx += xMsg;

      if( dimClient.cy < m_dimIcon.cy )
         dimClient.cy = m_dimIcon.cy;
   }

   xMsg += cxLeft;

   // Caching the minimum width needed for all buttons

   int cBtns = m_aBtns.GetSize();

   int cxBtns = 
      ( cBtns - 1 ) * FromDlgX( m_aMetrics[CX_BTNS_SPACE] ) +
      cBtns * m_dimBtn.cx;

   if( dimClient.cx < cxBtns )
      dimClient.cx = cxBtns;

   dimClient.cx += cxLeft + cxRight;
   dimClient.cy += cyTop + cyBottom + m_dimBtn.cy + FromDlgY( m_aMetrics[CY_BTNS_MSG_SPACE] );

   // Set client dimensions

   CRect rc( 0, 0, dimClient.cx, dimClient.cy );

   CalcWindowRect( rc );
   MoveWindow( rc );
   CenterWindow();

   // Icon layout
   
   if( m_hIcon != NULL )
      m_stIconCtrl.MoveWindow( cxLeft, cyTop, m_dimIcon.cx, m_dimIcon.cy );

   // Message layout

   m_dimMsg.cx += 2;
   xMsg = ( xMsg + dimClient.cx - cxRight - m_dimMsg.cx ) / 2;
   m_edCtrl.MoveWindow( xMsg, cyTop, m_dimMsg.cx, m_dimMsg.cy );

   // Buttons layout

   int x = ( dimClient.cx - cxBtns ) / 2;
   int y = dimClient.cy - cyBottom - m_dimBtn.cy;

   for( int i = 0; i < cBtns; ++i )
   {
      CWnd* pWndCtrl = GetDlgItem( m_aBtns[i].uIDC );
      pWndCtrl->MoveWindow( x, y, m_dimBtn.cx, m_dimBtn.cy );
      x += m_dimBtn.cx + cxBtnsSpace;
   }
}
