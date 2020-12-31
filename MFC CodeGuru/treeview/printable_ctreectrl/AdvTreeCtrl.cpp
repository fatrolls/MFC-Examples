//  ---------------------------------------------------------
//
//      ( C )     Copyright C - Channel Eng. AG 1998
//      Use or copying of all or any part of the document,
//      except as permitted by the License Agreement is
//      prohibited.
//
//      Author  : Michael Wild, 5063  C - Channel Eng. AG
//
//      Purpose : 
//      This File contains the class CAdvancedTreeCtrl
// 
//      Creation date: April 28, 1998
//
//  ---------------------------------------------------------

#include "stdafx.h"
#include "PrintTree.h"
#include "AdvTreeCtrl.h"

#include "winerror.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeCtrl

CAdvancedTreeCtrl::CAdvancedTreeCtrl()
    : m_imglDrives()
     ,m_PagingInfos()
{
    m_bContinuePrinting             = FALSE;
    m_lNumberOfItems                = 0;
    m_lPageStart                    = 0;
    m_hPageStartingItem             = NULL;
    m_ActualPage.m_hStartItem       = NULL;
    m_ActualPage.m_iNumberOfItems   = 0;
    m_dwLastError                   = 0;
}

CAdvancedTreeCtrl::~CAdvancedTreeCtrl()
{}

BEGIN_MESSAGE_MAP(CAdvancedTreeCtrl, CTreeCtrl)
    //{{AFX_MSG_MAP(CAdvancedTreeCtrl)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTreeCtrl message handlers

void CAdvancedTreeCtrl::InitImageList()
{
	//	Load Icons an generate a iconlist
    m_imglDrives.Create (IDR_DRIVEIMAGES, 16, 1, RGB (255, 0, 255));
    SetImageList(&m_imglDrives, TVSIL_NORMAL);
}

void CAdvancedTreeCtrl::MakePaging( CDC* pDC, CPrintInfo* pInfo )
{
    // Must be true
    assert( NULL != pInfo );
    assert( NULL != pDC );

    // Remove all Items from the Array first
    m_PagingInfos.RemoveAll();

    // Get first visible Item
    HTREEITEM hItem = GetRootItem();

    // Reset Class-Members
    m_lNumberOfItems    = 0;

    // Set the first Item as the first Pagestarting-item
    m_hPageStartingItem  = hItem;

    // Save the Top of the Pagestarting-item
    CRect  itemRect;
    GetItemRect( hItem, &itemRect, FALSE );
    m_lPageStart = itemRect.top;

    // Do the Paging stuff
    StartPaging( pDC, pInfo, hItem );

    // End and Clean up after Paging 
    EndPaging( pInfo );
}

void CAdvancedTreeCtrl::StartPaging( CDC* pDC, CPrintInfo* pInfo, HTREEITEM hItem )
{
    // Must be true
    assert( NULL != pInfo );
    assert( NULL != pDC );

    // Local variables
    CRect       itemRect;

    // Loop until ItemHandle is NULL == End of the Tree
    while( hItem )
    {
        // Count the Numbers of Items
        ++m_lNumberOfItems;

        // Get Item-Rect
        GetItemRect( hItem, &itemRect, FALSE );

        // Convert coordinates of DrawRectangle 
        CRect pagingRect = pInfo->m_rectDraw;
        pDC->DPtoLP( &pagingRect );

        // Make Rect with paged Area
        CRect pagedRect = itemRect;
        pagedRect.top   = m_lPageStart;

        // Is the Page full
        if( pagingRect.Height() < ( pagedRect.Height() ) )
        {
            // Fill the PageInfos into the Array
            PagingInfos locInfo;
            locInfo.m_hStartItem        = m_hPageStartingItem;
            locInfo.m_iNumberOfItems    = m_lNumberOfItems-1;
            m_PagingInfos.Add( locInfo );

            // Reset the Paging parameters
            m_lNumberOfItems            = 1;
            m_hPageStartingItem         = hItem;
            m_lPageStart                = itemRect.top;
        }
        
        // Get Child Item of actual Item
        HTREEITEM hChildItem = GetChildItem( hItem );

        // Only go to Subtree if visible 
        if( hChildItem == GetNextVisibleItem( hItem )&&( NULL != hChildItem ) )
        {
            StartPaging( pDC, pInfo, hChildItem );
        }

        // Get next Item
        hItem = GetNextItem( hItem, TVGN_NEXT );
    }
}

void CAdvancedTreeCtrl::EndPaging( CPrintInfo* pInfo )
{
    // Locals
    PagingInfos locInfo;

    // Fill up the Infos of the last Page
    locInfo.m_hStartItem        = m_hPageStartingItem;
    locInfo.m_iNumberOfItems    = m_lNumberOfItems;

    // Reset Number
    m_lNumberOfItems            = 0;

    // Add the last Page
    m_PagingInfos.Add( locInfo );

    // Set Pagenumber
    pInfo->SetMaxPage( m_PagingInfos.GetSize() );
}

void CAdvancedTreeCtrl::DrawTreeCtrl( CDC * pDC, CPrintInfo* pInfo )
{
    // Must be true
    assert( NULL != pDC );

    // Local Variables
    CRect rcBounds;
    HTREEITEM hItem = NULL;

    // Don't print Pages without Information in the Paging-Array
    if( pInfo->m_nCurPage <= (UINT)m_PagingInfos.GetSize() )
    {
        // Othervise it won't start printing
        m_bContinuePrinting = TRUE;

        // Get Infos of the actual Page
        m_ActualPage = m_PagingInfos.GetAt( pInfo->m_nCurPage-1 );

        // Set Handle for the actual Page
        hItem = m_ActualPage.m_hStartItem;

        // Offset for the scrolled Part of the Tree. 
        // Othervise it only prints from the first visible Item
        GetItemRect( hItem, &rcBounds, FALSE );
        pDC->OffsetWindowOrg( rcBounds.left, rcBounds.top );

        // Loop until Number of Items is printed
        while( 0 != m_ActualPage.m_iNumberOfItems )
        {
            // Iterate through the Tree
            DrawNodes( pDC, pInfo, hItem );

            // If you were trap on a Childnode, you have to go
            // back to the next Parent and Print further.
            if( 0 != m_ActualPage.m_iNumberOfItems )
            {
                HTREEITEM hNextParentItem = NULL;

                // Get the next valid Parent-Node
                while( NULL == hNextParentItem ) 
                {
                    hItem = GetParentItem( hItem );
                    hNextParentItem = GetNextItem( hItem, TVGN_NEXT );
                }

                // Set Hadle to continue
                hItem = hNextParentItem;
            }
        }

        // If all Pages are printed
        if( pInfo->m_nCurPage == (UINT)m_PagingInfos.GetSize() )
        {
            // Stop printing
            m_bContinuePrinting = FALSE;
        }
    }
    else
    {
        // Should never happen
        assert( pInfo->m_nCurPage <= (UINT)m_PagingInfos.GetSize() );
    }
}

void CAdvancedTreeCtrl::DrawNodes( CDC * pDC, CPrintInfo* pInfo, HTREEITEM actualItem )
{
    // Loop until Handle is NULL
    while( ( NULL != actualItem ) && ( 0 != m_ActualPage.m_iNumberOfItems ) )
    {
        // Must be true
        assert( NULL != actualItem );
        assert( NULL != pDC );
        assert( 0    != m_ActualPage.m_iNumberOfItems );

        // Locals
        CRect       rect;
        CFont       itemFont;
        CFont*      pOldFont;
        LOGFONT     logfont;
        BOOL        bResult;

        // Text Output to DC
            // Use window font
            CFont *pFont = GetFont();
            pFont->GetLogFont( &logfont );

            // Create Font with local Font-Struct
            bResult = itemFont.CreateFontIndirect( &logfont );

            // Could not create the Font
            assert( bResult );

            // Set new Font
            pOldFont = pDC->SelectObject( &itemFont );

            // Must be true
            assert( NULL != pOldFont );

            // Get Item Text
            CString sItem = GetItemText( actualItem );
            
            // Get Item-Rect
            GetItemRect( actualItem, &rect, TRUE );

            // Set Background-Color
            pDC->SetBkColor( GetSysColor( COLOR_WINDOW ) );

            // Write Item-Text to DC
            pDC->TextOut( rect.left+2, rect.top, sItem );
            
            // Set Old Font
            pOldFont = pDC->SelectObject( pOldFont );

            // Must be true
            assert( NULL != pOldFont );

        // Icon Output to DC
        if( 0 == m_dwLastError )
        {
            int     nImage, nSelectedImage;

            // Get Image of the Node
            GetItemImage( actualItem, nImage, nSelectedImage );

            // Is Overlay-Image set???
            if( GetItemState( actualItem, TVIS_OVERLAYMASK ) & TVIS_OVERLAYMASK )
            {
                // If Overlay-Image is set
                HANDLE hDib = ImageToDIB( &m_imglDrives, nImage, FromHandle( m_hWnd ), TRUE, actualItem );

                if( 0 == hDib )
                {
                    // Load String from Resource
                    CString locStr1, locStr2;
                    locStr1.LoadString( IDS_DIB_CONVERT_FAILED );
                    locStr2.Format( locStr1, m_dwLastError );
                    if( 0 == m_dwLastError )
                        m_dwLastError = ERROR_CAN_NOT_COMPLETE; 

                    AfxMessageBox( locStr2 );
                    return;
                }

                // Print DIBs
                if( FALSE == PrintDIB( pDC->m_hDC, hDib, rect.left-16, rect.top ) )
                {
                    AfxMessageBox( IDS_DIB_PRINT_FAILED );
                }

                // Free GlobalMemory
                GlobalFree( hDib );
            }
            else
            {
                // Print DIBs
                if( FALSE == PrintDIB( pDC->m_hDC, m_dibArray[nImage], rect.left-16, rect.top ) )
                {
                    AfxMessageBox( IDS_DIB_PRINT_FAILED );
                }
            }

            // Line Output to DC
            DrawTreeLines( pDC, actualItem, rect ); 

            // Buttons Output to DC
            DrawTreeButtons( pDC, actualItem, rect ); 
        }

        // Decrement the number of Items still to Print
        --m_ActualPage.m_iNumberOfItems;

        HTREEITEM hChildItem = NULL;

        // If all Items are printed, the stop
        if( 0 == m_ActualPage.m_iNumberOfItems )
        {
            break;
        }
        else
        {
            // Get Child Item of actual Item
            hChildItem = GetChildItem( actualItem );

            // Only go to Subtree if visible 
            if( hChildItem == GetNextVisibleItem( actualItem ) )
            {
                // Iterate to Subtree
                DrawNodes( pDC, pInfo, hChildItem );
            }

            // Get next Item
            actualItem = GetNextItem( actualItem, TVGN_NEXT );
        }
    }
}

HANDLE CAdvancedTreeCtrl::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal ) 
{
    // Local Variables
    BITMAP                  bm;
    BITMAPINFOHEADER        bi;
    LPBITMAPINFOHEADER      lpbi;
    DWORD                   dwLen;
    HANDLE                  hDIB;
    HDC                     hDC;
    HPALETTE                hPal;

    // Always a safe Handle
    ASSERT( bitmap.GetSafeHandle() );

    // The function has no arg for bitfields
    if( BI_BITFIELDS == dwCompression )
        return NULL;

    // If a palette has not been supplied use defaul palette
    hPal = (HPALETTE)pPal->GetSafeHandle();
    if( NULL == hPal )
    {
        hPal = (HPALETTE)GetStockObject( DEFAULT_PALETTE );
    }

    // If fails no resource available
    ASSERT( NULL != hPal );

    // Get bitmap information
    bitmap.GetObject( sizeof(bm), (LPSTR)&bm );

    // Initialize the bitmapinfoheader
    bi.biSize               = sizeof(BITMAPINFOHEADER);
    bi.biWidth              = bm.bmWidth;
    bi.biHeight             = bm.bmHeight;
    bi.biPlanes             = 1;
    bi.biBitCount           = (unsigned short)( bm.bmPlanes * bm.bmBitsPixel );
    bi.biCompression        = dwCompression;
    bi.biSizeImage          = 0;
    bi.biXPelsPerMeter      = 0;
    bi.biYPelsPerMeter      = 0;
    bi.biClrUsed            = 0;
    bi.biClrImportant       = 0;

    // Compute the size of the  infoheader and the color table
    int nColors = ( 1 << bi.biBitCount );
    if( 256 < nColors )
    {
        nColors = 0;
    }

    dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

    // We need a device context to get the DIB from
    hDC = ::GetDC( NULL );
    hPal = SelectPalette( hDC, hPal, FALSE );
    RealizePalette( hDC );

    // If fails no resource available
    ASSERT( NULL != hPal );
    ASSERT( NULL != hDC );

    // Allocate enough memory to hold bitmapinfoheader and color table
    hDIB = GlobalAlloc( GMEM_FIXED, dwLen );

    // Memory allocation failed
    if( NULL == hDIB )
    {
        // Get the ErrorCode
        m_dwLastError = GetLastError();

        SelectPalette( hDC, hPal, FALSE );
        ::ReleaseDC( NULL, hDC );
        return NULL;
    }

    lpbi = (LPBITMAPINFOHEADER)hDIB;
    *lpbi = bi;

    // Call GetDIBits with a NULL lpBits param, so the device driver 
    // will calculate the biSizeImage field 
    GetDIBits( hDC, 
               (HBITMAP)bitmap.GetSafeHandle(), 
               0L, 
               (DWORD)bi.biHeight,
               (LPBYTE)NULL, 
               (LPBITMAPINFO)lpbi, 
               (DWORD)DIB_RGB_COLORS );

    bi = *lpbi;

    // Set the Colorbit as allowed
    if( 1 >= bi.biBitCount )
        bi.biBitCount = 1;
    else if( 4 >= bi.biBitCount )
        bi.biBitCount = 4;
    else if( 8 >= bi.biBitCount )
        bi.biBitCount = 8;
    else
        bi.biBitCount = 24;

    // If the driver did not fill in the biSizeImage field, then compute it
    // Each scan line of the image is aligned on a DWORD (32bit) boundary
    if( 0 == bi.biSizeImage )
    {
        bi.biSizeImage = ( ( ( ( bi.biWidth * bi.biBitCount ) + 31 ) & ~31 ) / 8 ) * bi.biHeight;

        // If a compression scheme is used the result may infact be larger
        // Increase the size to account for this.
        if( BI_RGB != dwCompression )
        {
            bi.biSizeImage = bi.biSizeImage * 3 / 2;
        }
    }

    // Realloc the buffer so that it can hold all the bits
    dwLen += bi.biSizeImage;

    HANDLE locHandle = GlobalReAlloc( hDIB, dwLen, GMEM_MOVEABLE );

    if( NULL == locHandle )
    {
        // Get the ErrorCode
        m_dwLastError = GetLastError();

        // Free memory
        GlobalFree( hDIB );

        // Reselect the original palette
        SelectPalette( hDC, hPal, FALSE );
        ::ReleaseDC( NULL, hDC );
        return NULL;
    }
    
    // Set new Handle
    hDIB = locHandle;

    // Get the bitmap bits
    lpbi = (LPBITMAPINFOHEADER)hDIB;

    // Finally get the DIB
    BOOL bGotBits = GetDIBits( hDC,                             // DC-Handle
                               (HBITMAP)bitmap.GetSafeHandle(), // Bitmaphandle
                               0L,                              // Start scan line
                               (DWORD)bi.biHeight,              // Number of scan lines
                               (LPBYTE)lpbi + (bi.biSize + nColors * sizeof(RGBQUAD)),// address for bitmap bits
                               (LPBITMAPINFO)lpbi,              // address of bitmapinfo
                               (DWORD)DIB_RGB_COLORS);          // Use RGB for color table

    // The getting failed
    if( FALSE == bGotBits )
    {
        // Free memory
        GlobalFree( hDIB );
        hDIB = NULL;
    }

    // Reselect the original palette
    SelectPalette( hDC, hPal, FALSE );
    ::ReleaseDC( NULL, hDC );
    return hDIB;
}

HANDLE CAdvancedTreeCtrl::ImageToDIB( CImageList* pImageList, int iImageNumber, CWnd* pWnd
                                     ,BOOL bOverlay, HTREEITEM actualItem )
{
    // Local Variables
    CBitmap 	bitmap;
	CWindowDC	dc( pWnd );
	CDC 		memDC;
	CRect		rect;
	CPalette    pal;
    IMAGEINFO   imageInfo;

    if( FALSE == pImageList->GetImageInfo( iImageNumber, &imageInfo ) )
    {
        // Getting of the Imageinfos failed
        return NULL;
    }

    // Create compatible stuff and select Bitmap
    if( FALSE == memDC.CreateCompatibleDC( &dc ) )
    {
        // Create failed
        return NULL;
    }
    if( FALSE == bitmap.CreateCompatibleBitmap( &dc, 
                                                imageInfo.rcImage.bottom-imageInfo.rcImage.top, 
                                                imageInfo.rcImage.right-imageInfo.rcImage.left ) )
    {
        // Create failed
        return NULL;
    }

	CBitmap* pOldBitmap = memDC.SelectObject( &bitmap );
    if( NULL == pOldBitmap )
    {
        // Select failed
        return NULL;
    }

    // Local Variables for Draw
    CPoint point( 0, 0);
    UINT nStyle = ILD_NORMAL;

    // Is there an Overlay
    if( TRUE == bOverlay )
    {
        TV_ITEM     tv_item;
    
        // Set up the Item-Struct
        tv_item.hItem       = actualItem;

        // Get the full Item-Struct
        GetItem( &tv_item );

        // Set the wanted style
        nStyle = ILD_TRANSPARENT|( tv_item.state & TVIS_OVERLAYMASK );
    }

    // Draw Image to the compatible DC
    if( FALSE == pImageList->Draw( &memDC, iImageNumber, point, nStyle ) )
    {
        // Drawing of the Image failed
        return NULL;
    }

	// Create logical palette if device support a palette
	if( dc.GetDeviceCaps( RASTERCAPS ) & RC_PALETTE )
	{
		UINT        nSize   = sizeof(LOGPALETTE) + ( sizeof(PALETTEENTRY) * 256 );
		LOGPALETTE* pLP     = (LOGPALETTE*)new BYTE[nSize];
		pLP->palVersion     = 0x300;

		pLP->palNumEntries = (unsigned short)GetSystemPaletteEntries( dc, 0, 255, pLP->palPalEntry );

		// Create the palette
		pal.CreatePalette( pLP );

        // Free memory
		delete[] pLP;
	}

	memDC.SelectObject( pOldBitmap );

	// Convert the bitmap to a DIB
	return DDBToDIB( bitmap, BI_RGB, &pal );
}

void CAdvancedTreeCtrl::CreateDibArrays( void )
{
    // Icon-Arrays
    int iNumber = m_imglDrives.GetImageCount();
    int iCounter;

	for( iCounter = 0; iCounter <iNumber; ++iCounter )
    {
        // Convert Image to DIB
        HANDLE hDib = ImageToDIB( &m_imglDrives, iCounter, FromHandle( m_hWnd ) );
        m_dibArray.Add( hDib );
        if( 0 == hDib )
        {
            // Load String from Resource
            CString locStr1, locStr2;
            locStr1.LoadString( IDS_DIB_CONVERT_FAILED );
            locStr2.Format( locStr1, m_dwLastError );
            if( 0 == m_dwLastError )
                m_dwLastError = ERROR_CAN_NOT_COMPLETE; 

            // Show Errormessage
            AfxMessageBox( locStr2 );
            return;
        }
    }

    // Button-Arrays
    CBitmap bitmap1;
    CBitmap bitmap2;
    bitmap1.LoadBitmap( IDB_PLUSBUTTON );
    bitmap2.LoadBitmap( IDB_MINUSBUTTON );

    // Convert Bitmaps to DIB
    m_dibButtons[0] = DDBToDIB( bitmap1, BI_RGB, NULL );
    m_dibButtons[1] = DDBToDIB( bitmap2, BI_RGB, NULL );

    // Convert Failed
    if( ( 0 == m_dibButtons[0] ) ||
        ( 0 == m_dibButtons[1] ) )
    {
        // Load String from Resource
        CString locStr1, locStr2;
        locStr1.LoadString( IDS_DIB_CONVERT_FAILED );
        locStr2.Format( locStr1, m_dwLastError );
        if( 0 == m_dwLastError )
            m_dwLastError = ERROR_CAN_NOT_COMPLETE; 

        // Show Errormessage
        AfxMessageBox( locStr2 );
        return;
    }
}

void CAdvancedTreeCtrl::DeleteDibArrays( void )
{
    // Icon-Arrays
    int iNumber = m_dibArray.GetSize();
    int iCounter;

	for( iCounter = iNumber-1; iCounter >= 0; --iCounter )
    {
        // Get the handle and remove it from array
        HANDLE hDib = m_dibArray.GetAt( iCounter );
        m_dibArray.RemoveAt( iCounter );

        // Free global memory
        if( 0 != GlobalFree( hDib ) )
        {
            // Show Errormessage
            AfxMessageBox( IDS_DIB_FREE_FAILED );
        }
    }

    // Free unused Memory
    m_dibArray.FreeExtra();

    // Button-Arrays
    if( NULL != m_dibButtons[0] )
    {
        // Free global memory
        if( 0 != GlobalFree( m_dibButtons[0] ) )
        {
            // Show Errormessage
            AfxMessageBox( IDS_DIB_FREE_FAILED );
        }
    }
    if( NULL != m_dibButtons[1] )
    {
        // Free global memory
        if( 0 != GlobalFree( m_dibButtons[1] ) )
        {
            // Show Errormessage
            AfxMessageBox( IDS_DIB_FREE_FAILED );
        }
    }
}

BOOL CAdvancedTreeCtrl::PrintDIB( HDC hDC, HANDLE hDib, int xOrigin, int yOrigin ) 
{
    // Forget it!!!
    if( 0 == hDib )
    {
        return FALSE;
    }

    int                 iBits           = 0; 
    WORD                dwPaletteSize   = 0;
    LPBITMAPINFOHEADER  lpDIB           = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
    LPBITMAPINFOHEADER  lpbi            = lpDIB;
    LPBITMAPCOREHEADER  lpbc            = (LPBITMAPCOREHEADER)lpbi;

    //  With the BITMAPINFO format headers, the size of the palette
    //  is in biClrUsed. However, in the BITMAPCORE-style headers, it
    //  depends on the bits per pixel ( = 2 raised to the power of
    //  bits/pixel).
    if( lpbi->biSize != sizeof(BITMAPCOREHEADER) )
    {
       iBits = lpbi->biBitCount;
    }
    else
    {
       iBits = lpbc->bcBitCount;
    }

    if( ( lpbi->biSize != sizeof(BITMAPCOREHEADER) ) &&
        ( 0 != lpbi->biClrUsed ) )
    {
        dwPaletteSize = (WORD)lpbi->biClrUsed;
    }
    else
    {
        switch( iBits )
        {
            case 1:
                dwPaletteSize = 2;
                break;
            case 4:
                dwPaletteSize = 16;
                break;
            case 8:
                dwPaletteSize = 256;
                break;
            default:
                // A 24 bitcount DIB has no color table
                dwPaletteSize = 0;
                break;
        }
    }

    if( lpbi->biSize == sizeof(BITMAPCOREHEADER) )
       dwPaletteSize *= sizeof(RGBTRIPLE);
    else
       dwPaletteSize *= sizeof(RGBQUAD);

    LPSTR pBuf = (LPSTR)lpbi + (WORD)lpbi->biSize + dwPaletteSize; 

    iBits  = StretchDIBits( hDC, 
                            xOrigin,              // DestX 
                            yOrigin,              // DestY 
                            lpbi->biWidth,        // nDestWidth 
                            abs(lpbi->biHeight),  // nDestHeight 
                            0,                    // x-coord upper-left corner of source
                            0,                    // y-coord upper-left corner of source
                            lpbi->biWidth,        // width of source rectangle
                            abs(lpbi->biHeight),  // height of source rectangle 
                            pBuf,                 // buffer that holds the bits
                            (LPBITMAPINFO) lpbi,  // lpBitsInfo 
                            DIB_RGB_COLORS,       // wUsage 
                            SRCCOPY);             // raster operation code

    if (lpbi != lpDIB) 
    { 
        GlobalFree((HANDLE)lpbi); 
    } 
    GlobalUnlock(hDib);

    return( ( 0 != iBits ) && ( GDI_ERROR != iBits ) ); 
}

void CAdvancedTreeCtrl::DrawTreeLines( CDC* pDC, HTREEITEM actualItem, CRect rect ) 
{
    // Local Variable
    int ihLineStart  = 20;
    int ihLineEnd    = 30;
    int ivLineStart  = 8;
    int ivLineEnd    = 10;
    int ivLineLenght = 19;

    // Draw Line for Root-Item
    if( actualItem == GetRootItem() )
    {
        // Draw the line for the Rootitem
        POINT pointArray[2];
        pointArray[0] = CPoint( rect.left - ihLineStart, rect.top + ivLineStart );
        pointArray[1] = CPoint( rect.left - ihLineEnd, rect.top + ivLineStart );
        pDC->Polyline( pointArray, 2 );
    }
    else // Lines for all other Items
    {
        // Draw the lines for the other items
        HTREEITEM hParent = actualItem;
        int i = 0;
        while( hParent )
        {
            i += ivLineLenght;
            hParent = GetParentItem( hParent );

            POINT pointArray1[3];
            pointArray1[0] = CPoint( rect.left - ihLineStart, rect.top + ivLineStart );
            pointArray1[1] = CPoint( rect.left - ihLineEnd, rect.top + ivLineStart );

            POINT pointArray2[2];
            pointArray2[0] = CPoint( rect.left - ihLineEnd - i, rect.top + ivLineStart );
            pointArray2[1] = CPoint( rect.left - ihLineEnd - i, rect.top - ivLineEnd );

            HTREEITEM hSibling = GetPrevSiblingItem( actualItem );
            if( NULL != hSibling )
            {
                HTREEITEM hChildItem = GetChildItem( hSibling );
                if( ( NULL != hChildItem ) &&
                    ( hChildItem != GetNextVisibleItem( hSibling ) ) )
                {
                    // Give space for the Button
                    pointArray1[2] = CPoint( rect.left - ihLineEnd, rect.top - ivLineEnd + 4 );
                }
                else
                {
                    pointArray1[2] = CPoint( rect.left - ihLineEnd, rect.top - ivLineEnd );
                }
            }
            else
            {
                pointArray1[2] = CPoint( rect.left - ihLineEnd, rect.top - 2 );
                if( ivLineLenght == i )
                {
                    pointArray2[1] = CPoint( rect.left - ihLineEnd - i, rect.top - ivLineEnd + 4 );
                }
            }

            pDC->Polyline( pointArray1, 3 );


            // Draw vertical Lines
            if( ( NULL != hParent ) &&
                ( NULL != GetNextSiblingItem( hParent ) ) )
            {
                // Draw vertical Lines
                pDC->Polyline( pointArray2, 2 );
            }
        }
    }
}

void CAdvancedTreeCtrl::DrawTreeButtons( CDC* pDC, HTREEITEM actualItem, CRect rect ) 
{
    HTREEITEM hChildItem = GetChildItem( actualItem );
    if( NULL != hChildItem )
    {
        BOOL bResult;
        // Minus Button
        if( hChildItem == GetNextVisibleItem( actualItem ) )
        {
            if( NULL != m_dibButtons[1] )
                bResult = PrintDIB( pDC->m_hDC, m_dibButtons[1], rect.left-34, rect.top+4 );
        }
        else // Plus Button
        {
            if( NULL != m_dibButtons[0] )
                bResult = PrintDIB( pDC->m_hDC, m_dibButtons[0], rect.left-34, rect.top+4 );
        }

        // Error
        if( FALSE == bResult )
        {
            AfxMessageBox( IDS_DIB_PRINT_FAILED );
        }
    }
}

