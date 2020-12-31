/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#ifndef _FINDVIEW_H
#define _FINDVIEW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HexEdit.h"

#include "Resource.h"

#include "CrashFinderDoc.h"
class CCrashFinderDoc ;

class CFindView : public CFormView
{
protected   :
    CFindView ( ) ;

    DECLARE_DYNCREATE(CFindView)

// Form Data
public      :
    //{{AFX_DATA(CFindView)
    enum { IDD = IDD_FIND_FORM } ;
    //}}AFX_DATA

// Attributes
public      :

// Operations
public      :
    CEdit * GetHexEditControl ( void )
    {
        return ( &m_cHexCtrl ) ;
    }

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CFindView)
	public:
	virtual void OnInitialUpdate();
	protected:
    virtual void DoDataExchange ( CDataExchange * pDX ) ;
	//}}AFX_VIRTUAL

public      :
    void RedoFind ( void )
    {
        OnFind ( ) ;
    }

// Implementation
protected   :
    virtual ~CFindView ( ) ;
#ifdef _DEBUG
    virtual void AssertValid ( ) const ;
    virtual void Dump ( CDumpContext & dc ) const ;
#endif

    CCrashFinderDoc * GetDocument ( ) ;

    // Generated message map functions
    //{{AFX_MSG(CFindView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFind();
	afx_msg void OnClear();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected   :

    CHexEdit    m_cHexCtrl ;

} ;

#ifndef _DEBUG  // debug version in CrashFinderView.cpp
inline CCrashFinderDoc * CFindView :: GetDocument ( )
{
    return ( (CCrashFinderDoc *)m_pDocument ) ;
}
#endif

//{{AFX_INSERT_LOCATION}}

#endif  // _FINDVIEW_H


