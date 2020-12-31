/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

IMPLEMENT_DYNAMIC ( CColorStaticText , CStatic )

BEGIN_MESSAGE_MAP ( CColorStaticText , CStatic )
    ON_WM_NCHITTEST ( )
    ON_WM_CTLCOLOR_REFLECT ( )
END_MESSAGE_MAP ( )

#if _MSC_VER <= 1310
UINT CColorStaticText :: OnNcHitTest ( CPoint )
#else
LRESULT CColorStaticText :: OnNcHitTest ( CPoint )
#endif
{
    return ( HTCLIENT ) ;
}

HBRUSH CColorStaticText :: CtlColor ( CDC * pDC ,
                                      UINT /*nCtlColor*/ )
{
    //ASSERT ( nCtlColor == CTLCOLOR_STATIC ) ;
    DWORD dwStyle = GetStyle ( ) ;

    HBRUSH hbr = NULL ;
    if ( (dwStyle & 0xFF) <= SS_RIGHT )
    {

        pDC->SetTextColor(m_color);
        pDC->SetBkMode(TRANSPARENT);

        // return hollow brush to preserve parent background color
        hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
    }
    return hbr;
}

////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP ( CAboutDlg , CDialog )
END_MESSAGE_MAP ( )

CAboutDlg :: CAboutDlg ( void )
           : CDialog ( CAboutDlg::IDD ) ,
             m_cBigIcon ( )

{
    ASSERT ( this ) ;
    m_pcFont = NULL ;
}

CAboutDlg :: ~CAboutDlg ( void )
{
    ASSERT ( this ) ;
    if ( NULL != m_pcFont )
    {
        delete m_pcFont ;
        m_pcFont = NULL ;
    }
}

void CAboutDlg :: DoDataExchange ( CDataExchange * pDX )
{
    ASSERT ( this ) ;

    CDialog::DoDataExchange ( pDX ) ;
}

BOOL CAboutDlg :: OnInitDialog ( void )
{
    ASSERT ( this ) ;

    // Let the normal processing happen.
    CDialog::OnInitDialog ( ) ;

    // Do the big icon.
    m_cBigIcon.SubclassDlgItem ( IDC_BIGICON , this ) ;
    m_cBigIcon.SizeToContent ( ) ;

    // Create and set the name font.
    m_pcFont = new CFont ;
    BOOL bRet = m_pcFont->CreatePointFont ( 300 , _T ( "Arial" ) ) ;
    ASSERT ( bRet ) ;
    if ( TRUE == bRet )
    {
        CWnd * pWnd = GetDlgItem ( IDC_APPNAME ) ;
        ASSERT ( NULL != pWnd ) ;
        if ( NULL != pWnd )
        {
            pWnd->SetFont ( m_pcFont ) ;
        }
    }
    m_cRedText.SubclassDlgItem ( IDC_APPNAME , this ) ;


    // Stick the hint text into the edit control.
    HRSRC hRes = ::FindResource ( NULL                             ,
                                  MAKEINTRESOURCE ( IDR_HINTDATA ) ,
                                  _T ( "HINTDATA" )                 ) ;
    ASSERT ( NULL != hRes ) ;
    if ( NULL != hRes )
    {
        LPCTSTR szData = (LPCTSTR)::LoadResource ( NULL , hRes ) ;
        ASSERT ( NULL != szData ) ;
        if ( NULL != szData )
        {
            CWnd * pEdit = GetDlgItem ( IDC_HINTS ) ;
            ASSERT ( NULL != pEdit ) ;
            if ( NULL != pEdit )
            {
                
                // Skip past the BOM byte.
                LPCTSTR szFinalData = szData ;
                if ( 0xFEFF == szFinalData[0] )
                {
                    szFinalData++ ;
                }

                pEdit->SetWindowText ( szFinalData ) ;
            }
        }

    }

    // Get the hyperlink thing hooked up.
    //m_cWebLink.m_link = _T ( "www.wintellect.com" ) ;
    m_cWebLink.SubclassDlgItem ( IDC_HYPERLINK , this ) ;

    // Put the focus on the OK button.
    CWnd * pOK = GetDlgItem ( IDOK ) ;
    ASSERT ( NULL != pOK ) ;
    if ( NULL != pOK )
    {
        pOK->SetFocus ( ) ;
    }

    return ( FALSE ) ;
}

