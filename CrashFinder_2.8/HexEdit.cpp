/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "StdAfx.h"
#include "HexEdit.h"

#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

BEGIN_MESSAGE_MAP ( CHexEdit , CEdit )
    ON_WM_CHAR ( )
END_MESSAGE_MAP ( )

CHexEdit :: CHexEdit ( )
          : CEdit ( )
{
    ASSERT ( this ) ;
}

void CHexEdit :: OnChar ( UINT nChar , UINT nRepCnt , UINT nFlags )
{
    ASSERT ( this ) ;

    BOOL bAllowed = FALSE ;

    if ( nChar < 0x20 )
    {
        bAllowed = TRUE ;
    }
    else if ( ( (TCHAR)nChar >= _T ( '0' ) ) &&
              ( (TCHAR)nChar <= _T ( '9' ) )    )
    {
        bAllowed = TRUE ;
    }
    else if ( ( (TCHAR)nChar >= _T ( 'A' ) ) &&
              ( (TCHAR)nChar <= _T ( 'F' ) )    )
    {
        bAllowed = TRUE ;
    }
    else if ( ( (TCHAR)nChar >= _T ( 'a' ) ) &&
              ( (TCHAR)nChar <= _T ( 'f' ) )    )
    {
        bAllowed = TRUE ;
    }
    else if ( ( (TCHAR)nChar == _T ( ' ' ) ) ||
              ( (TCHAR)nChar == _T ( ';' ) ) ||
              ( (TCHAR)nChar == _T ( ',' ) )    )
    {
        bAllowed = TRUE ;
    }

    if ( TRUE == bAllowed )
    {
        CEdit::OnChar ( nChar , nRepCnt , nFlags ) ;
    }
    else
    {
        MessageBeep ( MB_ICONEXCLAMATION ) ;
    }
}

const LPCTSTR k_DELIMS = _T ( " ,;" ) ;

void CHexEdit :: GetNumbers ( CPtrArray & cArray )
{
    // Get the array into shape.
    cArray.RemoveAll ( ) ;

    CString strRaw ;
    GetWindowText ( strRaw ) ;

    int iBuffLen = (strRaw.GetLength ( ) + 1 ) * sizeof ( TCHAR ) ;
    TCHAR * szBuff = (TCHAR*)new TCHAR[ iBuffLen ] ;

    StringCchCopy ( szBuff                      , 
                    iBuffLen / sizeof ( TCHAR ) , 
                    (LPCTSTR)strRaw              ) ;

    // Use good ol' strtok to do the deed.
#if _MSC_VER <= 1310
        TCHAR * pCurr = _tcstok ( szBuff , k_DELIMS ) ;
#else
        TCHAR * cContext = NULL ;
        TCHAR * pCurr = _tcstok_s ( szBuff , k_DELIMS , &cContext ) ;
#endif
    while ( NULL != pCurr )
    {

        // Try and convert it to an value.  I'm taking the easy way out.
        DWORD64 dwAddr = 0 ;
#if _MSC_VER <= 1310
        int iRet = _stscanf ( pCurr          ,
                              _T ( "%I64x" ) ,
                              &dwAddr       ) ;
#else
        int iRet = _stscanf_s ( pCurr          ,
                               _T ( "%I64x" ) ,
                               &dwAddr       ) ;
#endif
        if ( 1 != iRet )
        {
            CString sMsg ;
            sMsg.FormatMessage ( IDS_LOADADDRBADCONVERSION ,
                                 pCurr                      ) ;
            AfxMessageBox ( sMsg ) ;
        }
        else
        {
            cArray.Add (  (void*)dwAddr ) ;
        }

        pCurr = 
#if _MSC_VER <= 1310
            _tcstok ( NULL , k_DELIMS ) ;
#else
            _tcstok_s ( NULL , k_DELIMS , &cContext ) ;
#endif
    }
    delete [] szBuff ;
}

