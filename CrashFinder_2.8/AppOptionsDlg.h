/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#ifndef _APPOPTIONSDLG_H
#define _APPOPTIONSDLG_H

#include "resource.h"


class CAppOptionsDlg : public CDialog
{
public      :

    CAppOptionsDlg ( ) ;

    // Dialog Data

    enum { IDD = IDD_APPOPTIONS } ;

protected   :
    virtual void DoDataExchange ( CDataExchange * pDX ) ;

// Implementation
protected   :

    DECLARE_MESSAGE_MAP ( )

public      :

    // The boolean options.
    BOOL m_bShowFullPaths ;
    BOOL m_bConfirmDeletions ;
    BOOL m_bOneLine ;
    BOOL m_bShowDisplacements ;
    BOOL m_bInsertText ;


} ;

#endif  // _APPOPTIONSDLG_H


