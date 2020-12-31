/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "BinaryImageOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

BEGIN_MESSAGE_MAP ( CBinaryImageOptionsDlg , CDialog )
END_MESSAGE_MAP ( )

CBinaryImageOptionsDlg :: CBinaryImageOptionsDlg ( )
           : CDialog ( CBinaryImageOptionsDlg::IDD ) ,
             m_cHexCtrl ( )
{
    ASSERT ( this ) ;
    m_dwAddr = 0 ;
}

void CBinaryImageOptionsDlg :: DoDataExchange ( CDataExchange * pDX )
{
    ASSERT ( this ) ;

    CDialog::DoDataExchange ( pDX ) ;
}

BOOL CBinaryImageOptionsDlg :: OnInitDialog ( void )
{
    ASSERT ( this ) ;
    ASSERT ( 0 != m_dwAddr ) ;

    // Subclass the edit control with my cheezy hex only edit control
    // class.
    m_cHexCtrl.SubclassDlgItem ( IDC_LOADADDREDIT , this ) ;

    CEdit * pEdit = (CEdit*)GetDlgItem ( IDC_LOADADDREDIT ) ;
    ASSERT ( NULL != pEdit ) ;
    if ( NULL != pEdit )
    {
        // Format the load address into a string and stick it into the edit
        // control.
        CString sTemp ;
    #ifdef _WIN64
        sTemp.Format ( _T ( "%016X" ) , m_dwAddr ) ;
    #else
        sTemp.Format ( _T ( "%08X" ) , (int)m_dwAddr ) ;
    #endif

        pEdit->SetWindowText ( sTemp ) ;

        // Show the binary in the title.
        CString strTitle ;
        GetWindowText ( strTitle ) ;
        strTitle += m_strImageName ;
        SetWindowText ( strTitle ) ;
    }
    return ( TRUE ) ;
}

void CBinaryImageOptionsDlg :: OnOK ( void )
{

    ASSERT ( this ) ;

    // Get the text out of the edit control.
    TCHAR szTemp[ 25 ] ;

    CEdit * pEdit = (CEdit*)GetDlgItem ( IDC_LOADADDREDIT ) ;
    ASSERT ( NULL != pEdit ) ;
    if ( NULL != pEdit )
    {

        pEdit->GetWindowText ( szTemp , 25 ) ;

        // Try and convert it to an value.  I'm taking the easy way out.
        DWORD dwTempAddr ;
#if _MSC_VER <= 1310
        int iRet = _stscanf ( szTemp         ,
                               _T ( "%x" )   ,
                               &dwTempAddr    ) ;
#else
        int iRet = _stscanf_s ( szTemp         ,
                                _T ( "%x" )   ,
                                &dwTempAddr    ) ;
#endif

        if ( 1 != iRet )
        {
            CString sMsg ;
            sMsg.FormatMessage ( IDS_LOADADDRBADCONVERSION , szTemp ) ;
            AfxMessageBox ( sMsg ) ;
        }
        else
        {
            m_dwAddr = dwTempAddr ;
            CDialog::OnOK ( ) ;
        }
    }
}


