/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#ifndef _BINARYIMAGEOPTIONSDLG_H
#define _BINARYIMAGEOPTIONSDLG_H

#include "resource.h"
#include "HexEdit.h"


class CBinaryImageOptionsDlg : public CDialog
{
public      :

    CBinaryImageOptionsDlg ( ) ;

    // Dialog Data
    enum { IDD = IDD_BINARYPROPERTIES } ;

    DWORD64 m_dwAddr ;

    CString m_strImageName ;

protected   :
    virtual void DoDataExchange ( CDataExchange * pDX ) ;
    virtual BOOL OnInitDialog ( void ) ;
    virtual void OnOK ( void ) ;

// Implementation
protected   :

    CHexEdit    m_cHexCtrl  ;

    DECLARE_MESSAGE_MAP ( )
} ;

#endif  // _BINARYIMAGEOPTIONSDLG_H


