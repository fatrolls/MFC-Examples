/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "CrashFinder.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

IMPLEMENT_DYNAMIC ( CMainFrame , CMDIFrameWnd )

BEGIN_MESSAGE_MAP ( CMainFrame , CMDIFrameWnd )
  //{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CLOSE ( )
  ON_WM_CREATE ( )
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP ( )

static UINT indicators[ ] =
{
  ID_SEPARATOR      ,
  ID_INDICATOR_CAPS ,
  ID_INDICATOR_NUM  ,
  ID_INDICATOR_SCRL ,
} ;

CMainFrame :: CMainFrame ( )
            : CMDIFrameWnd ( )   ,
              m_wndStatusBar ( ) ,
              m_wndToolBar ( )
{
    ASSERT ( this ) ;
}

CMainFrame :: ~CMainFrame ( )
{
    ASSERT ( this ) ;
}

int CMainFrame :: OnCreate ( LPCREATESTRUCT lpCreateStruct )
{
    ASSERT ( this ) ;

    if ( -1 == CMDIFrameWnd::OnCreate ( lpCreateStruct ) )
    {
        return ( -1 ) ;
    }

    if ( ( !m_wndToolBar.Create ( this )               ) ||
         ( !m_wndToolBar.LoadToolBar ( IDR_MAINFRAME ) )    )
    {
        TRACE0 ( "Failed to create toolbar\n" ) ;
        return ( -1 ) ; // fail to create
    }

    if ( ( !m_wndStatusBar.Create ( this )                          ) ||
         ( !m_wndStatusBar.SetIndicators ( indicators ,
                                           sizeof ( indicators ) /
                                                 sizeof ( UINT ) )  )  )
    {
        TRACE0 ( "Failed to create status bar\n" ) ;
        return ( -1 ) ; // fail to create
    }

    // TODO: Remove this if you don't want tool tips or a resizeable
    // toolbar
    m_wndToolBar.SetBarStyle ( m_wndToolBar.GetBarStyle ( ) |
                               CBRS_TOOLTIPS                |
                               CBRS_FLYBY                   |
                               CBRS_SIZE_DYNAMIC             ) ;

    return ( 0 ) ;
}

LPCTSTR k_FRAME   = _T ( "Frame"  ) ;
LPCTSTR k_STATUS  = _T ( "Status" ) ;
LPCTSTR k_TOP     = _T ( "Top"    ) ;
LPCTSTR k_LEFT    = _T ( "Left"   ) ;
LPCTSTR k_BOTTOM  = _T ( "Bottom" ) ;
LPCTSTR k_RIGHT   = _T ( "Right"  ) ;

BOOL CMainFrame :: PreCreateWindow ( CREATESTRUCT & cs )
{
	CWinApp* App = AfxGetApp();

    int iStatus = App->GetProfileInt ( k_FRAME , k_STATUS , -1 ) ;
    int iTop    = App->GetProfileInt ( k_FRAME , k_TOP    , -1 ) ;
    int iLeft   = App->GetProfileInt ( k_FRAME , k_LEFT   , -1 ) ;
    int iBottom = App->GetProfileInt ( k_FRAME , k_BOTTOM , -1 ) ;
    int iRight  = App->GetProfileInt ( k_FRAME , k_RIGHT  , -1 ) ;

	// Only restore if there is a previously saved position.
    if ( ( -1 != iStatus ) &&
         ( -1 != iTop    ) &&
         ( -1 != iLeft   ) &&
         ( -1 != iBottom ) &&
         ( -1 != iRight  )   )
    {

		// Restore the window's status
		App->m_nCmdShow = iStatus;

		// Restore the window's width and height.
		cs.cx = iRight - iLeft ;
		cs.cy = iBottom - iTop ;

		// The following correction is needed when the taskbar is
		// at the left or top and it is not "auto-hidden"
		RECT WorkArea ;
		SystemParametersInfo ( SPI_GETWORKAREA , 0 , &WorkArea , 0 ) ;
		iLeft += WorkArea.left ;
		iTop += WorkArea.top;

		// make sure the window is not completely out of sight
		int max_x = GetSystemMetrics ( SM_CXVIRTUALSCREEN ) ;
		int max_y = GetSystemMetrics ( SM_CYVIRTUALSCREEN ) ;
		cs.x = min ( iLeft , max_x ) ;
		cs.y = min ( iTop , max_y ) ;
	}

    return ( CMDIFrameWnd::PreCreateWindow ( cs ) ) ;
}

void CMainFrame::OnClose()
{
	// Save main window position
	CWinApp * App = AfxGetApp() ;
	WINDOWPLACEMENT wp ;
	GetWindowPlacement ( &wp ) ;
	App->WriteProfileInt ( k_FRAME      ,
	                       k_STATUS     ,
	                       wp.showCmd    ) ;
	App->WriteProfileInt ( k_FRAME                  ,
	                       k_TOP                    ,
	                       wp.rcNormalPosition.top   ) ;
	App->WriteProfileInt ( k_FRAME                  ,
	                       k_LEFT                   ,
	                       wp.rcNormalPosition.left  ) ;
	App->WriteProfileInt ( k_FRAME                      ,
	                       k_BOTTOM                     ,
	                       wp.rcNormalPosition.bottom    ) ;
	App->WriteProfileInt ( k_FRAME                   ,
	                       k_RIGHT                   ,
	                       wp.rcNormalPosition.right  ) ;

	CMDIFrameWnd :: OnClose ( ) ;
}

#ifdef _DEBUG
void CMainFrame :: AssertValid ( ) const
{
    ASSERT ( this ) ;

    CMDIFrameWnd::AssertValid ( ) ;
}

void CMainFrame :: Dump ( CDumpContext & dc ) const
{
    ASSERT ( this ) ;

    CMDIFrameWnd::Dump ( dc ) ;
}

#endif //_DEBUG


void CMainFrame :: OnGetMinMaxInfo ( MINMAXINFO FAR * lpMMI )
{
    lpMMI->ptMinTrackSize.x = 300 ;
    lpMMI->ptMinTrackSize.y = 400 ;

	CMDIFrameWnd::OnGetMinMaxInfo ( lpMMI ) ;
}
