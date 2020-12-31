/////////////////////////////////////////////////////////////////////////////
// TcxMsgBox.h
//
// Defines a extended Message Box class with fancy features as:
// - Rich Text Format support
// - Customizable buttons
// - Customizable icon
//
// xx-Nov-98 Thales P. Carvalho
// Created.
//

#ifndef TCXMSGBOX_H
#define TCXMSGBOX_H

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif __AFXTEMPL_H__

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox

class CTcxMsgBox : private CDialog
{
// Basic
public:

// Constructor
   CTcxMsgBox( CWnd* pParentWnd = NULL );

// Destructor
   virtual ~CTcxMsgBox();

// Execute
   int DoModal();

// Buttons operations
   void AddButton( UINT uIDC, BOOL bIsDefault, BOOL bIsEscape, LPCTSTR pszText );
   void AddButton( UINT uIDC, BOOL bIsDefault, BOOL bIsEscape, UINT uIdText = (UINT)-1 );

// Title operations
   void SetTitle( LPCTSTR pszTitle );
   void SetTitle( UINT uIdTitle );

// RTF Selection
   void SetRtf( BOOL bRtf = TRUE );

// Message operations
   BOOL SetMsg( UINT uMsgId );
   BOOL SetMsg( LPCTSTR pszMsg );
   BOOL SetMsgEx( LPCTSTR pszMsgResId, LPCTSTR pszMsgResType );
   BOOL FormatMsg( LPCTSTR pszFmt, ... );
   BOOL FormatMsg( UINT uFmtStrId, ... );
   BOOL FormatMsgEx( LPCTSTR pszMsgResId, LPCTSTR pszMsgResType, ... );
   BOOL FormatMsgV( LPCTSTR pszFmt, va_list marker );

// Icon operations
   void SetIcon( HICON hIcon );
   void SetIcon( UINT uIcon );
   void SetStandardIcon( LPCTSTR pszIconName );

// Metric enumerators (see SetMetric and GetMetric)
   enum
   {
      CX_LEFT_BORDER,
      CX_RIGHT_BORDER,      
      CY_TOP_BORDER,
      CY_BOTTOM_BORDER,

      CX_ICON_MSG_SPACE,
      CY_BTNS_MSG_SPACE,

      CX_BTN_BORDER,
      CY_BTN_BORDER,

      CX_BTNS_SPACE,
      CX_MIN_BTN,

      NUM_OF_METRICS
   };

// Set a metric (in dialog units)
   void SetMetric( int iMetric, int xy );

// Get a metric (in dialog units)
   int GetMetric( int iMetric );

private:

// CString help class (grants access to CString's FormatV)
   class XString : public CString
   {
   public:

      inline void FormatV( LPCTSTR pszFmt, va_list argList )
         { CString::FormatV( pszFmt, argList ); }
   };

// Graphical attributes
   int m_aMetrics[NUM_OF_METRICS];  // basic metrics (dialog units)
   CSize m_dimMsg;                  // message dimension (pixels)
   CSize m_dimBtn;                  // button dimension (pixels)
   CSize m_dimIcon;                 // icon dimension (pixels)

// Dialog unit base: dimensions used in d.u. <-> pixel conversion
   enum
   {
      CX_DLGUNIT_BASE = 1000,
      CY_DLGUNIT_BASE = 1000,
   };

// Pixel dimensions of the dialog unit base
   CSize m_dimDlgUnit;

// Controls' attributes
   UINT m_uDefCmdId;          // default command ID: <Return>
   UINT m_uEscCmdId;          // escape command ID: <ESC> or box close
   CStatic m_stIconCtrl;      // the icon control
   CRichEditCtrl m_edCtrl;    // the RTF control
   
// Button's attributes
   struct BTNDATA
   {
      UINT uIDC;                    // button ID
      CString strBtn;               // button Text
   };

   CArray<BTNDATA,const BTNDATA&> m_aBtns;   // buttons' attributes

// Message attributes
   BOOL m_bRtf;                     // TRUE if it's a RTF message
   HICON m_hIcon;                   // icon handle
   CString m_strMsg;                // the message
   CString m_strTitle;              // the title

// Overrides
   virtual BOOL OnInitDialog();
   virtual BOOL OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult );
   virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
   virtual BOOL PreTranslateMessage( MSG* pMsg );

// Utility - creating the nested controls
   void CreateRtfCtrl();
   void CreateBtns();
   void CreateIcon();

   void UpdateLayout();

   int FromDlgX( int x );
   int FromDlgY( int y );
};

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBox - inlined member functions

inline void CTcxMsgBox::SetTitle( LPCTSTR pszTitle )
   { m_strTitle = pszTitle; }

inline void CTcxMsgBox::SetTitle( UINT uIdTitle )
   { VERIFY( m_strTitle.LoadString( uIdTitle ) ); }

inline void CTcxMsgBox::SetRtf( BOOL bRtf )
   { m_bRtf = bRtf; }

inline void CTcxMsgBox::SetMetric( int iMetric, int nValue )
   {  ASSERT( 0 <= iMetric && iMetric < NUM_OF_METRICS );
      m_aMetrics[iMetric] = nValue; }

inline int CTcxMsgBox::GetMetric( int iMetric )
   {  ASSERT( 0 <= iMetric && iMetric < NUM_OF_METRICS );
      return m_aMetrics[iMetric]; }

/////////////////////////////////////////////////////////////////////////////

#endif TCXMSGBOX_H
