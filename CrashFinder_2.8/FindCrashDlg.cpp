/*----------------------------------------------------------------------
"Debugging Applications" (Microsoft Press)
Copyright (c) 1997-2000 John Robbins -- All rights reserved.

With excellent updates from Scott Bloom, Ching Ming Kwok, 
Jeff Shanholtz, and Pablo Presedo!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "CrashFinderDoc.h"
#include "FindCrashDlg.h"
#include "SymbolEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

BEGIN_MESSAGE_MAP ( CFindCrashDlg , CDialog )
    ON_COMMAND ( IDC_FIND , OnFindAddr )
    ON_COMMAND ( IDC_ADDRESS , OnFindAddr )
    ON_COMMAND ( IDC_MODULE , OnFindAddr )
    ON_COMMAND ( IDC_FUNCTION , OnFunction )
    ON_COMMAND ( IDC_FNDISPLACEMENT , OnFindAddr )
    ON_COMMAND ( IDC_SOURCEFILE , OnSourceFile )
    ON_COMMAND ( IDC_SOURCELINE , OnSourceLine )
    ON_COMMAND ( IDC_SRCDISPLACEMENT , OnFindAddr )
    ON_COMMAND ( IDC_ONELINE, OnFindAddr )
END_MESSAGE_MAP ( )


CFindCrashDlg :: CFindCrashDlg ( CCrashFinderDoc * pDoc )
               : CDialog ( CFindCrashDlg::IDD ) ,
                 m_cAddress ( )     ,
                 m_cModule ( )      ,
                 m_cFunction ( )    ,
                 m_cFnDispl ( )     ,
                 m_cSourceFile ( )  ,
                 m_cSourceLine ( )  ,
                 m_cSrcDispl ( )    ,
                 m_cOneLine ( )     ,
                                 m_cDetails ( )
{
    ASSERT ( this ) ;
    ASSERT ( NULL != pDoc ) ;
    m_pDoc = pDoc ;
}

void CFindCrashDlg :: DoDataExchange ( CDataExchange * pDX )
{
    ASSERT ( this ) ;

    CDialog::DoDataExchange ( pDX ) ;
    DDX_Text  ( pDX , IDC_HEXEDIT        , m_strAddresses     ) ;
    DDX_Check ( pDX , IDC_ADDRESS        , m_bAddress         ) ;
    DDX_Check ( pDX , IDC_MODULE         , m_bModule          ) ;
    DDX_Check ( pDX , IDC_FUNCTION       , m_bFunction        ) ;
    DDX_Check ( pDX , IDC_FNDISPLACEMENT , m_bFnDisplacement  ) ;
    DDX_Check ( pDX , IDC_SOURCEFILE     , m_bSourceFile      ) ;
    DDX_Check ( pDX , IDC_SOURCELINE     , m_bSourceLine      ) ;
    DDX_Check ( pDX , IDC_SRCDISPLACEMENT, m_bSrcDisplacement ) ;
    DDX_Check ( pDX , IDC_ONELINE        , m_bOneLine         ) ;

        if ( !pDX->m_bSaveAndValidate )
        {
                UpdateControls( );
        }
}

BOOL CFindCrashDlg :: OnInitDialog ( void )
{
    ASSERT ( this ) ;

    // Subclass the edit control with my cheezy hex only edit control
    // class.
    BOOL bRet = m_cHexCtrl.SubclassDlgItem ( IDC_HEXEDIT , this ) ;
    ASSERT ( TRUE == bRet ) ;

    // Attach to all the static text controls on the dialog.
    CWnd * pWnd = GetDlgItem ( IDC_ADDRESS ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cAddress.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_MODULE ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cModule.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_FUNCTION ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cFunction.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_FNDISPLACEMENT ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cFnDispl.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_SOURCEFILE ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cSourceFile.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_SOURCELINE ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cSourceLine.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_SRCDISPLACEMENT ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cSrcDispl.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_ONELINE ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cOneLine.Attach ( pWnd->m_hWnd ) ) ;

    pWnd = GetDlgItem ( IDC_DETAILS ) ;
    ASSERT ( NULL != pWnd ) ;
    VERIFY ( m_cDetails.Attach ( pWnd->m_hWnd ) ) ;

    // Let the normal initialization take place.
    bRet = CDialog::OnInitDialog ( ) ;

        if (!m_strAddresses.IsEmpty( ))
                OnFindAddr( );
    return ( bRet ) ;
}

void CFindCrashDlg :: OnCancel ( )
{
        UpdateData( );

    // Detach all the value controls.
    VERIFY ( m_cAddress.Detach ( )      ) ;
    VERIFY ( m_cModule.Detach ( )       ) ;
    VERIFY ( m_cFunction.Detach ( )     ) ;
    VERIFY ( m_cFnDispl.Detach ( )      ) ;
    VERIFY ( m_cSourceFile.Detach ( )   ) ;
    VERIFY ( m_cSourceLine.Detach ( )   ) ;
    VERIFY ( m_cSrcDispl.Detach ( )     ) ;
    VERIFY ( m_cOneLine.Detach ( )      ) ;
    VERIFY ( m_cDetails.Detach ( )      ) ;

    CDialog::OnCancel ( ) ;
}

void CFindCrashDlg :: OnFindAddr ( void )
{
    ASSERT ( this ) ;

    // Get the text out of the edit control.
        TCHAR szAddr[25];
        int startpos = 0, endpos, len;
        CString sDetails = "";
        int nTopLevelChecks = 0;
        BOOL bOneLine;

        UpdateData( );

        nTopLevelChecks += m_bAddress ? 1 : 0;
        nTopLevelChecks += m_bModule ? 1 : 0;
        nTopLevelChecks += m_bFunction ? 1 : 0;
        nTopLevelChecks += m_bSourceFile ? 1 : 0;
        bOneLine = nTopLevelChecks < 2 || m_cOneLine.GetCheck( );

        len = m_strAddresses.GetLength( );
        while ( startpos < len && (m_strAddresses[startpos] < '0' || m_strAddresses[startpos] > '9') && (m_strAddresses[startpos] < 'a' || m_strAddresses[startpos] > 'f') && (m_strAddresses[startpos] < 'A' || m_strAddresses[startpos] > 'F') )
                startpos++;
        endpos = startpos;

        while ( startpos < len )
        {
                while ( endpos < len && (m_strAddresses[endpos] >= '0' && m_strAddresses[endpos] <= '9' || m_strAddresses[endpos] >= 'a' && m_strAddresses[endpos] <= 'f' || m_strAddresses[endpos] >= 'A' && m_strAddresses[endpos] <= 'F') )
                        endpos++;
                if (startpos == endpos)
                        break;
                endpos--;
                strcpy( szAddr, m_strAddresses.Mid( startpos, endpos - startpos + 1 ) );

                // Try and convert it to an value.  I'm taking the easy way out.
                DWORD dwAddr ;
                int iRet = _stscanf ( szAddr      ,
                                                          _T ( "%x" ) ,
                                                          &dwAddr       ) ;

                if ( 1 != iRet )
                {
                        CString sMsg ;
                        sMsg.FormatMessage ( IDS_LOADADDRBADCONVERSION , m_strAddresses ) ;
                        AfxMessageBox ( sMsg ) ;
                        return ;
                }

                // Now look up the address through the document.
                ASSERT ( NULL != m_pDoc ) ;

                // Since the largest symbol that the MS code generators can handle
                // is 256 that is all that is needed.
                IMAGEHLP_SYMBOL * pstIHSym =
                          (IMAGEHLP_SYMBOL *)new BYTE [ sizeof ( IMAGEHLP_SYMBOL ) +
                                                                                        256                         ] ;
                memset ( pstIHSym , NULL , sizeof ( IMAGEHLP_SYMBOL ) + 256 ) ;
                pstIHSym->SizeOfStruct = sizeof ( IMAGEHLP_SYMBOL ) + 256 ;
                pstIHSym->MaxNameLength = 256 ;

                // The line information.
                CImageHlp_Line stIHLine ;

                // The displacements.
                DWORD dwFnDispl  ;
                DWORD dwSrcDispl ;

                // The module string.
                CString sModule ;

                // Where I build up the test to output.
                CString sTemp   ;

                // Do the look up.
                int iRes = m_pDoc->LookUpAddress ( dwAddr     ,
                                                                                   sModule    ,
                                                                                   *pstIHSym  ,
                                                                                   dwFnDispl  ,
                                                                                   stIHLine   ,
                                                                                   dwSrcDispl  ) ;

                if ( iRes < 0 )
                        return ;

                if ( !bOneLine && !sDetails.IsEmpty( ) && "\r\n\r\n" != sDetails.Right( 4 ) )
                        sDetails += "\r\n";

                if ( m_cAddress.GetCheck( ) )
                {
                        // show the address that was just looked up.
                        sTemp.Format ( _T ( "%08X" ) , dwAddr ) ;
                        sDetails += sTemp;
                        sDetails += bOneLine ? "->" : "\r\n";
                }

                if (m_cModule.GetCheck( ) )
                {
                        // Did a proper module get returned?
                        if ( eLUMOD == ( eLUMOD & iRes ) )
                        {
                                // Pull off the path information so the dialog does not have to
                                // be a mile wide.
                                TCHAR szFile[ MAX_PATH ] ;
                                TCHAR szExt[ MAX_PATH ] ;

                                _tsplitpath ( (LPCTSTR)sModule ,
                                                          NULL             ,
                                                          NULL             ,
                                                          szFile           ,
                                                          szExt             ) ;

                                sModule = szFile ;
                                sModule += szExt ;
                        }
                        else
                                sModule.LoadString ( IDS_MODNOTFOUND ) ;

                        sDetails += sModule;
                        sDetails += bOneLine ? "->" : "\r\n";
                }

                if (m_cFunction.GetCheck( ) )
                {
                        // Did a proper symbol get returned?
                        if ( eLUSYM == ( eLUSYM & iRes ) )
                        {
                                sDetails += (LPCSTR)pstIHSym->Name;

                                if (m_cFnDispl.GetCheck( ) )
                                        if ( 0 != dwFnDispl )
                                        {
                                                sTemp.Format ( IDS_DISPLACEMENTFMT  ,
                                                                           dwFnDispl             ) ;
                                                sDetails += " + ";
                                                sDetails += sTemp;
                                        }
                        }
                        else
                        {
                                VERIFY ( sTemp.LoadString ( IDS_FUNCNOTFOUND ) ) ;
                                sDetails += sTemp;
                        }
                        sDetails += bOneLine ? "->" : "\r\n";
                }

                if (m_cSourceFile.GetCheck( ) )
                {
                        // Did a proper source/line get returned?
                        if ( eLULINE == ( eLULINE & iRes ) )
                                sDetails += stIHLine.FileName;
                        else
                        {
                                VERIFY ( sTemp.LoadString ( IDS_LINENOTFOUND ) ) ;
                                sDetails += sTemp;
                        }

                        if (m_cSourceLine.GetCheck( ) )
                                // Did a proper source/line get returned?
                                if ( eLULINE == ( eLULINE & iRes ) )
                                {
                                        sTemp.Format ( IDS_LINEFMT , stIHLine.LineNumber ) ;
                                        sDetails += " ";
                                        sDetails += sTemp;

                                        if (m_cSrcDispl.GetCheck( ) )
                                                if ( 0 != dwSrcDispl )
                                                {
                                                        sTemp.Format ( IDS_DISPLACEMENTFMT  ,
                                                                                   dwSrcDispl            ) ;
                                                        sDetails += " + ";
                                                        sDetails += sTemp;
                                                }
                                }

                        sDetails += bOneLine ? "->" : "\r\n";
                }

                if (bOneLine)
                        if ("->" == sDetails.Right( 2 ))
                        {
                                int len = sDetails.GetLength( );
                                sDetails.SetAt( len-2, '\r' );
                                sDetails.SetAt( len-1, '\n' );
                        }

                // I am done so get rid of the memory that I allocated earlier.
                delete [] pstIHSym ;

                startpos = endpos + 1;
                while ( startpos < len && (m_strAddresses[startpos] < '0' || m_strAddresses[startpos] > '9') && (m_strAddresses[startpos] < 'a' || m_strAddresses[startpos] > 'f') && (m_strAddresses[startpos] < 'A' || m_strAddresses[startpos] > 'F') )
                        startpos++;
                endpos = startpos;
        }

        if ( "\r\n\r\n" == sDetails.Right( 4 ) )
                if ( 4 == sDetails.GetLength( ) )
                        sDetails.Empty( );
                else
                        sDetails.SetAt( sDetails.GetLength( ) - 2, '\0' );

        m_cDetails.SetWindowText ( sDetails );
}

void CFindCrashDlg :: UpdateControls ( void )
{
        m_cFnDispl.EnableWindow ( m_cFunction.GetCheck( ) ) ;
        m_cSourceLine.EnableWindow ( m_cSourceFile.GetCheck( ) ) ;
        m_cSrcDispl.EnableWindow ( m_cSourceLine.IsWindowEnabled( ) && m_cSourceLine.GetCheck( ) ) ;
}

void CFindCrashDlg :: OnFunction ( void )
{
    ASSERT ( this ) ;

        UpdateControls( );
        OnFindAddr( );
}

void CFindCrashDlg :: OnSourceFile ( void )
{
    ASSERT ( this ) ;

        UpdateControls( );
        OnFindAddr( );
}

void CFindCrashDlg :: OnSourceLine ( void )
{
    ASSERT ( this ) ;

        UpdateControls( );
        OnFindAddr( );
}
