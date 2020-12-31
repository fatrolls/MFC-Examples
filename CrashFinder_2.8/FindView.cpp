/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "crashfinder.h"
#include "CrashFinderDoc.h"
#include "FindView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CFindView, CFormView)

CFindView :: CFindView()
    : CFormView(CFindView::IDD)
{
    //{{AFX_DATA_INIT(CFindView)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

CFindView :: ~CFindView()
{
}

#ifdef _DEBUG
CCrashFinderDoc * CFindView :: GetDocument ( )
{
    return ( (CCrashFinderDoc *)m_pDocument ) ;
}
#endif

void CFindView :: DoDataExchange ( CDataExchange* pDX )
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFindView)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindView, CFormView)
    //{{AFX_MSG_MAP(CFindView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindView diagnostics

#ifdef _DEBUG
void CFindView :: AssertValid ( ) const
{
    CFormView::AssertValid ( ) ;
}

void CFindView :: Dump ( CDumpContext & dc ) const
{
    CFormView::Dump ( dc ) ;
}
#endif //_DEBUG

#define     MapWindowRect(hwndFrom, hwndTo, lprc) \
                    MapWindowPoints((hwndFrom), (hwndTo), (POINT *)(lprc), 2)

void CFindView :: OnSize ( UINT nType , int cx , int cy )
{

    if ( ( SIZE_MINIMIZED != nType ) &&
         ( cx > 0 )                  &&
         ( cy > 0 )                     )
    {
        CRect cParentRect ;

        GetClientRect ( &cParentRect ) ;

        HDWP hdwp = BeginDeferWindowPos ( 3 ) ;

        CWnd * pFindWnd = GetDlgItem ( IDC_FIND ) ;
        CWnd * pDetailsWnd = GetDlgItem ( IDC_DETAILS ) ;
        CWnd * pClearWnd = GetDlgItem ( IDC_CLEAR ) ;
        if ( ( NULL == pFindWnd    ) ||
             ( NULL == pDetailsWnd ) ||
             ( NULL == pClearWnd   )    )
        {
            return ;
        }

        CRect cFindRect ;
        CRect cDetailsRect ;
        CRect cClearRect ;

        pFindWnd->GetWindowRect ( &cFindRect ) ;
        pDetailsWnd->GetWindowRect ( &cDetailsRect ) ;
        pClearWnd->GetWindowRect ( &cClearRect ) ;

        // Map the screen coordinates to client positions.
        ::MapWindowRect ( HWND_DESKTOP , m_hWnd , &cFindRect ) ;
        ::MapWindowRect ( HWND_DESKTOP , m_hWnd , &cDetailsRect ) ;
        ::MapWindowRect ( HWND_DESKTOP , m_hWnd , &cClearRect ) ;

        // Start moving windows.

        cFindRect.right = cParentRect.right - 8 ;

        hdwp = DeferWindowPos ( hdwp                    ,
                                pFindWnd->m_hWnd        ,
                                NULL                    ,
                                cFindRect.left          ,
                                cFindRect.top           ,
                                cFindRect.Width ( )     ,
                                cFindRect.Height ( )    ,
                                SWP_NOZORDER             ) ;

        cDetailsRect.bottom = cParentRect.bottom - 8 ;
        cDetailsRect.right = cParentRect.right - 8 ;

        hdwp = DeferWindowPos ( hdwp                    ,
                                pDetailsWnd->m_hWnd     ,
                                NULL                    ,
                                cDetailsRect.left       ,
                                cDetailsRect.top        ,
                                cDetailsRect.Width ( )  ,
                                cDetailsRect.Height ( ) ,
                                SWP_NOZORDER             ) ;

        cClearRect.right = cParentRect.right - 8 ;

        hdwp = DeferWindowPos ( hdwp                    ,
                                pClearWnd->m_hWnd       ,
                                NULL                    ,
                                cClearRect.left         ,
                                cClearRect.top          ,
                                cClearRect.Width ( )    ,
                                cClearRect.Height ( )   ,
                                SWP_NOZORDER             ) ;

        EndDeferWindowPos ( hdwp ) ;
    }
}

int CFindView :: OnCreate ( LPCREATESTRUCT lpCreateStruct )
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
    {
		return ( -1 ) ;
    }

	return ( 0 ) ;
}

void CFindView :: OnInitialUpdate ( )
{
	CFormView::OnInitialUpdate ( ) ;

    // Subclass the edit control with my cheezy hex only edit control
    // class.
    BOOL bRet = m_cHexCtrl.SubclassDlgItem ( IDC_HEXEDIT , this ) ;
    ASSERT ( TRUE == bRet ) ;

}

void CFindView :: OnFind ( )
{
    CPtrArray aAddresses ;
    m_cHexCtrl.GetNumbers ( aAddresses ) ;

    if ( 0 != aAddresses.GetSize ( ) )
    {
        CEdit * pDetails = (CEdit*)GetDlgItem ( IDC_DETAILS ) ;
        ASSERT ( NULL != pDetails ) ;
        if ( NULL == pDetails )
        {
            return ;
        }

        CCrashFinderDoc * pDoc = GetDocument ( ) ;
        CSymbolEngine * pSymEng = pDoc->GetSymbolEngine ( ) ;

        CCrashFinderApp * pApp = (CCrashFinderApp*)AfxGetApp ( ) ;


        TCHAR * szSeps ;

        CString strCurr ;
        CString strTotal ;

        if ( TRUE == pApp->m_bOneLine )
        {
            szSeps = _T ( ", " ) ;
        }
        else
        {
            szSeps = _T  ( "\r\n" ) ;
        }

        for ( int i = 0 ; i < aAddresses.GetSize ( ) ; i++ )
        {
            if ( TRUE == GetAddressSymbolString(*pSymEng              ,
                                                (DWORD64)aAddresses[i],
                                                 strCurr              ,
                                                 szSeps              ))
            {
                strTotal += strCurr ;
                strTotal += _T ( "\r\n\r\n" ) ;
            }
        }
	if (TRUE == pApp->m_bInsertText) {
	    pDetails->SetSel(0,0); // we are going to insert the text at the top of the window
	    pDetails->ReplaceSel(strTotal);
	}
	else
	    pDetails->SetWindowText ( strTotal ) ;
    }
}


void CFindView::OnClear()
{
    CEdit * pDetails = (CEdit*)GetDlgItem ( IDC_DETAILS ) ;
    ASSERT ( NULL != pDetails ) ;
    if ( NULL == pDetails )
    {
	return ;
    }
    pDetails->SetWindowText(_T(""));
}
