/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#if !defined ( _CHILDFRM_H )
#define _CHILDFRM_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CChildFrame : public CMDIChildWnd
{
    //lint -e1511
    DECLARE_DYNCREATE ( CChildFrame )
    //lint +e1511

public      :

    CChildFrame ( ) ;

// Attributes
public      :

// Operations
public      :

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChildFrame)
    virtual BOOL PreCreateWindow ( CREATESTRUCT & cs ) ;
    //}}AFX_VIRTUAL

    // Implementation
public      :
    virtual ~CChildFrame ( ) ;

#ifdef _DEBUG
    virtual void AssertValid ( ) const ;
    virtual void Dump ( CDumpContext & dc ) const ;
#endif

    virtual void ActivateFrame ( int nCmdShow = -1 ) ;

    virtual void OnSize ( UINT nType , int cx , int cy ) ;


    // Generated message map functions
protected   :

    virtual BOOL OnCreateClient ( LPCREATESTRUCT   lpcs     ,
                                  CCreateContext * pContext  ) ;


    //{{AFX_MSG(CChildFrame)
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP ( )

private     :
    // The static splitter handler.
    CSplitterWnd    m_wndSplitter ;
    BOOL m_bActivated ;
    BOOL m_bSplitterCreated ;
} ;

//{{AFX_INSERT_LOCATION}}

#endif // _CHILDFRM_H
