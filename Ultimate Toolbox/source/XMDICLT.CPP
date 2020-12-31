// ==========================================================================
// 							Class Implementation : COXMDIClient
// ==========================================================================

// Source file : xmdiclt.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "xmdiclt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// COXMDIClient

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
	//	static  WNDPROC pfnSuper;
	// --- The new window procedure of this Object.

// Data members -------------------------------------------------------------
// protected:

	//	COXDIB		m_bmpBackGround;
	// --- the wallpaper of the mainframe
	
	//	CPalette*	m_pPictPalette;
	// --- the palette of the wallpaper 
	
	//	CBitmap*	m_pTotalNewBitmap;
	// --- the Bitmap of the wallpaper 
	
	//	COLORREF	m_rgbBkColor;
	// --- The Background color of the wallpaper

	//	EWallOrg	m_eWallPaperOrganisation;
	// ---- the organisation of the wallpaper like center, tile,..

	//	CSize		m_sizeClient;
	// --- The Size of the mainframe Client area = Size of the MDI CLIENT

	//	CSize 		m_DibSize;
	// --- The Size of the wallpaper bitmap
	
	//	HBITMAP		m_hOldDestBitmap;
	// --- Handle of the bitmap that was initially present in the Destination DC

	//	HBITMAP		m_hOldSrcBitmap;
	// --- Handle of the bitmap that was initially present in the Source DC

	//	CDC			m_MemDCSrc;
	// --- the Source Memory DC

	//	CDC			m_MemDCDest;
	// --- the the destination Memory DC

// Member functions ---------------------------------------------------------
// public:

COXMDIClient::COXMDIClient()
	:
	m_sizeClient(0,0),
	m_rgbBkColor(GetSysColor(COLOR_APPWORKSPACE)),
	m_DibSize(0,0),
	m_bFirstCreation(TRUE),
	m_bBackGround(FALSE),
	m_bWin4(FALSE),
	m_hOldDestBitmap(NULL),
	m_hOldSrcBitmap(NULL),
	m_pTotalNewBitmap(NULL),
	m_pPictPalette(NULL)
	{   
#ifdef WIN32
	OSVERSIONINFO VersionInfo;
	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&VersionInfo);
	if (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
		(VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && VersionInfo.dwMajorVersion >= 4))
		m_bWin4 = TRUE;
#endif
	}

BOOL COXMDIClient::SetPaletteState(BOOL bBackGround /* = TRUE */, 
	EPalUpdate ePalUpdate /* = PU_IntelUpdate */)
	{
	BOOL bChange = m_bBackGround != bBackGround;

	m_bBackGround = bBackGround;
	
	if ((bChange && !m_bBackGround && ePalUpdate != PU_NoUpdate) || ePalUpdate == PU_ForceUpdate)
		// Only redraw when we're changing from background to foreground
		{
		// Trigger the WM_ERASEBKGROUND message
		OnDoMDICltRealize((WPARAM)0, MAKELPARAM(1,0));   // same as SendMessage(WM_DOMDICLTREALIZE);
		}

	return TRUE;
	}

BOOL COXMDIClient::GetPaletteState()
	{
	return m_bBackGround;
	}


BOOL COXMDIClient::SetNewBackGround(COLORREF rgbColor /* = GetSysColor(COLOR_APPWORKSPACE) */,
	EWallOrg eWallOrganisation /* = WP_Center */, COXDIB* pDib /* = NULL */)
	{
	BOOL bSuccess = TRUE;

	m_eWallPaperOrganisation = eWallOrganisation;
	m_rgbBkColor = rgbColor;

	if (pDib != NULL  && !m_bFirstCreation )
		{
		ASSERT((WP_FIRST <= (int)eWallOrganisation) && ((int) eWallOrganisation <= WP_LAST));
		
		// Copy all external parameters to internal variables, so we don't have
		// to take in account what happens with those parameters outside our
		// MDI CLIENT object
		m_bmpBackGround = *pDib;
		
		//Place the Bitmap in the memory dc if there is one
		CSize BmpSize;
		
		if (!m_bmpBackGround.IsEmpty())
			// The user is giving us a new DIB to work with
			{
            // .... Replace the bitmap in the DC with the bitmap from the DIB
			CBitmap* pOldSrcBitmap = m_bmpBackGround.MakeBitmap(&m_MemDCSrc, BmpSize);

			if (pOldSrcBitmap == NULL)
				// An Error occurred
				{
			   	// Be sure that we will be working with no Bitmap to paint on our screen
		   		m_bmpBackGround.Empty();
				m_eWallPaperOrganisation = WP_Undefined;
				bSuccess = FALSE;
				}
			else
				{
		        if (m_hOldSrcBitmap == NULL)
				   	// Store the original bitmap handle, so we can select it back in when
					// we destroy this MDI Client object
				   	{
					// Only the first time we can select out the original bitmap and store it
				   	ASSERT(m_hOldSrcBitmap == NULL);

					m_hOldSrcBitmap = (HBITMAP)pOldSrcBitmap->GetSafeHandle();
			   		}
			   	else 
	            	// ... The bitmap we just selected out is a bitmap we allocated ourselves
					// ... so we must delete it too
	            	delete pOldSrcBitmap;

				m_pPictPalette = m_bmpBackGround.GetPalette();
				m_DibSize = m_bmpBackGround.GetSize();
			
				// Depending on the screen organisation and color and DIB, build up the 
				// resulting Memory DC that will be used finally in the OnEraseBackGround
				// function to be copied from into the screen DC
				if (!PrepareMemDC(m_sizeClient.cx, m_sizeClient.cy))
					// An Error occurred
					{
				   	// Be sure that we will be working with no Bitmap to paint on our screen
			   		m_bmpBackGround.Empty();
					bSuccess = FALSE;
					}
				}
		    }
		}
	else
	   	{             
	   	// Be sure that we will be working with no Bitmap to paint on our screen
	   	m_bmpBackGround.Empty();
		m_DibSize = CSize(0,0);
	   	}	                                   
	   	                                                       
	// Trigger the WM_ERASEBKGROUND message
	OnDoMDICltRealize((WPARAM)0, MAKELPARAM(1,0));   // same as SendMessage(WM_DOMDICLTREALIZE);
	RedrawWindow(NULL, NULL,
        RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
        
    return bSuccess;
	}
	
COXMDIClient::~COXMDIClient()
	{
	if (m_hOldDestBitmap != NULL)
		{
		// first select the new ones out and delete them afterwards
		CBitmap* ptemp3 = m_MemDCDest.SelectObject(CBitmap::FromHandle(m_hOldDestBitmap));
		delete ptemp3;
	    }
	    
	if (m_hOldSrcBitmap != NULL)
		{
		// first select the new ones out and delete them afterwards
		CBitmap* ptemp4 = m_MemDCSrc.SelectObject(CBitmap::FromHandle(m_hOldSrcBitmap));
		delete ptemp4;
	    }
	
	}

// protected:
BOOL COXMDIClient::PrepareMemDC(int nWidth, int nHeight)
	// --- In  : nWidth : The needed Width of the bitmap in the Destination MemDC
	//			 nHeight : The needed Height of the bitmap in the Destination MemDC
	// --- Out : 
	// --- Returns : TRUE if succeeded
	// --- Effect : Builds a Destination Memory DC out of a given bitmap and organisation
{
	// If there isn't a dib loaded, we don't need do all this calculating
	if (m_bmpBackGround.IsEmpty() || m_DibSize.cy <= 0 || m_DibSize.cx <= 0)
		return FALSE;

    BeginWaitCursor();
    
	int i,j;
    CRect TempDibRect(0,0,0,0);
	CPalette* pOldDestPal = NULL;
	CPalette* pOldSrcPal = NULL;
	BOOL bResult = TRUE;
    
	switch(m_eWallPaperOrganisation)
	{
		case WP_Tile:
		    // create a new bitmap which is compatible with the source DC but 
		    // which has other dimensions. We will use the changed dimensions
		    // to copy later one new build bitmap into a new DC.  This is done 
		    // because a memdc can only be used to copy ONE bmp into it.	
	    	m_pTotalNewBitmap = new CBitmap;
		    bResult = m_pTotalNewBitmap->CreateCompatibleBitmap(&m_MemDCSrc, nWidth, nHeight);
			if (bResult)
	        {
		        // Get the DIB's palette, then select it into DC
				if (m_pPictPalette != NULL)
				{
					// ... Select as background since we have
					//     already realized in forground if needed
					pOldDestPal = m_MemDCDest.SelectPalette(m_pPictPalette, TRUE);
				}
		        // select the compatible bmp into the new Destination memDC
		    	CBitmap* pOldDestBitmap = m_MemDCDest.SelectObject(m_pTotalNewBitmap);
                if (m_hOldDestBitmap == NULL)
					m_hOldDestBitmap = (HBITMAP)pOldDestBitmap->GetSafeHandle();
			    else
					delete pOldDestBitmap;

			    // Calculate the Tiling organisation and copy each tile to the Destination
				// MemDC where we selected a bitmap in with Client Area dimensions
				for (i = 0; i < nHeight; i += m_DibSize.cy)
					for (j = 0; j < nWidth; j += m_DibSize.cx)
					{
						TempDibRect =  CRect(CPoint(j, i), m_DibSize);
						m_MemDCDest.BitBlt(TempDibRect.left, TempDibRect.top,
							m_DibSize.cx, m_DibSize.cy, &m_MemDCSrc, 0, 0, SRCCOPY);
					}
				
				// ... Reselect old palette
				if (pOldDestPal != NULL)
				{
					m_MemDCDest.SelectPalette(pOldDestPal, TRUE);
				}
			}
				             			    
				break;
		case WP_Scale:

	    	m_pTotalNewBitmap = new CBitmap;
		    	
	    	// Get the DIB's palette, then select it into DC
			if (m_pPictPalette != NULL)
				{
				// ... Select as background since we have
				//     already realized in forground if needed
				pOldSrcPal = m_MemDCSrc.SelectPalette(m_pPictPalette, TRUE);
				}
			bResult = m_pTotalNewBitmap->CreateCompatibleBitmap(&m_MemDCSrc, nWidth, nHeight);
		    if (bResult)
		        {
				if (m_pPictPalette != NULL)
				{
					// ... Select as background since we have
					//     already realized in forground if needed
					pOldDestPal = m_MemDCDest.SelectPalette(m_pPictPalette, TRUE);
				}

		    	// ... Make sure to use the stretching mode best for color pictures
#ifdef WIN32
				::SetStretchBltMode(m_MemDCDest.m_hDC, COLORONCOLOR);
#else		    	
				::SetStretchBltMode(m_MemDCDest.m_hDC, STRETCH_DELETESCANS);
#endif
		    			    	
		    	CBitmap* pOldDestBitmap = m_MemDCDest.SelectObject(m_pTotalNewBitmap);
                if (m_hOldDestBitmap == NULL)
					m_hOldDestBitmap = (HBITMAP)pOldDestBitmap->GetSafeHandle();
			    else
					delete pOldDestBitmap;
				    
			    VERIFY(m_MemDCDest.StretchBlt(0, 0, nWidth, nHeight, &m_MemDCSrc, 0, 0, 
			    	m_DibSize.cx, m_DibSize.cy, SRCCOPY));
			    	
			    // ... Reselect old palette
				if (pOldDestPal != NULL)
				{
					m_MemDCDest.SelectPalette(pOldDestPal, TRUE);
				}	
		    }

		    // ... Reselect old palette
			if (pOldSrcPal != NULL)
			{
				m_MemDCSrc.SelectPalette(pOldSrcPal, TRUE);
			}	
	
				break;	    	
			case WP_Center:
				break;                             
			default:
				break;
	}             
	
	EndWaitCursor();	
	return bResult;
}

BEGIN_MESSAGE_MAP(COXMDIClient, CWnd)
	//{{AFX_MSG_MAP(COXMDIClient)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_DOMDICLTREALIZE, OnDoMDICltRealize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Message handlers ---------------------------------------------------------
BOOL COXMDIClient::OnEraseBkgnd(CDC* pDC)
	{
	CPalette* pOldPal = NULL;

	// Erase only the area needed
	// We don't need to paint a special background color, if the screen organisation
	// is other than CENTER because this is the only organisation that does not
	// cover the entire Client area
	if (m_rgbBkColor != pDC->GetBkColor() && (m_eWallPaperOrganisation == WP_Center) ||
		m_bmpBackGround.IsEmpty())
		{
	    // Make a brush to erase the background
		//
		CBrush NewBrush(m_rgbBkColor);
		
		pDC->SetBrushOrg(0,0);
		
		CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&NewBrush);
		
		// Paint the background....
		//
		pDC->PatBlt(0, 0, m_sizeClient.cx,
			m_sizeClient.cy,PATCOPY);
			
		pDC->SetBkColor(m_rgbBkColor);
		
		// Reselect the Old Brush
		pDC->SelectObject(pOldBrush);
		}
	else
		CWnd::OnEraseBkgnd(pDC);	
	
	//Place the Bitmap if there is one
	if (!m_bmpBackGround.IsEmpty()  && !m_bFirstCreation)
		{
	    // Get the DIB's palette, then select it into DC
		if (m_pPictPalette != NULL)
			{
			// ... Select as background since we have
			//     already realized in forground if needed
			pOldPal = pDC->SelectPalette(m_pPictPalette, TRUE);
			if (pOldPal != NULL)
				pDC->RealizePalette();
			}


		CRect DibRect(CPoint(0,0), m_DibSize);
		// centered rectangle
		CRect CenteredDibRect(CPoint(m_sizeClient.cx - (m_DibSize.cx>>1),
							  m_sizeClient.cy - (m_DibSize.cy>>1)),
							  m_DibSize);
			
		// Paint bitmap
	   	//
		switch(m_eWallPaperOrganisation)
			{
			case WP_Center:
				pDC->BitBlt(CenteredDibRect.left, CenteredDibRect.top,
					CenteredDibRect.Width(), CenteredDibRect.Height(),
					&m_MemDCSrc, 0, 0, SRCCOPY);
					
				break;
			case WP_Tile:
			case WP_Scale:
				pDC->BitBlt(0, 0,
					m_sizeClient.cx, m_sizeClient.cy, &m_MemDCDest, 0, 0, SRCCOPY);
				break;                             
			default:
				break;
			}
			
		// ... Reselect old palette
		if (pOldPal != NULL)
			{
			pDC->SelectPalette(pOldPal, TRUE);
			}
				
	    }               
		
	return TRUE;        
	
	}

WNDPROC  COXMDIClient::pfnSuper = NULL;

WNDPROC* COXMDIClient::GetSuperWndProcAddr()
	{
	return &pfnSuper;
	}

void COXMDIClient::OnSize(UINT nType, int cx, int cy)
	{
	CWnd::OnSize(nType, cx, cy);
	
    // if the app is just starting up, save the window
    // dimensions and get out

	// This is just done once at the first time this message is processed
	if (m_bFirstCreation)
		{
		// make the memory dc equal to the clientscreen dc
		CClientDC dc(this);
		if (m_MemDCSrc.CreateCompatibleDC(&dc) && m_MemDCDest.CreateCompatibleDC(&dc))
			{
			m_bFirstCreation = FALSE;
			}
		}

    if ((m_sizeClient.cx == 0) && (m_sizeClient.cy==0))
        {
        m_sizeClient.cx = cx;
        m_sizeClient.cy = cy;

        return;
        }
        
    // if the size hasn't changed, break and pass to default

    if ((m_sizeClient.cx == cx) && ( m_sizeClient.cy == cy))
        return;
    
    // window size has changed so save new dimensions and force
    // entire background to redraw, including icon backgrounds

    m_sizeClient.cx = cx;
    m_sizeClient.cy = cy;
    
    // build the memDC that will hold the entire clientscreen image
	if (!PrepareMemDC(cx, cy))
		return;
    
    switch(m_eWallPaperOrganisation)
		{
		case WP_Tile:
			break;
		case WP_Scale:
		case WP_Center:
			RedrawWindow(NULL, NULL,
       			RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
			break;                             
		default:
			break;
		} 
                 
    return; 
	}

LRESULT COXMDIClient::OnDoMDICltRealize(WPARAM wParam, LPARAM)
	{       
	if ((HWND)wParam == m_hWnd)
		return 0L;
		
	if ((m_eWallPaperOrganisation == WP_Center && m_bmpBackGround.IsEmpty())
		|| !m_bmpBackGround.IsEmpty())
		{
	    TRACE(_T("In COXMDIClient::OnDoRealize\n"));

	    CPalette* pOldPal = NULL;

	    CFrameWnd* pAppFrame = (CFrameWnd*)GetParent();
		ASSERT(pAppFrame->IsKindOf(RUNTIME_CLASS( CFrameWnd )));

		CClientDC appDC(pAppFrame);
	    int nColorsChanged(0);
	    // Get the DIB's palette, then select it into DC
		if (m_pPictPalette != NULL)
			{
			// ... Select as background because wallpaper is always background
			pOldPal = appDC.SelectPalette(m_pPictPalette, m_bBackGround);

			// match the selected palette to the system palette when we get active
			if (pOldPal != NULL)
				nColorsChanged = appDC.RealizePalette();
			}
	
		if (nColorsChanged > 0)
			Invalidate(TRUE);
			
		if (pOldPal != NULL)
			// ... Reselect old palette
			appDC.SelectPalette(pOldPal, TRUE);
		}
			
	return 0L;
	}
