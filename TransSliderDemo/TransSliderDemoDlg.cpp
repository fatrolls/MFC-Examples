// TransSliderDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TransSliderDemo.h"
#include "TransSliderDemoDlg.h"
#include "MySliderControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransSliderDemoDlg dialog

CTransSliderDemoDlg::CTransSliderDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransSliderDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransSliderDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransSliderDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransSliderDemoDlg)
	DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransSliderDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTransSliderDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDCHANGEBITMAP, OnChangebitmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransSliderDemoDlg message handlers

BOOL CTransSliderDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetBitmap(IDB_BITMAP);
	m_Slider.SetTicFreq(20);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Slider2.SetThumbColors(RGB(0, 0, 196), RGB(0, 0, 255));
	m_Slider.SetThumbColors(RGB(196, 196, 0), RGB(255, 255, 0));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransSliderDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransSliderDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CTransSliderDemoDlg::SetBitmap(UINT uResourceID)
{
	BITMAP bm;
	BOOL bRet;

	// Detach previous resources
	m_BmpPattern.Detach();  
	m_BmpPalette.Detach();  

	// Default return value
	bRet = TRUE;

	// Load new bitmap
	if (uResourceID != 0)
	{
		bRet = GetBitmapAndPalette(uResourceID, m_BmpPattern, m_BmpPalette);
		// If all ok
		if (bRet == TRUE)
		{
			// Get dimension
			m_BmpPattern.GetBitmap(&bm);
			// Width of the bitmap
			m_nBmpWidth = bm.bmWidth;
			// Height of the bitmap
			m_nBmpHeight = bm.bmHeight;
		}
	}

	return bRet;
} // End of SetBitmap

BOOL CTransSliderDemoDlg::GetBitmapAndPalette(UINT nIDResource, CBitmap & bitmap, CPalette & pal)
{
	LPCTSTR lpszResourceName = (LPCTSTR)nIDResource;

	HBITMAP hBmp = (HBITMAP)::LoadImage( AfxGetInstanceHandle(), 
		lpszResourceName, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);

	if (hBmp == NULL) return FALSE;

	bitmap.Attach(hBmp);

	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	bitmap.GetObject(sizeof(ds), &ds);

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL); // Desktop DC

	if(nColors > 256)
		pal.CreateHalftonePalette(&dc);
	else
	{
		// Create the palette
		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject( &bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;
		for (int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}
		pal.CreatePalette( pLP );
		delete[] pLP;
		delete[] pRGB;
	}
	return TRUE;
} // End of GetBitmapAndPalette


BOOL CTransSliderDemoDlg::TileBitmap(CDC* pDC, CRect rc)
{
	CDC MemDC;

	int x = 0, y = 0;

	// If there is a bitmap loaded
	if (m_BmpPattern.m_hObject != NULL)
	{
		MemDC.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = MemDC.SelectObject(&m_BmpPattern);

		// Tile the bitmap
		while (y < rc.Height()) 
		{
			while(x < rc.Width()) 
			{
				pDC->BitBlt(x, y, m_nBmpWidth, m_nBmpHeight, &MemDC, 0, 0, SRCCOPY);
				x += m_nBmpWidth;
			}
			x = 0;
			y += m_nBmpHeight;
		}

		MemDC.SelectObject(pOldBitmap);

		return TRUE;
	}

	return FALSE; // Normal behaviour
} // End of TileBitmap

BOOL CTransSliderDemoDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;

	GetClientRect(rc);

	if (TileBitmap(pDC, rc) == TRUE)
		return TRUE;
	else
		return CDialog::OnEraseBkgnd(pDC);
} // End of OnEraseBkgnd


void CTransSliderDemoDlg::OnChangebitmap() 
{
	static bool bm = false;
	bm = !bm;
	if (bm)
	{
		SetBitmap(IDB_BITMAP1);
	}
	else
	{
		SetBitmap(IDB_BITMAP);
	}
	m_Slider.DrawTransparent(TRUE);
	m_Slider2.DrawTransparent(TRUE);
	Invalidate();
}
