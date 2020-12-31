/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "CrashFinder.h"
#include "CrashFinderDoc.h"
#include "CrashFinderTreeView.h"
#include "FindView.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

IMPLEMENT_DYNCREATE ( CChildFrame , CMDIChildWnd )

BEGIN_MESSAGE_MAP ( CChildFrame , CMDIChildWnd )
//{{AFX_MSG_MAP(CChildFrame)
    ON_WM_SIZE ( )
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP ( )

CChildFrame :: CChildFrame ( )
             : CMDIChildWnd ( ) , m_wndSplitter ( )
{
    ASSERT ( this ) ;
    m_bActivated = FALSE ;
    m_bSplitterCreated = FALSE ;
}

CChildFrame :: ~CChildFrame ( )
{
    ASSERT ( this ) ;
}

BOOL CChildFrame :: PreCreateWindow ( CREATESTRUCT & cs )
{
    ASSERT ( this ) ;

    return ( CMDIChildWnd::PreCreateWindow ( cs ) ) ;
}

void CChildFrame :: ActivateFrame ( int nCmdShow )
{
    if ( !m_bActivated )
    {
        m_bActivated = TRUE ;
        nCmdShow = SW_SHOWMAXIMIZED ;
    }
    CFrameWnd::ActivateFrame ( nCmdShow ) ;
}

#ifdef _DEBUG
void CChildFrame :: AssertValid ( ) const
{
    ASSERT ( this ) ;

    CMDIChildWnd::AssertValid ( ) ;
}

void CChildFrame :: Dump ( CDumpContext & dc ) const
{
    ASSERT ( this ) ;

    CMDIChildWnd::Dump ( dc ) ;
}

#endif //_DEBUG

BOOL CChildFrame :: OnCreateClient ( LPCREATESTRUCT   /*lpcs*/ ,
                                     CCreateContext * pContext  )
{
    ASSERT ( this ) ;

    CRect Rect ;
    CWnd * pParent = GetParent ( ) ;
    pParent->GetClientRect ( &Rect ) ;

    Rect.bottom -= ( GetSystemMetrics ( SM_CYFRAME )  +
                     GetSystemMetrics ( SM_CYBORDER ) +
                     GetSystemMetrics ( SM_CYVSCROLL ) ) ;

    // Create the static splitter.
    if ( FALSE == m_wndSplitter.CreateStatic ( this , 2 , 1 ) )
    {
        return ( FALSE ) ;
    }
    m_bSplitterCreated = TRUE ;
    // Make the left hand view the tree control.
    if ( FALSE ==
          m_wndSplitter.CreateView ( 0                  ,
                                     0                  ,
                                    RUNTIME_CLASS(CCrashFinderTreeView),
                                     CSize ( 0 , Rect.Height ( ) / 2 ) ,
                                     pContext            ) )
    {
        return ( FALSE ) ;
    }
    // Make the right hand view the edit control.
    if ( FALSE ==
            m_wndSplitter.CreateView ( 1                ,
                                       0                ,
                                    RUNTIME_CLASS(CFindView),
                                       CSize ( 0 , Rect.Height ( ) / 2),
                                       pContext          ) )
    {
        return ( FALSE ) ;
    }

    return ( TRUE ) ;
}

void CChildFrame :: OnSize ( UINT nType , int cx , int cy )
{

    CMDIChildWnd::OnSize(nType, cx, cy);

    CRect rect;
    GetWindowRect( &rect );

    if ( TRUE == m_bSplitterCreated )
    {
        rect.bottom -= ( GetSystemMetrics ( SM_CYFRAME )  +
                         GetSystemMetrics ( SM_CYBORDER ) +
                         GetSystemMetrics ( SM_CYVSCROLL ) ) ;
        m_wndSplitter.SetRowInfo ( 0 , rect.Height() / 2 , 20 ) ;
        m_wndSplitter.SetRowInfo ( 1 , rect.Height() / 2 , 20 ) ;
        m_wndSplitter.RecalcLayout ( ) ;
    }
}

void CChildFrame :: OnGetMinMaxInfo ( MINMAXINFO FAR * lpMMI )
{
    // This is ugly.  However, the darn CScrollView that does
    // CFormView is derived from doesn't allow a clean way to set the
    // minimums from the view.  You would think that I'm not the only
    // one who wants this!
    CWnd::OnGetMinMaxInfo ( lpMMI ) ;
    lpMMI->ptMinTrackSize.y = 300 ;
    lpMMI->ptMinTrackSize.x = 280 ;
}
