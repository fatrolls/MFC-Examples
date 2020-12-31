/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/

#ifndef _BIGICON_H
#define _BIGICON_H

// The BigIcon lifted straight from SuperPad.

class CBigIcon : public CButton
{
    // Attributes
 public :

    // Operations
 public :
    void SizeToContent ( ) ;

    // Implementation
 protected :
    virtual void DrawItem ( LPDRAWITEMSTRUCT lpDrawItemStruct ) ;

    // Message handler.
    afx_msg BOOL OnEraseBkgnd ( CDC * pDC ) ;

    DECLARE_MESSAGE_MAP ( )
} ;

#endif  // _BIGICON_H
