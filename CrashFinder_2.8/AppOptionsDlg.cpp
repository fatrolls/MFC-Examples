/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "AppOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

CAppOptionsDlg :: CAppOptionsDlg ( )
                : CDialog ( CAppOptionsDlg::IDD )
{
    ASSERT ( this ) ;

    m_bConfirmDeletions  = TRUE  ;
    m_bShowFullPaths     = FALSE ;
    m_bOneLine           = FALSE ;
    m_bShowDisplacements = FALSE ;
    m_bInsertText        = FALSE ;
}

void CAppOptionsDlg :: DoDataExchange ( CDataExchange * pDX )
{
    ASSERT ( this ) ;
    CDialog::DoDataExchange ( pDX ) ;
    DDX_Check ( pDX , IDC_SHOWFULLPATHS     , m_bShowFullPaths     ) ;
    DDX_Check ( pDX , IDC_CONFIRMDELETIONS  , m_bConfirmDeletions  ) ;
    DDX_Check ( pDX , IDC_SHOWDISPLACEMENTS , m_bShowDisplacements ) ;
    DDX_Check ( pDX , IDC_ONELINE           , m_bOneLine           ) ;
    DDX_Check ( pDX , IDC_INSERTTEXT        , m_bInsertText        ) ;
}

BEGIN_MESSAGE_MAP ( CAppOptionsDlg , CDialog )
END_MESSAGE_MAP ( )


