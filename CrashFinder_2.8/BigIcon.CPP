/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "BigIcon.h"

BEGIN_MESSAGE_MAP ( CBigIcon , CButton )
      ON_WM_DRAWITEM ( )
      ON_WM_ERASEBKGND ( )
END_MESSAGE_MAP ( )

#define CY_SHADOW   4
#define CX_SHADOW   4

void CBigIcon::SizeToContent ( )
{
    // get system icon size
    int cxIcon =::GetSystemMetrics ( SM_CXICON ) ;
    int cyIcon =::GetSystemMetrics ( SM_CYICON ) ;

    // a big icon should be twice the size of an icon + shadows
    SetWindowPos ( NULL , 0 , 0 , cxIcon * 2 + CX_SHADOW + 4 , cyIcon * 2 + CY_SHADOW + 4 ,
        SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER ) ;
}

void CBigIcon::DrawItem ( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    CDC * pDC = CDC::FromHandle ( lpDrawItemStruct->hDC ) ;
    ASSERT ( pDC != NULL ) ;
    if ( NULL == pDC )
    {
        // Not much I can do!
        return ;
    }

    CRect rect ;
    GetClientRect ( rect ) ;
    int cxClient = rect.Width ( ) ;
    int cyClient = rect.Height ( ) ;

    // load icon
    CString sName ;
    GetWindowText ( sName ) ;
    HICON hicon = AfxGetApp ()->LoadIcon ( sName ) ;
    ASSERT ( NULL != hicon ) ;
    if ( hicon == NULL )
    {
        return ;
    }

    // draw icon into off-screen bitmap
    int cxIcon =::GetSystemMetrics ( SM_CXICON ) ;
    int cyIcon =::GetSystemMetrics ( SM_CYICON ) ;

    CBitmap bitmap ;
    if ( !bitmap.CreateCompatibleBitmap ( pDC , cxIcon , cyIcon ) )
    {
        return ;
    }
    CDC dcMem ;
    if ( !dcMem.CreateCompatibleDC ( pDC ) )
    {
        return ;
    }
    CBitmap * pBitmapOld = dcMem.SelectObject ( &bitmap ) ;
    if ( pBitmapOld == NULL )
    {
        return ;
    }

    // blt the bits already on the window onto the off-screen bitmap
    dcMem.StretchBlt ( 0 , 0 , cxIcon , cyIcon , pDC ,
        2 , 2 , cxClient - CX_SHADOW - 4 , cyClient - CY_SHADOW - 4 ,
        SRCCOPY ) ;

    // draw the icon on the background
    dcMem.DrawIcon ( 0 , 0 , hicon ) ;

    // draw border around icon
    CPen pen ;
    pen.CreateStockObject ( BLACK_PEN ) ;
    CPen * pPenOld = pDC->SelectObject ( &pen ) ;
    pDC->Rectangle ( 0 , 0 , cxClient - CX_SHADOW , cyClient-CY_SHADOW);
    if ( pPenOld )
    {
        pDC->SelectObject ( pPenOld ) ;
    }

    // draw shadows around icon
    CBrush br ;
    br.CreateStockObject ( DKGRAY_BRUSH ) ;
    rect.SetRect ( cxClient - CX_SHADOW , CY_SHADOW ,cxClient,cyClient);
    pDC->FillRect ( rect , &br ) ;
    rect.SetRect ( CX_SHADOW , cyClient - CY_SHADOW ,cxClient,cyClient);
    pDC->FillRect ( rect , &br ) ;

    // draw the icon contents
    pDC->StretchBlt ( 2 , 2 , cxClient - CX_SHADOW - 4 , cyClient -
                      CY_SHADOW - 4 , &dcMem , 0 , 0 , cxIcon ,
                      cyIcon , SRCCOPY ) ;
}

BOOL CBigIcon::OnEraseBkgnd ( CDC * )
{
    return TRUE ; // we don't do any erasing...
}


