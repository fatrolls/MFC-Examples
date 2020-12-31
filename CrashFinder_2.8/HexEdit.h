/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#ifndef _HEXEDIT_H
#define _HEXEDIT_H

class CHexEdit : public CEdit
{

public      :
    CHexEdit ( void ) ;

    void GetNumbers ( CPtrArray & cArray ) ;

protected   :
    afx_msg void OnChar ( UINT nChar , UINT nRepCnt , UINT nFlags ) ;

    DECLARE_MESSAGE_MAP ( )

} ;

#endif      // _HEXEDIT_H


