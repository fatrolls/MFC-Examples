/*----------------------------------------------------------------------
"Debugging Applications" (Microsoft Press)
Copyright (c) 1997-2000 John Robbins -- All rights reserved.

With excellent updates from Scott Bloom, Ching Ming Kwok, 
Jeff Shanholtz, and Pablo Presedo!
----------------------------------------------------------------------*/
#ifndef _FINDCRASHDLG_H
#define _FINDCRASHDLG_H

#include "resource.h"

#include "HexEdit.h"

class CFindCrashDlg : public CDialog
{
public      :

    CFindCrashDlg ( CCrashFinderDoc * pDoc ) ;

    enum { IDD = IDD_FINDCRASH } ;

        CString m_strAddresses;
        BOOL m_bAddress;
        BOOL m_bModule;
        BOOL m_bFunction;
        BOOL m_bFnDisplacement;
        BOOL m_bSourceFile;
        BOOL m_bSourceLine;
        BOOL m_bSrcDisplacement;
        BOOL m_bOneLine;

protected   :
    virtual BOOL OnInitDialog ( void ) ;
    virtual void OnCancel ( ) ;


    virtual void DoDataExchange ( CDataExchange * pDX ) ;

    afx_msg void OnFindAddr ( void ) ;
    afx_msg void OnFunction ( void ) ;
    afx_msg void OnSourceFile ( void ) ;
    afx_msg void OnSourceLine ( void ) ;

    DECLARE_MESSAGE_MAP ( )

        void UpdateControls ( void ) ;

private     :
    // The document object that controls this dialog.
    CCrashFinderDoc * m_pDoc ;

    // The hex edit control.
    CHexEdit    m_cHexCtrl  ;

    // The static controls for the values that show the results.
    CButton     m_cAddress      ;
    CButton     m_cModule       ;
    CButton     m_cFunction     ;
    CButton     m_cFnDispl      ;
    CButton     m_cSourceFile   ;
    CButton     m_cSourceLine   ;
    CButton     m_cSrcDispl     ;
    CButton     m_cOneLine      ;

        CEdit       m_cDetails      ;

} ;

#endif  // _FINDCRASHDLG_H


