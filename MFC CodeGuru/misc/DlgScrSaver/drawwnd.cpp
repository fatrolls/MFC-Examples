// drawwnd.cpp : implementation file
//

#include "stdafx.h"
//#include <fstream.h>
#include <io.h>
#include <time.h>
#include "collect.h"
#include "DlgScrSaver.h"
#include "drawwnd.h"
#include "CImage.h"
#include "Meta.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

LPCTSTR CDrawWnd::m_lpszClassName = NULL;

// LoadBMP		- Loads a BMP file and creates a logical palette for it.
// Returns		- TRUE for success
// sBMPFile		- Full path of the BMP file
// phDIB		- Pointer to a HGLOBAL variable to hold the loaded bitmap
//			  Memory is allocated by this function but should be 
//			  released by the caller.
// pPal			- Will hold the logical palette
BOOL LoadBMP( LPCTSTR sBMPFile, HGLOBAL* phDIB, CPalette* pPal )
{
	CFile file;
	if( !file.Open( sBMPFile, CFile::modeRead) )
		return FALSE;

	BITMAPFILEHEADER bmfHeader;
	long nFileLen;

	nFileLen = file.GetLength();


	// Read file header
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return FALSE;

	// File type should be 'BM'
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
		return FALSE;

	HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, nFileLen);
	if (hDIB == 0)
		return FALSE;

	// Read the remainder of the bitmap file.
	if (file.ReadHuge((LPSTR)hDIB, nFileLen - sizeof(BITMAPFILEHEADER)) !=
		nFileLen - sizeof(BITMAPFILEHEADER) )
	{
		::GlobalFree(hDIB);
		return FALSE;
	}


	
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;

	int nColors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 
						1 << bmInfo.bmiHeader.biBitCount;

	// Create the palette
	if( nColors <= 256 )
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
			pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		pPal->CreatePalette( pLP );

		delete[] pLP;
	}

	*phDIB = hDIB;
	return TRUE;
}

void DrawDIB(CRect& rect, CDC* pDC, HGLOBAL hDIB, CPalette* pPal )
{
	LPVOID	lpDIBBits;		// Pointer to DIB bits
	BOOL	bSuccess=FALSE; 	// Success/fail flag

	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
	int nColors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 
						1 << bmInfo.bmiHeader.biBitCount;

	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors +
			bmInfo.bmiHeader.biClrUsed) +
			((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);
	
	if( pPal && (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE) )
	{
		pDC->SelectPalette(pPal, FALSE);
		pDC->RealizePalette();
	}

	int DestX = (rect.Width()- bmInfo.bmiHeader.biWidth) / 2;
	int DestY = (rect.Height()- bmInfo.bmiHeader.biHeight) / 2;
	int nDestWidth = bmInfo.bmiHeader.biWidth;
	int nDestHeight = bmInfo.bmiHeader.biHeight;
	
	while (nDestWidth > rect.Width() || nDestHeight > rect.Height())
	{
		nDestWidth /= 2;
		nDestHeight /= 2;
	}
	
	//int DestX = (::GetSystemMetrics(SM_CXSCREEN)- bmInfo.bmiHeader.biWidth) / 2;
	//int DestY = (::GetSystemMetrics(SM_CYSCREEN)- bmInfo.bmiHeader.biHeight) / 2;
	if (DestX < 0)
		DestX = 0;
	if (DestY < 0)
		DestY = 0;
/*
	::StretchDIBits(pDC->m_hDC, 					// hDC
				   DestX,							// DestX
				   DestY,							// DestY
				   nDestWidth,						// nDestWidth
				   nDestHeight,						// nDestHeight
				   0,								// SrcX
				   0,								// SrcY
				   bmInfo.bmiHeader.biWidth,		// SrcWidth
				   bmInfo.bmiHeader.biHeight,		// ScrHeight
				   lpDIBBits,						// lpBits
				   (LPBITMAPINFO)hDIB,				// lpBitsInfo
				   DIB_RGB_COLORS,	 				// wUsage
				   PATCOPY);						// ROP
*/
	::SetDIBitsToDevice(pDC->m_hDC, 				// hDC
				   DestX,							// DestX
				   DestY,							// DestY
				   nDestWidth,						// nDestWidth
				   nDestHeight,						// nDestHeight
				   0,								// SrcX
				   0,								// SrcY
				   0,								// nStartScan
				   bmInfo.bmiHeader.biHeight,		// nNumScans
				   lpDIBBits,						// lpBits
				   (LPBITMAPINFO)hDIB,				// lpBitsInfo
				   DIB_RGB_COLORS); 				// wUsage

}

void DrawImage(CRect& rect, CDC* pDC, CImage& img)
{
	int DestX = (rect.Width()- img.GetWidth()) / 2;
	int DestY = (rect.Height()- img.GetHeight()) / 2;
/* no stretching
	int nDestWidth = img.GetWidth();
	int nDestHeight = img.GetHeight();
	
	while (nDestWidth > rect.Width() || nDestHeight > rect.Height())
	{
		nDestWidth /= 2;
		nDestHeight /= 2;
	}
*/	
	if (DestX < 0)
		DestX = 0;
	if (DestY < 0)
		DestY = 0;
	img.Draw(pDC, DestX, DestY);
}

void DrawMetafile(CRect& rect, CDC* pDC, CMetaFile& wmf)
{
	int nDestWidth = wmf.GetWidth();
	int nDestHeight = wmf.GetHeight();
	
	if (nDestWidth == 0)
		nDestWidth = 1;
	if (nDestHeight == 0)
		nDestHeight = 1;

	while (nDestWidth > rect.Width() || nDestHeight > rect.Height())
	{
		nDestWidth /= 2;
		nDestHeight /= 2;
	}
	/*
	while (nDestWidth < rect.Width()/2 && nDestHeight < rect.Height()/2)
	{
		nDestWidth *= 2;
		nDestHeight *= 2;
	}
	*/
	
	int DestX = (rect.Width()- nDestWidth) / 2;
	int DestY = (rect.Height()- nDestHeight) / 2;
	
	if (DestX < 0)
		DestX = 0;
	if (DestY < 0)
		DestY = 0;
	CRect rc(DestX, DestY, DestX+nDestWidth, DestY+nDestHeight);
	CBrush brush(RGB(255,255,255));
	pDC->FillRect(&rc, &brush);
	wmf.Display(pDC, rc);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawWnd
void CDrawWnd::SearchFiles(const char* BitmapPath, const char* filter)
{
	struct _finddata_t c_file;
	long hFile;
	char Filter[_MAX_PATH];
	strcpy(Filter, BitmapPath);
	strcat(Filter, filter);
    if ((hFile = _findfirst(Filter, &c_file)) != -1L)
	{
		if ((c_file.attrib & _A_SUBDIR)==0)
		{
			CString* str = new CString(BitmapPath);
			(*str) += c_file.name;
			BitmapList.Insert(str);
			//os << (*str) << endl;
		}
		/* Find the rest of the .c files */
		while( _findnext( hFile, &c_file ) == 0 )
		{
			if ((c_file.attrib & _A_SUBDIR)==0)
			{
				CString* str = new CString(BitmapPath);
				(*str) += c_file.name;
				BitmapList.Insert(str);
				//os << (*str) << endl;
			}
		}

		_findclose( hFile );
	}
}

CDrawWnd::CDrawWnd(BOOL bAutoDelete)
{
	m_bAutoDelete = bAutoDelete;
	m_nPos = 0;
	m_nStep = 1;
	m_nCounter = 0;
	m_nTimerID = 123;
	m_rgnLast.CreateRectRgn(0,0,0,0);

	m_nWidth = AfxGetApp()->GetProfileInt("Config", "Width", 10);
	m_nSteps = AfxGetApp()->GetProfileInt("Config", "Resolution", 10);
	m_nStyle = AfxGetApp()->GetProfileInt("Config", "Style", PS_ENDCAP_ROUND|PS_JOIN_ROUND);
	if (m_nSteps < 1)
		m_nSteps = 1;
	m_logbrush.lbStyle = m_logbrushBlack.lbStyle = BS_SOLID;
	m_logbrush.lbHatch = m_logbrushBlack.lbHatch = 0;
	m_logbrush.lbColor = RGB(
		AfxGetApp()->GetProfileInt("Config", "ColorRed", 255),
		AfxGetApp()->GetProfileInt("Config", "ColorGreen", 0),
		AfxGetApp()->GetProfileInt("Config", "ColorBlue", 0));
	m_logbrushBlack.lbColor = RGB(0, 0, 0);

	// initialize BitmapList
	char DefaultPath[_MAX_PATH];
	HINSTANCE hModul = AfxGetInstanceHandle();
	::GetModuleFileName(hModul, DefaultPath, sizeof(DefaultPath)-1);

	while (strlen(DefaultPath) > 0 && DefaultPath[strlen(DefaultPath)-1]!='\\')
		DefaultPath[strlen(DefaultPath)-1] = 0;
	BitmapPath = AfxGetApp()->GetProfileString("Config", "BitmapPath", DefaultPath);
	if (BitmapPath.GetLength() == 0)
	{
		BitmapPath = DefaultPath;
	}
	if (BitmapPath.GetAt(BitmapPath.GetLength()-1) != '\\')
	{
		BitmapPath += "\\";
	}
	//ofstream os("c:\\test.txt");
	//os << AfxGetApp()->m_pszAppName << endl;
	//os << DefaultPath << endl;
	//os << BitmapPath << endl;

	// Metafiles
	SearchFiles(BitmapPath, "*.wmf");
	SearchFiles(BitmapPath, "*.emf");

	// Bitmaps
	SearchFiles(BitmapPath, "*.bmp");
	SearchFiles(BitmapPath, "*.dib");
	SearchFiles(BitmapPath, "*.rle");

	// JPEG
	SearchFiles(BitmapPath, "*.jpg");
	SearchFiles(BitmapPath, "*.jpeg");
	SearchFiles(BitmapPath, "*.jpe");
	SearchFiles(BitmapPath, "*.jif");
	SearchFiles(BitmapPath, "*.jfif");
	
	// GIF
	SearchFiles(BitmapPath, "*.gif");

	// PNG
	SearchFiles(BitmapPath, "*.png");
}

CDrawWnd::~CDrawWnd()
{
}


BEGIN_MESSAGE_MAP(CDrawWnd, CWnd)
	//{{AFX_MSG_MAP(CDrawWnd)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPoint pos(GetScrollPosition());
	CRect rect;
	GetClientRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (pDoc->GetImage())
	{
		int x = -pos.x;
		int y = -pos.y;
		if (width >= pDoc->GetImage()->GetWidth())
			x = (width - pDoc->GetImage()->GetWidth())/2;
		if (height >= pDoc->GetImage()->GetHeight())
			y = (height - pDoc->GetImage()->GetHeight())/2;

		CDC *dc = GetDC();
		CPalette *hOldPal = 0;
		if (pDoc->GetImage()->GetPalette())
		{
			hOldPal = dc->SelectPalette(pDoc->GetImage()->GetPalette(), TRUE);
			dc->RealizePalette();
		}

		if (pDoc->GetStretchMode())
		{
			SetScrollSizes(MM_TEXT,
				CSize(0,0));
			pDoc->GetImage()->Stretch(dc, 0, 0, width, height);
		}
		else
		{
			SetScrollSizes(MM_TEXT,
				CSize(pDoc->GetImage()->GetWidth(), pDoc->GetImage()->GetHeight()));
			pDoc->GetImage()->Draw(dc, x, y);
		}

//		dc->SelectPalette(hOldPal, TRUE);
		ReleaseDC(dc);
	}
}
*/

void CDrawWnd::Draw(CDC& dc, int nWidth) 
{
	CBrush brush(RGB(0,0,0));
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(&rect, &brush);

	/*
	BYTE* buffer = new BYTE[5000000];
	readpcx(buffer, "F:\\swag\\pas\\chess.pcx");
	*/
	/*
	PCXHEADER hdr;
	BYTE* buffer = ReadPCX("F:\\swag\\pas\\chess.pcx", hdr);
	if (buffer)
	{
		DisplayPCX(&dc, rect, hdr, buffer);
	}
	*/
	BOOL bOK;
	long anz = BitmapList.Count();
	if (anz == 0)
		return;

	long index = m_nCounter % anz;
	//long index = abs(rand()) % anz;
	CPalette pal;
	HGLOBAL hBmp = NULL;
	bOK = LoadBMP(*(BitmapList.At(index)), &hBmp, &pal);
	if (bOK)
	{
		DrawDIB(rect, &dc, hBmp, &pal);
		GlobalFree(hBmp);
		return;
	}
	//else
	CMetaFile emf;
	emf.Read(*(BitmapList.At(index)));
	if (emf.IsOK())
	{
		DrawMetafile(rect, &dc, emf);
		return;
	}
	//else
	CImage img(*(BitmapList.At(index)));
	if (img.IsOK())
	{
		CPalette* hOldPal = NULL;
		if (img.GetPalette())
		{
			hOldPal = dc.SelectPalette(img.GetPalette(), TRUE);
			dc.RealizePalette();
		}
		DrawImage(rect, &dc, img);
		//img.Draw(&dc);
		return;
	}
}

void CDrawWnd::SetSpeed(int nSpeed)
{
	KillTimer(m_nTimerID);
	VERIFY((m_nTimerID = SetTimer(m_nTimerID, 20*(50+500-nSpeed*5), NULL)) != 0);
}


/////////////////////////////////////////////////////////////////////////////
// CDrawWnd message handlers

void CDrawWnd::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_nTimerID)
	{
		m_nCounter++;
		m_nPos += m_nStep;
		if (m_nPos > m_nSteps || m_nPos < 0)
		{
			m_nStep = -m_nStep;
			m_nPos += m_nStep;
		}
		CClientDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		int nWidth = m_nWidth * rect.Width() + ::GetSystemMetrics(SM_CXSCREEN)/2;
		nWidth = nWidth/::GetSystemMetrics(SM_CXSCREEN);
		Draw(dc, nWidth);
	}
	else	
		CWnd::OnTimer(nIDEvent);
}

void CDrawWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	m_rgnLast.DeleteObject();
	m_rgnLast.CreateRectRgn(0,0,0,0);
	CBrush brush(RGB(0,0,0));
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(&rect, &brush);
	int nWidth = m_nWidth * rect.Width() + ::GetSystemMetrics(SM_CXSCREEN)/2;
	nWidth = nWidth/::GetSystemMetrics(SM_CXSCREEN);
	Draw(dc, nWidth);
	// Do not call CWnd::OnPaint() for painting messages
}

void CDrawWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	m_nScale = cx/29;
	m_nHeight = cy;
}

int CDrawWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nSpeed = AfxGetApp()->GetProfileInt("Config", "Speed", 1);
	if (nSpeed < 0)
		nSpeed = 0;	
	SetSpeed(nSpeed);
	srand( (unsigned)time( NULL ) );
	return 0;
}

BOOL CDrawWnd::Create(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, 
	CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
    // Register a class with no cursor
	if (m_lpszClassName == NULL)
	{
    	m_lpszClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,
			::LoadCursor(AfxGetResourceHandle(), 
			MAKEINTRESOURCE(IDC_NULLCURSOR)));
	}

	// TODO: Add your specialized code here and/or call the base class
	return CreateEx(dwExStyle, m_lpszClassName, _T(""), dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 
		pParentWnd->GetSafeHwnd(), NULL, NULL );
}

void CDrawWnd::PostNcDestroy() 
{
	if (m_bAutoDelete)
		delete this;
}
