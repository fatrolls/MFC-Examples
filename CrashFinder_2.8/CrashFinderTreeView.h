/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#if !defined ( _CRASHFINDERTREEVIEW_H )
#define _CRASHFINDERTREEVIEW_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCrashFinderTreeView : public CTreeView
{
protected   :

    CCrashFinderTreeView ( ) ;

    //lint -e1511
    DECLARE_DYNCREATE ( CCrashFinderTreeView )
    //lint +e1511

// Attributes
public      :
    //lint -e1511
    CCrashFinderDoc * GetDocument ( ) ;
    //lint +e1511

// Operations
public      :

    // Overrides
public      :
protected   :
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCrashFinderTreeView)
    //}}AFX_VIRTUAL

    // Implementation
public      :
    virtual ~CCrashFinderTreeView ( ) ;

#ifdef _DEBUG
    virtual void AssertValid ( ) const ;
    virtual void Dump ( CDumpContext & dc ) const ;
#endif

protected   :

    // Generated message map functions
protected   :

    //{{AFX_MSG(CCrashFinderTreeView)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP ( )
} ;

#ifndef _DEBUG  // debug version in CrashFinderView.cpp
inline CCrashFinderDoc * CCrashFinderTreeView :: GetDocument ( )
{
    return ( (CCrashFinderDoc *)m_pDocument ) ;
}
#endif

//{{AFX_INSERT_LOCATION}}

#endif // !_CRASHFINDERTREEVIEW_H
