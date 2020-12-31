#include "stdafx.h"
#include "BkDialogST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef WM_NCLBUTTONDOWN
#define WM_NCLBUTTONDOWN                0x00A1
#define	BKDLGST_DEFINES
#endif

CBkDialogST::CBkDialogST(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CBkDialogST)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Init();
}

CBkDialogST::CBkDialogST(UINT uResourceID, CWnd* pParent)
	: CDialog(uResourceID, pParent)
{
	Init();
}


CBkDialogST::CBkDialogST(LPCTSTR pszResourceID, CWnd* pParent)
	: CDialog(pszResourceID, pParent)
{
	Init();
}

CBkDialogST::~CBkDialogST()
{
	FreeResources();
}

void CBkDialogST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBkDialogST)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBkDialogST, CDialog)
	//{{AFX_MSG_MAP(CBkDialogST)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CBkDialogST::Init()
{
	FreeResources(FALSE);

	// Default drawing bitmap mode
	m_byMode = BKDLGST_MODE_TILE;

	// No EasyMove mode
	m_bEasyMoveMode = FALSE;
} // End of Init

void CBkDialogST::FreeResources(BOOL bCheckForNULL)
{
	if (bCheckForNULL == TRUE)
	{
		// Destroy bitmap
		if (m_hBitmap)	::DeleteObject(m_hBitmap);
#ifndef UNDER_CE
		// Destroy region
		if (m_hRegion)
		{
			::SetWindowRgn(m_hWnd, NULL, FALSE);
			::DeleteObject(m_hRegion);
		} // if
#endif
	} // if

	m_hBitmap = NULL;
#ifndef UNDER_CE
	m_hRegion = NULL;
#endif
	m_dwWidth = 0;
	m_dwHeight = 0;
} // End of FreeResources

void CBkDialogST::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// EasyMove mode
	if (m_bEasyMoveMode == TRUE)
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	
	CDialog::OnLButtonDown(nFlags, point);
} // End of OnLButtonDown

void CBkDialogST::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// If there is a bitmap loaded
	if (m_hBitmap != NULL)
	{
		Invalidate();
	} // if
} // End of OnSize

BOOL CBkDialogST::OnEraseBkgnd(CDC* pDC) 
{
	CRect		rWnd;
	int			nX			= 0;
	int			nY			= 0;

	BOOL	bRetValue = CDialog::OnEraseBkgnd(pDC);

	// If there is a bitmap loaded
	if (m_hBitmap)
	{
		GetClientRect(rWnd);

		CDC			dcMemoryDC;
		CBitmap		bmpMemoryBitmap;
		CBitmap*	pbmpOldMemoryBitmap = NULL;

		dcMemoryDC.CreateCompatibleDC(pDC);
		bmpMemoryBitmap.CreateCompatibleBitmap(pDC, rWnd.Width(), rWnd.Height());
		pbmpOldMemoryBitmap = (CBitmap*)dcMemoryDC.SelectObject(&bmpMemoryBitmap);

		// Fill background 
		dcMemoryDC.FillSolidRect(rWnd, pDC->GetBkColor());

		CDC			dcTempDC;
		HBITMAP		hbmpOldTempBitmap = NULL;

		dcTempDC.CreateCompatibleDC(pDC);
		hbmpOldTempBitmap = (HBITMAP)::SelectObject(dcTempDC.m_hDC, m_hBitmap);

		switch (m_byMode)
		{
			case BKDLGST_MODE_TILE:
				// Tile the bitmap
				while (nY < rWnd.Height()) 
				{
					while(nX < rWnd.Width()) 
					{
						dcMemoryDC.BitBlt(nX, nY, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
						nX += m_dwWidth;
					} // while
					nX = 0;
					nY += m_dwHeight;
				} // while
				break;
			case BKDLGST_MODE_CENTER:
				nX = ((rWnd.Width() - m_dwWidth)/2);
				nY = ((rWnd.Height() - m_dwHeight)/2);
				dcMemoryDC.BitBlt(nX, nY, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
			case BKDLGST_MODE_STRETCH:
				// Stretch the bitmap
				dcMemoryDC.StretchBlt(0, 0, rWnd.Width(), rWnd.Height(), &dcTempDC, 0, 0, m_dwWidth, m_dwHeight, SRCCOPY);
				break;
			case BKDLGST_MODE_TILETOP:
				while(nX < rWnd.Width()) 
				{
					dcMemoryDC.BitBlt(nX, 0, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
					nX += m_dwWidth;
				} // while
				break;
			case BKDLGST_MODE_TILEBOTTOM:
				while(nX < rWnd.Width()) 
				{
					dcMemoryDC.BitBlt(nX, rWnd.bottom - m_dwHeight, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
					nX += m_dwWidth;
				} // while
				break;
			case BKDLGST_MODE_TILELEFT:
				while (nY < rWnd.Height()) 
				{
					dcMemoryDC.BitBlt(0, nY, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
					nY += m_dwHeight;
				} // while
				break;
			case BKDLGST_MODE_TILERIGHT:
				while (nY < rWnd.Height()) 
				{
					dcMemoryDC.BitBlt(rWnd.right - m_dwWidth, nY, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
					nY += m_dwHeight;
				} // while
				break;
			case BKDLGST_MODE_TOPLEFT:
				dcMemoryDC.BitBlt(0, 0, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
			case BKDLGST_MODE_TOPRIGHT:
				dcMemoryDC.BitBlt(rWnd.right - m_dwWidth, 0, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
			case BKDLGST_MODE_TOPCENTER:
				nX = ((rWnd.Width() - m_dwWidth)/2);
				dcMemoryDC.BitBlt(nX, 0, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
			case BKDLGST_MODE_BOTTOMLEFT:
				dcMemoryDC.BitBlt(0, rWnd.bottom - m_dwHeight, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
			case BKDLGST_MODE_BOTTOMRIGHT:
				dcMemoryDC.BitBlt(rWnd.right - m_dwWidth, rWnd.bottom - m_dwHeight, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
			case BKDLGST_MODE_BOTTOMCENTER:
				nX = ((rWnd.Width() - m_dwWidth)/2);
				dcMemoryDC.BitBlt(nX, rWnd.bottom - m_dwHeight, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
				break;
		} // switch

		pDC->BitBlt(0, 0, rWnd.Width(), rWnd.Height(), &dcMemoryDC, 0, 0, SRCCOPY);

		OnPostEraseBkgnd(&dcMemoryDC);

		::SelectObject(dcTempDC.m_hDC, hbmpOldTempBitmap);
		dcMemoryDC.SelectObject(pbmpOldMemoryBitmap);
	} // if

	return bRetValue;
} // End of OnEraseBkgnd

void CBkDialogST::OnPostEraseBkgnd(CDC* pDC)
{
} // End of OnPostEraseBkgnd

// -------------------------------------------------------------------------------------
// Scan a bitmap and return a perfect fit region.
// The caller must release the memory...
// (this method starts with a full region and excludes inside the loop)
// -------------------------------------------------------------------------------------
// Credits for this function go to Vander Nunes
//
#ifndef UNDER_CE
HRGN CBkDialogST::ScanRegion(HBITMAP hBitmap, BYTE byTransR, BYTE byTransG, BYTE byTransB)
{
	// bitmap width and height
	DWORD dwBmpWidth = 0, dwBmpHeight = 0;

	// the final region and a temporary region
	HRGN hRgn = NULL, hTmpRgn = NULL;

	// 24bit pixels from the bitmap
	LPBYTE lpbyPixels = Get24BitPixels(hBitmap, &dwBmpWidth, &dwBmpHeight);
	if (!lpbyPixels) return NULL;

	// create our working region
	hRgn = ::CreateRectRgn(0, 0, dwBmpWidth, dwBmpHeight);
	if (!hRgn) 
	{ 
		delete lpbyPixels; 
		return NULL; 
	} // if

	// ---------------------------------------------------------
	// scan the bitmap
	// ---------------------------------------------------------
	DWORD p=0;
	for (DWORD y=0; y<dwBmpHeight; y++)
	{
		for (DWORD x=0; x<dwBmpWidth; x++)
		{
			BYTE jRed   = lpbyPixels[p+2];
			BYTE jGreen = lpbyPixels[p+1];
			BYTE jBlue  = lpbyPixels[p+0];

			if (jRed == byTransR && jGreen == byTransG && jBlue == byTransB)
			{
				// remove transparent color from region
				hTmpRgn = ::CreateRectRgn(x,y,x+1,y+1);
				::CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				::DeleteObject(hTmpRgn);
			} // if

			// next pixel
			p+=3;
		} // for
	} // for

	// release pixels
	delete lpbyPixels;

	// return the region
	return hRgn;
} // End of ScanRegion
#endif

// -------------------------------------------------------------------------------------
// Return bitmap pixels in 24bits format.
// The caller must release the memory...
// -------------------------------------------------------------------------------------
// Credits for this function go to Vander Nunes
//
#ifndef UNDER_CE
LPBYTE CBkDialogST::Get24BitPixels(HBITMAP hBitmap, LPDWORD lpdwWidth, LPDWORD lpdwHeight)
{
	// a bitmap object just to get bitmap width and height
	BITMAP bmpBmp;

	// pointer to original bitmap info
	LPBITMAPINFO pbmiInfo;

	// bitmap info will hold the new 24bit bitmap info
	BITMAPINFO bmiInfo;

	// width and height of the bitmap
	DWORD dwBmpWidth = 0, dwBmpHeight = 0;

	// ---------------------------------------------------------
	// get some info from the bitmap
	// ---------------------------------------------------------
	::GetObject(hBitmap, sizeof(bmpBmp),&bmpBmp);
	pbmiInfo   = (LPBITMAPINFO)&bmpBmp;

	// get width and height
	dwBmpWidth  = (DWORD)pbmiInfo->bmiHeader.biWidth;
	dwBmpWidth -= (dwBmpWidth%4);                       // width is 4 byte boundary aligned.
	dwBmpHeight = (DWORD)pbmiInfo->bmiHeader.biHeight;

	// copy to caller width and height parms
	*lpdwWidth  = dwBmpWidth;
	*lpdwHeight = dwBmpHeight;
	// ---------------------------------------------------------

	// allocate width * height * 24bits pixels
	LPBYTE lpbyPixels = new BYTE[dwBmpWidth * dwBmpHeight * 3];
	if (!lpbyPixels) return NULL;

	// get user desktop device context to get pixels from
	HDC hDC = ::GetWindowDC(NULL);

	// fill desired structure
	bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiInfo.bmiHeader.biWidth = dwBmpWidth;
	bmiInfo.bmiHeader.biHeight = 0 - (int)dwBmpHeight;
	bmiInfo.bmiHeader.biPlanes = 1;
	bmiInfo.bmiHeader.biBitCount = 24;
	bmiInfo.bmiHeader.biCompression = BI_RGB;
	bmiInfo.bmiHeader.biSizeImage = dwBmpWidth * dwBmpHeight * 3;
	bmiInfo.bmiHeader.biXPelsPerMeter = 0;
	bmiInfo.bmiHeader.biYPelsPerMeter = 0;
	bmiInfo.bmiHeader.biClrUsed = 0;
	bmiInfo.bmiHeader.biClrImportant = 0;

	// get pixels from the original bitmap converted to 24bits
	int iRes = ::GetDIBits(hDC,hBitmap, 0, dwBmpHeight, (LPVOID)lpbyPixels, &bmiInfo, DIB_RGB_COLORS);

	// release the device context
	::ReleaseDC(NULL,hDC);

	// if failed, cancel the operation.
	if (!iRes)
	{
		delete lpbyPixels;
		return NULL;
	} // if

	// return the pixel array
	return lpbyPixels;
} // End of Get24BitPixels
#endif

//
// Parameters:
//		[IN]	bActivate
//				TRUE if EasyMove mode must be activated.
//
// Return value:
//		BKDLGST_OK
//			Function executed successfully.
//
DWORD CBkDialogST::ActivateEasyMoveMode(BOOL bActivate)
{
	m_bEasyMoveMode = bActivate;

	return BKDLGST_OK;
} // End of ActivateEasyMoveMode

//
// Parameters:
//		[IN]	nBitmap
//				Resource ID of the bitmap to use as background.
//		[IN]	crTransColor
//				A COLORREF value indicating the color to "remove" from the
//				bitmap. When crTransColor is specified (different from -1L)
//				a region will be created using the supplied bitmap and applied
//				to the window.
//
// Return value:
//		BKDLGST_OK
//			Function executed successfully.
//		BKDLGST_INVALIDRESOURCE
//			The resource specified cannot be found or loaded.
//		BKDLGST_FAILEDREGION
//			Failed creating region
//
DWORD CBkDialogST::SetBitmap(int nBitmap, COLORREF crTransColor)
{
	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);

	// Load bitmap In
	hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmap), IMAGE_BITMAP, 0, 0, 0);

	return SetBitmap(hBitmap, crTransColor);
} // End of SetBitmap

//
// Parameters:
//		[IN]	hBitmap
//				Handle to the bitmap to use as background.
//		[IN]	crTransColor
//				A COLORREF value indicating the color to "remove" from the
//				bitmap. When crTransColor is specified (different from -1L)
//				a region will be created using the supplied bitmap and applied
//				to the window.
//
// Return value:
//		BKDLGST_OK
//			Function executed successfully.
//		BKDLGST_INVALIDRESOURCE
//			The resource specified cannot be found or loaded.
//		BKDLGST_FAILEDREGION
//			Failed creating region
//
DWORD CBkDialogST::SetBitmap(HBITMAP hBitmap, COLORREF crTransColor)
{
	int		nRetValue;
	BITMAP	csBitmapSize;

	// Free any loaded resource
	FreeResources();

	if (hBitmap)
	{
		m_hBitmap = hBitmap;

		// Get bitmap size
		nRetValue = ::GetObject(hBitmap, sizeof(csBitmapSize), &csBitmapSize);
		if (nRetValue == 0)
		{
			FreeResources();
			return BKDLGST_INVALIDRESOURCE;
		} // if
		m_dwWidth = (DWORD)csBitmapSize.bmWidth;
		m_dwHeight = (DWORD)csBitmapSize.bmHeight;

#ifndef UNDER_CE
		// Create region ?
		if (crTransColor != -1L)
		{
			m_hRegion = ScanRegion(m_hBitmap, GetRValue(crTransColor), GetGValue(crTransColor), GetBValue(crTransColor));
			if (m_hRegion == NULL)
			{
				FreeResources();
				return BKDLGST_FAILEDREGION;
			} // if

			::SetWindowRgn(m_hWnd, m_hRegion, FALSE);
		} // if
#endif
	} // if

	Invalidate();

	return BKDLGST_OK;
} // End of SetBitmap

//
// Parameters:
//		[IN]	byMode
//				Specifies how the bitmap will be placed in the dialog background.
//		[IN]	bRepaint
//				If TRUE the dialog will be repainted.
//
// Return value:
//		BKDLGST_OK
//			Function executed successfully.
//		BKDLGST_INVALIDMODE
//			Invalid mode.
//
DWORD CBkDialogST::SetMode(BYTE byMode, BOOL bRepaint)
{
	if (byMode >= BKDLGST_MAX_MODES)	return BKDLGST_INVALIDMODE;

	// Set new mode
	m_byMode = byMode;

	if (bRepaint == TRUE)	Invalidate();

	return BKDLGST_OK;
} // End of SetMode

#ifndef UNDER_CE
DWORD CBkDialogST::ShrinkToFit(BOOL bRepaint)
{
	CRect	rWnd;
	CRect	rClient;
	DWORD	dwDiffCX;
	DWORD	dwDiffCY;

	GetWindowRect(&rWnd);
	GetClientRect(&rClient);

	dwDiffCX = rWnd.Width() - rClient.Width();
	dwDiffCY = rWnd.Height() - rClient.Height();

	m_byMode = BKDLGST_MODE_CENTER;

	MoveWindow(rWnd.left, rWnd.top, dwDiffCX + m_dwWidth, dwDiffCY + m_dwHeight, bRepaint);

	return BKDLGST_OK;
} // End of ShrinkToFit
#endif

#ifdef	BKDLGST_DEFINES
#undef	BKDLGST_DEFINES
#undef	WM_NCLBUTTONDOWN
#endif
